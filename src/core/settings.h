/*
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * Copyright (c) 2020, Savely Pototsky (SavaLione)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/**
 * @file
 * @brief Settings
 * @author SavaLione
 * @date 16 Nov 2020
 */
#ifndef CORE_SETTINGS_H
#define CORE_SETTINGS_H

#include <string>

enum database
{
    SQLITE = 1,
    MYSQL = 2,
    MARIADB = 3,
    POSTGRESQL = 4
};

enum log_level
{
    TRACE = 1,
    DEBUG = 2,
    INFO = 3,
    WARN = 4,
    ERROR = 5,
    CRITICAL = 6
};

class settings
{
public:
    static settings &Instance()
    {
        static settings s;
        return s;
    }

    ~settings();

    log_level l_level();

    std::string ip();
    int port();

    std::string fcgi_socket_path();
    int fcgi_thread_count();

    database db();
    std::string db_host();
    std::string db_name();
    std::string db_username();
    std::string db_password();

    std::string db_sqlite_name();

private:
    settings();
    settings(settings const &) = delete;
    settings &operator=(settings const &) = delete;

    // log_level _L_level = INFO;
    /* На время разработки SBC */
    log_level _l_level = DEBUG;

    std::string _ip = "0.0.0.0";
    int _port = 12340;
    
    // std::string _fcgi_socket_path = "127.0.0.1:9000";
    std::string _fcgi_socket_address = "127.0.0.1";
    std::string _fcgi_socket_port = "9000";
    int _fcgi_thread_count = 8;

    database _db = MYSQL;
    std::string _db_host = "tcp://127.0.0.1:3306";
    std::string _db_username = "username";
    std::string _db_password = "password";
    std::string _db_name = "db_name";

    std::string _db_sqlite_name = "db_name.db";

};

#endif // CORE_SETTINGS_H