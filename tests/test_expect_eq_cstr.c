#include "../cest.h"

int main(void)
{
     TEST_BEGIN();

     // String literal
     EXPECT_EQ(cstr, "", "");
     EXPECT_EQ(cstr, "hello", "hello");
     EXPECT_EQ(cstr, "hello\nworld", "hello\nworld");
     EXPECT_EQ(cstr, "📦", "\xf0\x9f\x93\xa6");

     return TEST_END();
}
