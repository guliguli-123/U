#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int main() {
    ofstream file("file.txt");
    system("cls");
    system("color a");
    for (int i = 0; i < 10000000; i++) {
        file << "ABCDEFGHIJKLMNOPQRSTUVWXYZ" << endl;
        cout << i << endl;
    }
    return 0;
}