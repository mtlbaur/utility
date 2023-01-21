#include <test.h>

static int staticVar = 0;

void f_void() {
    staticVar = 1;
}

int f_value() {
    staticVar = 2;
    return staticVar;
}

void f_void_t(int a, int b) {
    staticVar = 3 + a + b;
}

int f_value_t(int a, int b) {
    staticVar = 4 + a + b;
    return staticVar;
}

struct TestStruct {
    int classVar = 0;

    void c_f_void() {
        classVar = 1;
    }

    int c_f_value() {
        classVar = 2;
        return classVar;
    }

    void c_f_void_t(int a, int b) {
        classVar = 3 + a + b;
    }

    int c_f_value_t(int a, int b) {
        classVar = 4 + a + b;
        return classVar;
    }
};

int main() {
    {
        using namespace Utility;

        {
            using FncType = decltype(f_void);

            Functions<FncType> vf{
                f_void,
            };

            runtime(vf);
            test(vf);
        }
        {
            using FncType = decltype(f_value);
            using RetType = std::invoke_result<FncType>::type;

            Functions<FncType> vf{
                f_value,
            };

            Tests<RetType> vt{
                2,
                2,
            };

            check(vf, vt);
            runtime(vf);
            test(vf, vt);
        }
        {
            using FncType = decltype(f_void_t);
            using RetType = std::invoke_result<FncType, int, int>::type;

            Functions<FncType> vf{
                f_void_t,
            };

            Tests<RetType, int, int> vt{
                {{1, 2}},
                {{3, 4}},
            };

            runtime(vf, vt);
            test(vf, vt);
        }
        {
            using FncType = decltype(f_value_t);
            using RetType = std::invoke_result<FncType, int, int>::type;

            Functions<FncType> vf{
                f_value_t,
            };

            Tests<RetType, int, int> vt{
                {7,  {1, 2}},
                {11, {3, 4}},
            };

            vt.emplace_back(Test<RetType, std::tuple<int, int>>{
                7, {1, 2}
            });

            check(vf, vt);
            runtime(vf, vt);
            test(vf, vt);
        }
        {
            TestStruct ts;

            Functions<void()> vf{
                [&]() { ts.c_f_void(); },
            };

            runtime(vf);
            test(vf);
        }
        {
            TestStruct ts;

            Functions<int()> vf{
                [&]() { return ts.c_f_value(); },
            };

            Tests<int> vt{
                2,
                2,
            };

            check(vf, vt);
            runtime(vf);
            test(vf, vt);
        }
        {
            TestStruct ts;

            Functions<void(int, int)> vf{
                [&](int a, int b) { ts.c_f_void_t(a, b); },
            };

            Tests<void, int, int> vt{
                {{1, 2}},
                {{3, 4}},
            };

            runtime(vf, vt);
            test(vf, vt);
        }
        {
            TestStruct ts;

            Functions<int(int, int)> vf{
                [&](int a, int b) { return ts.c_f_value_t(a, b); },
            };

            Tests<int, int, int> vt{
                {7,  {1, 2}},
                {11, {3, 4}},
            };

            check(vf, vt);
            runtime(vf, vt);
            test(vf, vt);
        }
    }
}