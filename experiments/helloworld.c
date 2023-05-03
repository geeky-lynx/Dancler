#include <stdio.h>
#include <stdlib.h>
// #include <windows.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
    printf("Hello, World\n");
    // Sleep(3000);
    sleep(3);
    system("color 3");
    printf("Bye, World\n");
    return 0;
}