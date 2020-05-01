#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int T;
int N;
int map[17][17];
int visit[17];
int result = 987654321;

void dfs(int num, int selected) {
  if (num == N/2) {
    
    int food_a = 0;
    int food_b = 0;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (i == j)
          continue;
        if (visit[i]==1 && visit[j] ==1) {
          food_a += map[i][j];
        }
        else if(visit[i] != 1 && visit[j] != 1){
          food_b += map[i][j];
        }
      }
    }
    int result_temp = abs(food_a - food_b);
    result = min(result, result_temp);

    return;
  }
  if (selected == N)
    return;

  visit[selected] = 1;
  dfs(num + 1, selected + 1);
  visit[selected] = 0;
  dfs(num, selected + 1);
}
int main(void) {
  cin >> T;
  for (int t = 1; t <= T; t++) {
    cin >> N;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        cin >> map[i][j];
      }
    }
    memset(visit, 0, sizeof(visit));
    result = 987654321;
    dfs(0,0);
    printf("#%d %d\n", t, result);
  }
}

