#include "algorithms.h"

namespace codebase
{
	//-----------------------------------------------------------
	//
	//	BubbleSort()
	//
	//	Params:
	//	pArray		-	Unsorted array of integers
	//	arraySize	-	Number of elements in the array
	//
	//	Performs a bubble sort on an array of unsorted integers
	//
	//-----------------------------------------------------------
	void BubbleSort(int* pArray, int arraySize)
	{
		bool bSorted = false;
		int idx = 0;

		while (!bSorted) {
			bSorted = true;
			
			// Go through all elements
			while (idx < (arraySize - 1)) {
				// Swap if current 2 elements not sorted
				if (pArray[idx] > pArray[idx + 1]) {
					int temp = pArray[idx];
					pArray[idx] = pArray[idx + 1];
					pArray[idx + 1] = temp;
					bSorted = false;
				}
				idx++;
			}

			// Reset to 0 if gone to the end
			idx = 0;
		}
	}

	//-----------------------------------------------------------
	//
	//	Sort_1()
	//
	//	Params:
	//	pArray		-	Unsorted array of integers
	//	arraySize	-	Number of elements in the array
	//
	//	Performs an unknown sort on an array of unsorted integers
	//
	//-----------------------------------------------------------
	void Sort_1(int* pArray, int arraySize)
	{
		int currentIdx = 0;
		int compIdx = 0;
		int lowestIdx = 0;

		while (currentIdx < arraySize - 1) {
			compIdx = currentIdx + 1;
			lowestIdx = currentIdx;
			while (compIdx < arraySize) {
				if (pArray[currentIdx] > pArray[compIdx])
					lowestIdx = compIdx;
				compIdx++;
			}

			if (currentIdx != lowestIdx) {
				int temp = pArray[currentIdx];
				pArray[currentIdx] = pArray[lowestIdx];
				pArray[lowestIdx] = temp;
			}

			currentIdx++;
		}
	}

	void Sort_2(int* pArray, int arraySize)
	{
		int latestIdx = 0;
		int compIdx = 0;

		while (latestIdx < arraySize - 1) {
			if (pArray[latestIdx] > pArray[latestIdx + 1]) {
				int temp = pArray[latestIdx];
				pArray[latestIdx] = pArray[latestIdx + 1];
				pArray[latestIdx + 1] = temp;

			}
		}
	}
}