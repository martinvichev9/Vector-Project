#ifndef VECTOR_HPP
#define VECTOR_HPP

#define MAX_SIZE 1073741823
//The minimum capacity for an empty vector
#define MIN_CAPACITY 2

#include <cassert>

template<class T>
class Vector
{
private:

	void move(Vector&&);
	void copy(const Vector&);
	void del();
	void capacity_increment();

	T* buffer;
	unsigned current_size;
	unsigned current_capacity;

public:

	Vector();
	Vector(unsigned, const T&);
	Vector(const Vector&);
	Vector& operator=(const Vector&);
	~Vector();
	Vector(Vector&&);
	Vector& operator=(Vector&&);

	void push_back(const T&);
	void pop_back();
	void clear();

	bool empty()const;
	unsigned size()const;
	unsigned capacity()const;

	T& operator[](unsigned ind) const;
	T& operator[](unsigned ind);
	T& back() const;
	T& back();

	void resize(unsigned);
	void resize(unsigned, const T&);

	template<class M>
	friend std::ostream& operator<<(std::ostream&, const Vector<M>&);

	T& at(unsigned) const;
	T& at(unsigned);
	T& front() const;
	T& front();
	void insert(unsigned, const T&);
	void swap(Vector&);

	template<class M>
	friend bool operator==(const Vector<M>&, const Vector<M>&);

	template<class M>
	friend bool operator!=(const Vector<M>&, const Vector<M>&);

	template<class M>
	friend bool operator<(const Vector<M>&, const Vector<M>&);

	template<class M>
	friend bool operator>(const Vector<M>&, const Vector<M>&);

	template<class M>
	friend bool operator<=(const Vector<M>&, const Vector<M>&);

	template<class M>
	friend bool operator>=(const Vector<M>&, const Vector<M>&);

	//Class ReverseIterator that iterates through the elements of the
	//vector in a reverse order
	class ReverseIterator
	{
	public:

		ReverseIterator(T* _ptr)
		{
			ptr = _ptr;
		}

		//Prefix operator ++ that increments ptr by 1
		ReverseIterator& operator++()
		{
			ptr -= 1;
			return *this;
		}

		//Postfix operator ++ that increments ptr by 1
		ReverseIterator operator++(int)
		{
			ReverseIterator rit = *this;
			ptr -= 1;
			return rit;
		}

		//Returns the value of the node that ptr is pointing to and cannot
		//be modified
		T& operator*() const
		{
			return *ptr;
		}

		//Returns the value of the node that ptr is pointing to and can be
		//modified
		T& operator*()
		{
			return *ptr;
		}

		bool operator!=(const ReverseIterator& other) const
		{
			return ptr != other.ptr;
		}

		bool operator==(const ReverseIterator& other) const
		{
			return !(ptr != other.ptr);
		}

	private:
		T* ptr;
	};

	//Random-access Iterator
	class Iterator
	{
	public:

		Iterator(T* _ptr)
		{
			ptr = _ptr;
		}

		//Returns the value of the node that the ptr points to and cannot be
		//modified
		T& operator*() const
		{
			return *ptr;
		}
		//Returns the value of the node that the ptr points to and can be
		//modified
		T& operator*()
		{
			return *ptr;
		}

		//Prefix ++ and -- increments or decrements ptr by 1
		Iterator& operator++()
		{
			ptr += 1;
			return *this;
		}
		Iterator& operator--()
		{
			ptr -= 1;
			return *this;
		}

		//Postfix ++ and -- increments or decrements ptr by 1
		Iterator operator++(int)
		{
			Iterator copy = *this;
			ptr += 1;
			return copy;
		}
		Iterator operator--(int)
		{
			Iterator copy = *this;
			ptr -= 1;
			return copy;
		}

		bool operator!=(const Iterator& other)const
		{
			return ptr != other.ptr;
		}

		bool operator==(const Iterator& other)const
		{
			return !(ptr != other.ptr);
		}

		//Returns true if ptr points to smaller address
		bool operator<(const Iterator& other)const
		{
			return ptr < other.ptr;
		}

		bool operator>(const Iterator& other)const
		{
			return ptr > other.ptr;
		}

		Iterator operator+(unsigned num)
		{
			Iterator res(ptr + num);
			return res;
		}

