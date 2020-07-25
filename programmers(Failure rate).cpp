#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

vector<pair<double, int>> ww;

bool compare(pair<double, int> a, pair<double, int> b) {
	if (a.first == b.first)
		return a.second < b.second;
	return a.first > b.first;

}

vector<int> solution(int N, vector<int> stages) {
	vector<int> answer;
	map<double, double> m;
	for (int i = 0; i < stages.size(); i++) {
		m[stages[i]] += 1;
	}
	int sum = 0;
	for (auto& e : m) {
		sum += e.second;
	}

	for (int i = 1; i <= N; i++) {
		double point;
		if (sum == 0) {
			point = 0;
		}
		else {
			point = m[i] / sum;
		}
		ww.push_back({ point, i });
		sum -= m[i];
	}
	sort(ww.begin(), ww.end(), compare);

	for (auto& e : ww)
		answer.push_back(e.second);
	return answer;
}