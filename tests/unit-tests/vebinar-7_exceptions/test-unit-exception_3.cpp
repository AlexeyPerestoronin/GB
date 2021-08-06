#include "tests/test-common.hpp"

struct A {
    A() noexcept
    {
        //throw -102ui32;
    }
	
    ~A() {
        //throw -102i32;
    }
};

struct exc : std::exception {
    char const* what() const override {
        return "exc";
    }
};

void _F1() {
    throw std::exception("F()");
}

void _F2() {
    throw exc{};
}

TEST(Exceptions3, Test1) {
    try {
        //A a{};
        //_F1();
        _F2();
        std::exception error = static_cast<std::exception>(exc{});
    } catch (std::exception& error) {
        std::cout << "[std::exception] what happen? - " << error.what();
    } catch (exc& error) {
        std::cout << "[exc] what happen? - " << error.what();
    }
}