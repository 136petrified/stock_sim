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

struct PortfolioStock;
struct Stock;

#include "stk_sim_psht.h"
#include "stk_sim_stkht.h"

/*                          CONSTANT                VALUE */
constexpr int               NAME_MAX              = 20;
constexpr int               STOCK_SYMBOL_MAX      = 5;
constexpr double            MAX_BALANCE           = DBL_MAX;
constexpr int               LOAN_MAX              = 32767; // placeholder, TODO: make some function to calculate loans based on score
constexpr const char        ERR_FILE []           = "./err.txt";

// TODO: Merge all files to resolve linking errors

/*                          CONSTANT                VALUE */
/*
#define                     NAME_MAX                20
#define                     STOCK_SYMBOL_MAX        5
#define                     MAX_BALANCE             DBL_MAX
#define                     LOAN_MAX                32767
#define                     ERR_FILE                "./err.txt"
*/

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

    struct Stock *              next; // Linked list
};

struct StockList {
    struct Stock *              head;
    struct Stock *              tail;
};

struct Portfolio {
/*  TYPE                        MEMBER                  */
    struct PFSTOCK_HASHTABLE *  stocks;
    unsigned                    n_pfstocks;
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
};

struct Market {
/*  TYPE                        MEMBER                  */
	char *						name;

	int							max_stocks;
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
};

struct Loan {
/*  TYPE                        MEMBER                  */
    unsigned                    amount;
    unsigned                    fulfilled;
    time_t                      deadline;
    unsigned                    req_score;

    struct Loan *               next;
};

struct LoanList {
/*  TYPE                        MEMBER                  */
    struct Loan *               head;
    struct Loan *               tail;
};

struct MarketList markets;
struct WalletList wallets;

// TODO: Add list insert/remove for lists
// TODO: Update all init() funcs

// Market
/*  TYPE                        MEMBER                  */
    struct Market *             m_init(const char *name, const int max_stocks, const int u_speed);
    void                        m_display_ticker(const struct Market *m); // TODO: Add to event loop
    void                        m_add_stock(struct Market *m, struct Stock *stk);
    void                        m_remove_stock(struct Market *m, const char *sym);
    void                        m_update_stock(struct Market *m, const struct Stock *stk_src);
    struct Stock *              m_find_stock(const struct Market *m, const char *sym);
    struct Market *             m_destroy(struct Market *m);

// MarketList
/*  TYPE                        MEMBER                  */
    struct MarketList *         mlist_init();
	void						mlist_insert(struct Market *mlist);
	struct MarketList *			mlist_find(struct Market *mlist, const char *name);
	void						mlist_remove(struct Market *mlist);
    struct MarketList *         mlist_destroy(struct Market *mlist);

// Stock
/*  TYPE                        MEMBER                  */
    struct Stock *              s_init(const char *name, const char *sym, const char *sector,
                                       const double val, const int status, 
                                       const unsigned n_avail_shares, const unsigned n_total_shares);
    int                         s_is_full();
    void                        s_refresh(struct Stock *stk_dest, const struct Stock *stk_src);
    void                        s_update(struct Stock *stk_dest, const struct Stock *stk_src);
    double                      s_calc_diff(const double prev, const double curr);
    int                         s_bad_event();
    int                         s_good_event();
    void                        s_listall(const struct Stock *stk);
    struct Stock *              s_destroy(struct Stock *stk);

// LoanList
/*  TYPE                        MEMBER                  */
    struct StockList *          slist_init();
    void                        slist_insert();
    void                        slist_find();
    void                        slist_remove();
    struct StockList *          slist_destroy();

// Wallet
/*  TYPE                        MEMBER                  */
    struct Wallet *             w_init(const char *name, const int bal, struct Portfolio *pf, 
                                       const bool elligible_for_loan, struct LoanList *loans);
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
    struct Wallet *             w_destroy(struct Wallet *w);

// WalletList
    struct WalletList *         wl_init();
    struct WalletList *         wl_destroy(struct WalletList *wlist);

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

// PortfolioStock
/*  TYPE                        MEMBER                  */
    struct PortfolioStock *     ps_init(const char *name, const char *sym, const unsigned shares);
    void                        ps_update_stock(struct PortfolioStock *ps_dest, 
                                                const struct PortfolioStock *ps_src);
    struct PortfolioStock *     ps_destroy(struct PortfolioStock *ps);

// PFStockList
/*  TYPE                        MEMBER                  */
	struct PFStockList *		pfslist_init();
	struct PFStockList *		pfslist_destroy();

// Loan
/*  TYPE                        MEMBER                  */ // TODO: Introduce scoring system
    struct Loan *               l_init(const unsigned amount, const unsigned fulfilled, 
                                       const time_t deadline);
    inline unsigned             l_get_score_req(const struct Loan *l) { return l ? l->req_score : 0; }
    struct Loan *               l_destroy(struct Loan *l);

// LoanList
/*  TYPE                        MEMBER                  */
	struct LoanList *           llist_init();
	struct LoanList *           llist_destroy();

// General functions
/*  TYPE                        MEMBER                  */
    void                        print_err(const char *file, const char *msg);
    double                      generate_value(); // Value generator
    char *                      strdup(const char *str); // if < C23

#endif // _STKSIM_H