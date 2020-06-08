#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int N;
int map[52][10];
int visit[101];
int runnerOrder[10];
int baseMan[10];
int resultNum = 0;
int result = 0;
int out = 0;

/*
시간초과가 걸리기 쉬운 문제임
팀의 선수 9명 중 1번 선수는 4번 타자로 미리 정했기 때문에 8! 연산 필요.
8! * 50 * 9 = 18,144,000 (최악의 경우)
*/
void dfs(int num) {

	if (num == 9) {	
		int idx = 0;
		result = 0;
		for (int i = 0; i < N; i++) {
			out = 0;
			while (1) {
				idx = idx % 9;
				if (map[i][runnerOrder[idx]] == 0) {
					out++;
				}
				if (out == 3) {
					for (int i = 0; i <= 3; i++) {
						baseMan[i] = -1;
					}
					idx++;
					break;
				}
				for (int k = 0; k <= 3; k++) {
					if (baseMan[k] >= 0) {
						baseMan[k] += map[i][runnerOrder[idx]];

					}
				}
				for (int k = 0; k <= 3; k++) {
					if (baseMan[k] == -1) {
						baseMan[k] += map[i][runnerOrder[idx]];
						break;
					}
				}
				for (int k = 0; k <= 3; k++) {
					if (baseMan[k] >= 3) {
						result++;
						baseMan[k] = -1;
					}
				}
				idx++;
			}
		}

		resultNum = max(resultNum, result);
		return;
	}
	if (num > 9)
		return;
	for (int i = 0; i < 9; i++) {
		if (!visit[i]) {
			visit[i] = 1;
			runnerOrder[i] = num;
			dfs(num + 1);
			visit[i] = 0;
		}
	}
}
int main(void) {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 9; j++) {
			cin >> map[i][j];
		}
	}
	memset(visit, 0, sizeof(visit));
	memset(runnerOrder, 0, sizeof(runnerOrder));
	for (int k = 0; k < 9; k++) {
		baseMan[k] = -1;
	}
	visit[3] = 1;
	runnerOrder[3] = 0;
	//1번 선수를 4번 타자로 미리 정함
	dfs(1);
	printf("%d\n", resultNum);
}