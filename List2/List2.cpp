#include"List2.h"

//				Comperison operators:
template<typename T> bool List<T>::ConstBaseIterator::operator==(const ConstBaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template<typename T> bool List<T>::ConstBaseIterator::operator!=(const ConstBaseIterator& other)const
{
	return this->Temp != other.Temp;
}
//				Dereferense operators:
template<typename T>const T& List<T>::ConstBaseIterator::operator*()const
{
	return Temp->Data;
}
template<typename T>typename List<T>::ConstIterator List<T>::begin()const
{
	return Head;
}
template<typename T>typename List<T>::ConstIterator List<T>::end()const
{
	return nullptr;
}
template<typename T>typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template<typename T>typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template<typename T> typename List<T>::ConstReverseIterator List<T>::rbegin()const
{
	return Tail;
}
template<typename T> typename List<T>::ConstReverseIterator List<T>::rend()const
{
	return nullptr;
}
template<typename T> typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}
template<typename T> typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}

//				Constructors:
template<typename T>List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
template<typename T> List<T>::List(const std::initializer_list<T>& il) :List()
{
	for (T const* it = il.begin(); it != il.end(); ++it)
	{
		push_back(*it);
	}
}
template<typename T> List<T>::List(const List<T>& other) :List()
{
	*this = other;
	cout << "LCopyConstructor:\t" << this << endl;
}
template<typename T>List<T>::~List()
{
	//while (Head)pop_front();
	while (Tail)pop_back();
	cout << "LDestructor:\t" << this << endl;
}

//					Assignment operators:
template<typename T> List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		push_back(Temp->Data);
	cout << "LCopyAssignment:" << this << endl;
	return *this;
}

//				Adding elements:
template<typename T> void List<T>::push_front(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
	}
	else
	{
		/*Element* New = new Element(Data);
		New->pNext = Head;
		Head->pPrev = New;
		Head = New;*/

		Head = Head->pPrev = new Element(Data, Head);
	}
	size++;
}
template<typename T> void List<T>::push_back(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
	}
	else
	{
		/*Element* New = new Element(Data);
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;*/

		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	}
	size++;
}
template<typename T> void List<T>::insert(T Data, int Index)
{
	if (Index > size)return;
	if (Index == 0)return push_front(Data);
	if (Index == size)return push_back(Data);

	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < Index; i++)
			Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = Index; i < size - 1; i++)
			Temp = Temp->pPrev;
	}
	/*Element* New = new Element(Data);
	New->pNext = Temp;
	New->pPrev = Temp->pPrev;
	Temp->pPrev->pNext = New;
	Temp->pPrev = New;*/

	Temp = Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp);

	size++;
}

//					Removing elements:
template<typename T> void List<T>::pop_front()
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
template<typename T> void List<T>::pop_back()
{
	if (Head == nullptr && Tail == nullptr)return;
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
template<typename T> void List<T>::erase(int Index)
{
	if (Index > size) return;
	if (Index == 0) return pop_front();
	if (Index == size) return pop_back();

	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < Index; i++)
		{
			Temp = Temp->pNext;
		}
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - Index - 1; i++)
		{
			Temp = Temp->pPrev;
		}
	}
	Temp->pPrev->pNext = Temp->pNext;
	Temp->pNext->pPrev = Temp->pPrev;
	delete Temp;
	size--;
}


//					Methods:
template<typename T> void List<T>::print()const
{
	cout << delimiter << endl;
	cout << "Head:\t" << Head << endl;
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout
		<< Temp->pPrev << tab
		<< Temp << tab
		<< Temp->Data << tab
		<< Temp->pNext << endl;
	cout << "Tail:\t" << Tail << endl;
	cout << "Количество элементов списка: " << size << endl;
	cout << delimiter << endl;
}
template<typename T> void List<T>::reverse_print()const
{
	cout << delimiter << endl;
	cout << "Tail:\t" << Tail << endl;

	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout
		<< Temp->pPrev << tab
		<< Temp << tab
		<< Temp->Data << tab
		<< Temp->pNext << endl;

	cout << "Head:\t" << Head << endl;
	cout << "Количество элементов списка: " << size << endl;
	cout << delimiter << endl;
}

template<typename T>List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> buffer = left;					//CopyConstructor
	for (typename List<T>::ConstIterator it = right.begin(); it != right.end(); ++it)
	{
		buffer.push_back(*it);
		//*it *= 10;
	}
	return buffer;
}
template<typename T>void Grow(List<T>& list)
{
	for (typename List<T>::Iterator it = list.begin(); it != list.end(); ++it)
		*it *= 10;
}