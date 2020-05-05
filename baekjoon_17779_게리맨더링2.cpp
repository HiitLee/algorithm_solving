#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

int N;

int arrMap[101][101];
int visit[23];
int tvisit[101][101];

int d1, d2;
int result = 987654321;

int dx[4] = { 0,0,-1,1 };
int dy[4] = { 1,-1,0,0 };

/*
1. 문제에 주어진 조건을 고려하여 d1, d2 중복순열로 뽑기
2. 뽑고 난 후에는 for문을 돌려서 조건에 맞게 각 선거구에 구역을 채우기. 주어진 조건에 따라 그대로 채우는게 중요함!
3. 채운 후 각 선거구에 해당하는 인구를 세고 max min을 사용하여 정답구하기
*/
void dfs(int x, int y, int num) {
	if (num == 2) {
		d1 = visit[0];
		d2 = visit[1];

		if (d1 >= 0 && d2 >= 0 && x >= 0 && x < x + d1 + d2 && x + d1 + d2 <= N-1 && 0 <= y - d1 && y - d1 < y && y < y + d2 && y + d2 <= N-1) {
			memset(tvisit, 0, sizeof(tvisit));
			for (int i = 0; i <= d1; i++) {
				tvisit[x + i][y - i] = 5;
			}

			for (int i = 0; i <= d2; i++) {
				tvisit[x + i][y + i] = 5;
			}

			for (int i = 0; i <= d2; i++) {
				tvisit[x + d1 + i][y - d1 + i] = 5;
			}

			for (int i = 0; i <= d1; i++) {
				tvisit[x + d2 + i][y + d2 - i] = 5;
			}

			for (int i = 0; i < x + d1; i++) {
				for (int j = 0; j <=y; j++) {
					if (tvisit[i][j] == 5)
						break;
					tvisit[i][j] = 1;
				}
			}
			
			for (int i = 0; i <= x + d2; i++) {
				for (int j = N-1; j >=y+1; j--) {
					if (tvisit[i][j] == 5)
						break;
					tvisit[i][j]=2;
				}
			}

			for (int i = x + d1; i < N; i++) {
				for (int j = 0; j < y - d1 + d2; j++) {
					if (tvisit[i][j] == 5)
						break;
					tvisit[i][j] = 3;
				}
			}

			for (int i = x + d2 +1; i < N; i++) {
				for (int j = N - 1; j >= y - d1 + d2; j--) {
					if (tvisit[i][j] == 5)
						break;
					tvisit[i][j] = 4;
				}
			}
			int tresult = 0;
			int score[6];
			memset(score, 0, sizeof(score));

			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					if (tvisit[i][j] == 1)
						score[0] += arrMap[i][j];
					else if (tvisit[i][j] == 2)
						score[1] += arrMap[i][j];
					else if (tvisit[i][j] == 3)
						score[2] += arrMap[i][j];
					else if (tvisit[i][j] == 4)
						score[3] += arrMap[i][j];
					else
						score[4] += arrMap[i][j];
				}
			}
			int min_temp = 987654321;
			int max_temp = -987654321;
			for (int i = 0; i < 5; i++) {
				min_temp = min(min_temp, score[i]);
				max_temp = max(max_temp, score[i]);
			}
			tresult = max_temp - min_temp;
			result = min(tresult, result);
		}


		return;

	}


	for (int i = 1; i <= N - 2; i++) {
		visit[num] = i;
		dfs(x, y, num + 1);
		visit[num] = 0;
	}
}
int main(void) {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arrMap[i][j];
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			dfs(i, j, 0);
		}
	}
	printf("%d ", result);
}