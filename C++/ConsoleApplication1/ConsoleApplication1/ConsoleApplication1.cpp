// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <memory>

using namespace std;

void foo(shared_ptr<int> x, shared_ptr<int> y)
{
	cout << endl;
	cout << "Used by: " << x.use_count() << endl;
	cout << "The value is: " << *x << endl;
	cout << "Address: " << x << endl;
	x = y;
	cout << "Used by: " << x.use_count() << endl;
	cout << "The value is: " << *x << endl;
}

void foo2(shared_ptr<int> &x, shared_ptr<int> y)
{
	cout << endl;
	cout << "The value is: " << x.use_count() << endl;
	cout << "The value is: " << *x << endl;
	cout << "Address: " << x << endl;
	x = y;
	cout << "The value is: " << x.use_count() << endl;
	cout << "The value is: " << *x << endl;
}


int main()
{
	auto value = make_shared<int>(345345);
	auto testValue = make_shared<int>(20);
	cout << "Used by: " << testValue.use_count() << endl;
	cout << "Address: " << testValue << endl;
	cout << "The value is: " << *testValue << endl;
	foo(testValue, value);
	cout << endl;
	cout << "Used by: " << testValue.use_count() << endl;
	cout << "The value is: " << *testValue << endl;
	foo2(testValue, value);
	cout << endl;
	cout << "Used by: " << testValue.use_count() << endl;
	cout << "The value is: " << *testValue << endl;
	testValue = nullptr;
	cout << "Used by: " << testValue.use_count() << endl;
	//value = nullptr;
	cout << "Used by: " << value.use_count() << endl;

	return 0;
}



