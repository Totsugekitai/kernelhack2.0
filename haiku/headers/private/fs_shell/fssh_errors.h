/*
 * Copyright 2007-2014, Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _FSSH_ERRORS_H
#define _FSSH_ERRORS_H


#include <limits.h>


/* Error baselines */
#define FSSH_B_GENERAL_ERROR_BASE		INT_MIN
#define FSSH_B_OS_ERROR_BASE			FSSH_B_GENERAL_ERROR_BASE + 0x1000
#define FSSH_B_APP_ERROR_BASE			FSSH_B_GENERAL_ERROR_BASE + 0x2000
#define FSSH_B_INTERFACE_ERROR_BASE		FSSH_B_GENERAL_ERROR_BASE + 0x3000
#define FSSH_B_MEDIA_ERROR_BASE			FSSH_B_GENERAL_ERROR_BASE + 0x4000 /* - 0x41ff */
#define FSSH_B_TRANSLATION_ERROR_BASE	FSSH_B_GENERAL_ERROR_BASE + 0x4800 /* - 0x48ff */
#define FSSH_B_MIDI_ERROR_BASE			FSSH_B_GENERAL_ERROR_BASE + 0x5000
#define FSSH_B_STORAGE_ERROR_BASE		FSSH_B_GENERAL_ERROR_BASE + 0x6000
#define FSSH_B_POSIX_ERROR_BASE			FSSH_B_GENERAL_ERROR_BASE + 0x7000
#define FSSH_B_MAIL_ERROR_BASE			FSSH_B_GENERAL_ERROR_BASE + 0x8000
#define FSSH_B_PRINT_ERROR_BASE			FSSH_B_GENERAL_ERROR_BASE + 0x9000
#define FSSH_B_DEVICE_ERROR_BASE		FSSH_B_GENERAL_ERROR_BASE + 0xa000

/* Developer-defined errors start at (B_ERRORS_END+1) */
#define FSSH_B_ERRORS_END				(FSSH_B_GENERAL_ERROR_BASE + 0xffff)

/* General Errors */
#define FSSH_B_NO_MEMORY				(FSSH_B_GENERAL_ERROR_BASE + 0)
#define FSSH_B_IO_ERROR					(FSSH_B_GENERAL_ERROR_BASE + 1)
#define FSSH_B_PERMISSION_DENIED		(FSSH_B_GENERAL_ERROR_BASE + 2)
#define FSSH_B_BAD_INDEX				(FSSH_B_GENERAL_ERROR_BASE + 3)
#define FSSH_B_BAD_TYPE					(FSSH_B_GENERAL_ERROR_BASE + 4)
#define FSSH_B_BAD_VALUE				(FSSH_B_GENERAL_ERROR_BASE + 5)
#define FSSH_B_MISMATCHED_VALUES		(FSSH_B_GENERAL_ERROR_BASE + 6)
#define FSSH_B_NAME_NOT_FOUND			(FSSH_B_GENERAL_ERROR_BASE + 7)
#define FSSH_B_NAME_IN_USE				(FSSH_B_GENERAL_ERROR_BASE + 8)
#define FSSH_B_TIMED_OUT				(FSSH_B_GENERAL_ERROR_BASE + 9)
#define FSSH_B_INTERRUPTED				(FSSH_B_GENERAL_ERROR_BASE + 10)
#define FSSH_B_WOULD_BLOCK				(FSSH_B_GENERAL_ERROR_BASE + 11)
#define FSSH_B_CANCELED					(FSSH_B_GENERAL_ERROR_BASE + 12)
#define FSSH_B_NO_INIT					(FSSH_B_GENERAL_ERROR_BASE + 13)
#define FSSH_B_BUSY						(FSSH_B_GENERAL_ERROR_BASE + 14)
#define FSSH_B_NOT_ALLOWED				(FSSH_B_GENERAL_ERROR_BASE + 15)
#define FSSH_B_BAD_DATA					(FSSH_B_GENERAL_ERROR_BASE + 16)
#define FSSH_B_DONT_DO_THAT				(FSSH_B_GENERAL_ERROR_BASE + 17)

#define FSSH_B_ERROR					(-1)
#define FSSH_B_OK						((int)0)
#define FSSH_B_NO_ERROR					((int)0)

