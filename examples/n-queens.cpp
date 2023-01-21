#include <vector>
#include <string>

#include <test.h>

namespace NQueens {
    using Board  = std::vector<std::string>;
    using Boards = std::vector<Board>;

    namespace v1 {
        Boards boards(int n) {
            std::vector<std::pair<int, int>> placed;
            Boards boards;

            const auto dfs = [&](const auto& dfs, int i) -> void {
                if (i < n) {
                    for (int j = 0; j < n; j++) {
                        for (const auto& [qi, qj] : placed) {
                            if (j == qj || abs(qi - i) == abs(qj - j)) goto skip;
                        }

                        placed.emplace_back(std::pair(i, j));

                        dfs(dfs, i + 1);

                        placed.pop_back();

                    skip:;
                    }
                } else {
                    boards.emplace_back(Board());

                    for (const auto& [i, j] : placed) {
                        boards.back().emplace_back(std::string(n, '-'));
                        boards.back().back()[j] = '+';
                    }
                }
            };

            dfs(dfs, 0);

            return boards;
        }
    } // namespace v1

    namespace v2 {
        Boards boards(int n) {
            std::vector<std::pair<int, int>> placed;
            Boards boards;
            unsigned placedCols = 0;

            const auto dfs = [&](const auto& dfs, int i) -> void {
                if (i < n) {
                    for (int j = 0; j < n; j++) {
                        if (placedCols >> j & 1) continue;

                        for (const auto& [qi, qj] : placed) {
                            if (abs(qi - i) == abs(qj - j)) goto skip;
                        }

                        placed.emplace_back(std::pair(i, j));
                        placedCols ^= 1 << j;

                        dfs(dfs, i + 1);

                        placedCols ^= 1 << j;
                        placed.pop_back();

                    skip:;
                    }
                } else {
                    boards.emplace_back(Board());

                    for (const auto& [i, j] : placed) {
                        boards.back().emplace_back(std::string(n, '-'));
                        boards.back().back()[j] = '+';
                    }
                }
            };

            dfs(dfs, 0);

            return boards;
        }
    } // namespace v2
} // namespace NQueens

int main() {
    using Boards  = NQueens::Boards;
    using FncType = decltype(NQueens::v1::boards);

    Utility::Functions<FncType> vf{
        NQueens::v1::boards,
        NQueens::v2::boards,
    };

    {
        Utility::Tests<Boards, int> vt{
            {{
                 {
                     "+",
                 },
             },
             {
                 1,
             }},
            {{

             },
             {
                 2,
             }},
            {{

             },
             {
                 3,
             }},
            {{{
                  "-+--",
                  "---+",
                  "+---",
                  "--+-",
              },
              {
                  "--+-",
                  "+---",
                  "---+",
                  "-+--",
              }},
             {
                 4,
             }},
            {{{
                  "+----",
                  "--+--",
                  "----+",
                  "-+---",
                  "---+-",
              },
              {
                  "+----",
                  "---+-",
                  "-+---",
                  "----+",
                  "--+--",
              },
              {
                  "-+---",
                  "---+-",
                  "+----",
                  "--+--",
                  "----+",
              },
              {
                  "-+---",
                  "----+",
                  "--+--",
                  "+----",
                  "---+-",
              },
              {
                  "--+--",
                  "+----",
                  "---+-",
                  "-+---",
                  "----+",
              },
              {
                  "--+--",
                  "----+",
                  "-+---",
                  "---+-",
                  "+----",
              },
              {
                  "---+-",
                  "+----",
                  "--+--",
                  "----+",
                  "-+---",
              },
              {
                  "---+-",
                  "-+---",
                  "----+",
                  "--+--",
                  "+----",
              },
              {
                  "----+",
                  "-+---",
                  "---+-",
                  "+----",
                  "--+--",
              },
              {
                  "----+",
                  "--+--",
                  "+----",
                  "---+-",
                  "-+---",
              }},
             {
                 5,
             }},
        };

        Utility::test(vf, vt);
    }

    {
        Utility::Tests<void, int> vt{
            {{
                10,
            }},
        };

        Utility::runtime(vf, vt, 100);
    }
}