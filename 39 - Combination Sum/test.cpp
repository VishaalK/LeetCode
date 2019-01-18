#include <vector>
#include <iostream>
using namespace std;

int main() {
    vector<int> a = {5};
    auto& b = a;
    b.push_back(5);

    for (auto elt : a) {
        cout << elt << " ";
    }
    cout << endl;

    return 0;
}