#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

template <class T>
struct Node
{
	T data;
	Node<T>* next;
};

template <class T>
class LinkedList
{
private:

	Node<T>* head;
	Node<T>* itr;
	Node<T>* create(T& data)
	{
		Node<T>* nw = new Node<T>;
		nw->data = data;
		nw->next = nullptr;
		return nw;
	}
public:
	LinkedList()
	{
		this->head = nullptr;
		this->itr = nullptr;
	}
	~LinkedList()
	{
		Node<T>* tmp;
		while(this->head != nullptr)
		{
			tmp = this->head->next;
			delete this->head;
			this->head = tmp;
		}
	}
	Node<T>* begin()
	{
		this->itr = this->head;
		return this->itr;
	}
	Node<T>* end()
	{
		return nullptr;
	}
	Node<T>* next()
	{
		this->itr = this->itr->next;
		return this->itr;
	}

	void append(T& data)
	{
		if(this->head == nullptr)
		{
			this->head = this->create(data);
		}else
		{
			Node<T>* nodeptr = this->head;
			Node<T>* prevnode = this->head;
			while(nodeptr != nullptr)
			{
				prevnode = nodeptr;
				nodeptr = nodeptr->next;
			}
			prevnode->next = this->create(data);
		}
	}
};




#endif
