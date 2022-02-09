#ifndef DEBUG_HPP
#define DEBUG_HPP

/************************/
#define print(var)                     \
    do                                 \
    {                                  \
        std::cout << #var << " : ";    \
        std::cout << var << std::endl; \
    } while (0)

// 行数と関数名出力
#define debug(var)                                      \
    do                                                  \
    {                                                   \
        std::cerr << "-----------------"                \
                  << "\n"                               \
                  << "[" << #var << "] "                \
                  << "\n"                               \
                  << "func: " << __func__ << "\n"       \
                  << "line: " << __LINE__ << std::endl; \
    } while (0)

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
/**********************/

#endif
