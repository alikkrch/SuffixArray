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
	p.erase(p.begin(), p.begin() + 1);
	s.erase(s.size() - 1, 1);
	n--;
	cout << "Суффиксный массив: " << endl;
	for (int i = 0; i < n; ++i) {
		cout << p[i] << ' ';
	}
	vector<int> pos(n);
	for (int i = 0; i < n; ++i) {
		pos[p[i]] = i;
	}
	vector<int> lcp(n - 1);
	int l = 0; //текущая длина наибольшего общего префикса

	for (int i = 0; i < n; ++i) {
		if (l > 0)
			l--;
		if (pos[i] == n - 1)
			continue;
		int next = pos[i] + 1;
		int s_len = n - i; //длина рассматриваемого суффикса
		/*if (s_len <= l) {
			lcp[pos[i]] = s_len;
			continue;
		}*/
		int k = p[next]; //индекс в соседнем суффиксе
		//сравниваем соседние, начиная с l-ого
		while (max(i, k) < n && s[i + l] == s[k + l]) {
			l++;
		}
		lcp[pos[i]] = l;
	}
	cout << endl << "LCP: " << endl;
	for (int i = 0; i < n - 1; ++i) {
		cout << lcp[i] << ' ';
	}
}
/*abraabra

11
aabbcbabacb
1 7 2 9 11 6 8 3 4 10 5


*/