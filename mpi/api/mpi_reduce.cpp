#include <fmt/format.h>
#include <mpi.h>
#include <iostream>

int main(int argc, char const *argv[]) {
	MPI_Init(NULL, NULL);

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int recv = 0;
	if (rank != 0) {
		MPI_Reduce(&rank, &recv, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
	} else {
		MPI_Reduce(MPI_IN_PLACE, &recv, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
	}

	std::cout << fmt::format("rank:{}, recv={}", rank, recv) << std::endl;

	MPI_Finalize();

	return 0;
}

// link: -lmpi -lfmt
