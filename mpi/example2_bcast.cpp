#include <mpi.h>
#include <iostream>
#include <string>

void Gather(int rank, int numprocs) {
	int recvbuf[numprocs];
	int recvcount;
	MPI_Allgather(&rank, 1, MPI_INT, recvbuf, 1, MPI_INT, MPI_COMM_WORLD);

	std::cout << "[gather] rank:" << rank << ", data:" << recvbuf[0]
	          << recvbuf[1] << recvbuf[2] << recvbuf[3] << std::endl;
}

void Bcast(int rank) {
	std::string data = "hello";
	data.append(std::to_string(rank));

	MPI_Bcast((void *)data.data(), data.size(), MPI_CHAR, rank, MPI_COMM_WORLD);

	std::cout << "[bcast] rank:" << rank << ", data:" << data << std::endl;
}

int main(int argc, char *argv[]) {
	int rank;
	int numprocs;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	Gather(rank, numprocs);
	Bcast(rank);

	MPI_Finalize();
	return 0;
}
