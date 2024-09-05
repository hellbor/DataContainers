#pragma once
#include<iostream>
using namespace std;

using std::cin;
using std::cout;
using std::endl;;

#define tab "\t"

template<typename T> class ForwardList
{ 
	class Element
	{
	protected:
		T Data;			//«начение элемента
		Element* pNext;		//”казатель на следующий элемент
		static int count;
	public:
		Element(T Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
		{
			count++;
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~Element()
		{
			count--;
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

		}
		friend class ForwardList<T>;
		friend class Iterator<T>;
	}
};

template<typename T> class Iterator
{
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp = nullptr) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}

	Iterator& operator++();
	bool operator!=(const Iterator& other)const;
	T operator*();
};

template<typename T> class ForwardList
{
	Element<T>* Head;
	unsigned int size;
public:

	Iterator<T> begin();
	Iterator<T> end();
	//					Constructors:

	ForwardList();
	ForwardList(const std::initializer_list<T>& il);
	ForwardList(const ForwardList<T>& other);
	ForwardList(ForwardList<T>&& other)noexcept;
	~ForwardList();

	//					Operators:
	ForwardList<T>& operator=(const ForwardList<T>& other);
	ForwardList<T>& operator=(ForwardList<T>&& other)noexcept;

	//				Adding elements:
	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int Index);

	//					Removing elements:
	void pop_front();
	void pop_back();
	void erase(int Index);

	//					Methods:

	void reverse();
	void print()const;
};

void Print(int arr[]);
