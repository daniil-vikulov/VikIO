# VikIO

## Description

Header-only library for efficient reading from and writing in stdin/stdout streams and O(1) memory management

Based on `getchar_nolock()` and `putchar_nolock()`

<b><u>Warning:</u></b> thread-unsafe and memory-leaking. You may benefit from its speed in single-thread programs with
tight time limits such as contests

## How to use

### `FAST_MEMORY`

If you would like to use normal heap management (without memory-leaking), just comment
the macro.

Macro in the beginning of the file, which specifies whether to use stack-allocator for `new`/`delete` operations or not.

If stack allocator is enabled, the cost of each `new` operation will be O(1) instead standard of O(logN),
however `delete` operator will not free memory.

### `sep`

Global variable, holding `\n` by default

After each print(T value), `sep` character will be printed, thereby separating the output.

Set zero-character `\0` to ignore printing sep character.

### `print()`

Template function for printing such types as: `char`, `unsigned char`, `int`, `unsigned int`, `long long`,
`unsigned long long`, `const char*`, `std::string` and <code>std::vector<<text>T</text>></code> of supported type `T`

### `read(T &number)`

As for integer-like types, the function will skip all the characters before an integer value will be found: valid
integer is a continues sequence of digits with potential `-` before. If the function faces with a non-digit character,
it reads and ignores it. That is why it is crucial to fully understand the variable of which type is going to be read.
### `read(std::string &str)`

The string is a sequence of characters from the current position to the end of the stream or till `\n`
character.

    int num1; // 1
    std::string s; // Hello world!
    int num2; // 2
    read(num1, s, num2);

Input:

    1
    Hello world!
    2

The string to read must not exceed the size of internal buf macro (You can specify it manually in the library code).

### <code>read(std::vector<<text>T</text>> &array)</code>

Must be a pre-allocated vector, which will read array.size() objects of `T`.
Note that `T` must be supported for reading. Eventually, the array will be filled with corresponding data

## Development & Support

Found a bug or have a question?

Do not hesitate to contact me:

- **Email:** [39g60bx15@gmail.com](mailto:39g60bx15@gmail.com)
- **Telegram**: [t.me:studvik13](https://t.me/studvik13)