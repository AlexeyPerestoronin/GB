#include "tests/test-common.hpp"

#ifdef _DEBUG
#define CHECK_POINTER(pointer) if (!pointer) \
	throw std::exception("null pointer");
#else
#define CHECK_POINTER();
#endif

bool F(int* pointer) {
    CHECK_POINTER(pointer);

	return true;
}

TEST(Streams1, Example1) {
    bool flag1{ false };
    EXPECT_FALSE(flag1);
    bool flag2{ false };
    EXPECT_FALSE(flag2);
    //EXPECT_FALSE(F());
    EXPECT_FALSE(0);
    EXPECT_TRUE(-3);
    EXPECT_TRUE(+3);
}

TEST(Streams1, Example2) {
    EXPECT_EQ(3, 3);
    EXPECT_NE(3, 4);
    EXPECT_LE(3, 3);
    EXPECT_LE(3, 4);
}

struct MyException : std::exception {

};

void G() {
    //int i = MAX(FGG, 2);
    throw MyException{};
}

void G1() {
    throw std::exception{};
}

void H() {
    return;
}

TEST(Streams1, Example3) {
    EXPECT_THROW(G(), MyException);
    //EXPECT_NO_THROW(G1(), MyException);
    EXPECT_THROW(G(), std::exception);
    EXPECT_NO_THROW(H());
}

TEST(Streams1, Example4) {
    EXPECT_STREQ("one", "one");
    EXPECT_STRNE("one", "o1n");
    std::string str{ "one" };
    EXPECT_STREQ("one", str.c_str());
}

TEST(Streams1, Example5) {
    //EXPECT_EQ(3.14f, 3.14001f);
    EXPECT_NEAR(3.14f, 3.141f, 3);
}
