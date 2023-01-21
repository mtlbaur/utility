This folder contains a few utility function applications:
- `rng.cpp` simply generates a matrix of random alphabetical letters via `rng.h` and `rng.cpp`.
- `fibonacci_sequence.cpp`, `power_set.cpp`, and `n-queens.cpp` show `test.h` used to verify the results and compare runtimes of variations of the following algorithmic operations:
    - Computing the nth [Fibonacci number](https://en.wikipedia.org/wiki/Fibonacci_number)
    - Computing the [power set](https://en.wikipedia.org/wiki/Power_set) of a set.
    - Finding all possible solutions to the [n-queens](https://en.wikipedia.org/wiki/Eight_queens_puzzle) puzzle.
- `word_search.cpp` solves [word search](https://en.wikipedia.org/wiki/Word_search) problems via `trie.h` and recursion.
    - It has an additional printing function that generates the search output shown in `word_search_example_output.txt`.
        - This file shows the state of the board and trie after each found word.
    - The trie printing is handled by the trie itself: see the `write()` function in `trie.h`.