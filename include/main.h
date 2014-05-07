#ifndef __MAIN_H__INCLUDED__
#define __MAIN_H__INCLUDED__

#include <gmp.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct
{
    size_t numIndices;
    size_t *indices;
    uint8_t *values;
} CACHE_ENTRY;

typedef struct
{
    size_t numEntries;
    CACHE_ENTRY *entries;
} CACHE_ENTRIES;

typedef struct
{
    CACHE_ENTRY *entryPtr;
    mpz_t *vectorToLookupPtr;
} ENTRY_MATCH_DATA;

extern CACHE_ENTRIES cacheEntries;
extern mpz_t vectorToLookup;

#endif
