#include <print.h>
#include <rng.h>

int main() {
    Utility::RNG rng;
    const int size = 10;

    const auto c = [&]() { return char(rng.I('a', 'z')); };

    const auto row = [&]() {
        std::vector<char> row;
        row.reserve(size);

        for (int i = 0; i < size; i++) row.emplace_back(c());

        return row;
    };
    const auto rows = [&]() {
        std::vector<std::vector<char>> rows;
        rows.reserve(size);

        for (int i = 0; i < size; i++) rows.emplace_back(row());

        return rows;
    };

    std::vector<std::vector<char>> board = rows();

    Utility::println(board);
}