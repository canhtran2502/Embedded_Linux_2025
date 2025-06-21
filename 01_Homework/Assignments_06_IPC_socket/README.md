Socket Programming Exercises README

# Socket Programming Exercises

## Table of Contents
1. [Introduction](#introduction)
2. [Exercise 1: IPv4 Stream Socket](#exercise-1-ipv4-stream-socket)
3. [Exercise 2: IPv4 Datagram Socket](#exercise-2-ipv4-datagram-socket)
4. [Exercise 3: Unix Stream Socket](#exercise-3-unix-stream-socket)
5. [Exercise 4: Unix Datagram Socket](#exercise-4-unix-datagram-socket)
6. [Usage Instructions](#usage-instructions)
7. [Knowledge Summary](#knowledge-summary)

## Introduction
In this project, we will perform four exercises related to socket programming, including:
- IPv4 Stream Socket
- IPv4 Datagram Socket
- Unix Stream Socket
- Unix Datagram Socket

Each exercise will provide source code and detailed explanations of how each type of socket works.

## Exercise 1: IPv4 Stream Socket
### Description
This exercise guides you on how to use an IPv4 Stream Socket to establish a TCP connection between a client and a server.

### Usage
1. Run the server: 
   ```bash
   ./stream_server <port number>
   ```
2. Run the client:
   ```bash
    ./stream_client <server address> <port number>
   ```

## Exercise 2: IPv4 Datagram Socket
### Description
This exercise will help you get familiar with using an IPv4 Datagram Socket to send and receive connectionless data (UDP).

### Usage
1. Run the server:
   ```bash
   ./datagram_server
   ```
2. Run the client:
   ```bash
   ./datagram_client <server address> <message>
   ```

## Exercise 3: Unix Stream Socket
### Description
In this exercise, you will learn how to use a Unix Stream Socket to communicate between processes on the same machine.

### Usage
1. Run the server:
   ```bash
   ./stream_server
   ```
2. Run the client:
   ```bash
   ./stream_client <message>
   ```

## Exercise 4: Unix Datagram Socket
### Description
This exercise will guide you on how to use a Unix Datagram Socket to send and receive message data between processes.

### Usage
1. Run the server:
   ```bash
   ./datagram_server
   ```
2. Run the client:
   ```bash
   ./datagram_client <message>
   ```

## Usage Instructions
- $make -> build project.
- $make clean -> clean project.

## Knowledge Summary
- **Stream Socket**: Uses TCP protocol, ensuring that data is sent and received reliably.
- **Datagram Socket**: Uses UDP protocol, allowing for connectionless data transmission without reliability guarantees.
- **Unix Socket**: Allows communication between processes on the same machine, using either stream or datagram.




