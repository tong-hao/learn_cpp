// Author: Wes Kendall
// Copyright 2011 www.mpitutorial.com
// This code is provided freely with the tutorials on mpitutorial.com. Feel
// free to modify it for your own use. Any distribution of the code must
// either provide a link to www.mpitutorial.com or keep this header intact.
//
// Example of checking the MPI_Status object from an MPI_Recv call
//
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
	MPI_Init(NULL, NULL);

	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	if (world_size != 2) {
		fprintf(stderr, "Must use two processes for this example\n");
		MPI_Abort(MPI_COMM_WORLD, 1);
	}
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	int recv_bytes = 0;

	const int MAX_NUMBERS = 100;
	int numbers[MAX_NUMBERS];
	int number_amount;
	if (world_rank == 0) {
		std::string data = "123abc";
		recv_bytes = data.size();
		std::cout << "recv_bytes:" << recv_bytes << std::endl;
		MPI_Send(data.c_str(), data.size() - 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
	} else if (world_rank == 1) {
		MPI_Status status;
		char* s = nullptr;
		MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
		MPI_Get_count(&status, MPI_CHAR, &recv_bytes);
		std::cout << "recv_bytes:" << recv_bytes << std::endl;
		// recv_bytes = 100;

		char recv_data[recv_bytes];
		MPI_Recv(&recv_data, recv_bytes, MPI_CHAR, 0, 0, MPI_COMM_WORLD,
		         &status);

		std::cout << "recv: " << std::string(recv_data, recv_bytes)
		          << std::endl;
	}
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
}
