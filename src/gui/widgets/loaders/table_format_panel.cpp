/*  $Id: table_format_panel.cpp 43758 2019-08-28 17:11:20Z katargir $
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
 * Authors: Bob Falk
 *
 * File Description:
 *
 */

#include <ncbi_pch.hpp>////@begin includes
#include "wx/imaglist.h"
////@end includes

#include <corelib/ncbifile.hpp>
#include <corelib/ncbitime.hpp>

#include "table_format_panel.hpp"
#include <gui/objutils/registry.hpp>

#include <gui/widgets/wx/async_call.hpp>
#include <gui/widgets/wx/compressed_file.hpp>

#include <gui/widgets/loaders/table_import_listctrl.hpp>

#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/statbox.h>
#include <wx/icon.h>
#include <wx/bitmap.h>
#include <wx/msgdlg.h>
#include <wx/radiobut.h>
#include <wx/listctrl.h>
#include <wx/filename.h>

////@begin XPM images
////@end XPM images

BEGIN_NCBI_SCOPE
USING_SCOPE(objects);

IMPLEMENT_DYNAMIC_CLASS( CTableFormatPanel, wxPanel )

BEGIN_EVENT_TABLE( CTableFormatPanel, wxPanel )

////@begin CTableFormatPanel event table entries
    EVT_RADIOBUTTON( ID_DELIMITEDBUTTON, CTableFormatPanel::OnDelimitedButtonSelected )
    EVT_RADIOBUTTON( ID_FIXEDWIDTHBUTTON, CTableFormatPanel::OnFixedwidthButtonSelected )
    EVT_SPINCTRL( ID_FIRSTLINESPINCTRL, CTableFormatPanel::OnFirstLineSpinCtrlUpdated )
    EVT_TEXT( ID_COMMENTCHARTXTCTRL, CTableFormatPanel::OnCommentCharTxtCtrlTextUpdated )
    EVT_CHECKBOX( ID_PARSECOLUMNNAMESBTN, CTableFormatPanel::OnParseColumnNamesBtnClick )
    EVT_LIST_ITEM_SELECTED( ID_LISTCTRL, CTableFormatPanel::OnListCtrlSelected )
////@end CTableFormatPanel event table entries
END_EVENT_TABLE()

CTableFormatPanel::CTableFormatPanel()
{
    Init();
}

CTableFormatPanel::CTableFormatPanel( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}

bool CTableFormatPanel::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin CTableFormatPanel creation
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end CTableFormatPanel creation
    return true;
}

CTableFormatPanel::~CTableFormatPanel()
{
////@begin CTableFormatPanel destruction
////@end CTableFormatPanel destruction
}

void CTableFormatPanel::Init()
{
////@begin CTableFormatPanel member initialisation
    m_DelimitedBtn = NULL;
    m_FixedWidthBtn = NULL;
    m_ImportStaticText = NULL;
    m_DataImportLine = NULL;
    m_CommentStaticText = NULL;
    m_CommentCharTextCtrl = NULL;
    m_ParseColumnNamesBtn = NULL;
    m_HeaderImportRow = NULL;
    m_PreviewResultsInfoTxt = NULL;
    m_ListCtrlPanel = NULL;
    m_TableListCtrl = NULL;
////@end CTableFormatPanel member initialisation
}

