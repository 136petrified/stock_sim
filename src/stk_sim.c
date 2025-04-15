#include "stk_sim.h"

// TODO: Update into linked list
void m_display_ticker(const struct Market *m) {
    // TODO: Also put this in a file for printout
}

struct Stock * m_find_stock(const struct Market *m, const char *sym) {
    
}

double generate_value() {
    srand(time(NULL));
    uint64_t ct = (uint64_t) time(NULL);
    unsigned mask = 0x7F;
    unsigned offset = ((unsigned) (~ct ^ mask) & mask) & mask;

    double a = (1 + (rand() % 10)) * ((rand() % 2) ? -1.0 : 1.0);
    double b = ((1 + (rand() % 10)) / 10) * ((rand() % 2) ? -1.0 : 1.0);
    double c = ((rand() + offset) % 64) * ((rand() % 2) ? -1.0 : 1.0);
    double x = rand() % 8;

    return a * sin(b * x + c);
}

struct Stock * s_init(const char *name, const char *sym, const char *sector, const double val,
const int status, const unsigned avail_shares, const unsigned total_shares) {
}

void s_refresh(struct Stock *stk_dest, const struct Stock *stk_src) {
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

void s_listall(const struct Stock *stk) {
    // TODO: Finish this function
}

void w_add_stock(struct Wallet *w, const struct Stock *stk, const unsigned shares) {
}

void w_buy(struct Wallet *w, const struct Market *m, const char *sym, const unsigned shares) {
}

void w_update_stock(struct Wallet *w, const struct Stock *stk, const unsigned shares) {
}

void pf_add_stock(struct Portfolio *pf, const struct Stock *stk, const unsigned shares) {
}

void pf_remove_stock(struct Portfolio *pf, const char *sym) {
}

struct PortfolioStock * pf_find_stock(const struct Portfolio *pf, const char *sym) {
}

void pf_update_stock(struct Portfolio *pf, const struct PortfolioStock *ps_src) {
}

void ps_update_stock(struct PortfolioStock *ps_dest, const struct PortfolioStock *ps_src) {
}

struct Portfolio * pf_delete_stocks(struct Portfolio *pf) {
}

struct Portfolio * pf_delete(struct Portfolio *pf) {
}
