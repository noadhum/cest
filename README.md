# cest
Simple test runner for C

## Example
```c
#include "cest.h"

static int add(int a, int b)
{
     return a + b;
}

int main(void)
{
     TEST_BEGIN();

     EXPECT_EQ(int, add(1, 2), 3);

     return TEST_END();
}
```
