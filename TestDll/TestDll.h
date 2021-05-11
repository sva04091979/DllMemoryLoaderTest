#pragma once

#define DllTestApi __declspec(dllexport)

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	DllTestApi void Test();

#ifdef __cplusplus
}
#endif // __cplusplus
