/*  $Id: update_seq_dlg.hpp 44068 2019-10-18 18:57:05Z asztalos $
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
 * Authors:  Andrea Asztalos
 *
 * File Description:
 *          Dialog for updating a single sequence
 */
// Generated by DialogBlocks (unregistered), 26/01/2015 09:02:45

#ifndef _UPDATE_SEQ_DLG_H_
#define _UPDATE_SEQ_DLG_H_

#include <corelib/ncbistd.hpp>
#include <gui/objutils/reg_settings.hpp>
#include <gui/utils/job_future.hpp>
#include <gui/widgets/wx/dialog.hpp>
#include <wx/hyperlink.h>

BEGIN_NCBI_SCOPE

class CUpdateSeqPanel;
class CUpdateSeq_Input;

/*!
 * Control identifiers
 */

////@begin control identifiers
#define SYMBOL_CUPDATESEQ_DLG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_CUPDATESEQ_DLG_TITLE _("Update Sequence")
#define SYMBOL_CUPDATESEQ_DLG_IDNAME ID_CUPDATESEQ_DLG
#define SYMBOL_CUPDATESEQ_DLG_SIZE wxDefaultSize
#define SYMBOL_CUPDATESEQ_DLG_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * CUpdateSeq_Dlg class declaration
 */

class CUpdateSeq_Dlg : public CDialog
{    
    DECLARE_DYNAMIC_CLASS( CUpdateSeq_Dlg )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    CUpdateSeq_Dlg();
    CUpdateSeq_Dlg( wxWindow* parent, 
        CUpdateSeq_Input& updseq_in,
        wxWindowID id = SYMBOL_CUPDATESEQ_DLG_IDNAME, 
        const wxString& caption = SYMBOL_CUPDATESEQ_DLG_TITLE, 
        const wxPoint& pos = SYMBOL_CUPDATESEQ_DLG_POSITION, 
        const wxSize& size = SYMBOL_CUPDATESEQ_DLG_SIZE, 
        long style = SYMBOL_CUPDATESEQ_DLG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, 
        wxWindowID id = SYMBOL_CUPDATESEQ_DLG_IDNAME, 
        const wxString& caption = SYMBOL_CUPDATESEQ_DLG_TITLE, 
        const wxPoint& pos = SYMBOL_CUPDATESEQ_DLG_POSITION, 
        const wxSize& size = SYMBOL_CUPDATESEQ_DLG_SIZE, 
        long style = SYMBOL_CUPDATESEQ_DLG_STYLE );

    /// Destructor
    ~CUpdateSeq_Dlg();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin CUpdateSeq_Dlg event handler declarations
    
////@end CUpdateSeq_Dlg event handler declarations

////@begin CUpdateSeq_Dlg member function declarations
    void SetData(const SUpdateSeqParams& params);
    SUpdateSeqParams GetData() const;

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end CUpdateSeq_Dlg member function declarations

    void OnIdle(wxIdleEvent& event);
    void OnUpdateSequence(wxCommandEvent& event);

    virtual void x_LoadSettings(const CRegistryReadView& view);
    virtual void x_SaveSettings(CRegistryWriteView view) const;

    /// Should we show tooltips?
    static bool ShowToolTips();

private:
    void x_CalculateAlignment();

    CUpdateSeqPanel* m_UpdSeqPanel;
    CRef<CUpdateSeq_Input> m_UpdSeqInput;

    job_future<CConstRef<objects::CSeq_align> > m_Future;

    enum {
        ID_CUPDATESEQ_DLG = 10300,
    };
};

END_NCBI_SCOPE

#endif
    // _UPDATE_SEQ_DLG_H_