/*  $Id: asn_styles.cpp 24438 2011-09-22 16:24:17Z katargir $
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
 * Authors:  Roman Katargin
 *
 * File Description:
 *
 */

#include <ncbi_pch.hpp>

#include "asn_styles.hpp"

BEGIN_NCBI_SCOPE

vector<CTextStyle> CAsnStyles::m_Styles;

const CTextStyle& CAsnStyles::GetStyle(Element element)
{
    static CAsnStyles instance;
    return m_Styles[element];
}

CAsnStyles::CAsnStyles()
{
    m_Styles.push_back(CTextStyle(0,0,139,     255,255,255,wxTRANSPARENT,false,true));  // kHeader1
    m_Styles.push_back(CTextStyle(255,0,255,   255,255,255,wxTRANSPARENT,true,false));  // kHeader2
    m_Styles.push_back(CTextStyle(0,100,0,     255,255,255,wxTRANSPARENT,false,false)); // kBraces
    m_Styles.push_back(CTextStyle(0,0,0,       255,255,255,wxTRANSPARENT,false,false)); // kMember
    m_Styles.push_back(CTextStyle(0,0,0,       255,255,255,wxTRANSPARENT,true,true));   // kChoice
    m_Styles.push_back(CTextStyle(139,0,0,     255,255,255,wxTRANSPARENT,true,false));  // kTextValue
    m_Styles.push_back(CTextStyle(0,0,139,     255,255,255,wxTRANSPARENT,true,false));  // kNumberValue
    m_Styles.push_back(CTextStyle(0,0,139,     255,255,255,wxTRANSPARENT,true,false));  // kNullValue
    m_Styles.push_back(CTextStyle(128,128,128, 255,255,255,wxTRANSPARENT,false,false)); // kCollapsedBlock
    m_Styles.push_back(CTextStyle(128,128,128, 255,255,255,wxTRANSPARENT,false,false)); // kComment
    m_Styles.push_back(CTextStyle(255,0,0,     255,255,255,wxSOLID,true,false));        // kError
    m_Styles.push_back(CTextStyle(255,0,0,     255,255,255,wxSOLID,true,false));        // kFakeInfo
}

END_NCBI_SCOPE