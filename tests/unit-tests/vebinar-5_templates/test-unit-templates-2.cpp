#include "tests/test-common.hpp"

template<typename Type>
Type max1(Type lh, Type rh) {
    static_assert(false, "cannot use with not possible types");
    return lh > rh ? lh : rh;
}

template<>
int max1<int>(int lh, int rh) {
    return lh > rh ? lh : rh;
}

template<>
double max1<double>(double lh, double rh) {
    return lh > rh ? lh : rh;
}

template<>
char max1<char>(char lh, char rh) {
    return lh > rh ? lh : rh;
}

TEST(Part3, Simple1) {
    ASSERT_TRUE(true);
    ASSERT_EQ(max1<int>(2, 3), 3);
    ASSERT_EQ(max1<double>(2., 3.), 3);
    ASSERT_EQ(max1<char>('a', 'b'), 'b');

    ASSERT_EQ(max1<double>(2, 3.4), 3.4);
    ASSERT_EQ(max1<int>(2, 3.4), 3);

    //ASSERT_EQ(max1<uint32_t>(2, 3), 3); // compilation error
}
