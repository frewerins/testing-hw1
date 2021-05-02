//
// Created by akhtyamovpavel on 5/1/20.
//

#include "AddTestCase.h"
#include "Functions.h"


TEST_F(AddTestCase, test2) {
    ASSERT_EQ(5 + 7, Add(7, 5));
}

TEST_F(AddTestCase, test3) {
    ASSERT_EQ(1 + 0, Add(1, 0));
}
