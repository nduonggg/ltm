#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>


typedef struct Account{
    char username[50];
    char password[50];
    int status;
    struct Account *next;
} Account;

int checkSt(char *user)
{
    char username[1024];
    char password[1024];
    int status;
    FILE *file = fopen("account.txt", "r");
    do
    {
        if (fscanf(file, "%s %s %d", username, password, &status) > 0)
        {
            if (!strcmp(username, user))
            {
                return status;
            }
        }
    } while (1);
}


void setStatus(char *user, int st)
{
    const char *filename = "account.txt";
    FILE *file = fopen(filename, "rw");
    char line[100];
    while (fgets(line, sizeof(line), file))
    {
        char username[50];
        char password[50];
        int status;

        if (scanf(line, "%s %s %d", username, password, &status) == 3)
        {
            if (strcmp(username, user) == 0)
            {
                status = st;
            }

            // rewrite tmp file
            fprintf(file, "%s %s %d\n", username, password, status);
        }
    }

    fclose(file);

    return;
}



int checkPass(char *user, char *pass)
{
    char username[50];
    char password[50];
    int status;
    FILE *file = fopen("account.txt", "r");

    while (fscanf(file, "%s %s %d", username, password, &status) > 0)
    {
        if (strcmp(username, user) == 0)
        {
            if (strcmp(password, pass) == 0)
            {
                if (status != 1)
                {
                    return 3;
                }
                return 1;
            }
            else
                return 0;
        }
    }

    return 2;
    fclose(file);
}


int main(int argc, char *argv[]){
    struct sockaddr_in server;
    struct sockaddr_in client;
    int sv_sock;
    char buff[1024];
    char otherPassword[1024], new_password[1024];
    int byte_send, byte_received_client, byte_received_client2, message_received_client, username_password_received_client,otherPassword_received_client;
    
    int sin_sz;
    pid_t pid;
    
    
    if ((sv_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Error: ");
        exit(0);
    }

    
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[1]));
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server.sin_zero), 8);

    if (bind(sv_sock, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
    {
        perror("\nError");
        exit(0);
    }
    
    if (listen(sv_sock, 5) == -1) {
        perror("Error listening for connections");
        exit(0);
    }
 
    
    while (1){
        sin_sz = sizeof(struct sockaddr_in);
        
        int client_sock = accept(sv_sock, (struct sockaddr *)&client, &sin_sz) ; // Chấp nhận kết nối từ client
        
        if((pid = fork()) == 0) {

            close(sv_sock);
           if (client_sock < 0) {
               perror("\nError");
               exit(0);
           }
        
        printf("Client connected from %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
        
        
        
        
        int bytes_sent = send(client_sock, "done", 4, 0);
        if (bytes_sent < 0)
            perror("\nError");
        
      
            while (1){
                username_password_received_client = recv(client_sock, buff, 1024 - 1, 0);
                if (username_password_received_client < 0){
                    
                    perror("\nError");
                break;
                }
                else
                {
                    buff[username_password_received_client - 1] = '\0';
                    char *newline_pos = strchr(buff, '\n');

                    if (newline_pos != NULL)
                    {
                        *newline_pos = '\0';

                        char username[1024];
                        strcpy(username, buff);
                        char *password = newline_pos + 1;
                        int count = 0;

                        
                        if (checkPass(username, password) == 2)
                        {
                            byte_send = send(client_sock, "username_not_exist", 1024, 0);
                            exit(0);
                        }

                        
                        if (checkPass(username, password) == 3)
                        {
                            byte_send = send(client_sock, "not_ready", 1024, 0);
                            exit(0);
                        }

                    
                        while (checkPass(username, password) == 0 && count < 2)
                        {
                            byte_send = send(client_sock, "incorrect_password", 1024, 0);
                            if (byte_send < 0)
                                perror("\nError");
                            otherPassword_received_client = recv(client_sock, password, 1024 - 1, 0);
                            password[otherPassword_received_client - 1] = '\0';
                            count++;
                        }

                        if (count == 2)
                        {
                            byte_send = send(client_sock, "notOK", 6, 0);
                            setStatus(username, 0);
                        }

                    
                        int status = checkSt(username);
                        if (status == 1)
                        {
                            byte_send = send(client_sock, "OK", 1024, 0);
                            message_received_client = recv(client_sock, new_password, 1024 - 1, 0);
                            new_password[message_received_client - 1] = '\0';

                            // Signout
                            if (strcmp(new_password, "logout") == 0)
                            {
                                byte_send = send(client_sock, "Goodbye", 1024, 0);
                                exit(0);
                            }
                            
                        }
                        else if (status == 0 || status == 2)
                        {
                            byte_send = send(client_sock, "account_not_ready", 18, 0);
                        }
                    }
                }
            }
            close(client_sock);
            exit(0);
        }
        

    close(client_sock);
    }
    return 0;
}

