#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) {
            return std::move(s);
        }
        string result; //is this more optimal than reserving in a separate line?
        result.reserve();
        //track which direction we're shifting in
        int shift_row = 1;
        int row_position = 0;
        vector<list<char>> letter_rows(numRows);
        for (int i = 0; i < numRows; ++i) {
            letter_rows[i] = list<char>();
        }

        for (char ch:s) {
            letter_rows[row_position].push_back(ch);
            
            //increment position by shift, bouncing back and forth
            row_position += shift_row;
            if (row_position == numRows) {
                shift_row = -1;
                row_position = numRows-2;
            } else if (row_position < 0) {
                shift_row = 1;
                row_position = 1;
            }
        }

        for (int i = 0; i < numRows; ++i) {
            result.append(letter_rows[i].begin(), letter_rows[i].end());
        }

        return std::move(result);
    }
};

int main(int argc, char *argv[]) {
    Solution s;
    cout << "String: " << s.convert("PAYPALISHIRING", 3) << endl;
    cout << "String: " << s.convert("PAYPALISHIRING", 4) << endl;
    cout << "String: " << s.convert("A", 1) << endl;

    return 0;
}
