// Server side C/C++ program to demonstrate Socket
// programming
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080


int main(int argc, char const* argv[])
{
	int server_fd, new_socket, valread,rec_num,num_max_try = 10; 
	struct sockaddr_in address; 
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = { 0 }; 
	char str_num[20];

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET,
				SO_REUSEADDR | SO_REUSEPORT, &opt,
				sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);


	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr*)&address,
			sizeof(address))
		< 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	if (listen(server_fd, num_max_try) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

	if ((new_socket
		= accept(server_fd, (struct sockaddr*)&address,
				(socklen_t*)&addrlen))
		< 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}

	while(1){
		valread = read(new_socket, buffer, 1024);
		rec_num = atoi(buffer);
		if(rec_num == 0){
			break;
		}
		printf("Recibi este mensaje: %d\n", rec_num);
		rec_num += 1;
		sprintf(str_num,"%d",rec_num);
		send(new_socket, str_num, strlen(str_num), 0);
		printf("Mensaje enviado al cliente: %s\n",str_num);
	}
	
	
	// closing the connected socket
	close(new_socket);
	// closing the listening socket
	shutdown(server_fd, SHUT_RDWR);
	return 0;
}
