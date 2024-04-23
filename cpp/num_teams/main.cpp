#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

// https://leetcode.com/problems/count-number-of-teams/

class ISolution {
public:
    virtual int numTeams(vector<int>& rating) = 0;
};

class Solution : public ISolution {
public:
    virtual int numTeams(vector<int>& rating) {
        int result = 0;
        vector<size_t> falling_from(rating.size(), 0);
        vector<vector<size_t>> falling_to(rating.size(), vector<size_t>{});
        vector<size_t> rising_from(rating.size(), 0);
        vector<vector<size_t>> rising_to(rating.size(), vector<size_t>{});
        //pre calculate the counts for the last iteration after having done the first two
        //to reduce the explosive growth
        for (size_t target_idx = rating.size()-1; target_idx > 0; --target_idx) {
            int target_value = rating.at(target_idx);
            for (int source_idx = target_idx-1; source_idx >= 0; --source_idx) {
                int source_value = rating.at(source_idx);
                if (target_value > source_value) {
                    //rising
                    ++rising_from.at(source_idx);
                    rising_to.at(source_idx).push_back(target_idx);
                } else {
                    //falling
                    ++falling_from.at(source_idx);
                    falling_to.at(source_idx).push_back(target_idx);
                }
            }
        }

        if (rating.size() < 3) {
            return 0;
        }
        for (size_t rating_idx = 0; rating_idx < rating.size() - 2; ++rating_idx) {
            result += count_follow(rating_idx, rising_to, rising_from);
            result += count_follow(rating_idx, falling_to, falling_from);
        }

        return result;
    }
private:
    int count_follow(size_t index, vector<vector<size_t>> const & to, vector<size_t> const & counts) {
        int count = 0;
        for_each(to.at(index).begin(), to.at(index).end(), [&](auto count_idx) {
            count += int(counts.at(count_idx));
        });
        return count;
    }
};

//this approach tries everything literally; O(n^3)
class SolutionSlow : public ISolution {
public:
    virtual int numTeams(vector<int>& rating) {
        int result = 0;

        if (rating.size() < 3) {
            return 0;
        }
        for (size_t rating_idx = 0; rating_idx < rating.size() - 2; ++rating_idx) {
            auto r = rating.at(rating_idx);
            for (size_t mid_idx = rating_idx + 1; mid_idx < rating.size() - 1; ++mid_idx) {
                auto r_cmp = rating.at(mid_idx);
                if (r_cmp > r) {
                    for (size_t last_idx = mid_idx + 1; last_idx < rating.size(); ++last_idx) {
                        //add one for every digit still rising from r_cmp
                        auto l_cmp = rating.at(last_idx);
                        if (l_cmp > r_cmp) ++result;
                    }
                }
                else if (r_cmp < r) {
                    for (size_t last_idx = mid_idx + 1; last_idx < rating.size(); ++last_idx) {
                        //add one for every digit still falling from r_cmp
                        auto l_cmp = rating.at(last_idx);
                        if (l_cmp < r_cmp) ++result;
                    }
                }
            }
        }

        return result;
    }
};

//this approach builds a tree, and then traverses, generating every possible unique path of length 3
class SolutionOld : public ISolution {
public:
    virtual int numTeams(vector<int>& rating) {
        int result = 0;
        //both maps are "this node" -> "optional from node"; empty if node has no from
        multimap<int, int> rising;
        multimap<int, int> falling;
        vector<int> prior_ratings;
        prior_ratings.reserve(rating.size());

        for (auto ritr = rating.begin(); ritr != rating.end(); ++ritr) {
            int r = *ritr;
            for (auto prior_rating:prior_ratings) {
                if (prior_rating < r) {
                    //we are rising compared to this key so add a mapping
                    rising.insert(std::make_pair(r, prior_rating));
                }
                if (prior_rating > r) {
                    //we are falling compared to this key so add a mapping
                    falling.insert(std::make_pair(r, prior_rating));
                }
            }
            prior_ratings.push_back(r);
        }

        for_each(prior_ratings.begin(), prior_ratings.end(), [&](auto r) {
            bottom_up_count(rising, r, 3, result);
            bottom_up_count(falling, r, 3, result);
        });
        return result;
    }

private:
    void bottom_up_count(multimap<int, int> const& map, int key, int level, int& count) {
        if (level == 1) {
                //if it's found at this was the last node to search while traversing, count up
                ++count;
        }
        else {
            auto map_itr = map.lower_bound(key);
            //check if key is found in map otherwise, keep scanning up through
            //all nodes that mapped to previous and subtract one from level since
            //we traversed a hop
            while (map_itr != map.upper_bound(key)) {
                bottom_up_count(map, map_itr->second, level - 1, count);
                ++map_itr;
            }
        }
    }
};

void test_teams(ISolution* s) {
    vector<int> input1{1, 2, 3};
    cout << "number of teams: " << s->numTeams(input1) << endl;
    vector<int> input2{1, 2, 3, 4};
    cout << "number of teams: " << s->numTeams(input2) << endl;
    vector<int> input3{1, 2, 3, 4, 5};
    cout << "number of teams: " << s->numTeams(input3) << endl;
    vector<int> input4{1, 2, 3, 4, 5, 6};
    cout << "number of teams: " << s->numTeams(input4) << endl;
    vector<int> input5{1, 2, 3, 4, 5, 6, 7};
    cout << "number of teams: " << s->numTeams(input5) << endl;
    vector<int> input6{1, 2, 3, 4, 5, 6, 7, 8};
    cout << "number of teams: " << s->numTeams(input6) << endl;
    vector<int> input7{1, 2, 3, 4, 5, 6, 7, 8, 9};
    cout << "number of teams: " << s->numTeams(input7) << endl;
}

