#include "stk_sim.h"

struct MarketNode * mn_init(struct Market *m, struct MarketNode *next) {
    struct MarketNode *mn = (struct MarketNode *) malloc(sizeof(struct MarketNode));

    mn->data = m;
    mn->next = next;

    return mn;
}

void mn_destroy(struct MarketNode *mn) {
    if (mn == NULL) {
        print_err(ERR_FILE, "mn_destroy(): mn is NULL");
        return;
    }

    mn->data = m_destroy(mn->data); // Handle mn->data with other destructor
    free(mn);
}

struct MarketList * ml_init() {
    struct MarketList *ml = (struct MarketList *) malloc(sizeof(struct MarketList));
    if (ml == NULL) {
        print_err(ERR_FILE, "ml_init(): malloc() failed");
        return NULL;
    }

    ml->head = ml->tail = NULL;

    return ml;
}

void ml_insert(struct MarketList *ml, struct Market *m) {
    ml->head = mn_init(m, ml->head);
}

struct Market * ml_find(struct MarketList *ml, const char *name) {
    if (ml == NULL)
        return NULL;

    for (struct MarketNode *curr = ml->head; curr != NULL; curr = curr->next) {
        if (name == curr->data->name)
            return curr->data;
    }

    return NULL;
}

void ml_remove(struct MarketList *ml, const char *name) {
    struct MarketNode *target;

    if (ml == NULL) {
        print_err(ERR_FILE, "ml_remove(): ml is NULL");
        return;
    } else if (strcmp(name, ml->head->data->name) == 0) {
        target = ml->head;
        ml->head = ml->head->next;
        target->data = m_destroy(
        free(target);

        return;
    }

    struct MarketNode *curr = ml->head->next;
    struct MarketNode *prev = ml->head;

    for (; curr != NULL; curr = curr->next) {
        if (strcmp(name, ml->head->data->name) == 0) {
            target = curr;

        }
    }
}

struct MarketList * ml_destroy(struct MarketList *ml) {
    if (ml == NULL) {
        print_err(ERR_FILE, "ml_destroy: ml is NULL");
        return NULL;
    }

    struct MarketNode *target;
    struct MarketNode *curr = ml;

    while (curr != NULL) {
        target = curr;
        curr   = curr->next;
        free(target);
    }

    return NULL;
}

struct MarketParam * mpm_init(const char *name, const unsigned max_stocks, struct STOCK_HASHTABLE *avail_stocks,
                             const unsigned n_stocks, const int u_speed, bool is_open) {
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
                             const double val, const double diff, const double percentage, 
                             const int status, const unsigned n_avail_shares,
                             const unsigned n_total_shares, const char *hist) {
    struct StockParam *spm = (struct StockParam *) malloc(sizeof(struct StockParam));

    if (spm == NULL) {
        print_err(ERR_FILE, "spm_init(): malloc() failed");
        return NULL;
    }

    spm->name           = strdup(name);                 // Dynamically allocated, free required
    spm->sym            = strdup(sym);                  // Dynamically allocated, free required
    spm->sector         = strdup(sector);               // Dynamically allocated, free required
    spm->val            = val;
    spm->diff           = diff;
    spm->percentage     = percentage;
    spm->n_avail_shares = n_avail_shares;
    spm->n_total_shares = n_total_shares;
    spm->hist           = strdup(hist);                 // Dynamically allocated, free required

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