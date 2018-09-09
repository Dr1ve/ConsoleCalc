/*
 * gtest_test.cpp
 *
 *  Created on: 09.09.2018
 *      Author: yfpby
 */

#include "gtest/gtest.h"
#include "../../ConsoleCalc/Expression.h"

TEST(googleTestTest, Test1)
{
	Context * cont = new Context();
	Expression * expr = cont->evaluate("1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5)");
	double num = expr->interpret();

	ASSERT_EQ(11, num);
}
TEST(googleTestTest, Test2)
{
	Context * cont = new Context();
	Expression * expr = cont->evaluate("(1+2+3+4)/2");
	double num = expr->interpret();

	ASSERT_EQ(5, num);
}
TEST(googleTestTest, Test3)
{
	Context * cont = new Context();
	Expression * expr = cont->evaluate("(1+2+(3/2))/3");
	double num = expr->interpret();

	ASSERT_EQ(1.5, num);
}
