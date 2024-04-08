////////////////////////////////////////////////////////////////////////
//
// COPYRIGHT NovAtel Inc, 2022. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
////////////////////////////////////////////////////////////////////////
//                            DESCRIPTION
//
//! \file common.cpp
//! \brief Common functions for the EDIE source code
////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------
#include "common.hpp"

#include "jsonreader.hpp"

using namespace novatel::edie;

//-----------------------------------------------------------------------
bool IsEqual(double dVal1_, double dVal2_, double dEpsilon_) { return std::abs(dVal1_ - dVal2_) < dEpsilon_; }

//-----------------------------------------------------------------------
uint32_t CreateMsgID(uint32_t uiMessageID_, uint32_t uiSiblingID_, uint32_t uiMsgFormat_, uint32_t uiResponse_)
{
    return static_cast<uint16_t>(uiMessageID_) | (static_cast<uint32_t>(MESSAGEIDMASK::MEASSRC) & (uiSiblingID_ << 16)) |
           (static_cast<uint32_t>(MESSAGEIDMASK::MSGFORMAT) & (uiMsgFormat_ << 21)) |
           (static_cast<uint32_t>(MESSAGEIDMASK::RESPONSE) & (uiResponse_ << 23));
}

//-----------------------------------------------------------------------
void UnpackMsgID(const uint32_t uiMessageID_, uint16_t& usMessageID_, uint32_t& uiSiblingID_, uint32_t& uiMsgFormat_, uint32_t& uiResponse_)
{
    usMessageID_ = (uiMessageID_ & static_cast<uint32_t>(MESSAGEIDMASK::LOGID));
    uiSiblingID_ = (uiMessageID_ & static_cast<uint32_t>(MESSAGEIDMASK::MEASSRC)) >> 16;
    uiMsgFormat_ = (uiMessageID_ & static_cast<uint32_t>(MESSAGEIDMASK::MSGFORMAT)) >> 21;
    uiResponse_ = (uiMessageID_ & static_cast<uint32_t>(MESSAGEIDMASK::RESPONSE)) >> 23;
}

//-----------------------------------------------------------------------
unsigned char PackMsgType(const uint32_t uiSiblingID_, const uint32_t uiMsgFormat_, const uint32_t uiResponse_)
{
    return static_cast<uint8_t>(((uiResponse_ << 7) & static_cast<uint32_t>(MESSAGETYPEMASK::RESPONSE)) |
                                ((uiMsgFormat_ << 5) & static_cast<uint32_t>(MESSAGETYPEMASK::MSGFORMAT)) |
                                ((uiSiblingID_ << 0) & static_cast<uint32_t>(MESSAGETYPEMASK::MEASSRC)));
}

//-----------------------------------------------------------------------
std::string GetEnumString(const EnumDefinition* const stEnumDef_, uint32_t uiEnum_)
{
    if (stEnumDef_ != nullptr)
    {
        for (auto& e : stEnumDef_->enumerators)
        {
            if (e.value == uiEnum_) { return e.name; }
        }
    }

    return "UNKNOWN";
}

//-----------------------------------------------------------------------
int32_t GetEnumValue(const EnumDefinition* const stEnumDef_, std::string strEnum_)
{
    if (stEnumDef_ != nullptr)
    {
        for (auto& e : stEnumDef_->enumerators)
        {
            if (e.name == strEnum_) { return static_cast<int32_t>(e.value); }
        }
    }

    return 0;
}

//-----------------------------------------------------------------------
int32_t GetResponseId(const EnumDefinition* const stRespDef_, std::string strResp_)
{
    if (stRespDef_ != nullptr)
    {
        for (auto& e : stRespDef_->enumerators)
        {
            if (e.description == strResp_) { return static_cast<int32_t>(e.value); }
        }
    }

    return 0;
}

//-----------------------------------------------------------------------
int32_t ToDigit(char c) { return static_cast<int32_t>(c - '0'); }

//-----------------------------------------------------------------------
bool ConsumeAbbrevFormatting(uint64_t ullTokenLength_, char** ppucMessageBuffer_)
{
    if (ullTokenLength_ < 2 && (**ppucMessageBuffer_ == '\r' || **ppucMessageBuffer_ == '\n' || **ppucMessageBuffer_ == '<'))
    {
        bool bIsAbbrev = false;

        while (true)
        {
            switch (**ppucMessageBuffer_)
            {
            case '<': bIsAbbrev = true; [[fallthrough]];
            case '\r': [[fallthrough]];
            case '\n': ++(*ppucMessageBuffer_); break;
            case ' ':
                if (!bIsAbbrev) { return false; }
                ++(*ppucMessageBuffer_);
                break;
            default: return bIsAbbrev;
            }
        }
    }

    return false;
}
