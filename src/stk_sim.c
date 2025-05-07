#include "stk_sim.h"

struct Market * m_init(const char *name, const int max_stocks,const int u_speed) { // TODO: Update this
    struct Market *mkt = (struct Market *) malloc(sizeof(struct Market)); // NOTE: Market allocated here

    if (mkt == NULL) {
        print_err(ERR_FILE, "m_init(): Failed to allocate memory");
        return NULL;
    }

    m->name = strdup(name); // Dynamically allocated

    mkt->avail_stocks = STOCK_HASHTABLE_init(29);
    mkt->n_stocks = 0;
    mkt->u_speed = u_speed;

    return mkt;
}

void m_display_ticker(const struct Market *m) {
}

void m_add_stock(struct Market *m, struct Stock *stk) {
    STOCK_HASHTABLE_insert(m->avail_stocks, stk);
    ++m->n_stocks;
}

void m_remove_stock(struct Market *m, const char *sym) { // TODO::Error check later
    STOCK_HASHTABLE_remove(m->avail_stocks, sym);
    --m->n_stocks;
}

void m_update_stock(struct Market *m, const struct Stock *stk_src) {
    struct Stock *stk_dest = m_find_stock(m, stk_src->sym);

    if (stk_dest == NULL) {
        print_err(ERR_FILE, "m_update_stock(): Could not find stock");
        return;
    }

    s_update(stk_dest, stk_src);
}

struct Stock * m_find_stock(const struct Market *m, const char *sym) {
    return STOCK_HASHTABLE_find(m->avail_stocks, sym);
}

struct Market * m_destroy(struct Market *m) {
    m->avail_stocks = STOCK_HASHTABLE_destroy(m->avail_stocks); // avail_stocks is NULL
    free(m->name);
    free(m);

    return NULL;
}

struct Stock * s_init(const char *name, const char *sym, const char *sector,
const double val, const int status,
const unsigned n_avail_shares, const unsigned n_total_shares) {
    struct Stock *stk = (struct Stock *) malloc(sizeof(struct Stock));
    
    if (stk == NULL) {
        print_err(ERR_FILE, "s_init(): Failed to allocate memory");
        return;
    }

    stk->name           = strdup(name);     // NOTE: Dynamically allocated, free before updating
    stk->sym            = strdup(sym);      // NOTE: Dynamically allocated, free before updating
    stk->sector         = strdup(sector);   // NOTE: Dynamically allocated, free before updating
    stk->val            = val;
    stk->n_avail_shares = n_avail_shares;
    stk->n_total_shares = n_total_shares;
    stk->next           = NULL;

    return stk;
}

int s_is_full() {
    return 0; // TODO: Put empty/full funcs in hashtable header
}

int s_bad_event() {
    srand((time(NULL)));  // random seed
    int rval = rand();
    return rval % 67 == 0;
}

int s_good_event() {
    srand((time(NULL)));  // random seed
    int rval = rand();
    return rval % 103 == 0;
}

struct Stock * s_destroy(struct Stock *stk) {
    free(stk->name);
    free(stk->sym);
    free(stk->sector);

    free(stk);
    return NULL;
}

struct Wallet * w_init(const char *name, const int bal, struct Portfolio *pf,
const bool elligible_for_loan, struct LoanList *loans) {
    struct Wallet *wal = (struct Wallet *) malloc(sizeof(struct Wallet)); // Dynamically allocated

    wal->name               = strdup(name); // Dynamially allocated string, free required
    wal->bal                = bal;
    wal->portfolio          = pf;           // Free required
    wal->elligible_for_loan = elligible_for_loan;
    wal->loans              = loans;        // Free required
    wal->next               = NULL;         // Dealloc is already called for this

    return wal;
}

struct Wallet * w_destroy(struct Wallet *w) {
    return NULL; // TODO: Add insert, find, remove for lists
}

double generate_value() {
    srand(time(NULL));
    uint64_t ct = (uint64_t) time(NULL);
    unsigned mask = 0x7F;
    unsigned offset = (unsigned) ((~ct ^ mask) & mask);

    double a = (1 + (rand() % 14)) * (rand() % 2 ? -1.0 : 1.0);
    double b = ((1 + (rand() % 43)) / 43) * (rand() % 2 ? -1.0 : 1.0);
    double c = ((rand() + offset) % 64) * (rand() % 2 ? -1.0 : 1.0);
    double x = rand() % 43;

    return a * sin(b * x + c);
}
