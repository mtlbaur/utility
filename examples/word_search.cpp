#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include <trie.h>

using Trie = Utility::DataStructures::Trie<char>;
using Node = Trie::Node<char>;
using VC   = std::vector<char>;
using VVC  = std::vector<VC>;

void printVC(const VC& vc, std::string end = " ") {
    for (char c : vc) {
        std::cout << c;
    }
    std::cout << end;
}

void printVVC(const VVC& vvc, std::string rowend = " ", std::string end = "\n") {
    for (const auto& row : vvc) {
        printVC(row, rowend);
    }
    std::cout << end;
}

VVC searchPrint(VVC& board, VVC& searchWords, VVC& foundWords) {
    int imax      = board.size() - 1;
    int jmax      = board.front().size() - 1;
    int backtrack = 0;

    Trie trie(searchWords);
    Node* curr = &trie.root;
    VC word;

    Utility::println("INITIAL");
    printVVC(board, "\n", "----\n");
    Utility::print("SEARCH WORDS: ");
    printVVC(searchWords);

    const auto dfs = [&](const auto& dfs, int i, int j) -> void {
        char c = board[i][j];

        if (c != '*' && curr->map.contains(c)) {
            word.emplace_back(c);
            curr        = &curr->map[c];
            board[i][j] = '*';

            if (curr->end) {
                Utility::println("--------------------------------");
                printVVC(board, "\n", "----\n");
                trie.print();
                Utility::println("FOUND ", word, " -->");
                foundWords.emplace_back(word);
                backtrack = Trie::reverseRemove(foundWords.back(), curr);
                trie.print();
            }
            if (backtrack == 0 && j < jmax) { // right
                dfs(dfs, i, j + 1);
            }
            if (backtrack == 0 && j > 0) { // left
                dfs(dfs, i, j - 1);
            }
            if (backtrack == 0 && i < imax) { // down
                dfs(dfs, i + 1, j);
            }
            if (backtrack == 0 && i > 0) { // up
                dfs(dfs, i - 1, j);
            }

            board[i][j] = c;
            word.pop_back();

            if (backtrack == 0) {
                curr = curr->parent;
            } else {
                backtrack--;
            }
        }
    };

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.front().size(); j++) {
            dfs(dfs, i, j);
        }
    }

    Utility::println("================================");

    return foundWords;
}

VVC search(VVC& board, VVC& searchWords, VVC& foundWords) {
    int imax      = board.size() - 1;
    int jmax      = board.front().size() - 1;
    int backtrack = 0;

    Trie trie(searchWords);
    Node* curr = &trie.root;
    VC word;

    const auto dfs = [&](const auto& dfs, int i, int j) -> void {
        char c = board[i][j];

        if (c != '*' && curr->map.contains(c)) {
            word.emplace_back(c);
            curr        = &curr->map[c];
            board[i][j] = '*';

            if (curr->end) {
                foundWords.emplace_back(word);
                backtrack = Trie::reverseRemove(foundWords.back(), curr);
            }
            if (backtrack == 0 && j < jmax) { // right
                dfs(dfs, i, j + 1);
            }
            if (backtrack == 0 && j > 0) { // left
                dfs(dfs, i, j - 1);
            }
            if (backtrack == 0 && i < imax) { // down
                dfs(dfs, i + 1, j);
            }
            if (backtrack == 0 && i > 0) { // up
                dfs(dfs, i - 1, j);
            }

            board[i][j] = c;
            word.pop_back();

            if (backtrack == 0) {
                curr = curr->parent;
            } else {
                backtrack--;
            }
        }
    };

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.front().size(); j++) {
            dfs(dfs, i, j);
        }
    }

    return foundWords;
}

#define PRINT_1 0
#define PRINT_2 0

int main() {
    {
        const auto vc = [](std::string&& s) {
            return VC(s.begin(), s.end());
        };

        {
            VVC board = {
                vc("abc"),
                vc("def"),
                vc("ghi"),
            };

            VVC searchWords = {
                vc("abe"),
                vc("abef"),
                vc("abeh"),
                vc("abed"),
                vc("ade"),
                vc("adeb"),
                vc("adef"),
                vc("adeh"),
                vc("null"),
            };

            VVC foundWords;

            if (PRINT_1) searchPrint(board, searchWords, foundWords);
            else search(board, searchWords, foundWords);

            VVC presentWords = {
                vc("abe"),
                vc("abef"),
                vc("abeh"),
                vc("abed"),
                vc("ade"),
                vc("adeb"),
                vc("adef"),
                vc("adeh"),
            };

            std::sort(foundWords.begin(), foundWords.end());
            std::sort(presentWords.begin(), presentWords.end());

            std::cout << "FOUND: ";
            printVVC(foundWords);
            std::cout << "PRESENT: ";
            printVVC(presentWords);

            assert(foundWords == presentWords);
        }
        {
            VVC board = {
                vc("gusxbcfcuj"),
                vc("juqgcgwwis"),
                vc("xmgozmemku"),
                vc("xlgcjiwaho"),
                vc("lqghwzrvnc"),
                vc("ylaaxaopnx"),
                vc("secgxiscul"),
                vc("mojhefzitd"),
                vc("maehnbasiw"),
                vc("qzunlgrhac"),
            };

            VVC searchWords = {
                vc("isculdwcahrgbfzasiti"),
                vc("gmewwis"),
                vc("gmemkiww"),
                vc("qzueammojhgcesylxlgcjizaixxwhgqlaa"),
                vc("qgggacgxiscul"),
                vc("cahrglnuzq"),
                vc("nonexistent"),
            };

            VVC foundWords;

            if (PRINT_2) searchPrint(board, searchWords, foundWords);
            else search(board, searchWords, foundWords);

            VVC presentWords = {
                vc("isculdwcahrgbfzasiti"),
                vc("gmewwis"),
                vc("gmemkiww"),
                vc("qzueammojhgcesylxlgcjizaixxwhgqlaa"),
                vc("qgggacgxiscul"),
                vc("cahrglnuzq")};

            std::sort(foundWords.begin(), foundWords.end());
            std::sort(presentWords.begin(), presentWords.end());

            std::cout << "FOUND: ";
            printVVC(foundWords);
            std::cout << "PRESENT: ";
            printVVC(presentWords);

            assert(foundWords == presentWords);
        }
    }
}

#undef PRINT_1
#undef PRINT_2