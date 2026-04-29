#include <iostream>
#include <unordered_map>
#include <vector>
#include <tuple>

using namespace std;

template <>
struct std::hash<tuple<int,int>> {
    size_t operator()(const tuple<int, int> &p) const {
    //weak, but this isn't exactly the point here
    return hash<int>{}(get<0>(p)) ^ hash<int>{}(get<1>(p));
  }
};

class Solution {
public:
    int _maxArea(vector<int>& height, size_t front_index, size_t back_index, unordered_map<tuple<int, int>, int>& memo) {
        if (front_index >= back_index) {
            return 0;
        }
        
        const tuple<int, int> key = make_tuple(front_index, back_index);
        auto existing = memo.find(key);
        if (existing != memo.end()) {
            //short circuiting the calculation
            return existing->second;
        }

        int area = (back_index - front_index) * std::min(height[front_index], height[back_index]);
        int area_front_move = _maxArea(height, front_index+1, back_index, memo);
        int area_back_move = _maxArea(height, front_index, back_index-1, memo);
        int max_area = std::max(area, std::max(area_front_move, area_back_move));
        memo.insert(make_pair(key, max_area));

        return max_area;
    }

    int maxArea(vector<int>& height) {
        unordered_map<tuple<int, int>, int> memo;
        int result = _maxArea(height, 0, height.size()-1, memo);
        return result; 
    }
};

int main(int argc, char *argv[]) {
    Solution s;
    vector<int> vec1{1, 8, 6, 2, 5, 4, 8, 3, 7};
    cout << "Max area: " << s.maxArea(vec1) << endl;
    vector<int> vec2{1, 8, 6, 2, 5, 4, 8, 25, 7};
    cout << "Max area: " << s.maxArea(vec2) << endl;
    vector<int> vec3{1, 3, 2, 5, 25, 24, 5};
    cout << "Max area: " << s.maxArea(vec3) << endl;
    return 0;
}
