#ifndef STK_SIM_STOCK_HASHTABLE_H
#define STK_SIM_STOCK_HASHTABLE_H

#include "stk_sim.h"

struct STOCK_HASHTABLE {
    /*  TYPE                        MEMBER                  */
    struct StockList *              stk_buckets;
    unsigned                        capacity;
};

/*  TYPE                        MEMBER                  */
    struct STOCK_HASHTABLE *    STOCK_HASHTABLE_init(const unsigned capacity);
    unsigned                    STOCK_HASHTABLE_hash(const char *stk_sym);
    void                        STOCK_HASHTABLE_insert(struct STOCK_HASHTABLE *table, struct Stock *stk);
    void                        STOCK_HASHTABLE_remove(struct STOCK_HASHTABLE *table, const char *sym);
    struct Stock *              STOCK_HASHTABLE_find(struct STOCK_HASHTABLE *table, const char *sym);
    struct STOCK_HASHTABLE *    STOCK_HASHTABLE_destroy(struct STOCK_HASHTABLE *table);

#endif // STK_SIM_STOCK_HASHTABLE_H