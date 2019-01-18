#include <iostream>
#include <queue>
#include <vector>
#include <set>
using namespace std;

void printPermutations(const vector<vector<int>>& perms) {
    cout << "[\n";
    for (auto perm : perms) {
        cout << "\t[";
        for (int i = 0; i < perm.size(); i++) {
            cout << perm[i] << (i != perm.size() - 1 ? "," : "");
        }
        cout << "]\n";
    }
    cout << "]" << endl;
}

void printVector(const vector<int>& v) {
    cout << "[";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << (i != v.size() - 1 ? "," : "");
    }
    cout << "]\n";
}

void testPrint() {
    vector<vector<int>> a = {
        {1, 2, 3},
        {1, 3, 2},
        {2, 1, 3},
        {2, 3, 1},
        {3, 1, 2},
        {3, 2, 1}
    };

    printPermutations(a);
}

vector<vector<int>> genPerms(vector<int>& s, queue<int>& q) {
    vector<vector<int>> ret;
    if (q.empty()) {
        ret.push_back(s);
        return ret;
    }

    for (int i = 0; i < q.size(); i++) {
        s.push_back(q.front()); q.pop();
        auto morePerms = genPerms(s, q);
        ret.insert(ret.end(), morePerms.begin(), morePerms.end());
        q.push(s.back()); s.pop_back();
    }

    return ret;
}

vector<vector<int>> uniqueGenPerms(vector<int>& s, queue<int>& q) {
    vector<vector<int>> ret;
    if (q.empty()) {
        ret.push_back(s);
        return ret;
    }

    set<int> usedElts;
    printVector(s);
    for (int i = 0; i < q.size(); i++) {
        int originalElt = q.front();
        bool used = usedElts.count(q.front());

        s.push_back(q.front()); q.pop();
        vector<vector<int>> morePerms;
        if (!used) {
            // cout << "inserting " << originalElt << " at level " << s.size() << endl;
            morePerms = uniqueGenPerms(s, q);
            usedElts.insert(originalElt);
        } else {
            // cout << originalElt << " used at level " << s.size() << ", continuing" << endl;
        }

        ret.insert(ret.end(), morePerms.begin(), morePerms.end());
        q.push(s.back()); s.pop_back();
    }

    return ret;
}

void testGenPerms1() {
    queue<int> q({1,2,3});
    vector<int> s;
    auto perms = genPerms(s, q);

    printPermutations(perms);
}

void testGenPerms2() {
    queue<int> q({1, 1, 2});
    vector<int> s;
    auto perms = genPerms(s, q);

    printPermutations(perms);
}

void testUniqueGenPerms() {
    queue<int> q({1, 1, 2});
    vector<int> s;

    queue<int> q2(q);
    vector<int> s2(s);

    auto originalPerms = genPerms(s2, q2);
    printPermutations(originalPerms);

    auto perms = uniqueGenPerms(s, q);
    printPermutations(perms);
}

int main() {
    // testPrint();
    // testGenPerms2();
    testUniqueGenPerms();
}