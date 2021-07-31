#include "tests/test-common.hpp"

template<typename Type>
Type max(Type lh, Type rh) {
    static_assert(
        std::is_same_v<Type, int> ||
        std::is_same_v<Type, double> ||
        std::is_same_v<Type, char>,
        "cannot use with not possible types");

	return lh > rh ? lh : rh;
}

TEST(Part2, Simple1) {
    ASSERT_TRUE(true);
    ASSERT_EQ(max<int>(2, 3), 3);
    ASSERT_EQ(max<double>(2., 3.), 3);
    ASSERT_EQ(max<char>('a', 'b'), 'b');
	
    ASSERT_EQ(max<double>(2, 3.4), 3.4);
    ASSERT_EQ(max<int>(2, 3.4), 3);
	
    //ASSERT_EQ(max<uint32_t>(2, 3), 3); // compilation error
}