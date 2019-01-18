#include <iostream>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
using namespace std;


class Solution {
public:
    unordered_map<string, string> shortToLong;

    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        string key = generateRandomString();
        string shortUrl = "http://tinyurl.com/" + key;
        
        shortToLong[shortUrl] = longUrl;
        return shortUrl;
    }

    // a random alphanumeric char
    char generateRandomChar() {
        string alphaNumeric = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
        return alphaNumeric[rand() % alphaNumeric.size()];
    }
    
    string generateRandomString() {
        string s;
        for (int i = 0; i < 7; i++) {
            s += generateRandomChar();
        }
        return s;
    }
    
    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        return shortToLong[shortUrl];
    }
};

int main() {
    Solution solution;

    string a = solution.encode("https://leetcode.com/problems/design-tinyurl");
    cout << a << " " << solution.decode(a) << endl;
}