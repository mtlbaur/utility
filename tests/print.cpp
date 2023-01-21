#include <fstream>

#include <print.h>

using S = std::string;

template <typename T>
using V = std::vector<T>;

template <typename... T>
using T = std::tuple<T...>;

template <typename T, typename U>
using P = std::pair<T, U>;

int main() {
    {
        using namespace Utility;

        println(1);
        println("asdf");
        println(S("asdf"));
        println(V<int>{1, 2, 3});
        println(V<V<int>>{
            {1, 2},
            {3, 4}
        });
        println(V<V<V<int>>>{
            {{1, 2},
             {3, 4}},
            {{1, 2},
             {3, 4}}
        });
        println("teststring ",
                V<V<V<S>>>{
                    {{"one", "two"},
                     {"three", "four"}},
                    {{"one", "two"},
                     {"three", "four"}}
        },
                " 123");
        println(T<int, S, double>(1, "one", 2.23213));
        println("first ", T<int, S, double>(1, "one", 2.23213), " last");
        println("first ",
                V<S>{
                    "row 1",
                    "row 2",
                    "row 3",
                },
                " 123 ",
                P<int, double>(5, 11.1),
                " -- ",
                T<int, S, V<S>, double>(
                    1,
                    "one",
                    V<S>{
                        "row 1",
                        "row 2",
                        "row 3",
                    },
                    2.23213),
                " last");
    }

#define WRITE 0
#if WRITE
    {
        using namespace Utility;

        auto out = std::ofstream("out.txt");

        if (out.good()) {
            writeln(out, 1);
            writeln(out, "asdf");
            writeln(out, S("asdf"));
            writeln(out, V<int>{1, 2, 3});
            writeln(out, V<V<int>>{
                             {1, 2},
                             {3, 4}
            });
            writeln(out, V<V<V<int>>>{
                             {{1, 2},
                              {3, 4}},
                             {{1, 2},
                              {3, 4}}
            });
            writeln(out, "teststring ",
                    V<V<V<S>>>{
                        {{"one", "two"},
                         {"three", "four"}},
                        {{"one", "two"},
                         {"three", "four"}}
            },
                    " 123");
            writeln(out, T<int, S, double>(1, "one", 2.23213));
            writeln(out, "first ", T<int, S, double>(1, "one", 2.23213), " last");
            writeln(out, "first ",
                    V<S>{
                        "row 1",
                        "row 2",
                        "row 3",
                    },
                    " 123 ",
                    P<int, double>(5, 11.1),
                    " : ",
                    T<int, S, V<S>, double>(
                        1,
                        "one",
                        V<S>{
                            "row 1",
                            "row 2",
                            "row 3",
                        },
                        2.23213),
                    " last");
        }

        out.close();
    }
#endif
#undef WRITE
}