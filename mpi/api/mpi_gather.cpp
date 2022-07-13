#include <fmt/format.h>
#include <mpi.h>
#include <iostream>

int main(int argc, char const *argv[]) {
	MPI_Init(NULL, NULL);

	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	std::cout << "world_rank: " << world_rank << std::endl;

	int *array = new int[4];
	memset(array, 0, sizeof(int) * 4);
	array[world_rank] = world_rank + 1;

	if (world_rank != 0) {
		// Each process (root process included) sends the contents of its send
		// buffer to the root process. The root process receives the messages
		// and stores them in rank order.
		MPI_Gather(array + world_rank, 1, MPI_INT, array, 1, MPI_INT, 0,
		           MPI_COMM_WORLD);
	} else {
		MPI_Gather(MPI_IN_PLACE, 1, MPI_INT, array, 1, MPI_INT, 0,
		           MPI_COMM_WORLD);
	}

	std::cout << "world_rank: " << world_rank
	          << fmt::format(" {},{},{},{}", *array, *(array + 1), *(array + 2),
	                         *(array + 3))
	          << std::endl;

	MPI_Finalize();
	return 0;
}
// link: -lmpi -lfmt