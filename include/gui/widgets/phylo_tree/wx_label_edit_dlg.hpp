/*  $Id: wx_label_edit_dlg.hpp 30858 2014-07-31 14:05:43Z ucko $
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
 * Authors:  Vladimir Tereshkov
 *
 * File Description:
 *
 */
#ifndef _WX_LABEL_EDIT_DLG_H_
#define _WX_LABEL_EDIT_DLG_H_


#include <gui/widgets/phylo_tree/phylo_tree.hpp>
#include <gui/widgets/phylo_tree/phylo_tree_ds.hpp>
#include <gui/widgets/wx/wx_utils.hpp>

#include <corelib/ncbistl.hpp>

// This header must (at least indirectly) precede any wxWidgets headers.
#include <gui/widgets/wx/fixed_base.hpp>

#include <wx/dialog.h>
#include "wx/valgen.h"
#include "wx/valtext.h"
#include "wx/statline.h"
#include "wx/textctrl.h"


/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

BEGIN_NCBI_SCOPE

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_CWXLABELEDITDLG 10018
#define ID_TEXTCTRL16 10020
#define SYMBOL_CWXLABELEDITDLG_STYLE wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_CWXLABELEDITDLG_TITLE wxT("Edit Label")
#define SYMBOL_CWXLABELEDITDLG_IDNAME ID_CWXLABELEDITDLG
#define SYMBOL_CWXLABELEDITDLG_SIZE wxSize(400, 300)
#define SYMBOL_CWXLABELEDITDLG_POSITION wxDefaultPosition
////@end control identifiers

/*!
 * CwxLabelEditDlg class declaration
 */

class CwxLabelEditDlg: public wxDialog
{
    DECLARE_DYNAMIC_CLASS( CwxLabelEditDlg )
    DECLARE_EVENT_TABLE()

public:
    CwxLabelEditDlg();
    CwxLabelEditDlg( wxWindow* parent, wxWindowID id = SYMBOL_CWXLABELEDITDLG_IDNAME, const wxString& caption = SYMBOL_CWXLABELEDITDLG_TITLE, const wxPoint& pos = SYMBOL_CWXLABELEDITDLG_POSITION, const wxSize& size = SYMBOL_CWXLABELEDITDLG_SIZE, long style = SYMBOL_CWXLABELEDITDLG_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_CWXLABELEDITDLG_IDNAME, const wxString& caption = SYMBOL_CWXLABELEDITDLG_TITLE, const wxPoint& pos = SYMBOL_CWXLABELEDITDLG_POSITION, const wxSize& size = SYMBOL_CWXLABELEDITDLG_SIZE, long style = SYMBOL_CWXLABELEDITDLG_STYLE );

    ~CwxLabelEditDlg();

    void Init();

    void CreateControls();

    void SetParams(CPhyloTree* tree,
                   CPhyloTree::TTreeIdx node_idx);

    string GetUpdatedLabel() const { return ToStdString(m_Label); }

////@begin CwxLabelEditDlg event handler declarations

    void OnOkClick( wxCommandEvent& event );

////@end CwxLabelEditDlg event handler declarations

////@begin CwxLabelEditDlg member function declarations

    wxString GetNodeLabel() const { return m_Label ; }
    void SetNodeLabel(wxString value) { m_Label = value ; }

    wxBitmap GetBitmapResource( const wxString& name );

    wxIcon GetIconResource( const wxString& name );
////@end CwxLabelEditDlg member function declarations

    static bool ShowToolTips();

////@begin CwxLabelEditDlg member variables
    wxString m_Label;
////@end CwxLabelEditDlg member variables

protected:
    CPhyloTree* m_Tree;
    CPhyloTree::TTreeIdx m_NodeIdx;
};

END_NCBI_SCOPE

#endif
    // _WX_LABEL_EDIT_DLG_H_