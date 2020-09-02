/*
  FUSE: Filesystem in Userspace
  Copyright (C) 2001-2007  Miklos Szeredi <miklos@szeredi.hu>

  This program can be distributed under the terms of the GNU GPLv2.
  See the file COPYING.
*/

/** @file
 *
 * minimal example filesystem using high-level API
 *
 * Compile with:
 *
 *     gcc -Wall hello.c `pkg-config fuse3 --cflags --libs` -o hello
 *
 * ## Source code ##
 * \include hello.c
 */


#include <sys/types.h>
#define FUSE_USE_VERSION 31

#include <fuse.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <assert.h>
#include <time.h>
#include <linux/kernel.h>

static struct stat rootstat;
static struct stat filestat;

/*
 * Command line options
 *
 * We can't set default values for the char* fields here because
 * fuse_opt_parse would attempt to free() them when the user specifies
 * different values on the command line.
 */
static struct options {
    const char *filename;
    const char *contents;
    int show_help;
} options;

#define OPTION(t, p)                           \
    { t, offsetof(struct options, p), 1 }
static const struct fuse_opt option_spec[] = {
                                              OPTION("--name=%s", filename),
                                              OPTION("--contents=%s", contents),
                                              OPTION("-h", show_help),
                                              OPTION("--help", show_help),
                                              FUSE_OPT_END
};

static void write_log(const char *s)
{
    FILE *fp = fopen("/tmp/log", "a");
    if (fp == NULL) {
        printf("cannot open\n");
        exit(1);
    }

    time_t t = time(NULL);
    fprintf(fp, "[%ld] %s", t, s);

    fclose(fp);
}

static void file_init(void)
{
    time_t t;
    filestat.st_mode = S_IFREG | 0444;
    filestat.st_nlink = 1;
    filestat.st_size = strlen(options.contents);
    filestat.st_atim.tv_sec = time(&t);
    filestat.st_mtim.tv_sec = t;
    filestat.st_ctim.tv_sec = t;

    rootstat.st_mode = S_IFDIR | 0755;
    rootstat.st_nlink = 2;
    rootstat.st_mtim.tv_sec = t;
}

static void *logfuse_init(struct fuse_conn_info *conn,
                        struct fuse_config *cfg)
{
    (void) conn;
    cfg->kernel_cache = 1;

    file_init();
    write_log("logfuse init.\n");
    return NULL;
}

void write_file(struct stat *stbuf)
{
    FILE *fp = fopen("/var/log/fuse.log", "a+");
    if (fp == NULL) {
        return;
    }

    fprintf(fp, "===========================\n");
    fprintf(fp, "stbuf->st_dev:          %lu\n", stbuf->st_dev);
    fprintf(fp, "stbuf->st_ino:          %lu\n", stbuf->st_ino);
    fprintf(fp, "stbuf->st_mode:         %u\n", stbuf->st_mode);
    fprintf(fp, "stbuf->st_nlink:        %lu\n", stbuf->st_nlink);
    fprintf(fp, "stbuf->st_uid:          %u\n", stbuf->st_uid);
    fprintf(fp, "stbuf->st_gid:          %u\n", stbuf->st_gid);
    fprintf(fp, "stbuf->st_rdev:         %ld\n", stbuf->st_rdev);
    fprintf(fp, "stbuf->st_size:         %lu\n", stbuf->st_size);
    fprintf(fp, "stbuf->st_blksize:      %ld\n", stbuf->st_blksize);
    fprintf(fp, "stbuf->st_blocks:       %ld\n", stbuf->st_blocks);
    fprintf(fp, "stbuf->st_atim.tv_nsec: %ld\n", stbuf->st_atim.tv_nsec);
    fprintf(fp, "stbuf->st_atim.tv_sec:  %ld\n", stbuf->st_atim.tv_sec);
    fprintf(fp, "stbuf->st_mtim.tv_nsec: %ld\n", stbuf->st_mtim.tv_nsec);
    fprintf(fp, "stbuf->st_mtim.tv_sec:  %ld\n", stbuf->st_mtim.tv_sec);
    fprintf(fp, "stbuf->st_ctim.tv_nsec: %ld\n", stbuf->st_ctim.tv_nsec);
    fprintf(fp, "stbuf->st_ctim.tv_sec:  %ld\n", stbuf->st_ctim.tv_sec);

    fclose(fp);
}

