/*  $Id: subprepintropanel.cpp 33027 2015-05-18 13:17:40Z asztalos $
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
 * Authors:  Colleen Bollin
 */


#include <ncbi_pch.hpp>
#include <objects/submit/Submit_block.hpp>
#include <objects/seq/Pubdesc.hpp>
#include <objects/pub/Pub.hpp>
#include <objects/pub/Pub_equiv.hpp>

////@begin includes
////@end includes

#include <gui/utils/event_handler.hpp>
#include <gui/utils/app_popup.hpp>
#include <gui/objutils/cmd_create_desc.hpp>
#include <gui/objutils/descriptor_change.hpp>
#include <gui/packages/pkg_sequence_edit/subprep_util.hpp>
#include <gui/packages/pkg_sequence_edit/subprepintropanel.hpp>
#include <gui/packages/pkg_sequence_edit/submitblockdlg.hpp>
#include <gui/widgets/wx/async_call.hpp>
#include "subprep_event.hpp"

#include <wx/msgdlg.h>

////@begin XPM images
////@end XPM images

BEGIN_NCBI_SCOPE


/*!
 * CSubPrepIntroPanel type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CSubPrepIntroPanel, wxPanel )


/*!
 * CSubPrepIntroPanel event table definition
 */

BEGIN_EVENT_TABLE( CSubPrepIntroPanel, wxPanel )

////@begin CSubPrepIntroPanel event table entries
    EVT_HYPERLINK( ID_HYPERLINKCTRL5, CSubPrepIntroPanel::OnEditSubmitterInfoClicked )

    EVT_LISTBOX( ID_SUBMISSION_TYPE, CSubPrepIntroPanel::OnSubmissionTypeSelected )

    EVT_TEXT_URL( ID_INTRO_TEXT, CSubPrepIntroPanel::OnIntroTextClickUrl )

////@end CSubPrepIntroPanel event table entries

END_EVENT_TABLE()


/*!
 * CSubPrepIntroPanel constructors
 */

CSubPrepIntroPanel::CSubPrepIntroPanel()
{
    Init();
}

CSubPrepIntroPanel::CSubPrepIntroPanel( wxWindow* parent, IWorkbench* workbench, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) :
  m_Workbench(workbench)
{
    Init();
    Create(parent, id, pos, size, style);
}


/*!
 * CSubPrepIntroPanel creator
 */

bool CSubPrepIntroPanel::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
////@begin CSubPrepIntroPanel creation
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end CSubPrepIntroPanel creation
    return true;
}


/*!
 * CSubPrepIntroPanel destructor
 */

CSubPrepIntroPanel::~CSubPrepIntroPanel()
{
////@begin CSubPrepIntroPanel destruction
////@end CSubPrepIntroPanel destruction
}


/*!
 * Member initialisation
 */

void CSubPrepIntroPanel::Init()
{
////@begin CSubPrepIntroPanel member initialisation
    m_StarSubmitter = NULL;
    m_SubmitterLabel = NULL;
    m_StarType = NULL;
    m_SubmissionType = NULL;
    m_IntroText = NULL;
////@end CSubPrepIntroPanel member initialisation
}


/*!
 * Control creation for CSubPrepIntroPanel
 */

