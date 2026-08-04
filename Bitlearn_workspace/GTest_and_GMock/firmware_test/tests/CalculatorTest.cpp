#include <gtest/gtest.h>
#include "Calculator.hpp"
#include <limits>

/*TEST(TestSuiteName, TestName) {
  ... test body ...
}*/

TEST(AdditionTest, PositiveNumbers)
{
    Calculator c;
    EXPECT_EQ(c.add(5,4),9);
}

TEST(AdditionTest, NegativeNumbers)
{
    Calculator c;
    EXPECT_EQ(c.add(-4,-5),-9);
}

TEST(AdditionTest, ZeroValues)
{
    Calculator c;
    EXPECT_EQ(c.add(10,0),10);
    EXPECT_EQ(c.add(0,10),10);
}


TEST(SubtractionTest, PositiveNumbers)
{
    Calculator c;
    EXPECT_EQ(c.sub(5,4),1);
}

TEST(SubtractionTest, NegativeNumbers)
{
    Calculator c;
    EXPECT_EQ(c.sub(-5,-4),-1);
}

TEST(SubtractionTest, ZeroValues)
{
    Calculator c;
    ASSERT_EQ(c.sub(0,10),-10) << "substraction failure";
    EXPECT_EQ(c.sub(10,0),10);
    
}


TEST(MultiplicationTest, PositiveNumbers)
{
    Calculator c;
    EXPECT_EQ(c.multiply(5,4),20);
}

TEST(MultiplicationTest, NegativeNumbers)
{
    Calculator c;
    EXPECT_EQ(c.multiply(-4,-4),16);
}
TEST(MultiplicationTest, ZeroValues)
{
    Calculator c;
    EXPECT_EQ(c.multiply(10,0),0);
    EXPECT_EQ(c.multiply(0,10),0);
}

TEST(AdditionTest, BoundaryConditions)
{
    Calculator c;
    int maxval = std::numeric_limits<int>::max();
    EXPECT_EQ(c.add(maxval,0),maxval);
}

TEST(SubtractionTest, BoundaryConditions)
{
    Calculator c;
    int minval = std::numeric_limits<int>::min();
    EXPECT_EQ(c.sub(minval,0),minval);
}

TEST(MultiplicationTest, BoundaryConditions)
{
    Calculator c;
    int maxval = std::numeric_limits<int>::max();
    EXPECT_EQ(c.multiply(maxval, 1),maxval);
}