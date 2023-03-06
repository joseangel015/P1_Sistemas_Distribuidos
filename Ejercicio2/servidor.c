 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>

int main(int argc, char **argv){

  if(argc<2)
  {
    printf("Ingrese <puerto>\n");
    return 1;
  }
  int server_socket, client_socket, puerto,backlog=3,received_num; //Descriptores de los sockets de cliente y servidor
  struct sockaddr_in server_addr, client_addr; //Estructura que describe a una dirección de socket de internet
  socklen_t addrlen = sizeof(client_addr);
  char buffer[1024],str_num[20];; //Espacio de memoria que almacena el mensaje recibido

  puerto = atoi(argv[1]);

  // Creando el socket del servidor
	if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
 
  bzero((char *)&server_addr, sizeof(server_addr)); //Llenamos la estructura de 0's
  bzero((char *)&buffer, sizeof(buffer));
  
  server_addr.sin_family = AF_INET; //Especifica la familia de direcciones IPv4
  server_addr.sin_port = htons(puerto);
  server_addr.sin_addr.s_addr = INADDR_ANY; //Contiene al dirección del host
  if(bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
  { //asignamos un puerto al socket
    printf("Error al asociar el puerto a la conexion\n");
    close(server_socket);
    return 1;
  }
  listen(server_socket, backlog); //Pone el socket del servidor en modo pasivo, donde espera a que el cliente se acerque al servidor para establecer una conexión
  printf("A la escucha en el puerto %d\n", ntohs(server_addr.sin_port)); //Convierte de network byte order a host byte order
  
  if ((client_socket
		= accept(server_socket, (struct sockaddr*)&client_addr,
				&addrlen))
		< 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}

  printf("Conectando con %s:%d\n", inet_ntoa(client_addr.sin_addr),client_addr.sin_port);  
  int aux,num=0;
  while(1){ 
    aux = read(client_socket, &num, sizeof(num));
    if( aux< 0){ //Comenzamos a recibir datos del cliente
      //Si read() recibe 0 el cliente ha cerrado la conexion. Si es menor que 0 ha habido algún error.
      printf("Error al recibir los datos\n");
      close(server_socket);
      return 1;
    }else{ 
      printf("Mensaje recibido: %d\n", num);
      num=num+1;
      send(client_socket,&num, sizeof(num),0);
    }
  }
  close(client_socket);
  close(server_socket);
  return 0;
}
