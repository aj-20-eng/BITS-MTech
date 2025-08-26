MPI Send/Receive Lab – Theory
1. Introduction

This lab demonstrates point-to-point communication between two processes using MPI (Message Passing Interface).
MPI allows multiple processes (running on the same or different machines) to communicate and work together in parallel computing.

In this lab, we implement a simple ping-pong communication:

Process 0 sends a message to Process 1.

Process 1 receives the message, prints it, and sends a reply back to Process 0.

Process 0 receives the reply and prints it.

2. Key Concepts
a) Processes

Each MPI program consists of multiple processes, each identified by a rank.

rank = unique ID of a process (0, 1, 2…).

size = total number of processes in the communicator.

b) MPI Functions Used

MPI_Init(&argc, &argv)

Starts MPI environment. All MPI programs must call this first.

MPI_Comm_rank(MPI_COMM_WORLD, &rank)

Gets the rank of the current process.

MPI_Comm_size(MPI_COMM_WORLD, &size)

Gets the total number of processes.

MPI_Send(buffer, count, datatype, dest, tag, communicator)

Sends data from one process to another.

buffer = data to send

count = number of items

datatype = type of data (e.g., MPI_INT, MPI_CHAR)

dest = destination rank

tag = message label

communicator = group of processes (usually MPI_COMM_WORLD)

MPI_Recv(buffer, count, datatype, source, tag, communicator, status)

Receives data from another process.

source = rank of the sending process

status = information about the received message (can be ignored using MPI_STATUS_IGNORE)

MPI_Finalize()

Ends MPI environment. Always call at the end.

3. Message Flow (Ping-Pong Communication)
   Process 0 (A)                          Process 1 (B)
   -------------                          -------------
   |           | -- "Hi"  ------------->  |           |
   | waits     |                          | receives  |
   | for reply |                          | "Hi"      |
   |           | <----------- "I received your Hi, I am healthy" -- |
   | receives  |                          | sends reply |
   -------------                          -------------


Explanation:

Process 0 sends a greeting ("Hi") to Process 1.

Process 1 receives the greeting and prints it.

Process 1 sends a reply back ("I received your Hi, I am healthy") to Process 0.

Process 0 receives the reply and prints it.

4. Blocking Communication

MPI_Send and MPI_Recv are blocking functions, meaning:

MPI_Send will wait until the message is safely sent.

MPI_Recv will wait until the message is received.

Blocking ensures that messages are delivered in the correct order without data loss.

5. Applications

This simple lab simulates real-world communication between distributed systems:

Client-server messaging

Sensor networks

Parallel computation tasks

It teaches the basic principles of synchronous communication in MPI.

6. How to Run

Compile the program:

mpicc mpi_pingpong.c -o mpi_pingpong


Run with 2 processes:

mpirun -np 2 ./mpi_pingpong


Expected Output:

Process 0 sent: Hi
Process 1 received: Hi
Process 1 sent reply: I received your Hi, I am healthy
Process 0 received reply: I received your Hi, I am healthy

7. Conclusion

This lab demonstrates basic MPI communication between two processes.

It introduces:

Process ranks

Sending and receiving messages

Blocking communication

Forms the foundation for building more complex parallel programs.