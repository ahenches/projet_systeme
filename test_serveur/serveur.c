#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>



int main(int argc, char *argv[])
{

    // memset(&adresse, 0, sizeof(struct sockaddr_in));

    // adresse.sin_family = AF_INET;

    // // donner un numero de port disponible quelconque
    // adresse.sin_port = htons(0);

    // // aucun contr�le sur l'adresse IP :
    // adresse.sin_addr.s_addr = htons(INADDR_ANY);
    int sockServer = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adresseServer;
    struct sockaddr_in adresseClient;
    socklen_t csize = sizeof(adresseClient);
    
    adresseServer.sin_addr.s_addr = inet_addr("127.0.0.1");
    adresseServer.sin_family = AF_INET;
    adresseServer.sin_port = htons(30000);

    bind(sockServer, (const struct sockaddr *)&adresseServer, sizeof(adresseServer));
    printf("bind : %d\n", sockServer);

    listen(sockServer, 1);
    printf("listen\n");
    

    
    
    int sockClient = accept(sockServer, (struct sockaddr *)&adresseClient, &csize);
    printf("accepte\n");
    
    printf("client : %d\n", sockClient);

    send(sockClient, "Hello world!\r\n", 15, 0);

    close(sockClient);
    close(sockServer);

    return 0;
}
