# Loom - C String Library

A lightweight string utility library for C that provides safe, convenient string manipulation with built-in error handling.

## Table of Contents

- [Types](#types)
- [Macros](#macros)
- [Functions](#functions)
- [Usage Examples](#usage-examples)
- [Error Handling](#error-handling)

---

## Types

### LoomString

The core string structure used throughout the library.

```c
typedef struct {
    char *ptr;      // Pointer to the null-terminated string data
    size_t length;  // Length of the string (excluding null terminator)
} LoomString;
```

### LoomResult

Return type for most functions, indicating success or failure.

```c
typedef enum {
    LOOM_OK = 0,        // Operation successful
    LOOM_NULL_PTR,      // Null pointer was passed
    LOOM_ALLOC_FAIL,    // Memory allocation (malloc) failed
    LOOM_REALLOC_FAIL,  // Memory reallocation (realloc) failed
} LoomResult;
```

---

## Macros

### ls_len(ls)

Returns the length of a LoomString.

```c
#define ls_len(ls) ((ls)->length)
```

**Parameters:**
- `ls` - Pointer to a LoomString

**Returns:** `size_t` - The length of the string

**Example:**
```c
LoomString str = ls_init();
ls_new(&str, "Hello");
size_t len = ls_len(&str);  // len = 5
```

---

### CHECK_PTR(ls)

Internal macro for validating LoomString pointers. Returns `LOOM_NULL_PTR` if the pointer or its internal `ptr` is NULL.

```c
#define CHECK_PTR(ls) if ((ls) == NULL || (ls)->ptr == NULL) return LOOM_NULL_PTR
```

---

### CHECK_CSTR(str)

Internal macro for validating C string pointers. Returns `LOOM_NULL_PTR` if the string is NULL.

```c
#define CHECK_CSTR(str) if ((str) == NULL) return LOOM_NULL_PTR
```

---

## Functions

### Initialization & Creation

#### ls_init()

Initializes an empty LoomString structure.

```c
LoomString ls_init();
```

**Returns:** `LoomString` - An initialized structure with `ptr = NULL` and `length = 0`

**Example:**
```c
LoomString str = ls_init();
```

---

#### ls_new()

Creates a new LoomString from a C string.

```c
LoomResult ls_new(LoomString *ls, const char *str);
```

**Parameters:**
- `ls` - Pointer to the LoomString to initialize
- `str` - The C string to copy

**Returns:** `LoomResult`

**Example:**
```c
LoomString greeting = ls_init();
LoomResult result = ls_new(&greeting, "Hello, World!");
// greeting.ptr = "Hello, World!", greeting.length = 13
```

---

### Copying

#### ls_copy()

Copies the contents of one LoomString to another.

```c
LoomResult ls_copy(LoomString *dest, const LoomString *src);
```

**Parameters:**
- `dest` - Destination LoomString (must be initialized with `ls_new`)
- `src` - Source LoomString to copy from

**Returns:** `LoomResult`

**Example:**
```c
LoomString src = ls_init();
LoomString dest = ls_init();
ls_new(&src, "Original");
ls_new(&dest, "placeholder");

ls_copy(&dest, &src);  // dest now contains "Original"
```

---

#### ls_copy_cstr()

Copies a C string into a LoomString.

```c
LoomResult ls_copy_cstr(LoomString *dest, const char *src);
```

**Parameters:**
- `dest` - Destination LoomString (must be initialized with `ls_new`)
- `src` - C string to copy

**Returns:** `LoomResult`

**Example:**
```c
LoomString str = ls_init();
ls_new(&str, "temp");

ls_copy_cstr(&str, "New content");  // str now contains "New content"
```

---

### Concatenation

#### ls_concat()

Concatenates two LoomStrings and stores the result in a third.

```c
LoomResult ls_concat(const LoomString *ls1, const LoomString *ls2, LoomString *res);
```

**Parameters:**
- `ls1` - First LoomString
- `ls2` - Second LoomString
- `res` - Result LoomString (must be initialized with `ls_new`)

**Returns:** `LoomResult`

**Example:**
```c
LoomString hello = ls_init();
LoomString world = ls_init();
LoomString result = ls_init();

ls_new(&hello, "Hello, ");
ls_new(&world, "World!");
ls_new(&result, "");

ls_concat(&hello, &world, &result);  // result = "Hello, World!"
```

---

#### ls_concat_cstr()

Concatenates a LoomString with a C string.

```c
LoomResult ls_concat_cstr(const LoomString *ls, const char *str, LoomString *res);
```

**Parameters:**
- `ls` - LoomString
- `str` - C string to concatenate
- `res` - Result LoomString (must be initialized with `ls_new`)

**Returns:** `LoomResult`

**Example:**
```c
LoomString greeting = ls_init();
LoomString result = ls_init();

ls_new(&greeting, "Hello");
ls_new(&result, "");

ls_concat_cstr(&greeting, " everyone!", &result);  // result = "Hello everyone!"
```

---

### Appending

#### ls_append()

Appends one LoomString to another (modifies the first string in-place).

```c
LoomResult ls_append(LoomString *ls1, const LoomString *ls2);
```

**Parameters:**
- `ls1` - LoomString to append to (modified in-place)
- `ls2` - LoomString to append

**Returns:** `LoomResult`

**Example:**
```c
LoomString sentence = ls_init();
LoomString suffix = ls_init();

ls_new(&sentence, "Loom is ");
ls_new(&suffix, "awesome!");

ls_append(&sentence, &suffix);  // sentence = "Loom is awesome!"
```

---

#### ls_append_cstr()

Appends a C string to a LoomString.

```c
LoomResult ls_append_cstr(LoomString *ls, const char *str);
```

**Parameters:**
- `ls` - LoomString to append to (modified in-place)
- `str` - C string to append

**Returns:** `LoomResult`

**Example:**
```c
LoomString message = ls_init();
ls_new(&message, "Status: ");

ls_append_cstr(&message, "Success!");  // message = "Status: Success!"
```

---

#### ls_append_char()

Appends a single character to a LoomString.

```c
LoomResult ls_append_char(LoomString *ls, char ch);
```

**Parameters:**
- `ls` - LoomString to append to (modified in-place)
- `ch` - Character to append

**Returns:** `LoomResult`

**Example:**
```c
LoomString word = ls_init();
ls_new(&word, "Hell");

ls_append_char(&word, 'o');  // word = "Hello"
```

---

### Memory Management

#### ls_realloc()

Reallocates the internal buffer of a LoomString.

```c
LoomResult ls_realloc(LoomString *ls, size_t newLen);
```

**Parameters:**
- `ls` - LoomString to reallocate
- `newLen` - New buffer size in bytes

**Returns:** `LoomResult`

**Note:** This is primarily used internally by other functions. Direct use is rarely needed.

---

#### ls_free()

Frees the memory allocated for a LoomString and resets its fields.

```c
LoomResult ls_free(LoomString *ls);
```

**Parameters:**
- `ls` - LoomString to free

**Returns:** `LoomResult`

**Example:**
```c
LoomString str = ls_init();
ls_new(&str, "Hello");

// ... use the string ...

ls_free(&str);  // str.ptr = NULL, str.length = 0
```

---

## Usage Examples

### Basic String Operations

```c
#include "loom.h"
#include <stdio.h>

int main() {
    // Create strings
    LoomString greeting = ls_init();
    LoomString name = ls_init();
    
    ls_new(&greeting, "Hello, ");
    ls_new(&name, "World!");
    
    // Append strings
    ls_append(&greeting, &name);
    printf("%s\n", greeting.ptr);  // Output: Hello, World!
    
    // Get length
    printf("Length: %zu\n", ls_len(&greeting));  // Output: Length: 13
    
    // Cleanup
    ls_free(&greeting);
    ls_free(&name);
    
    return 0;
}
```

### Building Strings Character by Character

```c
LoomString path = ls_init();
ls_new(&path, "/home");

ls_append_char(&path, '/');
ls_append_cstr(&path, "user");
ls_append_char(&path, '/');
ls_append_cstr(&path, "documents");

printf("%s\n", path.ptr);  // Output: /home/user/documents

ls_free(&path);
```

---

## Error Handling

All functions that can fail return a `LoomResult`. Always check the return value:

```c
LoomResult result = ls_new(&str, "Hello");

switch (result) {
    case LOOM_OK:
        printf("Success!\n");
        break;
    case LOOM_NULL_PTR:
        printf("Error: Null pointer provided\n");
        break;
    case LOOM_ALLOC_FAIL:
        printf("Error: Memory allocation failed\n");
        break;
    case LOOM_REALLOC_FAIL:
        printf("Error: Memory reallocation failed\n");
        break;
}
```

### Common Error Scenarios

| Error | Cause |
|-------|-------|
| `LOOM_NULL_PTR` | Passing NULL to any function, or using an uninitialized LoomString |
| `LOOM_ALLOC_FAIL` | System out of memory during `ls_new()` |
| `LOOM_REALLOC_FAIL` | System out of memory during append/concat operations |
