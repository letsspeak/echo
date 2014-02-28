#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
  char *deststr;
  struct sockaddr_in server;
  int sock;
  char buf[32];
  int n;

  if (argc != 2) {
    fprintf(stderr, "USAGE: %s <host>\n", argv[0]);
    exit(1);
  }

  deststr = argv[1];
  sock = socket(AF_INET, SOCK_STREAM, 0);

  server.sin_family = AF_INET;
  server.sin_port = htons(12345);
  server.sin_addr.s_addr = inet_addr(deststr);
  if (server.sin_addr.s_addr == 0xffffffff) {
    struct hostent *host;
    host = gethostbyname(deststr);
    if (host == NULL) {
      fprintf(stderr, "hsot is NULL");
      exit(1);
    }
    server.sin_addr.s_addr = *(unsigned int *)host->h_addr_list[0];
  }

  printf("connecting %s (%s)...\n", deststr, inet_ntoa(server.sin_addr));
//  server.sin_addr.s_addr = inet_addr("127.0.0.1");

  connect(sock, (struct sockaddr*)&server, sizeof(server));

  memset(buf, 0, sizeof(buf));
  n = read(sock, buf, sizeof(buf));

  printf("%d, %s\n", n, buf);
  close(sock);

  return 0;
}
