#include "tests/test-common.hpp"

void F1() {
    throw -101i32; // type is int32_t
}

void F2() {
    throw 'a'; // type is char
}

void F3() {
    throw 3.14; // type is double
}

void F4() {
    throw 3.14f; // type is double
}

void F5() {
    throw []() {
        std::cout << "[]() -> void {}";
        return;
    }; // type is double
}

TEST(Exceptions1, Test1) {
    //ASSERT_THROW(F(), uint32_t);
    try {
        //F1();
        //F2();
        //F3();
        //F4();
        F5();
    }
	catch (int32_t error)
	{
        std::cout << "\n[int32_t] code = " << error;
	}
	catch (char error)
    {
        std::cout << "\n[char] code = " << error;
    }
	catch (double error)
	{
        std::cout << "\n[double] code = " << error;
	}
	catch (float error) {
        std::cout << "\n[float] code = " << error;
    }
	catch (std::function<void()>& error) {
        std::cout << "\n[lambda] code = ";
        error();
    }
	catch (...) {
        std::cout << "\nTEST(Exceptions, Test1)";
    }
}