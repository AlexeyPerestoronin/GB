#include "tests/test-common.hpp"
#include <array>

template<typename Type, size_t Size = 0>
class B {
    static_assert(Size == 0, "only for zero Size");
	
    Type _value{};

    public:
    void Print() {
        std::cout << "! " << typeid(Type).name() << ' ' << _value << std::endl;
    }
};

template<typename Type, size_t Size>
class B<Type*, Size> {
    static_assert(Size != 0, "only for non zero Size");
	
    Type* _values{};

    public:
    B(Type value) {
        _values = new Type[Size];
        for (size_t i = 0; i < Size; ++i)
            _values[i] = value;
    }

    ~B() {
        delete[] _values;
    }

    void Print() {
        std::cout << typeid(Type*).name();
        for (size_t i = 0; i < Size; ++i)
            std::cout << '\n' << _values[i];
    }
};

template<size_t Size>
class B<char*, Size> {
    static_assert(Size != 0, "only for non zero Size");

    char _values[Size + 1];

    public:
    B(char value) {
        for (size_t i = 0; i < Size; ++i)
            _values[i] = value;
        _values[Size] = '\0';
    }

    void Print() {
        std::cout << typeid(char*).name() << _values;
    }
};

TEST(Part6, Simple1) {
    B<int> b{};
    b.Print();
}

TEST(Part6, Simple2) {
    B<int, 0> b{};
    b.Print();
}

TEST(Part6, Simple3) {
    B<int*, 1> b{ 3 };
    b.Print();
}

TEST(Part6, Simple4) {
    B<int*, 5> b{ 5 };
    b.Print();
}

TEST(Part6, Simple5) {
    B<int*, 9> b{ 9 };
    b.Print();
}

TEST(Part6, Simple6) {
    B<char*, 9> b{ 'A' };
    b.Print();
}
