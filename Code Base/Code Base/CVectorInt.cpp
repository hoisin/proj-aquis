
#include "CVectorInt.h"


CVectorInt::CVectorInt(int vecSize) : pArray(nullptr), size(0), maxSize(vecSize)
{
	pArray = new int[maxSize];
}


CVectorInt::CVectorInt() : pArray(nullptr), size(0), maxSize(DEFAULT_SIZE)
{
	pArray = new int[maxSize];
}


CVectorInt::CVectorInt()
{
	if (pArray) {
		delete[] pArray;
		pArray = nullptr;
	}
}


void CVectorInt::Resize(int newSize)
{
}


//---------------------------------------------------------------------------
//
//	PushBack(...)
//
//	Params:
//	newVal	-	data to store
//
//	Adds new integer value to the back of the array
//
//---------------------------------------------------------------------------
void CVectorInt::PushBack(int newVal)
{
	// Expand vector if capacity reached
	if ((size + 1) >= maxSize) {
		int* pTempNew = new int[size + EXPAND_SIZE];
		int* pDst = pTempNew;
		const int* pSrc = pArray;
		const int* const pEnd = pDst + size;
		
		while (pDst != pEnd) 
			*pDst++ = *pSrc++;
		
		// Add new value to end
		pTempNew[size + 1] = newVal;
		size++;

		// Ressign array and cleanup old one
		pSrc = pArray;
		pArray = pTempNew;
		delete[] pSrc;
		pSrc = nullptr, pDst = nullptr, pTempNew = nullptr;
	}
	// Add new value to back of array
	else {
		pArray[size + 1] = newVal;
		size++;
	}
}


//---------------------------------------------------------------------------
//
//	PushFront(...)
//
//	Params:
//	newVal	-	data to store
//
//	Adds new integer value to the front of the array
//
//---------------------------------------------------------------------------
void CVectorInt::PushFront(int newVal)
{
	if ((size + 1) >= maxSize) {

	}
	else {
		int* pDst = pArray + (size + 1);
		int* pSrc = pArray + size;
		const int* const pEnd = pArray;

		while (pDst != pEnd)
			*pDst-- = *pSrc--;
	}
}
