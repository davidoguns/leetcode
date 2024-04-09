#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/multiply-strings/
class Solution {
public:

    string multiply(string num1, string num2) {
        const string MULTIPLY_TABLE[] {
                "0",  "0",  "0",  "0",  "0",  "0",  "0",  "0",  "0",  "0",
                "0",  "1",  "2",  "3",  "4",  "5",  "6",  "7",  "8",  "9",
                "0",  "2",  "4",  "6",  "8", "10", "12", "14", "16", "18",
                "0",  "3",  "6",  "9", "12", "15", "18", "21", "24", "27",
                "0",  "4",  "8", "12", "16", "20", "24", "28", "32", "36",
                "0",  "5", "10", "15", "20", "25", "30", "35", "40", "45",
                "0",  "6", "12", "18", "24", "30", "36", "42", "48", "54",
                "0",  "7", "14", "21", "28", "35", "42", "49", "56", "63",
                "0",  "8", "16", "24", "32", "40", "48", "56", "64", "72",
                "0",  "9", "18", "27", "36", "45", "54", "63", "72", "81",
            };
        const tuple<bool, char> ADD_TABLE[] {
                {false, '0'},  {false, '1'},  {false, '2'},  {false, '3'},  {false, '4'},  {false, '5'},  {false, '6'},  {false, '7'},  {false, '8'},  {false, '9'},
                {false, '1'},  {false, '2'},  {false, '3'},  {false, '4'},  {false, '5'},  {false, '6'},  {false, '7'},  {false, '8'},  {false, '9'},  {true, '0'},
                {false, '2'},  {false, '3'},  {false, '4'},  {false, '5'},  {false, '6'}, {false, '7'}, {false, '8'}, {false, '9'}, {true, '0'}, {true, '1'},
                {false, '3'},  {false, '4'},  {false, '5'},  {false, '6'}, {false, '7'}, {false, '8'}, {false, '9'}, {true, '0'}, {true, '1'}, {true, '2'},
                {false, '4'},  {false, '5'},  {false, '6'}, {false, '7'}, {false, '8'}, {false, '9'}, {true, '0'}, {true, '1'}, {true, '2'}, {true, '3'},
                {false, '5'},  {false, '6'}, {false, '7'}, {false, '8'}, {false, '9'}, {true, '0'}, {true, '1'}, {true, '2'}, {true, '3'}, {true, '4'},
                {false, '6'},  {false, '7'}, {false, '8'}, {false, '9'}, {true, '0'}, {true, '1'}, {true, '2'}, {true, '3'}, {true, '4'}, {true, '5'},
                {false, '7'},  {false, '8'}, {false, '9'}, {true, '0'}, {true, '1'}, {true, '2'}, {true, '3'}, {true, '4'}, {true, '5'}, {true, '6'},
                {false, '8'},  {false, '9'}, {true, '0'}, {true, '1'}, {true, '2'}, {true, '3'}, {true, '4'}, {true, '5'}, {true, '6'}, {true, '7'},
                {false, '9'},  {true, '0'}, {true, '1'}, {true, '2'}, {true, '3'}, {true, '4'}, {true, '5'}, {true, '6'}, {true, '7'}, {true, '8'},
            };
        const auto to_index = [] (const char &d1, const char &d2) -> size_t {
            size_t v1 = size_t(d1 - '0');
            size_t v2 = size_t(d2 - '0');
            return (v1 + v2 * 10);
        };
        const auto accumulate = [&ADD_TABLE, &to_index](const string &num1, string &num2) -> string {
            vector<char> buffer;
            buffer.reserve(max(num1.length(), num2.length())+2);
            bool carry = false;

            for (int idx = 1; idx <= max(num1.length(), num2.length()); ++idx) {
                // cout << "num1 idx: " << int(num1.length()) - idx << endl;
                // cout << "num2 idx: " << int(num2.length()) - idx << endl;
                char d1 = int(num1.length() - idx) >= 0 ? num1.at(num1.length() - idx) : '0';
                char d2 = int(num2.length() - idx) >= 0 ? num2.at(num2.length() - idx) : '0';
                auto sum_tuple = ADD_TABLE[to_index(d1, d2)];
                bool carry_again = get<0>(sum_tuple);
                if (carry) { // test the carry of the prior column
                    //add one to it
                    sum_tuple = ADD_TABLE[to_index(get<1>(sum_tuple), '1')];
                    //adding the carry could be what causes a carry to happen
                    if (!carry_again) {
                        carry_again = get<0>(sum_tuple);
                    }
                }
                carry = carry_again;
                //preprend digit
                // result = get<1>(sum_tuple) + result;
                buffer.push_back(get<1>(sum_tuple));
            }
            if (carry) {
                //we have one more column of 1 to prepend to the front
                buffer.push_back('1');
            }

            return std::move(string(buffer.rbegin(), buffer.rend())); 
        };

        string sum{"0"};
        //for each digit in one number, multiply by the other digits
        for (size_t n1_idx = 1; n1_idx <= num1.length(); ++n1_idx) {
            for (size_t n2_idx = 1; n2_idx <= num2.length(); ++n2_idx) {
                auto mt_index = to_index(num1.at(num1.length()-n1_idx), num2.at(num2.length()-n2_idx));
                size_t sum_mag = n1_idx + n2_idx - 2;
                string mt_result = MULTIPLY_TABLE[mt_index];
                mt_result.append(sum_mag, '0'); // adding n zeros at the end is multiplying by 10^n
                sum = accumulate(sum, mt_result);
            }
        }

        size_t trim_leading = 0;
        while (trim_leading < sum.length() && sum.at(trim_leading) == '0') {
            ++trim_leading;
        }
        if (trim_leading == sum.length()) {
            --trim_leading;
        }

        return sum.substr(trim_leading);
    }
};

int main(int argc, char *arg[]) {
    Solution s;
    cout << s.multiply("9133", "0") << endl;
    cout << s.multiply("999", "999") << endl;
    cout << s.multiply("123", "456") << endl;
    cout << s.multiply("15", "6") << endl;
    cout << s.multiply("15", "15") << endl;
    cout << s.multiply("25", "25") << endl;

    return 0;
}
