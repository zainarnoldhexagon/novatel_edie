// ===============================================================================
// |                                                                             |
// |  COPYRIGHT NovAtel Inc, 2022. All rights reserved.                          |
// |                                                                             |
// |  Permission is hereby granted, free of charge, to any person obtaining a    |
// |  copy of this software and associated documentation files (the "Software"), |
// |  to deal in the Software without restriction, including without limitation  |
// |  the rights to use, copy, modify, merge, publish, distribute, sublicense,   |
// |  and/or sell copies of the Software, and to permit persons to whom the      |
// |  Software is furnished to do so, subject to the following conditions:       |
// |                                                                             |
// |  The above copyright notice and this permission notice shall be included    |
// |  in all copies or substantial portions of the Software.                     |
// |                                                                             |
// |  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR |
// |  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   |
// |  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    |
// |  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER |
// |  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING    |
// |  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER        |
// |  DEALINGS IN THE SOFTWARE.                                                  |
// |                                                                             |
// ===============================================================================
// ! \file novatel_file_parser.hpp
// ===============================================================================

#ifndef DYNAMIC_LIBRARY_NOVATEL_FILE_PARSER_HPP
#define DYNAMIC_LIBRARY_NOVATEL_FILE_PARSER_HPP

#include "decoders/novatel/api/common.hpp"
#include "decoders/novatel/api/file_parser.hpp"
#include "decoders/novatel/api/filter.hpp"
#include "decoders_export.h"
#include "hw_interface/stream_interface/api/input_file_stream.hpp"

extern "C"
{
    // Construct/Destruct
    DECODERS_EXPORT novatel::edie::oem::FileParser* novatel_file_parser_init(JsonReader* pclJsonDb_);
    DECODERS_EXPORT void novatel_file_parser_delete(novatel::edie::oem::FileParser* pclFileParser_);

    // Config
    DECODERS_EXPORT void novatel_file_parser_load_json_db(novatel::edie::oem::FileParser* pclFileParser_, JsonReader* pclJsonDb_);

    DECODERS_EXPORT void novatel_file_parser_set_ignore_abbrev_ascii_responses(novatel::edie::oem::FileParser* pclFileParser_,
                                                                               bool bIgnoreAbbrevASCIIResponsesCmp_);
    DECODERS_EXPORT bool novatel_file_parser_get_ignore_abbrev_ascii_responses(novatel::edie::oem::FileParser* pclFileParser_);
    DECODERS_EXPORT void novatel_file_parser_set_decompress_rangecmp(novatel::edie::oem::FileParser* pclFileParser_, bool bDecompressRangeCmp_);
    DECODERS_EXPORT bool novatel_file_parser_get_decompress_rangecmp(novatel::edie::oem::FileParser* pclFileParser_);
    DECODERS_EXPORT void novatel_file_parser_set_return_unknown_bytes(novatel::edie::oem::FileParser* pclFileParser_, bool bReturnUnknownBytes_);
    DECODERS_EXPORT bool novatel_file_parser_get_return_unknown_bytes(novatel::edie::oem::FileParser* pclFileParser_);
    DECODERS_EXPORT void novatel_file_parser_set_encode_format(novatel::edie::oem::FileParser* pclFileParser_,
                                                               novatel::edie::ENCODEFORMAT eEncodeFormat_);
    DECODERS_EXPORT novatel::edie::ENCODEFORMAT novatel_file_parser_get_encode_format(novatel::edie::oem::FileParser* pclFileParser_);

    DECODERS_EXPORT novatel::edie::oem::Filter* novatel_file_parser_get_filter(novatel::edie::oem::FileParser* pclFileParser_);
    DECODERS_EXPORT void novatel_file_parser_set_filter(novatel::edie::oem::FileParser* pclFileParser_, novatel::edie::oem::Filter* pclFilter_);

    DECODERS_EXPORT unsigned char* novatel_file_parser_get_buffer(novatel::edie::oem::FileParser* pclFileParser_);

    // Stream, R/W
    DECODERS_EXPORT bool novatel_file_parser_set_stream(novatel::edie::oem::FileParser* pclFileParser_, InputFileStream* pclIFS_);
    DECODERS_EXPORT uint32_t novatel_file_parser_get_percent_read(novatel::edie::oem::FileParser* pclFileParser_);

    // R/W
    DECODERS_EXPORT novatel::edie::STATUS novatel_file_parser_read(novatel::edie::oem::FileParser* pclFileParser_,
                                                                   novatel::edie::MessageDataStruct* pstMessageData_,
                                                                   novatel::edie::oem::MetaDataStruct* pstMetaData_);
    DECODERS_EXPORT bool novatel_file_parser_reset(novatel::edie::oem::FileParser* pclFileParser_);

    DECODERS_EXPORT uint32_t novatel_file_parser_flush(novatel::edie::oem::FileParser* pclFileParser_, unsigned char* pucBuffer_,
                                                       uint32_t uiBufferSize_);
}

#endif // DYNAMIC_LIBRARY_NOVATEL_FILE_PARSER_HPP
