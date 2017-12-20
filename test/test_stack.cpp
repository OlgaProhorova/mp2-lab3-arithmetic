// тесты для стека

#include "stack.h"
#include <gtest.h>

template <class valtype>
class tstack1 : public testing::Test
{
	protected:
		stack <valtype> st1;
	public:
		tstack1(): st1(50)
		{
			valtype elem;
			for(int i=0;i<25;i++)
			{
				elem=(valtype)(i);
				st1.push(elem);
			}
		}
		virtual ~tstack1(){}
};

typedef ::testing::Types<int, double> MyTypes;

TYPED_TEST_CASE(tstack1, MyTypes);

TYPED_TEST(tstack1, can_get_top)
{
	TypeParam x = 30;
	st1.push(x);
	EXPECT_EQ(x, st1.gettop());
}

TYPED_TEST(tstack1, can_pop)
{
	TypeParam x = 30, y=16;
	st1.push(y);
	st1.push(x);
	st1.pop();
	EXPECT_EQ(y, st1.gettop());
}

TYPED_TEST(tstack1, can_push)
{
	TypeParam x = 30;
	st1.push(x);
	EXPECT_EQ(x, st1.gettop());
}

TYPED_TEST(tstack1, can_clean)
{
	st1.clean();
	EXPECT_EQ(0, st1.getnomber());
}

TYPED_TEST(tstack1, can_get_nomber)
{
	EXPECT_EQ(25, st1.getnomber());
}

TYPED_TEST(tstack1, empty)
{
	st1.clean();
	EXPECT_EQ(true, st1.isempty());
}