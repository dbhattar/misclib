#include <iostream>

template<typename Derived>
class GenericAbstraction
{
public:
	Derived * clone() const {
		const Derived *d = static_cast<const Derived *>(this);
		return new Derived(*d);
	}
};

class Base
{
public:
	virtual void display() = 0;
	virtual ~Base () = 0 {
	}
};

class DerivedType : public Base, public GenericAbstraction<DerivedType> {
public:
	virtual void display() {
		std::cout << "This is DerivedType." << std::endl;
	}
};

class DerivedType2: public Base, public GenericAbstraction<DerivedType2>  {
public:
	virtual void display() {
		std::cout << "This is DerivedType2." << std::endl;
	}
};

int main() {
	DerivedType d1;
	d1.display();
	DerivedType *dc = d1.clone();
	dc->display();
	DerivedType2 d2;
	d2.display();
	DerivedType2 *d2c = d2.clone();
	d2c->display();
	return 0;
}
