#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#define WRITE_DEVICE_FILENAME  "/dev/minor_led"  //major:230, minor:0
#define READ_DEVICE_FILENAME   "/dev/minor_key"   //major:230, minor:1
#define DEVICE_FILENAME   "/dev/minor"   //major:230, minor:2
int main()
{
    int read_dev;
    int write_dev;
    int dev;
    
    char buff[128];
    int loop;

    read_dev  = open( READ_DEVICE_FILENAME,  O_RDWR|O_NDELAY );
    if( read_dev < 0 ) 
    {  
		perror("open()");
        printf( READ_DEVICE_FILENAME " open error\n" );
        exit(1);
    }
    
    write_dev = open( WRITE_DEVICE_FILENAME, O_RDWR|O_NDELAY );
    if( write_dev < 0 ) 
    {  
		perror("open()");
        printf( WRITE_DEVICE_FILENAME " open error\n" );
        close( read_dev );
        exit(1);
    }

    dev = open( DEVICE_FILENAME, O_RDWR|O_NDELAY );
    if( dev < 0 ) 
    {  
		perror("open()");
        printf( DEVICE_FILENAME " open error\n" );
        close( dev );
        exit(1);
    }

    printf( "wait... input\n" );
    while(1)
    {
        if( read(read_dev,buff,1 ) == 1  && buff[0] != 0)
        {
            printf( "read data [%02X]\n", buff[0] & 0xFF );
//            if( !(buff[0] & 0x10) ) break;
            if( buff[0] & 0x80) break;
        }
    } 
    printf( "input ok...\n");
    
    printf( "led flashing...\n");
    for( loop=0; loop<5; loop++ )
    {
        buff[0] = 0xFF; 
        write(write_dev,buff,1 );
        sleep(1);
        buff[0] = 0x00; 
        write(write_dev,buff,1 );
        sleep(1);
    }

    printf( "input ok...\n");
    while(1)
    {
        if( read(dev,buff,1 ) == 1  && buff[0] != 0)
        {
            printf( "read data [%04X]\n", buff[0] & 0xFF );
            write(dev,buff,1 );
            if( buff[0] & 0x80) break;
        }
    }

    close(dev);
    close(read_dev);
    close(write_dev);

    return 0;
}

