#include "stk_sim.h"

struct Market * m_init(const int u_speed) {
    struct Market *mkt = (struct Market *) malloc(sizeof(struct Market)); // NOTE: Market allocated here

    mkt->avail_stocks = STOCK_HASHTABLE_init(29);
    mkt->n_stocks = 0;
    mkt->u_speed = u_speed;

    return mkt;
}

void m_display_ticker(const struct Market *m) {
}

void m_add_stock(struct Market *m, struct Stock *stk) {
    m->avail_stocks = STOCK_HASHTABLE_insert(m->avail_stocks, stk);
    ++m->n_stocks;
}

void m_remove_stock(struct Market *m, const char *sym) {
    m->avail_stocks = STOCK_HASHTABLE_remove(m->avail_stocks, sym);
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
    m->avail_stocks = STOCK_HASHTABLE_destroy(m->avail_stocks);
    free(m);

    return NULL;
}

double s_calc_diff(const double prev, const double curr) {
    if (prev == 0) {
        return curr * 100;
    }

    return (curr / prev - 1) * 100;
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

double generate_value() {
    srand(time(NULL));
    uint64_t ct = (uint64_t) time(NULL);
    unsigned mask = 0x7F;
    unsigned offset = (unsigned) ((~ct ^ mask) & mask);

    double a = (1 + (rand() % 10)) * (rand() % 2 ? -1.0 : 1.0);
    double b = ((1 + (rand() % 10)) / 10) * (rand() % 2 ? -1.0 : 1.0);
    double c = ((rand() + offset) % 64) * (rand() % 2 ? -1.0 : 1.0);
    double x = rand() % 8;

    return a * sin(b * x + c);
}
