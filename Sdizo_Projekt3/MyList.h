#pragma once
#include <iostream>

template<typename T>
struct MyListNode
{
	T data;
	MyListNode<T> *next;
};

template <typename T>
class MyList {
protected:
	int _size;
	MyListNode<T> *root;
	MyListNode<T> *last;

	MyListNode<T>* getNode(int index);

	static MyListNode<T>* findEndOfSortedString(MyListNode<T> *p, int(*cmp)(T &, T &));

public:
	MyList();
	~MyList();

	/*
	Returns current weight of MyList
	*/
	virtual int get_size();
	/*
	Adds a T object in the specified index;
	Unlink and link the MyList correcly;
	Increment _size
	*/
	virtual bool insert(int index, T);
	/*
	Adds a T object in the end of the MyList;
	Increment _size;
	*/
	virtual bool push_back(T);
	/*
	Adds a T object in the start of the MyList;
	Increment _size;
	*/
	virtual bool push_front(T);
	/*
	Set the object at index, with T;
	Increment _size;
	*/
	virtual bool set(int index, T);
	/*
	Remove object at index;
	If index is not reachable, returns false;
	else, decrement _size
	*/
	virtual T remove(int index);
	/*
	Remove last object;
	*/
	virtual T pop_back();
	/*
	Remove first object;
	*/
	virtual T pop_front();
	/*
	Get the index'th element on the list;
	Return Element if accessible,
	else, return false;
	*/
	virtual T get_by_index(int index);

	/*
	Clear the entire array
	*/
	virtual void clear();

	/*
	Sort the list, given a comparison function
	*/
	virtual void sort(bool(*cmp)(T &, T &));

	static bool ascending_int_comparator(int& x, int& y);
};

// Initialize MyList with false values
template<typename T>
MyList<T>::MyList()
{
	root = nullptr;
	last = nullptr;
	_size = 0;
}

// Clear Nodes and free Memory
template<typename T>
MyList<T>::~MyList()
{

	MyListNode<T>* tmp;
	while (root != nullptr)
	{
		tmp = root;
		root = root->next;
		delete tmp;
	}
	last = nullptr;
	_size = 0;
}

/*
Actualy "logic" coding
*/

template<typename T>
MyListNode<T>* MyList<T>::getNode(int index) {

	int _pos = 0;
	MyListNode<T>* current = root;



	while (_pos < index && current) {
		current = current->next;

		_pos++;
	}

	// Check if the object index got is the same as the required
	if (_pos == index) {
		return current;
	}

	return nullptr;
}

template<typename T>
int MyList<T>::get_size() {
	return _size;
}

template<typename T>
bool MyList<T>::insert(int index, T _t) {

	if (index >= _size)
		return push_back(_t);

	if (index == 0)
		return push_front(_t);

	MyListNode<T> *tmp = new MyListNode<T>(),
		*_prev = getNode(index - 1);
	tmp->data = _t;
	tmp->next = _prev->next;
	_prev->next = tmp;

	_size++;

	return true;
}

template<typename T>
bool MyList<T>::push_back(T _t) {

	MyListNode<T> *tmp = new MyListNode<T>();
	tmp->data = _t;
	tmp->next = nullptr;

	if (root) {
		// Already have elements inserted
		last->next = tmp;
		last = tmp;
	}
	else {
		// First element being inserted
		root = tmp;
		last = tmp;
	}

	_size++;

	return true;
}

template<typename T>
bool MyList<T>::push_front(T _t) {

	if (_size == 0)
		return push_back(_t);

	MyListNode<T> *tmp = new MyListNode<T>();
	tmp->next = root;
	tmp->data = _t;
	root = tmp;

	_size++;

	return true;
}

template<typename T>
bool MyList<T>::set(int index, T _t) {
	// Check if index position is in bounds
	if (index < 0 || index >= _size)
		return false;

	getNode(index)->data = _t;
	return true;
}

template<typename T>
T MyList<T>::pop_back() {
	if (_size <= 0)
		return T();


	if (_size >= 2) {
		MyListNode<T> *tmp = getNode(_size - 2);
		T ret = tmp->next->data;
		delete(tmp->next);
		tmp->next = nullptr;
		last = tmp;
		_size--;
		return ret;
	}
	else {
		// Only one element left on the list
		T ret = root->data;
		delete(root);
		root = nullptr;
		last = nullptr;
		_size = 0;
		return ret;
	}
}

template<typename T>
T MyList<T>::pop_front() {
	if (_size <= 0)
		return T();

	if (_size > 1) {
		MyListNode<T> *_next = root->next;
		T ret = root->data;
		delete(root);
		root = _next;
		_size--;

		return ret;
	}
	else {
		// Only one left, then pop_back()
		return pop_back();
	}

}

template<typename T>
T MyList<T>::remove(int index) {
	if (index < 0 || index >= _size)
	{
		return T();
	}

	if (index == 0)
		return pop_front();

	if (index == _size - 1)
	{
		return pop_back();
	}

	MyListNode<T> *tmp = getNode(index - 1);
	MyListNode<T> *toDelete = tmp->next;
	T ret = toDelete->data;
	tmp->next = tmp->next->next;
	delete(toDelete);
	_size--;
	return ret;
}


template<typename T>
T MyList<T>::get_by_index(int index) {
	MyListNode<T> *tmp = getNode(index);

	return (tmp ? tmp->data : T());
}

template<typename T>
void MyList<T>::clear() {
	while (get_size() > 0)
		pop_front();
}


template<typename T>
int partition(bool(*cmp)(T &, T &), T *tablica, int p, int r) // dzielimy tablice na dwie czesci, w pierwszej wszystkie liczby sa mniejsze badz rowne x, w drugiej wieksze lub rowne od x
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
void quicksort(bool(*cmp)(T &, T &), T*tablica, int p, int r) // sortowanie szybkie
{
	int q;
	if (p < r)
	{
		q = partition(cmp, tablica, p, r); // dzielimy tablice na dwie czesci; q oznacza punkt podzialu
		quicksort(cmp, tablica, p, q); // wywolujemy rekurencyjnie quicksort dla pierwszej czesci tablicy
		quicksort(cmp, tablica, q + 1, r); // wywolujemy rekurencyjnie quicksort dla drugiej czesci tablicy
	}
}

template<typename T>
void MyList<T>::sort(bool(*cmp)(T &, T &)) {
	int tab_size = this->get_size();
	T *tab = new T[tab_size];
	int i = 0;
	MyListNode<T> *p = this->root;
	while (p)
	{
		tab[i] = p->data;
		p = p->next;
		i++;
	}

	quicksort(cmp, tab, 0, this->get_size() - 1);

	this->clear();

	for (int i = 0; i < tab_size; i++)
	{
		this->push_back(tab[i]);
	}

	delete[] tab;
}

template <typename T>
bool MyList<T>::ascending_int_comparator(int& x, int& y)
{
	return x > y;
}

template<typename T>
MyListNode<T>* MyList<T>::findEndOfSortedString(MyListNode<T> *p, int(*cmp)(T &, T &)) {
	while (p->next && cmp(p->data, p->next->data) <= 0) {
		p = p->next;
	}

	return p;
}
