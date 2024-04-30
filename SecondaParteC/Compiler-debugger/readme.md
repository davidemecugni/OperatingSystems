# Makefile

This is a `Makefile` file used to compile and manage a C project. A `Makefile` is a configuration file that defines the rules for compiling and managing a project. It is used by the `make` command to automate the project compilation and management process.

```makefile
CC = gcc
CFLAGS = -Wall -std=c11 ...
NAME = executable
SRCS = source_files
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
    $(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f $(OBJS)

fclean: clean
    rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
```
### explanation:
- `CC = gcc`: This line defines the variable`CC` as `gcc`, which is the C compiler used.

- `CFLAGS = -Wall -std=c11`: This line defines the variable `CFLAGS` with build options. `-Wall` enables all compiler warnings and `-std=c11` specifies the version of the C standard to be used.

- `NAME = executable`: This line defines the variable `NAME` with the name of the final executable.

- `SRCS = source_files`: This line defines the variable`SRCS` with the name of the source file.

- `OBJS = $(SRCS:.c=.o)`: This line defines the variable `OBJS` with the object file name, obtained by replacing the extension `.c` of the source file with `.o`.

- `all: $(NAME)`: This is the rule `all` that depends on `$(NAME)`. When performing `make` without specifying a rule, the rule `all`is executed.

- `$(NAME): $(OBJS)`: This is the rule to create the executable. It depends on the object files and uses the `gcc` compiler with the specified build options to create the executable.

- `%. or: %.c`: This is a generic rule to create an object file from a source file. Use the `gcc` compiler with the specified build options.

- `clean:`: This rule removes all object files.

- `fclean: clean`: This rule executes the `clean` rule and then removes the executable.

- `re: fclean all`: This rule first executes the `fclean` rule and then the `all`rule. This is useful to recompile everything from scratch.

- `.PHONY: all clean fclean re`: This line defines `all`, `clean`, `fclean` and `re` as PHONY targets, meaning that they are always executed, regardless of whether files with those names exist.

### example:
- `make`: This command compiles the project and creates the executable. `make all` can also be used.
```bash
make
```
- `make clean`: This command removes all object files.
```bash
make clean
```
- `make fclean`: This command removes all object files and the executable.
```bash
make fclean
```
- `make re`: This command removes all object files and the executable, then recompiles the project.
```bash
make re
```
### Running the program
To run the program, use the following command:
```bash
./executable
```

# Debugging
Debugging is the process of finding and fixing errors in a program. There are different tools and techniques available to help debug C programs. Some of the common tools used for debugging C programs are `gdb`, `lldb`, `valgrind`, and `strace`.

## In Visual Studio Code
To debug a C program in Visual Studio Code, you need to install the `C/C++` extension and configure the `launch.json` file.

```makefile
...
CFLAGS = ... -g ...
...
```

Since we are using a `Makefile` to compile the program, we need to add the right flags to the `CFLAGS` variable in the `Makefile` to include debugging information. For `gcc`, the flag `-g` is used to include debugging information in the executable. Then we need to configure the `launch.json` file to use the appropriate debugger.

### Mac OS 
In this case we will use `lldb` as the debugger.
1. Install the `C/C++` extension in Visual Studio Code.
2. Create a new folder and add the C source files.
3. Create a new file named `launch.json` in the `.vscode` folder.
4. Add the following configuration to the `launch.json` file:
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Makefile Debug Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}/${fileBasenameNoExtension}",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${fileDirname}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "lldb",
        },
    ]
}
```
**Explanation:**
- `"name": "Makefile Debug Launch"`: This is the name of the debug configuration.
- `"type": "cppdbg"`: This specifies the type of debugger to use.
- `"request": "launch"`: This specifies that the debugger should launch the program.
- `"program": "${fileDirname}/${fileBasenameNoExtension}"`: This specifies the path to the program to be debugged. `${fileDirname}` is the directory of the current file, and `${fileBasenameNoExtension}` is the name of the current file without the extension.
- `"args": []`: This specifies any arguments to be passed to the program.
- `"stopAtEntry": false`: This specifies whether the debugger should stop at the entry point of the program.
- `"cwd": "${fileDirname}"`: This specifies the current working directory for the debugger.
- `"environment": []`: This specifies any environment variables to be set.
- `"externalConsole": false`: This specifies whether an external console should be used for input/output.
- `"MIMode": "lldb"`: This specifies the debugger to use (in this case, `lldb`).

---
5. Go to the terminal and run the `make` command to compile the program. 
    - (WE NEED THE EXECUTABLE FILE AND THE OBJECT FILES TO DEBUG THE PROGRAM)
6. Open the C source file you want to debug.
7. Set breakpoints in the source file by clicking on the left margin of the editor.
8. Press `F5` to start debugging and select the debug configuration you created. In this case, it should be `Makefile Debug Launch`.
9. The debugger will start, and you can use the debugging features such as stepping through the code, inspecting variables, and viewing the call stack.
10. When you finish, you can run `make clean` to remove the object files. Or `make fclean` to remove the object files and the executable.

### Windows
...

### Linux
...

`"program": "${fileDirname}/${fileBasenameNoExtension}"` 
è la parte del file `launch.json` più importante, l'ultima parte cambia in base al debugger utilizzate, il resto non dovrebbe essere troppo diverso

provate a vedere se funziona e nel caso lo aggiorniamo 