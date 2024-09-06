#pragma once
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n---------------------------------------------\n"

template<typename T>class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

		}
		friend class List;
	}*Head, * Tail;
	size_t size;

	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr) :Temp(Temp) {}
		~ConstBaseIterator() {}

		//				Comperison operators:
		bool operator==(const ConstBaseIterator& other)const;
		bool operator!=(const ConstBaseIterator& other)const;

		//				Dereferense operators:
		const T& operator*()const;
	};
public:
	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~ConstIterator()
		{
#ifdef DEBUG
			cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG
		}

		ConstIterator& operator++()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}
		ConstIterator operator--()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return old;
		}
	};
	class ConstReverseIterator :public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "RItConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~ConstReverseIterator()
		{
#ifdef DEBUG
			cout << "RItDestructor:\t" << this << endl;
#endif // DEBUG

		}

		//					Increment/Decrement:
		ConstReverseIterator& operator++()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}
	};

	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp) {}
		~Iterator() {}
		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr) :ConstReverseIterator(Temp) {}
		~ReverseIterator() {}
		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};

	ConstIterator begin()const;
	ConstIterator end()const;
	Iterator begin();
	Iterator end();

	ConstReverseIterator rbegin()const;
	ConstReverseIterator rend()const;
	ReverseIterator rbegin();
	ReverseIterator rend();

	//				Constructors:
	List();
	List(const std::initializer_list<T>& il);
	List(const List<T>& other);
	~List();

	//					Assignment operators:
	List<T>& operator=(const List<T>& other);

	//				Adding elements:
	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int Index);

	//					Removing elements:
	void pop_front();
	void pop_back();
	void erase(int Index);


	//					Methods:
	void print()const;
	void reverse_print()const;
};
