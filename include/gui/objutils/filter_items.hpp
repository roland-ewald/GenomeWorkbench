#ifndef GUI_OBJUTILS___FILTER_ITEMS__HPP
#define GUI_OBJUTILS___FILTER_ITEMS__HPP

/*  $Id: filter_items.hpp 25534 2012-04-04 19:06:52Z katargir $
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
 * Authors: Roman Katargin
 *
 * File Description:
 *
 */

#include <gui/gui_export.h>

BEGIN_NCBI_SCOPE

class IFilterItems
{
public:
    virtual ~IFilterItems() {}
    virtual void GetItems( const string& pattern, vector<string>& result ) = 0;
};

END_NCBI_SCOPE

#endif  // GUI_OBJUTILS___FILTER_ITEMS__HPP