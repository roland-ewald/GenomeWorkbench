#ifndef GUI_OBJUTILS___CMD_CREATE_DESC__HPP
#define GUI_OBJUTILS___CMD_CREATE_DESC__HPP

/*  $Id: cmd_create_desc.hpp 44316 2019-11-27 16:08:06Z filippov $
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

#include <corelib/ncbiobj.hpp>
#include <gui/gui_export.h>

#include <gui/utils/command_processor.hpp>

#include <objmgr/seq_entry_handle.hpp>

BEGIN_NCBI_SCOPE

class NCBI_GUIOBJUTILS_EXPORT CCmdCreateDesc : 
    public CObject, public IEditCommand
{
public:
    CCmdCreateDesc(const objects::CSeq_entry_Handle& seh, const objects::CSeqdesc& descr)
        : m_seh(seh), m_Desc(&descr), m_Failure(false)
    {
    }

    /// @name IEditCommand interface implementation
    /// @{
    virtual void Execute();
    virtual void Unexecute();
    virtual string GetLabel();
    /// @}
    
protected:
    objects::CSeq_entry_Handle m_seh,  m_TopSeqEntry;
    CConstRef<objects::CSeqdesc> m_Desc;
    bool m_Failure;
};

END_NCBI_SCOPE

#endif  // GUI_OBJUTILS___CMD_CREATE_DESC__HPP