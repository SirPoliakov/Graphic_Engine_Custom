#pragma once
#include <intrin.h>

//#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) glClearError();\
                  x;\
                  glLogCall(#x, __FILE__, __LINE__);

void glClearError();
bool glLogCall(const char* function, const char* file, int line);