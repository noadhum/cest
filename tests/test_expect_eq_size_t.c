#include "../cest.h"

int main(void)
{
     TEST_BEGIN();

     // Arithmetic
     EXPECT_EQ(size_t, 10 + 3, 13);
     EXPECT_EQ(size_t, 13 - 10, 3);
     EXPECT_EQ(size_t, 10 * 3, 30);
     EXPECT_EQ(size_t, 10 / 3, 3);

     // Bitwise
     EXPECT_EQ(size_t, 10 & 3, 2);
     EXPECT_EQ(size_t, 10 | 3, 11);
     EXPECT_EQ(size_t, 10 ^ 3, 9);
     EXPECT_EQ(size_t, 10 >> 3, 1);
     EXPECT_EQ(size_t, 10 << 3, 80);
     EXPECT_EQ(size_t, ~10, -11);

     // Unary

     // Post-increment
     {
          size_t x = 10;
          EXPECT_EQ(size_t, x++, 10);
          EXPECT_EQ(size_t, x, 11);
     }

     // Pre-increment
     {
          size_t x = 10;
          EXPECT_EQ(size_t, ++x, 11);
          EXPECT_EQ(size_t, x, 11);
     }

     // Post-decrement
     {
          size_t x = 10;
          EXPECT_EQ(size_t, x--, 10);
          EXPECT_EQ(size_t, x, 9);
     }

     // Pre-decrement
     {
          size_t x = 10;
          EXPECT_EQ(size_t, --x, 9);
          EXPECT_EQ(size_t, x, 9);
     }

     return TEST_END();
}
