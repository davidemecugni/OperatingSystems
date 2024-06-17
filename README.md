# Operating Systems
This repository contains all the material for the Operating Systems course at University of Modena in the Computer Science Engineering course, held by prof. Letizia Leonardi.

All the material here provided can be used during the exam(up to 2024 at least).

## First part: Shell
- PDF with all past midterm exams with description and solution provided by prof. Letizia Leonardi
- PDF with Bash commands taught during the lessons
- TreeScript is an utility to make a tree of folders and files to test recursive programs
- Snippets of Shell code frequently used in the exams

## Second part: C
- PDF with all past final exams with description and solution provided by prof. Letizia Leonardi
- PDF C_primitives with all the C primitives used in the exams
- Snippets for C(over 4k lines!) with all the functions and patterns used in the exams
- Snippet for makefile with all possible checks and flags for warnings and errors
- In the Compiler-debugger folder there is a makefile to compile the C code and a debugger to test the code


### tester.py utility
This utility tests .sh and .c files for the exams.
It checks that the exit codes are progressively correct and, for the C part,
checks the number of memory operations to verify proper handling of exit on
error conditions. 

### From .md to .pdf
```console
sudo apt install npm
sudo npm install -g pretty-markdown-pdf
pretty-md-pdf -i FILE.md
```
