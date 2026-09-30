*This project has been created as part of the 42 curriculum by yaalmoui*

# get_next_line

## Description:
get_next_line is a 42 School project focused on reading and processing files line by line using the read() function.

The goal is to implement:
`char *get_next_line(int fd);`
Each call returns the next line from the given file descriptor, including the `\n` character when it is present.
The project focuses on:
* File descriptors
* read()
* Static variables
* Dynamic memory allocation
* Pointers and pointer-to-pointer
* String manipulation
* Memory management
### Bonus
The bonus version supports multiple file descriptors simultaneously.
A separate static buffer is maintained for each file descriptor, allowing the function to switch between different files without losing previously read data.
For example:
* `fd 3 → saved[3]`
* `fd 4 → saved[4]`
* `fd 5 → saved[5]`

This allows calls such as:
* `get_next_line(fd1);`
* `get_next_line(fd2);`
* `get_next_line(fd1);`
* `get_next_line(fd2);`

without mixing the contents of the different files.

## Instruction:
### Compilation
Compile the project with:

`gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c`

You can change BUFFER_SIZE when compiling:

`cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c`

### Bonus
Compile the bonus version with:
`cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c`

## Resources:
* [42 get_next_line subject](https://cdn.intra.42.fr/pdf/pdf/208243/en.subject.pdf)

* [read() — Linux manual page](https://man7.org/linux/man-pages/man2/read.2.html)

* [Valgrind Documentation](https://valgrind.org/docs/manual/manual.html)
