#ifndef GUI_FRAMEWORK___PKG_WB_CONNECT__HPP
#define GUI_FRAMEWORK___PKG_WB_CONNECT__HPP

/*  $Id: pkg_wb_connect.hpp 27360 2013-02-01 16:39:16Z filippov $
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
 * Authors:  Igor Filippov
 *
 * File Description:
 *
 */

/** @addtogroup GUI_FRAMEWORK
*
* @{
*/

#include <corelib/ncbistd.hpp>
#include <gui/framework/workbench.hpp>

BEGIN_NCBI_SCOPE

#ifdef NCBI_OS_MSWIN
#  define NCBI_PACKAGEENTRYPOINT_EXPORT __declspec(dllexport)
#else
#  define NCBI_PACKAGEENTRYPOINT_EXPORT
#endif


class IPackageWorkbenchConnector
{
public:
    virtual ~IPackageWorkbenchConnector() {}
    virtual void SetWorkbench(IWorkbench* wb) = 0;
};

END_NCBI_SCOPE

/* @} */

#endif // GUI_FRAMEWORK___PKG_WB_CONNECT__HPP