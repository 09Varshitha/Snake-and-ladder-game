Snake and Ladder Game – C++ (DSA Based)

This project is a console-based Snake and Ladder game developed in C++ that demonstrates the practical implementation of Data Structures and Algorithms (DSA) along with Object-Oriented Programming (OOP) concepts. The game supports multiple players (1–4) and simulates the classic board game experience in a terminal environment.

The core idea behind this project is to model the game board as a graph where each cell represents a node and possible dice moves represent edges. Using this structure, the program constructs an adjacency list to represent all possible moves on the board while accounting for snakes and ladders that change a player’s position.

A key feature of this project is the implementation of Breadth-First Search (BFS) to determine the shortest possible path from the starting position (1) to the final position (100). This allows the program to analyze the optimal route to complete the game, providing insights into how many minimum moves are theoretically required to win.

The game also includes random dice generation using the C++ random library, ensuring fair and unpredictable gameplay. Each player's moves are recorded using a move history tracker, which is displayed at the end of the game as a complete path summary. This allows players to review their progression through the board.

Additionally, the project uses console color formatting to improve user experience by visually distinguishing players, snakes, ladders, and game messages.

Key Features

Multiplayer support (1–4 players)

Random dice simulation

Snake and ladder board mechanics

Graph-based board representation

BFS algorithm for optimal path calculation

Move history tracking and game summary

Cross-platform console color support

This project demonstrates how DSA concepts such as graphs, BFS traversal, and adjacency lists can be applied to build an interactive game while strengthening problem-solving and programming skills in C++.
