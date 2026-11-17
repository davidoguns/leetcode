#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        if (grid.empty()) return 0;

        int height = grid.size();
        int width = grid[0].size();
        auto in_bounds = [&](int r, int c) { return r >= 0 && r < height && c >= 0 && c < width; };
        int perimeter = 0;

        for (int r = 0; r < height; ++r) {
            for (int c = 0; c < width; ++c) {
                if (grid[r][c] == 1) {
                    //start at 4, subtract by the number of neighbors
                    int perimeter_start = 4;
                    //check if the neighboring cells are 1 or 0, substract one from the
                    //perimeter for each neighboring land
                    if (in_bounds(r+1, c) && grid[r+1][c] == 1) perimeter_start--;
                    if (in_bounds(r, c+1) && grid[r][c+1] == 1) perimeter_start--;
                    if (in_bounds(r-1, c) && grid[r-1][c] == 1) perimeter_start--;
                    if (in_bounds(r, c-1) && grid[r][c-1] == 1) perimeter_start--;
                    perimeter += perimeter_start;
                }
            }
        }
        return perimeter;
    }
};

int main(int argc, char** argv) {
    Solution s;
    vector<vector<int>> v1{vector{1}};
    cout << "perimeter sum: " << s.islandPerimeter(v1) << endl;
    vector<vector<int>> v2{vector{1, 0}};
    cout << "perimeter sum: " << s.islandPerimeter(v2) << endl;
    return 0;
}

