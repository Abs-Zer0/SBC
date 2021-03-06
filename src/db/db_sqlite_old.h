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
 * @brief Working with sqlite database
 * @author SavaLione
 * @date 16 Nov 2020
 */
#ifndef DB_DB_SQLITE_H
#define DB_DB_SQLITE_H

#include <string>
#include <vector>
#include <sqlite3.h>

class db_sqlite
{
public:
    static db_sqlite &Instance()
    {
        static db_sqlite d;
        return d;
    }

    ~db_sqlite();

    std::vector<std::string> open(std::string db_name);
    std::vector<std::string> open(std::string db_name, int &status);
    void close();
    bool db_open();

    std::vector<std::string> vec_answer(std::string request);
    std::vector<std::string> vec_answer(std::string request, int &rc);
    void request(std::string request);
    void request(std::string request, int &status);

private:
    db_sqlite();
    db_sqlite(db_sqlite const &) = delete;
    db_sqlite &operator=(db_sqlite const &) = delete;

    sqlite3 *_db;
    sqlite3_stmt *_stmt;

    std::string _db_name;

    std::vector<std::string> _open();
    std::vector<std::string> _open(int &status);

    bool _db_open = false;

    void _close();
};

#endif // DB_DB_SQLITE_H