#include <stdio.h>
#include <unistd.h>
#include <asm-generic/unistd.h>

#pragma GCC diagnostic ignored "-Wunused-result"

int main()
{
                long val;
                long key_old = 0;
				long key = 0;
				int ret;

                printf("input value = ");
                scanf("%ld", &val);
                
				ret = syscall(__NR_mysyscall, val);
                if(ret < 0)
                {
					perror("syscall");
					return 1;
                }

                do
                {
					// usleep(100000); // 디바운싱 + CPU 절약
					key = syscall(__NR_mysyscall, val);
				
                    if(key != key_old)
					{
						if(key)
						{
							val = key;
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
							syscall(__NR_mysyscall, val);
						}
                        key_old = key;
					}
                } while (1);

                // printf("mysyscall return value = %ld\n", val);
                return 0;
}
