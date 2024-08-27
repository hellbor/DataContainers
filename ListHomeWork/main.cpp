#include<iostream>
using namespace std;

#define tab "\t"

class Element
{
private:
	int Data;
	Element* pNext;
	Element* pPrev;
	static int count;
public:
	Element(int Data, Element* pPrev = nullptr, Element* pNext = nullptr) :Data(Data), pPrev(pPrev), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t\t" << this << endl;
	}
	friend class List;
	friend class Iterator;
};
int Element::count = 0;

	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp = nullptr) :Temp(Temp)
		{
			cout << "ItConstructor:\t" << this << endl;
		}
		~Iterator()
		{
			cout << "ItDestructor:\t" << this << endl;
		}
		Iterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		Iterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		bool operator!=(const Iterator& other)const
		{
			return this->Temp != other.Temp;
		}
		int operator*()
		{
			return Temp->Data;
		}
	};
class List
{
	Element* Head;
	Element* Tail;
	unsigned int size;
public:

	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return Tail;
	}

	//					Constructors
	List()
	{
		Head = nullptr;
		Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	List(const List& other) :List()
	{
		*this = other;
		cout << "LCopyConstructor:\t" << this << endl;
	}
	List(List&& other)noexcept :List()
	{
		*this = std::move(other);
		cout << "LMoveConstructor:\t" << this << endl;
	}
	~List()
	{
		cout << "LDestructor:\t\t" << this << endl;
	}

	//					Adding elements:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			Element* New = new Element(Data);
			New->pNext = Head;
			Head->pPrev = New;
			Head = New;
		}
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			Element* New = new Element(Data);
			New->pPrev = Tail;
			Tail->pNext = New;
			Tail = New;
		}
		size++;
	}

	//					Removing elements:
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
		}
		else
		{
			Head = Head->pNext;
			delete Head->pPrev;
			Head->pPrev = nullptr;
		}
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr && Tail == nullptr)
		if (Head == Tail)
		{
			delete Tail;
			Head = Tail = nullptr;
		}
		else
		{
			Tail = Tail->pPrev;
			delete Tail->pNext;
			Tail->pNext = nullptr;
		}
		size--;
	}

	//					Operators:
	List& operator=(const List& other)
	{
		if (this == &other)return *this;
		for (Element* Temp = other.Head; Temp; Temp = Temp->pPrev = Temp->pNext)
			cout << "LCopyAssignment:" << this << endl;
		return *this;
	}
	List& operator=(List&& other)noexcept
	{
		if (this == &other)return *this;
		this->Head = other.Head;
		this->Tail = other.Tail;
		this->size = other.size;
		other.Head = nullptr;
		other.Tail = nullptr;
		other.size = 0;
		cout << "LMoveAssignment:\t" << this << endl;
		return *this;
	}

	//					Methods:
	void print()const
	{
		cout << "Head:\t\t\t" << Head << endl;

		for(Element* Temp = Head;Temp; Temp = Temp->pNext)
			cout
			<< Temp->pPrev << tab
			<< Temp << tab
			<< Temp->Data << tab
			<< Temp->pNext << endl;
		cout << "Tail:\t\t\t" << Tail << endl;
		cout << "Введите количество элементов списка: " << size << endl;
		//cout << "Head:\t" << Head << tab << "Tail:\t" << Tail << endl;
	}
	void reverse_print()const
	{
		cout << "Tail:\t" << Tail << endl;

		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout
			<< Temp->pPrev << tab
			<< Temp << tab
			<< Temp->Data << tab
			<< Temp->pNext << endl;

		cout << "Head:\t" << Tail << endl;
		cout << "Введите количество элементов списка: " << size << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите количество элементов:"; cin >> n;
	List list;
	list.print();

	List list2 = list;
	list2.print();

	List list3 = std::move(list2);
	list3.print();
}