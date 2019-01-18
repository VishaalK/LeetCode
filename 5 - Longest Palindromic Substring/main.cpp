#include <algorithm>
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

class Solution {
public:
//     string longestPalindrome(string s) {
//         auto size = s.size();
        
//         vector<vector<bool>> mem(size);
        
//         for (int i = 0; i < size; i++) {
//             mem[i].resize(size);
//             for (int j = 0; j < size; j++) {
//                 mem[i][j] = false;
//             }
//         }
        
//         string longest = "";
//         for (int i = 0; i < size; i++) {
//             mem[i][i] = true;
//             longest = s.substr(i, 1); 
//         }
        
//         for (int i = 0; i < size - 1; i++) {
//             mem[i][i+1] = s[i] == s[i+1];
//             if (mem[i][i+1]) {
//                 longest = s.substr(i, 2);
//             }
//         }
        
//         for (int i = 2; i < size; i++) {
//             for (int j = 0; (j + i) < size; j++) {
//                 mem[j][j+i] = mem[j+1][j+i-1] && mem[j][j+i];
//                 if (mem[j][j+i] && i > longest.size()) {
//                     longest = substr(j, i);
//                 }
//             }
//         }
        
//         return longest;
//     }
    
    string longestPalindrome(string s) {
        int size = s.size();
        cout << "s: " << s << endl;
        string longest = "";
        
        // expand around each center
        for (int i = 0; i < size; i++) {
            auto center = s[i];
            int left = i;
            int right = i;
            int leftTwo = i;
            int rightTwo = i+1;

            int length = 0;

            while (left >= 0 && right <= size - 1) {
                if (s[left] == s[right]) {
                    length += (left == right) ? 1 :2;

                    if (length > longest.size()) {
                        longest = s.substr(left, length);
                    }

                    left--;
                    right++;
                } else {
                    break;
                }
            }

            length = 0;

            while (leftTwo >= 0 && rightTwo <= size - 1) {
                if (s[leftTwo] == s[rightTwo]) {
                    length += 2;

                    if (length > longest.size()) {
                        longest = s.substr(leftTwo, length);
                    }

                    leftTwo--;
                    rightTwo++;
                } else {
                    break;
                }
            }
        }
        
        return longest;
    }
};

string stringToString(string input) {
    assert(input.length() >= 2);
    string result;
    for (int i = 1; i < input.length() -1; i++) {
        char currentChar = input[i];
        if (input[i] == '\\') {
            char nextChar = input[i+1];
            switch (nextChar) {
                case '\"': result.push_back('\"'); break;
                case '/' : result.push_back('/'); break;
                case '\\': result.push_back('\\'); break;
                case 'b' : result.push_back('\b'); break;
                case 'f' : result.push_back('\f'); break;
                case 'r' : result.push_back('\r'); break;
                case 'n' : result.push_back('\n'); break;
                case 't' : result.push_back('\t'); break;
                default: break;
            }
            i++;
        } else {
          result.push_back(currentChar);
        }
    }
    return result;
}

int main() {
    string line;
    // while (getline(cin, line)) {
    //     string s = stringToString(line);
        
    //     string ret = Solution().longestPalindrome(s);

    //     string out = (ret);
    //     cout << out << endl;
    // }

    string ret = Solution().longestPalindrome("bb");

    string out = (ret);
    cout << out << endl;
    return 0;
}