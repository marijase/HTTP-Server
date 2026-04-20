/* 
    ********************************************************************
    Odsek:          Elektrotehnika i racunarstvo
    Departman:      Racunarstvo i automatika
    Katedra:        Racunarska tehnika i racunarske komunikacije (RT-RK)
    Predmet:        Osnovi Racunarskih Mreza 
    Godina studija: Treca (III)
    Skolska godina: 2024/2025
    Semestar:       Zimski (V)
    Tip zadatka:    Projektni zadatak

    Ime fajla:      server.c
    Opis:           HTTP server
    
    OS:             Ubuntu 20.04.4
    ********************************************************************
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>


#define PORT 80
#define BUFFER_SIZE 4096



void ParseRequest(const char *buffer, char *filename) {
    char method[8], path[256];
    sscanf(buffer, "%s %s", method, path);
    if (strcmp(method, "GET") == 0) {
        // ignore first '/' in the path
        strncpy(filename, path + 1, 255);
        filename[256] = '\0';
    } else {
        //received method is not GET method
        filename[0] = '\0'; 
        printf("Unexpected method /n");
    }
}

void SendError(int clientSock) {
    const char *notFoundBody = "HTTP/1.1 404 Page not found\n";
    char response[1024];
    sprintf(response,
        "HTTP/1.1 404 not found\r\n"
        "Connection: close\r\n"
        "\r\n");

    strcat(response, notFoundBody);
    send(clientSock, response, strlen(response), 0);
    
}


void SendResponse(int clientSock, const char *filename) {
    //check if file existes
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        SendError(clientSock);
        return;
    }

    char fileContent[BUFFER_SIZE];
    size_t fileSize = fread(fileContent, 1, sizeof(fileContent) - 1, fp);
    fileContent[fileSize] = '\0';
    fclose(fp);

    char response[5000];
    sprintf(response,
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "Connection: close\r\n"
        "\r\n");
        strcat(response, fileContent);

    send(clientSock, response, strlen(response), 0);
   
}



void HandleClient(int clientSock) {
    char buffer[BUFFER_SIZE];
    ssize_t readSize = recv(clientSock, buffer, sizeof(buffer) - 1, 0);
    if (readSize <= 0) return;

    buffer[readSize] = '\0';
    printf("Request accepted:\n%s\n", buffer);

    char filename[256];
    ParseRequest(buffer, filename);

    if (strlen(filename) > 0) {
        SendResponse(clientSock, filename);
    } else {
        SendError(clientSock);
    }

    close(clientSock);
}




int main() {
    int socketDesc, clientSock, c;
    struct sockaddr_in serverAddr, clientAddr;
  

    //Create socket
    socketDesc = socket(AF_INET, SOCK_STREAM, 0);
    if (socketDesc == -1) {
        perror("Could not create socket");
        exit(1);
    }

    //Make port reusable
    int opt = 1;
    setsockopt(socketDesc, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    //Prepare the sockaddr_in structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    //Bind
    if (bind(socketDesc, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed.");
        close(socketDesc);
        exit(1);
    }

    //Listen 
    listen(socketDesc, 3);
    printf("HTTP server waits for incoming connections at the port %d...\n", PORT);

    c = sizeof(struct sockaddr_in);


    while (1) {
        clientSock = accept(socketDesc, (struct sockaddr*)&clientAddr, (socklen_t*)&c);
        if (clientSock < 0) {
            perror("Accept failed");
            continue; 
        }

        HandleClient(clientSock);

    }

    close(socketDesc);
    return 0;
}

