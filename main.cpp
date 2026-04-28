/*
I use iostream to allow inputs and outputs through the console. here are the docs: https://en.cppreference.com/cpp/header/iostream
I use vector to represent a list. Docs: https://en.cppreference.com/cpp/container/vector
Developed with cpp.sh
*/
#include <iostream>
#include <vector>

class game {
private:
    std::vector<char> grid = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

    bool filled() const {
        for (char i : grid) {
            if (i == ' ') return false;
        }
        return true;
    }

    int winner() const {
        const int wins[8][3] = {
            {0, 1, 2}, 
            {3, 4, 5},
            {6, 7, 8},
            {0, 3, 6}, 
            {1, 4, 7},
            {2, 5, 8},
            {0, 4, 8}
            {2, 4, 6}
        };

        for (const auto &w : wins) {
            char a = grid[w[0]];
            char b = grid[w[1]];
            char c = grid[w[2]];
            if (a != ' ' && a == b && b == c) {
                return (a == 'X') ? -1 : 1;
            }
        }

        if (!filled()) return 2;
        return 0;
    }


    int dfs(char player) {
        int w = winner();
        if (w != 2) return w; 
        int best = (player == 'X') ? 2 : -2;
        int current;

        for (int i = 0; i < 9; ++i) {
            if (grid[i] == ' ') {
                grid[i] = player;
                current = dfs(player == 'X' ? 'O' : 'X');
                grid[i] = ' ';

                if (player == 'X') {
                    if (current < best) best = current;
                } else {
                    if (current > best) best = current;
                }
            }
        }
        return best;
    }

public:
    int bestmoveO() {
        int bestIdx = -1;
        int bestScore = -2;

        for (int i = 0; i < 9; ++i) {
            if (grid[i] == ' ') {
                grid[i] = 'O';
                int score = dfs('X');
                grid[i] = ' ';

                if (score > bestScore) {
                    bestScore = score;
                    bestIdx = i;
                }
            }
        }
        return bestIdx;
    }

    bool playMove(int idx, char player) {
        if (idx < 0 || idx >= 9) return false;
        if (grid[idx] != ' ') return false;
        grid[idx] = player;
        return true;
    }

    void print() const {
        std::cout << "\n";
        for (int i = 0; i < 9; ++i) {
            char c = grid[i];
            std::cout << (c == ' ' ? char('0' + i + 1) : c);
            if (i % 3 != 2)
                std::cout << " | ";
            else if (i != 8)
                std::cout << "\n--+---+--\n";
        }
        std::cout << "\n\n";
    }

    int getWinner() const { return winner(); }
    bool isFilled() const { return filled(); }
};

int main() {
    game g;
    char human = 'X';
    char ai    = 'O';

    std::cout << "You are x, computer is 0\n";
    std::cout << "Enter pos: 1-9:\n";

    bool humanTurn = true;

    while (true) {
        g.print();

        int w = g.getWinner();
        if (w != 2) { 
            if (w == -1) std::cout << "X win\n";
            else if (w == 1) std::cout << "O win\n";
            else std::cout << "Tie\n";
            break;
        }

        if (humanTurn) {
            int pos;
            std::cout << "Move 1-9: ";
            std::cin >> pos;
            int idx = pos - 1;;
            if (!g.playMove(idx, human)) {
                std::cout << "Invalid\n";
                continue;
            }
        } else {
            int move = g.bestmoveO();
            if (move == -1) {
                break;
            }
            g.playMove(move, ai);
        }

        humanTurn = !humanTurn;
    }

    g.print();
    return 0;
}
