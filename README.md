# Word Count with Raw File I/O Functions

## Project Specifications
For this assignment, you will complete a program that counts the number of words in a file. This is similar to the common Linux tool `wc` (word count). In fact, you can check that your program is functioning correctly by running `wc -w` on the provided corpus files.

### Buffering Your Own I/O
You must use raw file I/O for this assignment which means you will be filling a buffer of 1024 bytes using the `read()` system call and then parsing text out of that buffer. You should use `strsep()` to parse the text by space or newline character. This will result in a series of non-whitespace tokens that need to be saved in an *array of structs*. When you reach the end of this series of tokens, two things might happen:

    The filled buffer ends on a word boundary 😀 OR
    The filled buffer ends in the middle of a word 😕

Because this may happen, *you cannot trust the final token in the buffer to be complete*. You must move the (potentially) partial token to the front of the buffer and then fill the buffer starting from where that token ends (so the information is not overwritten). *This is very difficult to get correct*, and if you do not, the resulting word count will not be correct.

Many functions in the C stdlib return values *that are important, do not ignore them*.
