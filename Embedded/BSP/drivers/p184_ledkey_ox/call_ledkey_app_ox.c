#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define DEVICE_FILENAME  "/dev/ledkey"

int main(int argc, char * argv[])
{
    int dev;
    char buff;
    int ret;
	char key_old = 0;
	char key = 0;

	if(argc != 2)
	{
		printf("USAGE : %s ledval[0x00~0xff]\n",argv[0]);
		return 1;
	}
	key = strtoul(argv[1],NULL,16);

    if(access(DEVICE_FILENAME,F_OK) != 0)   //파일 없을시
    {
        int ret = mknod(DEVICE_FILENAME, S_IRWXU | S_IRWXG | S_IFCHR, (230 << 8) | 0);
        if(ret < 0)
            perror("mknod()");
    }

    dev = open( DEVICE_FILENAME, O_RDWR|O_NDELAY);
    if( dev < 0 )
    {
		perror("open");
		return 2;
	}
//	while(1);
	ret = read(dev,&buff, sizeof(buff));              
	if(ret < 0)
	{
		perror("read()");
		return 3;
	}
	printf( "ret = %08X, key = %#04x\n",ret, buff );

	ret = write(dev,&key,sizeof(key));
	printf( "ret = %08X\n", ret );

	do
	{
		// usleep(100000); // 디바운싱 + CPU 절약
		read(dev,&key, sizeof(key)); 

		if(key != key_old)
		{
			if(key)
			{
				write(dev,&key,sizeof(key));
				printf("0:1:2:3:4:5:6:7\n");
				for(int i=0;i<8;i++)
				{
					if(key & (0x01 << i))
					{
						printf("O");
					}
					else
						printf("X");
					if(i != 7 )
						printf(":");
					else
						printf("\n");
				}
				printf("\n");

				if(key == 0x80)
				{
					break;
				}
			}
			key_old = key;
		}
	} while (1);

	ret = close(dev);
    return 0;
}