void CSubPrepIntroPanel::CreateControls()
{    
////@begin CSubPrepIntroPanel content construction
    // Generated by DialogBlocks, 10/06/2013 17:53:48 (unregistered)

    CSubPrepIntroPanel* itemPanel1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemPanel1->SetSizer(itemBoxSizer2);

    wxFlexGridSizer* itemFlexGridSizer3 = new wxFlexGridSizer(0, 4, 0, 0);
    itemBoxSizer2->Add(itemFlexGridSizer3, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText4 = new wxStaticText( itemPanel1, wxID_STATIC, _("Submission Information"), wxDefaultPosition, wxSize(100, -1), wxALIGN_CENTRE );
    itemStaticText4->Wrap(20);
    itemFlexGridSizer3->Add(itemStaticText4, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_StarSubmitter = new wxStaticText( itemPanel1, wxID_STATIC, _("*"), wxDefaultPosition, wxDefaultSize, 0 );
    m_StarSubmitter->SetForegroundColour(wxColour(255, 0, 0));
    m_StarSubmitter->SetFont(wxFont(12, wxSWISS, wxNORMAL, wxNORMAL, false, wxT("Tahoma")));
    itemFlexGridSizer3->Add(m_StarSubmitter, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_SubmitterLabel = new wxTextCtrl( itemPanel1, wxID_STATIC, wxEmptyString, wxDefaultPosition, wxSize(400, -1), wxTE_MULTILINE|wxTE_READONLY );
    itemFlexGridSizer3->Add(m_SubmitterLabel, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxHyperlinkCtrl* itemHyperlinkCtrl7 = new wxHyperlinkCtrl( itemPanel1, ID_HYPERLINKCTRL5, _("Edit"), wxEmptyString, wxDefaultPosition, wxSize(20, -1), wxHL_DEFAULT_STYLE );
    itemFlexGridSizer3->Add(itemHyperlinkCtrl7, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText8 = new wxStaticText( itemPanel1, wxID_STATIC, _("Submission Type"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
    itemFlexGridSizer3->Add(itemStaticText8, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_StarType = new wxStaticText( itemPanel1, wxID_STATIC, _("*"), wxDefaultPosition, wxDefaultSize, 0 );
    m_StarType->SetForegroundColour(wxColour(255, 0, 0));
    m_StarType->SetFont(wxFont(12, wxSWISS, wxNORMAL, wxNORMAL, false, wxT("Tahoma")));
    itemFlexGridSizer3->Add(m_StarType, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxArrayString m_SubmissionTypeStrings;
    m_SubmissionType = new wxListBox( itemPanel1, ID_SUBMISSION_TYPE, wxDefaultPosition, wxDefaultSize, m_SubmissionTypeStrings, wxLB_SINGLE );
    if (CSubPrepIntroPanel::ShowToolTips())
        m_SubmissionType->SetToolTip(_("If you select the correct type of submission, this tool will suggest the required and recommended qualifiers needed to help the submission be processed more quickly by GenBank staff."));
    itemFlexGridSizer3->Add(m_SubmissionType, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemFlexGridSizer3->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_IntroText = new wxTextCtrl( itemPanel1, ID_INTRO_TEXT, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxTE_RICH|wxTE_AUTO_URL );
    itemBoxSizer2->Add(m_IntroText, 0, wxGROW|wxALL, 5);

    // Connect events and objects
    m_SubmitterLabel->Connect(wxID_STATIC, wxEVT_LEFT_DOWN, wxMouseEventHandler(CSubPrepIntroPanel::OnClickSubmitterSummary), NULL, this);
////@end CSubPrepIntroPanel content construction

    // later, will use all wizards; for now, just Standard and Uncultured Samples
#if 1
    m_SubmissionType->AppendString(_("Standard"));
    m_SubmissionType->AppendString(_("Uncultured Samples"));
#else
    TWizardNameList wizard_list = GetWizardNameList();

    ITERATE(TWizardNameList, kit, wizard_list) {
        m_SubmissionType->AppendString(ToWxString(kit->second));
    }
#endif

}


/*!
 * Should we show tooltips?
 */

bool CSubPrepIntroPanel::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap CSubPrepIntroPanel::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CSubPrepIntroPanel bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end CSubPrepIntroPanel bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CSubPrepIntroPanel::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CSubPrepIntroPanel icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end CSubPrepIntroPanel icon retrieval
}


static const wxString s_VectorScreenText = "\
Vector Contamination:\r\n\
Vector contamination should be removed before submitting your sequences to GenBank.\r\n\
Click the Vector Trim Tool button below if you have not yet screened your sequences for vector.\r\n\
Please see: \r\n\
https://www.ncbi.nlm.nih.gov/Sequin/sequin.hlp.html#VectorScreen\r\n\
";

static const wxString s_UnculturedSamplesIntroText = 
"\
Welcome to the Sequin Bulk DNA Sequence Submission Wizard!\r\n\
\r\n\
Use this tool if your sequences are from:\r\n\
-uncultured samples\r\n\
-the same gene region (for example: all 16S rRNA or all nifH)\r\n\
\r\n\
Requirements:\r\n\
-FASTA formatted nucleotide sequence text file or alignment file\r\n\
-Unique clone names\r\n\
-Isolation source (for example, freshwater lake at 100m depth)\r\n\
 or hostname (for example, Cocos nucifera) \r\n\
\r\n\
";

static const wxString s_VirusesIntroText = 
"\
Welcome to the Virus Sequence Submission Wizard!\r\n\
Use this tool if you are submitting:\r\n\
-virus sequences\r\n\
-viroid sequences\r\n\
\r\n\
Requirements\r\n\
-FASTA formatted nucleotide sequence text file or alignment file\r\n\
-Unique isolate/strain names\r\n\
-Country, host, collection-date, segment, genotype, and/or serotype may be required for certain viruses and is requested for all virus submissions\r\n\
\r\n\
Feature Annotation:\r\n\
Please use the assistance provided in the wizard to annotate the features your submission or annotate your submissions in the record viewer.\r\n\
If you do not provide feature annotation, assigning of Accession numbers will be delayed.\r\n\
\r\n\
";

static const wxString s_rRNA_ITS_IGSIntroText =
"\
Welcome to the Cultured rRNA-ITS-IGS Submission Wizard!\r\n\
\r\n\
Use this tool for rRNA, ITS, or IGS sequences from:\r\n\
- Cultured, pure strains of Bacteria, Archaea, or Fungi\r\n\
- Vouchered Fungi\r\n\
- Plant, animal or other eukaryotic sequences\r\n\
\r\n\
This tool is NOT for uncultured samples. Use the uncultured sample wizard if you are submitting sequences from an uncultured source.\r\n\
\r\n\
Requirements:\r\n\
   - FASTA formatted nucleotide sequence text file or alignment file\r\n\
   - Organism names\r\n\
   - Strain names for bacteria, and archaea\r\n\
   - Strain or specimen-vouchers for fungi\r\n\
   - Specimen vouchers or isolate codes for plants and animals\r\n\
\r\n\
Feature Annotation:\r\n\
Please use the wizard to annotate features in your sequences or annotate your submissions in the record viewer.\r\n\
If you do not provide feature annotation, assigning of Accession numbers will be delayed.\r\n\
\r\n\
";

static const wxString s_TSAIntroText = 
"\
Welcome to the TSA Submission Wizard!\r\n\
Use this tool for computationally assembled sequences from primary\r\n\
data such as ESTs, traces and Next Generation Sequencing\r\n\
Technologies.  TSA sequence records differ from EST and GenBank\r\n\
records because there are no physical counterparts to the assemblies.\r\n\
\r\n\
Prior to preparing your TSA submission please make sure your\r\n\
assemblies conform to the following standards:\r\n\
\r\n\
-Screen your sequences for vector contamination and remove any\r\n\
 vector sequence.\r\n\
-Remove any sequences less than 200bp in length.\r\n\
-Trim any sequences having more than 10% n's or containing greater\r\n\
 than 14 n's in a row.\r\n\
\r\n\
";

static const wxString s_IGSIntroText =
"\
Welcome to the Intergenic Spacer Submission Wizard!\r\n\
\r\n\
Use this tool for submitting intergenic spacer sequences.\r\n\
Do not use this tool for submitting complete genomes.\r\n\
\r\n\
Do not use this wizard if you are submitting rRNA-IGS sequences.\r\n\
If you are submitting rRNA-IGS sequences select the rRNA/ITS/IGS wizard instead.\r\n\
\r\n\
Requirements:\r\n\
- FASTA formatted nucleotide sequence text file or alignment file\r\n\
- Organism names\r\n\
- Unique Source information\r\n\
\r\n\
";
  
static const wxString s_MicrosatelliteIntroText = 
"\
Welcome to the Microsatellite Wizard!\r\n\
\r\n\
Use this tool for submitting Microsatellite sequences.\r\n\
\r\n\
Requirements:\r\n\
- FASTA formatted nucleotide sequence text file\r\n\
- Organism names\r\n\
- Unique microsatellite names or clone names\r\n\
\r\n\
";
  
static const wxString s_DLoopIntroText =
"\
Welcome to the D-loop & Control Region Wizard!\r\n\
\r\n\
Use this tool for submitting D-loop or Control Region sequences.\r\n\
\r\n\
Requirements:\r\n\
- FASTA formatted nucleotide sequence text file\r\n\
- Organism names\r\n\
- Unique source information (such as isolate, haplotype, or specimen- voucher)\r\n\
\r\n\
";

// note - have not yet implemented WGS wizard
static const wxString s_WGSIntroText =
"\
Welcome to the WGS wizard!\r\n\
\n\
Use this tool for submitting Whole Genome Shotgun Submissions to NCBI. \r\n\
This tool is for microbial genomes without annotation. Your file should include sequences from one organism only.\r\n\
\r\n\
Prior to preparing your WGS submission, please make sure your sequences and file conform to the following standards:\r\n\
-WGS contigs should not have any Ns representing gaps. If there are gaps in your sequence, you will need to split the sequences at the gaps. \r\n\
-do not include terminal N's\r\n\
-do not include any sequences shorter than 200 nt \r\n\
-do not include sequences containing more than 10% N's or large regions of low quality sequence\r\n\
-file should not contain more than 10,000 sequences\r\n\
\n\
For more information about WGS submissions, please see: \r\n\
";

static const wxString s_DefaultIntroText =
"\
Welcome to the Standard Submission Preparation Tool!\r\n\
\r\n\
The Standard Submission preparation tool may be used for any type of nucleotide sequence data except EST (expressed sequence tags), GSS (genome survey sequences), and STS (sequence tagged sites) submissions. Do not use this tool for EST, GSS, or STS submissions.\r\n\
\r\n\
Please review the GenBank data policies before proceeding:\r\n\
https://www.ncbi.nlm.nih.gov/genbank/submit_types \r\n\
\r\n\
";


// for communicating with parent
void CSubPrepIntroPanel::x_SetSubmissionNotReady(string error)
{
    CSubPrep_panel* parent = x_GetParent();
    if (parent) {
        parent->SetSubmissionNotReady(error);
    }
}


void CSubPrepIntroPanel::x_UpdateSubmitBlock(CRef<objects::CSubmit_block> new_block, CRef<objects::CCit_gen> new_gen, string alt_email)
{
    CSubPrep_panel* parent = x_GetParent();
    if (parent) {
        parent->UpdateSubmitBlock(new_block, new_gen, alt_email);
    }
}


static void s_ShowStar(wxStaticText* star, bool show)
{
    if (show) {
        star->SetLabel(wxT("*"));
    } else {
        star->SetLabel(wxT(" "));
    }
}


CSubPrep_panel* CSubPrepIntroPanel::x_GetParent()
{
    wxWindow* w = this->GetParent();
    while (w != NULL) {
        CSubPrep_panel* parent = dynamic_cast<CSubPrep_panel*>(w);
        if (parent) {
            return parent;
        } else {
            w = w->GetParent();
        }
    }
    return NULL;
}


static const string kSubmitterInfoComplete = "All required fields present";

void CSubPrepIntroPanel::RefreshSubmitterInfoStatus()
{
    CSubPrep_panel* parent = x_GetParent();
    if (!parent) {
        return;
    }
    
    CRef<objects::CCit_gen> gen(new objects::CCit_gen());

    objects::CSeqdesc_CI orig_citsub = parent->GetCitSubPub();
    if (orig_citsub) {
        gen->Assign(orig_citsub->GetPub().GetPub().Get().front()->GetGen());
    }

    CRef<objects::CSubmit_block> block = parent->GetSubmitBlock();
    string label = CSubmitBlockDlg::GetBlockProblems(block);
    string err = CSubmitBlockDlg::GetCitGenProblems(gen);
    if (!NStr::IsBlank(err)) {
        if (!NStr::IsBlank(label)) {
            label += " ";
        }
        label += err;
    }

    string alt_email = parent->GetAltEmailAddress();
    if (!IsValidEmail(alt_email)) {
        if (!NStr::IsBlank(label)) {
            label += " ";
        }
        label += "Valid alternate email address is missing";
    }
        
    if (NStr::IsBlank(label)) {
        label = kSubmitterInfoComplete;
        s_ShowStar (m_StarSubmitter, false);
    } else {
        x_SetSubmissionNotReady(label);
        s_ShowStar (m_StarSubmitter, true);
    }
    m_SubmitterLabel->SetLabel(ToWxString(label));
}



void CSubPrepIntroPanel::x_LaunchSubmitEditor()
{
    CSubPrep_panel* parent = x_GetParent();
    if (!parent) {
        return;
    }
    
    CRef<objects::CCit_gen> gen(new objects::CCit_gen());

    objects::CSeqdesc_CI orig_citsub = parent->GetCitSubPub();
    if (orig_citsub) {
        gen->Assign(orig_citsub->GetPub().GetPub().Get().front()->GetGen());
    }

    CRef<objects::CSubmit_block> orig_block = parent->GetSubmitBlock();
    string alt_email = parent->GetAltEmailAddress();

    CRef<objects::CSubmit_block> new_block;
    CRef<objects::CCit_gen> new_gen;
    CSubmitBlockDlg dlg (NULL, orig_block, gen, m_Workbench);
    dlg.SetAlternateEmailAddress(alt_email);
    // first time, require user to select release date
    if (!NStr::Equal("Yes", parent->GetWizardField(kReleaseDateConfirmed))) {
        dlg.UnselectReleaseDateChoice();
    }


    bool done = false;
    while (!done) {
        if (dlg.ShowModal() == wxID_OK) {
            new_block = dlg.GetSubmitBlock();
            new_gen = dlg.GetCitGen();
            alt_email = dlg.GetAlternateEmailAddress();
            if (new_block && new_gen && IsValidEmail(alt_email)) {
                dlg.Close();        
                done = true;
            } else {
                string error = dlg.GetErrors();
                if (!IsValidEmail(alt_email)) {
                    if (!NStr::IsBlank(error)) {
                        error += " ";
                    }
                    error += "You must provide a valid alternate email address.";
                }
                wxMessageBox(ToWxString(error), wxT("Error"),
                         wxOK | wxICON_ERROR, this);
                dlg.SetPageForError(error);
                new_block.Reset();
                new_gen.Reset();
            }
        } else {
            done = true;
        }
    }

    x_UpdateSubmitBlock(new_block, new_gen, alt_email);
}


/*!
 * wxEVT_LEFT_DOWN event handler for wxID_STATIC
 */

void CSubPrepIntroPanel::OnClickSubmitterSummary( wxMouseEvent& event )
{
    x_LaunchSubmitEditor(); 
}


/*!
 * wxEVT_COMMAND_HYPERLINK event handler for ID_HYPERLINKCTRL5
 */

void CSubPrepIntroPanel::OnEditSubmitterInfoClicked( wxHyperlinkEvent& event )
{
    x_LaunchSubmitEditor(); 
}


CSourceRequirements::EWizardType CSubPrepIntroPanel::x_GetWizardTypeFromSelection (int sel)
{
    CSourceRequirements::EWizardType wizard_type = CSourceRequirements::eWizardType_standard;

    switch (sel) {
        case 1:
            wizard_type = CSourceRequirements::eWizardType_uncultured_samples;
            break;
        case 2:
            wizard_type = CSourceRequirements::eWizardType_viruses;
            break;
        case 3:
            wizard_type = CSourceRequirements::eWizardType_rrna_its_igs;
            break;
        case 4:
            wizard_type = CSourceRequirements::eWizardType_tsa;
            break;
        case 5:
            wizard_type = CSourceRequirements::eWizardType_igs;
            break;
        case 6:
            wizard_type = CSourceRequirements::eWizardType_microsatellite;
            break;
        case 7:
            wizard_type = CSourceRequirements::eWizardType_d_loop;
            break;
        case 0:
        default:
            wizard_type = CSourceRequirements::eWizardType_standard;
            break;
    }
    return wizard_type;

}


CSourceRequirements::EWizardType CSubPrepIntroPanel::GetWizardTypeFromCtrl ()
{
    return x_GetWizardTypeFromSelection(m_SubmissionType->GetSelection());
}


void CSubPrepIntroPanel::x_SetIntroText(CSourceRequirements::EWizardType wizard_type)
{
    // set introductory text
    switch (wizard_type) {
        case CSourceRequirements::eWizardType_standard:
            m_IntroText->SetLabel(s_DefaultIntroText + s_VectorScreenText);
            break;
        case CSourceRequirements::eWizardType_uncultured_samples:
            m_IntroText->SetLabel(s_UnculturedSamplesIntroText + s_VectorScreenText);
            break;
        case CSourceRequirements::eWizardType_rrna_its_igs:
            m_IntroText->SetLabel(s_rRNA_ITS_IGSIntroText + s_VectorScreenText);
            break;
        case CSourceRequirements::eWizardType_igs:
            m_IntroText->SetLabel(s_IGSIntroText + s_VectorScreenText);
            break;
        case CSourceRequirements::eWizardType_d_loop:
            m_IntroText->SetLabel(s_DLoopIntroText + s_VectorScreenText);
            break;
        case CSourceRequirements::eWizardType_tsa:
            m_IntroText->SetLabel(s_TSAIntroText + s_VectorScreenText);
            break;
        case CSourceRequirements::eWizardType_viruses:
            m_IntroText->SetLabel(s_VirusesIntroText + s_VectorScreenText);
            break;
        case CSourceRequirements::eWizardType_microsatellite:
            m_IntroText->SetLabel(s_MicrosatelliteIntroText + s_VectorScreenText);
            break;
    }
}


void CSubPrepIntroPanel::SetWizardTypeCtrl()
{
    // require user to select
    string field = "";
    CSubPrep_panel* parent = x_GetParent();
    if (parent) {
        field = parent->GetWizardTypeField();
    }
    if (NStr::IsBlank(field)) {
        s_ShowStar(m_StarType, true);
        parent->SetSubmissionNotReady("Must select wizard type");
    } else {
        s_ShowStar(m_StarType, false);
    }
    CSourceRequirements::EWizardType wizard_type = GetWizardTypeFromName(field);
    
    m_SubmissionType->SetStringSelection(ToWxString (field));
    x_SetIntroText(wizard_type);
}


/*!
 * wxEVT_COMMAND_LISTBOX_SELECTED event handler for ID_SUBMISSION_TYPE
 */

void CSubPrepIntroPanel::OnSubmissionTypeSelected( wxCommandEvent& event )
{
    CSubPrep_panel* parent = x_GetParent();
    if (!parent) {
        return;
    }
    CSourceRequirements::EWizardType wizard_type = GetWizardTypeFromCtrl ();

    CSourceRequirements::EWizardType new_wizard_type = parent->SetWizardType(wizard_type);
    if (new_wizard_type != wizard_type) {
        m_SubmissionType->SetStringSelection(ToWxString (CSubPrep_panel::GetWizardTypeName(new_wizard_type)));
    }
    x_SetIntroText(wizard_type);
    s_ShowStar(m_StarType, false);
}


/*!
 * wxEVT_COMMAND_TEXT_URL event handler for ID_INTRO_TEXT
 */

void CSubPrepIntroPanel::OnIntroTextClickUrl( wxTextUrlEvent& event )
{
    if (event.GetMouseEvent().ButtonDown()) {
        wxTextCtrl* text_ctrl = dynamic_cast<wxTextCtrl*>(event.GetEventObject());
        if (text_ctrl) {
            wxString str = text_ctrl->GetValue();
            wxString url = str.substr(event.GetURLStart(), event.GetURLEnd() - event.GetURLStart() + 1); 
            CAppPopup::PopupURL(ToStdString(url));
        }
    }
}


bool CSubPrepIntroPanel::IsComplete()
{
    if (m_SubmissionType->GetSelection() < 0) {
        return false;
    }
    string label = ToStdString(m_SubmitterLabel->GetLabel());
    if (NStr::Equal(label, kSubmitterInfoComplete)) {
        return true;
    } else {
        return false;
    }
}


END_NCBI_SCOPE
