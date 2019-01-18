#include "string_utilities.h"
#include <vector>
#include <cassert>
using namespace std;

void test_join() {
    vector<int> v{1,2,3};
    assert(StringUtils::join(v, string(",")) == "1,2,3");
}

int main() {
    test_join();
}