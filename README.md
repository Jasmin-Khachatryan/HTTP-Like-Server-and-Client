# Multithreaded Web HTTP-Like Server and Client in C

## Overview

This project implements a simple **HTTP-like web server and client** in C. The server can handle **multiple client connections concurrently** using POSIX threads. It uses a **custom protocol with headers**, allowing you to explore how requests and responses work at a basic level.  

The server serves **plain text files** from a directory, and the client can send **GET, POST, and ECHO requests**.

---

## Features

- **Multithreaded server** – handles multiple clients simultaneously using POSIX threads.  
- **Custom protocol headers** – includes `Body-Size` to indicate message body length.  
- **Request types supported**:
  - **GET** – retrieve a file from the server.  
  - **POST** – send data to the server; the server saves it as a file.  
  - **ECHO** – server returns exactly what the client sends.  
- **Simple text files** – serves only plain text files.  
- **Interactive client** – choose request type and input data at runtime.

---
Got it — here is a **fully copy-friendly**, clean README text in **one block**, **no code fences**, no formatting that prevents copying.
Just plain Markdown with headings and indentation you can paste directly.

---

# How to Compile

### Server

gcc -Wall -pthread server/main.c server/handler.c server/utils.c -o server/server

### Client

gcc client/main.c -o client/client

# Running

### Start the server

./server/server

### Run the client (in another terminal)

./client/client

# Using the Client

Choose a request type:

1. GET
2. POST
3. ECHO

### GET

Enter a file name inside server/files/ to retrieve it.

### POST

Enter a file name and a message body.
The server saves the content into server/files/.

### ECHO

Enter any message; the server returns the exact same text.

---

