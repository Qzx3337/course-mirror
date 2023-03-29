#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 1005;
bool vis[MAXN][MAXN]; // 标记是否访问过
int maze[MAXN][MAXN]; // 迷宫地图
int path[MAXN][3]; // 记录路径（三元组）
int cnt; // 当前路径长度
int n, m; // 迷宫大小
int sx, sy, ex, ey; // 起点和终点坐标

// 深度优先搜索寻找路径
bool dfs(int x, int y) {
    if (x == ex && y == ey) return true; // 到达终点，返回 true
    vis[x][y] = true; // 标记当前点已被访问过

    // 下面从当前位置向四个方向递归查找路径
    if (x > 1 && !maze[x - 1][y] && !vis[x - 1][y]) { // 向上
        path[cnt][0] = x - 1;
        path[cnt][1] = y;
        path[cnt++][2] = 4;
        if (dfs(x - 1, y)) return true;
        cnt--;
    }

    if (x < n && !maze[x + 1][y] && !vis[x + 1][y]) { // 向下
        path[cnt][0] = x + 1;
        path[cnt][1] = y;
        path[cnt++][2] = 2;
        if (dfs(x + 1, y)) return true;
        cnt--;
    }

    if (y > 1 && !maze[x][y - 1] && !vis[x][y - 1]) { // 向左
        path[cnt][0] = x;
        path[cnt][1] = y - 1;
        path[cnt++][2] = 3;
        if (dfs(x, y - 1)) return true;
        cnt--;
    }

    if (y < m && !maze[x][y + 1] && !vis[x][y + 1]) { // 向右
        path[cnt][0] = x;
        path[cnt][1] = y + 1;
        path[cnt++][2] = 1;
        if (dfs(x, y + 1)) return true;
        cnt--;
    }

    return false; // 没有找到路径，返回 false
}

// 输出路径
void printPath() {
    cout << "(" << sx << "," << sy << ",0)";
    for (int i = 0; i < cnt; i++) {
        int x = path[i][0], y = path[i][1], d = path[i][2];
        cout << ",(" << x << "," << y << "," << d << ")";
    }
    cout << endl;
}

int main() {
    memset(vis, false, sizeof(vis));
    cnt = 0;

    cin >> n >> m; // 输入迷宫大小
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> maze[i][j]; // 输入迷宫地图
        }
    }
    cin >> sx >> sy >> ex >> ey; // 输入起点和终点坐标

    if (dfs(sx, sy)) {
        printPath();
    }
    else {
        cout << "No solution." << endl;
    }

    return 0;
}
