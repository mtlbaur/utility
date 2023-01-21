#ifndef TEST_H_GUARD
#define TEST_H_GUARD

#include <iostream>
#include <vector>
#include <tuple>
#include <chrono>
#include <functional>
#include <type_traits>
#include <concepts>

#include "print.h"

namespace Utility {
    namespace {
        template <typename T>
        concept VoidType = std::same_as<void, T>;

        template <typename T>
        concept ValueType = !std::same_as<void, T>;

        template <typename T>
        concept VoidTuple = (std::tuple_size_v<T> == 0);

        template <typename T>
        concept ValueTuple = (std::tuple_size_v<T> > 0);

        using DefaultDuration = std::chrono::duration<double, std::micro>;
    } // namespace

    template <typename S, typename T>
    struct Test;

    template <typename Fnc>
    using Functions = std::vector<std::function<Fnc>>;

    template <typename Ret, typename... Args>
    using Tests = std::vector<Test<Ret, std::tuple<Args...>>>;

    template <VoidType S, VoidTuple T>
    struct Test<S, T> {};

    template <ValueType S, VoidTuple T>
    struct Test<S, T> {
        S ret;

        Test(S&& ret) : ret(ret) {}
    };

    template <VoidType S, ValueTuple T>
    struct Test<S, T> {
        T args;

        Test(T&& args) : args(args) {}
    };

    template <ValueType S, ValueTuple T>
    struct Test<S, T> {
        S ret;
        T args;

        Test(S&& ret, T&& args) : ret(ret), args(args) {}
    };

    template <typename Fnc, ValueType S, VoidTuple T>
    bool check(const std::vector<Fnc>& vf, std::vector<Test<S, T>>& vt) {
        bool success = true;

        for (int i = 1; Test t : vt) {
            for (int j = 1; const Fnc& f : vf) {
                success &= [&](const auto& a, const auto& b) -> bool {
                    if (a != b) {
                        std::cout << "function " << j << " check " << i << ":\n --> ";
                        print(a);
                        std::cout << "\n  != ";
                        print(b);
                        std::cout << '\n';

                        return false;
                    }
                    return true;
                }(f(), t.ret);
                j++;
            }
            i++;
        }

        return success;
    }

    template <typename Fnc, ValueType S, ValueTuple T>
    bool check(const std::vector<Fnc>& vf, std::vector<Test<S, T>>& vt) {
        bool success = true;

        for (int i = 1; Test t : vt) {
            for (int j = 1; const Fnc& f : vf) {
                success &= [&](const auto& a, const auto& b) -> bool {
                    if (a != b) {
                        std::cout << "function " << j << " check " << i << ":\n --> ";
                        print(a);
                        std::cout << "\n  != ";
                        print(b);
                        std::cout << '\n';

                        return false;
                    }
                    return true;
                }(std::apply(f, t.args), t.ret);
                j++;
            }
            i++;
        }

        return success;
    }

    template <typename Fnc>
    auto runtimeRecord(Fnc f) {
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

        f();

        return std::chrono::steady_clock::now() - start;
    }

    template <typename Fnc, ValueTuple Args>
    auto runtimeRecord(Fnc f, Args a) {
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

        std::apply(f, a);

        return std::chrono::steady_clock::now() - start;
    }

    template <typename Fnc, typename Delta = DefaultDuration>
    void runtime(const std::vector<Fnc>& vf, int iterations = 10000, Delta delta = DefaultDuration::zero()) {
        for (int j = 1; const Fnc& f : vf) {
            delta = Delta::zero();

            for (int k = 0; k < iterations; k++) {
                delta += runtimeRecord(f);
            }

            std::cout << "function " << j << ": " << static_cast<double>(delta.count()) / static_cast<double>(iterations) << '\n';
            j++;
        }
    }

    template <typename Fnc, typename S, ValueTuple T, typename Delta = DefaultDuration>
    void runtime(const std::vector<Fnc>& vf, std::vector<Test<S, T>>& vt, int iterations = 10000, Delta delta = DefaultDuration::zero()) {
        for (int j = 1; const Fnc& f : vf) {
            delta = Delta::zero();

            for (Test<S, T>& t : vt) {
                for (int k = 0; k < iterations; k++) {
                    delta += runtimeRecord(f, t.args);
                }
            }

            std::cout << "function " << j << ": " << static_cast<double>(delta.count()) / static_cast<double>(iterations) << '\n';
            j++;
        }
    }

    template <typename Fnc>
    void modify(const std::vector<Fnc>& vf) {
        for (const Fnc& f : vf) {
            f();
        }
    }

    template <typename Fnc, typename S, ValueTuple T>
    void modify(const std::vector<Fnc>& vf, std::vector<Test<S, T>>& vt) {
        for (Test<S, T>& t : vt) {
            for (const Fnc& f : vf) {
                std::apply(f, t.args);
            }
        }
    }

    template <typename Fnc, typename Delta = DefaultDuration>
    void test(const std::vector<Fnc>& vf, int iterations = 10000, Delta delta = DefaultDuration::zero()) {
        runtime(vf, iterations, delta);
    }

    template <typename Fnc, VoidType S, ValueTuple T, typename Delta = DefaultDuration>
    void test(const std::vector<Fnc>& vf, std::vector<Test<S, T>>& vt, int iterations = 10000, bool modifyTests = false, Delta delta = DefaultDuration::zero()) {
        runtime(vf, vt, iterations, delta);

        if (modifyTests) {
            modify(vf, vt);
        }
    }

    template <typename Fnc, ValueType S, VoidTuple T, typename Delta = DefaultDuration>
    void test(const std::vector<Fnc>& vf, std::vector<Test<S, T>>& vt, int iterations = 10000, bool modifyTests = false, Delta delta = DefaultDuration::zero()) {
        if (check(vf, vt)) {
            runtime(vf, iterations, delta);
        }
        if (modifyTests) {
            modify(vf);
        }
    }

    template <typename Fnc, ValueType S, ValueTuple T, typename Delta = DefaultDuration>
    void test(const std::vector<Fnc>& vf, std::vector<Test<S, T>>& vt, int iterations = 10000, bool modifyTests = false, Delta delta = DefaultDuration::zero()) {
        if (check(vf, vt)) {
            runtime(vf, vt, iterations, delta);
        }
        if (modifyTests) {
            modify(vf, vt);
        }
    }
} // namespace Utility

#endif