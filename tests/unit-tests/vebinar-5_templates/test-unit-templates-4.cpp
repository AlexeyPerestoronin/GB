#include "tests/test-common.hpp"

template<typename Type>
class A {
    Type _value{};

    public:
    void Print() {
        std::cout << typeid(Type).name() << ' ' << _value << std::endl;
    }
};

template<typename Type>
class A<Type*> {
    Type* _value{};

    public:
    A() {
        _value = new Type{};
    }

    ~A() {
        delete _value;
    }

    void PrintP() {
        std::cout << typeid(Type*).name() << ' ' << _value << std::endl;
    }

	void PrintV() {
        std::cout << typeid(Type).name() << ' ' << *_value << std::endl;
    }
};

template<>
class A<char*> {
    char* _value{};

    public:
    A(std::string str) {
    	
        _value = new char[str.size()];
        for (size_t i{ 0 }; i < str.size(); ++i)
            _value[i] = str.at(i);
    }

    ~A() {
        delete[] _value;
    }

    void PrintP() {
        std::cout << typeid(char*).name() << ' ' << _value << std::endl;
    }

    void PrintV() {
        std::cout << typeid(char).name() << ' ' << *_value << std::endl;
    }
};

TEST(Part5, Simple1) {
    A<int> a{};
    a.Print();
}

TEST(Part5, Simple2) {
    A<double> a{};
    a.Print();
}

TEST(Part5, Simple3) {
    A<char> a{};
    a.Print();
}

TEST(Part5, Simple4) {
    A<int32_t*> a{};
    a.PrintP();
    a.PrintV();
}

TEST(Part5, Simple5) {
    std::string str{ "hello" };
    A<char*> a{ std::move(str) };
    a.PrintP();
    a.PrintV();
}
