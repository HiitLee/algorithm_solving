#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

set<string> errorMap;
void dfs(int num, int eraseIdx, vector<string> user_id, vector<string> banned_id, int bIdx, vector<string> v) {
	
	if (eraseIdx != -1) {
		user_id.erase(user_id.begin() + eraseIdx);
	}
	if ( num== banned_id.size())
	{
		sort(v.begin(), v.end());
		string st = "";
		for (auto e : v)
			st += e;
		errorMap.insert(st);
		return;
	}
	for (int i = 0; i < user_id.size(); i++) {
		if (user_id[i].size() == banned_id[bIdx].size())
		{
			int temp = 0;
			for (int n = 0; n < user_id[i].size(); n++)
				if (user_id[i][n] == banned_id[bIdx][n] || banned_id[bIdx][n] == '*')
					temp++;
			if (user_id[i].size() == temp)
			{
				v.push_back(user_id[i]);
				dfs(num + 1,i, user_id, banned_id, bIdx + 1, v);
				v.pop_back();
				
			}
		}
	}
}
int solution(vector<string> user_id, vector<string> banned_id) {
    int answer = 0;
    vector<string> v;
	dfs(0, -1, user_id, banned_id, 0,v);
    answer = errorMap.size();
    return answer;
}