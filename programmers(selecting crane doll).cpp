#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> map[1001];
int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    int N = board.size(), M = board[0].size();
	for (int j = 0; j < M; j++) {
		for (int i = N-1; i >=0; i--) {
			if(board[i][j] != 0)
				map[j+ 1].push_back(board[i][j]);
		}
	}
	vector<int> temp;
	for (auto e : moves) {
		if (map[e].size() == 0)
			continue;
		temp.push_back(map[e].back());
		map[e].pop_back();
		if (temp.size() <= 1)
			continue;
		else {
			if (temp.back() == temp[temp.size() - 2])
			{
				temp.pop_back();
				temp.pop_back();
				answer += 2;
			}
		}
	}
    return answer;
}