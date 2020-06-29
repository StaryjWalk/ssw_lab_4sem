#include <iostream>;
#include "Vector.h";
#include "Queue.h";
#include "Stack.h";
#include <chrono>;
#include <vector>;

int main()
{
	auto start = std::chrono::high_resolution_clock::now();

	Vector<int> vec1(0);
	for (int i = 0; i < 500; i++) {
		vec1.push(i);
	}
	for (int i = 0; i < 500; i++) {
		vec1.pop();
	}

	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Elapsed time: " << elapsed.count() << " s\n";



	auto start2 = std::chrono::high_resolution_clock::now();

	std::vector<int> vec2(0);
	for (int i = 0; i < 500; i++) {
		vec2.push_back(i);
	}
	for (int i = 0; i < 500; i++) {
		vec2.pop_back();
	}

	auto finish2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed2 = finish2 - start2;
	std::cout << "Elapsed time: " << elapsed2.count() << " s\n";

	return 0;
}
