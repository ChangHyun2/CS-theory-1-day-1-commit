#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;

struct Pos {int r,c;};
const int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

void spreadVirus(vector<vector<int> > &map, unsigned int subset, vector<Pos> &virus, int empty_size, int M, int &min) {
    
    vector<vector<bool> > visited(map.size(), vector<bool>(map.size(), 0)); 
    queue<Pos> qu;

    for(int i=0; i<M; i++) {
        int index = __builtin_ctz(subset);
        subset &= (subset-1);
        qu.push(virus[index]);
        visited[virus[index].r][virus[index].c] = 1;
    }

    int cnt = M;
    int time = 0;
    while(!qu.empty()) {
        if(time>=min) return;
        Pos here = qu.front();
        if(map[here.r][here.c] == 0) empty_size -= 1;
        qu.pop();
        cnt -= 1;

        for(int i=0; i<4; i++) {
            Pos there = Pos{here.r + dir[i][0], here.c + dir[i][1]};
            if(there.r<0 || there.c<0 || there.c>=map.size() || there.r>=map.size()) continue;
            if(visited[there.r][there.c]) continue;
            if(map[there.r][there.c] == 1) continue;
            qu.push(there);
            visited[there.r][there.c] = 1;
        }

        if(empty_size==0) break;
        if(cnt == 0) {
            cnt = qu.size();
            time += 1;
        }
    }

    if(empty_size!=0) {
        return ;
    }
    if(min > time) {
        min = time;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M;
    cin >> N >> M;
    
    int empty_size = 0;
    vector<vector<int> > map(N, vector<int>(N,0));
    vector<Pos> virus;
    for(int r=0; r<N; r++){
        for(int c=0; c<N; c++){
            cin >> map[r][c];
            if(map[r][c] == 2) virus.push_back(Pos{r,c});
            if(map[r][c] == 0) empty_size++;
        }
    }

    int answer = 987654321;

    unsigned int full = (1u << virus.size()) - 1;
    for(unsigned int subset = full; subset; subset--) {
        if((unsigned int)pow(2,M)-1 > subset) break;
        if(__builtin_popcount(subset) == M) {
            spreadVirus(map, subset, virus, empty_size, M, answer);
        }
    }

    if(answer == 987654321) answer = -1;
    cout << answer << endl;

    return 0;
}