#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>
#include <fstream>
using namespace std;

string s;
int n;

bool cmp(int j, int k) {
	int i = 0;
	while (max(j, k) + i < n) {
		if (s[j + i] < s[k + i])
			return true;
		if (s[j + i] > s[k + i])
			return false;
		i++;
	}
	return j > k;
}

int main() {
	setlocale(LC_ALL, "ru");
	int start_time = clock();

	fstream fin("input.txt");
	fin >> s;
	n = s.size();
	cout << n << endl;
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