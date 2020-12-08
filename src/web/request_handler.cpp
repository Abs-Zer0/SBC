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
 * @brief Обработчик веб запросов
 * @author SavaLione
 * @date 08 Dec 2020
 */
#include "web/request_handler.h"

request_handler::~request_handler()
{
}

void request_handler::_init()
{
    _recognize_cookie();
    _recognize_method();
}

void request_handler::_recognize_cookie()
{
    // if (FCGX_GetParam("HTTP_COOKIE", _request.envp) != NULL)
    // {
    //     _http_cookie = FCGX_GetParam("HTTP_COOKIE", _request.envp);
    //     _is_cookie_set = true;
    // }
    // else
    // {
    //     _http_cookie = "NULL";
    //     _is_cookie_set = false;
    // }

    if (_http_cookie == "NULL")
    {
        _is_cookie_set = false;
    }
    else
    {
        _is_cookie_set = true;
    }
    
}

void request_handler::_recognize_method()
{
    if (_request_method == "OPTIONS")
    {
        _method = _OPTIONS;
        return;
    }

    if (_request_method == "GET")
    {
        _method = _GET;
        return;
    }

    if (_request_method == "HEAD")
    {
        _method = _HEAD;
        return;
    }

    if (_request_method == "POST")
    {
        _method = _POST;
        return;
    }

    if (_request_method == "PUT")
    {
        _method = _PUT;
        return;
    }

    if (_request_method == "DELETE")
    {
        _method = _DELETE;
        return;
    }

    if (_request_method == "TRACE")
    {
        _method = _TRACE;
        return;
    }

    if (_request_method == "CONNECT")
    {
        _method = _CONNECT;
        return;
    }
}

const method request_handler::get_method()
{
    return _method;
}