#include <iostream>
#include "Animal.h"
#include "Dog.h"
#include <memory>

using namespace cpp_primer::ch07;

int main(int argc, char const *argv[])
{
	Animal a;
	a.SetName("Aea");
	a.Say();
 
	Dog d;
	d.SetName("Doo");
	d.Say();

	Animal* p1 = new Dog();
	p1->SetName("p1");
	p1->Say();

	std::shared_ptr<Animal> p2 = std::make_shared<Dog>();
	p2->Say();
	p2.reset(new Animal());
	p2->Say();

	//
	Animal a2;
	a2.Say2().SetName2("a2").Say2();

	Dog d2;
	d2.Say2().SetName2("d2").Say2();

	const Animal a3("a3");
	a3.TestConst();

	Animal a4("a4");
	a4.TestConst();

	return 0;
}
