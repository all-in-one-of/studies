#ifndef __AH_INPUT_H__
#define __AH_INPUT_H__

#include <string>
#include <vector>

namespace ah {
    void get_input(int argc, char *argv[], std::string&);
    void get_input(int argc, char *argv[], std::vector<std::string>&);
}

#endif