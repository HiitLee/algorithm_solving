#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int T;
int N, M, K;
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };



struct Stat {
    int state = -1;
    int life=0;
    int unactivate=0;
    int activate=0;
};
// staste -1: 아무것도 아닌 상태, 0: 비활성화 상태, 1: 활성화 상태, 2: 죽은 상태
// 맵의 크기가 무제한이지만, 배양시간의 범위가 1<=K<=300 이므로 맵의 크기를 [350][350]으로 설정

Stat map[350][350];
int main(void) {
    cin >> T;
    
    for (int t = 0; t < T; t++) {
        cin >> N >> M >> K;
        queue<pair<int, int>> v;
        for (int i = 0; i < 350 ; i++) {
            for (int j = 0; j < 350 ; j++) {
                map[i][j].life = 0;
                map[i][j].activate = 0;
                map[i][j].unactivate = 0;
                map[i][j].state = -1;

            }
        }
        //맵의 상태 초기화
   
        for (int i = 150; i < 150 + N; i++) {
            for (int j = 150; j < 150 + M; j++) {
                int temp_life = 0;
                cin >> temp_life;
                if (temp_life > 0) {
                    map[i][j].life = temp_life;
                    map[i][j].activate = temp_life;
                    map[i][j].unactivate = temp_life;
                    map[i][j].state = 0;
                }
                
            }
        }
        // 생명력 수치가 양수인 경우에만 state:0 인 비활성화 상태로 설정
        while (K--) {
            
            for (int i = 0; i < 350; i++) {
                for (int j = 0; j < 350; j++) {
                    if (map[i][j].state == 0) {
                        if (map[i][j].unactivate > 0) {
                            map[i][j].unactivate--;
                        }
                        if (map[i][j].unactivate == 0) {
                            map[i][j].state = 1;
                        }
                    }
                    else if (map[i][j].state == 1) {
                        if (map[i][j].activate > 0) {
                            
                            v.push({ i,j });
                            map[i][j].activate--;
                        }
                        if (map[i][j].activate == 0) {
                            map[i][j].state = 2;
                        }
                    }
                }
            }
            // 전체 맵을 돌면서 활성화인 경우, 비활성화인경우의 시간 --
            

            while (!v.empty()) {
                int x = v.front().first;
                int y = v.front().second;
                v.pop();
                for (int i = 0; i < 4; i++) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    if (nx >= 0 && ny >= 0 && nx < 350 && ny < 350) {
                        if (map[nx][ny].state == -1) {
                            map[nx][ny].life = map[x][y].life;
                            map[nx][ny].activate = map[x][y].life;
                            map[nx][ny].unactivate = map[x][y].life;
                            map[nx][ny].state = 0;
                        }
                        else if (map[nx][ny].life < map[x][y].life && map[nx][ny].state==0 && map[nx][ny].life == map[nx][ny].unactivate) {
                            map[nx][ny].life = map[x][y].life;
                            map[nx][ny].activate = map[x][y].life;
                            map[nx][ny].unactivate = map[x][y].life;
              
                        }
                    }
                }
            }


        }
        int result = 0;
        for (int i = 0; i < 350; i++) {
            for (int j = 0; j < 350; j++) {
                if (map[i][j].state == 0 || map[i][j].state == 1) {
                    result++;
                }
            }
        }
      
        printf("#%d %d\n", t+1, result);
   
    }

}