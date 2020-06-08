#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N, M, T;
int circleArr[51][51];
int tempArr[51][51];
int visit[101][101];
int x[101], d[101], k[101];
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };
int result = 0;
queue<pair<pair<int, int>, int>> q;

void rotate(int num, int num_rotate, int num_move) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      tempArr[i][j] = circleArr[i][j];
    }
  }
  int tindexNum = 0;
  int indexNum = 0;
  if (num_rotate == 1) {
    tindexNum = -1 * num_move;
    
    while (1) {

      if (indexNum == M)
        break;
      if (indexNum + tindexNum >= 0)
        circleArr[num][indexNum + tindexNum] = tempArr[num][indexNum];
      else
        circleArr[num][indexNum + tindexNum + M] = tempArr[num][indexNum];

      indexNum += 1;
    }
  }
  else {
    tindexNum = 1 * num_move;
    while (1) {

      if (indexNum == M)
        break;
      circleArr[num][(indexNum + (tindexNum)) % M] = tempArr[num][indexNum];
      indexNum += 1;
    }
  }


}

void hap() {
  
  int beforeNum = 0;
  int afterNum = 0;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      tempArr[i][j] = circleArr[i][j];
    }
  }
  
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (circleArr[i][j] == -1)
        beforeNum += 1;
      q.push({ {i,j},circleArr[i][j] });
    }
  }
  memset(visit, 0, sizeof(visit));
  while (!q.empty()) {
    int sz = q.size();
    for (int i = 0; i < sz; i++) {
      int x = q.front().first.first;
      int y = q.front().first.second;
      int checkNum = q.front().second;
      
      q.pop();
      for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && ny >= 0 && nx < N && ny < M) {
          if (circleArr[nx][ny] == checkNum && !visit[nx][ny]) {
            q.push({ { nx,ny }, circleArr[nx][ny] });
            circleArr[nx][ny] = -1;
            circleArr[x][y] = -1;
            visit[nx][ny] = 1;
          }
        }
      }
    }
  }

  for (int i = 0; i < N; i++) {
    if (tempArr[i][0] == tempArr[i][M - 1])
    {
      circleArr[i][0] = -1;
      circleArr[i][M - 1] = -1;
    }
  }

  int sumInt = 0;
  int numInt = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (circleArr[i][j] == -1)
        afterNum += 1;
      if (circleArr[i][j] != -1) {
        sumInt += circleArr[i][j];
        numInt += 1;
      }
    }
  }

  if (afterNum <= beforeNum && numInt != 0) {
    int mean_share = sumInt / numInt;
    int mean_rest = sumInt % numInt;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if (circleArr[i][j] != -1) {
          if (mean_rest > 0) {
            if (circleArr[i][j] <= mean_share) {
              circleArr[i][j] += 1;
            }
            else if (circleArr[i][j] > mean_share) {
              circleArr[i][j] -= 1;
            }
          }
          else if (mean_rest == 0) {
            if (circleArr[i][j] < mean_share) {
              circleArr[i][j] += 1;
            }
            else if (circleArr[i][j] > mean_share) {
              circleArr[i][j] -= 1;
            }
          }
        }
      }
    }
  }
}

int main(void) {
  cin >> N >> M >> T;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> circleArr[i][j];
      tempArr[i][j] = circleArr[i][j];
    }
  }
  


  for (int i = 0; i < T; i++) {
    cin >> x[i] >> d[i] >> k[i];
  }

  for (int i = 0; i < T; i++) {
    for (int j = x[i]; j <= N; j++) {
      if (j % (x[i]) == 0) {
        rotate(j - 1, d[i], k[i]);
      }
    }
    hap();
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (circleArr[i][j] != -1) {
        result += circleArr[i][j];
      }
    }
  }

  printf("%d\n", result);
}