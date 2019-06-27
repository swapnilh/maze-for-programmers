#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>

enum class Direction {
	North,
	East,
	West,
	South
};

#ifdef DEBUG
#define NOTE(...) {fprintf(stderr, __VA_ARGS__);}
#define LOG(M, ...) fprintf(stderr, "%s (%s:%d) " M "\n", __func__, __FILE__, __LINE__, __VA_ARGS__);
#else
#define NOTE(M, ...) do {} while(0)
#define LOG(M, ...) do {} while(0)
#endif

#endif // UTIL_HPP
