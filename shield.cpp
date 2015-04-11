#include <cstdio>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#define rep(i, a, b) for(int i=a; i<b; i++)

using namespace std;

int grid[3][5]; //Spelbräde. 0: tomt. 1: AI. 2: random
int filled = 0; //Antal fyllda rutor.

int dp[6][6][6];
pair<int, int> movearr[6][6][6];

int solve(int a, int b, int c) {
	if(dp[a][b][c] != -1) return dp[a][b][c];
	if(a == 0 && b == 0 && c == 0) return 1;
	if(a == 1 && b == 0 && c == 0) return 0;
	int ret = 0;
	int state[3] = {a, b, c};
	bool done = false;
	for(int y = 0; y < 3; y++) { // Search for winning move
		for(int x = 0; x < state[y]; x++) {
			int newState[3] = {a, b, c};
			for(int i = y; i < 3; i++) {
				newState[i] = min(x, state[i]);
			}
			if(solve(newState[0], newState[1], newState[2]) == 0) { // Winning move found
				ret = 1;
				movearr[a][b][c] = make_pair(x, y);
				done = true;
				break;
			}
		}
		if(done) break;
	}
	if(ret == 0) { // If no winning move exists, make random move
		int x, y;
		do {
			y = rand()%3;
			while(state[y] == 0) y = rand()%3;
			x = rand()%state[y];
			movearr[a][b][c] = make_pair(x, y);
		} while(x == 0 && y == 0);
	}
	return dp[a][b][c] = ret;
}

pair<int, int> makeMove() {
	int a = 0, b = 0, c = 0;
	for(; grid[0][a] == 0 && a < 5; a++);
	for(; grid[1][b] == 0 && b < 5; b++);
	for(; grid[2][c] == 0 && c < 5; c++);
	solve(a, b, c);
	return movearr[a][b][c];
}

//Utför ett drag.
void move(int y, int x, int player) {
	int count = 0;
	rep(i, y, 3) {
		rep(j, x, 5) {
			if(grid[i][j] == 0) {
				filled++;
				count++;
				grid[i][j] = player;
			}
		}
	}
}

void random_move() {
	int r;
	do {
		r = rand()%15;
	} while(grid[r/5][r%5] != 0);

	move(r/5, r%5, 2);
}

void ai_move() {
	auto p = makeMove();
	move(p.second, p.first, 1);
}

void print_grid() {
	rep(i, 0, 3) {
		rep(j, 0, 5) {
			printf("%d", grid[i][j]);

		}
		printf("\n");
	}
	printf("\n");
}

bool play() {
	memset(dp, -1, sizeof(dp));

	//Nollställ brädet
	rep(i, 0, 3) {
		rep(j, 0, 5) {
			grid[i][j] = 0;
		}
	}
	filled = 0;

	int turn = rand()%2;
	while(filled <= 15) {
		if(grid[0][0]==1) {
			printf("Slumpspelaren vinner.\n");
			return false;
		} else if(grid[0][0] == 2) {
			printf("AI vinner.\n");
			return true;
		}

		if(turn == 0) {
			printf("Slumpdrag:\n");
			random_move();
		} else {
			printf("AI-drag:\n");
			ai_move();
		}

		print_grid();
		turn = (turn+1)%2;
	}
	assert(false);
	return false;
}

int main() {
	srand(time(0));

	printf("Antal spel?\n");
	int n;
	scanf("%d", &n);

	int c = 0;

	rep(i, 0, n) {
		if(play()){
			c++;
		}
	}

	printf("AI andel vinster: %d/%d = %f\n", c, n, ((float)c)/((float)n));
	return 0;
}
