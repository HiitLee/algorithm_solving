#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
using namespace std;

int column, row;
vector<string> combination;

bool compare(string a, string b) {
	if (a.size() != b.size())
		return a.size() < b.size();
	return a < b;
}
void Combination(int k=0, string temp="") {
	for (int i = k; i < column; i++) {
		temp += to_string(i);
		combination.push_back(temp);
		Combination(i + 1, temp);
		temp = temp.substr(0, temp.length() - 1);
	}
}

bool checkUM(vector<vector<string>> relation, string combi) {
	set<string> tempSet;
	for (int i = 0; i < row; i++) {
		string temp = "";
		for (int j = 0; j < combi.size(); j++) {
			int num = combi[j] - '0';
			temp += relation[i][num];
		}
		tempSet.insert(temp);
	}
	if (tempSet.size() == row)
		return true;
	else
		return false;
}
int solution(vector<vector<string>> relation) {
    int answer = 0;
    row = relation.size();
	column = relation[0].size();
	Combination(0, "");
	sort(combination.begin(), combination.end(), compare);
	//각 조합에 대해 유일성, 최소성 체크
	for (int i = 0; i < combination.size(); i++) {
		if (checkUM(relation, combination[i])) {
			string temp = combination[i];
			for (int k = combination.size() - 1; k >= i; k--) {
				bool check = true;
				for (auto e : temp) {
					if (combination[k].find(e) == string::npos) {
						check = false;
						break;
					}
				}
				if (check)
					combination.erase(combination.begin()+k);
			}
			i--;
			answer++;
		}
		//cout << "111cycle11 " << endl;
	}

    return answer;
}