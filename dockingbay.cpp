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
 
const int N = 8;

bool test(vi& a) {
	rep(i, 0, N) {
		rep(j, 0, N) {
			if(i == j) continue;
			if(i + a[i] == j + a[j]) return false;
			if(i - a[i] == j - a[j]) return false;
		}
	}
	return true;
}

int main() {
	vi a(N);
	rep(i, 0, N) a[i] = i;
	do {
		if(test(a)) {
			rep(i, 0, N) {
				rep(j, 0, N) {
					if(a[i] == j) cout << 'x';
					else cout << '.';
				}
				cout << endl;
			}
			return 0;
		}
	} while(next_permutation(all(a)));
}

