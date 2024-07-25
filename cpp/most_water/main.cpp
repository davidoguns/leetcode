#include <iostream>
#include <vector>

using namespace std;


// Not quite correct
class Solution {
public:
    int maxArea(vector<int>& height) {
        int front_index = 0;
        int back_index = height.size() - 1;
        int max_area = 0;

        if (height.size() < 2) {
            return 0; //must have at least two sides
        }

        while (front_index < back_index) {
            int area = std::min<int>(height[front_index], height[back_index]) *
                    (back_index - front_index);
            // cout << "front index: " << front_index << "; back index: " << back_index 
            //     << "; gap = " << (back_index - front_index) << endl;
            // cout << "Area: " << area << "; front = " << height[front_index] << "; back = "
            //     << height[back_index] << endl << endl;
            if (area > max_area) {
                max_area = area;
            }
            //decision which side to move is based on which will "shrink less"
            //or "gain more". We have no choice but to lose 1 unit on X as we close
            //in, but we do have a chose to vertically decline slower
            int front_next_area = std::min<int>(height[front_index+1], height[back_index]) *
                (back_index - (front_index+1));
            int back_next_area = std::min<int>(height[front_index], height[back_index - 1]) *
                ((back_index-1) - front_index);
            if (front_next_area > back_next_area) {
                //move the back down one
                ++front_index;
            } else {
                --back_index;
            }
        } 

        return max_area; 
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
