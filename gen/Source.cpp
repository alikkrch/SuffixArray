#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>
using namespace std;

int rng(int l, int r) {
	return l + rand() % (r - l + 1);
}

string gen(int n) {
	string s;
	s.resize(n);
	for (int i = 0; i < n; ++i) {
		s[i] = rng('a', 'e');
	}
	return s;
}

int main() {
	freopen("input.txt", "w", stdout);
	srand(time(NULL));
	int n;
	//cin >> n;

	vector<string> t(10);
	for (int i = 0; i < 10; ++i) {
		string s(20, rng('a', 'f'));
		t[i] = s;
	}
	for (int i = 0; i < 5000; ++i) {
		cout << t[rng(0, 9)];
	}
}