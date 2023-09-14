#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

const int al = 200;
vector<int> p, c, cnt(al);
int n, len, stage = 0;

bool cmp(int j, int k) {
	return c[j] < c[k] || c[j] == c[k] && c[(j + len) % n] < c[(k + len) % n];
}

//функция, которая пересчитывает массив классов эквивалентности
vector<int> getC() {
	int k = 0; //номер класса эквивалентности
	vector<int> new_c(n);
	new_c[p[0]] = 0;
	for (int i = 1; i < n; ++i) {
		if (cmp(p[i - 1], p[i]) != cmp(p[i], p[i - 1])) k++;
		new_c[p[i]] = k;
	}
	return new_c;
}

int main() {
	setlocale(LC_ALL, "ru");
	cout << "Введите строку" << endl;
	string s;
	cin >> s;
	s += "#";
	n = s.size();
	p.resize(n);
	c.resize(n);
	//получение первой перестановки сортировкой подсчетом
	for (int i = 0; i < n; ++i)
		cnt[s[i]]++;
	for (int i = 1; i < al; ++i)
		cnt[i] += cnt[i - 1];
	for (int i = 0; i < n; ++i)
		p[--cnt[s[i]]] = i;
	int k = 0;
	len = 1;
	c[p[0]] = 0;
	for (int i = 1; i < n; ++i) {
		if (s[p[i - 1]] != s[p[i]]) k++;
		c[p[i]] = k;
	}
	while (len < n) {
		vector<int> pn(n);
		for (int i = 0; i < n; ++i) {
			pn[i] = p[i] - (1 << stage);
			if (pn[i] < 0) pn[i] += n;
		}
		cnt.assign(n, 0);
		for (int i = 0; i < n; ++i)
			cnt[c[pn[i]]]++;
		for (int i = 1; i < n; ++i)
			cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; --i)
			p[--cnt[c[pn[i]]]] = pn[i];
		c = getC();
		stage++;
		len *= 2;
	}
	cout << "Введите количество запросов" << endl;
	int q;
	cin >> q;
	while (q--) {
		string x;
		cin >> x;
		int l = 0, r = n;
		bool flag = false;
		while (r > l + 1) {
			int j, m = (l + r) / 2;
			flag = true;
			for (j = 0; j < x.size() && s[(p[m] + j) % n] != '#'; ++j) {
				if (s[(p[m] + j) % n] < x[j]) {
					l = m;
					flag = false;
					break;
				}
				if (s[(p[m] + j) % n] > x[j]) {
					r = m;
					flag = false;
					break;
				}
			}
			if (flag && j < x.size()) {
				l = m;
			}
			else if (flag) {
				cout << "Строка содержится на позиции " << p[m] + 1 << endl;
				flag = true;
				break;
			}
		}
		if (!flag)
			cout << "Строка не содержится в тексте" << endl;
	}
}
/*
aabacbacabbcc
12
b
cb
aabac
abbcc
cbaca
aabacbacabbcc
abac
acbac
acabb
aac
bab
d

*/