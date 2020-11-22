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
 * @brief SBC server
 * @author SavaLione
 * @date 15 Nov 2020
 */

#include <thread>

#include "core/settings.h"
#include "core/uuid.h"

#include "io/logger.h"

#include "net/server.h"

#include "db/db_sqlite.h"

#include "web/web.h"
#include "web/mime.h"

void web_server()
{
    spdlog::info("Start web FastCGI server.");
    web *web_f = new web();

    delete web_f;
}

void sbc_server()
{
    settings &settings_instance = settings::Instance();

    spdlog::info("Start SBC server.");

    try
    {
        boost::asio::io_context io_context;
        server s(io_context, settings_instance.port());
        io_context.run();
    }
    catch (const std::exception &e)
    {
        //std::cerr << "Exception: " << e.what() << '\n';
        spdlog::error("SBC server exception: {}", e.what());
    }
}

int main(int argc, char *argv[])
{
    /* Logger initialization */
    logger_init();

    /* Settings initialization */
    settings &settings_instance = settings::Instance();

    /* Запуск web сервера */
    std::thread thread_web_server(web_server);

    /* Запуск sbc сервера */
    std::thread thread_sbc_server(sbc_server);

    /* uuid */
    uuid_init();

    /* mime test */
    spdlog::debug("mime: \n{}\n", mime_type(text_html));
    spdlog::debug("mime: \n{}\n", mime_type(application_edi_x12));

    if (thread_web_server.joinable())
    {
        thread_web_server.join();
        spdlog::info("Stop web FastCGI server.");
    }

    if (thread_sbc_server.joinable())
    {
        thread_sbc_server.join();
        spdlog::info("Stop SBC server.");
    }

    return 0;
}
