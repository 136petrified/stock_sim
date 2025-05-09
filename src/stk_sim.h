#ifndef _STKSIM_H
#define _STKSIM_H

#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Forward Declarations */

struct Wallet;
struct WalletNode;
struct WalletList;
struct WalletParam;
struct Stock;
struct StockNode;
struct StockList;
struct StockParam;
struct Portfolio;
struct PFNode;
struct PFList;
struct PortfolioStock;
struct PFStockNode;
struct PFStockList;
struct Market;
struct MarketNode;
struct MarketList;
struct MarketParam;
struct Loan;
struct LoanNode;
struct LoanList;
struct LoanParam;

#include "stk_sim_pfsht.h"
#include "stk_sim_stkht.h"

/*                          CONSTANT                VALUE */
constexpr int               NAME_MAX              = 20;
constexpr int               STOCK_SYMBOL_MAX      = 5;
constexpr double            MAX_BALANCE           = DBL_MAX;
constexpr unsigned          LOAN_MAX              = UINT_MAX; // placeholder, TODO: make some function to calculate loans based on score
constexpr const char        ERR_FILE []           = "./err.txt";

// TODO: Merge all files to resolve linking errors

/*                          CONSTANT                VALUE */
/*
#define                     NAME_MAX                20
#define                     STOCK_SYMBOL_MAX        5
#define                     MAX_BALANCE             DBL_MAX
#define                     LOAN_MAX                UINT_MAX
#define                     ERR_FILE                "./err.txt"
*/ // This can be turned on if STDC_VERSION < C23

// enum sectors;

struct Wallet {
/*  TYPE                        MEMBER                  */
    char *                      name;
    double                      bal;
    struct Portfolio *          portfolio;

    bool                        elligible_for_loan;
    struct LoanList *           loans; // 3 loans maximum
    unsigned                    loan_score;
};

struct WalletNode {
/*  TYPE                        MEMBER                  */
    struct Wallet *             data;
    struct WalletNode *         next;
};

struct WalletList {
/*  TYPE                        MEMBER                  */
    struct WalletNode *         head;
    struct WalletNode *         tail;
    int                         size;
};

struct WalletParam {
/*  TYPE                        MEMBER                  */
    char *                      name;
    double                      bal;
    struct Portfolio *          portfolio;

    bool                        elligible_for_loan;
    struct LoanList *           loans; // 3 loans maximum
    unsigned                    loan_score;
};


struct Stock {
/*  TYPE                        MEMBER                  */
    char *                      name;
    char *                      sym;
    char *                      sector;

    double                      val;
    double                      diff;
    double                      percentage;

    int                         status;
    unsigned                    n_avail_shares;
    unsigned                    n_total_shares;

    char *                      hist; // This is a file name!
};

struct StockNode {
/*  TYPE                        MEMBER                  */
    struct Stock *              data;
    struct StockNode *          next;
};

struct StockList {
    struct StockNode *          head;
    struct StockNode *          tail;
    int                         size;
};

struct StockParam { // alias spm
    /*  TYPE                        MEMBER                  */
    char *                      name;
    char *                      sym;
    char *                      sector;

    double                      val;
    double                      diff;
    double                      percentage;

    int                         status;
    unsigned                    n_avail_shares;
    unsigned                    n_total_shares;

    char *                      hist; // This is a file name!
};

struct Portfolio {
/*  TYPE                        MEMBER                  */
    char *                      name;

    struct PFSTOCK_HASHTABLE *  stocks;
    unsigned                    n_pfstocks;
};

struct PFNode {
/*  TYPE                        MEMBER                  */
    struct Portfolio *          data;
    struct PFNode *             next;
};

struct PFList {
/*  TYPE                        MEMBER                  */
    struct PFNode *             head;
    struct PFNode *             tail;
    int                         size;
};

struct PortfolioStock {
/*  TYPE                        MEMBER                  */
    char *                      name;
    char *                      sym;
    unsigned                    owned_shares;
};

