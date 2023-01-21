#include <unordered_map>
#include <vector>

#include <test.h>

namespace Fibonacci {
    namespace v1 {
        int nth(int n) {
            if (n > 1) return nth(n - 1) + nth(n - 2);
            return n;
        }
    } // namespace v1

    namespace v2 {
        int nth(int n) {
            std::unordered_map<int, int> m;

            const auto dfs = [&](const auto& dfs, int n) -> int {
                if (m.contains(n)) return m[n];

                if (n > 1) {
                    m[n] = dfs(dfs, n - 1) + dfs(dfs, n - 2);
                    return m[n];
                }

                return n;
            };

            return dfs(dfs, n);
        }
    } // namespace v2

    namespace v3 {
        int nth(int n) {
            if (n < 2) return n;

            std::vector<int> a(n + 1, 0);
            a[1] = 1;

            for (int i = 2; i < n + 1; i++) {
                a[i] = a[i - 1] + a[i - 2];
            }

            return a[n];
        }
    } // namespace v3

    namespace v4 {
        int nth(int n) {
            int a[2]{0, 1};

            for (int i = 2; i < n + 1; i++) {
                a[i % 2] = a[(i + 1) % 2] + a[i % 2];
            }

            return a[n % 2];
        }
    } // namespace v4

    namespace v5 {
        int nth(int n) {
            int a[2]{0, 1};

            for (int i = 2; i < n + 1; i++) {
                a[i & 1] = a[i & 1 ^ 1] + a[i & 1];
            }

            return a[n & 1];
        }
    } // namespace v5

    namespace v6 {
        int nth(int n) {
            if (n < 2) return n;

            int a = 0, b = 1;

            for (; n > 1; n--) {
                int t = b;
                b += a;
                a = t;
            }

            return b;
        }
    } // namespace v6
} // namespace Fibonacci

int main() {
    Utility::Functions<int(int)> vf{
        Fibonacci::v1::nth,
        Fibonacci::v2::nth,
        Fibonacci::v3::nth,
        Fibonacci::v4::nth,
        Fibonacci::v5::nth,
        Fibonacci::v6::nth,
    };

    Utility::Tests<int, int> vt{
        {0,     {0} },
        {1,     {1} },
        {1,     {2} },
        {2,     {3} },
        {3,     {4} },
        {5,     {5} },
        {8,     {6} },
        {13,    {7} },
        {21,    {8} },
        {34,    {9} },
        {55,    {10}},
        {75025, {25}},
    };

    Utility::test(vf, vt);
}