#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "hashtable.h"

struct hashtable
{
    // TODO1: define hashtable struct to use linkedlist as buckets

    linkedlist_t **buckets;
    int size; // how many buckets
};
/**
 * Hash function to hash a key into the range [0, max_range)
 */
static int hash(int key, int max_range)
{
    // TODO2: feel free to write your own hash function (NOT REQUIRED)
    key = (key > 0) ? key : -key;
    return key % max_range;
}

hashtable_t *ht_init(int num_buckets)
{
    // TODO3: create a new hashtable
    hashtable_t *myhash;
    myhash = malloc(sizeof(hashtable_t));
    myhash->buckets = malloc(sizeof(linkedlist_t *) * num_buckets);
    for (int i = 0; i < num_buckets; i++)
    {
        myhash->buckets[i] = ll_init();
    }
    myhash->size = num_buckets;

    return myhash;
}

void ht_free(hashtable_t *table)
{
    //TODO:4 free a hashtable from memory
    for (int i = 0; i < table->size; i++)
    {
        ll_free(table->buckets[i]);
    }
    free(table);
}

void ht_add(hashtable_t *table, int key, int value)
{
    // TODO5: create a new mapping from key -> value.
    // If the key already exists, replace the value.
    int bucket;
    bucket = hash(key, table->size);
    ll_add(table->buckets[bucket], key, value);
}

int ht_get(hashtable_t *table, int key)
{
    // TODO6: retrieve the value mapped to the given key.
    // If it does not exist, return 0
    int bucket;
    bucket = hash(key, table->size);
    return ll_get(table->buckets[bucket], key);
}

int ht_size(hashtable_t *table)
{
    // TODO7: return the number of mappings in this hashtable
    int total = 0;
    for (int i = 0; i < table->size; i++)
    {
        total += ll_size(table->buckets[i]);
    }

    return total;
}
