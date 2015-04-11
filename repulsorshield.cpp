#include <bits/stdc++.h>
using namespace std;
 
#define rep(i, a, b) for(int i = a; i < int(b); i++)
#define trav(it, v) for(auto it = v.begin(); it != v.end(); it++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x).size()
 
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi; 

int dp[5][5][5];
pair<int, int> move[5][5][5];

int solve(int a, int b, int c) {
	if(dp[a][b][c] != -1) return dp[a][b][c];
	if(a == 0 && b == 0 && c == 0) return 1;
	if(a == 1 && b == 0 && c == 0) return 0;
	int ret = 0;
	int state[3] = {a, b, c};
	bool done = true;
	for(int y = 0; y < 3; y++) { // Search for winning move
		for(int x = 0; x < state[y]; x++) {
			int newState[3] = {a, b, c};
			for(int i = y; i < 3; i++) {
				newState[i] = min(x, state[i]);
			}
			if(solve(newState[0], newState[1], newState[2]) == 0) { // Winning move found
				ret = 1;
				move[a][b][c] = make_pair(x, y);
				done = true;
				break;
			}
		}
		if(done) break;
	}
	if(ret == 0) { // If no winning move exists, make random move
		int y = rand()%3;
		while(state[y] == 0) y = rand()%3;
		int x = rand()%state[y];
		move[a][b][c] = make_pair(x, y);
	} 
	return dp[a][b][c] = ret;
}

pair<int, int> makeMove(char[][]& grid) {
	int a = 0, b = 0, c = 0;
	for(; grid[0][a] == '0' && a < 5; a++);
	for(; grid[0][b] == '0' && b < 5; b++);
	for(; grid[0][c] == '0' && c < 5; c++);
	a++;b++;c++;
	solve(a, b, c);
	return move[a][b][c];
}

int main() {
}

