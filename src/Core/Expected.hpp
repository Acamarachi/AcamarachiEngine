#pragma once

#include <variant>

namespace Acamarachi::Core
{

    template <typename Result, typename Error>
    class Expected
    {
    public:
        template <typename T>
        Expected(T t) : value{std::move(t)} {}

        bool is_result() const { return value.index() == 1; }
        Result result() const { return std::move(*std::get_if<1>(&value)); }
        Result result() { return std::move(*std::get_if<1>(&value)); }

        bool is_error() const { return value.index() == 2; }
        Error error() const { return *std::get_if<2>(&value); }

        template <typename T>
        Expected &operator=(T t)
        {
            value = std::move(t);
            return *this;
        }

        operator bool() const
        {
            return is_result();
        }

    private:
        std::variant<std::monostate, Result, Error> value;
    };

    #define catch_err(expected) ;           \
        if (!expected)

    #define log_err(error)  std::cerr << "Error: " << __FILE__ ":" << __LINE__ << " with error code " << (int)error << std::endl

    // template <typename Result, typename Error>
    // struct CustomExpected {
    // private:
    //     union {
    //         Result result_;
    //         Error error_;
    //     };
    //     int tag;

    // public:
    //     CustomExpected(Result res) {
    //         tag = 0;
    //         result_ = std::move(res);
    //     }

    //     CustomExpected(Error err) {
    //         tag = 1;
    //         error_ = std::move(err);
    //     }

    //     ~CustomExpected() {}

    //     bool is_result() const { return tag == 0; }
    //     bool is_error() const { return tag == 1; }

    //     constexpr Result result() { assert(tag == 0); return result_; }
    //     constexpr Error error() { assert(tag == 1); return error_; }
    // };
}