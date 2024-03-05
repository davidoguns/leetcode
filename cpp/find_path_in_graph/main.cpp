#include <vector>
#include <set>
#include <algorithm>

using namespace std;

// https://leetcode.com/problems/find-if-path-exists-in-graph/description/
class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        set<int> visited;
        set<int> just_added;
        set<int> to_add;

        just_added.insert(source);

        if (source == destination) {
            return true; //early exist
        }
        
        while (!just_added.empty()) {
            for_each(edges.begin(), edges.end(), [&](auto edge) {
                if (just_added.find(edge[0]) != just_added.end()) {
                    if (visited.find(edge[1]) == visited.end()) {
                        to_add.insert(edge[1]);
                    } 
                }
                if (just_added.find(edge[1]) != just_added.end()) {
                    if (visited.find(edge[0]) == visited.end()) {
                        to_add.insert(edge[0]);
                    } 
                }
            });
            if (to_add.empty()) {
                // this means the next iteration can't find anything, so an early
                // false exists here
                return false;
            }
            if (to_add.find(destination) != to_add.end()) {
                return true; //found our path, can exit now
            }

            just_added.clear();
            for (auto v : to_add) {
                just_added.insert(v);
                visited.insert(v);
            }
            to_add.clear();
        }
        //if the above loop didn't find anything, none exists
        return false;
    }
};

int main(int argc, char *arv[]) {

    return 0;
}
