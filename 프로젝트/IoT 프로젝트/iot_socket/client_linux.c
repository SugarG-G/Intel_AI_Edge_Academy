/* 서울기술 교육센터 IoT */
/* author : CHI */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>

#define BUF_SIZE 100
#define NAME_SIZE 20
#define ARR_CNT 5

void * send_msg(void * arg);
void * recv_msg(void * arg);
void error_handling(char * msg);

char name[NAME_SIZE]="[Default]";
char msg[BUF_SIZE];
char nodded_count[4] = {0,};

int flag = 1;
int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	pthread_t snd_thread, rcv_thread;
	void * thread_return;
	
	if(argc != 4) {
		printf("Usage : %s <IP> <port> <name>\n",argv[0]);
		exit(1);
	}

	sprintf(name, "%s",argv[3]);

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
		error_handling("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
		error_handling("connect() error");

	sprintf(msg,"[%s:PASSWD]",name);
	write(sock, msg, strlen(msg));
	pthread_create(&rcv_thread, NULL, recv_msg, (void *)&sock);
	pthread_create(&snd_thread, NULL, send_msg, (void *)&sock);

	pthread_join(snd_thread, &thread_return);
	//	pthread_join(rcv_thread, &thread_return);

	close(sock);
	return 0;
}

void * send_msg(void * arg)
{
	int *sock = (int *)arg;
	int str_len;
	int ret;
	struct timeval tv;
	char name_msg[NAME_SIZE + BUF_SIZE+2];
    char db_msg[NAME_SIZE + BUF_SIZE+2];
	fputs("Input a message! [ID]msg (Default ID:ALLMSG)\n",stdout);
    time_t past_time;
    time(&past_time);
	while(1) {
		memset(msg,0,sizeof(msg));
        time_t current_time;
        time(&current_time);
        if(abs(current_time - past_time) >= 5)
        {
            past_time = current_time;
            name_msg[0] = '\0';
            db_msg[0] = '\0';
            sprintf(db_msg, "[CHI_SQL]GETDB@status\n");
            //fgets(msg, BUF_SIZE, stdin);
            // if(!strncmp(msg,"quit\n",5)) {
            //     *sock = -1;
            //     return NULL;
            // }
            // else if(msg[0] != '[')
            // {
            //     strcat(db_msg,"[ALLMSG]");
            //     strcat(db_msg,msg);
            // }
            // else
            //     strcpy(db_msg,msg);
            if(write(*sock, db_msg, strlen(db_msg))<=0)
            {
                *sock = -1;
                return NULL;
            }
            if(*sock == -1) 
            {
                return NULL;
            }
            
        }
        if(strcmp(nodded_count, "ON\n") == 0 && flag == 1)
        {
            flag = 2;
            sprintf(name_msg, "[CHI_STM2]DETECT@%s", nodded_count);
            if(write(*sock, name_msg, strlen(name_msg)) <= 0)
            {
                *sock = -1;
                return NULL;
            }
        } else if(strcmp(nodded_count, "OFF\n") == 0 && flag == 2){
            flag = 1;
            sprintf(name_msg, "[CHI_STM2]DETECT@%s", nodded_count);
            if(write(*sock, name_msg, strlen(name_msg)) <= 0)
            {
                *sock = -1;
                return NULL;
            }
        }
	}
}

void * recv_msg(void * arg)
{
	int * sock = (int *)arg;	
	int i;
	char *pToken;
	char *pArray[ARR_CNT]={0};

	char name_msg[NAME_SIZE + BUF_SIZE +1];
	int str_len;
	while(1) {
		memset(name_msg,0x0,sizeof(name_msg));
		str_len = read(*sock, name_msg, NAME_SIZE + BUF_SIZE );
		if(str_len <= 0) 
		{
			*sock = -1;
			return NULL;
		}
		name_msg[str_len] = 0;
		fputs(name_msg, stdout);
        
        pToken = strtok(name_msg,"[:]@ ");
        i = 0;
        while(pToken != NULL)
        {
            pArray[i] =  pToken;
            if(i++ >= ARR_CNT)
            break;
            pToken = strtok(NULL,"[:]@ ");
        }
        if(strcmp(pArray[1], "New") == 0)
        {
            continue;
        }
        printf("test : %s", pArray[3]);
        strcpy(nodded_count, pArray[3]);
        printf("cnt :%s\n", nodded_count);
	}
}

void error_handling(char * msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}
