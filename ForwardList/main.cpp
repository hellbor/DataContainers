#include<iostream>
using namespace std;

using std::cin;
using std::cout;
using std::endl;;

#define tab "\t"

class Element
{
protected:
	int Data;			//Значение элемента
	Element* pNext;		//Указатель на следующий элемент
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
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
	friend class ForwardList;
};
	int Element:: count = 0;

class ForwardList
{
	Element* Head;
	unsigned int size;
	//char* list;
public:
	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		*this = other;
		cout << "LCopyConstructor:" << this << endl;
	}
	ForwardList(ForwardList&& other)noexcept :ForwardList()
	{
		this->size = other.size;
		this->Head = other.Head;
		other.size = 0;
		other.Head = nullptr;
		cout << "LMoveConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		/*while (Head)pop_front();
		pop_back();*/
		//delete[] Head;
		cout << "LDestructor:\t" << this << endl;
	}

	//				Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "LCopyAssignment:" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)noexcept
	{
		if (this == &other)return *this;
		delete[] this->Head;
		this->Head = other.Head;
		this->size = other.size;
		other.size = 0;
		other.Head = nullptr;
		cout << "LMoveAssignment:\t\t" << this << endl;
		return *this;
	}

	//				Adding elements:
	void push_front(int Data)
	{
		////1) Создаем новый элемент:
		//Element* New = new Element(Data);
		////2) Включаем новый элемент в список:
		//New->pNext = Head;
		////3) Переводим Голову на новый элемент:
		//Head = New;

		Head = new Element(Data, Head);
		size++;
	}

	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//1) Доходим до конца списка:
		Element* Temp = Head;
		while (Temp -> pNext)
		{
			Temp = Temp->pNext;
		}

		////2) Создаем новый элемент:
		//Element* New = new Element(Data);
		////3) Включаем новый элемент в список:
		//Temp->pNext = New;

		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int Data, int Index)
	{
		if (Index > Head->count)return;
		if (Index == 0)return push_front(Data);
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;

		/*Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;*/

		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}

	//					Removing elements:
	void pop_front()
	{
		if (Head == nullptr)return;
		Element* erased = Head;	//1)Запоминаем адрес удаляемого элемента
		Head = Head->pNext;		//2)Смещаем Голову на следующий элемент
		delete erased;			//3)Удаляем элемент из памяти
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr||Head->pNext == nullptr)return pop_front();

		//1)Доходим до предпоследнего элемента списка
		Element* Temp = Head;
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
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;

		//2) Запоминаем адрес удаляемого элемента:
		Element* erased = Temp->pNext;

		//3) Исключаем удаляемый элемент из списка:
		Temp->pNext = Temp->pNext->pNext;

		//4) Удаляем элемент из памяти:
		delete erased;
		size--;
	}

	//					Methods:
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
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;;
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов списка: " << Element::count << endl;
		//cout << "Общее количество элементов списка: " << Head->count << endl;
	}
};

//#define BASE_CHECK
//#define COUNT_CHECK
#define LIST_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	//Element element(5);
	int n;
	cout << "введите количество элементов: "; cin >> n;
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
	//ForwardList list2 = list;				//CopyConstructor
	//ForwardList list2;
	//list2 = list;
	ForwardList list2 = std::move(list);	//MoveConstructor
	list2.print();

#endif // LIST_CHECK
}