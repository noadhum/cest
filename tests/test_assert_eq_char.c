#include "../cest.h"

int main(void)
{
     TEST_BEGIN();

     // Character literal
     ASSERT_EQ(char, 'A', 'A');
     ASSERT_EQ(char, '0', '0');
     ASSERT_EQ(char, '\n', '\n');

     // Arithmetic

     // Post-increment
     {
          char x = 'A';
          ASSERT_EQ(char, x++, 'A');
          ASSERT_EQ(char, x, 'B');
     }

     // Pre-increment
     {
          char x = 'A';
          ASSERT_EQ(char, ++x, 'B');
          ASSERT_EQ(char, x, 'B');
     }

     // Post-decrement
     {
          char x = 'A';
          ASSERT_EQ(char, x--, 'A');
          ASSERT_EQ(char, x, '@');
     }

     // Pre-decrement
     {
          char x = 'A';
          ASSERT_EQ(char, --x, '@');
          ASSERT_EQ(char, x, '@');
     }

     return TEST_END();
}
