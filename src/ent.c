#include <ent.h>
#include "config.h"

#if defined(ENT_GETENTROPY)
# include <unistd.h>
# if defined(ENT_GE_SYSRANDOM)
#   include <sys/random.h>
# endif

  int
  ent_getentropy(void* buf, size_t len)
  {
    return getentropy(buf, len);
  }

#elif defined(ENT_GETRANDOM) || defined(ENT_URANDOM)
# if defined(ENT_GETRANDOM)
#   define _GNU_SOURCE
#   include <unistd.h>
#   include <sys/syscall.h>
# else
#   include <stdio.h>
# endif
# include <errno.h>

  static int
  _ent_fail(void)
  {
    errno = EIO;
    return -1;
  }

  int
  ent_getentropy(void* buf, size_t len)
  {
    int r;

    if (len > 256)
      return _ent_fail();
# if defined(ENT_GETRANDOM)
    r = syscall(SYS_getrandom, buf, len, 0);
    if (r < 0)
      return r;
# else
    {
      FILE *f;

      if (!(f = fopen("/dev/urandom", "re")))
        return -1;
      r = fread(buf, 1, len, f);
      (void) fclose(f);
    }
# endif
    if (r != (int)len)
      return _ent_fail();
    return 0;
  }

#else
# error "libent: platform not supported"
#endif
