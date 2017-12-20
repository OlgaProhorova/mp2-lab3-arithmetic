// тесты для вычисления арифметических выражений

#include <gtest.h>
#include <string>
#include "arithmetic.h"

class teststr1: public ::testing::TestWithParam<string>
{
protected:
	string s;

public:
	teststr1(): s(GetParam()) {}
	~teststr1() {}
};

TEST_P(teststr1, error)
{
	ariphmetic vr(s);
	EXPECT_EQ(false, vr.check());
}

string valtest1[] = {"(1+1*)","(((x+1)*2)-1","1-*1","1*2-","4- 1"};

INSTANTIATE_TEST_CASE_P(Instantiation1,
	teststr1,
	::testing::ValuesIn(valtest1));

class TestStr2 : public teststr1 {};

TEST_P(TestStr2, no_error)
{
	ariphmetic vr(s);
	EXPECT_EQ(true, vr.check());
}

string valtest2[] = {"1+1","1.2+2.1","abc*(1-2)/34","-1/(1-0)","(-2)*5*(78)"};

INSTANTIATE_TEST_CASE_P(Instantiation2,
	TestStr2,
	::testing::ValuesIn(valtest2));

struct T
{
	string s;
	double res;

	T(string vs = "", double v = 0.0)
	{
		s = vs;
		res = v;
	}
};

class teststr3 : public ::testing::TestWithParam<T>
{
protected:
	T testcase;
public:
	teststr3() : testcase(GetParam()){}
	~teststr3() {}
};

TEST_P(teststr3, can_calculate)
{
	string str;
	str = minus(GetParam().s);
	ariphmetic res(str);
	res.getpolish();
	EXPECT_EQ(GetParam().res, res.calculate());
}

T valtest3[] = { T("10*((1.5-0.5)+2)",30),T("(-1*(3+5)-1)/9",-1), T("-3+2", -1)};

INSTANTIATE_TEST_CASE_P(Instantiation3,
	teststr3,
	::testing::ValuesIn(valtest3));

TEST(ariphmetic, testlex)
{
	string str="17+4.8(6*as)/b";
	str = minus(str);
	ariphmetic res(str);
	EXPECT_EQ("17",res.getstrn(0));
	EXPECT_EQ("+",res.getstrn(1));
	EXPECT_EQ("4.8",res.getstrn(2));
	EXPECT_EQ("(",res.getstrn(3));
	EXPECT_EQ("6",res.getstrn(4));
	EXPECT_EQ("*",res.getstrn(5));
	EXPECT_EQ("as",res.getstrn(6));
	EXPECT_EQ(")",res.getstrn(7));
	EXPECT_EQ("/",res.getstrn(8));
	EXPECT_EQ("b",res.getstrn(9));
};