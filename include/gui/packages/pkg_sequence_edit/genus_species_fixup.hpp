/*  $Id: genus_species_fixup.hpp 42425 2019-02-21 15:31:49Z asztalos $
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
 * Authors:  Igor Filippov
 */
#ifndef _GENUS_SPECIES_FIXUP_H_
#define _GENUS_SPECIES_FIXUP_H_

#include <corelib/ncbistd.hpp>
#include <gui/packages/pkg_sequence_edit/modify_bsrc_interface.hpp>


BEGIN_NCBI_SCOPE

class CGenusSpeciesFixup : public IModifyBiosourceQuals
{
public:
    CRef<CCmdComposite> GetCommand(objects::CSeq_entry_Handle tse);
private:
    virtual bool x_ApplyToBioSource(objects::CBioSource& biosource);
    static void s_GetNameFromTaxonServer(CRef<objects::COrg_ref> org);
    static bool s_HasTaxId(const objects::CBioSource&);
    static void s_PermuteTaxname(const string &name, vector<string> &submit);
    
};

END_NCBI_SCOPE

#endif
    // _GENUS_SPECIES_FIXUP_H_
