#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int T;
int K;
int arrGear[101][101];
int arrRule[101][2];
int result;
int arrVisit[101];
// arrGear: 각 톱니바퀴에 대한 배열, arRule: 회전정보 배열, arrVisit: 주어진 룰에 따라 톱니바퀴를 시계/반시계로 회전시키기 전에 전체 톱니바퀴의 회전 위치 정하는 배열
// 1) 주어진 회전정보를 통해 각 반복문마다 시계/반시계 회전이 정해지는 톱니바퀴를 arrVisit에 저장
// 2) 저장된 arrVisit에 따라 각 톱니바퀴 시계/반시계 회전

int main() {
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> K;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 8; j++) {
				cin >> arrGear[i][j];
			}
		}
		for (int i = 0; i < K; i++) {
			cin >> arrRule[i][0] >> arrRule[i][1];
		}

		for (int i = 0; i < K; i++) {
			int selectedNum = arrRule[i][0]-1;
			int selectedDir = arrRule[i][1];
			memset(arrVisit, 0, sizeof(arrVisit));
			arrVisit[selectedNum] = selectedDir;
			for (int i = selectedNum; i < 4; i++) {
				if (arrGear[i][2] != arrGear[i + 1][6]) {
					if (arrVisit[i] == 1)
						arrVisit[i + 1] = -1;
					else
						arrVisit[i + 1] = 1;
				}
				else
					break;
			}
			for (int i = selectedNum; i >=0 ; i--) {
				if (arrGear[i][6] != arrGear[i - 1][2]) {
					if (arrVisit[i] == 1)
						arrVisit[i - 1] = -1;
					else
						arrVisit[i - 1] = 1;
				}
				else
					break;

			}
			int temp;
			for (int i = 0; i < 4; i++) {
				if (arrVisit[i] == 1) {
					temp = arrGear[i][7];
					for (int n = 7; n >= 1; n--) {
						arrGear[i][n] = arrGear[i][n - 1];
					}
					arrGear[i][0] = temp;
				}
				else if(arrVisit[i]==-1) {
					temp = arrGear[i][0];
					for (int n = 0; n < 7; n++) {
						arrGear[i][n] = arrGear[i][n + 1];
					}
					arrGear[i][7] = temp;
				}
			}
		}
		result = 0;
		for (int i = 0; i < 4; i++) {
			if (arrGear[i][0] == 1) {
				result += ( pow(2, i));

			}
		}
		printf("#%d %d\n", t, result);
	}
	return 0;

}