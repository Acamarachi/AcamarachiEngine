#ifndef ACAMARACHI_CORE_EXPECTED
#define ACAMARACHI_CORE_EXPECTED 1

#include <variant>
#include "macros.hpp"

namespace Acamarachi::Core
{

    template <typename Result, typename Error>
    class Expected
    {
    public:
        template <typename T>
        Expected(T t) : value{std::move(t)} {}

        bool is_result() const { return value.index() == 1; }
        Result result() const { return *std::get_if<1>(&value); }

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
}

#endif