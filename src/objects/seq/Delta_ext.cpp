/* $Id: Delta_ext.cpp 513588 2016-09-13 13:46:29Z ivanov $
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
 *   using the following specifications:
 *   'seq.asn'.
 */

// standard includes
#include <ncbi_pch.hpp>

// generated includes
#include <objects/seq/Delta_ext.hpp>

#include <util/sequtil/sequtil_convert.hpp>
#include <util/sequtil/sequtil_expt.hpp>
#include <objects/seq/Delta_seq.hpp>
#include <objects/seq/Seq_literal.hpp>
#include <objects/seq/Seq_data.hpp>
#include <objects/seq/IUPACaa.hpp>
#include <objects/seq/IUPACna.hpp>
#include <objects/seq/NCBI2na.hpp>
#include <objects/seq/NCBI4na.hpp>
#include <objects/seq/NCBI8na.hpp>
#include <objects/seq/seqport_util.hpp>

// generated classes

BEGIN_NCBI_SCOPE

BEGIN_objects_SCOPE // namespace ncbi::objects::

// destructor
CDelta_ext::~CDelta_ext(void)
{
}


/// add a literal segment at the end
/// this variant adds a gap literal
CDelta_seq& CDelta_ext::AddLiteral(TSeqPos len)
{
    if ( !Get().empty()  &&  Get().back()->IsLiteral()
        &&  !Get().back()->GetLiteral().IsSetSeq_data()
        &&  !Get().back()->GetLiteral().IsSetFuzz()) {
        // merge adjacent plain gaps
        Set().back()->SetLiteral().SetLength() += len;
        return *Set().back();
    }

    CRef<CDelta_seq> seg(new CDelta_seq());
    seg->SetLiteral().SetLength(len);

    Set().push_back(seg);
    return *seg;
}


/// add a literal segment at the end
/// this variant adds a non-gap literal
CDelta_seq& CDelta_ext::AddLiteral(const CTempString& iupac_seq,
                                   CSeq_inst::EMol mol, bool do_pack)
{
    CRef<CDelta_seq> seg(new CDelta_seq());
    seg->SetLiteral().SetLength((CSeq_literal::TLength)iupac_seq.size());

    switch (mol) {
    case CSeq_inst::eMol_aa:
        seg->SetLiteral().SetSeq_data().SetIupacaa().Set().assign(iupac_seq.data(), iupac_seq.length());
        break;

    case CSeq_inst::eMol_na:
    case CSeq_inst::eMol_dna:
    case CSeq_inst::eMol_rna:
        seg->SetLiteral().SetSeq_data().SetIupacna().Set().assign(iupac_seq.data(), iupac_seq.length());
        if (do_pack)
            CSeqportUtil::Pack(&seg->SetLiteral().SetSeq_data());
        break;

    default:
        NCBI_THROW(CException, eUnknown,
                   "CDelta_ext::AddLiteral(): unhandled mol type");
        break;
    }

    Set().push_back(seg);
    return *seg;
}


class CDelta_ext_PackTarget : public CSeqConvert::IPackTarget
{
public:
    CDelta_ext_PackTarget(CDelta_ext& obj, bool gaps_ok)
        : m_Obj(obj), m_GapsOK(gaps_ok)
        { }

    // Rough memory overhead per segment, in bytes.  The actual values
    // are system specific, but this code's behavior shouldn't be.
    SIZE_TYPE GetOverhead(TCoding coding) const
        { return coding == CSeqUtil::e_not_set ? 96 : 128; }
    
    virtual bool GapsOK(TCodingType) const { return m_GapsOK; }

    char* NewSegment(TCoding coding, TSeqPos length);

private:
    CDelta_ext& m_Obj;
    bool        m_GapsOK;
};


