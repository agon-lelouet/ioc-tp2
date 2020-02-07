#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fctnl.h>
#include <unistd.h>

int main(int argc, char** argv) {
    int delta = 1;
    char bufoff[1] = "0";
    char bufon[1] = "1";
    if (argc > 1) {
        delta = atoi(argv[1]);
    }

    int devicefd = open("/dev/ledbpAL", O_RDWR);
    while(true) {
        write(devicefd, bufoff, 1);
        sleep(delta);
        write(devicefd, bufN, 1);
    }
}