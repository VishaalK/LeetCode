#include <vector>
#include <iostream>
#include <map>
using namespace std;

class ZigzagIterator {
    int numElts;
    int eltsRead;
    int curVector;
    map<int, int> curVectorToIdx;
    vector<vector<int>> vectors;
    
public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        eltsRead = 0;
        curVector = 0;
        numElts = v1.size() + v2.size();
        vectors = vector<vector<int>>{v1, v2};
    }

    int next() {
        auto& idx = curVectorToIdx[curVector];
        // cout << "before: curVector: " << curVector << endl;

        auto ret = vectors.at(curVector).at(idx);
        // cout << "idx: " << idx << ", ret: " << ret << endl;
        // cout << "curVector: " << curVector << endl;
        idx++;
        eltsRead++;

        do {
            curVector = (curVector + 1) % vectors.size();
            // cout << "curVector: " << curVector << endl;
        } while (curVectorToIdx[curVector] >= vectors[curVector].size() && eltsRead != numElts);
        
        
        return ret;
    }

    bool hasNext() {
        return eltsRead < numElts;
    }
};


/**
 * Your ZigzagIterator object will be instantiated and called as such:
 * ZigzagIterator i(v1, v2);
 * while (i.hasNext()) cout << i.next();
 */

void test1() {
    vector<int> v1{1,2};
    vector<int> v2{3,4,5,6};

    vector<int> output{1,3,2,4,5,6};

    ZigzagIterator i(v1, v2);
    while (i.hasNext()) 
        cout << i.next();
}


int main() {
    test1();
}