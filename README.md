
# Simple Shell

A small Unix shell implementation in C. This project provides a lightweight command interpreter that supports interactive and non-interactive modes, built-in shell commands, command separators, pipes, and I/O redirection.

## Features

- Interactive prompt showing the current working directory
- Executable command lookup using the `PATH` environment variable
- Support for absolute/relative command paths when available
- Built-in commands:
  - `cd [dir]` — change working directory
  - `setenv VAR VALUE` — set or update an environment variable
  - `unsetenv VAR` — remove an environment variable
  - `env` — print the current environment
  - `exit [status]` — exit the shell with optional status code
- Special environment-like tokens supported by builtins:
  - `echo $?` — print exit status of the last command
  - `echo $$` — print the shell process ID
  - `echo $PATH` — print the current `PATH`
- Shell operators and separators:
  - `&&` — run next command only if previous succeeds
  - `||` — run next command only if previous fails
  - `;` — run commands sequentially regardless of status
- Pipes and redirection support:
  - `|` — pipe output from one command to another
  - `>` — redirect stdout to a file (overwrite)
  - `>>` — redirect stdout to a file (append)
  - `<` — redirect stdin from a file
- Ignores comments beginning with `#`
- Custom implementations of `_getline` and `_strtok`

## Build

```sh
make
```

This produces the executable `hsh`.

### Clean

```sh
make clean
```

### Full clean

```sh
make fclean
```

### Rebuild

```sh
make re
```

## Usage

Run the shell in interactive mode:

```sh
./hsh
```

Run the shell in non-interactive mode by piping or redirecting commands:

```sh
echo "ls -l" | ./hsh
```

## Examples

```sh
./hsh
cd /tmp
pwd
ls -l
env
setenv MYVAR hello
echo $PATH
unsetenv MYVAR
ls | grep ".c"
cat < input.txt
echo "done" > output.txt
./hsh && echo "next command"
```

## File Structure

- `main.c` — program entry point and shell loop
- `main.h` — shared declarations and helper prototypes
- `fork_cmd.c` — child process creation and command execution
- `builtin_cmd.c` — built-in command handling
- `command_path.c` — command path resolution logic
- `get_line.c` — custom input reading and tokenization
- `logical_op.c` — support for `&&`, `||`, and `;`
- `read_input.c` — stdin reading and pipe/redirection dispatch
- `to_print.c` — custom output helpers
- `help_me.c` — builtins for `cd`, `setenv`, `unsetenv`, `env`, and `exit`
- `func_prot.c` — additional string utilities and parser helpers
- `Makefile` — build rules for the shell
- `AUTHORS` — contributor information
- `generate-authors.sh` — helper script for author metadata

## Notes

- The shell is designed for Linux systems and depends on standard Unix APIs.
- The command parser uses simple tokenization rules and does not implement full POSIX shell parsing.
- Built-in command support is implemented directly in C.

## License

No license is specified in this repository. Use and modify the code according to your local policies.
