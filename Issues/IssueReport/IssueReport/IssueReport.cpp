#pragma once

#include <iostream>
#include <vector>
#include <mpi.h>
#include <thread>
#include <random>

// Repeat the frozon issue using multiple threads for Microsoft MPI.
std::default_random_engine e;
std::uniform_int_distribution<unsigned> u(0, 100);

void func(const int& size, const int& rank, const int& threadId) {
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(10));		
		std::vector<std::vector<float>> in_values(size);
		for (unsigned int i = 0; i < size; ++i) {
			in_values[i].push_back(rank);
			in_values[i].push_back(threadId);
			in_values[i].push_back(u(e));
		}
		std::vector<int> recv_count(size);
		std::vector<int> send_count(size);
		std::vector<int> send_disp(size + 1, 0);
		for (std::size_t p = 0; p < size; ++p)
		{
			recv_count[p] = in_values[p].size();
			send_count[p] = in_values[p].size();
			send_disp[p + 1] = send_disp[p] + send_count[p];
		}

		std::vector<int> recv_disp(size + 1, 0);
		std::vector<float> send_buff(send_disp[size]);
		for (std::size_t p = 0; p < size; ++p)
		{
			recv_disp[p + 1] = recv_disp[p] + send_count[p];
			std::copy(in_values[p].begin(), in_values[p].end(),
				send_buff.begin() + send_disp[p]);
		}

		std::vector<float> recv_buff;
		recv_buff.resize(recv_disp[size]);

		MPI_Alltoallv(send_buff.data(), send_count.data(),
			send_disp.data(), MPI_FLOAT,
			recv_buff.data(), recv_count.data(),
			recv_disp.data(), MPI_FLOAT, MPI_COMM_WORLD);

		size_t step = recv_buff.size() / size;
		for (std::size_t i = 0; i < size; ++i)
			std::cout << "Process No." << rank << "'s thread " << threadId << " received a random number " << recv_buff[i * step + 2] << " from Process No." << recv_buff.at(i * step) << "'s thread of " << recv_buff.at(i * step + 1) << "." << std::endl;

		MPI_Barrier(MPI_COMM_WORLD);

	}

}

int main(int argc, char** argv) {

	int rank, comm_size;
	int provided = -1;
	MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	std::thread t1(func, comm_size, rank, 0);
	std::thread t2(func, comm_size, rank, 1);
	std::thread t3(func, comm_size, rank, 2);
	std::thread t4(func, comm_size, rank, 3);
	std::thread t5(func, comm_size, rank, 4);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();

	MPI_Finalize();

	return 0;

}