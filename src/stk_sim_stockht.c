#include "stk_sim_stockht.h"

struct STOCK_HASHTABLE * STOCK_HASHTABLE_init(const unsigned capacity) {
    struct STOCK_HASHTABLE *table = (struct STOCK_HASHTABLE *) malloc(sizeof(struct STOCK_HASHTABLE));
    table->stocks_buckets = (struct STOCK_HASHTABLE *) malloc(capacity * sizeof(struct Stock));
    table->capacity = capacity;

    for (unsigned i = 0; i < capacity; ++i) {
        table->stocks_buckets = NULL;
    }

    return table;
}

struct STOCK_HASHTABLE * STOCK_HASHTABLE_insert(struct STOCK_HASHTABLE *table, struct Stock *stk) {
    unsigned bucket = STOCK_HASHTABLE_hash(stk->sym);
    stk->next = table->stocks_buckets[bucket];
    table->stocks_buckets[bucket] = stk;
    return table;
}

struct STOCK_HASHTABLE * STOCK_HASHTABLE_remove(struct STOCK_HASHTABLE *table, const char *sym) {
    unsigned bucket = STOCK_HASHTABLE_hash(sym);
    for (struct Stock *curr = table->stocks_buckets[bucket], *prev = NULL; curr != NULL; curr = curr->next) {
        if (sym == curr->sym) {
            prev->next = curr->next;
            free(curr);

            if (prev == NULL) {
                table->stocks_buckets[bucket] = NULL;
            }

            return table;
        }

        prev = curr;
    }

    return table;
}

struct Stock * STOCK_HASHTABLE_find(struct STOCK_HASHTABLE *table, const char *sym) {
    unsigned bucket = STOCK_HASHTABLE_hash(sym);
    for (struct Stock *curr = table->stocks_buckets[bucket]; curr != NULL; curr = curr->next) {
        if (sym == curr->sym) {
            return curr;
        }
    }

    return NULL; // NULL if not found
}

struct STOCK_HASHTABLE * STOCK_HASHTABLE_destroy(struct STOCK_HASHTABLE *table) {
    for (unsigned i = 0; i < table->capacity; ++i) {
        struct Stock *stk = table->stocks_buckets[i];
        struct Stock *next;

        for (; stk != NULL; stk = next) {
            next = stk->next;
            free(stk);
        }

        table->stocks_buckets[i] = NULL;
    }
}