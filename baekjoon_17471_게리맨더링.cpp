#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int N;
int electionArea[11][11];
int populationNum[11];
int visit[11];
int result = 987654321;
queue<int> q;

/*
예외처리가 많이 필요한 문제임
모든 구역이 연결되지 않은 경우 고려해야함
조합을 통해 구역을 2개의 선거구로 구분하여 선택
같은 선거구는 서로 연결되어 있어야 하므로 bfs를 통해 확인

시간복잡도: 모든 케이스를 고려하는 브루트 포스 방식으로 문제를 푼다면 시간 복잡도는 대략 O(N*2^N)이 됨
왜냐면 구역은 N개가 있고, 각각 A가 아니면 B선거구에 속해야 하기 때문임
*/
int bfs() {
	int tempVisit[101];
	int tempInt = 1;
	for (int i = 0; i < 2; i++) {
		tempInt = i % 2;
		memset(tempVisit, 0, sizeof(tempVisit));
		for (int i = 0; i < N; i++) {
			if (visit[i] == tempInt) {
				q.push(i);
				tempVisit[i] = 1;
				break;
			}
		}
		int nn = 0;
		while (!q.empty()) {
			int sz = q.size();
			for (int k = 0; k < sz; k++) {
				int x = q.front();
				q.pop();
				for (int i = 0; i < N; i++) {
					if (electionArea[x][i] == 1 && visit[i] == tempInt) {
						if (!tempVisit[i]) {
							tempVisit[i] = 1;
							q.push(i);
							nn++;
						}
					}
				}
			}
		}
		for (int i = 0; i < N; i++) {
			if (tempVisit[i] != 1 && visit[i] == tempInt) {
				return 0;
			}
		}
	}
	return 1;
}
void dfs(int selected, int num, int selectNum) {
	if (num == selectNum) {
		if (bfs() == 0) {
			return;
		}
	

		int numA = 0;
		int numB = 0;
		for (int i = 0; i < N; i++) {
			if (visit[i] == 1) {
				numA += populationNum[i];
			}
			else {
				numB += populationNum[i];
			}
		}
		

		result = min(result, abs(numA - numB));
		return;
	}
	if (selected > N)
		return;
	visit[selected] = 1;
	dfs(selected + 1, num + 1, selectNum);
	visit[selected] = 0;
	dfs(selected + 1, num , selectNum);
}
int main(void) {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> populationNum[i];
	}
	int num_p = 0;
	for (int i = 0; i < N; i++) {
		int t_num;
		int t_num2;
		cin >> t_num;
		if(t_num ==0)
			num_p += 1;
		for (int j = 0; j < t_num; j++) {
			cin >> t_num2;
			electionArea[i][t_num2-1] = 1;
		}
	}

	if (num_p == 2 && N==2) {
		result = abs(populationNum[0] - populationNum[1]);
		printf("%d\n", result);
		return 0;
	}
	else if (num_p > 2)
	{
		printf("-1\n");
		return 0;
	}
	for (int i = 0; i < N; i++) {
		dfs(0, 0, i);
	}
	if (result != 987654321)
		printf("%d\n", result);
	else
		printf("-1\n");
}


/*
[반례 목록]

input :
6
5 2 3 4 1 2
2 2 4
4 1 3 6 5
2 4 2
2 1 3
1 2
1 2
output : 1

input :
6
1 1 1 1 1 1
2 2 4
4 1 3 6 5
2 4 2
2 1 3
1 2
1 2
output : 0

input :
6
10 20 10 20 30 40
0
0
0
0
0
0
output : -1

input :
6
2 3 4 5 6 7
2 2 3
2 1 3
2 1 2
2 5 6
2 4 6
2 4 5
output : 9

input :
5
5 2 3 4 1
1 2
4 1 3 5 4
1 2
1 2
1 2
output : 5

input :
3
1 2 1
1 2
2 1 3
1 2
output : 2

input :
10
1 2 3 4 5 6 7 8 9 10
2 2 10
2 3 1
2 4 2
2 5 3
2 6 4
2 7 5
2 8 6
2 9 7
2 10 8
2 1 9

output : 1
input :
6
2 2 2 2 2 2
1 3
1 4
1 1
1 2
1 6
1 5
output : -1

input :
4
1 2 3 4
1 2
1 3
1 1
0
output : 2


input :
2
3 4
0
0
output : 1
*/