		Iterator operator-(unsigned num)
		{
			Iterator res(ptr - num);
			return res;
		}

		Iterator& operator+=(unsigned num)
		{
			ptr += num;
			return *this;
		}

		Iterator& operator-=(unsigned num)
		{
			ptr -= num;
			return *this;
		}

	private:
		T* ptr;
	};

	Iterator begin() const;
	Iterator end() const;
	ReverseIterator rbegin() const;
	ReverseIterator rend() const;

};


template<class T>
Vector<T>::Vector()
	: current_size(0), current_capacity(MIN_CAPACITY), buffer(nullptr)
{
	buffer = new T[current_capacity];
}

template<class T>
Vector<T>::Vector(unsigned _size, const T& _elem)
	: current_size(_size), current_capacity(_size)
{
	buffer = new T[current_size];
	for (int i = 0; i < current_size; ++i)
	{
		buffer[i] = _elem;
		//push_back(_elem);
	}
}

//Allocates new amount of memory when possible
template<class T>
void Vector<T>::capacity_increment()
{
	if (current_capacity * 2 < MAX_SIZE)
	{
		current_capacity *= 2;
		T* toCopy = new T[current_capacity];
		for (int i = 0; i < size(); ++i)
		{
			toCopy[i] = buffer[i];
		}
		delete[] buffer;
		buffer = toCopy;
	}

	else
		std::cerr << "No more available capacity!!!\n";
}

template<class T>
void Vector<T>::del()
{
	delete[] buffer;
}

//Copies the content of other to the content of the "our" vector  
template<class T>
void Vector<T>::copy(const Vector<T>& other)
{
	buffer = new T[other.size()];
	current_size = other.current_size;
	current_capacity = other.current_capacity;
	for (int i = 0; i < current_size; ++i)
	{
		buffer[i] = other.buffer[i];
	}
}

//Moves the other's content to the "our" vector and sets defaul
//values to all other's data members
template<class T>
void Vector<T>::move(Vector<T>&& other)
{
	buffer = other.buffer;
	current_size = other.size;
	current_capacity = other.capacity;
	other.buffer = nullptr;
	other.capacity = 0;
	other.size = 0;
}

//The rule of five(copy constructor, copy assignment operator, destructor
//move constructor and move assignment operator)
template<class T>
Vector<T>::Vector(const Vector<T>& other)
{
	copy(other);
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this != &other)
	{
		del();
		copy(other);
	}
	return *this;
}

template<class T>
Vector<T>::~Vector()
{
	del();
}

template<class T>
Vector<T>::Vector(Vector<T>&& other)
{
	move(other);
}

template<class T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other)
{
	if (this != &other)
	{
		delete[] buffer;
		move(other);
	}
	return *this;
}

template<class T>
bool Vector<T>::empty() const
{
	return current_size == 0;
}

template<class T>
unsigned Vector<T>::size() const
{
	return current_size;
}

template<class T>
unsigned Vector<T>::capacity() const
{
	return current_capacity;
}

template<class T>
void Vector<T>::push_back(const T& elem)
{
	if (current_size == MAX_SIZE)
	{
		std::cerr << "No more space available for adding new element!!\n";
		return;
	}

	if (current_size == current_capacity)
		capacity_increment();

	buffer[current_size] = elem;
	++current_size;
}

template<class T>
T& Vector<T>::operator[](unsigned ind)
{
	assert(ind < current_size);
	return buffer[ind];
}

template<class T>
T& Vector<T>::operator[](unsigned ind) const
{
	assert(ind < current_size);
	return buffer[ind];
}

template<class T>
T& Vector<T>::back() const
{
	assert(!empty());
	return buffer[size() - 1];
}

template<class T>
T& Vector<T>::back()
{
	assert(!empty());
	return buffer[size() - 1];
}

template<class T>
void Vector<T>::clear()
{
	delete[] buffer;
	buffer = nullptr;
	current_size = 0;
}

template<class T>
T& Vector<T>::at(unsigned ind) const
{
	assert(!empty());
	return buffer[ind - 1];
}

template<class T>
T& Vector<T>::at(unsigned ind)
{
	assert(!empty());
	return buffer[ind - 1];
}

template<class T>
T& Vector<T>::front() const
{
	assert(!empty());
	return buffer[0];
}

