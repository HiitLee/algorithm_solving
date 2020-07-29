#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <string>
using namespace std;


int visit[4];
string expp[3] = {"-","*","+"};
long long answer = 0;
void dfs(int num , vector<long long> v, vector<string> q) {
	if (num == 3) {
		while (1) {
			if (q.size() == 1)
				break;
			for (int i = 0; i < 3; i++) {
				int qs = q.size();
				
				while (1) {
					int flag = false;
					for (int j = 0; j < qs; j++) {
						if (expp[v[i]] == q[j]) {
							if (q[j] == "+")
							{
								q[j - 1] = to_string(stoll(q[j - 1]) + stoll(q[j + 1]));
							}
							else if (q[j] == "-") {
								q[j - 1] = to_string(stoll(q[j - 1]) - stoll(q[j + 1]));
							}
							else if (q[j] == "*") {
								q[j - 1] = to_string(stoll(q[j - 1]) * stoll(q[j + 1]));
							}

							q.erase(q.begin() + j);
							q.erase(q.begin() + j);
							qs -= 2;
                            i=0;
							flag = true;
						}

					}
					if (flag == false){
                        
						break;
                    }
				}
			}
		}
	
		answer = max(answer, abs(stoll(q[0])));
		return;
	}
	for (int i = 0; i < 3; i++) {
		if (!visit[i]) {
			v.push_back(i);
			visit[i] = 1;
			dfs(num + 1,v,q);
			visit[i] = 0;
			v.pop_back();
		}
	}
}
long long solution(string expression) {
    
    string temp = "";
	vector<long long> v;
	vector<string> q;
	for (int i = 0; i < expression.size(); i++) {
		
		if (expression[i] - '0' >= 0 && expression[i] - '0' <= 9) {
			temp += expression[i];
		}
		else {
			q.push_back(temp);
			temp = expression[i];
			q.push_back(temp);
			temp = "";
		}
	}
	q.push_back(temp);
	memset(visit, 0, sizeof(visit));
	dfs(0, v, q);
	return answer;
}