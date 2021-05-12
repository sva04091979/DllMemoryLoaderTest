#include <iostream>
//#include "TestDll.h"
#include "MemoryModule.h"

#pragma comment(lib,"MemoryModule.lib")

using namespace std;

struct DllPtr {
	LPVOID ptr;
	DWORD size;
};

DllPtr GetDll() {
	DllPtr ret = { nullptr,0 };
	auto hndl = GetModuleHandle(NULL);
	if (hndl != NULL) {
		auto res = FindResource(hndl, L"TestDll", RT_RCDATA);
		if (res != NULL) {
			auto resHndl = LoadResource(hndl, res);
			if (resHndl != NULL) {
				ret.size = SizeofResource(hndl, res);
				ret.ptr = LockResource(resHndl);
			}
		}
	}
	return ret;
}

int main()
{
	DllPtr ptr = GetDll();
	if (!ptr.ptr) return 1;
	auto dllHndl = MemoryLoadLibrary(ptr.ptr, ptr.size);
	if (dllHndl != NULL) {
		auto Test = MemoryGetProcAddress(dllHndl, "Test");
		if (Test != NULL)
			Test();
		else cout << "Get adress error" << endl;
	}
	else cout << "Load Error" << endl;
	MemoryFreeLibrary(dllHndl);
	getchar();
	return 0;
}
