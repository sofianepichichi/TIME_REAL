#ifndef __TIMEUTILS_H__
#define __TIMEUTILS_H__
#include <time.h>

typedef struct timespec tspec;

typedef long ptime;

/* time units */
#define SEC 0
#define MILLI   1
#define MICRO   2
#define NANO    3



/**    Computes s = a + b   */
tspec tspec_add(const tspec *a, const tspec *b);

/**
   Compares two timespecs
 */
int tspec_cmp(const tspec *a, const tspec *b);

/**     delta = a - b  */
tspec tspec_sub(const tspec *a, const tspec *b);

tspec tspec_from(double tu, int unit);

#endif 