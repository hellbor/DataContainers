#include"ForwardList.h"

template<typename T> int ForwardList<T>::Element::count = 0;

template<typename T> class ForwardList
{
	Element<T>* Head;
	unsigned int size;
public:

	template<typename T>Iterator<T> ForwardList<T>::begin()
	{
		return Head;
	}
	template<typename T>Iterator<T> ForwardList<T>::end()
	{
		return nullptr;
	}
	//					Constructors:

	template<typename T>ForwardList<T>::ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	template<typename T>ForwardList<T>::ForwardList(const std::initializer_list<T>& il) :ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		for (T const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	template<typename T>ForwardList<T>::ForwardList(const ForwardList<T>& other) :ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
		*this = other;
		cout << "LCopyConstructor:" << this << endl;
	}
	template<typename T>ForwardList::ForwardList(ForwardList<T>&& other)noexcept :ForwardList()
	{
		/*this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;*/
		*this = std::move(other);
		cout << "LMoveConstructor:\t" << this << endl;
	}
	template<typename T>ForwardList::~ForwardList()
	{
		/*while (Head)pop_front();
		pop_back();*/
		cout << "LDestructor:\t" << this << endl;
	}
	//				Adding elements:
	template<typename T>void ForwardList<T>::push_front(T Data)
	{
		////1) ������� ����� �������:
		//Element* New = new Element(Data);
		////2) �������� ����� ������� � ������:
		//New->pNext = Head;
		////3) ��������� ������ �� ����� �������:
		//Head = New;

		Head = new Element(Data, Head);
		size++;
	}

	template<typename T> void ForwardList<T>::push_back(T Data)
	{
		if (Head == nullptr)return push_front(Data);
		//1) ������� �� ����� ������:
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}

		////2) ������� ����� �������:
		//Element* New = new Element(Data);
		////3) �������� ����� ������� � ������:
		//Temp->pNext = New;

		Temp->pNext = new Element<T>(Data);
		size++;
	}
	template<typename T> void ForwardList<T>::insert(T Data, int Index)
	{
		if (Index > Head->count)return;
		if (Index == 0)return push_front(Data);
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;

		/*Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;*/

		Temp->pNext = new Element<T>(Data, Temp->pNext);
		size++;
	}

	//					Removing elements:
	template<typename T> void ForwardList<T>::pop_front()
	{
		if (Head == nullptr)return;
		Element<T>* erased = Head;	//1)���������� ����� ���������� ��������
		Head = Head->pNext;		//2)������� ������ �� ��������� �������
		delete erased;			//3)������� ������� �� ������
		size--;
	}
	template<typename T> void ForwardList<T>::pop_back()
	{
		if (Head == nullptr || Head->pNext == nullptr)return pop_front();

		//1)������� �� �������������� �������� ������
		Element<T>* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;

		//2) ������� ��������� ������� �� ������:
		delete Temp->pNext;

		//3) �������� ��������� �� ��������� �������:
		Temp->pNext = nullptr;
		size--;
	}
	template<typename T> void ForwardList<T>::erase(int Index)
	{
		if (Index >= size)return;
		if (Index == 0)return pop_front();

		//1) ������� �� �������� ����� ���������:
		Element<T>* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;

		//2) ���������� ����� ���������� ��������:
		Element<T>* erased = Temp->pNext;

		//3) ��������� ��������� ������� �� ������:
		Temp->pNext = Temp->pNext->pNext;

		//4) ������� ������� �� ������:
		delete erased;
		size--;
	}

	//					Methods:

	template<typename T> void ForwardList<T>::reverse()
	{
		ForwardList buffer;
		while (Head)
		{
			buffer.push_front(Head->Data);
			pop_front();
		}
		this->Head = buffer.Head;
		this->size = buffer.size;
		buffer.Head = nullptr;
	}

	template<typename T> void ForwardList<T>::print()const
	{
		cout << "Head:\t" << Head << endl;
		//Element* Temp = Head;	//Temp - ��� ��������.
		////�������� - ��� ���������, ��� ������ �������� ����� ���������� ��������� ������
		//while (Temp)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext; //������� �� ��������� �������
		//}
		for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;;
		cout << "���������� ��������� ������: " << size << endl;
		cout << "����� ���������� ��������� ������: " << Element<T>::count << endl;
		//cout << "����� ���������� ��������� ������: " << Head->count << endl;
	}
};

template<typename T>void Print(int arr[])
{
	cout << typeid(arr).name() << endl;
	cout << sizeof(arr) << endl;
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;
	/*for (int : arr)
	{
		cout << i << tab;
	}
	cout << endl;*/
}