void CTableFormatPanel::CreateControls()
{    
////@begin CTableFormatPanel content construction
    // Generated by DialogBlocks, 14/08/2019 16:36:08 (unregistered)

    CTableFormatPanel* itemPanel1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemPanel1->SetSizer(itemBoxSizer2);

    wxStaticBox* itemStaticBoxSizer3Static = new wxStaticBox(itemPanel1, wxID_ANY, wxEmptyString);
    wxStaticBoxSizer* itemStaticBoxSizer3 = new wxStaticBoxSizer(itemStaticBoxSizer3Static, wxVERTICAL);
    itemBoxSizer2->Add(itemStaticBoxSizer3, 0, wxALIGN_LEFT|wxALL, 5);

    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    itemStaticBoxSizer3->Add(itemBoxSizer4, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer5Static = new wxStaticBox(itemStaticBoxSizer3->GetStaticBox(), wxID_ANY, _("Table Data Format"));
    wxStaticBoxSizer* itemStaticBoxSizer5 = new wxStaticBoxSizer(itemStaticBoxSizer5Static, wxVERTICAL);
    itemBoxSizer4->Add(itemStaticBoxSizer5, 1, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5);

    m_DelimitedBtn = new wxRadioButton( itemStaticBoxSizer5->GetStaticBox(), ID_DELIMITEDBUTTON, _("Delimited - Columns are separated by characters, e.g. tabs or commas"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
    m_DelimitedBtn->SetValue(false);
    itemStaticBoxSizer5->Add(m_DelimitedBtn, 0, wxALIGN_LEFT|wxALL, 5);

    m_FixedWidthBtn = new wxRadioButton( itemStaticBoxSizer5->GetStaticBox(), ID_FIXEDWIDTHBUTTON, _("Fixed Width - Columns all have a fixed character width"), wxDefaultPosition, wxDefaultSize, 0 );
    m_FixedWidthBtn->SetValue(false);
    itemStaticBoxSizer5->Add(m_FixedWidthBtn, 0, wxALIGN_LEFT|wxALL, 5);

    wxBoxSizer* itemBoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    itemStaticBoxSizer3->Add(itemBoxSizer8, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT, 5);

    m_ImportStaticText = new wxStaticText( itemStaticBoxSizer3->GetStaticBox(), wxID_STATIC, _("Import data starting with row:"), wxDefaultPosition, wxDefaultSize, 0 );
    m_ImportStaticText->Enable(false);
    itemBoxSizer8->Add(m_ImportStaticText, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_DataImportLine = new wxSpinCtrl( itemStaticBoxSizer3->GetStaticBox(), ID_FIRSTLINESPINCTRL, wxT("1"), wxDefaultPosition, wxSize(80, -1), wxSP_ARROW_KEYS, 1, 500, 1 );
    m_DataImportLine->Enable(false);
    itemBoxSizer8->Add(m_DataImportLine, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_CommentStaticText = new wxStaticText( itemStaticBoxSizer3->GetStaticBox(), wxID_STATIC, _("Comment Character:"), wxDefaultPosition, wxDefaultSize, 0 );
    m_CommentStaticText->Enable(false);
    itemBoxSizer8->Add(m_CommentStaticText, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_CommentCharTextCtrl = new wxTextCtrl( itemStaticBoxSizer3->GetStaticBox(), ID_COMMENTCHARTXTCTRL, wxEmptyString, wxDefaultPosition, wxSize(20, -1), 0 );
    m_CommentCharTextCtrl->SetMaxLength(1);
    m_CommentCharTextCtrl->Enable(false);
    itemBoxSizer8->Add(m_CommentCharTextCtrl, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer13 = new wxBoxSizer(wxHORIZONTAL);
    itemStaticBoxSizer3->Add(itemBoxSizer13, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT, 5);

    m_ParseColumnNamesBtn = new wxCheckBox( itemStaticBoxSizer3->GetStaticBox(), ID_PARSECOLUMNNAMESBTN, _("Parse Column Names from Selected Row:"), wxDefaultPosition, wxDefaultSize, 0 );
    m_ParseColumnNamesBtn->SetValue(false);
    itemBoxSizer13->Add(m_ParseColumnNamesBtn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_HeaderImportRow = new wxStaticText( itemStaticBoxSizer3->GetStaticBox(), wxID_COLUMNNAMESROW, wxEmptyString, wxDefaultPosition, wxSize(40, -1), wxST_NO_AUTORESIZE|wxSTATIC_BORDER );
    itemBoxSizer13->Add(m_HeaderImportRow, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_PreviewResultsInfoTxt = new wxStaticText( itemStaticBoxSizer3->GetStaticBox(), wxID_PREVIEWRESULTSTXT, _("Preview Results"), wxDefaultPosition, wxDefaultSize, 0 );
    m_PreviewResultsInfoTxt->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), wxNORMAL_FONT->GetFamily(), wxNORMAL_FONT->GetStyle(), wxFONTWEIGHT_BOLD, wxNORMAL_FONT->GetUnderlined(), wxNORMAL_FONT->GetFaceName()));
    itemStaticBoxSizer3->Add(m_PreviewResultsInfoTxt, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticBox* itemStaticBoxSizer17Static = new wxStaticBox(itemPanel1, wxID_ANY, _("Table Preview"));
    wxStaticBoxSizer* itemStaticBoxSizer17 = new wxStaticBoxSizer(itemStaticBoxSizer17Static, wxHORIZONTAL);
    itemBoxSizer2->Add(itemStaticBoxSizer17, 1, wxGROW|wxALL, 5);

    m_ListCtrlPanel = new wxPanel( itemStaticBoxSizer17->GetStaticBox(), ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    itemStaticBoxSizer17->Add(m_ListCtrlPanel, 1, wxGROW|wxTOP, 5);

    wxBoxSizer* itemBoxSizer19 = new wxBoxSizer(wxHORIZONTAL);
    m_ListCtrlPanel->SetSizer(itemBoxSizer19);

    m_TableListCtrl = new CTableImportListCtrl( m_ListCtrlPanel, ID_LISTCTRL, wxDefaultPosition, wxSize(100, 100), wxLC_REPORT );
    itemBoxSizer19->Add(m_TableListCtrl, 1, wxGROW|wxALL, 5);

////@end CTableFormatPanel content construction
}

void CTableFormatPanel::SetMainTitle(const wxString& /*title*/)
{
   // m_MainBox->SetLabel(title);
}

bool CTableFormatPanel::IsInputValid()
{
    if (m_DelimitedBtn->GetValue() == false &&
        m_FixedWidthBtn->GetValue() == false)
        return false;

    /// Make sure file was loade successfully:
    if (m_ImportedTableData->GetNumImportedRows() > 0)
       return true;
    else
        return false;
}


void CTableFormatPanel::SetRegistryPath( const string& path )
{
    m_RegPath = path;
}


void CTableFormatPanel::LoadSettings()
{
    m_TableListCtrl->SetViewType(CTableImportListCtrl::eSingleColumn);
}


void CTableFormatPanel::SaveSettings() const
{
}

bool CTableFormatPanel::IsDelimitedFile() const
{
    if (m_FixedWidthBtn->GetValue())
        return false;

    return true;
}


bool CTableFormatPanel::PreviewData()
{
    wxString s = m_PreviewFname;

    try {

        CStopWatch  loadtime;
        loadtime.Start();

        Int8 filesize = -1;
        {
            CFile tstfile(s.c_str().AsChar());

            if (!tstfile.IsFile()) {
                if (!CCompressedFile::FileExists(s)) {
                    wxString msg = wxT("Error opening file: ") + s;
                    wxMessageBox(msg, wxT("Error Opening or Loading File"),
                        wxOK | wxICON_ERROR, this);
                    return false;
                }
            }
            else
                filesize = tstfile.GetLength();
        }

        // Set listcontrol to an empty table first so that any ui events don't try to access
        // the loading table.
        CRef<CTableImportDataSource> empty_table;
        m_TableListCtrl->SetDataSource(empty_table);

        if (!GUI_AsyncExec(
            [this, filesize](ICanceled& canceled)
            {
                return m_ImportedTableData->LoadTable(m_PreviewFname, filesize, &canceled) || canceled.IsCanceled();
            }, wxT("Loading Table..."))) {
            wxString msg = wxT("Error loading table from file: ") + m_PreviewFname;
            wxMessageBox(msg, wxT("Error Opening or Loading File"),             
                wxOK | wxICON_ERROR);
        }
      
        //_TRACE("Time to load: " << loadtime.Elapsed());

        // If there was an error or user cancelled the load there will be no rows
        // so just refresh and return.
        if (m_ImportedTableData->GetNumRows() == 0) {
            m_TableListCtrl->SetDataSource(m_ImportedTableData);
            Refresh();
        }

        /// Set the import row (subtract 1 to make it 0 based)
        //m_ImportedTableData->SetFirstImportRow(m_DataImportLine->GetValue()-1);
        m_DataImportLine->Enable(true);
        m_CommentCharTextCtrl->Enable(true);
        m_ImportStaticText->Enable(true);
        m_CommentStaticText->Enable(true);
        m_ParseColumnNamesBtn->SetValue(false);
        m_HeaderImportRow->SetLabelText(ToWxString(""));


        // Set (optional) character preceeding comments.  Blank, ' ', indicates that
        // there is no comment character so we set the field empty, "", in this case.
        wxString comment_char = ToWxString(string(1,m_ImportedTableData->GetCommentChar()));
        if (comment_char == wxT(" ") )
            comment_char = wxT("");

        m_CommentCharTextCtrl->SetValue(comment_char);
        m_DataImportLine->SetValue(m_ImportedTableData->GetFirstImportRow()+1);

        if (m_ImportedTableData->GetTableType() == 
            CTableImportDataSource::eDelimitedTable) {
                m_DelimitedBtn->SetValue(true);
                m_FixedWidthBtn->SetValue(false);

                if (m_ImportedTableData->GetDelimiters().size() == 1) {
                    char delim = m_ImportedTableData->GetDelimiters()[0];
                    wxString delim_char(delim);
                    if (delim == ' ')
                        delim_char = "space";
                    else if (delim == '\t')
                        delim_char = "tab";

                    m_PreviewResultsInfoTxt->SetLabelText(wxT("The table file seems to be delimited by character: '") +
                        delim_char + wxT("'"));
                }
                // Currently only option for two characters as delimiters from first
                // panel is whitespace:
                else if (m_ImportedTableData->GetDelimiters().size() == 2) {
                    m_PreviewResultsInfoTxt->SetLabelText(wxT("The table file seems to be delimited by whitespace"));
                }
        }
        else {
            m_DelimitedBtn->SetValue(false);
            m_FixedWidthBtn->SetValue(true);

            m_PreviewResultsInfoTxt->SetLabelText("The table file seems to be composed of fixed-width fields");                    
        }

        m_TableListCtrl->SetDataSource(m_ImportedTableData);

        Refresh();
    }
    catch(...) {
        wxString msg = wxT("Unable to open file: ") + s + wxT(" for reading");
        wxMessageBox(msg, wxT("Error Opening File"),             
            wxOK | wxICON_ERROR, this);
        return false;
    }

    return true;
}

bool CTableFormatPanel::ShowToolTips()
{
    return true;
}
wxBitmap CTableFormatPanel::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CTableFormatPanel bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end CTableFormatPanel bitmap retrieval
}
wxIcon CTableFormatPanel::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CTableFormatPanel icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end CTableFormatPanel icon retrieval
}

void CTableFormatPanel::OnDelimitedButtonSelected( wxCommandEvent& /*event*/ )
{
    m_ImportedTableData->SetTableType(CTableImportDataSource::eDelimitedTable);
}

void CTableFormatPanel::OnFixedwidthButtonSelected( wxCommandEvent& /*event*/ )
{
    m_ImportedTableData->SetTableType(CTableImportDataSource::eFixedWidthTable);
}

void CTableFormatPanel::OnFirstLineSpinCtrlUpdated( wxSpinEvent& /*event*/ )
{
    int first_row = m_DataImportLine->GetValue();
    if (!m_ImportedTableData.IsNull()) {
        /// Set the import row (subtract 1 to make it 0 based)
        m_ImportedTableData->SetFirstImportRow(first_row-1);
        m_TableListCtrl->Refresh();
    }
}

void CTableFormatPanel::OnCommentCharTxtCtrlTextUpdated( wxCommandEvent& /*event*/ )
{
    string str = ToStdString(m_CommentCharTextCtrl->GetValue());
    char updated_char = str.size() > 0 ? str[0] : ' ';

    // Treat tab as default comment char (meaning there is none)
    if (updated_char == '\t')
        updated_char = ' ';
    
    char comment_char = m_ImportedTableData->GetCommentChar();

    // Update table if comment character has changed.  Blank (' ') is
    // the defualt character.
    if (comment_char != updated_char) {
        m_ImportedTableData->SetCommentChar(updated_char);
        m_TableListCtrl->Refresh();
    }
}


void CTableFormatPanel::OnParseColumnNamesBtnClick( wxCommandEvent& /*event*/ )
{
    int sel = m_TableListCtrl->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

    // Currently no row is selected
    if (m_ParseColumnNamesBtn->GetValue() && sel == -1) {
        m_ParseColumnNamesBtn->SetValue(false);
        return;
    }
        
    if (sel != -1 && m_ParseColumnNamesBtn->GetValue()) {
        string numstr = NStr::Int8ToString(Int8(sel+1));
        m_HeaderImportRow->SetLabelText(ToWxString(numstr.c_str()));
        m_ImportedTableData->SetColumnHeaderRow(sel);        
    }
    else {
        m_HeaderImportRow->SetLabelText(ToWxString(""));
        m_ImportedTableData->SetColumnHeaderRow(-1);
    }

    m_ImportedTableData->RecomputeHeaders();
    m_TableListCtrl->Refresh();
}

void CTableFormatPanel::OnListCtrlSelected( wxListEvent& event )
{
    if (m_ParseColumnNamesBtn->GetValue()) {
        string numstr = NStr::Int8ToString(Int8(event.GetIndex()+1));
        m_HeaderImportRow->SetLabelText(ToWxString(numstr.c_str()));
        m_ImportedTableData->SetColumnHeaderRow(event.GetIndex());

        m_ImportedTableData->RecomputeHeaders();        
        m_TableListCtrl->Refresh();
    }
}


END_NCBI_SCOPE



