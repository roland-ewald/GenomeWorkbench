/*  $Id: cleanup_alignments_params_panel.cpp 39666 2017-10-25 16:01:13Z katargir $
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
 * Authors: Andrey Yazhuk
 *
 * File Description:
 *
 */

// Generated by DialogBlocks (unregistered), 18/07/2008 15:31:02

#include <ncbi_pch.hpp>////@begin includes
////@end includes

#include <gui/packages/pkg_alignment/cleanup_alignments_params_panel.hpp>
#include <gui/widgets/wx/wx_utils.hpp>

#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>

BEGIN_NCBI_SCOPE


SCleanupAlignmentsParams::SCleanupAlignmentsParams()
{
    Init();
}

void SCleanupAlignmentsParams::Init()
{
    m_Algo = eAlignmentManager;
    m_HitFilter_MinLength = 100;
    m_HitFilter_MinIdentity = 0.85f;
    m_AlnMgr_PreserveRows = false;
    m_AlnMgr_Transloc = false;
    m_AlnMgr_Sort = true;
    m_AlnMgr_FillUnaligned = false;
}

void SCleanupAlignmentsParams::SetRegistryPath(const string& WXUNUSED(reg_path))
{
}

void SCleanupAlignmentsParams::LoadSettings()
{

}

void SCleanupAlignmentsParams::SaveSettings() const
{

}


/////////////////////////////////////////////////////////////////////////////



IMPLEMENT_DYNAMIC_CLASS( CCleanupAlignmentsParamsPanel, CAlgoToolManagerParamsPanel )

BEGIN_EVENT_TABLE( CCleanupAlignmentsParamsPanel, CAlgoToolManagerParamsPanel )

////@begin CCleanupAlignmentsParamsPanel event table entries
    EVT_COMBOBOX( ID_COMBOBOX, CCleanupAlignmentsParamsPanel::OnComboboxSelected )

////@end CCleanupAlignmentsParamsPanel event table entries

END_EVENT_TABLE()

CCleanupAlignmentsParamsPanel::CCleanupAlignmentsParamsPanel()
    : m_Params(NULL)
    , m_InputObjects(NULL)
    , m_InputListDirty(true)
{
    Init();
}

CCleanupAlignmentsParamsPanel::CCleanupAlignmentsParamsPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, pos, size, style);
}

bool CCleanupAlignmentsParamsPanel::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
////@begin CCleanupAlignmentsParamsPanel creation
    CAlgoToolManagerParamsPanel::Create( parent, id, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end CCleanupAlignmentsParamsPanel creation
    return true;
}

CCleanupAlignmentsParamsPanel::~CCleanupAlignmentsParamsPanel()
{
////@begin CCleanupAlignmentsParamsPanel destruction
////@end CCleanupAlignmentsParamsPanel destruction
}

void CCleanupAlignmentsParamsPanel::Init()
{
////@begin CCleanupAlignmentsParamsPanel member initialisation
    m_ObjectList = NULL;
    m_AlgoSelector = NULL;
    m_ParamsPanel = NULL;
    m_HitFilter_MinIdentity = NULL;
    m_HitFilter_MinLength = NULL;
    m_AlnMgr_Transloc = NULL;
    m_AlnMgr_Sort = NULL;
    m_AlnMgr_PreserveRows = NULL;
    m_AlnMgr_FillUnaligned = NULL;
////@end CCleanupAlignmentsParamsPanel member initialisation
}

