#include "../cest.h"

int main(void)
{
     TEST_BEGIN();

     // String literal
     ASSERT_EQ(cstr, "", "");
     ASSERT_EQ(cstr, "hello", "hello");
     ASSERT_EQ(cstr, "hello\nworld", "hello\nworld");
     ASSERT_EQ(cstr, "📦", "\xf0\x9f\x93\xa6");

     return TEST_END();
}
