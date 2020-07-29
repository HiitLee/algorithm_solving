#include <iostream>
#include <algorithm>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

int solution(vector<vector<int>> board) {
    int answer = 987654321;
	int visit2[101][101];
	int board_size = board.size();

	queue<pair<pair<int, int>, pair<int, int>>> q;
	q.push({ {1,0},{0,0} });
	q.push({ {0,0},{0,0} });
	for (int i = 0; i < board_size; i++) {
		for (int j = 0; j < board_size; j++) {
			visit2[i][j] = 987654321;
		}
	}
	int ans = 987654321;
	while (!q.empty()) {
		int sz = q.size();
		for (int i = 0; i < sz; i++) {
			int x = q.front().second.first;
			int y = q.front().second.second;
			int dir = q.front().first.first;
			int cost = q.front().first.second;
			q.pop();
			if (x == board_size - 1 && y == board_size - 1) {
				answer = min(answer, cost);

			}
			for (int k = 0; k < 4; k++) {
				int nx = x + dx[k];
				int ny = y + dy[k];
				if (nx >= 0 && ny >= 0 && nx < board_size && ny < board_size &&  board[nx][ny] == 0) {
					if ((dir + 2) % 4 == k || k == dir) {
						if (visit2[nx][ny] >= cost + 100) {
							visit2[nx][ny] = cost + 100;
							q.push({ {k,cost + 100},{nx,ny} });
						}
					}
					else {
						if (visit2[nx][ny] >=cost + 600) {							
							visit2[nx][ny] = cost + 600;
							q.push({ {k % 4,cost + 600},{nx,ny} });
								
						}
					}
				}
			}
		}
	}
	return answer;
}