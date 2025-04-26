#ifndef STK_SIM_PFSTOCK_HASHTABLE_H
#define STK_SIM_PFSTOCK_HASHTABLE_H

#include "stk_sim.h"

struct PFSTOCK_HASHTABLE {
    struct PFStockList **pfs_buckets;
    unsigned capacity;
};

struct PFSTOCK_HASHTABLE * PFSTOCK_HASHTABLE_init(const unsigned capacity);
unsigned PFSTOCK_HASHTABLE_hash(const char *stk_sym);
struct PFSTOCK_HASHTABLE * PFSTOCK_HASHTABLE_insert(struct PFSTOCK_HASHTABLE *table, struct PortfolioStock *ps);
struct PFSTOCK_HASHTABLE * PFSTOCK_HASHTABLE_remove(struct PFSTOCK_HASHTABLE *table, const char *sym);
struct PortfolioStock * STOCK_HASHTABLE_find(struct PFSTOCK_HASHTABLE *table, const char *sym);
struct PFSTOCK_HASHTABLE * STOCK_HASHTABLE_destroy(struct PFSTOCK_HASHTABLE *table);


#endif