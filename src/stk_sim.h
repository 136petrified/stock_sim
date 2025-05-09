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
struct WalletList;
struct WalletParam;
struct Stock;
struct StockList;
struct StockParam;
struct Portfolio;
struct PFList;
struct PortfolioStock;
struct PFSTockList;
struct Market;
struct MarketList;
struct MarketParam;
struct Loan;
struct LoanList;
struct LoanParam;

#include "stk_sim_psht.h"
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

    struct Wallet *             next;
};

struct WalletList {
/*  TYPE                        MEMBER                  */
    struct Wallet *             head;
    struct Wallet *             tail;
};

struct WalletParam {
/*  TYPE                        MEMBER                  */
    char *                      name;
    double                      bal;
    struct Portfolio *          portfolio;

    bool                        elligible_for_loan;
    struct LoanList *           loans; // 3 loans maximum
    unsigned                    loan_score;

    struct Wallet *             next;
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

    struct Stock *              next; // Linked list
};

struct StockList {
    struct Stock *              head;
    struct Stock *              tail;
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

    struct Stock *              next; // Linked list
};

struct Portfolio {
/*  TYPE                        MEMBER                  */
    char *                      name;

    struct PFSTOCK_HASHTABLE *  stocks;
    unsigned                    n_pfstocks;
};

struct PFList {
/*  TYPE                        MEMBER                  */
    struct Portfolio *          head;
    struct Portfolio *          tail;
    int                         size;
};

struct PortfolioStock {
/*  TYPE                        MEMBER                  */
    char *                      name;
    char *                      sym;
    unsigned                    owned_shares;

    struct PortfolioStock *     next; // Linked list
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

    struct Market *             next;
};

struct MarketList {
/*  TYPE                        MEMBER                  */
    struct Market *             head;
    struct Market *             tail;
    int                         size;
};

struct MarketParam {
    char *						name;

	unsigned					max_stocks;
    struct STOCK_HASHTABLE *    avail_stocks;   // Dynamically allocated
    unsigned                    n_stocks;

    int                         u_speed; // update speed
    bool                        is_open; // if open

    struct Market *             next;
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

    struct Loan *               next;
};

struct LoanList {
/*  TYPE                        MEMBER                  */
    struct Loan *               head;
    struct Loan *               tail;
    int                         size;
};

struct LoanParam{
/*  TYPE                        MEMBER                  */
    char *                      name;

    double                      principal;
    double                      interest;

    double                      total;
    unsigned                    fulfilled;

    unsigned                    req_score;
    time_t                      deadline;

    struct Loan *               next;
};

// static struct MarketList markets;
// static struct WalletList wallets;

// TODO: REDO .c
// TODO: Add list insert/remove for lists
// TODO: Update all init() funcs
// TODO: Look into spaCy and NLTK for sentiment-based changes
// TODO: Param structs
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

// MarketList
/*  TYPE                        MEMBER                  */
    struct MarketList *         ml_init();
	void						ml_insert(struct MarketList *ml, struct Market *m);
	struct MarketList *			ml_find(struct MarketList *ml, const char *name);
	void						ml_remove(struct MarketList *ml, const char *name);
    struct MarketList *         ml_destroy(struct MarketList *ml);

// MarketParam
    struct MarketParam *        mpm_init(const char *name, const unsigned max_stocks, struct STOCK_HASHTABLE *avail_stocks,
                                         const unsigned n_stocks, const int u_speed, bool is_open, struct Market *next);
    struct MarketParam *        mpm_destroy(struct MarketParam *mpm);

// Stock
/*  TYPE                        MEMBER                  */
    struct Stock *              s_init(const struct StockParam *spm);
    int                         s_is_full();
    void                        s_refresh(struct Stock *stk_dest, const struct Stock *stk_src);
    void                        s_update(struct Stock *stk_dest, const struct StockParam *spm);
    double                      s_get_percent(const double prev, const double curr);
    int                         s_bad_event();
    int                         s_good_event();
    void                        s_print();
    struct Stock *              s_destroy(struct Stock *stk);

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
                                         const double val,  
                                         const int status, const unsigned n_avail_shares,
                                         const unsigned n_total_shares, const char *hist, struct Stock *next);
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

// WalletList
    struct WalletList *         wl_init();
    void                        wl_insert(struct WalletList *wl, struct Wallet *w);
    struct Wallet *             wl_find(struct WalletList *wl, const char *name);
    void                        wl_remove(struct WalletList *wl, const char *name);
    struct WalletList *         wl_destroy(struct WalletList *wl);

// WalletParam
/*  TYPE                        MEMBER                  */
    struct WalletParam *        wpm_init(const char *name, const double bal, struct Portfolio *pf,
                                         bool elligible_for_loan, struct LoanList *loans, const unsigned loan_score,
                                         struct Wallet *next);
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

// PortfolioList
/*  TYPE                        MEMBER                  */
    struct PFList *		        pfl_init();
    void                        pfl_insert(struct PFList *pfl, struct Portfolio *pf);
    struct PortfolioStock *     pfl_find(struct PFList *pfl, const char *name);
    void                        pfl_remove(struct PFList *pfl, const char *namw);
    struct PFList *		        pfl_destroy(struct PFList *pfl);

// PortfolioStock
/*  TYPE                        MEMBER                  */
    struct PortfolioStock *     ps_init(const char *name, const char *sym, const unsigned shares);
    void                        ps_update(struct PortfolioStock *ps);
    void                        ps_update_stock(struct PortfolioStock *ps_dest, 
                                                const struct PortfolioStock *ps_src);
    struct PortfolioStock *     ps_destroy(struct PortfolioStock *ps);

// PFStockList
/*  TYPE                        MEMBER                  */
	struct PFStockList *	    pfsl_init();
    void                        pfsl_insert(struct PFStockList *pfsl, struct PortfolioStock *pfs);
    struct PortfolioStock *     pfsl_find(struct PFStockList *pfsl, const char *sym);
    void                        pfsl_remove(struct PFStockList *pfsl, const char *sym);
	struct PFStockList *		pfsl_destroy(struct PFStockList *pfsl);

// Loan
/*  TYPE                        MEMBER                  */ // TODO: Introduce scoring system
    struct Loan *               l_init(const unsigned total, const unsigned fulfilled, 
                                       const time_t deadline);
    void                        l_update(struct Loan *l);
    static unsigned             l_calc_loan_score(struct Loan *l, struct Wallet *w);
    inline unsigned             l_get_score_req(const struct Loan *l) { return l ? l->req_score : 0; }
    struct Loan *               l_destroy(struct Loan *l);

// LoanList
/*  TYPE                        MEMBER                  */
	struct LoanList *           ll_init();
    void                        ll_insert(struct LoanList *ll, struct Loan *l);
    struct LoanList *           ll_find(struct LoanList *ll, const char *name);
    void                        ll_remove(struct LoanList *ll, const char *name);
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