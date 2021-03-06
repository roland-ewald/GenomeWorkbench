/*  $Id: sequence_istream_bdb.cpp 414724 2013-09-26 14:44:17Z morgulis $
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
 * Author:  Aleksandr Morgulis
 *
 * File Description:
 *   Implementation file for CSequenceIStreamBlastDB class.
 *
 */

#include <ncbi_pch.hpp>
#include <algorithm>

#ifdef LOCAL_SVN
#include "sequence_istream_bdb.hpp"
#else
#include <algo/blast/dbindex/sequence_istream_bdb.hpp>
#endif

BEGIN_NCBI_SCOPE
BEGIN_SCOPE( blastdbindex )

namespace {

//------------------------------------------------------------------------------
void CheckBlastDBMaskAlgorithmId( CRef< CSeqDB > & db, int id ) {
    std::vector< int > ids;
    db->GetAvailableMaskAlgorithms( ids );

    if( std::find( ids.begin(), ids.end(), id ) == ids.end() ) {
            NCBI_THROW( CSequenceIStream::CSequenceIStream_Exception, eParam,
                    std::string( "unrecognized filter algorithm id" ) + 
                    db->GetAvailableMaskAlgorithmDescriptions() );
    }
}

}

//------------------------------------------------------------------------------
CSequenceIStreamBlastDB::CSequenceIStreamBlastDB( 
        const string & dbname, bool use_filter, int filter_algo_id )
    : seqdb_( new CSeqDB( dbname, CSeqDB::eNucleotide ) ), oid_( 0 ),
      filter_algo_id_( filter_algo_id ), use_filter_( use_filter )
{
    if( use_filter_ ) CheckBlastDBMaskAlgorithmId( seqdb_, filter_algo_id_ );
}

//------------------------------------------------------------------------------
CSequenceIStreamBlastDB::CSequenceIStreamBlastDB( 
        const string & dbname, bool use_filter, 
        string const & filter_algo_name )
    : seqdb_( new CSeqDB( dbname, CSeqDB::eNucleotide ) ), oid_( 0 ),
      filter_algo_id_( 0 ), use_filter_( use_filter )
{
    if( use_filter_ ) {
        try {
            if( NStr::StringToNumeric( 
                        filter_algo_name, &filter_algo_id_, 
                        NStr::fConvErr_NoThrow, 10) ) {
                CheckBlastDBMaskAlgorithmId( seqdb_, filter_algo_id_ );
            }
            else {
                filter_algo_id_ = 
                    seqdb_->GetMaskAlgorithmId( filter_algo_name );
            }
        }
        catch( CSeqDBException & e ) {
            NCBI_RETHROW( 
                    e, CSequenceIStream_Exception, eParam,
                    std::string( "unrecognised filter algorithm name" ) +
                    seqdb_->GetAvailableMaskAlgorithmDescriptions() );
        }
    }
}

//------------------------------------------------------------------------------
CRef< CSequenceIStream::TSeqData > CSequenceIStreamBlastDB::next()
{
    CRef< CSeq_entry > entry( null );
    TSeqData::TMask m;

    if( oid_ < seqdb_->GetNumOIDs() ) {
        CRef< CBioseq > seq = seqdb_->GetBioseq( oid_ );
        entry.Reset( new CSeq_entry );
        entry->SetSeq( *seq );

        if( use_filter_ ) {
            list< CRef< CSeq_id > > ids( seqdb_->GetSeqIDs( oid_ ) );
            CSeqDB::TSequenceRanges r;
            seqdb_->GetMaskData( oid_, filter_algo_id_, r );
            CPacked_seqint::TRanges seqint_ranges;

            for( CSeqDB::TSequenceRanges::const_iterator i( r.begin() );
                    i != r.end(); ++i ) {
                seqint_ranges.push_back( 
                        CRange< TSeqPos >( i->first, i->second - 1 ) );
            }

            CRef< CPacked_seqint > seqint( 
                    new CPacked_seqint( **ids.begin(), seqint_ranges ) );
            CRef< CSeq_loc > sl( new CSeq_loc );
            sl->SetPacked_int( *seqint );
            m.push_back( sl );
        }

        ++oid_;
    }

    CRef< TSeqData > data( new TSeqData );
    data->seq_entry_ = entry;
    if( use_filter_ ) data->mask_locs_ = m;
    return data;
}

//------------------------------------------------------------------------------
void CSequenceIStreamBlastDB::putback()
{ if( oid_ > 0 ) --oid_; }

END_SCOPE( blastdbindex )
END_NCBI_SCOPE

