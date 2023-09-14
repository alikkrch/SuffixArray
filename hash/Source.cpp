#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
using namespace std;

string s;
int n;
const long long mod = pow(2, 64), P = 307;
vector<long long> h, pw;

long long Hash(int l, int r) {
	return (h[r] + mod - (l ? h[l - 1] : 0)) % mod * pw[n - l] % mod;
}

int lcp(int j, int k) {
	int m = min(n - j, n - k), l = 0, r = m;
	while (r > l + 1) {
		int mid = (l + r) / 2;
		if (Hash(j, j + mid - 1) == Hash(k, k + mid - 1)) {
			l = mid;
		}
		else {
			r = mid;
		}
	}
	return l;
}

bool cmp(int j, int k) {
	int x = lcp(j, k);
	return s[j + x] < s[k + x] || s[j + x] == s[k + x] && j > k;
}

int main() {
	setlocale(LC_ALL, "ru");
	int start_time = clock();

	fstream fin("input.txt");
	fin >> s;
	n = s.size();
	h.resize(n);
	pw.resize(n + 1);

	pw[0] = 1;
	for (int i = 1; i <= n; ++i)
		pw[i] = pw[i - 1] * P % mod;

	h[0] = s[0];
	for (int i = 1; i < n; ++i) {
		h[i] = h[i - 1] + pw[i] * s[i];
		h[i] %= mod;
	}
	vector<int> p(n);
	for (int i = 0; i < n; ++i)
		p[i] = i;
	sort(p.begin(), p.end(), cmp);

	/*cout << "Суффиксы в порядке возрастания: " << endl;
	for (int i = 0; i < n; ++i) {
		for (int j = p[i]; j < n; ++j) {
			cout << s[j];
		}
		cout << endl;
	}*/
	int end_time = clock();
	cout << "Время работы: " << (end_time - start_time) / 1000.;
}