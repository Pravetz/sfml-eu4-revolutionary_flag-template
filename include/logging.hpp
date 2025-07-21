#ifndef EU4RVF_LOGGING_MACROS_HPP
#define EU4RVF_LOGGING_MACROS_HPP

#define INJECT_FLINECOL(file, line, col) (file + ":" + std::to_string(line) + ":" + std::to_string(col) + ": ")
#define LOGINFO(...) std::cerr<<"[i] "<<__VA_ARGS__<<std::endl
#define LOGERROR(...) std::cerr<<"[!] "<<__VA_ARGS__<<std::endl
#define LOGSUCCESS(...) std::cout<<"[^] "<<__VA_ARGS__<<std::endl

#endif