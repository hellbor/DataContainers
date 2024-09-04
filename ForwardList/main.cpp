#include<iostream>
using namespace std;

using std::cin;
using std::cout;
using std::endl;;

#define tab "\t"

template<typename T> class Iterator;
template<typename T> class ForwardList;

template<typename T> class Element
{
protected:
	T Data;			//Значение элемента
	Element<T>* pNext;		//Указатель на следующий элемент
	static int count;
public:
	Element(T Data, Element<T>* pNext = nullptr) :Data(Data), pNext(pNext)
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
};
	template<typename T> int Element<T>::count = 0;

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

		Iterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}

		bool operator!=(const Iterator& other)const
		{
			return this->Temp != other.Temp;
		}

		T operator*()
		{
			return Temp->Data;
		}
	};

template<typename T> class ForwardList
{
	Element<T>* Head;
	unsigned int size;
public:

	Iterator<T> begin()
	{
		return Head;
	}
	Iterator<T> end()
	{
		return nullptr;
	}
	//					Constructors:

	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const std::initializer_list<T>& il) :ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		for (T const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	ForwardList(const ForwardList<T>& other) :ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
		*this = other;
		cout << "LCopyConstructor:" << this << endl;
	}
	ForwardList(ForwardList<T>&& other)noexcept :ForwardList()
	{
		/*this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;*/
		*this = std::move(other);
		cout << "LMoveConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		/*while (Head)pop_front();
		pop_back();*/
		cout << "LDestructor:\t" << this << endl;
	}

	//					Operators:
	ForwardList<T>& operator=(const ForwardList<T>& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		reverse();
		cout << "LCopyAssignment:" << this << endl;
		return *this;
	}
	ForwardList<T>& operator=(ForwardList<T>&& other)noexcept
	{
		if (this == &other)return *this;
		//delete[]this->Head;
		while (Head)pop_front();
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "LMoveAssignment:\t\t" << this << endl;
		return *this;
	}

	//				Adding elements:
	void push_front(T Data)
	{
		////1) Создаем новый элемент:
		//Element* New = new Element(Data);
		////2) Включаем новый элемент в список:
		//New->pNext = Head;
		////3) Переводим Голову на новый элемент:
		//Head = New;

		Head = new Element<T>(Data, Head);
		size++;
	}

	void push_back(T Data)
	{
		if (Head == nullptr)return push_front(Data);
		//1) Доходим до конца списка:
		Element<T>* Temp = Head;
		while (Temp -> pNext)
		{
			Temp = Temp->pNext;
		}

		////2) Создаем новый элемент:
		//Element* New = new Element(Data);
		////3) Включаем новый элемент в список:
		//Temp->pNext = New;

		Temp->pNext = new Element<T>(Data);
		size++;
	}
	void insert(T Data, int Index)
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
	void pop_front()
	{
		if (Head == nullptr)return;
		Element<T>* erased = Head;	//1)Запоминаем адрес удаляемого элемента
		Head = Head->pNext;		//2)Смещаем Голову на следующий элемент
		delete erased;			//3)Удаляем элемент из памяти
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr||Head->pNext == nullptr)return pop_front();

		//1)Доходим до предпоследнего элемента списка
		Element<T>* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;

		//2) Удаляем последний элемент из памяти:
		delete Temp->pNext;

		//3) Зануляем указатель на последний элемент:
		Temp->pNext = nullptr;
		size--;
	}
	void erase(int Index)
	{
		if (Index >= size)return;
		if (Index == 0)return pop_front();

		//1) Доходим до элемента перед удаляемым:
		Element<T>* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;

		//2) Запоминаем адрес удаляемого элемента:
		Element<T>* erased = Temp->pNext;

		//3) Исключаем удаляемый элемент из списка:
		Temp->pNext = Temp->pNext->pNext;

		//4) Удаляем элемент из памяти:
		delete erased;
		size--;
	}

	//					Methods:

	void reverse()
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

	void print()const
	{
		cout << "Head:\t" << Head << endl;
		//Element* Temp = Head;	//Temp - это итератор.
		////Итератор - это указатель, при помощи которого можно перебирать структуры данных
		//while (Temp)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext; //Переход на следующий элемент
		//}
		for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;;
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов списка: " << Element<T>::count << endl;
		//cout << "Общее количество элементов списка: " << Head->count << endl;
	}
};

void Print(int arr[])
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

//#define BASE_CHECK
//#define COUNT_CHECK
//#define LIST_CHECK
//#define RANGE_BASED_FOR_ARRAY
#define RANGE_BASED_FOR_LIST

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	//Element element(5);
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	list.print();
	//list.push_back(123);
	//list.print();
	//list.pop_back();
	//list.print();

	int index;
	int value;
	cout << "Введите индекс нового элемента: "; cin >> index;
	cout << "Введите значение нового элемента: "; cin >> value;
	list.insert(value, index);
	list.print();

	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();

#endif // BASE_CHECK

#ifdef COUNT_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();
	
	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();

#endif // COUNT_CHECK

#ifdef LIST_CHECK
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	cout << "List filled" << endl;
	list.print();

	cout << "Making copy" << endl;
	ForwardList list2 = list;				//CopyConstructor
	//ForwardList list2;
	//list2 = list;
	list2.print();
	cout << "Copy DONE" << endl;

	ForwardList list3 = std::move(list2);	//MoveConstructor
	list3.print();

#endif // LIST_CHECK

#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3,5,8,13,21,34,55,89,144 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	//Ranged-based for:
	//Range (диапозон) в данном случае понимается как контейнер
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;

	Print(arr);
#endif // RANGE_BASED_FOR_ARRAY

#ifdef RANGE_BASED_FOR_LIST
	ForwardList<int> list = { 3, 5, 8, 13, 21 };
	//list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_LIST
}