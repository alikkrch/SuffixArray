#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

const int al = 200;
vector<int> p, cnt(al);
vector<vector<int>> c;
int n, len, stage = 0;

bool cmp(int j, int k) {
	return c[stage][j] < c[stage][k] || c[stage][j] == c[stage][k] && c[stage][(j + len) % n] < c[stage][(k + len) % n];
}

void getC(vector<int>& new_c) {
	int k = 0; //номер класса эквивалентности
	new_c[p[0]] = 0;
	for (int i = 1; i < n; ++i) {
		if (cmp(p[i - 1], p[i]) != cmp(p[i], p[i - 1])) k++;
		new_c[p[i]] = k;
	}
}

int compare(int i, int j, int l, int k) {
	pair<int, int> a = make_pair(c[k][i], c[k][i + l - (1 << k)]);
	pair<int, int> b = make_pair(c[k][j], c[k][j + l - (1 << k)]);
	return a == b ? 0 : a < b ? -1 : 1;
}

int main() {
	freopen("substrcmp.in", "r", stdin); freopen("substrcmp.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	//setlocale(LC_ALL, "ru");
	//cout << "¬ведите строку" << endl;
	string s;
	cin >> s;
	n = s.size();
	p.resize(n);
	for (int i = 0; i < n; ++i) 
		cnt[s[i]]++;
	for (int i = 1; i < al; ++i) 
		cnt[i] += cnt[i - 1];
	for (int i = 0; i < n; ++i) 
		p[--cnt[s[i]]] = i;
	int k = 0;
	len = 1;
	c.push_back(vector<int>(n));
	c[0][p[0]] = 0;
	for (int i = 1; i < n; ++i) {
		if (s[p[i - 1]] != s[p[i]]) k++;
		c[0][p[i]] = k;
	}
	while (len < n) {
		vector<int> pn(n);
		for (int i = 0; i < n; ++i) {
			pn[i] = p[i] - (1 << stage);
			if (pn[i] < 0) pn[i] += n;
		}
		cnt.assign(n, 0);
		for (int i = 0; i < n; ++i)
			cnt[c[stage][pn[i]]]++;
		for (int i = 1; i < n; ++i)
			cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; --i)
			p[--cnt[c[stage][pn[i]]]] = pn[i];
		c.push_back(vector<int>(n));
		getC(c[stage + 1]);
		stage++;
		len *= 2;
	}
	//cout << "¬ведите количество запросов" << endl;
	int q;
	cin >> q;
	while (q--) {
		int a, b, c, d, pw = 1, k = 0;
		cin >> a >> b >> c >> d;
		a--; b--; c--; d--;
		int l1 = b - a + 1, l2 = d - c + 1, l = min(l1, l2);
		while (2 * pw < l) {
			pw *= 2;
			k++;
		}
		int res = compare(a, c, l, k);
		if (res == -1 || res == 0 && l1 < l2)
			cout << "No";
		else if (res == 1 || res == 0 && l1 > l2)
			cout << "No";
		else
			cout << "Yes";
		cout << endl;
	}
}

/*
trololo
3
1 7 1 7
3 5 5 7
1 1 1 5

abacbabbacb
7
1 10 1 10
1 1  3 3
2 5  8 11
1 3  6 8
2 4  5 7
4 6  10 11
2 4  8 11

eoeou

*/