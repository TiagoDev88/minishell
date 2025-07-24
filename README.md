<h2 align="center">

[![MINISHELL](https://github.com/TiagoDev88/42-project-badges/blob/main/covers/cover-minishell.png)](https://github.com/TiagoDev88/minishell)

</h2>

<p align="center">
	<b><i>Recreating a simplified Bash shell - 42 School project</i></b><br>
</p>


<h3 align="center">
	<a href="#about-">About</a>
	<span> · </span>
	<a href="#features-">Features</a>
	<span> · </span>
	<a href="#usage-">Usage</a>
	<span> · </span>
	<a href="#author-">Author</a>
</h3>

---

## About 💡

> _Minishell is a 42 School project that aims to recreate a simplified Bash shell, handling commands, pipes, redirections, environment variables and built-in commands, with proper signal and memory management._

This project focuses on learning Unix process management, input parsing, file descriptors, and the design of a minimal shell that behaves similarly to Bash in its core functionality.

---

## Features 🚀

Minishell implements:

- A custom prompt waiting for user input
- Command execution via absolute/relative path or `$PATH`
- History using the readline library
- Input parsing with support for:
  - Quoting: `'` and `"` (with correct expansion behavior)
  - Escaped characters inside quotes
  - Variable expansion (`$VAR`, `$?`)
- Built-in commands:
  - `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Redirections:
  - `>` : output redirection
  - `>>`: output append
  - `<` : input redirection
  - `<<`: heredoc (with optional variable expansion)
- Pipe support (`|`)
- Proper signal handling:
  - `Ctrl-C` → display new prompt
  - `Ctrl-D` → exit shell
  - `Ctrl-\` → ignored
- Only **one global variable** used to store the signal number (as per subject constraints)
- No support for bonus features like `&&`, `||`, `()`, or wildcards

---

## Usage 📘

### Requirements

- GCC compiler
- Make

### Instructions

**1. Clone the repository**

```bash
git clone https://github.com/TiagoDev88/minishell.git
```

**2. Compile**
```bash
make
```

**3. Run**
```bash
./minishell
```
- Then enter commands as you would in a typical Bash session:
```bash
minishell$ echo Hello, world!
Hello, world!
```
### Author 👤

42 login: tfilipe-  /  GitHub: @TiagoDev88

42 login: edfreder  /  GitHub: @EdgarFir