struct PFStockList {
/*  TYPE                        MEMBER                  */
    struct PortfolioStock *     head;
    struct PortfolioStock *     tail;
    int                         size;
};

struct Market {
/*  TYPE                        MEMBER                  */
	char *						name;

	unsigned					max_stocks;
    struct STOCK_HASHTABLE *    avail_stocks;   // Dynamically allocated
    unsigned                    n_stocks;

    int                         u_speed; // update speed
    bool                        is_open; // if open
};

struct MarketNode {
    struct Market *             data;
    struct MarketNode *         next;
};

struct MarketList {
/*  TYPE                        MEMBER                  */
    struct MarketNode *         head;
    struct MarketNode *         tail;
    int                         size;
};

struct MarketParam {
    char *						name;

	unsigned					max_stocks;
    struct STOCK_HASHTABLE *    avail_stocks;   // Dynamically allocated
    unsigned                    n_stocks;

    int                         u_speed; // update speed
    bool                        is_open; // if open
};

struct Loan {
/*  TYPE                        MEMBER                  */
    char *                      name;

    double                      principal;
    double                      interest;

    double                      total;
    unsigned                    fulfilled;

    unsigned                    req_score;
    time_t                      deadline;
};

struct LoanNode {
    struct Loan *               data;
    struct LoanNode *           next;
};

struct LoanList {
/*  TYPE                        MEMBER                  */
    struct LoanNode *           head;
    struct LoanNode *           tail;
    int                         size;
};

struct LoanParam {
/*  TYPE                        MEMBER                  */
    char *                      name;

    double                      principal;
    double                      interest;

    double                      total;
    unsigned                    fulfilled;

    unsigned                    req_score;
    time_t                      deadline;
};

// static struct MarketList markets;
// static struct WalletList wallets;

// TO-DO list
// TODO: REDO .c
// TODO: Add list insert/remove for lists
// TODO: Hashtable implementation
// TODO: Update all init() funcs
// TODO: Look into spaCy and NLTK for sentiment-based changes
// TODO: Look into GUI for ticker, React for iOS, Android? Also webservers + API
// TODO: Loan scoring system, loan overhaul, overhaul bad / good events

// Market
/*  TYPE                        MEMBER                  */
    struct Market *             m_init(const struct MarketParam *mpm);
    void                        m_display_ticker(const struct Market *m); // TODO: Add to event loop
    void                        m_add_stock(struct Market *m, struct Stock *stk);
    void                        m_remove_stock(struct Market *m, const char *sym);
    void                        m_update_stock(struct Market *m, const struct Stock *stk_src);
    struct Stock *              m_find_stock(const struct Market *m, const char *sym);
    struct Market *             m_destroy(struct Market *m);

// MarketNode
/*  TYPE                        MEMBER                  */
    struct MarketNode *         mn_init(struct Market *m, struct MarketNode *next);
    void                        mn_destroy(struct MarketNode *mn);

// MarketList
/*  TYPE                        MEMBER                  */
    struct MarketList *         ml_init();
	void						ml_insert(struct MarketList *ml, struct Market *m);
	struct Market *			    ml_find(struct MarketList *ml, const char *name);
	void						ml_remove(struct MarketList *ml, const char *name);
    inline bool                 ml_is_empty(struct MarketList *ml) { return ml->size <= 0; }
    inline int                  ml_size(struct MarketList *ml) { return ml->size; }
    struct MarketList *         ml_destroy(struct MarketList *ml);

// MarketParam
    struct MarketParam *        mpm_init(const char *name, const unsigned max_stocks, struct STOCK_HASHTABLE *avail_stocks,
                                         const unsigned n_stocks, const int u_speed, bool is_open);
    struct MarketParam *        mpm_destroy(struct MarketParam *mpm);

// Stock
/*  TYPE                        MEMBER                  */
    struct Stock *              s_init(const struct StockParam *spm);
    bool                        s_is_empty();
    bool                        s_is_full();
    void                        s_refresh(struct Stock *stk_dest, const struct Stock *stk_src);
    void                        s_update(struct Stock *stk_dest, const struct StockParam *spm);
    double                      s_get_percent(const double prev, const double curr);
    int                         s_bad_event();
    int                         s_good_event();
    void                        s_print();
    struct Stock *              s_destroy(struct Stock *stk);

