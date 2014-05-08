#include "../include/main.h"
#include "../include/init.h"

#include <gmp.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <inttypes.h>

CACHE_ENTRIES cacheEntries = { 0 };
mpz_t vectorToLookup;

void *findMatch(void *args)
{
    size_t i = 0;
    ENTRY_MATCH_DATA *data = NULL;

    data = (ENTRY_MATCH_DATA *) args;

    // Determine if this cache entry matches the lookup vector
    for(i = 0; i < data->entryPtr->numIndices; i++)
    {
        if(mpz_tstbit(*(data->vectorToLookupPtr), data->entryPtr->indices[i]) !=
           data->entryPtr->values[i])
        {
            return (void *) false;
        }
    }

    return (void *) true;
}

int main(int argc, char **argv)
{
    printf("\n");

    // Initialize the resources by obtaining input
    init();

    printf("\nCreating %zu threads...\n", cacheEntries.numEntries);
    {
        size_t i = 0;
        pthread_t threadIds[cacheEntries.numEntries];
        ENTRY_MATCH_DATA entryMatchData[cacheEntries.numEntries];

        // Build the data for each thread
        for(i = 0; i < cacheEntries.numEntries; i++)
        {
            entryMatchData[i].entryPtr = &(cacheEntries.entries[i]);
            entryMatchData[i].vectorToLookupPtr = &vectorToLookup;
        }

        // Create the threads
        for(i = 0; i < cacheEntries.numEntries; i++)
        {
            pthread_create(&threadIds[i], NULL, findMatch, &(entryMatchData[i]));
        }

        // Wait for all the threads
        printf("Waiting for all the created threads...\n\n");
        for(i = 0; i < cacheEntries.numEntries; i++)
        {
            bool foundMatch = false;
            pthread_join(threadIds[i], (void **) &foundMatch);

            if(foundMatch)
            {
                printf("Cache entry %zu matched\n", (i + 1));
            }
            else
            {
                printf("Cache entry %zu did not match\n", (i + 1));
            }
        }
    }

    // Be nice. Free all resources
    deinit();

    printf("\n");
    return 0;
}
