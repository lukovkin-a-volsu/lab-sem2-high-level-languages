# Что такое puts, gets, putc, getc, putchar?

In programming, puts, gets, putc, getc, and putchar are functions used for performing input/output operations in C and other programming languages. Here is a brief overview of what each function does:

<ul>
    <li>
        puts: This function is used to write a string to the standard output, adding a newline character at the end.
    </li>
    <li>
        gets: This function is used to read a line of text from the stdin (standard input) and store it as a string in memory. However, using gets is not recommended due to its potential vulnerability to buffer overflow attacks.
    </li>
    <li>
        putc: This function writes a single character to the    standard output.
    </li>
    <li>
        getc: This function reads a single character from the stdin (standard input).
    </li>
    <li>
        putchar: This function writes a single character to the standard output.
    </li>
</ul>

All of these functions can be used to perform basic input/output operations in C, and are often used in console or command-line applications. It is worth noting that gets() is a deprecated version of fgets() and is not safe for use due to the risk of buffer overflow.


# Какая разница между putc и putchar?

The putc and putchar functions in C perform a similar task in terms of writing a single character to a given output stream. The main difference between them is that putchar writes to the standard output stream (stdout) while putc writes to a specified file stream.

In addition, putchar is a standard library function that is guaranteed to be available on all systems, while putc is part of the C standard library, but may be implemented differently by different compilers or operating systems.

It's worth noting that the putchar function is actually a macro defined in the C standard library header stdio.h, with the definition being equivalent to putc(c, stdout). In practice, this means that putchar can be considered to be more portable than putc.

Overall, both putc and putchar are useful functions for input/output operations in C, with putchar being more commonly used for outputting data to the console or terminal, while putc is preferred for writing output to a file.


