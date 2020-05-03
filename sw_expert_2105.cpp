#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

int T, N;
int arrMap[101][101];
int visit[101][101];
int numDesert[101];
int arrDir[10];
int temp_x, temp_y;
int dx[4] = { 1,1,-1,-1 };
int dy[4] = { 1,-1,1,-1 };
vector<pair<int, int>> v;
int result;
// arrMap: ����Ʈ ī�� �迭 , visit: ī�� �湮 ���� �Ǵ�, numDesert: ���� ������ ����Ʈ ���� �Ǵ�
// dfs�������� �����ϵ�, ����纯�� �÷� �湮�� �� ����. ��,  �� �������� ���������� �ѹ����� ���������ϹǷ� arrDir�� ����Ͽ� ���� ��� ���� Ȯ��


void dfs(int x, int y, int num, int dir) {
	if (x == temp_x && y == temp_y && num > 3) {
		result = max(result, num);
		return;
	}

	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx >= 0 && ny >= 0 && nx < N && ny < N && !visit[nx][ny] && !numDesert[arrMap[nx][ny]] && !arrDir[dir]) {
			if (dir != i) 
				arrDir[dir] = 1;
			visit[nx][ny] = 1;
			numDesert[arrMap[nx][ny]] = 1;
			v.push_back({ nx,ny });
			dfs(nx, ny, num + 1, i);
			visit[nx][ny] = 0;
			v.pop_back();
			numDesert[arrMap[nx][ny]] = 0;
			arrDir[dir] = 0;
		}
	}
}

int main(void) {

	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> N;
		for (int i = 0; i < N; i++) 
			for (int j = 0; j < N; j++) 
				cin >> arrMap[i][j];
		result = -1;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				memset(visit, 0, sizeof(visit));
				memset(numDesert, 0, sizeof(numDesert));
				memset(arrDir, 0, sizeof(arrDir));
				temp_x = i;
				temp_y = j;
				dfs(i, j, 0, 0);
			}
		}
		printf("#%d %d\n",t, result);
	}
}