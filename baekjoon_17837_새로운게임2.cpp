#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N, K;
int arrMap[13][13];
vector<pair<int, int>> arrchase[13][13];
vector<pair<pair<int, int>, pair<int, int>>> v;
int dx[4] = { 0,0,-1,1 };
int dy[4] = { 1,-1,0,0 };
// ������, ����, ��, �Ʒ�

/*
���� ���ذ� �߿���
ũ�� 2���� ����� ���� ������
(�ǿ��� 0�� 1�� ������ ���) / (������ ��� ���� 2�� ������ ���)

����Ǯ�ٰ� ������ ���� ��ü ���� ������ �� 4���� ���ƴ��� Ȯ���ϴ°� �ƴ϶� ���� �ϳ� �����϶����� 4���̻� ���ƴ��� ���� Ȯ���ؾ���
*/

int main(void) {
  cin >> N >> K;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> arrMap[i][j];
    }
  }
  for (int i = 0; i < K; i++) {
    int temp_x, temp_y, temp_num;
    cin >> temp_x >> temp_y >> temp_num;
    v.push_back({ {i,temp_num-1}, {temp_x-1,temp_y-1} });
    arrchase[temp_x-1][temp_y-1].push_back({ i,temp_num-1 });
  }

  int result = -1;
  for (int m = 0; m < 1000; m++) {
    for (int i = 0; i < K; i++) {
      int x = v[i].second.first;
      int y = v[i].second.second;
      int dir = v[i].first.second;
      int id = v[i].first.first;
      int nx = x + dx[dir];
      int ny = y + dy[dir];
      // �ǿ� ���� 2���� �̻� ��ģ���
      int c_num = arrchase[x][y].size();
      int start_x = 0;
      for (int n = 0; n < c_num; n++) {
        if (arrchase[x][y][n].first == id) {
          start_x = n;
        }
      }
      if ((nx >= 0 && ny >= 0 && nx < N && ny < N && arrMap[nx][ny] == 2) || !(nx >= 0 && ny >= 0 && nx < N && ny < N)) {
        vector<pair<int, int>> temp;

        if (dir == 0)
          dir = 1;
        else if (dir == 1)
          dir = 0;
        else if (dir == 2)
          dir = 3;
        else
          dir = 2;

        arrchase[x][y][start_x].second = dir;

        nx = x + dx[dir];
        ny = y + dy[dir];
        if (arrMap[nx][ny] == 2 || !(nx >= 0 && ny >= 0 && nx < N && ny < N))
          continue;

        for (int i = start_x; i < c_num; i++) {
          temp.push_back({ arrchase[x][y][i].first, arrchase[x][y][i].second });
          v[arrchase[x][y][i].first].first.first = arrchase[x][y][i].first;
          v[arrchase[x][y][i].first].first.second = arrchase[x][y][i].second;
          v[arrchase[x][y][i].first].second.first = nx;
          v[arrchase[x][y][i].first].second.second = ny;
        }

        for (int i = c_num - 1; i >= start_x; i--)
          arrchase[x][y].pop_back();

        if (arrMap[nx][ny] == 1)
          reverse(temp.begin(), temp.end());

        for (int i = 0; i < temp.size(); i++)
          arrchase[nx][ny].push_back({ temp[i].first, temp[i].second });
      }
      else if (nx >= 0 && ny >= 0 && nx < N && ny < N) {
        vector<pair<int, int>> temp;
        for (int i = start_x; i < c_num; i++) {
          temp.push_back({ arrchase[x][y][i].first, arrchase[x][y][i].second });
          v[arrchase[x][y][i].first].first.first = arrchase[x][y][i].first;
          v[arrchase[x][y][i].first].first.second = arrchase[x][y][i].second;
          v[arrchase[x][y][i].first].second.first = nx;
          v[arrchase[x][y][i].first].second.second = ny;
        }

        for (int i = c_num - 1; i >= start_x; i--)
          arrchase[x][y].pop_back();

        if (arrMap[nx][ny] == 1)
          reverse(temp.begin(), temp.end());

        for (int i = 0; i < temp.size(); i++)
          arrchase[nx][ny].push_back({ temp[i].first, temp[i].second });
      }

      for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
          if (arrchase[i][j].size() >= 4) {
            result = m + 1;
            printf("%d \n", result);
            return 0;
          }
        }
      }
    }

    while (!v.empty())
      v.pop_back();
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (arrchase[i][j].size() >= 1) {
          for (int kk = 0; kk < arrchase[i][j].size(); kk++)
            v.push_back({ {arrchase[i][j][kk].first,arrchase[i][j][kk].second},{i,j} });
        }
        
      }
    }
    sort(v.begin(), v.end());
  }
 
  printf("%d \n", result);
}