#ifndef _EXTERN_INLINE
#define _EXTERN_INLINE __extern_inline
#endif
_EXTERN_INLINE int __libc_use_alloca (size_t size)
{
  return size <= __MAX_ALLOCA_CUTOFF;
}
