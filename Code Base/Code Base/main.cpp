#include <iostream>
#include "algorithms.h"
#include "CTimer.h"


int main(int argc, char* argv[])
{
	const bool bPrint = false;
	const int arraySize = 50000;
	int data[arraySize], data2[arraySize];

	for (int i = 0; i < arraySize; i++) {
		data[i] = arraySize - i; // Worst case
		data2[i] = arraySize - i;
		//data[i] = rand() % arraySize; // random
	}

	if (bPrint) {
		// Output the unsorted data
		for (int j = 0; j < arraySize; j++)
			printf("Element %d contains: %d\n", j, data[j]);
	}

	CTimer t1;
	t1.Start();
	codebase::BubbleSort(data, arraySize);
	t1.Stop();

	CTimer t2;
	t2.Start();
	codebase::Sort_3(data2, arraySize);
	t2.Stop();

	if (bPrint) {
		for (int k = 0; k < arraySize; k++)
			printf("Sorted Element %d contains: %d\n", k, data2[k]);
	}

	printf("Time to run bubble sort: %f\n", t1.Time());
	printf("Time to run sort 1: %f\n", t2.Time());

	system("PAUSE");
	return 0;
}
