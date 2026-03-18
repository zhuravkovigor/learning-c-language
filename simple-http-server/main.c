#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

struct sockaddr_in address;

int main() {
  const int server_fd = socket(AF_INET, SOCK_STREAM, 0);

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(8080);

  socklen_t address_length = sizeof(address);

  const int bind_id =
      bind(server_fd, (struct sockaddr *)&address, address_length);

  if (bind_id < 0) {
    perror("8080 Server is already busy\n");
  }
  listen(server_fd, 10);

  int new_socket;

  while (1) {
    new_socket =
        accept(server_fd, (struct sockaddr *)&address, &address_length);
    char buffer[3000] = {0};
    read(new_socket, buffer, 30000);

    FILE *f = fopen("index.html", "r");

    if (f == NULL) {
      char *error = "HTTP/1.1 404 Not Found\nContent-Length: 0\n\n";
      write(new_socket, error, strlen(error));
    } else {
      fseek(f, 0, SEEK_END);

      long file_size = ftell(f);
      fseek(f, 0, SEEK_SET);

      char *file_content = malloc(file_size + 1);
      fread(file_content, 1, file_size, f);
      fclose(f);

      char header[512];
      sprintf(header,
              "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: "
              "%ld\n\n",
              file_size);

      write(new_socket, header, strlen(header));
      write(new_socket, file_content, strlen(file_content));

      free(file_content);
    }

    close(new_socket);
  }

  return 0;
}
