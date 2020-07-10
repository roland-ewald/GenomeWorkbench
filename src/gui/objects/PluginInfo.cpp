/* $Id: PluginInfo.cpp 14666 2007-07-09 13:40:22Z dicuccio $
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
 * File Description:
 *   .......
 *
 * Remark:
 *   This code was originally generated by application DATATOOL
 *   using specifications from the data definition file
 *   'plugin.asn'.
 */

// standard includes

// generated includes
#include <ncbi_pch.hpp>

#include <gui/objects/PluginInfo.hpp>
#include <gui/objects/PluginUserType.hpp>

// generated classes

BEGIN_NCBI_SCOPE

BEGIN_objects_SCOPE // namespace ncbi::objects::

// destructor
CPluginInfo::~CPluginInfo(void)
{
}


// set the standard plugin boilerplate fields
void CPluginInfo::SetInfo(int major, int minor, int rev,
                          const string& build_date,
                          const string& class_name,
                          const string& menu_item,
                          const string& tooltip,
                          const string& help_file)
{
    // required items
    SetVer_major     (major);
    SetVer_minor     (minor);
    SetVer_revision  (rev);
    SetVer_build_date(build_date);
    SetClass_name    (class_name);

    // optional items
    if ( !menu_item.empty() ) {
        SetMenu_item(menu_item);
    }

    if ( !tooltip.empty() ) {
        SetTooltip(tooltip);
    }

    if ( !help_file.empty() ) {
        SetHelp_file(help_file);
    }
}


void CPluginInfo::SetInfo(int major, int minor, int rev,
                          const string& build_date,
                          const string& class_name,
                          const string& menu_item,
                          const string& tooltip,
                          const string& help_file,
                          const string& icon_alias,
                          const string& icon_local_path)

{
    SetInfo(major, minor, rev, build_date, class_name, menu_item, tooltip, help_file);
    SetIcon_info().SetAlias(icon_alias);
    SetIcon_info().SetPath(icon_local_path);
}


CPluginCommand& CPluginInfo::SetAlgoCommand(CPluginCommand::TCommand cmd)
{
    CPluginCommand& algo = SetCommand();
    algo.SetCommand(cmd);
    return algo;
}


CPluginCommand& CPluginInfo::SetViewCommand(CPluginCommand::TCommand cmd)
{
    CPluginCommand& view = SetCommand();
    view.SetCommand(cmd);

    /// force all view-related commands to run in the foreground by default
    SetAffinity(eAffinity_foreground);

    return view;
}


CPluginCommand& CPluginInfo::SetDataCommand(CPluginCommand::TCommand cmd)
{
    CPluginCommand& data = SetCommand();
    data.SetCommand(cmd);
    return data;
}


void CPluginInfo::AddApplicableUserType(const string& type, const string& subtype)
{
    CRef<CPluginUserType> ref(new CPluginUserType());
    ref->SetType(type);
    ref->SetSubtype(subtype);
    SetApplicable_user_types().push_back(ref);
}


END_objects_SCOPE // namespace ncbi::objects::

END_NCBI_SCOPE

/* Original file checksum: lines: 64, chars: 1880, CRC32: 17968bbc */