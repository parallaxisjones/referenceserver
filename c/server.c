#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    int create_socket, new_socket;
    socklen_t addrlen;

    int bufsize = 1024;
    char *buffer = malloc(bufsize);
    struct sockaddr_in address;

    create_socket = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(15000);

    bind(create_socket, (struct sockaddr *) &address, sizeof(address));

    while (1) {
        listen(create_socket, 10);
	new_socket = accept(create_socket, (struct sockaddr *) &address, &addrlen);
	recv(new_socket, buffer, bufsize, 0);
	printf("%s\n", buffer);
	write(new_socket, "hello world\n", 12);
	close(new_socket);
    }

    close(create_socket);
    return 0;
}
