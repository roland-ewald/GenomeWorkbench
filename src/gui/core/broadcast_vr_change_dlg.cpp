/*  $Id: broadcast_vr_change_dlg.cpp 23922 2011-06-22 14:39:29Z katargir $
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
 * Authors:
 *
 * File Description:
 *
 */

// Generated by DialogBlocks (unregistered), 24/03/2009 16:27:45

#include <ncbi_pch.hpp>
#include <gui/core/broadcast_vr_change_dlg.hpp>

#include <wx/sizer.h>
#include <wx/radiobut.h>
#include <wx/button.h>
#include <wx/icon.h>

////@begin includes
////@end includes

BEGIN_NCBI_SCOPE

////@begin XPM images
////@end XPM images

IMPLEMENT_DYNAMIC_CLASS( CBroadcastVRChangeDialog, wxDialog )

BEGIN_EVENT_TABLE( CBroadcastVRChangeDialog, wxDialog )

////@begin CBroadcastVRChangeDialog event table entries
    EVT_CHECKBOX( ID_CHECKBOX, CBroadcastVRChangeDialog::OnByDefaultClick )

////@end CBroadcastVRChangeDialog event table entries

END_EVENT_TABLE()

CBroadcastVRChangeDialog::CBroadcastVRChangeDialog()
{
    Init();
}

CBroadcastVRChangeDialog::CBroadcastVRChangeDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}

bool CBroadcastVRChangeDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin CBroadcastVRChangeDialog creation
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end CBroadcastVRChangeDialog creation
    return true;
}

CBroadcastVRChangeDialog::~CBroadcastVRChangeDialog()
{
////@begin CBroadcastVRChangeDialog destruction
////@end CBroadcastVRChangeDialog destruction
}

void CBroadcastVRChangeDialog::Init()
{
////@begin CBroadcastVRChangeDialog member initialisation
    m_ByDefault = NULL;
////@end CBroadcastVRChangeDialog member initialisation
}

