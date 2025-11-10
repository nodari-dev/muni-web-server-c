#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
  char buffer[BUFFER_SIZE];
  char resp[] = "HTTP/1.0 200 OK\r\n"
                "Server: webserver-c\r\n"
                "Content-type: text/html\r\n\r\n"
                "<html>hello, world</html>\r\n";

  // 1. Create a socket (socket file descriptor)
  // SOCK_STREAM = TCP
  // TODO: man socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    perror("webserver (socket)");
    return 1;
  }
  printf("socket created successfully\n");

  // 2.1. create the address to bind the socket to
  struct sockaddr_in host_addr;
  int host_addrlen = sizeof(host_addr);

  host_addr.sin_family = AF_INET;
  host_addr.sin_port = htons(PORT);

  // NOTE: INADDR_ANY -> any address -> 0.0.0.0
  host_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  // 2.2 bind a socket to an address
  if (bind(sockfd, (struct sockaddr *)&host_addr, host_addrlen) != 0) {
    perror("webserver (bind)");
    return 1;
  }
  printf("socket successfully bound to address\n");

  // 3. set socket in a 'listen state'
  // TODO: man listen
  // NOTE: SOMAXCONN -> max length of the queue of pending connections for our TCP socket
  if (listen(sockfd, SOMAXCONN) != 0) {
    perror("webserver (listen)");
    return 1;
  }
  printf("server listening for connections\n");

  // 4. accept connections
  // TODO: man accept
  // TODO: man close
  while (1) {
	// NOTE: every time we accept the connection -> new socket is created
    int newsockfd = accept(sockfd, (struct sockaddr *)&host_addr,
                           (socklen_t *)&host_addrlen);
    if (newsockfd < 0) {
      perror("webserver (accept)");
      continue;
    }
    printf("connection accepted\n");

    // 5 read request
    // read -> read up to count bytes from file descriptor into buffer pointer
    int valread = read(newsockfd, buffer, BUFFER_SIZE);
    if (valread < 0) {
      perror("webserver (read)");
      continue;
    }

    printf("Request:\n%s", buffer);

    // 6 write response to the socket
    int valwrite = write(newsockfd, resp, strlen(resp));
    if (valwrite < 0) {
      perror("webserver (write)");
      continue;
    }
    close(newsockfd);
  }

  return 0;
}