/* Kernel Kit Errors */
#define FSSH_B_BAD_SEM_ID				(FSSH_B_OS_ERROR_BASE + 0)
#define FSSH_B_NO_MORE_SEMS				(FSSH_B_OS_ERROR_BASE + 1)

#define FSSH_B_BAD_THREAD_ID			(FSSH_B_OS_ERROR_BASE + 0x100)
#define FSSH_B_NO_MORE_THREADS			(FSSH_B_OS_ERROR_BASE + 0x101)
#define FSSH_B_BAD_THREAD_STATE			(FSSH_B_OS_ERROR_BASE + 0x102)
#define FSSH_B_BAD_TEAM_ID				(FSSH_B_OS_ERROR_BASE + 0x103)
#define FSSH_B_NO_MORE_TEAMS			(FSSH_B_OS_ERROR_BASE + 0x104)

#define FSSH_B_BAD_PORT_ID				(FSSH_B_OS_ERROR_BASE + 0x200)
#define FSSH_B_NO_MORE_PORTS			(FSSH_B_OS_ERROR_BASE + 0x201)

#define FSSH_B_BAD_IMAGE_ID				(FSSH_B_OS_ERROR_BASE + 0x300)
#define FSSH_B_BAD_ADDRESS				(FSSH_B_OS_ERROR_BASE + 0x301)
#define FSSH_B_NOT_AN_EXECUTABLE		(FSSH_B_OS_ERROR_BASE + 0x302)
#define FSSH_B_MISSING_LIBRARY			(FSSH_B_OS_ERROR_BASE + 0x303)
#define FSSH_B_MISSING_SYMBOL			(FSSH_B_OS_ERROR_BASE + 0x304)

#define FSSH_B_DEBUGGER_ALREADY_INSTALLED (FSSH_B_OS_ERROR_BASE + 0x400)

/* Application Kit Errors */
enum {
	FSSH_B_BAD_REPLY = FSSH_B_APP_ERROR_BASE,
	FSSH_B_DUPLICATE_REPLY,
	FSSH_B_MESSAGE_TO_SELF,
	FSSH_B_BAD_HANDLER,
	FSSH_B_ALREADY_RUNNING,
	FSSH_B_LAUNCH_FAILED,
	FSSH_B_AMBIGUOUS_APP_LAUNCH,
	FSSH_B_UNKNOWN_MIME_TYPE,
	FSSH_B_BAD_SCRIPT_SYNTAX,
	FSSH_B_LAUNCH_FAILED_NO_RESOLVE_LINK,
	FSSH_B_LAUNCH_FAILED_EXECUTABLE,
	FSSH_B_LAUNCH_FAILED_APP_NOT_FOUND,
	FSSH_B_LAUNCH_FAILED_APP_IN_TRASH,
	FSSH_B_LAUNCH_FAILED_NO_PREFERRED_APP,
	FSSH_B_LAUNCH_FAILED_FILES_APP_NOT_FOUND,
	FSSH_B_BAD_MIME_SNIFFER_RULE,
	FSSH_B_NOT_A_MESSAGE,
	FSSH_B_SHUTDOWN_CANCELLED,
	FSSH_B_SHUTTING_DOWN
};

/* Storage Kit/File System Errors */
#define FSSH_B_FILE_ERROR			(FSSH_B_STORAGE_ERROR_BASE + 0)
#define FSSH_B_FILE_NOT_FOUND		(FSSH_B_STORAGE_ERROR_BASE + 1)
#define FSSH_B_FILE_EXISTS			(FSSH_B_STORAGE_ERROR_BASE + 2)
#define FSSH_B_ENTRY_NOT_FOUND		(FSSH_B_STORAGE_ERROR_BASE + 3)
#define FSSH_B_NAME_TOO_LONG		(FSSH_B_STORAGE_ERROR_BASE + 4)
#define FSSH_B_NOT_A_DIRECTORY		(FSSH_B_STORAGE_ERROR_BASE + 5)
#define FSSH_B_DIRECTORY_NOT_EMPTY	(FSSH_B_STORAGE_ERROR_BASE + 6)
#define FSSH_B_DEVICE_FULL			(FSSH_B_STORAGE_ERROR_BASE + 7)
#define FSSH_B_READ_ONLY_DEVICE		(FSSH_B_STORAGE_ERROR_BASE + 8)
#define FSSH_B_IS_A_DIRECTORY		(FSSH_B_STORAGE_ERROR_BASE + 9)
#define FSSH_B_NO_MORE_FDS			(FSSH_B_STORAGE_ERROR_BASE + 10)
#define FSSH_B_CROSS_DEVICE_LINK	(FSSH_B_STORAGE_ERROR_BASE + 11)
#define FSSH_B_LINK_LIMIT			(FSSH_B_STORAGE_ERROR_BASE + 12)
#define FSSH_B_BUSTED_PIPE			(FSSH_B_STORAGE_ERROR_BASE + 13)
#define FSSH_B_UNSUPPORTED			(FSSH_B_STORAGE_ERROR_BASE + 14)
#define FSSH_B_PARTITION_TOO_SMALL	(FSSH_B_STORAGE_ERROR_BASE + 15)
#define FSSH_B_PARTIAL_READ			(FSSH_B_STORAGE_ERROR_BASE + 16)
#define FSSH_B_PARTIAL_WRITE		(FSSH_B_STORAGE_ERROR_BASE + 17)

