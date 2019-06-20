/*
	client 접속 정보를 담기위해서 client_info 구조체 생성
		Client 5개가 접속 될 때까지 대기 및 각 클라이언트간 메시지 전송
			접속이 완료되면 client_info를 각 클라이언트로 모두 전송 받음
				전송 받은 client 정보를 출력
				*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAXLINE 1024 //buf 크기
#define LISTENQ 100 //Listen Q 설정
#define TOTALCL 5 //클라이언 동시 접속 수

//client 정보를 저장하기 위한 구조체 (접속 IP, port)
struct client_info {
		char clientAddr[32];
			int clientPort;
};

int main(int argc, char *argv[]) {
		struct sockaddr_in servaddr, cliaddr;
			struct client_info cliinfo[TOTALCL];
				int listen_sock, accp_sock[TOTALCL];
					int addrlen = sizeof(servaddr);
						int nbyte; //전송 받은 메시지 byte 저장
							char buf[MAXLINE];
								int conNum = 0;

									if(argc != 2) {
												printf("Use %s PortNumber\n", argv[0]);
														exit(0);
															}
										
										if((listen_sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
													perror("socket Fail");
															exit(0);
																}

											memset(&servaddr, 0, sizeof(servaddr)); //0으로 초기화
												servaddr.sin_family = AF_INET;
													servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
														servaddr.sin_port = htons(atoi(argv[1]));

															//bind 호출
															if(bind(listen_sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
																		perror("bind Fail");
																				exit(0);
																					}
																
																//소켓을 수동 대기모드로 세팅
																listen(listen_sock, LISTENQ);

																	//interative 에코 서비스 수행
																	while(conNum < 5) {
																				puts("서버가 연결 요청을 대기");		

																						accp_sock[conNum] = accept(listen_sock, (struct sockaddr *)&cliaddr, &addrlen);
																								if(accp_sock[conNum] < 0) {
																												perror("accept fail");
																															exit(0);
																																	}
																										
																										strcpy(cliinfo[conNum].clientAddr, inet_ntoa(cliaddr.sin_addr));
																												cliinfo[conNum].clientPort = ntohs(cliaddr.sin_port);
																														printf("Client 연결 됨 IP %s, Port %d\n", cliinfo[conNum].clientAddr, cliinfo[conNum].clientPort);

																																//접속 성공 메시지
																																if((nbyte = read(accp_sock[conNum], buf, MAXLINE)) < 0) {
																																				perror("read fail");
																																							exit(0);
																																									}
																																		buf[nbyte] = 0;
																																				if(!strncmp(buf, "Connect Success", 15)) {
																																								printf("client message : %s\n", buf);
																																										}

																																						conNum++; //접속자 수 증가
																																							}

																		puts("모든 클라이언트에 접속 정보 전송");
																			conNum = 0;
																				while(1) {
																							buf[0] = '\0';
																									send(accp_sock[conNum], &cliinfo, sizeof(struct client_info) * 5, 0);
																											
																											if((nbyte = read(accp_sock[conNum], buf, MAXLINE)) < 0) {
																															perror("set read fail");
																																		exit(0);
																																				}
																													buf[nbyte] = 0;
																															printf("%s\n", buf);
																																	if(!strncmp(buf, "GetOK", 5)) {
																																					conNum++;
																																								if(conNum == 5)
																																													break;
																																										}
																																		}

																					close(listen_sock);
																						
																						return 0;
}
