#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cassert>
#include <array>
#include <cmath>
using namespace std;

class Solution {
public:
    std::array<int, 26> maxWord(const vector<string>& ws) {
        vector<array<int, 26>> maps;
        for (auto word : ws) {
            maps.push_back(letterCountsStaticMap(word));
        }

        array<int, 26> maxes;
        for (int i = 0; i < 26; i++) {
            maxes.at(i) = 0;
        }

        for (auto map : maps) {
            for (int i = 0; i < 26; i++) {
                maxes.at(i) = max(maxes.at(i), map.at(i));
            }
        }

        return maxes;
    }

    map<char, int> letterCounts(const string& a) {
        map<char, int> ret;
        for (auto c : a) {
            ret[c]++;
        }
        return ret;
    }

    bool containedIn(const std::array<int, 26>& left, const std::array<int, 26>& right) {
        for (int i = 0; i < 26; i++) {
            if (left.at(i) > right.at(i)) {
                return false;
            }
        }

        return true;
    }

    std::array<int, 26> letterCountsStaticMap(const string& a) {
        array<int, 26> ret;
        for (int i = 0; i < 26; i++) {
            ret[i] = 0;
        }
        for (auto c: a) {
            // cout << "index: " << c-'a' << endl;
            ret[c - 'a']++;
        }
        return ret;
    }

    // Returns True if Left is contained_in Right
    bool containedIn(map<char, int> left, map<char, int> right) {
        for (pair<char, int> kv : left) {
            char key = kv.first;
            if (right.count(kv.first) != 1 || right[kv.first] < kv.second) {
                // cout << "(kv.first, kv.second): " << kv.first << " " << kv.second << endl;
                // cout << "(right.first, right.second)" << right.count(kv.first)
                return false;
            }
        }

        return true;
    }

    // Returns True if Left is contained_in Right
    bool containedIn(const string& a, const string& b) {
        auto letterCountsForA = letterCounts(a);
        auto letterCountsForB = letterCounts(b);
        return containedIn(letterCountsForA, letterCountsForB);
    }

    bool containedInOptimized(const string& b, const map<char, int>& letterCountsForA) {
        auto letterCountsForB = letterCounts(b);
        return containedIn(letterCountsForB, letterCountsForA);
    }

    // a is universal if for all b in B, b is contained in a
    bool universal(const string& a, const vector<string>& B) {
        auto letterCountsForA = letterCounts(a);
        // vector<map<char, int>> letterCountsForAs = transform()

        return all_of(B.begin(), B.end(), [letterCountsForA, this](const string& b){
            return this->containedInOptimized(b, letterCountsForA);
        });
    }

    bool universalOptimized(const map<char, int>& letterCountForA, const vector<map<char, int>>& letterCountsForBs) {
        return all_of(letterCountsForBs.begin(), letterCountsForBs.end(), [letterCountForA, this](const map<char, int>& b) {
            return this->containedIn(b, letterCountForA);
        });
    }

    bool containedInStaticMap(const std::array<int, 26>& left, const std::array<int, 26>& right) {
        for (int i = 0; i < left.size(); i++) {
            if (left.at(i) > right.at(i)) {
                return false;
            }
        }

        return true;
    }

    bool universalExtremelyOptimized(const std::array<int, 26>& letterCountForA, const vector<std::array<int, 26>>& Bs) {
        return all_of(Bs.begin(), Bs.end(), [this, &letterCountForA](const std::array<int, 26>& letterCountForB) {
            return this->containedInStaticMap(letterCountForB, letterCountForA);
        });
    }

    vector<string> wordSubsets(vector<string>& A, vector<string>& B) {
        vector<std::array<int, 26>> letterCountsForAs(A.size());
        transform(A.begin(), A.end(), letterCountsForAs.begin(), [this](const string& a) {
            return this->letterCountsStaticMap(a);
        });

        // vector<std::array<int, 26>> letterCountsForBs(B.size());
        // transform(B.begin(), B.end(), letterCountsForBs.begin(), [this](const string& b) {
        //     return this->letterCountsStaticMap(b);
        // });

        auto maxWord = Solution().maxWord(B);

        vector<string> ret;
        for (int i = 0; i < letterCountsForAs.size(); i++) {
            auto a = letterCountsForAs[i];
            if (Solution().containedInStaticMap(maxWord, a)) {
                ret.push_back(A[i]);
            }
        }

        return ret;
        // vector<string> ret;
        // for (string a : A) {
        //     if (universal(a, B)) {
        //         ret.push_back(a);
        //     }
        // };
        // return ret;
    }
};

