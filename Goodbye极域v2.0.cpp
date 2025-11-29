#include <iostream>
#include <windows.h>
using namespace std;
int main(){
    POINT mouse;
    while (1) {
        if (GetCursorPos(&mouse)){
            if (mouse.x == 1919 && mouse.y == 0 && GetAsyncKeyState(VK_RBUTTON)){
                system("taskkill /f /im studentmain.exe");
                MessageBox(NULL, (LPCSTR)"taskkilled:StudentMain.exe!", (LPCSTR)"info", MB_OK);
            }
        }
        Sleep(100);
    }
}
