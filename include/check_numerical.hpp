#ifndef EU4RVF_CHKNUMERICAL_HPP
#define EU4RVF_CHKNUMERICAL_HPP

#include <string>

inline bool is_numerical(const std::string &str){
	return str.find_first_not_of("0123456789") == std::string::npos;
}

#endif