#include <string>
#include <vector>
#include <iostream>
#include <sstream>

namespace StringUtils {
    template<typename T>
    std::string join(const std::vector<T>& v, std::string delim)  {
        std::ostringstream ret;
        for (int i = 0; i < v.size(); i++) {
            ret << v[i] << (i != v.size() - 1 ? delim : "");
        }
        return ret.str();
    }
}