// StockNode
/*  TYPE                        MEMBER                  */
    struct Stock *              sn_init(struct Stock *stk, struct StockNode *next);
    void                        sn_destroy(struct StockNode *sn);

// StockList
/*  TYPE                        MEMBER                  */
    struct StockList *          sl_init();
    void                        sl_insert(struct StockList *sl, struct Stock *stk);
    struct Stock *              sl_find(struct StockList *sl, const char *sym);
    void                        sl_remove(struct StockList *sl, const char *sym);
    struct StockList *          sl_destroy(struct StockList *sl);

// StockParam
/*  TYPE                        MEMBER                  */
    struct StockParam *         spm_init(const char *name, const char *sym, const char *sector,
                                         const double val, const int status, const unsigned n_avail_shares,
                                         const unsigned n_total_shares, const char *hist);
    struct StockParam *         spm_destroy(struct StockParam *spm);

// Wallet
/*  TYPE                        MEMBER                  */
    struct Wallet *             w_init(const struct WalletParam *wpm);
    void                        w_add_stock(struct Wallet *w, const struct Stock *stk, 
                                            const unsigned shares);
    void                        w_remove_stock(struct Wallet *w, const struct Stock *stk);
    void                        w_update_stock(struct Wallet *w, const struct Stock *stk, 
                                               const unsigned shares);
    void                        w_buy(struct Wallet *w, const struct Market *m, const char *sym, 
                                      const unsigned shares);
    void                        w_sell(struct Wallet *w, const char *sym, const unsigned shares);
    void                        w_sellall(struct Wallet *w, const char *sym);
    void                        w_show_bal(struct Wallet *w);
    inline double               w_get_bal(struct Wallet *w) { return w ? w->bal : -1; }
    inline void                 w_set_bal(struct Wallet *w, const int val) { w->bal = val; }
    void                        w_update(struct Wallet *w, const struct WalletParam *wpm); // TODO: Implement this
    struct Wallet *             w_destroy(struct Wallet *w);

// WalletNode
/*  TYPE                        MEMBER                  */
    struct WalletNode *         wn_init(struct Wallet *w, struct WalletNode *next);
    void                        wn_destroy(struct WalletNode *wn);

// WalletList
/*  TYPE                        MEMBER                  */
    struct WalletList *         wl_init();
    void                        wl_insert(struct WalletList *wl, struct Wallet *w);
    struct Wallet *             wl_find(struct WalletList *wl, const char *name);
    void                        wl_remove(struct WalletList *wl, const char *name);
    inline bool                 wl_is_empty(struct WalletList *wl) { return wl->size <= 0; }
    inline int                  wl_size(struct WalletList *wl) { return wl->size; }
    struct WalletList *         wl_destroy(struct WalletList *wl);

// WalletParam
/*  TYPE                        MEMBER                  */
    struct WalletParam *        wpm_init(const char *name, const double bal, struct Portfolio *pf,
                                         bool elligible_for_loan, struct LoanList *loans, const unsigned loan_score);
    struct WalletParam *        wpm_destroy(struct WalletParam *wpm);

// Portfolio
/*  TYPE                        MEMBER                  */
    struct Portfolio *          pf_init();
    void                        pf_add_stock(struct Portfolio *pf, const struct Stock *stk, 
                                             const unsigned shares);
    void                        pf_remove_stock(struct Portfolio *pf, const char *sym);
    struct PortfolioStock *     pf_find_stock(const struct Portfolio *pf, const char *sym);
    void                        pf_update_stock(struct Portfolio *pf, 
                                                const struct PortfolioStock *ps_src);
    struct Portfolio *          pf_destroy_stocks(struct Portfolio *pf);
    struct Portfolio *          pf_destroy(struct Portfolio *pf);

