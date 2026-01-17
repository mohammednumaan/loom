# loom

A lightweight string utility library for C.

> **Note:** This library is not production-ready. It was built as a learning project to explore memory management in C.

## Quick Example

```c
#include "loom.h"
#include <stdio.h>

int main() {
    LoomString greeting = ls_init();
    ls_new(&greeting, "Hello, ");
    ls_append_cstr(&greeting, "World!");
    
    printf("%s\n", greeting.ptr);  // Output: Hello, World!
    
    ls_free(&greeting);
    return 0;
}
```

## Documentation

See [docs/docs.md](docs/docs.md) for full API documentation.

## Note

This was a fun project to build and a good start to memory management in C. Future improvements may include:

- SSO (Small String Optimization)
- Adding a `capacity` field to avoid unnecessary `realloc` calls
- Exploring the SDS string library design for more efficient dynamic strings
