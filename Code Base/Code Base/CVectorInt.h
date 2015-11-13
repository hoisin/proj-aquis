/*
	13/11/2015

	Vector array containing integers.
	Contiguous memory block
*/

#ifndef CVECTORINT_H_
#define CVECTORINT_H_

#define DEFAULT_SIZE 64
#define EXPAND_SIZE 64

class CVectorInt
{
public:
	CVectorInt(int vecSize);
	CVectorInt();
	~CVectorInt();

	void Resize(int newSize);

	void PushBack(int newVal);
	void PushFront(int newVal);

private:
	int* pArray;

	int size;		// Total elements used
	int maxSize;	// Entire size of vector
};


#endif
