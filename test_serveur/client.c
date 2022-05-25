#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>


int main(int argc, char *argv[])
{
    int sockClient = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adresseClient;
    char buffer[15];
    
    adresseClient.sin_addr.s_addr = inet_addr("127.0.0.1");
    adresseClient.sin_family = AF_INET;
    adresseClient.sin_port = htons(30000);

    int connectres = connect(sockClient, (const struct sockaddr *)&adresseClient, sizeof(adresseClient));

    printf("%d\n", sockClient);

    printf("errno : %s\n", strerror(errno));
    
    printf("attente de donnée ... ");
    int res = recv(sockClient, buffer, 15, 0);
    printf("%d\n", res);

    printf("%s\n", buffer);

    close(sockClient);

    return 0;
}
