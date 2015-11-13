/*
	03/11/2015

	Stack storing integers (signed)
	Default stack size of 10
*/

#ifndef CSTACK_H_
#define CSTACK_H_


class CStackInt
{
public:
	CStackInt();
	CStackInt(int stackSize);
	CStackInt(const CStackInt& other);
	~CStackInt();

	CStackInt& operator=(const CStackInt& rhs);

	int Top();

	void Push(int value);
	int Pop();

	bool IsEmpty();

	void Print();

	int GetCount() const { return count; }
	int GetMaxSize() const { return maxSize; }

private:
	int* top;
	int* stack;

	unsigned int count;
	unsigned int maxSize;
};


#endif