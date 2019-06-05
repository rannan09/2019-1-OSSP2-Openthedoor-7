#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
//#include <signal.h>
#include <termios.h>
#include <string.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>

//#include <pthread.h>
//#include <semaphore.h>

int user_idx;

int first(char * myId, char * myPwd);
int previousScore();

int main(int argc, char **argv){
    
    char myId[100];
    char myPwd[100];
    int user_idx = -1;
    user_idx = first(myId, myPwd);
    printf("\tlogin complete\n");
    
    //system("clear");
    int score = previousScore();
    printf("\tprevious Score : ", score);
    // 시작하시겠습니까? 같은거
    // ------------------
    //      게임 코드
    // ------------------
    // 점수 vs 디비의 점수 -> 큰 거 출력 & 저장
    
}


int first(char * myId, char * myPwd){
    int sock, sign;
    char buff[1000];
    struct sockaddr_in serv_addr;
    sock = socket(PF_INET, SOCK_STREAM, 0); //0 = IPPROTO_TCP
    
    memset(buff, 0x00, sizeof(buff));
    memset(myId, 0x00, sizeof(myId));
    memset(myPwd, 0x00, sizeof(myPwd));
    memset(&serv_addr, 0, sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("13.124.167.29");
    //serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(3090);
    
    
    system("clear");
    printf("\n\n\t -------LOGIN--------\n\n");
    printf("\tID : ");
    scanf("%s", myId);
    
    printf("\tPW : ");
    scanf("%s", myPwd);
    printf("\n\n");
    
    while (1) {
        printf("\t[1]signup [2]signin : ");
        scanf("%d", &sign);
        
        if (sign == 1) {
            //for signup
            // serv_addr.sin_addr.s_addr = inet_addr("13.209.29.192");
            
            if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
                printf("connect error/n");
            }
            
            sprintf(buff, "%c|%s|%s", '1', myId, myPwd);
            //printf("before send %s/n",buff);
            write(sock, buff, sizeof(buff)); // send socket to server
            //printf("after send %s\n",buff);
            memset(buff, 0x00, sizeof(buff)); // empty buffer
            read(sock, buff, sizeof(buff)); // read socket from server
            printf("\tuser_idx : ");
            printf("%s\n", buff);
            if (buff != NULL) {
                printf("\t success !");
            }
            break;
            
        }
        else if (sign == 2) {
            //for login
            if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
                printf("connect error");
            
            sprintf(buff, "%c|%s|%s", '2', myId, myPwd);
            // printf("before send %s\n",buff);
            write(sock, buff, sizeof(buff)); // send socket to server
            //printf("after send %s\n",buff);
            memset(buff, 0x00, sizeof(buff)); // empty buffer
            read(sock, buff, sizeof(buff)); // read socket from server
            //printf("after read %s\n",buff);
            printf("\tuser_idx : ");
            printf("%s\n", buff);
            
            if (buff != NULL) {
                printf("\t success ! \n");
            }
            break;
            
        }
        else {
            printf("It is wrong");
        }
    }
    close(sock);
    user_idx = (atoi)(buff);
    return user_idx;
}


int previousScore() {
	int sock, previous_score;
	char buff[1000];
	struct sockaddr_in serv_addr;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(buff, 0x00, sizeof(buff));

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("13.124.167.29");
	serv_addr.sin_port = htons(3090);

	if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
		printf("connect error");
	}
	//socre get
	sprintf(buff, "%c|%d", '5', user_idx);
	write(sock, buff, sizeof(buff));
	//printf("%s\n", buff);
	memset(buff, 0x00, sizeof(buff));
	read(sock, buff, sizeof(buff));
	//printf("%s\n", buff);
	//printf("current score : ");
	previous_score = (atoi)(buff);
	close(sock);
	return previous_score;
}
