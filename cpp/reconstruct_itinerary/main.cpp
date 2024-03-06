#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
    typedef map<string, multiset<string>> TicketMap;
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
        if (findItinerary(ticket_map, result)) {
            //actual positive result found, versus a "used what was possible" return
            cout << "exhausted all tickets..." << endl;
        }

        return std::move(result); 
    }

    bool findItinerary(TicketMap &ticket_map, vector<string> &result) {
        if (!multimap_empty(ticket_map)) {
            auto current = result.back();
            auto dest_set_pair_itr = ticket_map.find(current);
            if (dest_set_pair_itr != ticket_map.end()) {
                auto &dest_set = dest_set_pair_itr->second;
                //make a copy of destination set so call stack nested modifications don't mess up this iteration
                auto dest_set_cpy(dest_set);
                for (auto dest_itr = dest_set_cpy.begin(); dest_itr != dest_set_cpy.end(); ++dest_itr) {
                    auto &dest_value = *dest_itr;
                    result.push_back(dest_value);
                    //we are going to modify the actual "multiset" here
                    dest_set.erase(dest_set.find(dest_value));
                    if (multimap_empty(ticket_map) || findItinerary(ticket_map, result)) {
                        return true;
                    }
                    result.pop_back();
                }
                //restore destination set as we captured before passing the map along.
                //not sure if this does what I think
                dest_set = std::move(dest_set_cpy); 
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

    vector<vector<string>> tickets2{{"JFK","KUL"},{"JFK","NRT"},{"NRT","JFK"}};
    auto ans2 = s.findItinerary(tickets2);
    cout << "Solution: ";
    for (auto const &ap : ans2) {
        cout << ap << ", ";
    }
    cout << endl;
//

    return 0;
}
