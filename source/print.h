#ifndef PRINT_H_GUARD
#define PRINT_H_GUARD

#include <iostream>
#include <vector>
#include <tuple>

namespace Utility {
    template <typename T, typename... A>
    void write(std::ostream&, const std::vector<T>&, const A&...);

    template <typename... T, typename... A>
    void write(std::ostream&, const std::tuple<T...>&, const A&...);

    template <typename T, typename U, typename... A>
    void write(std::ostream&, const std::pair<T, U>&, const A&...);

    template <typename T>
    void write(std::ostream& out, const T& t) {
        out << t;
    }

    template <typename... A>
    void write(std::ostream& out, const A&... a) {
        (write(out, a), ...);
    }

    template <typename T, typename... A>
    void write(std::ostream& out, const std::vector<T>& v, const A&... a) {
        out << "[ ";

        for (const auto& x : v) write(out, x, ' ');

        out << ']';

        (write(out, a), ...);
    }

    template <typename... T, typename... A>
    void write(std::ostream& out, const std::tuple<T...>& t, const A&... a) {
        out << "( ";

        std::apply(
            [&](const auto&... pack) -> void {
                ([&](const auto& arg) -> void {
                    write(out, arg, ' ');
                }(pack),
                 ...);
            },
            t);

        out << ')';

        (write(out, a), ...);
    }

    template <typename T, typename U, typename... A>
    void write(std::ostream& out, const std::pair<T, U>& p, const A&... a) {
        write(out, "( ", p.first, " : ", p.second, " )");

        (write(out, a), ...);
    }

    template <typename... A>
    void writeln(std::ostream& out, const A&... a) {
        write(out, a..., '\n');
    }

    template <typename... A>
    void print(const A&... a) {
        write(std::cout, a...);
    }

    template <typename... A>
    void println(const A&... a) {
        write(std::cout, a..., '\n');
    }
} // namespace Utility

#endif