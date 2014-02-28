#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char **argv)
{
  struct hostent *host;
  struct sockaddr_in server;
  int sock;
  char buf[32];
  int n;

  if (argc != 2) {
    fprintf(stderr, "USAGE: ./client <host>");
    exit(1);
  }

  if ((host = gethostbyname(argv[1])) == NULL) {
    fprintf(stderr, "(mini) nslookup failed on '%s'\n", argv[1]);
    exit(1);
  }

  sock = socket(AF_INET, SOCK_STREAM, 0);

  server.sin_family = AF_INET;
  server.sin_port = htons(12345);
  server.sin_addr.s_addr = *((unsigned long*) host->h_addr_list[0]);
  printf("connecting %s (%s)...\n", argv[1], inet_ntoa(server.sin_addr));
//  server.sin_addr.s_addr = inet_addr("127.0.0.1");

  connect(sock, (struct sockaddr*)&server, sizeof(server));

  memset(buf, 0, sizeof(buf));
  n = read(sock, buf, sizeof(buf));

  printf("%d, %s\n", n, buf);
  close(sock);

  return 0;
}