// PortfolioNode
/*  TYPE                        MEMBER                  */
    struct PFNode *             pfn_init(struct Portfolio *pf, struct PFNode *next);
    void                        pfn_destroy(struct PFNode *pfn);

// PortfolioList
/*  TYPE                        MEMBER                  */
    struct PFList *		        pfl_init();
    void                        pfl_insert(struct PFList *pfl, struct Portfolio *pf);
    struct Portfolio *          pfl_find(struct PFList *pfl, const char *name);
    void                        pfl_remove(struct PFList *pfl, const char *name);
    inline bool                 pfl_is_empty(struct PFList *pfl) { return pfl->size <= 0; }
    inline int                  pfl_size(struct PFList *pfl) { return pfl->size; }
    struct PFList *		        pfl_destroy(struct PFList *pfl);

// PortfolioStock
/*  TYPE                        MEMBER                  */
    struct PortfolioStock *     pfs_init(const char *name, const char *sym, const unsigned shares);
    void                        pfs_update(struct PortfolioStock *pfs);
    void                        pfs_update_stock(struct PortfolioStock *pfs_dest, 
                                                const struct PortfolioStock *pfs_src);
    struct PortfolioStock *     pfs_destroy(struct PortfolioStock *pfs);

// PFStockNode
/*  TYPE                        MEMBER                  */
    struct PFStockNode *        pfsn_init(struct PortfolioStock *pfs, struct PFStockNode *next);
    void                        pfsn_destroy(struct PFStockNode *pfsn);

// PFStockList
/*  TYPE                        MEMBER                  */
	struct PFStockList *	    pfsl_init();
    void                        pfsl_insert(struct PFStockList *pfsl, struct PortfolioStock *pfs);
    struct PortfolioStock *     pfsl_find(struct PFStockList *pfsl, const char *sym);
    void                        pfsl_remove(struct PFStockList *pfsl, const char *sym);
    inline bool                 pfsl_is_empty(struct PFStockList *pfsl) { return pfsl->size <= 0; }
    inline int                  pfsl_size(struct PFStockList *pfsl) { return pfsl->size; }
	struct PFStockList *		pfsl_destroy(struct PFStockList *pfsl);

// Loan
/*  TYPE                        MEMBER                  */ // TODO: Introduce scoring system
    struct Loan *               l_init(const unsigned total, const unsigned fulfilled, 
                                       const time_t deadline);
    void                        l_update(struct Loan *l);
    static unsigned             l_calc_loan_score(struct Loan *l, struct Wallet *w);
    inline unsigned             l_get_score_req(const struct Loan *l) { return l ? l->req_score : 0; }
    struct Loan *               l_destroy(struct Loan *l);

// LoanNode
/*  TYPE                        MEMBER                  */
    struct LoanNode *           ln_init(struct Loan *l, struct LoanNode *next);
    void                        ln_destroy(struct LoanNode *ln);

// LoanList
/*  TYPE                        MEMBER                  */
	struct LoanList *           ll_init();
    void                        ll_insert(struct LoanList *ll, struct Loan *l);
    struct LoanList *           ll_find(struct LoanList *ll, const char *name);
    void                        ll_remove(struct LoanList *ll, const char *name);
    inline bool                 ll_is_empty(struct LoanList *ll) { return ll->size <= 0; }
    inline int                  ll_size(struct LoanList *ll) { return ll->size; }
	struct LoanList *           ll_destroy(struct LoanList *ll);

// LoanParam
/*  TYPE                        MEMBER                  */
    struct LoanParam *          lpm_init();
    struct LoanParam *          lpm_destroy(struct LoanParam *lpm);

// General functions
/*  TYPE                        MEMBER                  */
    void                        print_err(const char *file, const char *msg);
    static inline void          seed_random() { srand(time(NULL)); }
    void                        stk_sim_loop(); // NOTE: Must be called or else simulation stops!
    double                      generate_value(); // Value generator
    char *                      strdup(const char *str); // if < C23

#endif // _STKSIM_H