int main(int argc, char *argv[]) {
    ISolution *s = new Solution();
    ISolution *sslow = new SolutionSlow();
    ISolution *sold = new SolutionOld();
    test_teams(s);
    cout << "==========================================================" << endl;
    test_teams(sold);
    cout << "==========================================================" << endl;
    test_teams(sslow);

    // vector<int> input4{2032,2688,1116,1016,1476,2117,2178,144,52,1811,1684,1866,895,2393,2632,508,653,2000,1393,369,1897,171,2492,2583,1319,2756,206,136,1922,1806,1952,462,379,2266,1453,20,172,1242,2545,853,1536,1958,491,313,1265,1104,1888,673,1953,1820,1313,2293,1174,767,929,611,665,2626,393,2052,1149,1362,2051,21,1959,189,199,1558,1382,583,2466,1096,105,1515,2001,2549,308,2329,1048,2563,2372,1152,2976,234,1859,2581,196,2555,1280,557,2067,1068,1962,2433,1401,1559,972,1595,2744,1225,978,758,181,1840,2547,2403,154,2711,1475,2014,648,2081,1785,2044,166,2249,1413,1144,1070,734,2239,484,2785,2907,96,1561,2156,1972,2321,801,692,1711,1577,1933,2497,161,582,1271,1974,149,1852,724,1854,2130,754,82,1833,1813,1300,322,1674,1798,440,348,2576,2388,2591,1816,2356,1202,2243,1301,1628,741,900,1752,2020,1119,1479,721,745,186,2007,2676,2822,1112,182,2337,122,2502,2515,2734,409,2074,2931,573,2245,2700,1658,2641,94,2216,2513,908,1555,952,1266,784,2928,2102,1893,2048,1901,1272,956,2065,472,2609,2755,768,1697,1195,2899,213,2789,2952,2327,1344,310,2118,1830,2224,2749,148,2690,2777,324,2322,2248,187,1165,2175,1170,1290,1364,2593,1942,2256,2562,395,256,2079,752,2120,2923,804,865,934,933,211,2797,882,1920,1219,1827,468,401,1498,1934,2837,2111,1929,538,1793,1191,574,2105,2585,391,2396,744,2119,597,2373,389,626,2426,1932,1387,1837,2505,2802,2235,2171,2680,1823,896,2036,2401,1976,964,1478,367,682,2906,319,2174,1169,425,1180,264,380,2557,2574,2895,999,1508,377,1567,1543,1748,1587,780,1380,1916,2452,2269,1051,1114,1551,2965,1946,240,157,46,805,47,104,1713,2561,504,997,35,1669,1867,1909,1998,2559,910,2908,1636,194,1131,359,2195,870,994,2622,572,2422,1007,374,2753,2969,293,423,1297,50,1315,1512,1106,1239,1375,2650,39,849,1652,603,2041,108,1863,696,2182,479,788,2148,2988,1746,443,2544,515,333,478,1255,781,1292,634,959,1947,1677,1872,197,242,2693,2885,1629,1173,314,1200,1572,2548,2187,1679,2495,686,2501,1815,2432,505,707,1237,476,1539,958,195,2880,2397,1098,365,1032,2614,1374,1573,2139,248,2717,2191,1493,1227,2246,89,1483,1759,110,2459,2077,1631,969,598,791,2228,1005,2436,1410,2872,2250,1258,415,1826,1026,580,1504,474,1420,2512,1033,1666,1217,419,1989,2096,620,2302,579,2030,2721,1755,810,2172,119,2556,1358,1419,1141,795,1349,1895,265,2770,325,2348,1715,383,2094,1023,1610,1871,2638,1388,2375,2635,1522,1495,2183,1055,685,2517,1843,1370,1162,2856,566,2026,2778,1285,150,1960,433,2113,2073,1240,747,2602,1688,986,2071,2425,539,529,1900,2309,796,798,2941,699,251,2643,1259,1537,233,2350,27,1606,2703,2229,773,901,434,1566,1136,175,13,659,1052,2826,1654,2809,602,737,1604,2633,1730,555,133,1491,1727,2451,543,435,2529,1318,2305,30,1359,575,1949,2787,60,1120,2820,1562,2606,1335,2085,2710,2893,2283,936,1594,2323,2022,1528,117,1767,2312,2324,29,1857,1448,1753,1721,1836,678,2799,2605,998,1496,74,2407,1651,1719,2850,92,2271,2121,403,1637,2919,2740,1706,1801,1747,1967,1057,2185,1693,127,2739,2253,302,1894,1422,2668,294,863,2219,2902,1570,2075,155,2509,1926,31,390,2109,1462,262,2435,1130,245,37,2301,1295,2803,893,159,1464,2378,1887,1518,1441,1160,503,2854,1814,1579,970,835,2454,318,664,782};
    // cout << "number of teams: " << s.numTeams(input4) << endl;
    return 0;
}
