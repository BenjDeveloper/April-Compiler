#include <iostream>
#include <list>

int main()
{
	std::list<int> l;

	l.push_front(1);
	l.push_front(2);
	l.push_front(3);

	std::list<int>::iterator it = l.begin();

	while (it != l.end())
	{
		std::cout << *it++ << std::endl;
	}
	l.pop_front();
	std::cout << "---------------" << std::endl;
	it = l.begin();	
	while (it != l.end())
	{
		std::cout << *it++ << std::endl;
	}
	
}
