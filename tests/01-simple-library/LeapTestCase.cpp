//
// Created by akhtyamovpavel on 5/1/20.
//

#include "LeapTestCase.h"
#include <Functions.h>

TEST_F(LeapTestCase, test1) {
    ASSERT_THROW(IsLeap(-1), std::invalid_argument);
}

TEST_F(LeapTestCase, test2) {
    ASSERT_THROW(IsLeap(0), std::invalid_argument);
}

TEST_F(LeapTestCase, test3) {
    ASSERT_EQ(IsLeap(1904), true);
}

TEST_F(LeapTestCase, test4) {
    ASSERT_EQ(IsLeap(2000), true);
}

TEST_F(LeapTestCase, test5) {
    ASSERT_EQ(IsLeap(2001), false);
}

TEST_F(LeapTestCase, test6) {
    ASSERT_EQ(IsLeap(200), false);
}


TEST_F(LeapTestCase, MonthTest1) {
    ASSERT_EQ(GetMonthDays(2001, 2), 28);
}

TEST_F(LeapTestCase, MonthTest2) {
    ASSERT_EQ(GetMonthDays(2000, 2), 29);
}

TEST_F(LeapTestCase, MonthTest3) {
    ASSERT_THROW(GetMonthDays(1, 0), std::invalid_argument);
}

TEST_F(LeapTestCase, MonthTest4) {
    ASSERT_THROW(GetMonthDays(1, 13), std::invalid_argument);
}

TEST_F(LeapTestCase, MonthTest5) {
    ASSERT_EQ(GetMonthDays(2020, 12), 31);
}

TEST_F(LeapTestCase, MonthTest6) {
    ASSERT_EQ(GetMonthDays(2020, 1), 31);
}

TEST_F(LeapTestCase, MonthTest7) {
    ASSERT_EQ(GetMonthDays(2020, 4), 30);
}

TEST_F(LeapTestCase, MonthTest8) {
    ASSERT_EQ(GetMonthDays(2020, 6), 30);
}

TEST_F(LeapTestCase, MonthTest9) {
    ASSERT_EQ(GetMonthDays(2020, 9), 30);
}

TEST_F(LeapTestCase, MonthTest10) {
    ASSERT_EQ(GetMonthDays(2020, 11), 30);
}