void CBroadcastVRChangeDialog::CreateControls()
{    
////@begin CBroadcastVRChangeDialog content construction
    CBroadcastVRChangeDialog* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer2->Add(itemBoxSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    itemBoxSizer3->Add(0, 0, 1, wxALIGN_CENTER_HORIZONTAL, 0);

    m_ByDefault = new wxCheckBox( itemDialog1, ID_CHECKBOX, _("By default"), wxDefaultPosition, wxDefaultSize, 0 );
    m_ByDefault->SetValue(false);
    itemBoxSizer3->Add(m_ByDefault, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticLine* itemStaticLine6 = new wxStaticLine( itemDialog1, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer3->Add(itemStaticLine6, 0, wxGROW|wxALL, 5);

    wxRadioButton* itemRadioButton7 = new wxRadioButton( itemDialog1, ID_RADIOBUTTON1, _("Track"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
    itemRadioButton7->SetValue(false);
    itemBoxSizer3->Add(itemRadioButton7, 0, wxALIGN_LEFT|wxALL, 5);

    wxRadioButton* itemRadioButton8 = new wxRadioButton( itemDialog1, ID_RADIOBUTTON2, _("Track and Center"), wxDefaultPosition, wxDefaultSize, 0 );
    itemRadioButton8->SetValue(false);
    itemBoxSizer3->Add(itemRadioButton8, 0, wxALIGN_LEFT|wxALL, 5);

    wxRadioButton* itemRadioButton9 = new wxRadioButton( itemDialog1, ID_RADIOBUTTON3, _("Track and Expand"), wxDefaultPosition, wxDefaultSize, 0 );
    itemRadioButton9->SetValue(false);
    itemBoxSizer3->Add(itemRadioButton9, 0, wxALIGN_LEFT|wxALL, 5);

    wxRadioButton* itemRadioButton10 = new wxRadioButton( itemDialog1, ID_RADIOBUTTON4, _("Track and Contract"), wxDefaultPosition, wxDefaultSize, 0 );
    itemRadioButton10->SetValue(false);
    itemBoxSizer3->Add(itemRadioButton10, 0, wxALIGN_LEFT|wxALL, 5);

    wxRadioButton* itemRadioButton11 = new wxRadioButton( itemDialog1, ID_RADIOBUTTON5, _("Track and Follow"), wxDefaultPosition, wxDefaultSize, 0 );
    itemRadioButton11->SetValue(false);
    itemBoxSizer3->Add(itemRadioButton11, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticLine* itemStaticLine12 = new wxStaticLine( itemDialog1, ID_STATICLINE2, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer2->Add(itemStaticLine12, 0, wxGROW|wxALL, 5);

    wxStdDialogButtonSizer* itemStdDialogButtonSizer13 = new wxStdDialogButtonSizer;

    itemBoxSizer2->Add(itemStdDialogButtonSizer13, 0, wxALIGN_RIGHT|wxALL, 5);
    wxButton* itemButton14 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemButton14->SetDefault();
    itemStdDialogButtonSizer13->AddButton(itemButton14);

    wxButton* itemButton15 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer13->AddButton(itemButton15);

    itemStdDialogButtonSizer13->Realize();

    // Set validators
    m_ByDefault->SetValidator( wxGenericValidator(& mf_ByDefault) );
    itemRadioButton7->SetValidator( wxGenericValidator(& m_BroadcastFlags[0]) );
    itemRadioButton8->SetValidator( wxGenericValidator(& m_BroadcastFlags[1]) );
    itemRadioButton9->SetValidator( wxGenericValidator(& m_BroadcastFlags[2]) );
    itemRadioButton10->SetValidator( wxGenericValidator(& m_BroadcastFlags[3]) );
    itemRadioButton11->SetValidator( wxGenericValidator(& m_BroadcastFlags[4]) );
////@end CBroadcastVRChangeDialog content construction
}

int CBroadcastVRChangeDialog::GetBroadcastFlag() const
{
    if( !mf_ByDefault ){
        for( size_t i = 0; i < sizeof(m_BroadcastFlags)/sizeof(bool); i++ ){
            if( m_BroadcastFlags[i] ){
                return (int)i;
            }                                   
        }
    }

    return -1; // CVisibleRange::eBasic_Default;
}

void CBroadcastVRChangeDialog::SetBroadcastFlag( int shift )
{
    if( shift >= 0 && (size_t)shift < sizeof(m_BroadcastFlags)/sizeof(bool) ){
        for( size_t i = 0; i < sizeof(m_BroadcastFlags)/sizeof(bool); i++ ){
            m_BroadcastFlags[i] = false;
        }
    
        m_BroadcastFlags[shift] = true;
    }
}

bool CBroadcastVRChangeDialog::ShowToolTips()
{
    return true;
}
wxBitmap CBroadcastVRChangeDialog::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CBroadcastVRChangeDialog bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end CBroadcastVRChangeDialog bitmap retrieval
}
wxIcon CBroadcastVRChangeDialog::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CBroadcastVRChangeDialog icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end CBroadcastVRChangeDialog icon retrieval
}

void CBroadcastVRChangeDialog::ResetRadioButtons( bool show )
{
    if( show ){
        FindWindow( ID_RADIOBUTTON1 )->Enable();
        FindWindow( ID_RADIOBUTTON2 )->Enable();
        FindWindow( ID_RADIOBUTTON3 )->Enable();
        FindWindow( ID_RADIOBUTTON4 )->Enable();
        FindWindow( ID_RADIOBUTTON5 )->Enable();
    
    } else {
        FindWindow( ID_RADIOBUTTON1 )->Disable();
        FindWindow( ID_RADIOBUTTON2 )->Disable();
        FindWindow( ID_RADIOBUTTON3 )->Disable();
        FindWindow( ID_RADIOBUTTON4 )->Disable();
        FindWindow( ID_RADIOBUTTON5 )->Disable();
    }
}



void CBroadcastVRChangeDialog::OnByDefaultClick( wxCommandEvent& event )
{
    ResetRadioButtons( !event.IsChecked() );
}

END_NCBI_SCOPE


