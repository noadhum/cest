#include "../cest.h"

int main(void)
{
     TEST_BEGIN();

     // Arithmetic
     EXPECT_EQ(int, 10 + 3, 13);
     EXPECT_EQ(int, 13 - 10, 3);
     EXPECT_EQ(int, 10 * 3, 30);
     EXPECT_EQ(int, 10 / 3, 3);

     // Bitwise
     EXPECT_EQ(int, 10 & 3, 2);
     EXPECT_EQ(int, 10 | 3, 11);
     EXPECT_EQ(int, 10 ^ 3, 9);
     EXPECT_EQ(int, 10 >> 3, 1);
     EXPECT_EQ(int, 10 << 3, 80);
     EXPECT_EQ(int, ~10, -11);

     // Unary

     // Post-increment
     {
          int x = 10;
          EXPECT_EQ(int, x++, 10);
          EXPECT_EQ(int, x, 11);
     }

     // Pre-increment
     {
          int x = 10;
          EXPECT_EQ(int, ++x, 11);
          EXPECT_EQ(int, x, 11);
     }

     // Post-decrement
     {
          int x = 10;
          EXPECT_EQ(int, x--, 10);
          EXPECT_EQ(int, x, 9);
     }

     // Pre-decrement
     {
          int x = 10;
          EXPECT_EQ(int, --x, 9);
          EXPECT_EQ(int, x, 9);
     }

     return TEST_END();
}
