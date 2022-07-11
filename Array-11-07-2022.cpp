// Array-11-07-2022.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Добавить коментарии 
// 2. Применение перемещения при перегрузке оператора присваивания урок 4 стр 30

#include <iostream>
using namespace std;

class DynArray
{
	int* arr;
	int size;

public:
	DynArray(int sizeP)
		: arr{ new int[sizeP] {} }, size{ sizeP }
	{
		cout << "DynArr constructed for " << size
			<< " elements, for " << this << '\n';
	}
	DynArray() : DynArray(5) {}
	DynArray(const DynArray& object)
		: arr{ new int[object.size] }, size{ object.size }
	{
		for (int i{ 0 }; i < size; ++i)
		{
			arr[i] = object.arr[i];
		};
		cout << "DynArr copy constructed for "
			<< size << " elements, for " << this
			<< '\n';
	}
	DynArray(DynArray&& object)
		: arr{ object.arr }, size{ object.size }
	{
		object.arr = nullptr;
		object.size = 0;
		cout << "DynArr move constructed for "
			<< size << " elements, for " << this
			<< '\n';
	}
	DynArray& operator=(const DynArray& object)
	{
		if (!(this == &object))
		{
			if (size != object.size)
			{
				delete arr;
				arr = new int[object.size];
			}
			size = object.size;
			int* dest{ arr };
			int* src{ object.arr };
			int* const end{ arr + size };
			while (dest < end)
			{
				*dest++ = *src++;
			}
		}
		cout << "DynArr copy assigned for "
			<< size << " elements, for " << this
			<< '\n';
		return *this;
	}
	DynArray& operator=(DynArray&& object)
	{
		if (!(this == &object))
		{
			delete arr;
			arr = object.arr;
			size = object.size;
			object.arr = nullptr;
			object.size = 0;
		}
		cout << "DynArr move assigned for "
			<< size << " elements, for " << this
			<< '\n';
		return *this;
	}
	int getElem(int idx)const { return arr[idx]; }
	void setElem(int idx, int val) { arr[idx] = val; }
	void print()const;
	void randomize();
	~DynArray()
	{
		cout << "Try to free memory from DynArray for"
			<< arr << " pointer\n";
		delete[] arr;
		cout << "DynArr destructed for " << size
			<< " elements, for " << this << '\n';
	}
};
void DynArray::print()const
{
	for (int i{ 0 }; i < size; ++i)
	{
		cout << arr[i] << ' ';
	}
	cout << '\n';
}
void DynArray::randomize()
{
	for (int i{ 0 }; i < size; ++i)
	{
		arr[i] = rand() % 10;
	}
}
DynArray arrayFactory(int arrSize)
{
	DynArray arr{ arrSize };
	arr.randomize();
	return arr;
}
int main()
{
	DynArray ar1{ arrayFactory(10) };
	cout << "ar1 elements: ";
	ar1.print();
	cout << "\nCreate new array for 5 elements.\n\n";
	ar1 = arrayFactory(5);
	cout << "ar1 elements: ";
	ar1.print();
	return 0;
}