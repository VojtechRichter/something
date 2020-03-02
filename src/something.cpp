#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <SDL.h>
#include <SDL_ttf.h>

#include <png.h>

template <typename T>
T min(T a, T b)
{
    return a < b ? a : b;
}

template <typename T>
T abs(T x)
{
    return x < 0 ? -x : x;
}

// READ THIS FIRST ---> https://en.wikipedia.org/wiki/Single_Compilation_Unit
#include "something_error.cpp"
#include "something_vec.cpp"
#include "something_string.cpp"
#include "something_sprite.cpp"
#include "something_level.cpp"
#include "something_projectile.cpp"
#include "something_entity.cpp"
#include "something_main.cpp"