#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <iostream>

using namespace std;

vector<string> answer;
int main() {
	vector<string> record = { "Enter uid1234 Muzi", "Enter uid4567 Prodo","Leave uid1234","Enter uid1234 Prodo","Change uid4567 Ryan" };
	stringstream spt;
	map<string, string> m;
	vector<pair<string,string>> v;
	string motion, id, name;
	for (auto& e : record) {
		spt.str(e);
		spt >> motion;
		spt >> id;
		spt >> name;
		cout << motion << " " << id << " " << name << " " << endl;
		if (motion == "Enter") {
			m[id] = name;
			v.push_back({id, "´ÔÀÌ µé¾î¿Ô½À´Ï´Ù." });
		}
		else if (motion == "Leave") {
			v.push_back({ id,"´ÔÀÌ ³ª°¬½À´Ï´Ù." });
		}
		else if (motion == "Change") {
			m[id] = name;
		}
		spt.clear();
	}
	string temp = "";
	for (int i = 0; i < v.size(); i++) {
		temp = m[v[i].first] + v[i].second;
		cout << temp << endl;
		answer.push_back(temp);
	}
}