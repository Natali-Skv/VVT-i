//
// Created by Yut Fut on 18.11.2021.
//

// http base

#ifndef VVT_I_HTTP_REQEST_H
#define VVT_I_HTTP_REQEST_H

#include "command.h"

#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <cstring>

#include <fstream>
#include <iostream>

class HTTPRequest {
public:

    static void init_sockaddr(struct sockaddr_in* name);

    static void crate_message(std::string &file_name, std::string &message);

    static void write_to_server(int filedes, std::string msg);

    static void read_from_server(int filedes);

    static int send(std::string file_name);
};

#endif //VVT_I_HTTP_REQEST_H