#ifndef GUI_UTILS___FETCH_URL__HPP
#define GUI_UTILS___FETCH_URL__HPP

/*  $Id: fetch_url.hpp 30183 2014-04-11 19:08:25Z kuznets $
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
 * Authors:  Josh Cherry
 *
 * File Description:  fetch data from the net using http
 *
 */

/** @addtogroup GUI_UTILS
*
* @{
*/

#include <corelib/ncbistd.hpp>
#include <gui/gui.hpp>
#include <connect/ncbi_types.h>



BEGIN_NCBI_SCOPE

class NCBI_GUIUTILS_EXPORT CFetchURL
{
public:
    /// Fetch a URL from the net using http GET
    ///
    /// @param is_cache - use local cache to accelarate the retrieval
    static void Fetch(const string& url,
                      string& result,
                      const STimeout* timeout = kDefaultTimeout,
                      bool is_cache = false);
};

END_NCBI_SCOPE

/* @} */

#endif  // GUI_UTILS___FETCH_URL__HPP