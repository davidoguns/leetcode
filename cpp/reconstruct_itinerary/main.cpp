#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
    typedef unordered_map<string, multiset<string>> TicketMap;
    vector<string> findItinerary(vector<vector<string>> &tickets) {
        TicketMap ticket_map;
        vector<string> result;
       
        //build map of itinerary
        for(auto const & ticket:tickets) {
            auto dept_set = ticket_map.find(ticket[0]);
            if (dept_set == ticket_map.end()) {
                ticket_map[ticket[0]] = multiset<string>();
                dept_set = ticket_map.find(ticket[0]);
            }
            dept_set->second.insert(ticket[1]);
        }

        result.push_back("JFK");
        findItinerary(ticket_map, result);
        return std::move(result); 
    }

    void summarize_map(TicketMap &ticket_map) {
        for_each(ticket_map.begin(), ticket_map.end(), [](auto entry) {
            cout << "key " << entry.first << " {" << entry.second.size() << "} = ";
            for_each(entry.second.begin(), entry.second.end(), [](auto value) {
                cout << value << ", ";
            });
            cout << endl;
        });
    }

    bool findItinerary(TicketMap &ticket_map, vector<string> &result) {
        //an optimization would be: instead of counting the map size, over and over again, we could track it
        //along with modifications that add and remove from it, and never count again
        auto num_tickets = multimap_size(ticket_map);
        if (num_tickets != 0) {
            auto current = result.back();
            auto dest_set_pair_itr = ticket_map.find(current);
            if (dest_set_pair_itr != ticket_map.end()) {
                auto &dest_set = dest_set_pair_itr->second;
                //we would possibly make a copy of destination set so call stack nested modifications don't mess up this iteration
                //however, we actually need a de-duped set here so we don't entertain iterations that won't produce different results
                //from here on out
                set<string> dest_set_cpy;
                dest_set_cpy.insert(dest_set.begin(), dest_set.end());
                for (auto dest_itr = dest_set_cpy.cbegin(); dest_itr != dest_set_cpy.cend(); ++dest_itr) {
                    auto &dest_value = *dest_itr;
                    result.push_back(dest_value);
                    //we are going to modify the actual "multiset" here
                    dest_set.erase(dest_set.find(dest_value));
                    if (num_tickets == 1 || findItinerary(ticket_map, result)) {
                        return true;
                    }
                    dest_set.insert(dest_value);
                    result.pop_back();
                }
                return false;
            }
            return false;
        } else {
            //ticket map is empty, and we're tracking forward in order
            return true;
        }
    }

    size_t multimap_size(TicketMap const &ticket_map) {
        size_t count = 0;
        for (auto const &pair:ticket_map) {
            count += pair.second.size();
        }
        return count;
    }

    bool multimap_empty(TicketMap const &ticket_map) {
        return multimap_size(ticket_map) == 0;
    }
};

int main(int argc, char *argv[]) {
    Solution s;
    // vector<vector<string>> tickets{{"MUC","LHR"},{"JFK","MUC"},{"SFO","SJC"},{"LHR","SFO"}};
    // auto ans = s.findItinerary(tickets);
    // cout << "Solution: ";
    // for (auto const &ap : ans) {
    //     cout << ap << ", ";
    // }
    // cout << endl;
    //
    // vector<vector<string>> tickets2{{"JFK","KUL"},{"JFK","NRT"},{"NRT","JFK"}};
    // auto ans2 = s.findItinerary(tickets2);
    // cout << "Solution: ";
    // for (auto const &ap : ans2) {
    //     cout << ap << ", ";
    // }
    // cout << endl;
    //
    vector<vector<string>> tickets3{{"JFK","SFO"},{"JFK","ATL"},{"SFO","JFK"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"}};
    auto ans3 = s.findItinerary(tickets3);
    cout << "Solution: ";
    for (auto const &ap : ans3) {
        cout << ap << ", ";
    }
    cout << endl;

    return 0;
}
