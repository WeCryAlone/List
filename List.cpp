﻿#include <iostream>

using namespace std;

#define tab "\t"
#define DEBUG

class List
{
	class Element
	{
		int Data; // Значение элемента
		Element* pNext; // Указатель на некст элемент
		Element* pPrev; // Указатель на пред элемент
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) // :Data(Data), pNext(pNext), pPrev(pPrev)
		{
			this->Data = Data;
			this->pNext = pNext;
			this->pPrev = pPrev;
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
	};
	Element* Head; // Указатель на начальный элем списка
	Element* Tail; // На конечный
	unsigned int size; // Размер списка
public:
	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp = nullptr) :Temp(Temp)
		{
#ifdef DEBUG
			cout << "ITConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~Iterator()
		{
#ifdef DEBUG
			cout << "ITDestructor:\t" << this << endl;
#endif // DEBUG

		}

		Iterator& operator++() // Prefix increment
		{
			Temp = Temp->pNext;
			return *this;
		}
		Iterator operator++(int)
		{
			Iterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		bool operator==(const Iterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const Iterator& other)const
		{
			return this->Temp != other.Temp;
		}

		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	size_t getSize()const
	{
		return size;
	}
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	List()
	{
		Head = Tail = nullptr;
		size = 0;
#ifdef DEBUG
		cout << "LConstructor:\t" << this << endl;
#endif // DEBUG

	}
	explicit List(int size) :List()
	{
		while (size--)push_back(0);
	}
	List(const initializer_list<int>& il) :List()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
			push_back(*it);
	}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
#ifdef DEBUG
		cout << "LDestructor:\t" << this << endl;
#endif // DEBUG

	}

	//			Operators

	int& operator[](size_t index)
	{
		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (size_t i = 0; i < index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (size_t i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;
		}
		return Temp->Data;
	}

	//			Adding elements

	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data); 
			size++;
			return;
		}

		//Element* New = new Element(Data);
		//New->pNext = Head;
		///*New->pNext->*/Head->pPrev = New;
		//Head = New;
		//size++;
		Head = Head->pPrev = new Element(Data, Head);
		size++;
	}

	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		/*Element* New = new Element(Data);
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;*/
		Tail = Tail->pNext = new Element(Data, nullptr ,Tail);
		size++;
	}

	void insert(unsigned int Index, int Data)
	{
		if (Index > size)return;
		if (Index == 0)
		{
			push_front(Data);
			return;
		}
		if (Index == size)
		{
			push_back(Data);
			return;
		}
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (size_t i = 0; i < Index; i++)Temp = Temp->pNext;

		}
		else
		{
			Temp = Tail;
			for (size_t i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
		}
		/*Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;*/
		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
		size++;
	}

	//			Erasing elements

	void pop_front()
	{
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			size--;
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
		size--;
	}

	void pop_back()
	{
		if (Head == Tail)
		{
			delete Tail;
			Head = Tail = nullptr;
			size--;
			return;
		}
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}

	void erase(int index)
	{
		if (index == 0)
		{
			pop_front();
			return;
		}
		if (index == size - 1)
		{
			pop_back();
			return;
		}
		if (index >= size)return;
		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (size_t i = 0; i < index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (size_t i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;
		}
		Temp->pPrev->pNext = Temp->pNext; // В указатель pNext элемента Temp->pPrev записываем адрес элемента Temp->pNext
		Temp->pNext->pPrev = Temp->pPrev; // В указатель pPrev элемента Temp->pNext записываем адрес элемента Temp->pPrev
		delete Temp; // Удаляем элемент из памяти
	}

	//			methods

	void print()
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp << tab;
			cout << Temp->pPrev << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Кол-во элементов списка: " << size << endl;
	}

	void print_reverse()
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		{
			cout << Temp << tab;
			cout << Temp->pPrev << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Кол-во элементов списка: " << size << endl;
	}
};

//#define BaseCheck
//#define SizeConstructor

int main()
{
	setlocale(LC_ALL, "Russian");
	system("color 0A");

	int n;
	cout << "Введите размер списка: "; cin >> n;

#ifdef SizeConstructor
	List list(n);
	for (size_t i = 0; i < list.getSize(); i++)list[i] = rand() % 100;
	for (size_t i = 0; i < list.getSize(); i++)cout << list[i] << tab;
	cout << endl;
	list.print();
#endif // SizeConstructor


#ifdef BaseCheck
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	cout << endl << endl;
	list.pop_front();
	list.print();
	cout << endl << endl;
	list.pop_back();
	list.print();
	cout << endl << endl;
	int index;
	int value;
	cout << "Индекс: "; cin >> index;
	cout << "Добавить: "; cin >> value;
	list.insert(index, value);
	list.print();
	list.print_reverse();
	cout << "Индекс удаляемого: "; cin >> index;
	list.erase(index);
	list.print();
#endif // BaseCheck

	List list = { 3, 5, 8, 13, 21 };
	list.print();
	for (int i : list)
		cout << i << tab;
	cout << endl;

	for (List::Iterator it = list.begin(); it != list.end(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;
}
