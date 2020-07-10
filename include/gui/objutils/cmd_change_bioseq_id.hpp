#ifndef GUI_OBJUTILS___CMD_CHANGE_BIOSEQ_ID__HPP
#define GUI_OBJUTILS___CMD_CHANGE_BIOSEQ_ID__HPP

/*  $Id: cmd_change_bioseq_id.hpp 36303 2016-09-09 19:46:21Z filippov $
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

#include <corelib/ncbiobj.hpp>
#include <gui/gui_export.h>

#include <gui/utils/command_processor.hpp>
#include <objects/seq/seq_id_handle.hpp>
#include <objmgr/bioseq_handle.hpp>

BEGIN_NCBI_SCOPE

class NCBI_GUIOBJUTILS_EXPORT CCmdChangeBioseqId : 
    public CObject, public IEditCommand
{
public:
    CCmdChangeBioseqId(const objects::CBioseq_Handle& bh, const objects::CSeq_id& old_id, const objects::CSeq_id& new_id);

    /// @name IEditCommand interface implementation
    /// @{
    virtual void Execute();
    virtual void Unexecute();
    virtual string GetLabel();
    /// @}

protected:
    objects::CBioseq_Handle m_BH;
    objects::CSeq_id_Handle m_old_idh;
    objects::CSeq_id_Handle m_new_idh;
};

END_NCBI_SCOPE

#endif  // GUI_OBJUTILS___CMD_CHANGE_BIOSEQ_ID__HPP