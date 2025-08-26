# Introduction to MPI (Message Passing Interface)

## What is MPI?

MPI (Message Passing Interface) is a standardized and portable message-passing system designed to allow processes to communicate with each other in parallel computing environments. It is widely used for programming on clusters and supercomputers.

## Why Use MPI?

- **Scalability:** Enables parallel programs to run on many nodes.
- **Portability:** Works across different hardware and operating systems.
- **Performance:** Efficient communication between processes.

## Basic MPI Program Structure

### 1. Initialization and Finalization

Every MPI program must initialize and finalize the MPI environment:

```c
#include <mpi.h>
int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);      // Initialize MPI
    // ... your code ...
    MPI_Finalize();              // Finalize MPI
    return 0;
}
```

### 2. Communicators

A communicator defines a group of processes that can communicate. The default communicator is `MPI_COMM_WORLD`, which includes all processes.

```c
int rank, size;
MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get process rank
MPI_Comm_size(MPI_COMM_WORLD, &size); // Get total number of processes
```

### 3. Sending and Receiving Messages

- **MPI_Send:** Send a message to another process.
- **MPI_Recv:** Receive a message from another process.

```c
if (rank == 0) {
    int data = 100;
    MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD); // Send to process 1
} else if (rank == 1) {
    int received;
    MPI_Recv(&received, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // Receive from process 0
}
```

### 4. Example: Complete MPI Program

```c
#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        int data = 42;
        MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent data %d to process 1\n", data);
    } else if (rank == 1) {
        int received;
        MPI_Recv(&received, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received data %d from process 0\n", received);
    }

    MPI_Finalize();
    return 0;
}
```

## Summary of MPI Functions

- `MPI_Init`: Initialize MPI environment.
- `MPI_Finalize`: Clean up MPI environment.
- `MPI_Comm_rank`: Get process rank in communicator.
- `MPI_Comm_size`: Get number of processes in communicator.
- `MPI_Send`: Send data to another process.
- `MPI_Recv`: Receive data from another process.

## Layman Reading

Imagine you have a group of friends working together on a big project. Instead of everyone shouting across the room, each person sends messages to others to share information and coordinate tasks. MPI is like a set of rules for how these messages are sent and received between computers (the "friends") working together.

- **Initialization:** Everyone agrees to start working together.
- **Communicator:** The group of friends who can talk to each other.
- **Send/Receive:** One friend sends a message, another receives it.

### Azure Cloud Example

Suppose you want to run a weather simulation using several computers in the Azure cloud. Each computer (virtual machine) is like a friend in the group. Using MPI, you can split the simulation into parts, and each computer works on its part. When a computer needs results from another, it sends a message using MPI. Azure lets you easily create and connect these computers, so MPI helps them work together efficiently.

**Practical Steps:**
1. Create multiple virtual machines on Azure.
2. Install MPI (like OpenMPI) on each machine.
3. Use MPI commands to run your program across all machines.
4. The program uses MPI to send and receive data, just like in the examples above.

This way, you can solve big problems faster by letting many computers work together and communicate using MPI!