bool vector_equality(const vector<string>& l, const vector<string>& r) {
    if (l.size() != r.size()) {
        return false;
    }

    for (auto str : l) {
        if (std::find(r.begin(), r.end(), str) == r.end()) {
            return false;
        }
    }

    return true;
}

void test_vector_equality() {
    vector<string> l{"facebook", "google"};
    vector<string> r{"facebook", "google", "leetcode"};


    assert(!vector_equality(l, r));
    assert(vector_equality(l, vector<string>{"google", "facebook"}));
}

bool test_static_map_equality(const array<int, 26>& l, const array<int, 26>& r) {
    for (int i = 0; i < 26; i++) {
        if (l[i] != r[i]) {
            return false;
        }
    }
    return true;
}

void test_max_word() {
    auto ans = Solution().letterCountsStaticMap(string("arrow"));
    auto l = Solution().maxWord(vector<string>{"wrr", "wa", "or"});
    auto check = test_static_map_equality(l, ans);
    assert(check);
}

void test1() {
    // For example, "wrr" is a subset of "warrior", but is not a subset of "world".
    string wrr("wrr");
    string warrior("warrior");
    string world("world");
    assert(Solution().containedIn(wrr, warrior));
    assert(!Solution().containedIn(wrr, world));
}


void print_static_map(const std::array<int, 26>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        // cout << "(" << char(i+'a') <<  "," << arr.at(i) << ") ";
    }
    // cout << endl;
}

void test_static_map_equality() {
    auto wrr = Solution().letterCountsStaticMap(string("wrr"));
    auto warrior = Solution().letterCountsStaticMap(string("warrior"));
    auto world = Solution().letterCountsStaticMap(string("world"));

    // print_static_map(wrr);
    // print_static_map(warrior);
    // print_static_map(world);

    assert(Solution().containedIn(wrr, warrior));
    assert(!Solution().containedIn(wrr, world));
}

void test_universal() {
    assert(Solution().universal(string("facebook"), vector<string>{"b", "o"}));
    assert(!Solution().universal(string("apple"), vector<string>{"b", "o"}));
}

void test_universal_extremely_optimized() {
    auto facebook = Solution().letterCountsStaticMap("facebook");
    vector<std::array<int, 26>> Bs(2);
    vector<string> bs{string("e"), string("o")};
    transform(bs.begin(), bs.end(), Bs.begin(), [](const string& b){
        // cout << "strang: " << b << endl;
        auto ret = Solution().letterCountsStaticMap(b);
        print_static_map(ret);
        return ret;
    });

    print_static_map(facebook);
    print_static_map(Bs[0]);
    print_static_map(Bs[1]);


    assert(Solution().universalExtremelyOptimized(facebook, Bs));
}

void test2() {
    vector<string> A{"amazon","apple","facebook","google","leetcode"};
    vector<string> B{"e", "o"};

    auto ans = Solution().wordSubsets(A, B);
    assert(vector_equality(ans, vector<string>{"facebook", "google", "leetcode"}));
}

void test_word_subsets() {
    vector<string> A{"amazon","apple","facebook","google","leetcode"};
    vector<string> B{"ec","oc","ceo"};
    vector<string> ans{"facebook","leetcode"};

    auto my_ans = Solution().wordSubsets(A, B);
    for (auto my_answers : my_ans) {
        // cout << my_answers << " ";
    }
    // cout << endl;

    assert(vector_equality(my_ans, ans));
    assert(!vector_equality(Solution().wordSubsets(A, B), vector<string>{"google", "facebook"}));
}

void test_word_subsets2() {
    
    vector<string> A{"amazon","apple","facebook","google","leetcode"};
    vector<string> B{"e","oo"};

    vector<string> ans{"facebook","google"};

    vector<string> wrong_ans{"dafasd","sd"};

    assert(vector_equality(Solution().wordSubsets(A, B), ans));
    assert(!vector_equality(Solution().wordSubsets(A, B), wrong_ans));
}

int main() {
    test_max_word();
    test_static_map_equality();
    test_vector_equality();
    test1();
    test2();
    test_universal();
    test_universal_extremely_optimized();
    test_word_subsets();
    test_word_subsets2();
}