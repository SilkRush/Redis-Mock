/**
 * @file server.h
 * @brief TCP server (a program that accepts connections and echoes back what it receives)
 *
 * @author Abhishek Regmi
 * @date 05/26/2026
 */

#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>

#include "parser.h"
#include "command.h"

class Server
{
public:
    int socket_fd;
    Store store;
    Server()
    {
        // AF_INET means IPV4
        // SOCK_STREAM means TCP
        socket_fd = socket(AF_INET, SOCK_STREAM, 0);

        if (socket_fd < 0)
        {
            // Throws the error
            perror("socket");
            exit(EXIT_FAILURE);
        }

        // Set SO_REUSEADDR so,it can restart without waiting
        int opt = 1;
        int socket_opt = setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

        if (socket_opt < 0)
        {
            perror("setsocketopt");
            exit(EXIT_FAILURE);
        }

        // Initialize and configure IPv4 address structure to bind port 6379 on all network interfaces.
        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(6379);
        addr.sin_addr.s_addr = INADDR_ANY;

        int socket_bind = bind(socket_fd, (struct sockaddr *)&addr, sizeof(addr));
        if (socket_bind < 0)
        {
            perror("bind");
            exit(EXIT_FAILURE);
        }

        int socket_listen = listen(socket_fd, 10);
        if (socket_listen < 0)
        {
            perror("listen");
            exit(EXIT_FAILURE);
        }
    }

    ~Server()
    {
        if (socket_fd >= 0)
        {
            close(socket_fd);
        }
    }

    // Runs the server in a loop and handles incoming client
    // Accept one client at a time
    void run()
    {
        while (true)
        {
            struct sockaddr_in client_addr;
            socklen_t client_len = sizeof(client_addr);
            int client_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &client_len);
            if (client_fd == -1)
            {
                perror("accept");
                continue;
            }
            char buffer[1024];
            int byte_read = read(client_fd, buffer, sizeof(buffer) - 1);
            if (byte_read == -1)
            {
                perror("read");
                close(client_fd);
                continue;
            }
            buffer[byte_read] = '\0';

            // Calling the parser from the parser.h
            std::vector<std::string> command = parse(std::string(buffer, byte_read));
            std::string response = handle(command, store);
            write(client_fd, response.c_str(), response.length());
            close(client_fd);
        }
    }
};

#endif