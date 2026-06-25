# Minishell

A Unix shell written in C as part of the 42 Lisboa Common Core curriculum.

Developed collaboratively by **Fábio Santos** and **Tomaz**.

The goal of this project is to recreate the core behavior of a Unix shell by implementing command parsing, process creation, pipes, redirections, environment expansion and built-in commands.

---

## Features

* Interactive shell
* Command execution
* Environment variable expansion
* Pipes (`|`)
* Input redirections (`<`)
* Output redirections (`>`)
* Append redirections (`>>`)
* Here documents (`<<`)
* Built-in commands
* PATH resolution
* Signal handling
* Quote handling

---

## Built-in Commands

* echo
* cd
* pwd
* export
* unset
* env
* exit

---

## Technologies

* C
* POSIX API
* Readline
* Linux
* Makefile

---

## Build

Compile the project:

```bash
make
```

Clean object files:

```bash
make clean
```

Remove object files and executable:

```bash
make fclean
```

Rebuild the project:

```bash
make re
```

---

## Usage

Run the shell:

```bash
./minishell
```

Example:

```bash
minishell$ ls -la
minishell$ echo Hello World
minishell$ cat file.txt | grep hello
minishell$ export PATH=/usr/bin
```

---

## Implementation

### Tokenizer

The parser is implemented in two stages.

The first stage separates the input into preliminary tokens while preserving quoted strings.

Example:

```text
echo "hello"world>file
```

↓

```text
[echo]
["hello"world>file]
```

The second stage re-parses each token to separate operators while preserving adjacent quoted strings.

Example:

```text
echo "hello"world>file
```

↓

```text
[echo]
["hello"world]
[>]
[file]
```

This allows expressions such as:

```bash
echo "Hello"World
```

to produce:

```text
HelloWorld
```

instead of inserting unwanted spaces.

---

### Command Representation

After tokenization, the shell builds an intermediate execution structure containing:

* Command and arguments
* Input redirections
* Output redirections
* Pipe information

This representation is later used by the execution stage.

---

### Environment Expansion

The shell supports variable expansion using:

```bash
$HOME
```

Special variables:

```bash
$$
$?
```

Supported behavior:

* Variables are validated before expansion.
* Undefined variables expand to an empty string.
* Numeric identifiers follow Bash-compatible behavior.

---

### Redirections

Supported operators:

```text
<
>
>>
<<
```

Features:

* Left-to-right processing
* Multiple input and output redirections
* Here-document support
* Quote-aware parsing
* Redirections inside pipelines

---

### Tilde Expansion

Supported expansions:

```bash
~
~/
```

These expand using the value stored in `$HOME`.

---

## Concepts Covered

* Parsing
* Lexical analysis
* Process management
* fork()
* execve()
* Pipes
* File descriptors
* Environment variables
* Signal handling
* Dynamic memory management

---

## What We Learned

This project provided a deeper understanding of Unix internals and process management.

During its development we learned how to:

* Design a multi-stage parser.
* Execute commands using POSIX system calls.
* Implement pipes and redirections.
* Handle environment variable expansion.
* Build a complete execution pipeline.
* Manage memory safely in a large codebase.
* Work collaboratively on a complex software project.
