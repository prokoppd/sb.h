
# A simple string builder in C
[![CI](https://github.com/prokoppd/sb.h/actions/workflows/ci.yml/badge.svg)](https://github.com/prokoppd/sb.h/actions/workflows/ci.yml)
[![codecov](https://codecov.io/gh/<OWNER>/<REPO>/branch/main/graph/badge.svg)](https://codecov.io/gh/prokoppd/sb.h)
## How to use
Include the header file in your C source and define `SB_IMPLEMENTATION` in **one** source file before including it.

```c
#include <stdio.h>

#define SB_IMPLEMENTATION
#include "sb.h"

int main() {
    StringBuilder *sb = sb_create(10);
    
    sb_append(sb, "Hello, ");
    sb_append(sb, "World!");
    
    printf("%s\n", sb_cstr(sb));
    
    sb_destroy(sb);
    return 0;
}
```