template<class T>
T& Vector<T>::front()
{
	assert(!empty());
	return buffer[0];
}

template<class T>
void Vector<T>::insert(unsigned ind, const T& elem)
{
	assert(ind <= size());
	if (size() == ind)
		push_back(elem);
	else
	{
		++current_size;
		if (current_size >= current_capacity)
			capacity_increment();
		T* toCopy = new T[current_size];
		for (int i = 0; i < ind; ++i)
		{
			toCopy[i] = buffer[i];
		}
		toCopy[ind] = elem;
		for (int i = ind + 1; i < current_size; ++i)
		{
			toCopy[i] = buffer[i - 1];
		}
		delete[] buffer;
		buffer = toCopy;
	}
}

template<class T>
void Vector<T>::pop_back()
{
	if (!empty())
		--current_size;
}

//Resizes the vector so that its size is now equal to newSize. If newSize is less
//than the old one, removes elements at positions equal or greater than the newSize.
//Else, adds default values to fill the vector.
template<class T>
void Vector<T>::resize(unsigned newSize)
{
	int vector_size = current_size;
	if (newSize < current_size)
	{
		for (int i = newSize; i < vector_size; ++i)
		{
			pop_back();
		}
	}
	else
	{
		for (int i = vector_size; i < newSize; ++i)
		{
			push_back(T());
		}
	}
}

//Resizes the vector and if the new size is greater than the old one
//inserts 'elem' at the end to fill the new vector. Else, removes the "extra" elements.
template<class T>
void Vector<T>::resize(unsigned newSize, const T& elem)
{
	if (newSize < current_size)
		resize(newSize);
	else
	{
		for (int i = current_size; i < newSize; ++i)
		{
			push_back(elem);
		}
	}
}

template<class T>
void Vector<T>::swap(Vector<T>& other)
{
	Vector<T> copy = *this;
	*this = other;
	other = copy;

}

//Overloaded operator<< with some "extra" details(size,capacity...)
template<class T>
std::ostream& operator<<(std::ostream& out, const Vector<T>& vec)
{
	out << "Size: " << vec.size() << std::endl;
	out << "Capacity: " << vec.capacity() << std::endl;
	out << "Vector contains: ";
	for (int i = 0; i < vec.size(); ++i)
	{
		out << vec[i] << " ";
	}
	out << std::endl;
	return out;
}

template<class T>
bool operator==(const Vector<T>& left, const Vector<T>& right)
{
	if (left.size() != right.size())
		return false;
	for (int i = 0; i < left.size(); ++i)
	{
		if (left[i] != right[i])
			return false;
	}
	return true;
}

template<class T>
bool operator!=(const Vector<T>& left, const Vector<T>& right)
{
	return !(left == right);
}

template<class T>
bool operator<(const Vector<T>& left, const Vector<T>& right)
{
	unsigned count = 0;
	while (count < left.size() && count < right.size())
	{
		if (left[count] > right[count])
			return false;
		if (left[count] < right[count])
			return true;
		++count;
	}
	if (count == right.size())
		return false;
	else
		return true;
}

template<class T>
bool operator>(const Vector<T>& left, const Vector<T>& right)
{
	return !(left < right) && left != right;
}

template<class T>
bool operator<=(const Vector<T>& left, const Vector<T>& right)
{
	return !(left > right);
}

template<class T>
bool operator>=(const Vector<T>& left, const Vector<T>& right)
{
	return !(left < right);
}

//Returns an Iterator pointing to the first element of the vector
template<class T>
typename Vector<T>::Iterator Vector<T>::begin() const
{
	return Iterator(buffer);
}

//Returns an Iterator pointing to the last element of the vector
template<class T>
typename Vector<T>::Iterator Vector<T>::end() const
{
	return Iterator(buffer + size());
}

//Returns a ReverseIterator pointing to the last element of the vector
template<class T>
typename Vector<T>::ReverseIterator Vector<T>::rbegin() const
{
	return ReverseIterator(buffer + size() - 1);
}

//Returns a ReverseIterator pointing to the first element before the vector's one
template<class T>
typename Vector<T>::ReverseIterator Vector<T>::rend() const
{
	return ReverseIterator(buffer - 1);
}

#endif // !VECTOR_HPP