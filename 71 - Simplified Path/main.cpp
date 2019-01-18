#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

vector<string> tokenize(const string& s) {
    istringstream token(s);
        
    vector<string> ret;
    string currentToken;
    while (std::getline(token, currentToken, '/')) {
        ret.push_back(currentToken);
    }

    return ret;
}

string implode(const vector<string>& tokens, char delim) {
    string ret;
    for (int i = 0; i < tokens.size(); i++) {
        ret += tokens[i];

        if (i != tokens.size() - 1) {
            ret += delim;
        }
    }
    return ret;
}

vector<string> process(const vector<string>& tokens) {
    vector<string> ret;
    bool onDirectory = false;
    for (auto token: tokens) {
        if (token.empty() || token == ".") {
            continue;
        }

        if (token == "..") {
            if (ret.size() != 0) {
                ret.pop_back();
            } else {
                onDirectory = false;
            }
        } else {
            onDirectory = true;
            ret.push_back(token);
        }
    }
    return ret;
}

class Solution {
public:
    string simplifyPath(string path) {
        vector<string> tokens = tokenize(path);

        auto ret = process(tokens);

        auto constructed = '/' + implode(ret, '/');
        return constructed;
    }
};

void testTokenize() {
    vector<string> ret = tokenize("/a//b////c/d//././/..");

    cout << "(";
    for (auto r : ret) {
        cout << r << ",";
    }
    cout << ")" << endl;
}

void testImplode() {
    vector<string> tokens = {"a", "b", "c"};
    auto ret = implode(tokens, '/');

    cout << "implode: " << ret << endl;
}

void testSimplify() {
    auto path = Solution().simplifyPath("/a//b////c/d//././/..");
    cout << path << endl;
}

void testAll() {
    string path1 = "/home/"; // , => "/home"
    string path2 = "/a/./b/../../c/"; // , => "/c"
    string path3 = "/a/../../b/../c//.//"; //, => "/c"
    string path4 = "/a//b////c/d//././/.."; // => "/a/b/c"

    string path = Solution().simplifyPath(path1);
    cout << path << endl;

    path = Solution().simplifyPath(path2);
    cout << path << endl;

    path = Solution().simplifyPath(path3);
    cout << path << endl;

    path = Solution().simplifyPath(path4);
    cout << path << endl;
}

void test3() {
    string path3 = "/a/../../b/../c//.//"; //, => "/c"

    auto ret = tokenize(path3);
    for (auto r : ret) {
        cout << r << ","; 
    }
    cout << endl;

    cout << "processed: ";
    auto processed = process(ret);
    for (auto p : processed) {
        cout << p << ","; 
    }
    cout << endl;


    auto path = Solution().simplifyPath(path3);
    cout << path << endl;
}

void testDoublePopback() {

}

int main() {
    // testTokenize();
    // testImplode();
    // testSimplify();
    testAll();
    // test3();
}