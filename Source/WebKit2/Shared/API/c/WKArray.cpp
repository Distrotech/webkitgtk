/*
 * Copyright (C) 2010 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "WKArray.h"

#include "APIArray.h"
#include "WKAPICast.h"

using namespace WebKit;

WKTypeID WKArrayGetTypeID()
{
    return toAPI(API::Array::APIType);
}

WKArrayRef WKArrayCreate(WKTypeRef* values, size_t numberOfValues)
{
    Vector<RefPtr<API::Object>> elements;
    elements.reserveInitialCapacity(numberOfValues);

    for (size_t i = 0; i < numberOfValues; ++i)
        elements.uncheckedAppend(const_cast<API::Object*>(static_cast<const API::Object*>(values[i])));

    return toAPI(API::Array::create(std::move(elements)).leakRef());
}

WKArrayRef WKArrayCreateAdoptingValues(WKTypeRef* values, size_t numberOfValues)
{
    Vector<RefPtr<API::Object>> elements;
    elements.reserveInitialCapacity(numberOfValues);

    for (size_t i = 0; i < numberOfValues; ++i)
        elements.uncheckedAppend(adoptRef(const_cast<API::Object*>(static_cast<const API::Object*>(values[i]))));

    return toAPI(API::Array::create(std::move(elements)).leakRef());
}

WKTypeRef WKArrayGetItemAtIndex(WKArrayRef arrayRef, size_t index)
{
    return toImpl(arrayRef)->at(index);
}

size_t WKArrayGetSize(WKArrayRef arrayRef)
{
    return toImpl(arrayRef)->size();
}
