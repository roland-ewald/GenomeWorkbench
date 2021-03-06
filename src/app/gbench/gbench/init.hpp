#ifndef GUI_GBENCH___INIT__HPP
#define GUI_GBENCH___INIT__HPP

/*  $Id: init.hpp 18666 2009-01-23 19:58:39Z katargir $
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
*  and reliability of the software and data,  the NLM and the U.S.
*  Government do not and cannot warrant the performance or results that
*  may be obtained by using this software or data. The NLM and the U.S.
*  Government disclaim all warranties,  express or implied,  including
*  warranties of performance,  merchantability or fitness for any particular
*  purpose.
*
*  Please cite the author in any work or product based on this material.
*
* ===========================================================================
*
* Authors:  Roman Katargin
*/

#include <corelib/ncbistd.hpp>

//
// This function purpose to make initialization calls for gbench app.
// For example register extensions which otherwise would be initialized
// via static objects (undesirable, as linker may drop file
// with no external referenses).
//

BEGIN_NCBI_SCOPE
bool init_gui_app_gbench();
END_NCBI_SCOPE

#endif  // GUI_GBENCH___INIT__HPP
