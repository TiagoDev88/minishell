<h1 align="center">
	📚 libft
</h1>

<p align="center">
	<b><i>Your own C standard library</i></b><br>
</p>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/TiagoDev88/libft?color=lightblue" />
	<img alt="Number of lines of code" src="https://img.shields.io/tokei/lines/github/TiagoDev88/libft?color=critical" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/TiagoDev88/libft?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/TiagoDev88/libft?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/TiagoDev88/libft?color=green" />
</p>

<h3 align="center">
	<a href="#️-about">About</a>
	<span> · </span>
	<a href="#️-usage">Usage</a>
	<span> · </span>
	<a href="#-functions">Functions</a>
</h3>

---

## 💡 About

> _libft is a foundational project at 42 that consists of reimplementing basic functions from the standard C library, as well as some additional utilities._

It helped me understand:
- C memory management
- String manipulation
- Linked list operations
- Function pointers and custom implementations

---

## 🛠️ Usage

### Requirements

- GCC compiler
- Make

### Instructions

**1. Clone the repository**

```bash
git clone https://github.com/TiagoDev88/libft.git
cd libft
```
**2. Compile the library**

```bash
make
```
This will generate the libft.a static library.

**3. Use it in your project**

```bash
#include "libft.h"
```
Compile with:

```bash
gcc your_program.c -L. -lft
```

## 🧩 Functions
## **Part 1 - libc functions**

ft_isalpha

ft_isdigit

ft_isalnum

ft_isascii

ft_isprint

ft_strlen

ft_memset

ft_bzero

ft_memcpy

ft_memmove

ft_strlcpy

ft_strlcat

ft_toupper

ft_tolower

ft_strchr

ft_strrchr

ft_strncmp

ft_memchr

ft_memcmp

ft_strnstr

ft_atoi

ft_calloc

ft_strdup

## **Part 2 - Additional functions**

ft_substr

ft_strjoin

ft_strtrim

ft_split

ft_itoa

ft_strmapi

ft_striteri

ft_putchar_fd

ft_putstr_fd

ft_putendl_fd

ft_putnbr_fd

## **Bonus part - Linked list**

ft_lstnew

ft_lstadd_front

ft_lstsize

ft_lstlast

ft_lstadd_back

ft_lstdelone

ft_lstclear

ft_lstiter

ft_lstmap

## **👤 Author**
42 login: tfilipe-

GitHub: @TiagoDev88
