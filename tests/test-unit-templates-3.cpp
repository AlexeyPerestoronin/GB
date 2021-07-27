#include "tests/test-unit-common.hpp"

template<typename LType, typename RType>
auto max2(LType lh, RType rh) {
    return lh > rh ? lh : rh;
}

template<typename LType, typename RType, typename ReturnType>
ReturnType max3(LType lh, RType rh) {
    return lh > rh ? lh : rh;
}

template<typename LType, typename RType>
auto max4(LType lh, RType rh) -> decltype(lh > rh ? lh : rh) {
    return lh > rh ? lh : rh;
}

TEST(Part4, Simple1) {
    ASSERT_TRUE(true);
    ASSERT_EQ(max2(2, 3), 3);
    ASSERT_TRUE((std::is_same_v<decltype(max2<int, int>(3, 4)), int>));
    ASSERT_TRUE((std::is_same_v<decltype(max2<int, double>(3, 4)), double>));
    ASSERT_TRUE((std::is_same_v<decltype(max2<int, double>(5, 4)), double>));

    ASSERT_TRUE((std::is_same_v<decltype(max3<int, int, int>(3, 4)), int>));
    ASSERT_TRUE((std::is_same_v<decltype(max3<int, double, double>(3, 4)), double>));
    ASSERT_TRUE((std::is_same_v<decltype(max3<int, double, double>(5, 4)), double>));
    ASSERT_TRUE((std::is_same_v<decltype(max3<int, double, int>(5, 4)), int>));

	//auto res = max4<int, int>(3, 4);
    //ASSERT_TRUE((std::is_same_v<decltype(max4<int, int>(3ui32, 4ui32)), uint32_t>));
    //ASSERT_TRUE((std::is_same_v<decltype(max4<int, double>(3, 4)), double>));
    //ASSERT_TRUE((std::is_same_v<decltype(max4<int, double>(5, 4)), double>));
    //ASSERT_TRUE((std::is_same_v<decltype(max4<int, double>(5, 4)), int>));
}
