// matrix: 2D
// contain 1 or 0
// given position [x, y] indicating index of row and col respectively
// find the cell that has closest distance to the given cell

// closest distance: mahathan distance

// closest distance = K -> do bfs K-th level

// Output: the nereast distance

// Edge case:
// + Not find nearest 0 => -1
// + 
 


// [[0, 1, 1, 1],
// [1, 1, [1], 1]],
// [[0, 1, 1, 0]]

// Time: n * m (n is number of rows, m is number of columns)
// Space: n * m (n is number of rows, m is number of columns)

// [[0, 1, 1, 1],
// [1, 1, 1, 1]],
// [[0, 1, 1, 0]]

#include <bits/stdc++.h>
using namespace std;

int findNearestZeroCellFromCurrentCell(vector<vector<int>> &matrix, int x, int y) {
    if (matrix[x][y] == 0) {
        return 0;
    }
    
    int n = matrix.size();
    int m = matrix[0].size();
    vector<pair<int,int>> moves = {{-1,0},{0,-1},{1,0},{0,1}};
    vector<vector<int>> visited(n, vector<int>(m, false));
    deque<pair<int,int>> q;
    q.push_front({x, y});
    visited[x][y] = 1;
    int distance = 0;
    while ((int) q.size()) {
        int sz = q.size();
        for (int i = 0; i < sz; i++) {
            pair<int,int> u = q.back();
            q.pop_back();
            int curX = u.first;
            int curY = u.second;
            if (matrix[curX][curY] == 0) {
                return distance;
            }
            for (auto &currentMove : moves) {
                int nextX = curX + currentMove.first;
                int nextY = curY + currentMove.second;
                if (0 <= nextX && nextX < n && 0 <= nextY && nextY < m) {
                    if (!visited[nextX][nextY]) {
                        visited[nextX][nextY] = 1;
                        q.push_front({nextX, nextY});
                    }
                }
            }
        }
        distance++;
    }
    return -1;
}

// Time: n * m (n is number of rows, m is number of columns)
// Space: n * m (n is number of rows, m is number of columns)
vector<vector<int>> findNearestZeroCellForAnyCell(vector<vector<int>> &matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    vector<pair<int,int>> moves = {{-1,0},{0,-1},{1,0},{0,1}};
    vector<vector<int>> dist(n, vector<int>(m, -1));
    deque<pair<int,int>> q;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == 0) {
                dist[i][j] = 0;
                q.push_front({i, j});
            }
        }
    }

    while ((int) q.size()) {
        int sz = q.size();
        for (int i = 0; i < sz; i++) {
            pair<int,int> u = q.back();
            q.pop_back();
            int curX = u.first;
            int curY = u.second;
            for (auto &currentMove : moves) {
                int nextX = curX + currentMove.first;
                int nextY = curY + currentMove.second;
                if (0 <= nextX && nextX < n && 0 <= nextY && nextY < m) {
                    if (dist[nextX][nextY] == -1) {
                        dist[nextX][nextY] = dist[curX][curY] + 1;
                        q.push_front({nextX, nextY});
                    }
                }
            }
        }
    }

    return dist;
}

int main() {
    vector<vector<int>> matrix = {{0, 1, 1, 1}, 
                                  {1, 1, 1, 1},
                                  {0, 1, 1, 1}};
    int initX = 1, initY = 2;
    int distance = findNearestZeroCellFromCurrentCell(matrix, initX, initY);

    return 0;
}
