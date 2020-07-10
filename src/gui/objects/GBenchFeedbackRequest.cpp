/* $Id: GBenchFeedbackRequest.cpp 14666 2007-07-09 13:40:22Z dicuccio $
 * ===========================================================================
 *
 *                            PUBLIC DOMAIN NOTICE
 *               National Center for Biotechnology Information
 *
 *  This software/database is a "United States Government Work" under the
 *  terms of the United States Copyright Act.  It was written as part of
 *  the author's official duties as a United States Government employee and
 *  thus cannot be copyrighted.  This software/database is freely available
 *  to the public for use. The National Library of Medicine and the U.S.
 *  Government have not placed any restriction on its use or reproduction.
 *
 *  Although all reasonable efforts have been taken to ensure the accuracy
 *  and reliability of the software and data, the NLM and the U.S.
 *  Government do not and cannot warrant the performance or results that
 *  may be obtained by using this software or data. The NLM and the U.S.
 *  Government disclaim all warranties, express or implied, including
 *  warranties of performance, merchantability or fitness for any particular
 *  purpose.
 *
 *  Please cite the author in any work or product based on this material.
 *
 * ===========================================================================
 *
 * Author:  .......
 *
 * File Desc:
 *   .......
 *
 * Remark:
 *   This code was originally generated by application DATATOOL
 *   using the following specifications:
 *   'gbench_svc.asn'.
 */

// standard includes
#include <ncbi_pch.hpp>

// generated includes
#include <gui/objects/GBenchFeedbackRequest.hpp>
#include <util/compress/zlib.hpp>
#include <util/compress/stream.hpp>
#include <connect/ncbi_conn_stream.hpp>
#include <objects/general/Date.hpp>

// generated classes

BEGIN_NCBI_SCOPE

BEGIN_objects_SCOPE // namespace ncbi::objects::

/////////////////// CGBenchFeedbackRequest inline methods

// constructor
CGBenchFeedbackRequest::CGBenchFeedbackRequest(void)
{
    SetDate().SetToTime(CTime(CTime::eCurrent));
}


// destructor
CGBenchFeedbackRequest::~CGBenchFeedbackRequest(void)
{
}


static void s_Decompress(const vector<char>& data, string& str)
{
    CNcbiIstrstream strstr(&data[0], data.size());
    CZipStreamDecompressor proc(16384, 16384,
                                15 /* window bits */,
                                CZipCompression::fCheckFileHeader);
    CCompressionIStream istr(strstr, &proc);

    char buf[512];
    while ( !istr.fail() ) {
        istr.read(buf, sizeof(buf));
        str.append(buf, istr.gcount());
    }
}


static void s_Compress(CNcbiIstream& istr, vector<char>& data)
{
    CConn_MemoryStream mem_str;
    {{
         CZipStreamCompressor proc(CCompression::eLevel_Best,
                                   16384, 16384,
                                   15 /* window bits */,
                                   9  /* memory bits */,
                                   kZlibDefaultStrategy,
                                   CZipCompression::fWriteGZipFormat);
         CCompressionOStream ostr(mem_str, &proc);

         char buf[512];
         while (istr) {
             istr.read(buf, sizeof(buf));
             ostr.write(buf, istr.gcount());
         }
     }}
    mem_str.flush();

    data.resize(mem_str.tellp() - CT_POS_TYPE(0));
    mem_str.read(&data[0], data.size());
}


void CGBenchFeedbackRequest::DecodeDesc(string& str) const
{
    if (IsSetDesc()) {
        s_Decompress(GetDesc(), str);
    }
}


void CGBenchFeedbackRequest::EncodeDesc(const string& str)
{
    CNcbiIstrstream istr(str.data(), str.size());
    EncodeDesc(istr);
}

void CGBenchFeedbackRequest::EncodeDesc(CNcbiIstream& istr)
{
    s_Compress(istr, SetDesc());
}


void CGBenchFeedbackRequest::EncodeApp_log(const string& str)
{
    CNcbiIstrstream istr(str.data(), str.size());
    EncodeApp_log(istr);
}

void CGBenchFeedbackRequest::EncodeApp_log(CNcbiIstream& istr)
{
    s_Compress(istr, SetApp_log());
}


void CGBenchFeedbackRequest::EncodeSys_config(const string& str)
{
    CNcbiIstrstream istr(str.data(), str.size());
    EncodeSys_config(istr);
}

void CGBenchFeedbackRequest::EncodeSys_config(CNcbiIstream& istr)
{
    s_Compress(istr, SetSys_config());
}


void CGBenchFeedbackRequest::DecodeApp_log(string& str) const
{
    if (IsSetApp_log()) {
        s_Decompress(GetApp_log(), str);
    }
}


void CGBenchFeedbackRequest::DecodeSys_config(string& str) const
{
    if (IsSetSys_config()) {
        s_Decompress(GetSys_config(), str);
    }
}


END_objects_SCOPE // namespace ncbi::objects::

END_NCBI_SCOPE

/* Original file checksum: lines: 65, chars: 1923, CRC32: 6f7c836e */