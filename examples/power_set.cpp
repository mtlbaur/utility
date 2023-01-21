#include <vector>
#include <cmath>
#include <cassert>

#include <test.h>

namespace PowerSet {
    template <typename T>
    using Set = std::vector<T>;

    template <typename T>
    using Sets = std::vector<Set<T>>;

    namespace {
        template <typename T>
        Set<T> operator+(const Set<T>& a, const T& b) {
            Set<T> r;
            r.reserve(a.size() + 1);

            std::copy(a.begin(), a.end(), std::back_inserter(r));
            r.emplace_back(b);

            return r;
        }

        template <typename T>
        void combine(Sets<T>& ps, const Set<T>& items, const T& item) {
            Set<T> s;
            s.reserve(items.size() + 1);

            std::copy(items.begin(), items.end(), std::back_inserter(s));
            s.emplace_back(item);

            ps.emplace_back(std::move(s));
        }
    } // namespace

    namespace v1 {
        template <typename T>
        Sets<T> compute(const Set<T>& n) {
            const unsigned nSize = n.size();

            Sets<T> ps;
            ps.reserve(pow(2, nSize));
            ps.emplace_back(Set<T>{});

            for (unsigned i = 0; i < nSize; i++) {
                const unsigned psSize = ps.size();

                for (unsigned j = 0; j < psSize; j++) {
                    ps.emplace_back(ps[j] + n[i]);
                }
            }

            return ps;
        }
    } // namespace v1

    namespace v2 {
        template <typename T>
        Sets<T> compute(const Set<T>& n) {
            const unsigned nSize = n.size();

            Sets<T> ps;
            ps.reserve(pow(2, nSize));
            ps.emplace_back(Set<T>{});

            for (unsigned i = 0; i < nSize; i++) {
                const unsigned psSize = ps.size();

                for (unsigned j = 0; j < psSize; j++) {
                    combine(ps, ps[j], n[i]);
                }
            }

            return ps;
        }
    } // namespace v2

    namespace v3 {
        template <typename T>
        Sets<T> compute(const Set<T>& n) {
            const unsigned nSize  = n.size();
            const unsigned psSize = 1 << nSize;

            Sets<T> ps(psSize, Set<T>{});

            for (unsigned subsetBits = 0; subsetBits < psSize; subsetBits++) {
                for (unsigned nthBit = 0; nthBit < nSize; nthBit++) {
                    if ((subsetBits >> nthBit) & 1) {
                        ps[subsetBits].emplace_back(n[nthBit]);
                    }
                }
            }

            return ps;
        }
    } // namespace v3
} // namespace PowerSet

int main() {
    {
        auto r1 = PowerSet::v1::compute<int>({1, 2, 3, 4, 5, 6});
        auto r2 = PowerSet::v2::compute<int>({1, 2, 3, 4, 5, 6});
        auto r3 = PowerSet::v3::compute<int>({1, 2, 3, 4, 5, 6});

        assert(r1 == r2 && r2 == r3);
    }

    using Set     = PowerSet::Set<int>;
    using FncType = decltype(PowerSet::v1::compute<int>);

    Utility::Functions<FncType> vf{
        PowerSet::v1::compute<int>,
        PowerSet::v2::compute<int>,
        PowerSet::v3::compute<int>,
    };

    {
        Utility::Tests<PowerSet::Sets<int>, Set> vt{
            {{{{}},
              {{}}},
             {{{}, {1}},
              {{1}}},
             {{{}, {1}, {2}, {1, 2}},
              {{1, 2}}},
             {{{}, {1}, {2}, {1, 2}, {3}, {1, 3}, {2, 3}, {1, 2, 3}},
              {{1, 2, 3}}}},
        };

        test(vf, vt);
    }

    {
        Utility::Tests<void, Set> vt{
            {{{1, 2, 3, 4, 5, 6}}}};

        runtime(vf, vt);
    }
}