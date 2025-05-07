#include "stk_sim.h"

TEST(Market, Init) {
    struct Market *mkt = m_init(30);
    EXPECT_EQ(mkt->u_speed, 30);
    mkt = m_destroy(mkt);
}