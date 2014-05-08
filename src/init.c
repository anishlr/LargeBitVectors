#include "../include/main.h"
#include "../include/init.h"

#include <gmp.h>
#include <stdio.h>
#include <inttypes.h>

void init()
{
    size_t i = 0;

    // Read the number of cache entries
    fflush(stdin);
    scanf("%zu", &(cacheEntries.numEntries));

    // Read each cache entry
    cacheEntries.entries = calloc(cacheEntries.numEntries, sizeof(*cacheEntries.entries));
    for(i = 0; i < cacheEntries.numEntries; i++)
    {
        size_t j = 0;

        /*
         *  Read the number of indices whose bit values are specified. These are based from the
         *  LSB, not the MSB.
         */

        fflush(stdin);
        scanf("%zu", &(cacheEntries.entries[i].numIndices));

        // Read in all the indices and their corresponding values
        cacheEntries.entries[i].indices = calloc(cacheEntries.entries[i].numIndices,
                                                 sizeof(*(cacheEntries.entries[i].indices)));
        cacheEntries.entries[i].values = calloc(cacheEntries.entries[i].numIndices,
                                                sizeof(*(cacheEntries.entries[i].values)));
        for(j = 0; j < cacheEntries.entries[i].numIndices; j++)
        {
            fflush(stdin);
            scanf("%zu %" SCNu8, &(cacheEntries.entries[i].indices[j]),
                  &(cacheEntries.entries[i].values[j]));
        }
    }

    // Read the vector to lookup
    char temp[1000000];
    scanf("%s", temp);
    mpz_init_set_str(vectorToLookup, temp, 10);

    // Confirm the input data read
    printf("Number of cache entries = %zu\n", cacheEntries.numEntries);
    for(i = 0; i < cacheEntries.numEntries; i++)
    {
        size_t j = 0;

        printf("Cache entry %zu:\nNumber of indices = %zu\n", (i + 1),
               cacheEntries.entries[i].numIndices);

        for(j = 0; j < cacheEntries.entries[i].numIndices; j++)
        {
            printf("Index = %zu\tValue = %" SCNu8 "\n", cacheEntries.entries[i].indices[j],
                   cacheEntries.entries[i].values[j]);
        }

        printf("\n");
    }

    printf("Vector to look up = %s\n", mpz_get_str(NULL, 10, vectorToLookup));
}

void deinit()
{
    size_t i = 0;
    for(i = 0; i < cacheEntries.numEntries; i++)
    {
        free(cacheEntries.entries[i].indices);
        free(cacheEntries.entries[i].values);

        cacheEntries.entries[i].indices = NULL;
        cacheEntries.entries[i].values = NULL;
    }

    free(cacheEntries.entries);
    cacheEntries.entries = NULL;
}
