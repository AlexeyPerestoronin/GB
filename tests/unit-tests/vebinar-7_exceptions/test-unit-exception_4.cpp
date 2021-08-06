#include "tests/test-common.hpp"
#include <optional>
#include <strstream>

struct Error;

struct Error : std::exception {
    int32_t d_code{};
    int32_t d_line{};
    std::string d_message{};
    std::string d_file{};
    std::string d_function{};
	
    Error* d_subError{};

    Error(int32_t code, int32_t line, const std::string& message, const std::string& file, const std::string& function)
        : d_code(code)
        , d_line(line)
        , d_message(message)
        , d_file(file)
        , d_function(function) {}

	~Error()
	{
        //if (d_subError)
        //    delete d_subError;
	}

	Error& operator=(const Error& error)
    {
        d_code = error.d_code;
        d_line = error.d_line;
        d_message = error.d_message;
        d_file = error.d_file;
        d_function = error.d_function;
    };

	Error& AddSubError(const Error& subError) {
        d_subError = new Error(subError.d_code, subError.d_line, subError.d_message, subError.d_file, subError.d_function);
        return *this;
    }

	std::string CreateMessage() const
	{
        std::strstream message;
        message << "code = " << d_code;
        message << "; message = " << d_message;
        message << "; file = " << d_file;
        message << "; line = " << d_line;
        message << "; function = " << d_function;
        if (d_subError) {
            message << "\n" << d_subError->CreateMessage();
        }
        return message.str();
	}
	

    char const* what() const override {
        static std::string message{};
        message = CreateMessage();
        return message.c_str();
    }
};

#define GET_ERROR(CODE, MESSAGE) Error{ CODE, __LINE__, MESSAGE, __FILE__, __FUNCTION__ }

void Func1() {
    throw GET_ERROR(-101, "something happen in Func1");
}

void Func2() {
	try
	{
        Func1();
	}
	catch (Error& error)
	{
        Error error2 = GET_ERROR(-102, "something happen in Func2");
        error2.AddSubError(error);
        throw std::move(error2);
	}
}

TEST(Exceptions4, Test1) {
    try {
        Func2();
    } catch (Error& error) {
        std::cout << error.what();
    }
}