#include "tests/test-common.hpp"

class A {
    int32_t _index{};

    public:
    A() = default;

    A& operator++() {
        ++_index;
        return *this;
    }

    A operator++(int) {
        A copy{ *this };
        ++(this->_index);
        return copy;
    }

    A operator--(int) {
        A copy{ *this };
        --(this->_index);
        return copy;
    }

    A& operator--() {
        --_index;
        return *this;
    }

    int32_t GetIndex() {
        return _index;
    }
};

TEST(Part1, Simple1) {
    ASSERT_TRUE(true);
    A a{};
    ASSERT_EQ((++a).GetIndex(), 1);
    ASSERT_EQ((--a).GetIndex(), 0);
    ASSERT_EQ((a++).GetIndex(), 0);
    ASSERT_EQ(a.GetIndex(), 1);
    ASSERT_EQ((a--).GetIndex(), 1);
    ASSERT_EQ(a.GetIndex(), 0);
}
