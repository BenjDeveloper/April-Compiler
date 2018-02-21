#include <iostream>

class A;

class B
{
	public:
	public:
		B(){}
		void ver_Dato(A* a);
};

class A
{
	private:
		int dato;
	
	public:
		A(int dato): dato(dato) {}
		~A() {}
		int get_Dato() const { return dato; }
		friend void B::ver_Dato(A*);
};

void B::ver_Dato(A* a)
{ 
	std::cout << "a: " << a->dato << std::endl; 
}

int main()
{
	A* a = new A{5};
	std::cout << "a: " << a->get_Dato() << std::endl;
	B* b = new B{};
	b->ver_Dato(a);
	delete a;
	delete b;
}