char* CDelta_ext_PackTarget::NewSegment(CSeqUtil::TCoding coding,
                                        TSeqPos length)
{
    CRef<CDelta_seq> ds(new CDelta_seq);
    CSeq_literal&    lit = ds->SetLiteral();
    lit.SetLength(length);
    m_Obj.Set().push_back(ds);

    switch (coding) {
    case CSeqUtil::e_not_set:
        return NULL;

#define CODING_CASE_EX(key, type, setter, len) \
    case CSeqUtil::key: \
    { \
        type& dest = lit.SetSeq_data().setter(); \
        dest.Set().resize(len); \
        return &dest.Set()[0]; \
    }
#define CODING_CASE(name, type) \
    CODING_CASE_EX(e_##name, type, Set##name, length)

    CODING_CASE_EX(e_Ncbi2na, CNCBI2na, SetNcbi2na, (length + 3) / 4)
    CODING_CASE_EX(e_Ncbi4na, CNCBI4na, SetNcbi4na, (length + 1) / 2)

    // case CSeqUtil::e_Ncbi4na_expand:
    // CODING_CASE(Ncbi8na, CNCBI8na)

    CODING_CASE(Iupacaa,   CIUPACaa)
    CODING_CASE(Ncbi8aa,   CNCBI8aa)
    CODING_CASE(Ncbieaa,   CNCBIeaa)
    CODING_CASE(Ncbistdaa, CNCBIstdaa)
#undef CODING_CASE
#undef CODING_CASE_EX

    default:
        NCBI_THROW(CSeqUtilException, eInvalidCoding,
                   "CDelta_ext_PackTarget: unexpected coding");
    }        
}


void CDelta_ext::AddAndSplit(const CTempString& src, CSeq_data::E_Choice in_format,
                             TSeqPos length /* in residues */, 
                             bool gaps_ok, bool allow_packing)
{
    CSeqUtil::TCoding coding = CSeqUtil::e_not_set;

    switch (in_format) {
    case CSeq_data::e_Iupacna:    coding = CSeqUtil::e_Iupacna;     break;
    case CSeq_data::e_Iupacaa:    coding = CSeqUtil::e_Iupacaa;     break;
    case CSeq_data::e_Ncbi4na:    coding = CSeqUtil::e_Ncbi4na;     break;
    case CSeq_data::e_Ncbi8na:    coding = CSeqUtil::e_Ncbi8na;     break;
    case CSeq_data::e_Ncbi8aa:    coding = CSeqUtil::e_Ncbi8aa;     break;
    case CSeq_data::e_Ncbieaa:    coding = CSeqUtil::e_Ncbieaa;     break;
    case CSeq_data::e_Ncbistdaa:  coding = CSeqUtil::e_Ncbistdaa;   break;
    default:
        coding = CSeqUtil::e_not_set;
    }

    if (allow_packing)
    {
        CDelta_ext_PackTarget dst(*this, gaps_ok);
        CSeqConvert::Pack(src.data(), length, coding, dst);
    }
    else
    {
        // add as a single piece
        CRef<CSeq_data>  data (new CSeq_data(src, in_format));
        CRef<CDelta_seq> ds   (new CDelta_seq);
        CSeq_literal&    lit = ds->SetLiteral();
        lit.SetLength(length);
        lit.SetSeq_data(*data);
        Set().push_back(ds);
    }
}

/// add a segment that refers to another segment
CDelta_seq& CDelta_ext::AddSeqRange(const CSeq_id& id,
                                    TSeqPos from, TSeqPos to,
                                    ENa_strand strand)
{
    CRef<CDelta_seq> seg(new CDelta_seq());
    seg->SetLoc().SetInt().SetFrom(from);
    seg->SetLoc().SetInt().SetTo  (to);
    seg->SetLoc().SetId(id);
    seg->SetLoc().SetStrand(strand);

    Set().push_back(seg);
    return *seg;
}


END_objects_SCOPE // namespace ncbi::objects::

END_NCBI_SCOPE

/* Original file checksum: lines: 65, chars: 1883, CRC32: 149e396a */