static int logfuse_getattr(const char *path, struct stat *stbuf, struct fuse_file_info *fi)
{
    (void) fi;
    int res = 0;

    memset(stbuf, 0, sizeof(struct stat));
    if (strcmp(path, "/") == 0) {
        stbuf->st_mode = rootstat.st_mode;
        stbuf->st_nlink = rootstat.st_nlink;
        stbuf->st_mtim.tv_sec = rootstat.st_mtim.tv_sec;
    } else if (strcmp(path+1, options.filename) == 0) {
        stbuf->st_mode = filestat.st_mode;
        stbuf->st_nlink = filestat.st_nlink;
        stbuf->st_size = filestat.st_size;
        stbuf->st_atim.tv_sec = filestat.st_atim.tv_sec;
        stbuf->st_mtim.tv_sec = filestat.st_mtim.tv_sec;
        stbuf->st_ctim.tv_sec = filestat.st_mtim.tv_sec;
    } else
        res = -ENOENT;

    write_log("logfuse getattr.\n");

    return res;
}

static int logfuse_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                         off_t offset, struct fuse_file_info *fi,
                         enum fuse_readdir_flags flags)
{
    (void) offset;
    (void) fi;
    (void) flags;

    if (strcmp(path, "/") != 0)
        return -ENOENT;

    filler(buf, ".", NULL, 0, 0);
    filler(buf, "..", NULL, 0, 0);
    filler(buf, options.filename, NULL, 0, 0);

    write_log("logfuse readdir.\n");

    return 0;
}

static int logfuse_open(const char *path, struct fuse_file_info *fi)
{
    if (strcmp(path+1, options.filename) != 0)
        return -ENOENT;

    if ((fi->flags & O_ACCMODE) != O_RDONLY)
        return -EACCES;

    write_log("logfuse open.\n");

    return 0;
}

static int logfuse_read(const char *path, char *buf, size_t size, off_t offset,
                      struct fuse_file_info *fi)
{
    size_t len;
    (void) fi;
    time_t t;

    if(strcmp(path+1, options.filename) != 0)
        return -ENOENT;

    len = strlen(options.contents);
    if (offset < len) {
        if (offset + size > len)
            size = len - offset;
        memcpy(buf, options.contents + offset, size);
    } else {
        size = 0;
    }

    filestat.st_atim.tv_sec = time(&t);
    write_log("logfuse read.\n");

    return size;
}

static void logfuse_destroy(void *private_data)
{
    write_log("logfuse destroy.\n");
}

static const struct fuse_operations hello_oper = {
                                                  .init = logfuse_init,
                                                  .getattr = logfuse_getattr,
                                                  .readdir = logfuse_readdir,
                                                  .open = logfuse_open,
                                                  .read = logfuse_read,
                                                  .destroy = logfuse_destroy,
};

static void show_help(const char *progname)
{
    printf("usage: %s [options] <mountpoint>\n\n", progname);
    printf("File-system specific options:\n"
           "    --name=<s>          Name of the \"hello\" file\n"
           "                        (default: \"hello\")\n"
           "    --contents=<s>      Contents \"hello\" file\n"
           "                        (default \"Hellop, World!\\n\")\n"
           "\n");
}

int main(int argc, char *argv[])
{
    int ret;
    struct fuse_args args = FUSE_ARGS_INIT(argc, argv);

    /* Set defaults -- we have to use strdup so that
       fuse_opt_parse can free the defaults if other
       values are specified */
    options.filename = strdup("logstamp");
    options.contents = strdup("stamp!!!\n");

    /* Parse options */
    if (fuse_opt_parse(&args, &options, option_spec, NULL) == -1)
        return 1;

    /* When --help is specified, first print our own file-system
       specific help text, then signal fuse_main to show
       additional help (by adding `--help` to the options again)
       without usage: line (by setting argv[0] to the empty
       string) */
    if (options.show_help) {
        show_help(argv[0]);
        assert(fuse_opt_add_arg(&args, "--help") == 0);
        args.argv[0][0] = '\0';
    }

    ret = fuse_main(args.argc, args.argv, &hello_oper, NULL);
    fuse_opt_free_args(&args);
    return ret;
}
