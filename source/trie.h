#ifndef TRIE_H_GUARD
#define TRIE_H_GUARD

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

#include "print.h"

namespace Utility::DataStructures {
    template <typename T>
    struct Trie {
        template <typename U>
        struct Node {
            bool end     = false;
            Node* parent = nullptr;
            std::unordered_map<U, Node> map;

            Node() = default;
            Node(Node* parent) : parent(parent) {}
        };

        template <typename U>
        using Se = std::vector<U>; // sequence

        template <typename U>
        using Ses = std::vector<Se<U>>; // sequences

        Node<T> root;

        Trie() = default;
        Trie(const Se<T>& se) { add(se); }
        Trie(const Ses<T>& ses) { addList(ses); }

        // Add sequences from a list.
        void addList(const Ses<T>& ses) {
            for (const Se<T>& se : ses) {
                add(se);
            }
        }

        // Add a sequence.
        void add(const Se<T>& se) {
            Node<T>* curr = &root;

            for (const T& t : se) {
                if (curr->map.contains(t)) {
                    curr = &curr->map[t];
                } else {
                    const auto& [it, success] = curr->map.emplace(t, curr);
                    assert(success);
                    curr = &it->second; // `first` == key; `second` == value == Node
                }
            }

            curr->end = true;
        }

        // Returns a pointer to the end node of a sequence OR nullptr if the sequence was not found.
        Node<T>* search(const Se<T>& se) {
            if (se.empty()) return nullptr;

            Node<T>* curr = &root;

            for (const T& t : se) {
                if (curr->map.contains(t)) {
                    curr = &curr->map[t];
                } else {
                    return nullptr;
                }
            }

            return curr->end ? curr : nullptr;
        }

        // Accepts a sequence `se` and a starting node `curr` and attempts to remove `se` by starting at its last value and iterating backwards.
        // Returns the number of removed nodes.
        // NOTE: this function will NOT CHECK if the entirety of `se` exists before it starts removing nodes; it will invalidate the tree if used incorrectly.
        // NOTE: `curr` is a pointer reference and will be altered depending on how many nodes are removed.
        static int reverseRemove(const Se<T>& se, Node<T>*& curr) {
            if (se.empty() || !curr) return 0;

            int i = se.size() - 1;

            if (curr->end) {
                curr->end = false;

                if (curr->map.empty()) {
                    do {
                        curr = curr->parent;
                        curr->map.erase(se[i]);
                        i--;
                    } while (i > -1 && curr->map.empty() && !curr->end);
                }

                return se.size() - (i + 1);
            }

            return 0;
        }

        // Removes the sequence `se`, if it exists, and returns the number of removed nodes.
        int remove(const Se<T>& se) {
            Node<T>* end = search(se);
            return reverseRemove(se, end);
        }

        // Writes a graph of the tree starting at node `curr` to `out`.
        static void write(std::ostream& out, Node<T>* curr, bool isRoot) {
            out << (isRoot ? 'R' : 'N') << '\n';

            const auto fill = [&](int depth, const std::vector<int>& width) {
                for (int j = 0; j < depth; j++) {
                    out << (width[j] > 0 ? "\u2502  " : "   "); // vertical `|` line with spacing OR only spacing
                }
            };

            const auto dfs = [&](const auto& dfs, const std::unordered_map<T, Node<T>>& map, int depth, std::vector<int> width) -> void {
                width.emplace_back(static_cast<int>(map.size()) - 1);

                int i = 0;

                for (const auto& [key, value] : map) { // internal nodes
                    fill(depth, width);

                    out << (i < map.size() - 1 ? "\u251c" : "\u2514") // `|-` branching line OR `L` line
                        << "\u2500\u2500";                            // double `--` horizontal line

                    Utility::write(out, key);

                    out << (value.end ? "\u2b26" : "") // angled hollow square indicating end of a sequence OR nothing
                        << '\n';

                    dfs(dfs, value.map, depth + 1, width);

                    width[depth]--;
                    i++;
                }

                if (i == 0) { // leaf node
                    fill(depth, width);

                    out << "\u2514"       // `|-` branching line OR `L` line
                        << "\u2500\u2500" // double `--` horizontal line
                        << "\u25c1"       // angled hollow triangle indicating leaf node
                        << '\n';
                }
            };

            dfs(dfs, curr->map, 0, {});
        }

        void write(std::ostream& out, Node<T>* start) {
            write(out, start, start == root);
        }

        void print(Node<T>* start) {
            write(std::cout, start, start == &root);
        }

        void print() {
            write(std::cout, &root, true);
        }
    };
} // namespace Utility::DataStructures

#endif