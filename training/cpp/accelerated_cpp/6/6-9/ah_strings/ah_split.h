#ifndef __AH_SPLIT_H__
#define __AH_SPLIT_H__

#include <string>
#include <vector>

namespace ah {
    bool space(char c);
    bool not_space(char c);
    std::vector<std::string> split(const std::string& s) ;
}

#endif