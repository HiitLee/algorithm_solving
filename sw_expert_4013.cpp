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
// arrGear: �� ��Ϲ����� ���� �迭, arRule: ȸ������ �迭, arrVisit: �־��� �꿡 ���� ��Ϲ����� �ð�/�ݽð�� ȸ����Ű�� ���� ��ü ��Ϲ����� ȸ�� ��ġ ���ϴ� �迭
// 1) �־��� ȸ�������� ���� �� �ݺ������� �ð�/�ݽð� ȸ���� �������� ��Ϲ����� arrVisit�� ����
// 2) ����� arrVisit�� ���� �� ��Ϲ��� �ð�/�ݽð� ȸ��

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