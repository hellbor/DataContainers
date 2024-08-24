#include<iostream>
using namespace std;

#define tab "\t"

class Element
{
private:
	int Data;
	Element* pNext;
	Element* pPrev;
public:
	Element(int Data, Element* pNext, Element* pPrev) :Data(Data), pNext(pNext), pPrev(pPrev)
	{
		cout << "EConstructor:\t\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t\t" << this << endl;
	}
	friend class List;
	friend class Iterator;
};

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
			Temp = Temp->pPrev = Temp->pNext;
			return *this;
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
		for(Element* Temp = Head;Temp; Temp = Temp->pPrev = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pPrev << tab << Temp->pNext << endl;
		cout << "Head:\t\t\t" << Head << endl;
		cout << "Tail:\t\t\t" << Tail << endl;
		//cout << "Head:\t" << Head << tab << "Tail:\t" << Tail << endl;
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