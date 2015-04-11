#include <vector>
#include <map>
#include <iostream>

using namespace std;

struct Entry {
	string name;
	int cost;
	int prio;
	int avail;
	int counts;
	int origIndex;
};

int BUDGET = 10000;

int main () {

	int maxSum = 0;
	int maxCount = 0;
	string name;

	vector<Entry> entries;
	vector<Entry> origEntries;

	entries.push_back(Entry());
	while (cin >> name) {
		Entry e;
		e.counts = 0;

		while (!(cin >> e.cost)) {
			cin.clear();
			string s2;
			cin >> s2;
			name = name + " " + s2;
		}
		
		e.name = string(name);	
		e.origIndex = origEntries.size();
		origEntries.push_back(e);

		cin >> e.prio >> e.avail;

		for (int i = 0; i < e.avail; i++) {
			entries.push_back(e);
		}
		
		maxSum += e.cost * e.avail;
		maxCount += e.avail;

	}

	vector<vector<int> > buffer (maxSum+5, vector<int>(entries.size(), -1));
	vector<vector<int> > parent (maxSum+5, vector<int>(entries.size(), 0));
	buffer[0][0] = 0;

	for (int e = 1; e < entries.size(); e++) {
		for (int i = 0; i < maxSum; i++) {
			buffer[i][e] = buffer[i][e-1];
			if (i - entries[e].cost >= 0) {
				int prevScore = buffer[i-entries[e].cost][e-1];

				int newScore = prevScore + entries[e].prio;
				if (prevScore != -1 && newScore > buffer[i][e]) {
				 	buffer[i][e] = newScore;
				 	parent[i][e] = 1;
				 }
			}
		}
	}

	int mxIndex = 0;
	int mxEn = 0;
	//cout << maxSum << " " << BUDGET << endl;
	for (int i = 0; i <= min(maxSum, BUDGET); i++) {
		for (int j = 1; j < entries.size(); j++) {
			if (buffer[i][j] > buffer[mxIndex][mxEn]) {
				mxIndex = i;
				mxEn = j;
			}
		}
	}

	cout << mxIndex << " " << mxEn << " " << buffer[mxIndex][mxEn] << endl;

	while (mxIndex != -1) {
		//cout << mxIndex << endl;
		while (parent[mxIndex][mxEn] == 0 && mxEn >= 0) mxEn--;

		if (mxEn < 0) break;

		origEntries[entries[mxEn].origIndex].counts++;

 		mxIndex = mxIndex - entries[mxEn].cost;
 		mxEn--;
	}

	vector<pair<int,pair<int,int> > > result;

	for (int i = 0; i < origEntries.size(); i++) {
		if (origEntries[i].counts > 0) {
			result.push_back(pair<int,pair<int,int> >(origEntries[i].prio, pair<int,int>(origEntries[i].counts,i)));
		}
	}

	sort (result.begin(), result.end());

	for (int i = 0; i < result.size(); i++) {
		cout << origEntries[result[i].second.second].name << ": " << result[i].second.first << endl;
	}
}

