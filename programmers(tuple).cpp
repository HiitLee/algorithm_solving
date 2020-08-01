#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <sstream>
#include <set>
using namespace std;

vector<int> map[101];

bool compare(vector<int> a, vector<int> b) {
	return a.size() < b.size();
}
vector<int> solution(string s) {
    vector<int> answer;
    string c;
	bool flag = false;
	vector<vector<int>> v;
	vector<int> tempM;
	string sb = "";
	for (int i = 1; i < s.size() - 1; i++) {
		if (s[i] == '{') {
			flag = true;
		}
		else if (flag == true) {
			sb += s[i];
			if (s[i] == ',' || s[i] =='}') {	
				tempM.push_back(stoi(sb));
				sb = "";
			}
			
		}
		if (s[i] == '}') {
			v.push_back(tempM);
			while (!tempM.empty())
				tempM.pop_back();
			flag = false;
		}

		if (s[i] == ',')
			continue;
	}
	
	set<int> ss;
	sort(v.begin(), v.end(), compare);

	for (auto e : v) {
		for (auto ee : e) {
			if (ss.find(ee) == ss.end()) {
				ss.insert(ee);
				answer.push_back(ee);
			}
		}
	}
	return answer;
}