#pragma once


namespace stuff
{
	template<class T>
	class LinkedList
	{
		template<class>
		class Node
		{
		public:
			T data;
			Node<T>* next;
			Node<T>(const T& d) : data(d), next() {}
			Node<T>(const Node<T>& node) : data(node.data), next() {}
			Node<T>(const Node<T>& copyNode, Node<T>* next) :
				data(copyNode.data), next(next) {}

		private:
			Node<T>& operator=(const Node<T>&) = delete;
		};

	public:
		LinkedList() : head(NULL) {}
		LinkedList(const LinkedList<T>& other);
		LinkedList(Node<T>* newNode) : head(newNode) {}
		~LinkedList();

		Node<T>* GetHead();
		void Insert(T val);

		operator =(LinkedList other);

		void Print();

	private:
		Node<T>* head;
	};
}


template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& other)
{
	Node<T>* current = other.head;

	if(head != current)
	{
		head = new LinkedList::Node<T>(other.data, other.next);
		current = current->next;

		Node<T>* tempNode = head;

		while(current)
		{
			Node<T>* newNode = new Node<T>(current->data);
			tempNode->next = newNode;
			tempNode = newNode;
			current = current->next;
		}
	}
}

template<class T>
LinkedList<T>& LinkedList<T>::opreator=(LinkedList other)
{

}