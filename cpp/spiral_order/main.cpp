#include <iostream>
#include <vector>
#include <functional>
#include <tuple>

using namespace std;

class Solution {
private:
    struct Bounds {
        int xLo;
        int yLo;
        int xHi;
        int yHi;
    };

    //each "direction" comes with functions to do based on the state
    //of the spiral search.
    //First moves the cursor in the proper direction
    //Second adjusts the bounds when the "move" adjusts out of bounds
    typedef tuple<
        std::function<void(int&, int&)>,
        std::function<void(Bounds&)>> Direction;

    bool isInBounds(int const x, int const y, Bounds const& bounds) {
        if (x < bounds.xLo || x >= bounds.xHi) {
            return false;
        } else if (y < bounds.yLo || y >= bounds.yHi) {
            return false;
        }
        return true;
    }

public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        Direction movement[4] = {
            make_tuple(
                [](int &x, int &y) { // 0 = east-right
                    x = x + 1;
                },
                [](Bounds &b) {
                    b.yLo++;
                }
            ),
            make_tuple(
                [](int &x, int &y) { // 1 = south-down
                    y = y + 1;
                },
                [](Bounds &b) {
                    b.xHi--;
                }
            ),
            make_tuple(
                [](int &x, int &y) { // 2 = west-left
                    x = x - 1;
                },
                [](Bounds &b) {
                    b.yHi--;
                }
            ),
            make_tuple(
                [](int &x, int &y) { // 3 = north-up
                    y = y - 1;
                },
                [](Bounds &b) {
                    b.xLo++;
                }
            )
        };
        Bounds b;
        b.xLo = 0; b.yLo = 0; b.xHi = matrix[0].size(); b.yHi = matrix.size();
        //dynamic bounds
        int xOffset = 0;
        int yOffset = 0;

        vector<int> result;
        //continue loop as long as bounds haven't closed in
        //there may be a better check that work
        int currentTravelMode = 0;
        while (b.xLo != b.xHi && b.yLo != b.yHi) {
            if (!isInBounds(xOffset, yOffset, b)) {
                //we need to do three things:
                //1 -- undo the move that landed here;
                //this is done that by leveraging the "opposite" movement, which is offset by 2
                int undoTravelMode = currentTravelMode + 2;
                if (undoTravelMode > 3) {
                    undoTravelMode = undoTravelMode - 2;
                }
                get<0>(movement[undoTravelMode])(xOffset, yOffset);
                
                //2 -- reduce the bounds we hit
                //adjust bounds based on the travel mode
                get<1>(movement[currentTravelMode])(b);

                //3 -- then move in the next direction
                currentTravelMode++;
                if (currentTravelMode > 3) {
                    currentTravelMode = 0;
                }
                get<0>(movement[currentTravelMode])(xOffset, yOffset);
            } else {
                result.push_back(matrix.at(yOffset).at(xOffset));
                //move in the next direction (which may be found invalid)
                get<0>(movement[currentTravelMode])(xOffset, yOffset);
            }
        }

        return result;
    }
};

template <class T>
void print_list(const vector<T> &vec) {
    for(const T &i:vec)
    {
        cout << "[" << i << "]";
    }
}

int main(int argc, char** argv) {
    Solution s;
    vector<vector<int>> matrix;
    matrix.push_back(vector{1, 2, 3, 4});
    matrix.push_back(vector{5, 6, 7, 8});
    matrix.push_back(vector{9, 10, 11, 12});
    vector<int> r1 = s.spiralOrder(matrix);

    cout << "Result: ";
    print_list(r1);
    cout << endl;
    

    return 0;
}
