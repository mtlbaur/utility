#include <cassert>

#include <test.h>

using S = std::string;

template <typename T>
using V = std::vector<T>;

template <typename... T>
using T = std::tuple<T...>;

template <typename T>
bool hasMember(const T& o, const S& name) {
    return name == "ret" && (requires { o.ret; }) ||
           name == "args" && (requires { o.args; });
}

int main() {
    {
        using namespace Utility;

        {
            // VOID()
            Test<void, T<>> t;
            assert(!hasMember(t, "ret"));
            assert(!hasMember(t, "args"));
        }
        {
            // VALUE()
            Test<int, T<>> t(1);
            assert(hasMember(t, "ret"));
            assert(!hasMember(t, "args"));
        }
        {
            // VOID(T)
            Test<void, T<int, S>> t({1, "two"});
            assert(!hasMember(t, "ret"));
            assert(hasMember(t, "args"));
        }
        {
            // VALUE(S, T)
            Test<double, T<int, S>> t(1.0, {1, "two"});
            assert(hasMember(t, "ret"));
            assert(hasMember(t, "args"));
        }
        {
            // VECTOR<VOID()>
            Tests<void> vt{
                {},
                {},
            };
            for (const auto& t : vt) {
                assert(!hasMember(t, "ret"));
                assert(!hasMember(t, "args"));
            }
        }
        {
            // VECTOR<VALUE()>
            Tests<int> vt{
                1,
                2,
            };
            for (const auto& t : vt) {
                assert(hasMember(t, "ret"));
                assert(!hasMember(t, "args"));
            }
        }
        {
            // VOID<VALUE(T)>
            Tests<void, int, S> vt{
                {{1, "two"}},
                {{3, "four"}},
            };
            for (const auto& t : vt) {
                assert(!hasMember(t, "ret"));
                assert(hasMember(t, "args"));
            }
        }
        {
            // VECTOR<VALUE(S, T)>
            Tests<double, int, S> vt{
                {1.0, {1, "two"} },
                {3.0, {3, "four"}},
            };
            for (const auto& t : vt) {
                assert(hasMember(t, "ret"));
                assert(hasMember(t, "args"));
            }
        }
    }
}