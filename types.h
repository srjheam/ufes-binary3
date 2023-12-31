#ifndef _TYPES_H_
#define _TYPES_H_

#include <stdbool.h>

typedef void (*destructor_fn)(void *);
typedef void *(*copy_fn)(void *);
typedef int (*compar_fn)(void *, void *);

typedef unsigned char byte;

#endif
