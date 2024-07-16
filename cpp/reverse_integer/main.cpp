#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

//https://leetcode.com/problems/reverse-integer/
class Solution {
public:
    int reverse(int x) {
        auto get_digit = [](int num, int digit) -> int {
            num /= pow(10, digit);
            return num % 10;
        };
        auto num_digits_f = [](int num) -> size_t {
            int digits = 0;
            while (num > 0) {
                num /= 10;
                digits += 1;
            }
            return digits;
        };
        bool is_negative = false;
        if (x < 0) {
            if (x == std::numeric_limits<int>::min()) {
                return 0;
            }
            x = -x;
            is_negative = true;
        }

        int reversed = 0;
        size_t num_digits = num_digits_f(x);
        for (int i = 0; i < num_digits; ++i) {
            if (i != 0) {
                if (reversed > (std::numeric_limits<int>::max() / 10)) {
                    return 0;
                }
                reversed *= 10;
            }
            reversed += get_digit(x, i);
        }

        if (is_negative) {
            reversed = -reversed;
        }

        return reversed;
    }
};

int main(int argc, char *argv[]) {
    Solution s;

    cout << "Reversed: " << s.reverse(123) << endl;
    return 0;
}
