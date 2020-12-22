#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define LENGTH  100
#define TEST "LINUX,GDB"
int main(int argc, char *argv[])
{
    int fd,len;
    char str[LENGTH];

    fd = open("/dev/globalmem", O_RDWR);
    if (fd) {
        write(fd, TEST, strlen(TEST));
        close(fd);
    }

    fd = open("/dev/globalmem", O_RDWR);
    len = read(fd, str, LENGTH);
    str[len] = '\0';
    printf("str:%s\n", str);
    close(fd);

    return 0;
}
