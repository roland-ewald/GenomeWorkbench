/*  $Id: external_layout_track.cpp 23901 2011-06-20 20:23:37Z wuliangs $
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
 * Authors:  Liangshou Wu
 *
 * File Description:
 *
 */

#include <ncbi_pch.hpp>

#include <gui/widgets/seq_graphic/external_layout_track.hpp>
#include <gui/widgets/seq_graphic/rendering_ctx.hpp>


BEGIN_NCBI_SCOPE
USING_SCOPE(objects);

///////////////////////////////////////////////////////////////////////////////
///   CExternalLayoutTrack
///////////////////////////////////////////////////////////////////////////////

CTrackTypeInfo CExternalLayoutTrack::m_TypeInfo("external_layout_track",
                                                "Graphical View External Layout Track");

CExternalLayoutTrack::CExternalLayoutTrack(CRenderingContext* r_cntx)
    : CGlyphContainer(r_cntx)
{
    TTrackAttrFlags attr = fShowAlways | fFullTrack;
    SetTrackAttr(attr);
    SetLayoutPolicy(m_Layered);
    m_Layered->SetTopMargin(0);
}


const CTrackTypeInfo&  CExternalLayoutTrack::GetTypeInfo() const
{
    return m_TypeInfo;
}


///////////////////////////////////////////////////////////////////////////////
/// CExternalLayoutTrackFactory
///////////////////////////////////////////////////////////////////////////////
ILayoutTrackFactory::TTrackMap
CExternalLayoutTrackFactory::CreateTracks(SConstScopedObject& /*object*/,
                                          ISGDataSourceContext* /*ds_context*/,
                                          CRenderingContext* r_cntx,
                                          const SExtraParams& /*params*/,
                                          const TAnnotMetaDataList& /*src_annots*/) const
{
    TTrackMap tracks;
    tracks["External layout"] =
        CRef<CLayoutTrack>(new CExternalLayoutTrack(r_cntx));
    return tracks;
}

string CExternalLayoutTrackFactory::GetExtensionIdentifier() const
{
    return CExternalLayoutTrack::m_TypeInfo.GetId();
}

string CExternalLayoutTrackFactory::GetExtensionLabel() const
{
    return CExternalLayoutTrack::m_TypeInfo.GetDescr();
}

END_NCBI_SCOPE