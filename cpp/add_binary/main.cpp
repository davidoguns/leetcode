#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;

class Solution {
public:
    string addBinary(string a, string b) {
        vector<char> result;
        result.reserve(std::max(a.length(), b.length()) + 1);
        auto a_itr = a.rbegin();
        auto b_itr = b.rbegin();
        int carry = 0;

        while (!(a_itr == a.rend() && b_itr == b.rend())) {
            int digit_sum = carry;
            if (a_itr != a.rend()) {
                if (*a_itr == '1') {
                    ++digit_sum;
                }
                ++a_itr;
            }
            if (b_itr != b.rend()) {
                if (*b_itr == '1') {
                    ++digit_sum;
                }
                ++b_itr;
            }

            switch (digit_sum) {
                case 0:
                    result.push_back('0');
                    carry = 0;
                    break;
                case 1:
                    result.push_back('1');
                    carry = 0;
                    break;
                case 2:
                    result.push_back('0');
                    carry = 1;
                    break;
                case 3:
                    result.push_back('1');
                    carry = 1;
                    break;
            }
        } // while

        if (carry != 0) {
            result.push_back('1');
        }
        string result_str;
        result_str.append(result.rbegin(), result.rend());
        return result_str;
    }
};

int main(int argc, char **argv) {
    using std::cout;
    using std::endl;
    Solution s;
    cout << "Add result: [" << s.addBinary("1", "1") << "]"  << endl;
    cout << "Add result: [" << s.addBinary("11", "1") << "]"  << endl;
    return 0;
}
