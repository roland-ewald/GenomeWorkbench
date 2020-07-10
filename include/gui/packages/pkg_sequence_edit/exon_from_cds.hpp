/*  $Id: exon_from_cds.hpp 39649 2017-10-24 15:22:12Z asztalos $
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
#ifndef _EXON_FROM_CDS_H_
#define _EXON_FROM_CDS_H_

#include <corelib/ncbistd.hpp>
#include <objmgr/seq_entry_handle.hpp>
#include <gui/packages/pkg_sequence_edit/bulk_cmd_dlg.hpp>
#include <gui/widgets/edit/feature_type_panel.hpp>
#include <gui/packages/pkg_sequence_edit/edit_feat_loc_panel.hpp>
#include <gui/packages/pkg_sequence_edit/ok_cancel_panel.hpp>
#include <objtools/edit/loc_edit.hpp>
#include <gui/packages/pkg_sequence_edit/miscedit_util.hpp>

#include <gui/packages/pkg_sequence_edit/string_constraint_panel.hpp>
#include <gui/packages/pkg_sequence_edit/field_choice_panel.hpp>
#include <gui/widgets/edit/feature_field_name_panel.hpp>
#include <gui/packages/pkg_sequence_edit/cap_change_panel.hpp>

/*!
 * Includes
 */

////@begin includes
////@end includes

#include <wx/sizer.h>
#include <wx/radiobut.h>
#include <wx/choice.h>

/*!
 * Forward declarations
 */

////@begin forward declarations
class CFeatureTypePanel;
class wxBoxSizer;
class CFieldConstraintPanel;
class COkCancelPanel;
////@end forward declarations

BEGIN_NCBI_SCOPE

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_CEXONFROMCDS wxID_ANY
#define SYMBOL_CEXONFROMCDS_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_CEXONFROMCDS_TITLE _("Exon From CDS")
#define SYMBOL_CEXONFROMCDS_IDNAME ID_CEXONFROMCDS
#define SYMBOL_CEXONFROMCDS_SIZE wxSize(900, 500)
#define SYMBOL_CEXONFROMCDS_POSITION wxDefaultPosition
////@end control identifiers



class CExonFromCds: public CBulkCmdDlg 
{    
    DECLARE_DYNAMIC_CLASS( CExonFromCds )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    CExonFromCds();
    CExonFromCds( wxWindow* parent, IWorkbench* wb, CSeqFeatData::ESubtype subtype, const string &title, wxWindowID id = SYMBOL_CEXONFROMCDS_IDNAME, const wxString& caption = SYMBOL_CEXONFROMCDS_TITLE, const wxPoint& pos = SYMBOL_CEXONFROMCDS_POSITION, const wxSize& size = SYMBOL_CEXONFROMCDS_SIZE, long style = SYMBOL_CEXONFROMCDS_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_CEXONFROMCDS_IDNAME, const wxString& caption = SYMBOL_CEXONFROMCDS_TITLE, const wxPoint& pos = SYMBOL_CEXONFROMCDS_POSITION, const wxSize& size = SYMBOL_CEXONFROMCDS_SIZE, long style = SYMBOL_CEXONFROMCDS_STYLE );

    /// Destructor
    ~CExonFromCds();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

     void ProcessUpdateFeatEvent( wxCommandEvent& event );


    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );

    /// Should we show tooltips?
    static bool ShowToolTips();

    virtual CRef<CCmdComposite> GetCommand();
    virtual string GetErrorMessage();

private:
    void AddIntron( CSeq_entry_Handle seh, CRef<CCmdComposite> cmd, int intron_start, int intron_stop, bool intron_fuzz_start, bool intron_fuzz_stop, CRef<CSeq_id> id, TSeqPos seq_length, int exon_number, bool minus_strand);

    string m_ErrorMessage;
    CStringConstraintPanel* m_StringConstraintPanel;
    COkCancelPanel* m_OkCancel;
    wxCheckBox* m_Introns;
    wxTextCtrl * m_Number;
    int m_ExonNum;
    CFieldChoicePanel *m_FieldType;
    CSeqFeatData::ESubtype m_Type;
    string m_Title;
};

END_NCBI_SCOPE

#endif
