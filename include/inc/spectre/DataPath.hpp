#ifndef DATAPATH_HPP_INCLUDED
#define DATAPATH_HPP_INCLUDED

#include <vector>
#include <ostream>
#include <string>

/// Path to a Data/Element inside a container
using DataPath = std::vector<std::string>;


namespace std {
    std::ostream &operator<< (std::ostream &os, const DataPath &path);
}


#endif // DATAPATH_HPP_INCLUDED