/* POSIX Errors */
#define FSSH_E2BIG				(FSSH_B_POSIX_ERROR_BASE + 1)
#define FSSH_ECHILD				(FSSH_B_POSIX_ERROR_BASE + 2)
#define FSSH_EDEADLK			(FSSH_B_POSIX_ERROR_BASE + 3)
#define FSSH_EFBIG				(FSSH_B_POSIX_ERROR_BASE + 4)
#define FSSH_EMLINK				(FSSH_B_POSIX_ERROR_BASE + 5)
#define FSSH_ENFILE				(FSSH_B_POSIX_ERROR_BASE + 6)
#define FSSH_ENODEV				(FSSH_B_POSIX_ERROR_BASE + 7)
#define FSSH_ENOLCK				(FSSH_B_POSIX_ERROR_BASE + 8)
#define FSSH_ENOSYS				(FSSH_B_POSIX_ERROR_BASE + 9)
#define FSSH_ENOTTY				(FSSH_B_POSIX_ERROR_BASE + 10)
#define FSSH_ENXIO				(FSSH_B_POSIX_ERROR_BASE + 11)
#define FSSH_ESPIPE				(FSSH_B_POSIX_ERROR_BASE + 12)
#define FSSH_ESRCH				(FSSH_B_POSIX_ERROR_BASE + 13)
#define FSSH_EFPOS				(FSSH_B_POSIX_ERROR_BASE + 14)
#define FSSH_ESIGPARM			(FSSH_B_POSIX_ERROR_BASE + 15)
#define FSSH_EDOM				(FSSH_B_POSIX_ERROR_BASE + 16)
#define FSSH_ERANGE				(FSSH_B_POSIX_ERROR_BASE + 17)
#define FSSH_EPROTOTYPE			(FSSH_B_POSIX_ERROR_BASE + 18)
#define FSSH_EPROTONOSUPPORT	(FSSH_B_POSIX_ERROR_BASE + 19)
#define FSSH_EPFNOSUPPORT		(FSSH_B_POSIX_ERROR_BASE + 20)
#define FSSH_EAFNOSUPPORT		(FSSH_B_POSIX_ERROR_BASE + 21)
#define FSSH_EADDRINUSE			(FSSH_B_POSIX_ERROR_BASE + 22)
#define FSSH_EADDRNOTAVAIL		(FSSH_B_POSIX_ERROR_BASE + 23)
#define FSSH_ENETDOWN			(FSSH_B_POSIX_ERROR_BASE + 24)
#define FSSH_ENETUNREACH		(FSSH_B_POSIX_ERROR_BASE + 25)
#define FSSH_ENETRESET			(FSSH_B_POSIX_ERROR_BASE + 26)
#define FSSH_ECONNABORTED		(FSSH_B_POSIX_ERROR_BASE + 27)
#define FSSH_ECONNRESET			(FSSH_B_POSIX_ERROR_BASE + 28)
#define FSSH_EISCONN			(FSSH_B_POSIX_ERROR_BASE + 29)
#define FSSH_ENOTCONN			(FSSH_B_POSIX_ERROR_BASE + 30)
#define FSSH_ESHUTDOWN			(FSSH_B_POSIX_ERROR_BASE + 31)
#define FSSH_ECONNREFUSED		(FSSH_B_POSIX_ERROR_BASE + 32)
#define FSSH_EHOSTUNREACH		(FSSH_B_POSIX_ERROR_BASE + 33)
#define FSSH_ENOPROTOOPT		(FSSH_B_POSIX_ERROR_BASE + 34)
#define FSSH_ENOBUFS			(FSSH_B_POSIX_ERROR_BASE + 35)
#define FSSH_EINPROGRESS		(FSSH_B_POSIX_ERROR_BASE + 36)
#define FSSH_EALREADY			(FSSH_B_POSIX_ERROR_BASE + 37)
#define FSSH_EILSEQ     	    (FSSH_B_POSIX_ERROR_BASE + 38)
#define FSSH_ENOMSG         	(FSSH_B_POSIX_ERROR_BASE + 39)
#define FSSH_ESTALE				(FSSH_B_POSIX_ERROR_BASE + 40)
#define FSSH_EOVERFLOW			(FSSH_B_POSIX_ERROR_BASE + 41)
#define FSSH_EMSGSIZE			(FSSH_B_POSIX_ERROR_BASE + 42)
#define FSSH_EOPNOTSUPP			(FSSH_B_POSIX_ERROR_BASE + 43)
#define FSSH_ENOTSOCK			(FSSH_B_POSIX_ERROR_BASE + 44)
#define FSSH_EHOSTDOWN			(FSSH_B_POSIX_ERROR_BASE + 45)
#define	FSSH_EBADMSG			(FSSH_B_POSIX_ERROR_BASE + 46)
#define FSSH_ECANCELED			(FSSH_B_POSIX_ERROR_BASE + 47)
#define FSSH_EDESTADDRREQ		(FSSH_B_POSIX_ERROR_BASE + 48)
#define FSSH_EDQUOT				(FSSH_B_POSIX_ERROR_BASE + 49)
#define FSSH_EIDRM				(FSSH_B_POSIX_ERROR_BASE + 50)
#define FSSH_EMULTIHOP			(FSSH_B_POSIX_ERROR_BASE + 51)
#define FSSH_ENODATA			(FSSH_B_POSIX_ERROR_BASE + 52)
#define FSSH_ENOLINK			(FSSH_B_POSIX_ERROR_BASE + 53)
#define FSSH_ENOSR				(FSSH_B_POSIX_ERROR_BASE + 54)
#define FSSH_ENOSTR				(FSSH_B_POSIX_ERROR_BASE + 55)
#define FSSH_ENOTSUP			(FSSH_B_POSIX_ERROR_BASE + 56)
#define FSSH_EPROTO				(FSSH_B_POSIX_ERROR_BASE + 57)
#define FSSH_ETIME				(FSSH_B_POSIX_ERROR_BASE + 58)
#define FSSH_ETXTBSY			(FSSH_B_POSIX_ERROR_BASE + 59)

