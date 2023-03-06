#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
int main(int argc, char **argv){
  if(argc<2)//verifica que se hayan mandao como argumento el hostname y el puerto
  {
    printf("<host> <puerto>\n");
    return 1;
  }
  struct sockaddr_in cliente; //estructura para el socket del cliente
  struct hostent *servidor;  //estructura para almacenar los datos del cliente
  servidor = gethostbyname(argv[1]); //se obtiene el IP del servidor a partir del hostname
  if(servidor == NULL)
  { //Comprobación
    printf("Host erróneo\n");
    return 1;
  }
  int puerto, conexion;
  char buffer[100];
  conexion = socket(AF_INET, SOCK_STREAM, 0); //crea un socket que use IPv4 y TCP
  puerto=(atoi(argv[2])); //determina el puerto a partir del segundo argumento 
  bzero((char *)&cliente, sizeof((char *)&cliente)); //inicializa en cero la estructura cliente
        
  cliente.sin_family = AF_INET; //el cliente usará IPv4
  cliente.sin_port = htons(puerto); //se asigna el puerto a usar
  //La dirección sockaddr_in del cliente se utiliza para especificar la dirección de destino en la conexión
  bcopy((char *)servidor->h_addr, (char *)&cliente.sin_addr.s_addr, sizeof(servidor->h_length)); //se asigna la dirección de destino en la conexión
  
  if(connect(conexion,(struct sockaddr *)&cliente, sizeof(cliente)) < 0)//se realiza la conexión 
  { 
    printf("Error conectando con el host\n");
    close(conexion);
    return 1;
  }
  printf("Conectado con %s:%d\n",inet_ntoa(cliente.sin_addr),htons(cliente.sin_port));
  while(1){
  printf("Escribe un mensaje: ");
  fgets(buffer, 100, stdin); 
  send(conexion, buffer, 100, 0); //envio del mensaje mediante el socket conexión
  bzero(buffer, 100); //limpia el buffer
  recv(conexion, buffer, 60, 0); //recepción del mensaje mediante el socket conexión
  printf("%s", buffer);
  }
  
return 0;
}
