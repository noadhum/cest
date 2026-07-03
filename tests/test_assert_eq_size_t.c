#include "../cest.h"

int main(void)
{
     TEST_BEGIN();

     // Arithmetic
     ASSERT_EQ(size_t, 10 + 3, 13);
     ASSERT_EQ(size_t, 13 - 10, 3);
     ASSERT_EQ(size_t, 10 * 3, 30);
     ASSERT_EQ(size_t, 10 / 3, 3);

     // Bitwise
     ASSERT_EQ(size_t, 10 & 3, 2);
     ASSERT_EQ(size_t, 10 | 3, 11);
     ASSERT_EQ(size_t, 10 ^ 3, 9);
     ASSERT_EQ(size_t, 10 >> 3, 1);
     ASSERT_EQ(size_t, 10 << 3, 80);
     ASSERT_EQ(size_t, ~10, -11);

     // Unary

     // Post-increment
     {
          size_t x = 10;
          ASSERT_EQ(size_t, x++, 10);
          ASSERT_EQ(size_t, x, 11);
     }

     // Pre-increment
     {
          size_t x = 10;
          ASSERT_EQ(size_t, ++x, 11);
          ASSERT_EQ(size_t, x, 11);
     }

     // Post-decrement
     {
          size_t x = 10;
          ASSERT_EQ(size_t, x--, 10);
          ASSERT_EQ(size_t, x, 9);
     }

     // Pre-decrement
     {
          size_t x = 10;
          ASSERT_EQ(size_t, --x, 9);
          ASSERT_EQ(size_t, x, 9);
     }

     return TEST_END();
}
