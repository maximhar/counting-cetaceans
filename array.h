/* A really cool generic array with pseudo-methods.
   methods:
    at: returns the element at the specified index, checks for bounds
    remove: deletes the element at the specified location
    add: adds the specified element to the end of the array
    contains: checks whether the specified criteria is contained within the
        array, using a supplied comparison function
    find: returns the first element that specifies the supplied criteria, using
        a supplied comparison function
    copy: returns a shallow copy of the array */
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
    int (*contains) (struct ARR_NAME(type)*, void*, int (*comp) (void*, type*)); \
    type* (*find) (struct ARR_NAME(type)*, void*, int (*comp) (void*, type*)); \
    struct ARR_NAME(type) (*copy) (struct ARR_NAME(type)*); \
} COMB(array_,type)

DECLARE_ARRAY(ARR_TYPE);

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
void* elem, int (*comp) (void*, type*))

#define MAKE_FIND_EX(type) \
type* COMB(find_,type) (ARR_NAME(type) *self, \
void* what, int (*comp) (void*, type*))

#define MAKE_COPY_EX(type) \
ARR_NAME(type) COMB(copy_,type) (ARR_NAME(type) *self)

MAKE_AT_EX(ARR_TYPE);
MAKE_ADD_EX(ARR_TYPE);
MAKE_CONTAINS_EX(ARR_TYPE);
MAKE_FIND_EX(ARR_TYPE);
MAKE_REMOVE_EX(ARR_TYPE);
MAKE_COPY_EX(ARR_TYPE);
MAKE_CONSTRUCTOR_EX(ARR_TYPE);

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
    arr.copy = &COMB(copy_,type); \
    arr.find = &COMB(find_,type); \
    return arr; \
}

#define MAKE_COPY(type) \
ARR_NAME(type) COMB(copy_,type) (ARR_NAME(type) *self) { \
    ARR_NAME(type) cpy = COMB(new_array_,type)(); \
    int i; \
    for(i = 0; i < self->count; i++){ \
        type el = *self->at(self,i); \
        cpy.add(&cpy,el); } \
    return cpy; \
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
    void* elem, int (*comp) (void*, type*)) { \
    if((self->find(self, (void*)elem, comp)) != NULL) { \
        return 1; } else { \
        return 0; }\
}

#define MAKE_FIND(type) \
type* COMB(find_,type) (ARR_NAME(type) *self, \
void* what, int (*comp) (void*, type*)) {\
    int i; \
    for(i = 0; i < self->count; i++) { \
        if(comp(what, &self->_buf[i])) { \
            return &self->_buf[i]; } \
    } \
    return NULL; \
}

MAKE_AT(ARR_TYPE);
MAKE_ADD(ARR_TYPE);
MAKE_CONTAINS(ARR_TYPE);
MAKE_REMOVE(ARR_TYPE);
MAKE_COPY(ARR_TYPE);
MAKE_FIND(ARR_TYPE);
MAKE_CONSTRUCTOR(ARR_TYPE);
#endif

#endif