#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

int T;
int N, W, H;
// N: �� �� �ִ� ���� , W: width, H; height
int map[101][101];
int visit[101];
int height[101];
int map2[101][101];
int height2[101];
int result = 987654321;
vector<pair<int, int>> vv;
queue<pair<pair<int, int>, int>> v;
/*
1. map ����
2. height �迭�� ���̰� ���� �� ���� index �ֱ�
3. ��Ž�� ���� ���� �� �迭���� ������ �� index N�� ã��
4. ã�� index�� �������� ��������(bfs ����Ͽ� ���� ���� ����)
5. ���� ���� �� bfs�� ����Ͽ� ������ �б�
6. ���� ���ϰ�, result���ϱ�
7. �ð��� �� ���̱� ���� result=0�� ��� ���� �ʰ� ����
*/
void dfs(int num) {
	if (result == 0)
		return;
	if (num == N) {
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				map2[i][j] = map[i][j];
			}
		}
		for (int i = 0; i < W; i++) {
			height2[i] = height[i];
		}
		for (int i = 0; i < N; i++) {
			v.push({ {height2[visit[i]],visit[i]},map2[height2[visit[i]]][visit[i]] });
			while (!v.empty()) {
				int x = v.front().first.first;
				int y = v.front().first.second;
				int num = v.front().second;
				v.pop();
				map2[x][y] = 0;
				for (int k = 1; k < num; k++) {
					if (x + k >= 0 && x + k < H) {
						if (map2[x + k][y] > 1) {
							v.push({ {x + k,y},map2[x + k][y] });
						}
						map2[x + k][y] = 0;
					}
					if (x - k >= 0 && x - k < H) {
						if (map2[x - k][y] > 1) {
							v.push({ {x - k,y},map2[x - k][y] });
						}
						map2[x - k][y] = 0;
					}
					if (y + k >= 0 && y + k < W) {
						if (map2[x][y + k] > 1) {
							v.push({ {x,y + k},map2[x][y + k] });
						}
						map2[x][y + k] = 0;
					}
					if (y - k >= 0 && y - k < W) {
						if (map2[x][y - k] > 1) {
							v.push({ {x,y - k},map2[x][y - k] });
						}
						map2[x][y - k] = 0;
					}

				}
			}
			for (int ii = 0; ii < W; ii++) {

				for (int jj = H - 1; jj >= 0; jj--) {
					
					if (map2[jj][ii] != 0) {
						vv.push_back({ jj,ii });
					}
					while (!vv.empty()) {
						int x = vv.front().first;
						int y = vv.front().second;
						vv.pop_back();
						if (map2[x + 1][y] == 0 && x + 1 < H) {
							vv.push_back({ x + 1,y });
							map2[x + 1][y] = map2[x][y];
							map2[x][y] = 0;
						}
					}
				}
			}
			for (int ii = 0; ii < W; ii++) {
				for (int jj = 0; jj < H; jj++) {
					if (map2[jj][ii] != 0) {
						height2[ii] = jj;
						break;
					}
				}
			}
		}
		int temp_result = 0;
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				if (map2[i][j] != 0) {
					temp_result += 1;
				}
			}
		}
		result = min(result, temp_result);
		return;
	}
	if (num > N)
		return;
	for (int i = 0; i < W; i++) {
		visit[num] = i;
		dfs(num + 1);
		visit[num] = 0;
	}
}
int main(void) {
	cin >> T;
	for (int t = 0; t < T; t++) {
		cin >> N >> W >> H;
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				cin >> map[i][j];

			}
		}

		for (int i = 0; i < W; i++) {
			for (int j = 0; j < H; j++) {
				if (map[j][i] != 0) {
					height[i] = j;
					break;
				}
			}
		}
		result = 987654321;
		dfs(0);
		printf("#%d %d\n", t+1, result);
	}

}

/*
5
3 10 10
0 0 0 0 0 0 0 0 0 0
1 0 1 0 1 0 0 0 0 0
1 0 3 0 1 1 0 0 0 1
1 1 1 0 1 2 0 0 0 9
1 1 4 0 1 1 0 0 1 1
1 1 4 1 1 1 2 1 1 1
1 1 5 1 1 1 1 2 1 1
1 1 6 1 1 1 1 1 2 1
1 1 1 1 1 1 1 1 1 5
1 1 7 1 1 1 1 1 1 1
2 9 10
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 1 0 0 0 0 0 0 0
0 1 0 0 0 0 0 0 0
1 1 0 0 1 0 0 0 0
1 1 0 1 1 1 0 1 0
1 1 0 1 1 1 0 1 0
1 1 1 1 1 1 1 1 0
1 1 3 1 6 1 1 1 1
1 1 1 1 1 1 1 1 1
3 6 7
1 1 0 0 0 0
1 1 0 0 1 0
1 1 0 0 4 0
4 1 0 0 1 0
1 5 1 0 1 6
1 2 8 1 1 6
1 1 1 9 2 1
4 4 15
0 0 0 0
0 0 0 0
0 0 0 0
1 0 0 0
1 0 0 0
1 0 0 0
1 0 0 0
1 0 5 0
1 1 1 0
1 1 1 9
1 1 1 1
1 6 1 2
1 1 1 5
1 1 1 1
2 1 1 2
4 12 15
9 9 9 9 9 9 9 9 9 9 9 9
9 9 9 9 9 9 9 9 9 9 9 9
9 9 9 9 9 9 9 9 9 9 9 9
9 9 9 9 9 9 9 9 9 9 9 9
9 9 9 9 9 9 9 9 9 9 9 9
9 9 9 9 9 9 9 9 9 9 9 9
9 9 9 9 9 9 9 9 9 9 9 9
9 9 9 9 9 9 9 9 9 9 9 9
9 9 9 9 9 9 9 9 9 9 9 9
9 9 9 9 9 9 9 9 9 9 9 9
9 9 9 9 9 9 9 9 9 9 9 9
9 9 9 9 9 9 9 9 9 9 9 9
9 9 9 9 9 9 9 9 9 9 9 9
9 9 9 9 9 9 9 9 9 9 9 9
9 9 9 9 9 9 9 9 9 9 9 9


#1 12
#2 27
#3 4
#4 8
#5 0


*/