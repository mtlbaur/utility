#include <cassert>
#include <fstream>
#include <vector>

#include <trie.h>

int main() {
    Utility::DataStructures::Trie<int> trie;

    {
        const auto add = [&](const std::vector<int>& v) {
            Utility::print("ADD ", v, '\n');
            trie.add(v);
            trie.print();
        };

        add({1, 2, 3});
        add({1});
        add({1, 2, 3});
        add({1, 2, 4});
        add({1, 2, 4, 5});
        add({0, 1, 2, 3, 4, 5, 6, 7});
        add({0, 1, 2, 3, 8, 9, 10});
        add({0, 1, 2, 3, 8, 11, 12, 13});
        add({0, 1, 14, 15, 16, 17});
        add({0, 1, 2, 3, 8});
        add({0});
        add({2, 2, 2});
        add({2, 2, 2, 2, 2});
    }
    {
        const auto doesNotContain = [&](const std::vector<int>& v) {
            Utility::print("DOES NOT CONTAIN ", v, '\n');
            assert(!trie.search(v));
        };

        doesNotContain({1, 14, 15});
        doesNotContain({3, 1, 4});
        doesNotContain({1, 2, 3, 8});
        doesNotContain({0, 1, 2, 3, 8, 11});
        doesNotContain({2});
        doesNotContain({2, 2});
        doesNotContain({2, 2, 2, 2});
        doesNotContain({2, 2, 2, 2, 2, 2});
    }
    {
        const auto remove = [&](const std::vector<int>& v, int i) {
            Utility::print("REMOVE ", v, '\n');
            assert(!!trie.search(v));
            assert(trie.remove(v) == i);
            trie.print();
        };

        remove({1, 2, 3}, 1);
        remove({1, 2, 4}, 0);
        remove({1, 2, 4, 5}, 3);
        remove({1}, 1);
        remove({0}, 0);
        remove({0, 1, 2, 3, 8}, 0);
        remove({0, 1, 2, 3, 8, 9, 10}, 2);
        remove({0, 1, 2, 3, 4, 5, 6, 7}, 4);
        remove({0, 1, 14, 15, 16, 17}, 4);
        remove({0, 1, 2, 3, 8, 11, 12, 13}, 8);
        remove({2, 2, 2}, 0);
        remove({2, 2, 2, 2, 2}, 5);
    }

#define WRITE 0
#if WRITE
    {
        auto out = std::ofstream("trie.txt");

        if (out.good()) {
            {
                const auto add = [&](const std::vector<int>& v) {
                    Utility::write(out, "ADD ", v, '\n');
                    trie.add(v);
                    trie.write(out);
                };

                add({1, 2, 3});
                add({1});
                add({1, 2, 3});
                add({1, 2, 4});
                add({1, 2, 4, 5});
                add({0, 1, 2, 3, 4, 5, 6, 7});
                add({0, 1, 2, 3, 8, 9, 10});
                add({0, 1, 2, 3, 8, 11, 12, 13});
                add({0, 1, 14, 15, 16, 17});
                add({0, 1, 2, 3, 8});
                add({0});
            }
            {
                const auto doesNotContain = [&](const std::vector<int>& v) {
                    Utility::write(out, "DOES NOT CONTAIN ", v, '\n');
                    assert(!trie.search(v));
                };

                doesNotContain({1, 14, 15});
                doesNotContain({3, 1, 4});
                doesNotContain({1, 2, 3, 8});
                doesNotContain({0, 1, 2, 3, 8, 11});
            }
            {
                const auto remove = [&](const std::vector<int>& v, int i) {
                    Utility::write(out, "REMOVE ", v, '\n');
                    assert(!!trie.search(v));
                    assert(trie.remove(v) == i);
                    trie.write(out);
                };

                remove({1, 2, 3}, 1);
                remove({1, 2, 4}, 0);
                remove({1, 2, 4, 5}, 3);
                remove({1}, 1);
                remove({0}, 0);
                remove({0, 1, 2, 3, 8}, 0);
                remove({0, 1, 2, 3, 8, 9, 10}, 2);
                remove({0, 1, 2, 3, 4, 5, 6, 7}, 4);
                remove({0, 1, 14, 15, 16, 17}, 4);
                remove({0, 1, 2, 3, 8, 11, 12, 13}, 8);
            }
        }

        out.close();
    }
#endif
#undef WRITE
}