
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;

    fd = open("/dev/mymod", O_RDONLY);

    if (fd < 0)
        return 1;

    close(fd);

    return 0;
}
