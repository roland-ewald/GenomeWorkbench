#ifndef GUI_WIDGETS_EDIT___FEATURE_FIELD_NAME_PANEL__HPP
#define GUI_WIDGETS_EDIT___FEATURE_FIELD_NAME_PANEL__HPP
/*  $Id: feature_field_name_panel.hpp 44636 2020-02-11 20:00:50Z asztalos $
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
// Generated by DialogBlocks (unregistered), 10/06/2013 17:47:10

#include <corelib/ncbistd.hpp>
#include <objects/seqfeat/Genetic_code_table.hpp>
#include <gui/widgets/edit/field_name_panel.hpp>
#include <gui/widgets/edit/feature_type_panel.hpp>

/*!
 * Includes
 */

////@begin includes
////@end includes

#include <wx/listbox.h>
#include <wx/stattext.h>

/*!
 * Forward declarations
 */

////@begin forward declarations
class CFeatureTypePanel;
////@end forward declarations

BEGIN_NCBI_SCOPE

/*!
 * Control identifiers
 */

////@begin control identifiers
#define SYMBOL_CFEATUREFIELDNAMEPANEL_STYLE wxTAB_TRAVERSAL
#define SYMBOL_CFEATUREFIELDNAMEPANEL_TITLE _("FeatureFieldNamePanel")
#define SYMBOL_CFEATUREFIELDNAMEPANEL_IDNAME ID_CFEATUREFIELDNAMEPANEL
#define SYMBOL_CFEATUREFIELDNAMEPANEL_SIZE wxDefaultSize
#define SYMBOL_CFEATUREFIELDNAMEPANEL_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * CFeatureFieldNamePanel class declaration
 */

class NCBI_GUIWIDGETS_EDIT_EXPORT CFeatureFieldNamePanel : public CFieldNamePanel, public CFieldNamePanelParent
{    
    DECLARE_DYNAMIC_CLASS( CFeatureFieldNamePanel )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    CFeatureFieldNamePanel();
    CFeatureFieldNamePanel( wxWindow* parent, CFeatureFieldNamePanel* sibling = NULL, 
        wxWindowID id = SYMBOL_CFEATUREFIELDNAMEPANEL_IDNAME, 
        const wxPoint& pos = SYMBOL_CFEATUREFIELDNAMEPANEL_POSITION, 
        const wxSize& size = SYMBOL_CFEATUREFIELDNAMEPANEL_SIZE, 
        long style = SYMBOL_CFEATUREFIELDNAMEPANEL_STYLE );

    /// Creation
    bool Create( wxWindow* parent, 
        wxWindowID id = SYMBOL_CFEATUREFIELDNAMEPANEL_IDNAME, 
        const wxPoint& pos = SYMBOL_CFEATUREFIELDNAMEPANEL_POSITION, 
        const wxSize& size = SYMBOL_CFEATUREFIELDNAMEPANEL_SIZE, 
        long style = SYMBOL_CFEATUREFIELDNAMEPANEL_STYLE );

    /// Destructor
    ~CFeatureFieldNamePanel();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin CFeatureFieldNamePanel event handler declarations

    /// wxEVT_COMMAND_LISTBOX_SELECTED event handler for ID_QUALIFIER_LISTBOX
    void OnQualifierListboxSelected( wxCommandEvent& event );

    // triggers the event of populating the listbox with the relevant features first
    void PopulateFeatureListbox(void);
////@end CFeatureFieldNamePanel event handler declarations

////@begin CFeatureFieldNamePanel member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end CFeatureFieldNamePanel member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin CFeatureFieldNamePanel member variables
    wxStaticText* m_FeatureTypeLabel;
    CFeatureTypePanel* m_FeatureType;
    wxListBox* m_QualifierName;
////@end CFeatureFieldNamePanel member variables

    string GetFeatureType();
    bool SetFeatureType(const string& feature_type);
    string GetQualifierName();
    virtual string GetFieldName(const bool subfield = false);
    virtual bool SetFieldName(const string& field);
    virtual string GetMacroFieldName(const string &target, const string& selected_field = kEmptyStr);

    CFeatureTypePanel* GetFeatureTypePanel(void) {return m_FeatureType;}
    enum {
        ID_CFEATUREFIELDNAMEPANEL = 6110,
        ID_FEATQUALIFIER_LISTBOX
    };
    virtual void ClearValues(void);
    virtual vector<string> GetChoices(bool& allow_other);
    void ListPresentFeaturesFirst(objects::CSeq_entry_Handle seh, vector<const objects::CFeatListItem *> *featlist = nullptr);
    virtual void UpdateEditor();
    virtual void SetShowLegalOnly(bool show);

    static wxArrayString s_FillFeatQualList(objects::CSeqFeatData::ESubtype subtype);

private:
    CFeatureFieldNamePanel* m_Sibling;
    const objects::CGenetic_code_table& m_code_table;
    bool m_show_legal_only;
};


DECLARE_EXPORTED_EVENT_TYPE(NCBI_GUIWIDGETS_EDIT_EXPORT, wxEVT_COMMAND_UPDATE_FEATLIST, wxCommandEvent);

typedef void (wxEvtHandler::*CUpdateFeatListEventFunction)(wxCommandEvent&);

#define CUpdateFeatListEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(CUpdateFeatListEventFunction, &func)

#define EVT_UPDATE_FEATURE_LIST(id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_UPDATE_FEATLIST, id, CUpdateFeatListEventHandler(fn))

END_NCBI_SCOPE

#endif
    // GUI_WIDGETS_EDIT___FEATURE_FIELD_NAME_PANEL__HPP