#pragma once

typedef struct occam_allocator_tag
{
    void *(*alloc)(const size_t size, void * userdata);
    void (*free)(void *p, void * userdata);
    void *(*realloc)(void *p, const size_t size, void * userdata);
    void *userdata;
} occam_allocator_t;

#define occam_alloc(A, SZ) ((A) ? (A)->alloc(SZ, (A)->userdata) : malloc(SZ))
#define occam_realloc(A, P, SZ) ((A) ? (A)->realloc(P, SZ, (A)->userdata) : realloc(P, SZ))
#define occam_free(A, P) ((A) ?(A)->free(P, (A)->userdata) : free(P))
