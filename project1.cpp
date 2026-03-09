// Snake and Ladder Game in C++ with DSA concepts, path analysis, and multiplayer support
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>
#include <limits>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h> 
#endif

using namespace std;

const int N = 100;


const int COLOR_DEFAULT = 7;
const int COLOR_PLAYER = 14;
const int COLOR_SNAKE = 12;
const int COLOR_LADDER = 10;
const int COLOR_BOARD = 11;
const int COLOR_NUMBER = 15;

class Player {
public:
    string name;
    int position;
    char symbol;
    int color;
    vector<int> moveHistory;

    Player(string n, char s, int c) : name(n), position(1), symbol(s), color(c) {}
};

class SnakeAndLadder {
private:
    vector<Player> players;
    unordered_map<int, int> snakes, ladders;
    vector<int> adjacencyList[N + 1];
    vector<int> shortestPath;
    mt19937 rng;
    bool gameOver = false;
    int winnerIdx = -1;

#ifdef _WIN32
    void setConsoleColor(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }
#else
    void setConsoleColor(int color) {
        const char* colors[] = {
            "\033[0m", "\033[31m", "\033[32m", "\033[33m",
            "\033[34m", "\033[35m", "\033[36m", "\033[37m"
        };
        cout << colors[color % 8];
    }
#endif

    void initializeBoard() {
        snakes = {
            {99, 54}, {70, 55}, {52, 42}, {25, 2}, {95, 72},
            {16, 6}, {47, 26}, {49, 11}, {56, 53}, {62, 19}, {64, 60}, {87, 24}, {93, 73}, {98, 78}
        };

        ladders = {
            {6, 25}, {11, 40}, {60, 85}, {46, 90}, {17, 69},
            {1, 38}, {4, 14}, {9, 31}, {21, 42}, {28, 84}, {36, 44}, {51, 67}, {71, 91}, {80, 100}
        };

        for (int i = 1; i < N; ++i) {
            for (int dice = 1; dice <= 6; ++dice) {
                int next = i + dice;
                if (next > N) continue;
                if (snakes.count(next)) next = snakes[next];
                else if (ladders.count(next)) next = ladders[next];
                adjacencyList[i].push_back(next);
            }
        }
        shortestPath = findShortestPath();
    }

    vector<int> findShortestPath() {
        vector<int> parent(N + 1, -1);
        vector<bool> visited(N + 1, false);
        queue<int> q;

        q.push(1);
        visited[1] = true;

        while (!q.empty()) {
            int curr = q.front(); q.pop();
            for (int neighbor : adjacencyList[curr]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    parent[neighbor] = curr;
                    q.push(neighbor);
                    if (neighbor == 100) {
                        vector<int> path;
                        for (int at = 100; at != -1; at = parent[at])
                            path.push_back(at);
                        reverse(path.begin(), path.end());
                        return path;
                    }
                }
            }
        }
        return {};
    }

public:
    SnakeAndLadder() : rng(chrono::steady_clock::now().time_since_epoch().count()) {
        initializeBoard();
    }

    void setColor(int color) {
        setConsoleColor(color);
    }

    void addPlayer(string name, char symbol, int color) {
        players.emplace_back(name, symbol, color);
    }

    int rollDice() {
        uniform_int_distribution<int> dist(1, 6);
        return dist(rng);
    }

    void movePlayer(Player &player, int diceValue) {
        int newPos = player.position + diceValue;
        if (newPos > 100) {
            setColor(COLOR_NUMBER);
            cout << player.name << " needs exact roll to reach 100. Skipped.\n";
            setColor(COLOR_DEFAULT);
            return;
        }

        setColor(player.color);
        cout << player.name << " rolled a " << diceValue << ". ";

        if (snakes.count(newPos)) {
            cout << "Bitten by snake! " << newPos << " -> " << snakes[newPos] << "\n";
            newPos = snakes[newPos];
        } else if (ladders.count(newPos)) {
            cout << "Climbed ladder! " << newPos << " -> " << ladders[newPos] << "\n";
            newPos = ladders[newPos];
        } else {
            cout << "Moved to " << newPos << "\n";
        }

        player.position = newPos;
        player.moveHistory.push_back(newPos);

        if (player.position == 100) {
            gameOver = true;
            winnerIdx = &player - &players[0];
            setColor(COLOR_PLAYER);
            cout << "\n" << player.name << " wins the game! \n";
            setColor(COLOR_DEFAULT);
        }
    }

    void startGame() {
        if (players.empty()) {
            cout << "Add players before starting game.\n";
            return;
        }

        while (!gameOver) {
            for (auto &player : players) {
                if (gameOver) break;
                setColor(player.color);
                cout << "\n" << player.name << "'s turn. Press Enter to roll the dice...";
                setColor(COLOR_DEFAULT);
                cin.ignore();

                int dice = rollDice();
                movePlayer(player, dice);
            }
        }
        displaySummary();
    }

    void displaySummary() {
        cout << "\n\n=== GAME SUMMARY ===\n";
        for (const auto &player : players) {
            setColor(player.color);
            cout << player.name << "'s Path: ";
            for (int pos : player.moveHistory) cout << pos << " -> ";
            cout << "End\n";
        }
        setColor(COLOR_NUMBER);
        cout << "\n Optimal path requires " << shortestPath.size() - 1 << " moves.\n";
        setColor(COLOR_DEFAULT);
    }
};

int main() {
    SnakeAndLadder game;
    int numPlayers;

    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif

    game.setColor(COLOR_BOARD);
    cout << "\n******** WELCOME TO SNAKE AND LADDER GAME ********\n\n";
    game.setColor(COLOR_DEFAULT);

    cout << "Enter number of players (1-4): ";
    cin >> numPlayers;
    cin.ignore();

    if (numPlayers < 1 || numPlayers > 4) {
        cout << "Invalid player count. Exiting.\n";
        return 1;
    }

    int colors[] = {COLOR_PLAYER, 11, 13, COLOR_LADDER};
    for (int i = 0; i < numPlayers; ++i) {
        string name;
        cout << "Enter name for player " << i + 1 << ": ";
        getline(cin, name);
        game.addPlayer(name, 'A' + i, colors[i]);
    }

    game.startGame();
    return 0;
}
