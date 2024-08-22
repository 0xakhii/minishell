# Minishell

Minishell is a simple Unix shell implementation written in C. It supports basic shell features, including executing commands, handling pipelines, and managing environment variables.

## Features

- Execute basic Unix commands
- Handle pipelines (`|`)
- Manage environment variables
- Input/output redirection (`<`, `>`, `>>`)
- Built-in commands: `cd`, `echo`, `env`, `exit`, `export`, `unset`, `pwd` 

## Getting Started

### Prerequisites

Before you start, ensure you have the following installed:

- **Make**: Used to build the project.
- **GCC**: The GNU Compiler Collection for compiling C programs.

### Cloning the Repository

To get a local copy up and running, clone the repository using the following command:

```bash
git clone https://github.com/yourusername/minishell.git
cd minishell
make
./minishell
```
You will now be able to enter commands just like in a regular Unix shell.