/* POSIX errors that can be mapped to BeOS error codes */
#define FSSH_ENOMEM				FSSH_B_NO_MEMORY
#define FSSH_EACCES				FSSH_B_PERMISSION_DENIED
#define FSSH_EINTR				FSSH_B_INTERRUPTED
#define FSSH_EIO				FSSH_B_IO_ERROR
#define FSSH_EBUSY				FSSH_B_BUSY
#define FSSH_EFAULT				FSSH_B_BAD_ADDRESS
#define FSSH_ETIMEDOUT			FSSH_B_TIMED_OUT
#define FSSH_EAGAIN 			FSSH_B_WOULD_BLOCK	/* SysV compatibility */
#define FSSH_EWOULDBLOCK	 	FSSH_B_WOULD_BLOCK	/* BSD compatibility */
#define FSSH_EBADF				FSSH_B_FILE_ERROR
#define FSSH_EEXIST				FSSH_B_FILE_EXISTS
#define FSSH_EINVAL				FSSH_B_BAD_VALUE
#define FSSH_ENAMETOOLONG		FSSH_B_NAME_TOO_LONG
#define FSSH_ENOENT				FSSH_B_ENTRY_NOT_FOUND
#define FSSH_EPERM				FSSH_B_NOT_ALLOWED
#define FSSH_ENOTDIR			FSSH_B_NOT_A_DIRECTORY
#define FSSH_EISDIR				FSSH_B_IS_A_DIRECTORY
#define FSSH_ENOTEMPTY			FSSH_B_DIRECTORY_NOT_EMPTY
#define FSSH_ENOSPC				FSSH_B_DEVICE_FULL
#define FSSH_EROFS				FSSH_B_READ_ONLY_DEVICE
#define FSSH_EMFILE				FSSH_B_NO_MORE_FDS
#define FSSH_EXDEV				FSSH_B_CROSS_DEVICE_LINK
#define FSSH_ELOOP				FSSH_B_LINK_LIMIT
#define FSSH_ENOEXEC			FSSH_B_NOT_AN_EXECUTABLE
#define FSSH_EPIPE				FSSH_B_BUSTED_PIPE

