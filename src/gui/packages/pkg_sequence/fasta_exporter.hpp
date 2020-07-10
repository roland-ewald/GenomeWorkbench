#ifndef PKG_SEQUENCE___FASTA_EXPORTER__HPP
#define PKG_SEQUENCE___FASTA_EXPORTER__HPP

/*  $Id: fasta_exporter.hpp 20361 2009-11-12 19:12:19Z katargir $
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

#include <corelib/ncbistd.hpp>

#include <gui/utils/extension.hpp>
#include <gui/core/ui_export_tool.hpp>

BEGIN_NCBI_SCOPE

class CFastaExporterFactory :
    public CObject,
    public IExtension,
    public IExporterFactory
{
public:
    /// @name IExtension interface implementation
    /// @{
    virtual string  GetExtensionIdentifier() const;
    virtual string  GetExtensionLabel() const;
    /// @}

    /// @name IExporterFactory interface implementation
    /// @{
    virtual IUIExportTool*  CreateInstance() const;
    virtual bool TestInputObjects(TConstScopedObjects& objects) const;
    /// @}
};

END_NCBI_SCOPE

#endif  // PKG_SEQUENCE___FASTA_EXPORTER__HPP