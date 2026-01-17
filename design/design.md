# introduction
this is a document that describes all my thoughts/ideas, design and features to build this library. 

# goal
the main goal of this utility is to handle strings with less effort. things like creating a new string, manipulating strings, copying strings and much more should be accessible via a single function call. moreover, these functions which operate on the strings must be efficient. 


# fixed size strings
to get things started, working on fixed size strings seems the most logical choice. we can expand this library to support dynamic strings later.

before we talk about the design and implemention. lets understand how fixed-size strings work.

## about fixed-size strings

`fixed-size` strings are exactly what they sound like. they are strings that have a **fixed-length**. 

fundamentally, strings are just an **array of characters**. each character is a **byte (8-bits)**. however, there is one important thing about strings in C, they end with a **null terminator** represented as `\0` and the number `0` in ASCII.

```
why need a null terminator?

well, null-terminators signal the end of a string. without it many functions that operate on strings could cause undefined behaviour.

since strings are just an array of characters, the function that operates on a string keeps reading the memory locations (which can lead to accessing invalid memory causing undefined behaviour).
```

so, when we store a fixed-size string in C, we need to allocate `length + 1` bytes (the `+ 1` is for the null terminator). so, we can visualize a string stored in memory as:

```
--------------------------
| h | e | l | l | o | \0 |
--------------------------

where each block is a single byte (8-bits)
```

creating and manipulating strings are way easier than dynamic strings (which i will talk about later), there is no complex memory management involved.

however, these are some things we need to think about while implementing it:

- avoid overflows when operating on strings.

one of the biggest disadvantages of a fixed-size string is **size**. creating different length strings is really difficult because:
- a small string may occupy only a portion of the fixed-size array, wasting memory.
- a larger string might not even fit in the array.


## design and implementation
`loom` is a minimal string library for C. since its main goal is to be minimal (atleast for now), it supports only the most critical features to operate on strings. these features will be listed below.

`loom` represents a fixed-size string in a custom data type called `LoomString`, which is defined as follows:
```c
struct FixedString {
    char data[MAX_SIZE];
    size_t length;
}
```

since the `data` field is a `char` array and not a `pointer`, it is going to be allocated on the **stack**.

## features

- [x] `ls_init`: creates an empty `LoomString` object. (creates an empty string)

- [x] `ls_create`: creates a `LoomString` from C strings.

- [x] `ls_copy`: copies string/data content of one `LoomString` object to another.

- [x] `ls_copy_str`: copies string/data content of a C string to a `LoomString` object.

- [x] `ls_concat`: concats the string/data content from two `LoomString` objects.

- [x] `ls_concat_str`: concatenates string/data content of a C string to a `LoomString` object.

- [x] `ls_append_char`: appends a character to the `LoomString` object.

- [x] `ls_append_str`: appends a string to the `LoomString` object.


# dynamic strings

fixed-size strings is simple, however they have a ton of limitations:
- waste of memory space.
- limited capacity/space.
- unsuitable for applications that require dynamic strings.

to overcome all the issues listed above, we use **dynamic strings**. dynamic strings are exactly what they sound like. strings that grow and shrink in size during runtime. however, managing dynamic strings in C requires manual memory management.

dynamic strings can be created in C by allocating memory in the **heap**. unlike stack data-structure, the heap can store data as long as the application lives (or) if the memory is freed. in C we allocate some amount of bytes to store some sequence of characters and use a pointer variable to reference the memory address of the first character. we can visualize it as:

```
-----------------------                                              |----------Heap------------|
| Pointer Variable (a)|--------------------------------------------> | h | e | l | l | o | '\0' |
-----------------------                                              |--------------------------|

```

if we want to resize the string, we can simply reallocate memory. however, `realloc` in C can do the following 2 things:
1. extend/shrink the same memory blocks.
2. allocate completely new memory blocks and copy the data to it.

so its really important to update the pointers. if `realloc` allocates it to a new memory block, the existing pointer becomes invalid.


## design and implementaion
`loom` represents a dynamic string with a custom data type called `LoomString`. it is defined as follows:
```c
typedef struct {
    char *ptr;
    size_t length;
}
```
the struct instance itself might be stored in the stack, but the string (referenced by *ptr) will be stored in the `heap` memory.
these functions use `memcpy` for efficient copying of data between 2 memory locations. (unlike before, wherein i used loops).

## features
- [x] `ls_init`: creates an empty `LoomString` object. (creates an empty string)

- [x] `ls_new`: creates a `LoomString` from C strings by allocating memory using `malloc`.

- [x] `ls_copy`: copies string/data content of one `LoomString` object to another.

- [x] `ls_copy_cstr`: copies string/data content of a C string to a `LoomString` object.

- [x] `ls_concat`: concats the string/data content from two `LoomString` objects.

- [x] `ls_concat_cstr`: concatenates string/data content of a C string to a `LoomString` object.

- [x] `ls_append`: appends content of a `LoomString` to the `LoomString` object.

- [x] `ls_append_cstr`: appends a C string literal to the `LoomString` object.

- [x] `ls_append_char`: appends a character to the `LoomString` object.

- [x] `ls_realloc`: reallocates/resizes the given `LoomString` object.

- [x] `ls_free`: frees the memory allocated to the `*ptr` in a `LoomString` object.

moreover, these functions return a `LoomResult` enum which have the following values:
- LOOM_OK = 0
- LOOM_NULL_PTR = 1
- LOOM_ALLOC_FAIL = 2
- LOOM_REALLOC_FAIL= 3

i thought this was a pretty clean way to handle errors without exiting/crashing the process. this provides clients to handle the error themselves.


# final note

this was a fun project to build, learnt a lot about how memory works (still a long way to go), but i believe this project gave me a good start to memory management and building things with C.

i might come back to this project later to improve and optimize it and also to learn new stuff like:
- using SSO (small string optimization)
- using `capacity` field within `LoomString` to track how much memory is left which can help me avoid unncessary `realloc` calls.
- explore how the `SDS` string library works (which uses a different design to store strings) to make dynamic strings more efficient. 

i haven't really explored these techniques, but will definitely try to explore them in the future. for now, its time to build more projects in C.