/* new error codes that can be mapped to POSIX errors */
#define	FSSH_B_BUFFER_OVERFLOW	FSSH_EOVERFLOW
#define FSSH_B_TOO_MANY_ARGS	FSSH_E2BIG
#define	FSSH_B_FILE_TOO_LARGE	FSSH_EFBIG
#define FSSH_B_RESULT_NOT_REPRESENTABLE FSSH_ERANGE
#define	FSSH_B_DEVICE_NOT_FOUND	FSSH_ENODEV
#define FSSH_B_NOT_SUPPORTED	FSSH_EOPNOTSUPP

/* Media Kit Errors */
enum {
	FSSH_B_STREAM_NOT_FOUND = FSSH_B_MEDIA_ERROR_BASE,
	FSSH_B_SERVER_NOT_FOUND,
	FSSH_B_RESOURCE_NOT_FOUND,
	FSSH_B_RESOURCE_UNAVAILABLE,
	FSSH_B_BAD_SUBSCRIBER,
	FSSH_B_SUBSCRIBER_NOT_ENTERED,
	FSSH_B_BUFFER_NOT_AVAILABLE,
	FSSH_B_LAST_BUFFER_ERROR
};

/* Mail Kit Errors */
enum {
	FSSH_B_MAIL_NO_DAEMON = FSSH_B_MAIL_ERROR_BASE,
	FSSH_B_MAIL_UNKNOWN_USER,
	FSSH_B_MAIL_WRONG_PASSWORD,
	FSSH_B_MAIL_UNKNOWN_HOST,
	FSSH_B_MAIL_ACCESS_ERROR,
	FSSH_B_MAIL_UNKNOWN_FIELD,
	FSSH_B_MAIL_NO_RECIPIENT,
	FSSH_B_MAIL_INVALID_MAIL
};

/* Printing Errors */
enum {
	FSSH_B_NO_PRINT_SERVER = FSSH_B_PRINT_ERROR_BASE
};

/* Device Kit Errors */
enum {
	FSSH_B_DEV_INVALID_IOCTL = FSSH_B_DEVICE_ERROR_BASE,
	FSSH_B_DEV_NO_MEMORY,
	FSSH_B_DEV_BAD_DRIVE_NUM,
	FSSH_B_DEV_NO_MEDIA,
	FSSH_B_DEV_UNREADABLE,
	FSSH_B_DEV_FORMAT_ERROR,
	FSSH_B_DEV_TIMEOUT,
	FSSH_B_DEV_RECALIBRATE_ERROR,
	FSSH_B_DEV_SEEK_ERROR,
	FSSH_B_DEV_ID_ERROR,
	FSSH_B_DEV_READ_ERROR,
	FSSH_B_DEV_WRITE_ERROR,
	FSSH_B_DEV_NOT_READY,
	FSSH_B_DEV_MEDIA_CHANGED,
	FSSH_B_DEV_MEDIA_CHANGE_REQUESTED,
	FSSH_B_DEV_RESOURCE_CONFLICT,
	FSSH_B_DEV_CONFIGURATION_ERROR,
	FSSH_B_DEV_DISABLED_BY_USER,
	FSSH_B_DEV_DOOR_OPEN,

	FSSH_B_DEV_INVALID_PIPE,
	FSSH_B_DEV_CRC_ERROR,
	FSSH_B_DEV_STALLED,
	FSSH_B_DEV_BAD_PID,
	FSSH_B_DEV_UNEXPECTED_PID,
	FSSH_B_DEV_DATA_OVERRUN,
	FSSH_B_DEV_DATA_UNDERRUN,
	FSSH_B_DEV_FIFO_OVERRUN,
	FSSH_B_DEV_FIFO_UNDERRUN,
	FSSH_B_DEV_PENDING,
	FSSH_B_DEV_MULTIPLE_ERRORS,
	FSSH_B_DEV_TOO_LATE
};


#endif	/* _FSSH_ERRORS_H */