void CCleanupAlignmentsParamsPanel::CreateControls()
{
////@begin CCleanupAlignmentsParamsPanel content construction
    CCleanupAlignmentsParamsPanel* itemCAlgoToolManagerParamsPanel1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemCAlgoToolManagerParamsPanel1->SetSizer(itemBoxSizer2);

    wxStaticBox* itemStaticBoxSizer3Static = new wxStaticBox(itemCAlgoToolManagerParamsPanel1, wxID_ANY, _("Choose a set of alignments"));
    wxStaticBoxSizer* itemStaticBoxSizer3 = new wxStaticBoxSizer(itemStaticBoxSizer3Static, wxVERTICAL);
    itemBoxSizer2->Add(itemStaticBoxSizer3, 1, wxGROW|wxALL, 5);

    m_ObjectList = new CObjectListWidget( itemStaticBoxSizer3->GetStaticBox(), ID_LISTCTRL2, wxDefaultPosition, wxSize(100, 200), wxLC_REPORT );
    itemStaticBoxSizer3->Add(m_ObjectList, 1, wxGROW|wxALL, 5);

    wxArrayString m_AlgoSelectorStrings;
    m_AlgoSelectorStrings.Add(_("Alignment Manager"));
    m_AlgoSelectorStrings.Add(_("Hit Filter"));
    m_AlgoSelector = new wxComboBox( itemCAlgoToolManagerParamsPanel1, ID_COMBOBOX, _("Alignment Manager"), wxDefaultPosition, wxDefaultSize, m_AlgoSelectorStrings, wxCB_READONLY|wxCB_SORT );
    m_AlgoSelector->SetStringSelection(_("Alignment Manager"));
    itemBoxSizer2->Add(m_AlgoSelector, 0, wxGROW|wxALL, 5);

    m_ParamsPanel = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer2->Add(m_ParamsPanel, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer7 = new wxBoxSizer(wxVERTICAL);
    m_ParamsPanel->Add(itemBoxSizer7, 0, wxGROW|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer8 = new wxFlexGridSizer(0, 2, 0, 0);
    itemBoxSizer7->Add(itemFlexGridSizer8, 0, wxALIGN_RIGHT|wxALL, 0);

    wxStaticText* itemStaticText9 = new wxStaticText( itemCAlgoToolManagerParamsPanel1, wxID_STATIC, _("Minimum alignment identity"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer8->Add(itemStaticText9, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_HitFilter_MinIdentity = new wxTextCtrl( itemCAlgoToolManagerParamsPanel1, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer8->Add(m_HitFilter_MinIdentity, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer11 = new wxFlexGridSizer(0, 2, 0, 0);
    itemBoxSizer7->Add(itemFlexGridSizer11, 0, wxALIGN_RIGHT|wxALL, 0);

    wxStaticText* itemStaticText12 = new wxStaticText( itemCAlgoToolManagerParamsPanel1, wxID_STATIC, _("Minimum alignment length"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer11->Add(itemStaticText12, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_HitFilter_MinLength = new wxTextCtrl( itemCAlgoToolManagerParamsPanel1, ID_TEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer11->Add(m_HitFilter_MinLength, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer14 = new wxFlexGridSizer(0, 2, 0, 0);
    m_ParamsPanel->Add(itemFlexGridSizer14, 1, wxALIGN_LEFT|wxALL, 5);

    m_AlnMgr_Transloc = new wxCheckBox( itemCAlgoToolManagerParamsPanel1, ID_CHECKBOX1, _("Permit Translocations"), wxDefaultPosition, wxDefaultSize, 0 );
    m_AlnMgr_Transloc->SetValue(false);
    itemFlexGridSizer14->Add(m_AlnMgr_Transloc, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_AlnMgr_Sort = new wxCheckBox( itemCAlgoToolManagerParamsPanel1, ID_CHECKBOX2, _("Sort Segments By Score"), wxDefaultPosition, wxDefaultSize, 0 );
    m_AlnMgr_Sort->SetValue(true);
    itemFlexGridSizer14->Add(m_AlnMgr_Sort, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_AlnMgr_PreserveRows = new wxCheckBox( itemCAlgoToolManagerParamsPanel1, ID_CHECKBOX, _("Preserve Self Alignments"), wxDefaultPosition, wxDefaultSize, 0 );
    m_AlnMgr_PreserveRows->SetValue(false);
    itemFlexGridSizer14->Add(m_AlnMgr_PreserveRows, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_AlnMgr_FillUnaligned = new wxCheckBox( itemCAlgoToolManagerParamsPanel1, ID_CHECKBOX5, _("Fill Unaligned Regions With Gaps"), wxDefaultPosition, wxDefaultSize, 0 );
    m_AlnMgr_FillUnaligned->SetValue(false);
    itemFlexGridSizer14->Add(m_AlnMgr_FillUnaligned, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

////@end CCleanupAlignmentsParamsPanel content construction

    m_AlnMgr_Transloc->Enable(false);

    m_ParamsPanel->Show((size_t)0, false);
    m_ParamsPanel->Show((size_t)1, true);
    m_ParamsPanel->Layout();

}

void CCleanupAlignmentsParamsPanel::OnComboboxSelected( wxCommandEvent& event )
{
    x_AdjustToAlgoSelector();

    // Before editing this code, remove the block markers.
    event.Skip();
}

void CCleanupAlignmentsParamsPanel::x_AdjustToAlgoSelector()
{
    if (m_AlgoSelector->GetCurrentSelection() == 0) {
        /// alignment manager panel
        m_ParamsPanel->Show((size_t)0, false);
        m_ParamsPanel->Show((size_t)1, true);
    } else {
        m_ParamsPanel->Show((size_t)0, true);
        m_ParamsPanel->Show((size_t)1, false);
    }
    m_ParamsPanel->Layout();
}

bool CCleanupAlignmentsParamsPanel::ShowToolTips()
{
    return true;
}
wxBitmap CCleanupAlignmentsParamsPanel::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CCleanupAlignmentsParamsPanel bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end CCleanupAlignmentsParamsPanel bitmap retrieval
}
wxIcon CCleanupAlignmentsParamsPanel::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CCleanupAlignmentsParamsPanel icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end CCleanupAlignmentsParamsPanel icon retrieval
}


void CCleanupAlignmentsParamsPanel::SetRegistryPath(const string& path)
{
    m_RegPath = path; // store for later use
}


static const char* kTableTag = "Table";

void CCleanupAlignmentsParamsPanel::SaveSettings() const
{
    if( ! m_RegPath.empty())   {
        CGuiRegistry& gui_reg = CGuiRegistry::GetInstance();
        string reg_path = CGuiRegistryUtil::MakeKey(m_RegPath, kTableTag);

        CRegistryWriteView table_view = gui_reg.GetWriteView(reg_path);
        m_ObjectList->SaveTableSettings(table_view);
    }
}


void CCleanupAlignmentsParamsPanel::LoadSettings()
{
    if( ! m_RegPath.empty()) {
        CGuiRegistry& gui_reg = CGuiRegistry::GetInstance();
        string reg_path = CGuiRegistryUtil::MakeKey(m_RegPath, kTableTag);

        CRegistryReadView table_view = gui_reg.GetReadView(reg_path);
        m_ObjectList->LoadTableSettings(table_view);
    }
}



void CCleanupAlignmentsParamsPanel::SetParams(SCleanupAlignmentsParams* params,
                                              TConstScopedObjects* objects)
{
    m_Params = params;
    m_InputObjects = objects;
}


bool CCleanupAlignmentsParamsPanel::TransferDataToWindow()
{
    if (m_InputListDirty)    {
        m_ObjectList->SetObjects(*m_InputObjects);
        m_ObjectList->SelectAll();
        m_InputListDirty = false;
    }

    m_AlnMgr_PreserveRows->SetValue(m_Params->m_AlnMgr_PreserveRows);
    //m_AlnMgr_Transloc->SetValue(m_Params->m_AlnMgr_Transloc);
    m_AlnMgr_Sort->SetValue(m_Params->m_AlnMgr_Sort);
    m_AlnMgr_FillUnaligned->SetValue(m_Params->m_AlnMgr_FillUnaligned);

    m_HitFilter_MinIdentity->SetValue
        (ToWxString(NStr::DoubleToString(m_Params->m_HitFilter_MinIdentity)));
    m_HitFilter_MinLength->SetValue
        (ToWxString(NStr::DoubleToString(m_Params->m_HitFilter_MinLength)));


    switch (m_Params->m_Algo) {
    case SCleanupAlignmentsParams::eHitFilter:
        m_AlgoSelector->SetSelection(1);
        break;
    case SCleanupAlignmentsParams::eAlignmentManager:
        m_AlgoSelector->SetSelection(0);
        break;
    }
    x_AdjustToAlgoSelector();

    return wxPanel::TransferDataToWindow();
}


bool CCleanupAlignmentsParamsPanel::TransferDataFromWindow()
{
    if(wxPanel::TransferDataFromWindow())   {
        m_ObjectList->GetSelection(m_Params->m_Alignments);

        m_Params->m_AlnMgr_PreserveRows  = m_AlnMgr_PreserveRows->GetValue();
        m_Params->m_AlnMgr_Transloc      = m_AlnMgr_Transloc->GetValue();
        m_Params->m_AlnMgr_Sort          = m_AlnMgr_Sort->GetValue();
        m_Params->m_AlnMgr_FillUnaligned = m_AlnMgr_FillUnaligned->GetValue();

        string v;
        v = ToStdString(m_HitFilter_MinIdentity->GetValue());
        m_Params->m_HitFilter_MinIdentity = NStr::StringToDouble(v);
        v = ToStdString(m_HitFilter_MinLength->GetValue());
        m_Params->m_HitFilter_MinLength = NStr::StringToInt(v);

        switch (m_AlgoSelector->GetSelection()) {
        case 0:
            m_Params->m_Algo = SCleanupAlignmentsParams::eAlignmentManager;
            break;

        case 1:
            m_Params->m_Algo = SCleanupAlignmentsParams::eHitFilter;
            break;
        }

        return true;
    }
    return false;
}

void CCleanupAlignmentsParamsPanel::RestoreDefaults()
{
    if (!m_Params)
        return;
    m_Params->Init();
    TransferDataToWindow();
}

END_NCBI_SCOPE