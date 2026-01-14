# introduction
this is a document that describes all my thoughts/ideas, design and features to build this library. 

# goal
the main goal of this utility is to handle strings with less effort. things like creating a new string, manipulating strings, copying strings and much more should be accessible via a single function call. moreover, these functions which operate on the strings must be efficient. 


# fixed size strings
to get things started, working on fixed size strings seems the most logical choice. we can expand this library to support dynamic strings later.
before we talk about the design and implemention. lets understand how fixed size strings work.

## a primer on fixed size strings
fixed size strings as the name suggests is an **fixed** length array of characters. the main characteristic of such strings is their **fixed length**. since the size of the string is pre-defined, we cannot increase the size of the string. you can fit (length - 1) characters within this array.

why (length - 1)? well, in C strings need to be terminated with a special character called '\0' also called as the null terminator. the importance of this is, various functions that operate on strings (for example: printf) expect a null terminator to signal the end of the string. if there is no null terminator, the behaviour is undefined and can cause issues. so its best to terminate strings with the null character.

## design and implementation
`loom` is a minimal string library for C. since its main goal is to be minimal (atleast for now), it supports only the most critical features to operate on strings. these features will be listen later below.

`loom` represents a fixed size string in a custom data type calld `FixedString`, which defined as follows:
```c
struct FixedString {
    char data[MAX_SIZE];
    size_t length;
}
```

here are the core features that `loom` supports for fixed-size strings.

\> creating strings
    - create strings from string literals (char *str)
    - create strings from another FixedString instance. 

\> copying strings
    - copy strings from string literals to a `FixedString` instance.
    - copy strings from one `FixedString` instance to another.

\> concat strings
    - concat strings between two string literals.
    - concat strings between two `FixedString` instances.


