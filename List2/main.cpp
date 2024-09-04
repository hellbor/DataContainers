#include"List2.h"
#include"List2.cpp"

//#define BASE_CHECK
//#define ITERATORS_CHECK
//#define OPERATORS_CHECK
//#define CONST_ITERATORS_CHECK
#define DOUBLE_CHECK
#define STRING_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите количество элементов:"; cin >> n;
	List<T> list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();
	for (int i = 0; i < 100; i++)list.pop_back();

	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	list.reserve_print();

	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
#endif // BASE_CHECK

#ifdef ITERATORS_CHECK
	List<T> list = { 3,5,8,13,21 };
	/*list.print();
	list.reverse_print();*/
	for (int i : list)cout << i << tab; cout << endl;
	for (List::ConstReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // ITERATORS_CHECK

#ifdef OPERATORS_CHECK
	List list1 = { 3,5,8,13,21 };
	List list2 = { 34,55,89 };
	List list3 = list1 + list2;
	list3.print();
	list3.reverse_print();
	//for (int i : list3)cout << i << tab; cout << endl;  
#endif // OPERATORS_CHECK

#ifdef CONST_ITERATORS_CHECK
	List<int> list1 = { 3,5,8,13,21 };
	List<int> list2 = { 34,55,89 };
	List<int> list3 = list1 + list2;
	/*list3.print();
	list3.reverse_print();*/
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;
	Grow(list3);
	for (int i : list3)cout << i << tab; cout << endl;
#endif // CONST_ITERATORS_CHECK

#ifdef DOUBLE_CHECK
	List<double> d_list1 = { 1.3, 2.1, 3.7 };
	List<double> d_list2 = { 3.4, 5.5, 8.9 };
	List<double> d_list3 = d_list1 + d_list2;
	/*list3.print();
	list3.reverse_print();*/
	for (double i : d_list1)cout << i << tab; cout << endl;
	for (double i : d_list2)cout << i << tab; cout << endl;
	for (double i : d_list3)cout << i << tab; cout << endl;
	/*Grow<double>(list3);
	for (double i : list3)cout << i << tab; cout << endl;*/
#endif // DOUBLE_CHECK
	
#ifdef STRING_CHECK
	List<std::string>s_list1 = { "Hello" };
	List<std::string>s_list2 = { "World" };
	List<std::string>s_list3 = s_list1 + s_list2;
	/*list2.print();
	list2.reverse_print();*/
	for (std::string i : s_list1)cout << i << tab; cout << endl;
	for (std::string i : s_list2)cout << i << tab; cout << endl;
	for (std::string i : s_list3)cout << i << tab; cout << endl;
#endif // STRING_CHECK

}