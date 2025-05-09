#include "stk_sim.h"

struct MarketParam * mpm_init(const char *name, const unsigned max_stocks, struct STOCK_HASHTABLE *avail_stocks,
                             const unsigned n_stocks, const int u_speed, bool is_open, struct Market *next) {
    struct MarketParam *mpm = (struct MarketParam *) malloc(sizeof(struct MarketParam));

    if (mpm == NULL) {
        print_err(ERR_FILE, "mpm_init(): malloc() failed");
        return NULL;
    }

    mpm->name           = strdup(name);
    mpm->max_stocks     = max_stocks;
    mpm->avail_stocks   = avail_stocks;
    mpm->n_stocks       = n_stocks;
    mpm->u_speed        = u_speed;
    mpm->is_open        = is_open;
    mpm->next           = NULL;

    return mpm;
}

struct MarketParam * mpm_destroy(struct MarketParam *mpm) {
    if (mpm == NULL) {
        print_err(ERR_FILE, "mpm_destroy(): MarketParam is NULL");
        return NULL;
    }

    free(mpm->name);
    free(mpm);

    return NULL;
}

struct StockParam * spm_init(const char *name, const char *sym, const char *sector,
                             const double val, const int status, const unsigned n_avail_shares,
                             const unsigned n_total_shares, const char *hist, struct Stock *next) {
    struct StockParam *spm = (struct StockParam *) malloc(sizeof(struct StockParam));

    if (spm == NULL) {
        print_err(ERR_FILE, "spm_init(): malloc() failed");
        return NULL;
    }

    spm->name           = strdup(name);
    spm->sym            = strdup(sym);
    spm->sector         = strdup(sector);
    spm->val            = val;
    spm->diff           = 0;
    spm->percentage     = 0;
    spm->n_avail_shares = n_avail_shares;
    spm->n_total_shares = n_total_shares;
    spm->hist           = strdup(hist);
    spm->next           = NULL;

    return spm;
}

struct StockParam * spm_destroy(const struct StockParam *spm) {
    if (spm != NULL) {
        print_err(ERR_FILE, "mpm_destroy(): StockParam is NULL");
        return NULL;
    }

    free(spm->name);
    free(spm->sym);
    free(spm->sector);
    free(spm->hist);

    free(spm);

    return NULL;
}

int s_bad_event() {
    return rand() % 67 == 0;
}

int s_good_event() {
    return rand() % 103 == 0;
}

void print_err(const char *file, const char *msg) {
    FILE *fp = fopen(file, "a");
    fprintf(fp, "%s\n", msg);
    fclose(fp);
}

void stk_sim_loop() {
    // TODO: Implement this
    seed_random();

    while (1) {
        // here...
    }
}

double generate_value() {
    uint64_t ct = (uint64_t) time(NULL);
    unsigned mask = 0x7F;
    unsigned offset = (unsigned) ((~ct ^ mask) & mask);

    double a = (1 + (rand() % 14)) * (rand() % 2 ? -1.0 : 1.0);
    double b = ((1 + (rand() % 43)) / 43) * (rand() % 2 ? -1.0 : 1.0);
    double c = ((rand() + offset) % 64) * (rand() % 2 ? -1.0 : 1.0);
    double x = rand() % 43;

    return a * sin(b * x + c);
}

char * strdup(const char *str) {
    size_t buflen = strlen(str) + 1;
    char *new_str = (char *) malloc(buflen);

    if (new_str == NULL) {
        print_err(ERR_FILE, "strdup(): malloc() failed\n");
        return NULL;
    }

    strcpy(new_str, str);
    return new_str;
}