#include <iostream>


using namespace std;
template <class T>
class List
{
public:
	struct Node
	{
		T elem;
		Node* next;
		Node(T newElem, Node* newNext = nullptr)
		{
			elem = newElem;
			next = newNext;
		}
		Node(const Node& node)
		{
			elem = node.elem;
			delete[] next;
			next = new Node();
			next = node.next;
		}
	};

	Node* root;

	class iterator
	{
	public:
		Node* i_node;

		iterator()
		{
			i_node = nullptr;
		}

		iterator(Node* nptr)
		{
			i_node = nptr;
		}

		iterator(const iterator& iter)
		{
			i_node = iter.i_node;
		}

		~iterator()
		{
			i_node = nullptr;
		}

		iterator& operator++()
		{
			i_node = i_node->next;
			return *this;
		}

		iterator operator++(int)
		{
			iterator tmp(*this);
			i_node = i_node->next;
			return tmp;
		}

		T& operator*()
		{
			return i_node->elem;
		}

		iterator& operator=(const iterator& it1)
		{
			i_node = it1.i_node;
			return *this;
		}

		iterator operator+(int step)
		{
			iterator tmp = i_node;
			for (int i = 0; i < step; i++)
			{
				tmp++;
			}
			return tmp;
		}

		friend bool operator==(const iterator& it1, const iterator& it2)
		{
			return (it1.i_node == it2.i_node);
		}

		friend bool operator!=(const iterator& it1, const iterator& it2)
		{
			return (it1.i_node != it2.i_node);
		}
	};

	List()
	{
		root = nullptr;
	}

	List(int size)
	{
		root = new Node(0);
		Node* tmp = root;
		for (int i = 1; i < size; i++) {
			tmp->next = new Node(0);
			tmp = tmp->next;
		}
	}

	List(const List& other)
	{
		root = new Node(other.root->elem);
		Node* tmp = root;
		Node* res = other.root;
		while (res->next)
		{
			tmp->next = new Node(res->next->elem);
			tmp = tmp->next;
			res = res->next;
		}
	}

	~List()
	{
		clear();
	}

	List& operator=(const List& list)
	{
		if (this == list)
		{
			return *this;
		}
		root = new Node(list.root->elem);
		Node* tmp1 = root;
		Node* tmp2 = list.root;
		while (tmp2->next)
		{
			tmp1->next = new Node(tmp2->next->elem);
			tmp1 = tmp1->next;
			tmp2 = tmp2->next;
		}
	}

	bool empty() const
	{
		if (root == nullptr)
		{
			return true;
		}
		return false;
	}

	int getSize()
	{
		int size = 0;
		for (auto it = begin(); it != end(); ++it)
		{
			size++;
		}
		return ++size;
	}

	void clear()
	{
		if (empty())
		{
			return;
		}
		else
		{
			Node* tmp = root;
			Node* tmp2;
			while (tmp->next != nullptr)
			{
				tmp2 = tmp->next;
				delete tmp;
				tmp = tmp2;
			}
			root = nullptr;
		}
	}

	void merge(const List& list)
	{
		if (getSize() + list.getSize() == 0)
		{
			return;
		}
		Node* res = new Node(root->elem);
		Node* tmp = res;
		Node* tmp2 = root->next;
		iterator iter = begin();
		for (++iter; iter != end(); ++iter)
		{
			tmp->next = new Node(tmp2->elem);
			tmp = tmp->next;
			tmp2 = tmp2->next;
		}
		tmp2 = list.root;
		for (iterator it = list.begin(); it != list.end(); ++it)
		{
			tmp->next = new Node(tmp2->elem);
			tmp = tmp->next;
			tmp2 = tmp2->next;
		}
		root = res;
	}

	List mergeSort()
	{

	}

	iterator begin()
	{
		return iterator(root);
	}

	iterator end()
	{
		Node* tmp = root;
		while (tmp->next != nullptr)
		{
			tmp = tmp->next;
		}
		return iterator(tmp);
	}

	iterator insert_after(iterator pos, T value)
	{
		Node* tmp = new Node(value);
		tmp->next = pos.i_node->next;
		pos.i_node->next = tmp;
		return iterator(tmp);
	}

	iterator erase_after(iterator pos)
	{
		Node* tmp = pos.i_node;
		Node* tmp2 = tmp->next;
		tmp->next = tmp2->next;
		delete tmp2;
		return iterator(tmp->next);
	}

	void push_front(T value)
	{
		Node* node = new Node(value, nullptr);
		if (empty())
		{
			root = node;
		}
		else
		{
			node->next = root;
			root = node;
		}
	}

	void push_back(T value)
	{
		if (empty())
		{
			Node* tmp = new Node(value);
			root = tmp;
		}
		else
		{
			Node* tmp = root;
			while (tmp->next != nullptr)
			{
				tmp = tmp->next;
			}
			Node* tmp2 = new Node(value);
			tmp->next = tmp2;
		}
	}

	void pop_back()
	{
		iterator iter = begin();
		for (int i = 0; i < getSize() - 2; i++)
		{
			++iter;
		}
		erase_after(iter);
	}

	void pop_front()
	{
		if (root == nullptr)
		{
			throw "Error pop_front because list is empty";
		}
		Node* tmp = root->next;
		root = tmp;
	}

	void print()
	{
		Node* tmp = root;
		while (tmp)
		{
			cout << tmp->elem;
			tmp = tmp->next;
		}
		cout << endl;
	}
};