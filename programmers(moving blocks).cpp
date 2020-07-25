#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N;
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
int rdx[4] = { -1,1,1,-1 };
int rdy[4] = { 1,1,-1,-1 };
int visit[100][100][4];

bool isCheck(int nx, int ny, int nxx, int nyy) {
	if (nx < 0 || ny < 0 || nx >= N || ny >= N)
		return false;
	if (nxx < 0 || nyy < 0 || nxx >= N || nyy >= N)
		return false;

	return true;
}

int main(void) {
	int answer = 0;
	vector<vector<int>> board = { {0,0,0,1,1},{0,0,0,1,0},{0,1,0,1,1},{1,1,0,0,1},{0,0,0,0,0} };
	memset(visit, 0, sizeof(visit));
	queue<pair<pair<int, int>, pair<int, int>>> q;
	q.push({ {0,0},{0,0} });
	visit[0][0][0] = 1;
	N = board.size();
	while (!q.empty()) {
		int x = q.front().first.first;
		int y = q.front().first.second;
		int time = q.front().second.first;
		int dir = q.front().second.second;

		q.pop();
		int xx = x + dx[dir];
		int yy = y + dy[dir];
		int nx, ny, nxx, nyy;
		if (x == N - 1 && y == N - 1)
		{
			answer = time;
			break;
		}
		if (xx == N - 1 && yy == N - 1) {
			answer = time;
			break;
		}

		// 상,하,좌,우 이동
		for (int i = 0; i < 4; i++) {
			nx = x + dx[i];
			ny = y + dy[i];
			nxx = xx + dx[i];
			nyy = yy + dy[i];
			if (!isCheck(nx, ny, nxx, nyy))
				continue;
			if (visit[nx][ny][dir])
				continue;
			if (board[nx][ny] == 1 || board[nxx][nyy] == 1)
				continue;
			visit[nx][ny][dir] = 1;
			q.push({ {nx,ny},{time + 1, dir} });

		}
		// x, y로 회전

		for (int i = 1; i < 4; i += 2) {
			int rdir = (dir + i) % 4;
			nxx = x + dx[rdir];
			nyy = y + dy[rdir];
			//시계
			int r_nx, r_ny;
			if (i == 1) {
				r_nx = x + rdx[rdir];
				r_ny = y + rdy[rdir];
			}
			//반시계
			else {
				r_nx = x + rdx[dir];
				r_ny = y + rdy[dir];
			}
			if (!isCheck(r_nx, r_ny, nxx, nyy))
				continue;
			if (visit[x][y][rdir])
				continue;

			if (board[nxx][nyy] == 1)
				continue;
			if (board[r_nx][r_ny])
				continue;
			visit[x][y][rdir] = 1;
			q.push({ {x,y},{time + 1,rdir} });

		}
		// xx, yy로 회전
		dir = (dir + 2) % 4;
		for (int i = 1; i < 4; i += 2) {
			int rdir = (dir + i) % 4;
			nx = xx + dx[rdir];
			ny = yy + dy[rdir];

			int r_nx, r_ny;
			if (i == 1) {
				r_nx = xx + rdx[rdir];
				r_ny = yy + rdy[rdir];
			}
			//반시계
			else {
				r_nx = xx + rdx[dir];
				r_ny = yy + rdy[dir];
			}

			if (!isCheck(nx, ny, r_nx, r_ny))
				continue;
			if (board[nx][ny] == 1)
				continue;
			if (board[r_nx][r_ny] == 1)
				continue;
			rdir = (rdir + 2) % 4;
			if (visit[nx][ny][rdir])
				continue;
			visit[nx][ny][rdir] = 1;
			q.push({ {nx,ny},{time + 1,rdir} });

		}
	}
	cout << answer << endl;
	return answer;

}