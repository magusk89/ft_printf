*This project has been created as part of the 42 curriculum by alebarbo.*

# ft_printf

## Description

**ft_printf** is a project that reimplements the standard C library function `printf()`. The objective is to understand how variadic functions work in C and to build a robust, extensible formatted output function from scratch.

The function handles the following conversion specifiers: `%c`, `%s`, `%p`, `%d`, `%i`, `%u`, `%x`, `%X`, and `%%`.

In addition to the mandatory conversions, the implementation also supports the full bonus flag set: `-`, `0`, `.` (precision), minimum field width, `#`, `+`, and space — applicable under all conversions.

## Instructions

**Compilation**
* Run `make` at the root of the repository to compile the library. This will generate `libftprintf.a`.
* Run `make bonus` to compile with bonus flag support.
* Additional Makefile rules available: `clean`, `fclean`, `re`.

**Usage**
* Include `ft_printf.h` in your source files.
* Link against `libftprintf.a` when compiling your programs:
  ```
  cc -Wall -Wextra -Werror your_file.c libftprintf.a
  ```

## Algorithm and Data Structure

The implementation is organized around a central `t_flags` struct that carries all formatting state for a given conversion:

```c
typedef struct s_flags
{
    char    bitflag;    // bitmask for active flags (-, 0, #, space, +)
    int     width;      // minimum field width
    int     precision;  // precision (-1 if unset)
    int     guard;      // error sentinel: set to -1 on write failure
}           t_flags;
```

Flag bits are defined as powers of two (`DASH=1`, `ZERO=2`, `HASH=4`, `SPACE=8`, `PLUS=16`), allowing any combination to be stored and tested efficiently with bitwise operations.

**Parsing loop — `ft_printf.c`**

`ft_printf()` initializes a `va_list` and passes control to `ft_print_counter()`, which walks the format string one character at a time. When a `%` is encountered, `ft_flag_check()` parses any flags, width, and precision that follow, populating the `t_flags` struct. Control then passes to `ft_conversion()`, which dispatches to the appropriate output function based on the conversion specifier.

For non-`%` characters, the raw byte is written directly via `ft_write_guard()`.

**Write guard — `ft_write_guard.c`**

All output goes through `ft_write_guard()`, which wraps `write(1, ...)` and records any error by setting `flags->guard = -1`. The main loop checks this sentinel after every character and returns `-1` immediately if a write failure is detected, matching the behavior of the original `printf()`.

**Output functions**

Each conversion specifier has a dedicated output function that applies the width, precision, and flag logic before writing:

- `ft_putchar.c` — handles `%c`: prints the character, then pads right with spaces if `-` is set, or left-pads with spaces otherwise.
- `ft_putstr.c` — handles `%s`: computes the effective length (capped by precision), pads with spaces according to width and alignment. Prints `(null)` for NULL pointers, respecting precision (a precision smaller than 6 suppresses the `(null)` output).
- `ft_putnbr.c` — handles `%d`/`%i`: manages sign (`-`, `+`, space flags), precision zero-padding, and field width padding. The special case of `INT_MIN` (`-2147483648`) is handled directly to avoid undefined behavior from negation.
- `ft_putunbr.c` — handles `%u`: same structure as `ft_putnbr` but without sign logic.
- `ft_puthex.c` — handles `%x`/`%X`: converts to hex using a fixed 21-byte buffer filled from right to left, then applies `#` prefix (`0x`/`0X`), precision zeros, and width padding. Uppercase is achieved by subtracting 32 from lowercase hex digits in-place.
- `ft_putmem.c` / `ft_printmem.c` — handle `%p`: NULL pointers print as `(nil)` with width support; non-NULL pointers delegate to `ft_printmem`, which follows the same hex logic as `ft_puthex` but always prepends `0x` and operates on `unsigned long int` to cover 64-bit addresses.

**Helper functions**

- `ft_atoi.c` — parses the width and precision fields from the format string.
- `ft_strlen.c` — returns string length; used throughout for padding calculations.
- `ft_nbrlen.c` — returns the number of decimal digits in a signed integer; used to compute width and precision padding for `%d`/`%i`.

**Width and precision interaction**

When precision exceeds the natural length of the value, the difference is subtracted from the width before padding is applied. This ensures that total output width is counted correctly even when precision adds leading zeros.

## Resources

**References:**
- [printf(3) — Linux manual page](https://www.man7.org/linux/man-pages/man3/printf.3.html)
- [va_start / stdarg.h — cppreference](https://en.cppreference.com/w/c/variadic)
- [Formatted output — GNU C Library Reference Manual](https://www.gnu.org/software/libc/manual/html_node/Formatted-Output.html)
- [Bitwise operations in C — Wikipedia](https://en.wikipedia.org/wiki/Bitwise_operations_in_C)

**AI Usage**

AI was used to help write this README.
