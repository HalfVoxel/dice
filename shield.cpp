#include <cstdio>
#include <cstdlib>
#include <ctime>

#define rep(i, a, b) for(int i=a; i<b; i++)

int grid[3][5]; //Spelbräde. 0: tomt. 1: AI. 2: random
int filled = 0; //Antal fyllda rutor.

//Låt spel
int move(int y, int x, int player) {
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

bool random_move() {
	int r;
	do {
		r = rand()%15;
	} while(grid[r/5][r%3] != 0);

	int res = move(r/5, r%5, 2);

	if(grid[0][0] == 2) {
		return false;
	} else {
		return true;
	}
}

bool ai_move() {
	return random_move();
}

bool play() {
	//Nollställ brädet
	rep(i, 0, 3) {
		rep(j, 0, 5) {
			grid[i][j] = 0;
		}
	}
	filled = 0;

	int turn = rand()%2;
	while(filled < 15) {
		if(turn == 0) {
			if(!random_move()) {
				printf("AI vinner\n");
				return true;
			}
		}
		else {
			if(!ai_move()) {
				printf("Slumpspelaren vinner\n");
				return false;
			}
		}

		turn = (turn+1)%2;
	}
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

	printf("AI andel vinster: %f\n", ((float)c)/((float)n));
	return 0;
}
