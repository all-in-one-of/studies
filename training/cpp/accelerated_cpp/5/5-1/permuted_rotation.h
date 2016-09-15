#ifndef __Permuted_Rotations__
#define __Permuted_Rotations__

#include <vector>
#include <string>

struct permuted_rotation {
    std::vector<std::string> rotated;
    double f_index;
};

std::vector<permuted_rotation> rotations(const std::string& s);
void rotate(const std::string& s);

#endif