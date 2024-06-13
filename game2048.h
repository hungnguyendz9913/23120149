#ifndef GAME2048
#define GAME2048

#include <iostream>
#include "constant.h"
#include "vector.h"

using namespace std;

class game2048 {
public:
	int* board;
	int score;
	int step;

	game2048() {
		score = 0;
		step = 0;
		board = new int[SIZE * SIZE];
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				board[i * SIZE + j] = 0;
			}
		}

		addRandomTile();
		addRandomTile();
	}

	game2048(const game2048 &other) {
		this->score = other.score;
		this->step = other.step;
		this->board = new int[SIZE * SIZE];
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				this->board[i * SIZE + j] = other.board[i * SIZE + j];
			}
		}
	}

	game2048& operator = (const game2048& other) {
		if (this != &other) {
			delete[] board;
			this->score = other.score;
			this->step = other.step;
			this->board = new int[SIZE * SIZE];
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					this->board[i * SIZE + j] = other.board[i * SIZE + j];
				}
			}
		}

		return *this;
	}

	bool isLosing() {
		bool col = false;
		for (int i = 1; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				if (board[i * SIZE + j] == board[(i - 1) * SIZE + j] || board[i * SIZE + j] == 0 || board[(i - 1) * SIZE + j] == 0)
					col = true;
			}
		}

		bool row = false;
		for (int i = 0; i < SIZE; i++) {
			for (int j = 1; j < SIZE; j++) {
				if (board[i * SIZE + j] == board[i * SIZE + j - 1])
					row = true;
			}
		}

		return !(row || col);
	}

	bool isWinning() {
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				if (board[i * SIZE + j] >= 2048) return true;
			}
		}
		return false;
	}

	bool Up() {
		return moveUp();
	}

	bool Down() {
		return moveDown();
	}

	bool Left() {
		return moveLeft();
	}

	bool Right() {
		return moveRight();
	}

	bool Inactive() {
		return false;
	}

	bool Achieved() {
		return true;
	}

	bool moving(bool (game2048::* revise)()) {
		bool moved = (this->*revise)();
		if (moved) {
			step++;
			addRandomTile();
			addRandomTile();
		}
		return moved;
	}

private:
	void addRandomTile() {
		vectorh<int> emptyTiles;
		for (int i = 0; i < SIZE; ++i) {
			for (int j = 0; j < SIZE; ++j) {
				if (board[i * SIZE + j] == 0) {
					emptyTiles.push_back(i * SIZE + j);
				}
			}
		}

		if (!emptyTiles.empty()) {
			int index = getRandomNumber(0, emptyTiles.size());
			board[emptyTiles[index]] = getRandomNumber(0, 2) * 2 + 2;
		}
	}

	void addNumber(int i, int j) {
		board[i] += board[j];
		board[j] = 0;
	}

	void swapNumber(int i, int j) {
		int temp = board[i];
		board[i] = board[j];
		board[j] = temp;
	}

	bool moveUp() {
		bool moved = false;

		for (int i = 0; i < SIZE; i++) {
			int val_prv = 0;
			int j_prv = 0;
			for (int j = 0; j < SIZE; j++) {
				if (board[i * SIZE + j] != 0) {
					if (board[i * SIZE + j] == val_prv) {
						moved = true;
						addNumber(i * SIZE + j_prv, i * SIZE + j);
						score += board[i * SIZE + j_prv];
						j_prv++;
						val_prv = 0;
						continue;
					}

					if (val_prv == 0) {
						if (j != j_prv) moved = true;
						val_prv = board[i * SIZE + j];
						swapNumber(i * SIZE + j, i * SIZE + j_prv);
						continue;
					}

					if (board[i * SIZE + j] != val_prv) {
						if (j != j_prv) moved = true;
						val_prv = board[i * SIZE + j];
						j_prv++;
						swapNumber(i * SIZE + j, i * SIZE + j_prv);
						continue;
					}
				}
			}
		}

		return moved;
	}

	bool moveDown() {
		bool moved = false;

		for (int i = 0; i < SIZE; i++) {
			int val_prv = 0;
			int j_prv = SIZE - 1;
			for (int j = SIZE - 1; j >= 0; j--) {
				if (board[i * SIZE + j] != 0) {
					if (board[i * SIZE + j] == val_prv) {
						moved = true;
						addNumber(i * SIZE + j_prv, i * SIZE + j);
						score += board[i * SIZE + j_prv];
						j_prv--;
						val_prv = 0;
						continue;
					}

					if (val_prv == 0) {
						if (j != j_prv) moved = true;
						val_prv = board[i * SIZE + j];
						swapNumber(i * SIZE + j, i * SIZE + j_prv);
						continue;
					}

					if (board[i * SIZE + j] != val_prv) {
						if (j != j_prv) moved = true;
						val_prv = board[i * SIZE + j];
						j_prv--;
						swapNumber(i * SIZE + j, i * SIZE + j_prv);
						continue;
					}
				}
			}
		}

		return moved;
	}

	bool moveLeft() {
		bool moved = false;

		for (int j = 0; j < SIZE; j++) {
			int val_prv = 0;
			int i_prv = 0;
			for (int i = 0; i < SIZE; i++) {
				if (board[i * SIZE + j] != 0) {
					if (board[i * SIZE + j] == val_prv) {
						moved = true;
						addNumber(i_prv * SIZE + j, i * SIZE + j);
						score += board[i_prv * SIZE + j];
						i_prv++;
						val_prv = 0;
						continue;
					}

					if (val_prv == 0) {
						if (i != i_prv) moved = true;
						val_prv = board[i * SIZE + j];
						swapNumber(i_prv * SIZE + j, i * SIZE + j);
						continue;
					}

					if (board[i * SIZE + j] != val_prv) {
						if (i != i_prv) moved = true;
						val_prv = board[i * SIZE + j];
						i_prv++;
						swapNumber(i_prv * SIZE + j, i * SIZE + j);
						continue;
					}
				}
			}
		}

		return moved;
	}

	bool moveRight() {
		bool moved = false;

		for (int j = 0; j < SIZE; j++) {
			int val_prv = 0;
			int i_prv = SIZE - 1;
			for (int i = SIZE - 1; i >= 0; i--) {
				if (board[i * SIZE + j] != 0) {
					if (board[i * SIZE + j] == val_prv) {
						moved = true;
						addNumber(i_prv * SIZE + j, i * SIZE + j);
						score += board[i_prv * SIZE + j];
						i_prv--;
						val_prv = 0;
						continue;
					}

					if (val_prv == 0) {
						if (i != i_prv) moved = true;
						val_prv = board[i * SIZE + j];
						swapNumber(i_prv * SIZE + j, i * SIZE + j);
						continue;
					}

					if (board[i * SIZE + j] != val_prv) {
						if (i != i_prv) moved = true;
						val_prv = board[i * SIZE + j];
						i_prv--;
						swapNumber(i_prv * SIZE + j, i * SIZE + j);
						continue;
					}
				}
			}
		}

		return moved;
	}
};

//void moving(game2048 game);

#endif // !BOARDGAME
