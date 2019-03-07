#ifndef TESTS_HPP
#define TESTS_HPP

#include "Vector.hpp"
#include <cassert>
#include <iostream>

void test_operators()
{
	Vector<int> v1;
	v1.push_back(2);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	
	Vector<int> v;
	v.push_back(2);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	

	std::cout << ((v == v1) ? "Equals" : "Not equals") << std::endl;
	std::cout << ((v <= v1) ? "'v' is less or equal than 'v1'" : "'v' is greater than 'v1'") << std::endl;
	std::cout << ((v >= v1) ? "'v' is equals or greater than 'v1'" : "'v' is less than 'v1'") << std::endl;
	std::cout << ((v < v1) ? "'v' is less than 'v1'" : "'v' is not less than 'v1'") << std::endl;
	std::cout << ((v > v1) ? "'v1' is less than 'v'" : "'v1' is not less than 'v'") << std::endl;
	std::cout << ((v != v1) ? "Not equals"  : "Equals") << std::endl;
}

void test_thousand_elements()
{
	Vector<int> v;
	for (int i = 0; i < 1000; ++i)
	{
		v.push_back(i);
	}
	std::cout << "Vector's size: " << v.size() << std::endl;
	std::cout << "Vector's allocated capacity: " << v.capacity() << std::endl;
	std::cout << "Vector's first element(with front()): " << v.front() << std::endl;
	std::cout << "Vector's first element(with operator[]): " << v[0] << std::endl;
	std::cout << "Vector's 35 element: " << v[35] << std::endl;
	std::cout << "Vector's 35 element(with at()): " << v.at(35) << std::endl;
	std::cout << "Vector's last element(with operator[]): " << v[999] << std::endl;
	std::cout << "Vector's last element(with back()): " << v.back() << std::endl;


	v.pop_back();
	std::cout << "After popping, the last elements is " << v.back() << std::endl;

	//prints all 1000 elements
	/*for(Vector<int>::Iterator it=v.begin();it!=v.end();++it)
	{
	std::cout<<(*it)<<std::endl;
	}*/
}

//All insert operations (insert, push_back)
void test_insert_elements()
{

	Vector<int> v1;
	
	assert(v1.empty());

	v1.push_back(1);
	v1.push_back(3);
	v1.push_back(4);

	assert(v1.size() == 3);
	assert(v1.capacity() == 4);

	v1.insert(0, 9);
	assert(v1[0] != 1);
	assert(v1[0] == 9);


}

void test_pop_back()
{
	Vector<int> v1;

	v1.pop_back();
	v1.push_back(1);
	v1.push_back(2);

	v1.pop_back();
	assert(v1.size() == 1);
	v1.pop_back();
	assert(v1.empty());
}

void test_resize()
{
	Vector<int> v(5, 9);
	assert(v.size() == 5);

	v.resize(2);
	assert(v.size() == 2);

	v.resize(4, 7);
	assert(v.size() == 4);
	assert(v[2] == 7 && v[3] == 7);
	assert(v[1] == 9 && v[0] == 9);

}

void test_iterators()
{
	int count = 0;

	Vector<int> v(10, 9);
	for (Vector<int>::Iterator it = v.begin(); it != v.end(); ++it)
	{
		assert((*it) == 9);
		++count;
	}
	
	assert(count == 10);

	for (Vector<int>::ReverseIterator rit = v.rbegin(); rit != v.rend(); ++rit)
	{
		assert((*rit) == 9);
		++count;
	}
	
	assert(count == 20);
}

void test_getters()
{
	Vector<int> v(5, 9);
	
	assert(v.at(3) == 9);
	v.at(3) = 10;
	assert(v.at(3) != 9);
	assert(v.at(3) == 10);
	
	assert(v.front() == 9);
	v.front() = 10;
	assert(v.front() == 10);
	
	assert(v.back() == 9);
	v.back() = 10;
	assert(v.back() == 10);

	assert(v[1] == 9);
	v[1] = 10;
	assert(v[1] == 10);

}

void start_tests() 
{
	//test_operators();
	//test_thousand_elements();
	test_insert_elements();
	test_pop_back();
	test_resize();
	test_iterators();
	test_getters();
}



#endif // !TESTS_HPP