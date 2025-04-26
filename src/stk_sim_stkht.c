#include "stk_sim_stkht.h"

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
}

struct Stock * STOCK_HASHTABLE_find(struct STOCK_HASHTABLE *table, const char *sym) {
}

struct STOCK_HASHTABLE * STOCK_HASHTABLE_destroy(struct STOCK_HASHTABLE *table) {
}