#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;


vector<int> solution(vector<string> gems) {
    set<string> gemsNum;
	vector<int> answer;
	for (auto e : gems) {
		gemsNum.insert(e);
	}
	int gN = gemsNum.size();
	int start = 0, end = 0, minNum = 987654321;
	int start_x = 0, end_x = 0, startMin = 987654321;
	int idx = 0;
	map<string,int> gemsTemp;
	while(1){
		if (gemsTemp.size() < gN) {
            if (idx >= gems.size())
				break;
			end++;
			gemsTemp[gems[idx]] += 1;
			idx++;
		}
		else if (gemsTemp.size() == gN) {
			gemsTemp[gems[start]] -= 1;
			if (gemsTemp[gems[start]] == 0) {
				gemsTemp.erase(gems[start]);
			}
			start++;
			
		}

		if (gemsTemp.size() == gN) {
			int dist = abs(end - start);
			if (dist < minNum) {
				start_x = start;
				end_x = end;
				minNum = dist;
				startMin = start;
			}
			else if (dist == minNum && startMin > start) {
				start_x = start;
				end_x = end;
				minNum = dist;
				startMin = start;
			}
		}
	}
	answer.push_back(start_x+1);
	answer.push_back(end_x);
	return answer;
}