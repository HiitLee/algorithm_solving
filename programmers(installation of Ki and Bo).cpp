#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
vector<vector<int>> build_frame;
int mapK[101][101];
int mapB[101][101];
int N;



bool isBuildKi(int x, int y) {
	if (x == 0)
		return true;
	else if (x>0 && mapK[x - 1][y] == 1)
		return true;
	else if (y > 0 && mapB[x][y - 1] == 1)
		return true;
	else if (x < N && mapB[x][y] == 1)
		return true;

	return false;
}
bool isBuildBo(int x, int y) {
	if (x>0 && mapK[x - 1][y] == 1) 
		return true;
	else if (x>0 && y < N && mapK[x - 1][y + 1] == 1)
		return true;
	else if (y >0 && y < N && mapB[x][y - 1] == 1 && mapB[x][y + 1]==1)
		return true;

	return false;
}
vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    N=n;
    memset(mapK, 0, sizeof(mapK));
	memset(mapB, 0, sizeof(mapB));
	for (auto& e : build_frame) {
		int y = e[0], x = e[1], Bo_Ki = e[2], isBuild = e[3];	
		// 기둥 설치
		if (Bo_Ki == 0 && isBuild == 1) {
			if (isBuildKi(x, y)==true) {
				mapK[x][y] = 1;
			}

		}
		// 보 설치
		else if (Bo_Ki == 1 && isBuild == 1) {
			if (isBuildBo(x, y) == true) {
				mapB[x][y] = 1;
			}
		}
		// 기둥 삭제
		else if (Bo_Ki == 0 && isBuild == 0) {
			mapK[x][y] = 0;
			if (x < n && mapB[x+1][y] == 1 && isBuildBo(x+1, y) == false) {
				mapK[x][y] = 1;
				continue;
			}
			if (x<n && y  >0 &&  mapB[x+1][y-1] == 1 && isBuildBo(x+1,y-1)== false) {
				mapK[x][y] = 1;
				continue;
			}
			if (x < n  && mapK[x + 1][y] == 1 && isBuildKi(x + 1, y) == false) {
				mapK[x][y] = 1;
				continue;
			}
			
		}
		//보 삭제
		else if (Bo_Ki == 1 && isBuild == 0) {
			mapB[x][y] = 0;
			if (mapK[x][y] == 1 && isBuildKi(x, y) == false)
			{
				mapB[x][y] = 1;
				continue;
			}
			if (y>0 && mapB[x][y - 1] == 1 && isBuildBo(x, y - 1) == false) {
				mapB[x][y] = 1;
				continue;
			}
			if (y < n && mapB[x][y + 1] == 1 && isBuildBo(x, y + 1) == false) {
				mapB[x][y] = 1;
				continue;
			}
			if (y < n && mapK[x][y+1] == 1 && isBuildKi(x, y+1) == false) {
				mapB[x][y] = 1;
				continue;
			}
		
			
		}
	}
	vector<vector<int>> answer;
	for (int j = 0; j <= n; j++) {
		
		for (int i = 0; i <= n; i++) {
			vector<int> temp;
			if (mapK[i][j] == 1) {
				answer.push_back({j,i,0});
			}
			if (mapB[i][j] == 1) {
				answer.push_back({ j,i,1 });
			}
		}
	}
	
	//sort(answer.begin(), answer.end(), compare);
	return answer;
}