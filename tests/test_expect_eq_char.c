#include "../cest.h"

int main(void)
{
     TEST_BEGIN();

     // Character literal
     EXPECT_EQ(char, 'A', 'A');
     EXPECT_EQ(char, '0', '0');
     EXPECT_EQ(char, '\n', '\n');

     // Arithmetic

     // Post-increment
     {
          char x = 'A';
          EXPECT_EQ(char, x++, 'A');
          EXPECT_EQ(char, x, 'B');
     }

     // Pre-increment
     {
          char x = 'A';
          EXPECT_EQ(char, ++x, 'B');
          EXPECT_EQ(char, x, 'B');
     }

     // Post-decrement
     {
          char x = 'A';
          EXPECT_EQ(char, x--, 'A');
          EXPECT_EQ(char, x, '@');
     }

     // Pre-decrement
     {
          char x = 'A';
          EXPECT_EQ(char, --x, '@');
          EXPECT_EQ(char, x, '@');
     }

     return TEST_END();
}
