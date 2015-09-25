/*
	25/09/2015

	Author: Matty

	Singular Linked list class
*/

#ifndef __CBLINKEDLIST_H__
#define __CBLINKEDLIST_H__

namespace cbstruct
{

	template <class T>
	class Node
	{
	public:
		template <typename T>
		Node(const Node<T>& other) : data(other.data), pNext(other.pNext)
		{
		}

		template <typename T>
		Node(T val, Node<T>* pNode = nullptr) : data(val), pNext(pNode)
		{
		}

		Node() {}
		~Node() {}

	public:
		T data;
		Node<T>* pNext;
	};


	template <class T>
	class LinkedList
	{
	public:
		LinkedList() : pHead(nullptr)
		{
		}

		~LinkedList()
		{
			Clear();
		}

		void PushFront(T val)
		{
			Node<T>* pNewNode = new Node<T>(val);

			if (pHead != nullptr) {
				pNewNode->pNext = pHead;
				pHead = pNewNode;
			}
			else
				pHead = pNewNode;
		}

		void PushBack(val)
		{
			Node<T>* pNewNode = new Node<T>(val);

			if (pHead != nullptr) {
				Node<T>* pCurrentNode = pHead, pNextNode = pHead->pNext;
				while (pNextNode != nullptr) {
					pCurrentNode = pCurrentNode->pNext;		// Get next current node
					pNextNode = pCurrentNode->pNext;		// Get new current node's next ptr
				}
				pCurrentNode->pNext = pNewNode;
			}
			else
				pHead = pNewNode;
		}

		T Pop()
		{
			if (pHead != nullptr) {
				T returnVal = pHead->data;
				Node<T>* pTempNode = pHead;
				pHead = pHead->pNext;
				delete pTempNode;
				pTempNode = nullptr;
				return returnVal;
			}
			return nullptr;
		}

		void Clear()
		{
			if (pHead != nullptr) {
				while (pHead != nullptr) {
					Node<T>* pTempNode = pHead->pNext;
					delete pHead;
					pHead = pTempNode;
				}
			}
		}

		bool IsEmpty()
		{
			if (pHead == nullptr)
				return true;

			return false;
		}

	public:
		Node<T>* pHead;
	};

};


#endif