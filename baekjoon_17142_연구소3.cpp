#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;

int N, M;
int virusArr[101][101];
int visit[101];
int researchNum = 0;
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
vector<pair<int, int>> v;
queue<pair<pair<int, int>,int>> q;
int tvisitArr[101][101];
int result = 987654321;

/*
조합을 통해 M개 활성화 지점 선택
bfs를 사용하여 선택된 활성화 지점 기준으로 복제 및 활성화 
빈칸인 경우에는 시간을 1초 증가시키고, 비활성 지점인 경우 시간 증가 안시킴
한 지점을 기준으로 4 방향을 볼 때, 1방향이라도 복제된 곳이 존재한다면 시간 증가
 0 1 0 
 2 2 2
 0 2 0   

 이 때,  (1,1)이 활성화 상태일 때, (0,1)을 복제하므로 0초->1초 증가함. 즉, (0,1), (1,2), (2,1) 전부 1초 상태임
*/
void dfs(int selected, int num) {
	if (num == M) {
		
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				tvisitArr[i][j] = -1;
			}
		}
		for (int i = 0; i < researchNum; i++) {
			if (visit[i] == 1) {
				q.push({ { v[i].first,v[i].second },0 });
				tvisitArr[v[i].first][v[i].second] = 0;
			}
		}
		int v_num = 0;
		while (!q.empty()) {
			int x = q.front().first.first;
			int y = q.front().first.second;
			int t = q.front().second;
			q.pop();
			
			for (int i = 0; i < 4; i++) {
				int nx = x + dx[i];
				int ny = y + dy[i];
				if (nx >= 0 && ny >= 0 && nx < N && ny < N && tvisitArr[nx][ny]==-1) {
					if (virusArr[nx][ny] == 0) {
						tvisitArr[nx][ny] = t + 1;
						q.push({ { nx,ny },t + 1 });
					}
					else if (virusArr[nx][ny] == 2) {
						tvisitArr[nx][ny] = tvisitArr[x][y];
						q.push({ { nx,ny },t + 1 });
					}
				}
			}
		}
	
		int num = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				v_num = max(v_num, tvisitArr[i][j]);
				if (tvisitArr[i][j] != -1)
					num++;
				if (virusArr[i][j] == 1)
					num++;
			}
		}
	
		if (num == N*N) {
			result = min(result, v_num);
		}
		return; 
	}
	
	if (selected > researchNum)
		return;

	visit[selected] = 1;
	dfs(selected + 1, num + 1);
	visit[selected] = 0;
	dfs(selected + 1, num);
}

int main(void) {

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> virusArr[i][j];
			if (virusArr[i][j] == 2) {
				researchNum += 1;
				v.push_back({ i,j });
			}
		}
	}
	dfs(0, 0);
	if (result == 987654321)
		printf("-1\n");
	else
		printf("%d\n", result);

}