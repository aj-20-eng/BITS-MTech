#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    char message[100];  // array to hold text messages

    MPI_Init(&argc, &argv);                 // start MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   // get process rank
    MPI_Comm_size(MPI_COMM_WORLD, &size);   // get total processes

    if (size < 2) {
        if (rank == 0)
            printf("This program requires at least 2 processes.\n");
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        // Process A (rank 0) sends "Hi"
        strcpy(message, "Hi");
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent: %s\n", message);

        // Then wait for reply
        MPI_Recv(message, 100, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 0 received reply: %s\n", message);
    }
    else if (rank == 1) {
        // Process B (rank 1) receives "Hi"
        MPI_Recv(message, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received: %s\n", message);

        // Send back reply
        strcpy(message, "I received your Hi, I am healthy");
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        printf("Process 1 sent reply: %s\n", message);
    }

    MPI_Finalize();   // end MPI
    return 0;
}
