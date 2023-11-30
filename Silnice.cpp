#include "Silnice.h"
#include <vector>
#include <cmath>
#include <iostream>

Silnice::Silnice(TerrainMap& m, std::string name_in, Point start_in, Point finish_in) : Path(m, name_in, start_in, finish_in) {}

bool Silnice::find() {
    const int MAX_DISTANCE = 1000000;
    std::vector<std::vector<int>> dist(map.nx, std::vector<int>(map.ny, MAX_DISTANCE));
    std::vector<std::vector<bool>> visited(map.nx, std::vector<bool>(map.ny, false));
    std::vector<std::vector<Point>> prev(map.nx, std::vector<Point>(map.ny, {-1, -1}));

    dist[start.x][start.y] = 0;

    for (int count = 0; count < map.nx * map.ny - 1; ++count) {
        Point u = {-1, -1};
        int min_distance = MAX_DISTANCE;

        for (int x = 0; x < map.nx; ++x) {
            for (int y = 0; y < map.ny; ++y) {
                if (!visited[x][y] && dist[x][y] < min_distance) {
                    u = {x, y};
                    min_distance = dist[x][y];
                }
            }
        }

        if (u.x == -1 || u == finish) break;

        visited[u.x][u.y] = true;

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) continue;

                Point v = {u.x + dx, u.y + dy};
                if (!map.validCoords(v) || map.alt(v) <= 0) continue;

                double incline = (map.alt(u) - map.alt(v))/10;
                if (incline > 6.0) continue;

                int new_dist = dist[u.x][u.y] + 1;

                if (new_dist < dist[v.x][v.y]) {
                    dist[v.x][v.y] = new_dist;
                    prev[v.x][v.y] = u;
                }
            }
        }
    }

    Point u = finish;
    if (prev[u.x][u.y].x == -1) return false;

    while (prev[u.x][u.y].x != -1) {
        path.push_back(u);
        u = prev[u.x][u.y];
    }

    path.push_back(start);

    return true;
}
