#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(void)
{
  int sock0;
  struct sockaddr_in addr;
  struct sockaddr_in client;
  int len;
  int sock;

  sock0 = socket(AF_INET, SOCK_STREAM, 0);
  addr.sin_family = AF_INET;
  addr.sin_port = htons(12345);
  addr.sin_addr.s_addr = INADDR_ANY;
  bind(sock0, (struct sockaddr*)&addr, sizeof(addr));

  listen(sock0, 5);
  len = sizeof(client);
  sock = accept(sock0, (struct sockaddr*)&client, &len);
  write(sock, "HELLO", 5);
  close(sock);
  close(sock0);
  return 0;

//  printf("hogehoge");
//  int port = 1234;
//  struct sockaddr_in my_addr;
//  memset((char*)&my_addr, 0, sizeof(my_addr));
//  my_addr.sin_family = AF_INET;
//  my_addr.sin_port = htons(port);
//  my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
//
//  int sock = socket(PF_INET, SOCK_STREAM);
//
//  bind(sock, (struct sockaddr *)&my_addr);
//  listen(sock);
//  while(1) {
//    int new_sock = accept(sock, &addr);
//
//    char buf[100];
//    size_t size = read(new_sock, buf, 100);
//
//    if (size == 0) {
//      close(new_sock);
//    } else{
//      write(new_sock, buf, size);
//    }
//  }
// 
//  return 0;
}
