#pragma once
#include "stdafx.h"
#include <iostream>

template <typename T>
class MyTable
{
public:
	MyTable();
	~MyTable();

	void remove_by_index(int index); // Removes element at indeks 
	void remove_by_value(T value); // Removes  all elements with given value
	void remove_last(); // Removes last element
	void insert(int index, T value); // Inserts value at given position increasing weight
	void insert_at(int index, T value);

	void push_back(T value); // Insert value on back of the table
	void push_front(T value); // Insert value on front of the table
	void print_me(); // displays all values 

	T get_by_index(int index); // Get element at index
	int get_size() const; // Get weight

	bool find_value(T v);

	void sort(bool(*cmp)(T &, T &), int start, int end);

	T* get_tab();

	void reverse(int start, int end);

	void permutate(int start, int end);

	void swap(int i, int j);



private:
	int size;
	T *tab;
};

template<typename T>
MyTable<T>::MyTable()
{
	this->tab = new T[0];
	this->size = 0;
}


template<typename T>
MyTable<T>::~MyTable()
{
	delete[] tab;
}

template <typename T>
T* MyTable<T>::get_tab()
{
	return this->tab;
}

template <typename T>
void MyTable<T>::reverse(int start, int end)
{
	while(start < end)
	{
		swap(start, end);
		start++;
		end--;
	}
}

template <typename T>
void MyTable<T>::permutate(int l, int r)
{
	int i;
	if (l == r)
		print_me();
	else
	{
		for (i = l; i <= r; i++)
		{
			swap(l, i);
			permutate(l + 1, r);
			swap(l,  i); //backtrack
		}
	}
}

template <typename T>
void MyTable<T>::swap(int i, int j)
{
	T temp = tab[i];
	tab[i] = tab[j];
	tab[j] = temp;
}


template<typename T>
void MyTable<T>::remove_by_index(int index)
{
	if (index >= size) return;

	T *tempTab = new T[size];
	for (int i = 0, j = 0; i <= size; ++i, ++j) {
		if (index == i) { // skip value at index
			j--;
			continue;
		}

		tempTab[j] = tab[i];
	}

	delete[] tab;

	tab = tempTab;
	size--;
}

template<typename T>
void MyTable<T>::remove_by_value(T value)
{
	int *tempTab = new int[size - 1];
	int j = 0;
	for (int i = 0; i <= size; ++i, ++j) {
		if (this->tab[i] == value) { // skip value
			j--;
			continue;
		}

		tempTab[j] = tab[i];
	}

	delete[] tab;

	tab = tempTab;
	size = j;
}

template<typename T>
void MyTable<T>::remove_last()
{
	remove_by_index(size - 1);
}

template<typename T>
void MyTable<T>::insert(int index, T value)
{
	if (index > size)
	{
		push_back(value);
		return;
	}

	T* tempTab = new T[size + 2];
	for (int i = 0, j = 0; i < size + 1; ++i, ++j) {
		if (index == i) {
			tempTab[j] = value;
			j++;
		}

		tempTab[j] = tab[i];
	}

	delete[] tab;

	tab = tempTab;
	size++;
}

template <typename T>
void MyTable<T>::insert_at(int index, T value)
{
	tab[index] = value;
}

template<typename T>
void MyTable<T>::push_back(T value)
{
	this->insert(size, value);
}
template<typename T>
void MyTable<T>::push_front(T value)
{
	this->insert(0, value);
}

template<typename T>
void MyTable<T>::print_me()
{
	for (int i = 0; i < size; i++)
		std::cout << this->tab[i] << " ";

	std::cout << std::endl;
}

template<typename T>
T MyTable<T>::get_by_index(int index)
{
	return tab[index];
}

template<typename T>
int MyTable<T>::get_size() const
{
	return size;
}

template<typename T>
bool MyTable<T>::find_value(T v)
{
	for (int i = 0; i < size; i++)
		if (tab[i] == v)
			return true;

	return false;
}

template<typename T>
int partition(bool(*cmp)(T &, T &), T tablica[], int p, int r) // dzielimy tablice na dwie czesci, w pierwszej wszystkie liczby sa mniejsze badz rowne x, w drugiej wieksze lub rowne od x
{
	T x = tablica[p]; // obieramy x
	int i = p, j = r; // i, j - indeksy w tabeli
	T w;
	while (true) // petla nieskonczona - wychodzimy z niej tylko przez return j
	{
		while (cmp(tablica[j], x)) // dopoki elementy sa wieksze od x
			j--;
		while (cmp(x, tablica[i])) // dopoki elementy sa mniejsze od x
			i++;
		if (i < j) // zamieniamy miejscami gdy i < j
		{
			w = tablica[i];
			tablica[i] = tablica[j];
			tablica[j] = w;
			i++;
			j--;
		}
		else // gdy i >= j zwracamy j jako punkt podzialu tablicy
			return j;
	}
}

template<typename T>
void quicksort(bool(*cmp)(T &, T &), T tablica[], int p, int r) // sortowanie szybkie
{
	int q;
	if (p < r)
	{
		q = partition(cmp, tablica, p, r); // dzielimy tablice na dwie czesci; q oznacza punkt podzialu
		quicksort(cmp, tablica, p, q); // wywolujemy rekurencyjnie quicksort dla pierwszej czesci tablicy
		quicksort(cmp, tablica, q + 1, r); // wywolujemy rekurencyjnie quicksort dla drugiej czesci tablicy
	}
}

template <typename T>
void MyTable<T>::sort(bool(*cmp)(T &, T &), int start, int end)
{
	quicksort(cmp, this->tab, start, end);
}