#ifdef ARR_TYPE

#include <stdlib.h>
#define COMB(x,y) x ## y
#define ARR_NAME(type) COMB(array_,type)
#define DECLARE_ARRAY(type) \
typedef struct COMB(array_,type){ \
    type *_buf; \
    int _cap; \
    int count; \
    type* (*at) (struct ARR_NAME(type)*, int); \
    void (*remove) (struct ARR_NAME(type)*, int); \
    void (*add) (struct ARR_NAME(type)*, type); \
    int (*contains) (struct ARR_NAME(type)*, type*, int (*comp) (type*, type*)); \
} COMB(array_,type)

DECLARE_ARRAY(ARR_TYPE);

#ifdef DEFINE_ARR


#define INIT_CAP 1

#define MAKE_CONSTRUCTOR(type) \
ARR_NAME(type) COMB(new_array_,type) (void) { \
    ARR_NAME(type) arr; \
    arr.count = 0; \
    arr._cap = INIT_CAP; \
    arr._buf = malloc(arr._cap * sizeof(type)); \
    arr.at = &COMB(at_,type); \
    arr.add = &COMB(add_,type); \
    arr.contains = &COMB(contains_,type); \
    arr.remove = &COMB(remove_,type); \
    return arr; \
}

#define MAKE_AT(type) \
type* COMB(at_,type) (ARR_NAME(type) *self, int ind) { \
    if(ind >= self->count || ind < 0) { \
        perror("Index out of bounds!\n"); \
        return NULL; } \
    return &(self->_buf[ind]); \
}

#define MAKE_REMOVE(type) \
void COMB(remove_,type) (ARR_NAME(type) *self, int ind) { \
    if(ind >= self->count || ind < 0) { \
        perror("Index out of bounds!\n"); \
        return; } \
    int i = ind; \
    for(i; i < self->count-1; i++){ \
        self->_buf[i] = self->_buf[i+1]; } \
    self->count--; \
}

#define MAKE_ADD(type) \
void COMB(add_,type) (ARR_NAME(type) *self, type elem) { \
    if(self->count >= self->_cap) { \
        self->_cap *= 2; \
        self->_buf = realloc(self->_buf, self->_cap * sizeof(type)); \
    } \
    self->_buf[self->count++] = elem; \
}

#define MAKE_CONTAINS(type) \
int COMB(contains_,type) (ARR_NAME(type) *self, \
    type* elem, int (*comp) (type*, type*)) { \
    int i; \
    for(i = 0; i < self->count; i++) { \
        if(comp(elem, &self->_buf[i])) { \
            return 1; } \
    } \
    return 0; \
}

MAKE_AT(ARR_TYPE);
MAKE_ADD(ARR_TYPE);
MAKE_CONTAINS(ARR_TYPE);
MAKE_REMOVE(ARR_TYPE);
MAKE_CONSTRUCTOR(ARR_TYPE);
#endif

#ifndef DEFINE_ARR
#define MAKE_CONSTRUCTOR_EX(type) \
ARR_NAME(type) COMB(new_array_,type) (void)

#define MAKE_AT_EX(type) \
type* COMB(at_,type) (ARR_NAME(type) *self, int ind)

#define MAKE_REMOVE_EX(type) \
void COMB(remove_,type) (ARR_NAME(type) *self, int ind)

#define MAKE_ADD_EX(type) \
void COMB(add_,type) (ARR_NAME(type) *self, type elem)

#define MAKE_CONTAINS_EX(type) \
int COMB(contains_,type) (ARR_NAME(type) *self, \
type elem, int (*comp) (type*, type*))

MAKE_AT_EX(ARR_TYPE);
MAKE_ADD_EX(ARR_TYPE);
MAKE_CONTAINS_EX(ARR_TYPE);
MAKE_REMOVE_EX(ARR_TYPE);
MAKE_CONSTRUCTOR_EX(ARR_TYPE);
#endif
#endif