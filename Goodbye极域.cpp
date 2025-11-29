#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
	system("chcp 65001 > nul");
    system("taskkill /f /im studentmain.exe");
    cout << "极域似了" << endl;
    return 0;
}
