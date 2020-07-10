/*  $Id: align_tab_export_params.cpp 39666 2017-10-25 16:01:13Z katargir $
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

#include <ncbi_pch.hpp>

#include <gui/objutils/registry.hpp>

#include <gui/widgets/wx/wx_utils.hpp>

#include <gui/packages/pkg_alignment/align_tab_export_params.hpp>

BEGIN_NCBI_SCOPE

CAlignTabExportParams::CAlignTabExportParams()
{
    Init();
}
CAlignTabExportParams::CAlignTabExportParams(const CAlignTabExportParams& data)
{
    Init();
    Copy(data);
}
CAlignTabExportParams::~CAlignTabExportParams()
{
}
void CAlignTabExportParams::operator=(const CAlignTabExportParams& data)
{
    Copy(data);
}
bool CAlignTabExportParams::operator==(const CAlignTabExportParams& data) const
{
////@begin CAlignTabExportParams equality operator
     if (!(m_AlignmentName == data.m_AlignmentName)) return false;
     if (!(m_Fields == data.m_Fields)) return false;
     if (!(m_FileName == data.m_FileName)) return false;
////@end CAlignTabExportParams equality operator
    return true;
}
void CAlignTabExportParams::Copy(const CAlignTabExportParams& data)
{
////@begin CAlignTabExportParams copy function
    m_AlignmentName = data.m_AlignmentName;
    m_Fields = data.m_Fields;
    m_FileName = data.m_FileName;
////@end CAlignTabExportParams copy function
    m_Object = data.m_Object;
}
void CAlignTabExportParams::Init()
{
////@begin CAlignTabExportParams member initialisation
////@end CAlignTabExportParams member initialisation
}

static const char* kFileName      = "FileName";
static const char* kAlignmentName = "AlignmentName";
static const char* kFields        = "Fields";

/// IRegSettings
void CAlignTabExportParams::SaveSettings() const
{
    if (!m_RegPath.empty()) {
        CGuiRegistry& gui_reg = CGuiRegistry::GetInstance();
        CRegistryWriteView view = gui_reg.GetWriteView(m_RegPath);
        view.Set(kFileName, FnToStdString( m_FileName ));
        view.Set(kAlignmentName, m_AlignmentName);
        view.Set(kFields, m_Fields);
    }
}

void CAlignTabExportParams::LoadSettings()
{
    if (!m_RegPath.empty()) {
        CGuiRegistry& gui_reg = CGuiRegistry::GetInstance();
        CRegistryReadView view = gui_reg.GetReadView(m_RegPath);
        m_FileName = FnToWxString(view.GetString(kFileName, FnToStdString(m_FileName)));
        m_AlignmentName = view.GetString(kAlignmentName, m_AlignmentName);
        view.GetStringVec(kFields, m_Fields);
    }
}

END_NCBI_SCOPE