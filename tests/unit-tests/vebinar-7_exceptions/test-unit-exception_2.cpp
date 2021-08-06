#include "tests/test-common.hpp"

// clang-format off
struct A
{
	A()
	{
		std::cout << "\nA()";
		throw -101i32;
	}
};

struct B : A
{
	B() try : A{}
	{
		std::cout << "\nB()";
	}
	catch(...)
	{
		std::cout << "\ncatch B()";
	}
};
// clang-format on

TEST(Exceptions2, Test1) {
    try {
        B();
    } catch (...) {
        std::cout << "\nTEST(Exceptions, Test1)";
    }
}