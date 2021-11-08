#define _GNU_SOURCE

#define __attribute__(x)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __DARWIN__
#include <malloc/malloc.h>
#else
#include <malloc.h>
#endif

#include <gc.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>

#include <sys/select.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/types.h>

```
if echo $ARG | sed -e 's/-gc/NEOC_GC/' | grep NEOC_GC 1> /dev/null 2> /dev/null
then
    cat $PREFIX/include/neo-c2-gc.h | cpp -I . -U__GNUC__
else
    cat $PREFIX/include/neo-c2-no-gc.h | cpp -I . -U__GNUC__
fi
```

#define foreach(o1, o2) for(auto _obj = nomove (o2), auto o1 = _obj.begin(); !_obj.end(); o1 = _obj.next())

static void come_fd_zero(fd_set* fds)
{
    FD_ZERO(fds);
}

static void come_fd_set(int fd, fd_set* fds)
{
    FD_SET(fd, fds);
}

static int come_fd_isset(int fd, fd_set* fds)
{
    return FD_ISSET(fd, fds);
}
