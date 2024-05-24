#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

//https://leetcode.com/problems/integer-to-roman
class Solution {
public:
    vector<tuple<int, string, size_t>> table = {
        make_tuple(3000, "MMM", 3),
        make_tuple(2000, "MM", 3),
        make_tuple(1000, "M", 3),
        make_tuple(900, "CM", 12),
        make_tuple(800, "DCCC", 12),
        make_tuple(700, "DCC", 12),
        make_tuple(600, "DC", 12),
        make_tuple(500, "D", 12),
        make_tuple(400, "CD", 12),
        make_tuple(300, "CCC", 12),
        make_tuple(200, "CC", 12),
        make_tuple(100, "C", 12),
        make_tuple(90, "XC", 21), //12
        make_tuple(80, "LXXX", 21),
        make_tuple(70, "LXX", 21),
        make_tuple(60, "LX", 21),
        make_tuple(50, "L", 21),
        make_tuple(40, "XL", 21),
        make_tuple(30, "XXX", 21),
        make_tuple(20, "XX", 21),
        make_tuple(10, "X", 21),
        make_tuple(9, "IX", 0), // 21
        make_tuple(8, "VIII", 0), //jump index at this point is meaningless as the number should cause an exit condition
        make_tuple(7, "VII", 0),  //jumping to 0 will allow larger than expected numbers to complete, but produce invalid
        make_tuple(6, "VI", 0),   //results. If num < 0 at the start, then the loop will exit after scanning vector once
        make_tuple(5, "V", 0),
        make_tuple(4, "IV", 0),
        make_tuple(3, "III", 0),
        make_tuple(2, "II", 0),
        make_tuple(1, "I", 0),
    };
    string intToRoman(int num) {
        //using a vector because we're actually going to subtract instead of divide
        //I'm sure there's an optimized way to constexpr static this vector and it's content as it should be

        //The third member of the tuple is a "jump" index that is used to push the loop
        //along faster to the next index it should bother checking if the current value
        //was successfully subtracted from the integer. The jump list is only valid of course
        //with valid input (0 <= num <= 3999). Outside of that, the code will fall into non
        //terminal conditions
        
        //Not sure if the "jumping" really helps all that much as leetcode submissions don't exactly
        //use accurate performance measures. The same submission may be bottom 5% or top 25% if it's
        //all under 15ms or less.
        string result; //0 is empty string in roman numerals?
        size_t idx = 0;
        while (idx < table.size())  { //terminal condition is only really used if num < 0
            auto const& tupl = table.at(idx);
            auto new_num = num - get<0>(tupl);
            if (new_num >= 0) {
                num = new_num;
                result.append(get<1>(tupl));
                if (num == 0) {
                    break;
                }
                //use jump index to skip a few checks
                idx = get<2>(tupl);
            } else {
                //otherwise increment normally
                ++idx;
            }
        }

        return result;
    }
};

int main(int argc, char *argv[]) {
    Solution s;
    cout << "Solution: " << s.intToRoman(3749) << endl;
    cout << "Solution: " << s.intToRoman(58) << endl;
    cout << "Solution: " << s.intToRoman(1994) << endl;
    return 0;
}
