Inter-Process Communication Exercises

# Inter-Process Communication Exercises

## Table of Contents
1. [Introduction](#introduction)
2. [homeowork_1: Using Pipe for Communication Between Parent and Child Process](#exercise-1-using-pipe-for-communication-between-parent-and-child-process)
3. [homeowork_2: Using Multiple Pipes for Communication Between Multiple Processes](#exercise-2-using-multiple-pipes-for-communication-between-multiple-processes)
4. [homeowork_3: Counting Characters via Pipe](#exercise-3-counting-characters-via-pipe)
5. [Usage Instructions](#usage-instructions)
6. [Knowledge Summary](#knowledge-summary)

## Introduction
In this project, we will perform three exercises related to inter-process communication using pipes in the C programming language. Each exercise will provide source code and detailed explanations of how pipes work.

## Exercise 1: Using Pipe for Communication Between Parent and Child Process
### Description
This exercise guides you on how to use a pipe to communicate between a parent process and a child process. The parent process will send a string of text into the pipe, and the child process will read the string from the pipe and print it to the screen.

## Exercise 2: Using Multiple Pipes for Communication Between Multiple Processes
### Description
This exercise expands upon the previous one to use multiple pipes for three processes. The parent process sends a message to child process 1, which modifies the message and sends it to child process 2. Finally, child process 2 receives the message and prints it.

## Exercise 3: Counting Characters via Pipe
### Description
This exercise requires you to write a program that uses a pipe to count the number of characters in a string. The parent process will send a string of characters into the pipe, and the child process will read the string from the pipe, count the characters, and print the result.

## Usage Instructions
- Use the command `make` to build the project.
- Use the command `make clean` to clean up the project.

## Knowledge Summary
- **Pipe**: A mechanism for inter-process communication, allowing one process to send data to another.
- **fork()**: A function used to create a child process from a parent process.
- **read()/write()**: Functions used to read from and write to pipes.

