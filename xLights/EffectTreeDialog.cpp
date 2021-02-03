/***************************************************************
 * This source files comes from the xLights project
 * https://www.xlights.org
 * https://github.com/smeighan/xLights
 * See the github commit history for a record of contributing
 * developers.
 * Copyright claimed based on commit dates recorded in Github
 * License: https://github.com/smeighan/xLights/blob/master/License.txt
 **************************************************************/

//(*InternalHeaders(EffectTreeDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include <wx/persist/toplevel.h>
#include <wx/busyinfo.h>
#include <wx/utils.h>
#include <wx/artprov.h>

#include "EffectTreeDialog.h"
#include "xLightsMain.h"
#include "xLightsVersion.h"
#include "UtilFunctions.h"

#include <log4cpp/Category.hh>

//(*IdInit(EffectTreeDialog)
const long EffectTreeDialog::ID_TREECTRL1 = wxNewId();
const long EffectTreeDialog::ID_STATICBITMAP_GIF = wxNewId();
const long EffectTreeDialog::ID_BUTTON6 = wxNewId();
const long EffectTreeDialog::ID_BUTTON1 = wxNewId();
const long EffectTreeDialog::ID_BUTTON2 = wxNewId();
const long EffectTreeDialog::ID_BUTTON7 = wxNewId();
const long EffectTreeDialog::ID_BUTTON3 = wxNewId();
const long EffectTreeDialog::ID_BUTTON4 = wxNewId();
const long EffectTreeDialog::ID_BUTTON5 = wxNewId();
const long EffectTreeDialog::ID_BUTTON8 = wxNewId();
const long EffectTreeDialog::ID_TEXTCTRL_SEARCH = wxNewId();
const long EffectTreeDialog::ID_BUTTON_SEARCH = wxNewId();
const long EffectTreeDialog::ID_TIMER_GIF = wxNewId();
//*)

BEGIN_EVENT_TABLE(EffectTreeDialog,wxDialog)
	//(*EventTable(EffectTreeDialog)
	//*)
END_EVENT_TABLE()

#define MIN_PREVIEW_SIZE 64
#define MAX_PREVIEW_SIZE 256

EffectTreeDialog::EffectTreeDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size):
    frameCount(0)
{
	//(*Initialize(EffectTreeDialog)
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer2;
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer3;
	wxStdDialogButtonSizer* StdDialogButtonSizer1;

	Create(parent, wxID_ANY, _("Effect Presets"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER, _T("wxID_ANY"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(0);
	FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer2->AddGrowableCol(0);
	FlexGridSizer2->AddGrowableRow(0);
	TreeCtrl1 = new wxTreeCtrl(this, ID_TREECTRL1, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE, wxDefaultValidator, _T("ID_TREECTRL1"));
	TreeCtrl1->SetMinSize(wxDLG_UNIT(this,wxSize(80,-1)));
	FlexGridSizer2->Add(TreeCtrl1, 1, wxALL|wxEXPAND, 5);
	FlexGridSizer3 = new wxFlexGridSizer(2, 1, 0, 0);
	FlexGridSizer3->AddGrowableCol(0);
	FlexGridSizer3->AddGrowableRow(0);
	StaticBitmapGif = new wxStaticBitmap(this, ID_STATICBITMAP_GIF, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP_GIF"));
	FlexGridSizer3->Add(StaticBitmapGif, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	btApply = new wxButton(this, ID_BUTTON6, _("&Apply Preset"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
	btApply->SetToolTip(_("Apply the selected effect Preset."));
	BoxSizer1->Add(btApply, 0, wxALL|wxEXPAND, 5);
	btNewPreset = new wxButton(this, ID_BUTTON1, _("&New Preset"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	btNewPreset->SetToolTip(_("Create New Effect Preset from current settings."));
	BoxSizer1->Add(btNewPreset, 0, wxALL|wxEXPAND, 5);
	btUpdate = new wxButton(this, ID_BUTTON2, _("&Update Preset"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	btUpdate->SetToolTip(_("Update the selected effect preset to reflect current effect settings."));
	BoxSizer1->Add(btUpdate, 0, wxALL|wxEXPAND, 5);
	btAddGroup = new wxButton(this, ID_BUTTON7, _("Add &Group"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
	btAddGroup->SetToolTip(_("Add effect preset group."));
	BoxSizer1->Add(btAddGroup, 0, wxALL|wxEXPAND, 5);
	btRename = new wxButton(this, ID_BUTTON3, _("&Rename"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	btRename->SetToolTip(_("Rename currently selected effect preset."));
	BoxSizer1->Add(btRename, 0, wxALL|wxEXPAND, 5);
	btDelete = new wxButton(this, ID_BUTTON4, _("&Delete"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	btDelete->SetToolTip(_("Delete curently selected effect preset."));
	BoxSizer1->Add(btDelete, 0, wxALL|wxEXPAND, 5);
	btExport = new wxButton(this, ID_BUTTON5, _("Export"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
	BoxSizer1->Add(btExport, 0, wxALL|wxEXPAND, 5);
	btImport = new wxButton(this, ID_BUTTON8, _("&Import"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON8"));
	btImport->SetToolTip(_("Import presets from another file."));
	BoxSizer1->Add(btImport, 0, wxALL|wxEXPAND, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL_SEARCH, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL_SEARCH"));
	BoxSizer2->Add(TextCtrl1, 1, wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	ETButton1 = new wxButton(this, ID_BUTTON_SEARCH, _("Search"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT, wxDefaultValidator, _T("ID_BUTTON_SEARCH"));
	BoxSizer2->Add(ETButton1, 0, wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxFIXED_MINSIZE, 0);
	BoxSizer1->Add(BoxSizer2, 0, wxALL|wxEXPAND, 5);
	FlexGridSizer3->Add(BoxSizer1, 1, wxALL|wxEXPAND, 5);
	FlexGridSizer2->Add(FlexGridSizer3, 1, wxALL|wxEXPAND, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxEXPAND, 5);
	StdDialogButtonSizer1 = new wxStdDialogButtonSizer();
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_OK, wxEmptyString));
	StdDialogButtonSizer1->Realize();
	FlexGridSizer1->Add(StdDialogButtonSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	TimerGif.SetOwner(this, ID_TIMER_GIF);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_TREECTRL1,wxEVT_COMMAND_TREE_BEGIN_DRAG,(wxObjectEventFunction)&EffectTreeDialog::OnTreeCtrl1BeginDrag);
	Connect(ID_TREECTRL1,wxEVT_COMMAND_TREE_END_DRAG,(wxObjectEventFunction)&EffectTreeDialog::OnTreeCtrl1EndDrag);
	Connect(ID_TREECTRL1,wxEVT_COMMAND_TREE_ITEM_ACTIVATED,(wxObjectEventFunction)&EffectTreeDialog::OnTreeCtrl1ItemActivated);
	Connect(ID_TREECTRL1,wxEVT_COMMAND_TREE_SEL_CHANGED,(wxObjectEventFunction)&EffectTreeDialog::OnTreeCtrl1SelectionChanged);
	Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EffectTreeDialog::OnbtApplyClick);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EffectTreeDialog::OnbtNewPresetClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EffectTreeDialog::OnbtUpdateClick);
	Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EffectTreeDialog::OnbtAddGroupClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EffectTreeDialog::OnbtRenameClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EffectTreeDialog::OnbtDeleteClick);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EffectTreeDialog::OnbtExportClick);
	Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EffectTreeDialog::OnbtImportClick);
	Connect(ID_TEXTCTRL_SEARCH,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&EffectTreeDialog::OnTextCtrl1TextEnter);
	Connect(ID_BUTTON_SEARCH,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EffectTreeDialog::OnETButton1Click);
	Connect(ID_TIMER_GIF,wxEVT_TIMER,(wxObjectEventFunction)&EffectTreeDialog::OnTimerGifTrigger);
	//*)

    treeRootID = TreeCtrl1->AddRoot("Effect Presets");
    xLightParent = (xLightsFrame*)parent;

    // remember dialog size/location
    if (!wxPersistentRegisterAndRestore(this, "xLights.EffectTreeDialog")) {
        // defaults if this hasn't already been persisted
        SetSize(700, 500);
        CenterOnScreen();
    }


    // Get the optimal preview size based on current dialog size
    int previewSize = GetOptimalPreviewSize();
    
    // Set size for bitmap widget and blank image to optimal size so the dialog
    // doesn't jump around when first preset is loaded
    StaticBitmapGif->SetSize(wxSize(previewSize, previewSize));
    _blankGIFImage = std::make_unique<wxBitmap>(previewSize, previewSize, true);
    StaticBitmapGif->SetBitmap(*_blankGIFImage.get());

    StaticBitmapGif->SetMinSize(wxSize(previewSize, previewSize));
    StaticBitmapGif->SetMaxSize(wxSize(MAX_PREVIEW_SIZE, MAX_PREVIEW_SIZE));
    
    Layout();

    ValidateWindow();
}

EffectTreeDialog::~EffectTreeDialog()
{
    StaticBitmapGif->SetBitmap(wxNullBitmap);

    //(*Destroy(EffectTreeDialog)
	//*)
}

void EffectTreeDialog::InitItems(wxXmlNode *EffectsNode)
{
    wxString name;
    wxTreeItemId curGroupID;
    XrgbEffectsNode = EffectsNode;

    TreeCtrl1->SetItemData( treeRootID, new MyTreeItemData(EffectsNode, true));

    for(wxXmlNode *ele = EffectsNode->GetChildren(); ele!=nullptr; ele=ele->GetNext() )
    {
        if (ele->GetName() == "effectGroup")
        {
            name = ele->GetAttribute("name");
            curGroupID = TreeCtrl1->AppendItem(treeRootID, name,-1,-1,new MyTreeItemData (ele, true));
            TreeCtrl1->SetItemHasChildren(curGroupID);
            AddTreeElementsRecursive(ele, curGroupID);
        }
        else if (ele->GetName() == "effect")
        {
            if (ele->GetAttribute("settings").Contains("\t"))
            {
                name = ele->GetAttribute("name");
                name += " [" + ParseLayers(name, ele->GetAttribute("settings")) + ", " + ParseDuration(name, ele->GetAttribute("settings")) + "ms]";
                if (!name.IsEmpty())
                {
                    TreeCtrl1->AppendItem(treeRootID, name, -1, -1, new MyTreeItemData(ele));
                }
            }
        }
    }

	TreeCtrl1->Expand(treeRootID);
    ValidateWindow();
}

void EffectTreeDialog::AddTreeElementsRecursive(wxXmlNode *EffectsNode, wxTreeItemId curGroupID)
{
    wxString name;
    wxTreeItemId nextGroupID;

    for(wxXmlNode *ele = EffectsNode->GetChildren(); ele!=nullptr; ele=ele->GetNext() )
    {
        if (ele->GetName() == "effect")
        {
            name=ele->GetAttribute("name");
            if (!name.IsEmpty())
            {
                name += " [" + ParseLayers(name, ele->GetAttribute("settings")) + ", " + ParseDuration(name, ele->GetAttribute("settings")) + "ms]";
                TreeCtrl1->AppendItem(curGroupID, name,-1,-1, new MyTreeItemData(ele));
            }
        }
        else if (ele->GetName() == "effectGroup")
        {
            name=ele->GetAttribute("name");
            if (!name.IsEmpty())
            {
                nextGroupID = TreeCtrl1->AppendItem(curGroupID, name,-1,-1,new MyTreeItemData (ele, true));
                TreeCtrl1->SetItemHasChildren(nextGroupID);
                AddTreeElementsRecursive(ele, nextGroupID);
            }
        }
    }
}

void EffectTreeDialog::ApplyEffect(bool dblClick)
{
    wxTreeItemId itemID = TreeCtrl1->GetSelection();
    if (!itemID.IsOk())
    {
         DisplayError(_("No effect selected."), this);
    }
    else if (TreeCtrl1->HasChildren(itemID))
    {
        if (dblClick)
        {
            TreeCtrl1->Toggle(itemID);
        }
        else
        {
            DisplayError(_("An effect group can not be applied."), this);
        }
    }
    else
    {
        MyTreeItemData *item = (MyTreeItemData *)TreeCtrl1->GetItemData(itemID);
        if ( item != nullptr )
        {
            wxXmlNode *ele = item->GetElement();
            wxString settings = ele->GetAttribute("settings");
            if (!settings.IsEmpty())
            {
                xLightParent->ApplyEffectsPreset(settings, ele->GetAttribute("xLightsVersion", "4.0"));
            }
        }
    }
}

void EffectTreeDialog::OnbtApplyClick(wxCommandEvent& event)
{
    ApplyEffect();
    ValidateWindow();
}

wxXmlNode* EffectTreeDialog::CreateEffectGroupNode(wxString& name)
{
    wxXmlNode* NewXml=new wxXmlNode(wxXML_ELEMENT_NODE, "effectGroup");
    NewXml->AddAttribute("name", name);
    return NewXml;
}

bool EffectTreeDialog::PromptForName(wxWindow* parent, wxString *name, wxString prompt, wxString errorMsg)
{
    wxTextEntryDialog dialog(/*this*/ parent,prompt,_("Name"));
    int DlgResult;
    bool ok;
    do
    {
        ok=true;
        DlgResult=dialog.ShowModal();
        if (DlgResult == wxID_OK)
        {
            // validate inputs
            *name=dialog.GetValue();
            name->Trim();
            if ((name->IsEmpty() && !errorMsg.IsEmpty()) || name->Contains('&') || name->Contains('<') || name->Contains('>')) // !errorMsg => empty is allowed -DJ
            {
                ok=false;
                DisplayError(errorMsg);
            }
        }
    }
    while (DlgResult == wxID_OK && !ok);
    return (DlgResult == wxID_OK );
}
void EffectTreeDialog::OnbtNewPresetClick(wxCommandEvent& event)
{
    wxTreeItemId itemID = TreeCtrl1->GetSelection();
    wxTreeItemId parentID;
    MyTreeItemData *parentData;

    if (!itemID.IsOk())
    {
        DisplayError(_("A preset cannot be added at the currently selected location"), this);
        ValidateWindow();
        return;
    }
    wxString prompt = "Enter effect preset name";
    wxString errMsg = "Effect preset name may not be empty not contain &<>";
    wxString name;
    if (!PromptForName(this, &name, prompt, errMsg)) return;

    MyTreeItemData *itemData = (MyTreeItemData *)TreeCtrl1->GetItemData(itemID);
    if (itemData->IsGroup())
    {
        parentID = itemID;
        parentData = itemData;
    }
    else
    {
        parentID = TreeCtrl1->GetItemParent(itemID);
        parentData = (MyTreeItemData *)TreeCtrl1->GetItemData(parentID);
    }

    wxXmlNode *node = parentData->GetElement();
    wxXmlNode *newNode = xLightParent->CreateEffectNode(name);
    node->AddChild(newNode);
    name += " [" + ParseLayers(name, newNode->GetAttribute("settings")) + ", " + ParseDuration(name, newNode->GetAttribute("settings")) + "ms]";
    wxTreeItemId newitemID = TreeCtrl1->AppendItem(parentID, name, -1,-1, new MyTreeItemData(newNode));
    TreeCtrl1->Expand(parentID);
    TreeCtrl1->SelectItem(newitemID, true);
    TreeCtrl1->EnsureVisible(newitemID);
    GenerateGifImage(newitemID, true);
    EffectsFileDirty();
    ValidateWindow();
}

wxString EffectTreeDialog::ParseLayers(wxString name, wxString settings)
{
    if (settings == "") return "0";

    //static log4cpp::Category &logger_base = log4cpp::Category::getInstance(std::string("log_base"));
    //logger_base.debug("Name: %s", (const char *)name.c_str());
    //logger_base.debug("Settings: %s", (const char *)settings.c_str());
    int res = 0;
    bool ac = false;

    if (settings.Contains("\t"))
    {
        int start = 9999;
        int end = -1;

        wxArrayString all_efdata = wxSplit(settings, '\n');

        bool cf1 = false;
        for (int i = 0; i < all_efdata.size(); i++)
        {
            //logger_base.debug("    %d: %s", i, (const char *)all_efdata[i].c_str());

            wxArrayString efdata = wxSplit(all_efdata[i], '\t');

            if (efdata.size() > 0)
            {
                if (efdata[0] == "CopyFormat1")
                {
                    cf1 = true;
                }
                else if (efdata[0] == "CopyFormatAC")
                {
                    ac = true;
                    start = wxAtoi(efdata[7]);
                    end = wxAtoi(efdata[8]);
                    break;
                }
                else
                {
                    if (cf1 && efdata.size() > 6 && efdata[0] != "CopyFormat1" && efdata[0] != "None" && efdata.back() != "NO_PASTE_BY_CELL")
                    {
                        int row = wxAtoi(efdata[efdata.size() - 6]);
                        if (row < start) start = row;
                        if (row > end) end = row;
                        //logger_base.debug("        row: %d start: %d end: %d", row, start, end);
                    }
                    else if (!cf1 && efdata.size() > 2 && efdata[0] != "None")
                    {
                        int row = wxAtoi(efdata[efdata.size() - 2]);
                        if (row < start) start = row;
                        if (row > end) end = row;
                        //logger_base.debug("        row: %d start: %d end: %d", row, start, end);
                    }
                    else if (efdata.back() == "NO_PASTE_BY_CELL" && efdata.size() > 3 && efdata[0] != "None")
                    {
                        int row = wxAtoi(efdata[efdata.size() - 3]);
                        if (row < start) start = row;
                        if (row > end) end = row;
                        //logger_base.debug("        row: %d start: %d end: %d", row, start, end);
                    }
                }
            }
        }

        if (end != -1)
        {
            res = end - start + 1;
        }
    }
    else
    {
        // effect1,effect2,blend,settings ...
        wxArrayString efdata = wxSplit(settings, ',');
        if (efdata.size() < 2) return "0";
        if (efdata[0] != "None") res++;
        if (efdata[1] != "None") res++;
    }

    //logger_base.debug("    **** %d", res);

    if (ac)
    {
        return wxString::Format("%d - AC", res);
    }
    else
    {
        return wxString::Format("%d", res);
    }
}

wxString StripLayers(wxString s)
{
    wxString res = s;
    if (s.EndsWith("]"))
    {
        res = s.BeforeLast('[');
        if (res.EndsWith(" "))
        {
            res = res.BeforeLast(' ');
        }
    }

    return res;
}

wxString EffectTreeDialog::ParseDuration(wxString name, wxString settings)
{
    if (settings == "") return "0";

    //static log4cpp::Category &logger_base = log4cpp::Category::getInstance(std::string("log_base"));
    //logger_base.debug("Name: %s", (const char *)name.c_str());
    //logger_base.debug("Settings: %s", (const char *)settings.c_str());
    int minstart = 99999999;
    int maxend = -99999999;

    if (settings.Contains("\t"))
    {
        wxArrayString all_efdata = wxSplit(settings, '\n');

        bool cf1 = false;
        for (int i = 0; i < all_efdata.size(); i++)
        {
            //logger_base.debug("    %d: %s", i, (const char *)all_efdata[i].c_str());

            wxArrayString efdata = wxSplit(all_efdata[i], '\t');

            if (efdata.size() > 0)
            {
                if (efdata[0] == "CopyFormat1")
                {
                    cf1 = true;
                }
                else if (efdata.size() > 10 && efdata[0] == "CopyFormatAC")
                {
                    int start = wxAtoi(efdata[9]);
                    int end = wxAtoi(efdata[10]);
                    minstart = std::min(start, minstart);
                    maxend = std::max(end, maxend);
                    break;
                }
                else
                {
                    if (efdata.size() > 4 && efdata[0] != "CopyFormat1" && efdata[0] != "None")
                    {
                        int start = wxAtoi(efdata[3]);
                        int end = wxAtoi(efdata[4]);
                        minstart = std::min(start, minstart);
                        maxend = std::max(end, maxend);
                    }
                    else if (efdata[0] != "None")
                    {
                        wxASSERT(false);
                    }
                }
            }
        }
    }
    else
    {
        // effect1,effect2,blend,settings ...
        wxArrayString efdata = wxSplit(settings, ',');
        if (efdata.size() < 5) return "0";
        minstart = wxAtoi(efdata[3]);
        maxend = wxAtoi(efdata[4]);
    }

    if (minstart == 99999999) return "0";

    return wxString::Format("%d", maxend - minstart);
}

void EffectTreeDialog::OnbtUpdateClick(wxCommandEvent& event)
{
    wxTreeItemId itemID = TreeCtrl1->GetSelection();
    wxString name(TreeCtrl1->GetItemText(itemID));

    if ( TreeCtrl1->HasChildren(itemID))
    {
        wxMessageBox(_("You cannot store an effect on the selected item."), _("ERROR"));
        ValidateWindow();
        return;
    }
    MyTreeItemData *selData = (MyTreeItemData *)TreeCtrl1->GetItemData(itemID);
    wxXmlNode *xml_node=selData->GetElement();

    xml_node->DeleteAttribute("settings");
    xLightParent->UpdateEffectNode(xml_node);

    TreeCtrl1->SetItemText(itemID, StripLayers(name) + " [" + ParseLayers(StripLayers(name), xml_node->GetAttribute("settings")) + ", " + ParseDuration(StripLayers(name), xml_node->GetAttribute("settings")) + "ms]");

    EffectsFileDirty();
    ValidateWindow();

    GenerateGifImage(itemID, true);
}

void EffectTreeDialog::OnbtRenameClick(wxCommandEvent& event)
{
    wxTreeItemId itemID = TreeCtrl1->GetSelection();
    if (!itemID.IsOk())
    {
        DisplayError(_("You Cannot rename this item"), this);
        ValidateWindow();
        return;
    }

    wxString prompt = "Enter new effect preset name";
    wxString errMsg = "Effect preset name may not be empty or contain &<>";
    wxString newName;
    if (!PromptForName(this, &newName, prompt, errMsg)) return;

    DeleteGifImage(itemID);

    MyTreeItemData *itemData= (MyTreeItemData *)TreeCtrl1->GetItemData(itemID);
    wxXmlNode* e=(wxXmlNode*)itemData->GetElement();
    e->DeleteAttribute("name");
    e->AddAttribute("name",newName);
    if (!itemData->IsGroup())
    {
        newName += " [" + ParseLayers(newName, e->GetAttribute("settings")) + ", " + ParseDuration(newName, e->GetAttribute("settings")) + "ms]";
    }

    TreeCtrl1->SetItemText(itemID, newName);
    GenerateGifImage(itemID, true);
    EffectsFileDirty();
    ValidateWindow();
}

void EffectTreeDialog::OnbtDeleteClick(wxCommandEvent& event)
{
    std::lock_guard<std::mutex> lock(preset_mutex);

    wxTreeItemId itemID = TreeCtrl1->GetSelection();
    wxTreeItemId parentID;

    if( !itemID.IsOk() || itemID == treeRootID )
    {
        DisplayError(_("You cannot delete this item"), this);
        ValidateWindow();
        return;
    }
    DeleteGifImage(itemID);
    parentID = TreeCtrl1->GetItemParent(itemID);
    MyTreeItemData *parentData=(MyTreeItemData *)TreeCtrl1->GetItemData(parentID);
    wxXmlNode *pnode=parentData->GetElement();

    MyTreeItemData *selData = (MyTreeItemData *)TreeCtrl1->GetItemData(itemID);
    wxXmlNode *oldXml=selData->GetElement();

    pnode->RemoveChild(oldXml);
    delete oldXml;

    TreeCtrl1->Delete(itemID);
    EffectsFileDirty();
    ValidateWindow();
}

void EffectTreeDialog::OnbtAddGroupClick(wxCommandEvent& event)
{
    wxTreeItemId itemID = TreeCtrl1->GetSelection();
    wxTreeItemId parentID;
    MyTreeItemData *parentData;
    wxString prompt = "Enter effect group name";
    wxString errMsg = "Effect group name may not be empty or contain &<>";
    wxString name;
    if (!PromptForName(this, &name, prompt, errMsg)) return;

    // update Choice_Presets
    MyTreeItemData *itemData=(MyTreeItemData *)TreeCtrl1->GetItemData(itemID);
    if( itemData->IsGroup() )
    {
        parentID = itemID;
        parentData = itemData;
    }
    else
    {
        parentID = TreeCtrl1->GetItemParent(itemID);
        parentData=(MyTreeItemData *)TreeCtrl1->GetItemData(parentID);
    }

    wxXmlNode *node=parentData->GetElement();
    wxXmlNode *newNode=CreateEffectGroupNode(name);
    node->AddChild(newNode);
    itemID = TreeCtrl1->AppendItem(parentID, name, -1,-1, new MyTreeItemData(newNode, true));
    TreeCtrl1->SetItemHasChildren(itemID);
    TreeCtrl1->Expand(parentID);
    TreeCtrl1->SelectItem(itemID);
    TreeCtrl1->EnsureVisible(itemID);
    EffectsFileDirty();
    ValidateWindow();
}

void EffectTreeDialog::OnTreeCtrl1ItemActivated(wxTreeEvent& event)
{
    ApplyEffect(true);
    ValidateWindow();
}

void EffectTreeDialog::EffectsFileDirty()
{
    xLightParent->GetOutputModelManager()->AddASAPWork(OutputModelManager::WORK_RGBEFFECTS_CHANGE, "EffectsFileDirty");
}

void EffectTreeDialog::OnButton_OKClick(wxCommandEvent& event)
{
    Show(false);
    ValidateWindow();
}

void EffectTreeDialog::OnTreeCtrl1BeginDrag(wxTreeEvent& event)
{
    wxTreeItemId itemID = event.GetItem();
    if( !TreeCtrl1->ItemHasChildren(itemID) )
    {
        m_draggedItem = event.GetItem();
        event.Allow();
    }
    ValidateWindow();
}

void EffectTreeDialog::OnTreeCtrl1EndDrag(wxTreeEvent& event)
{
    wxTreeItemId itemSrc = m_draggedItem,
                 itemDst = event.GetItem();
    m_draggedItem = (wxTreeItemId)0l;

    // where to copy the item?
    if ( itemDst.IsOk() && !TreeCtrl1->ItemHasChildren(itemDst) )
    {
        // copy to the parent then
        itemDst = TreeCtrl1->GetItemParent(itemDst);
    }

    if ( !itemDst.IsOk() )
    {
        ValidateWindow();
        return;
    }

    wxString name = TreeCtrl1->GetItemText(itemSrc);
    wxTreeItemId parentID = TreeCtrl1->GetItemParent(itemSrc);
    MyTreeItemData *parentData = (MyTreeItemData *)TreeCtrl1->GetItemData(parentID);
    wxXmlNode *pnode = parentData->GetElement();

    MyTreeItemData *selData = (MyTreeItemData *)TreeCtrl1->GetItemData(itemSrc);
    wxXmlNode *oldXml=selData->GetElement();

    MyTreeItemData *dstParentData = (MyTreeItemData *)TreeCtrl1->GetItemData(itemDst);
    wxXmlNode *dst_pnode = dstParentData->GetElement();

    pnode->RemoveChild(oldXml);
    dst_pnode->AddChild(oldXml);

    TreeCtrl1->Delete(itemSrc);

    wxTreeItemId itemID = TreeCtrl1->AppendItem(itemDst, name, -1,-1, new MyTreeItemData(oldXml));
    TreeCtrl1->Expand(itemDst);
    TreeCtrl1->SelectItem(itemID);
    TreeCtrl1->EnsureVisible(itemID);

    EffectsFileDirty();
    ValidateWindow();
}

void EffectTreeDialog::AddEffect(wxXmlNode* ele, wxTreeItemId curGroupID)
{
    MyTreeItemData *parentData;
    wxString name = ele->GetAttribute("name");
    wxString settings = ele->GetAttribute("settings");
    wxString version = ele->GetAttribute("version", "0000");
    wxString xlVer = ele->GetAttribute("xLightsVersion", "4.0");
    if (!name.IsEmpty())
    {
        parentData = (MyTreeItemData *)TreeCtrl1->GetItemData(curGroupID);
        wxXmlNode *node = parentData->GetElement();
        wxXmlNode *newNode = new wxXmlNode(wxXML_ELEMENT_NODE, "effect");
        newNode->AddAttribute("name", name);
        newNode->AddAttribute("settings", settings);
        newNode->AddAttribute("version", version);
        newNode->AddAttribute("xLightsVersion", xlVer);

        node->AddChild(newNode);
        name += " [" + ParseLayers(name, newNode->GetAttribute("settings")) + ", " + ParseDuration(name, newNode->GetAttribute("settings")) + "ms]";
        auto newItem = TreeCtrl1->AppendItem(curGroupID, name, -1, -1, new MyTreeItemData(newNode));
        TreeCtrl1->Expand(curGroupID);
        TreeCtrl1->SelectItem(newItem);
        TreeCtrl1->EnsureVisible(newItem);
    }
}

void EffectTreeDialog::AddGroup(wxXmlNode* ele, wxTreeItemId curGroupID)
{
    MyTreeItemData *parentData = (MyTreeItemData*)TreeCtrl1->GetItemData(curGroupID);
    wxString name = ele->GetAttribute("name");

    if (!name.IsEmpty())
    {
        wxXmlNode *node = parentData->GetElement();
        wxXmlNode *newNode = new wxXmlNode(wxXML_ELEMENT_NODE, "effectGroup");
        newNode->AddAttribute("name", name);
        node->AddChild(newNode);

        wxTreeItemId nextGroupID = TreeCtrl1->AppendItem(curGroupID, name, -1, -1, new MyTreeItemData(newNode, true));
        TreeCtrl1->SetItemHasChildren(nextGroupID);

        for (wxXmlNode *ele2 = ele->GetChildren(); ele2 != nullptr; ele2 = ele2->GetNext())
        {
            if (ele2->GetName() == "effect")
            {
                AddEffect(ele2, nextGroupID);
            }
            else if (ele2->GetName() == "effectGroup")
            {
                AddGroup(ele2, nextGroupID);
            }
        }
    }
}

void EffectTreeDialog::OnbtImportClick(wxCommandEvent& event)
{
    wxFileDialog* OpenDialog = new wxFileDialog( this, "Choose file to Import", wxEmptyString, wxEmptyString,
                                                "Preset files (*.xpreset)|*.xpreset|"
#ifdef __WXOSX__
                                                "Show files (*.xml)|*.xml",   //cannot filter by full name, only extension
#else
                                                "Show files (xlights_rgbeffects.xml)|xlights_rgbeffects.xml",
#endif
                                                wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_MULTIPLE, wxDefaultPosition);
    OpenDialog->SetDirectory(xLightParent->CurrentDir);
    if (OpenDialog->ShowModal() == wxID_OK)
    {
        wxTreeItemId id = TreeCtrl1->GetSelection();
        wxTreeItemId insertPoint = treeRootID;

        if ((id.IsOk() && id == treeRootID) || TreeCtrl1->HasChildren(id))
        {
            insertPoint = id;
        }
        else if (id.IsOk())
        {
            // if on an effect then add it to the same parent
            insertPoint = TreeCtrl1->GetItemParent(id);
        }

        wxString fDir = OpenDialog->GetDirectory();
        wxArrayString files;
        OpenDialog->GetFilenames(files);

        for (auto it = files.begin(); it != files.end(); ++it)
        {
            wxString filename = *it;
            wxFileName name_and_path(filename);
            name_and_path.SetPath(fDir);
            wxString file_to_import = name_and_path.GetFullPath();

            wxXmlDocument input_xml;
            if (!input_xml.Load(file_to_import)) {
                static log4cpp::Category &logger_base = log4cpp::Category::getInstance(std::string("log_base"));
                logger_base.warn("EffectTreeDialog::Unable to load %s to import presets.", (const char *)file_to_import.c_str());
                ValidateWindow();
                return;
            }

            bool presetFound = false;

            wxXmlNode* input_root = input_xml.GetRoot();

            if (name_and_path.GetExt().Lower() == "xpreset")
            {
                for (wxXmlNode *ele = input_root->GetChildren(); ele != nullptr; ele = ele->GetNext())
                {
                    if (ele->GetName() == "effectGroup")
                    {
                        AddGroup(ele, insertPoint);
                        presetFound = true;
                    }
                    else
                    {
                        AddEffect(ele, insertPoint);
                        presetFound = true;
                    }
                }
            }
            else
            {
                for (wxXmlNode* e = input_root->GetChildren(); e != nullptr; e = e->GetNext())
                {
                    if (e->GetName() == "effects")
                    {
                        for (wxXmlNode *ele = e->GetChildren(); ele != nullptr; ele = ele->GetNext())
                        {
                            if (ele->GetName() == "effectGroup")
                            {
                                AddGroup(ele, insertPoint);
                                presetFound = true;
                            }
                            else
                            {
                                AddEffect(ele, insertPoint);
                                presetFound = true;
                            }
                        }
                    }
                }
            }

            if (!presetFound)
            {
                DisplayError(wxString::Format("No presets found, Presets file %s is empty.\n", filename).ToStdString(), this);
                ValidateWindow();
                return;
            }
        }
        EffectsFileDirty();
    }
    ValidateWindow();
}

void EffectTreeDialog::WriteEffect(wxFile& f, wxXmlNode* n)
{
    f.Write("<effect name=\"" + StripLayers(n->GetAttribute("name")) + "\" settings=\""+XmlSafe(n->GetAttribute("settings").ToStdString())
            +"\" version=\""+n->GetAttribute("version")
            +"\" xLightsVersion=\""+n->GetAttribute("xLightsVersion", "4.0")
            +"\" />\n");
}

void EffectTreeDialog::WriteGroup(wxFile& f, wxXmlNode* n)
{
    f.Write("<effectGroup name=\"" + n->GetAttribute("name") + "\" >\n");
    for (auto it = n->GetChildren(); it != nullptr; it = it->GetNext())
    {
        if (it->GetName() == "effectGroup")
        {
            WriteGroup(f, it);
        }
        else
        {
            WriteEffect(f, it);
        }
    }
    f.Write("</effectGroup>\n");
}

void EffectTreeDialog::OnbtExportClick(wxCommandEvent& event)
{
    wxTreeItemId id = TreeCtrl1->GetSelection();
    if (!id.IsOk()) return;

    wxString name = TreeCtrl1->GetItemText(id);

    wxLogNull logNo; //kludge: avoid "error 0" message from wxWidgets after new file is written

    wxString filename = wxFileSelector(_("Choose output file"), wxEmptyString, StripLayers(name), wxEmptyString, "Preset files (*.xpreset)|*.xpreset", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (filename.IsEmpty()) return;
    wxFile f(filename);

    if (!f.Create(filename, true) || !f.IsOpened())
    {
        DisplayError(wxString::Format("Unable to create file %s. Error %d\n", filename, f.GetLastError()).ToStdString(), this);
        ValidateWindow();
        return;
    }

    bool presetFound = false;

    f.Write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    wxString v = xlights_version_string;
    f.Write(wxString::Format("<preset SourceVersion=\"%s\" >\n", v));

    if (id == treeRootID)
    {
        wxTreeItemIdValue cookie;
        for (wxTreeItemId i = TreeCtrl1->GetFirstChild(id, cookie); i.IsOk(); i = TreeCtrl1->GetNextChild(id, cookie))
        {
            MyTreeItemData *itemData = (MyTreeItemData *)TreeCtrl1->GetItemData(i);
            wxXmlNode* n = itemData->GetElement();

            if (itemData->IsGroup())
            {
                WriteGroup(f, n);
                presetFound = true;
            }
            else
            {
                WriteEffect(f, n);
                presetFound = true;
            }
        }
    }
    else
    {
        MyTreeItemData *itemData = (MyTreeItemData *)TreeCtrl1->GetItemData(id);

        wxXmlNode* n = itemData->GetElement();

        if (itemData->IsGroup())
        {
            WriteGroup(f, n);
            presetFound = true;
        }
        else
        {
            WriteEffect(f, n);
            presetFound = true;
        }
    }
    f.Write("</preset>\n");
    f.Close();

    if (!presetFound)
    {
        DisplayError(wxString::Format("No presets found, Created presets file %s is empty.\n", filename).ToStdString(), this);
        ValidateWindow();
        return;
    }
}

// This handles all the enabling and disabling of buttons ... stops lots of dialog boxes popping up when users do something
// that is not allowed.
void EffectTreeDialog::ValidateWindow()
{
    bool effectselected = false;
    bool effectgroupselected = false;

    wxTreeItemId id = TreeCtrl1->GetSelection();

    if (!id.IsOk() || id == treeRootID)
    {
        // nothing selected
    }
    else if (TreeCtrl1->HasChildren(id))
    {
        effectgroupselected = true;
    }
    else
    {
        effectselected = true;
    }

    if (effectgroupselected)
    {
        btApply->Disable();
        btExport->Enable();
        btDelete->Enable();
        btUpdate->Disable();
        btRename->Enable();
    }
    else if (effectselected)
    {
        btApply->Enable();
        btExport->Enable();
        btDelete->Enable();
        btUpdate->Enable();
        btRename->Enable();
    }
    else
    {
        btApply->Disable();
        if (id == treeRootID)
        {
            btExport->Enable();
        }
        else
        {
            btExport->Disable();
        }
        btDelete->Disable();
        btUpdate->Disable();
        btRename->Disable();
    }
}


void EffectTreeDialog::OnTreeCtrl1SelectionChanged(wxTreeEvent& event)
{
    ValidateWindow();

    GenerateGifImage(TreeCtrl1->GetSelection());
}

wxTreeItemId EffectTreeDialog::findTreeItem(wxTreeCtrl* pTreeCtrl, const wxTreeItemId& root, const wxTreeItemId& startID, const wxString& text, bool &startfound)
{
    wxTreeItemId item = root, child;
    wxTreeItemIdValue cookie;
    wxString findtext(text), itemtext;
    bool bFound;

    //make search case insensitive
    findtext.MakeLower();

    //Loop through all element and branches, first look for start location, second loop until new element of text found
    while (item.IsOk())
    {
        if (startfound)
        {   //second state found
            itemtext = pTreeCtrl->GetItemText(item).MakeLower();
            bFound = itemtext.Contains(findtext);
            if (bFound)//text found
                return item;
        }
        //state element found
        if (item == startID)
            startfound = true;

        child = pTreeCtrl->GetFirstChild(item, cookie);
        if (child.IsOk())
            child = findTreeItem(pTreeCtrl, child, startID, text, startfound);
        if (child.IsOk())
            return child;

        item = pTreeCtrl->GetNextSibling(item);
    }

    return item;
}

void EffectTreeDialog::OnETButton1Click(wxCommandEvent& event)
{
    SearchForText();
}

void EffectTreeDialog::OnTextCtrl1TextEnter(wxCommandEvent& event)
{
    SearchForText();
}

void EffectTreeDialog::SearchForText()
{
    wxArrayTreeItemIds Selections;
    wxTreeItemId item;

    //dont search for blank strings
    if (TextCtrl1->GetValue().IsEmpty())
        return;

    item = TreeCtrl1->GetRootItem();

    // empty tree control, return
    if (!TreeCtrl1->GetCount())
        return;

    //Get Current selected ID and search from there
    wxTreeItemId startID = TreeCtrl1->GetSelection();

    bool bStartFound = false; //pass a bool by ref to keep track if staring location was found, too lazy for state machine
    item = findTreeItem(TreeCtrl1, TreeCtrl1->GetRootItem(), startID, TextCtrl1->GetValue(), bStartFound);

    //none found, start at the top of tree this time
    if (!item.IsOk())
    {
        bStartFound = false;
        item = findTreeItem(TreeCtrl1, TreeCtrl1->GetRootItem(), TreeCtrl1->GetRootItem(), TextCtrl1->GetValue(), bStartFound);
    }

    //none found anywhere
    if (!item.IsOk())
    {
        DisplayInfo(_("Search Found No Results."), this);
        return;
    }

    // found an item woot
    TreeCtrl1->UnselectAll();
    TreeCtrl1->SelectItem(item, true);
    TreeCtrl1->EnsureVisible(item);
}

wxString EffectTreeDialog::generatePresetName(wxTreeItemId itemID)
{
    wxString presetName;
    if (itemID.IsOk()) {
        MyTreeItemData* item = (MyTreeItemData*)TreeCtrl1->GetItemData(itemID);
        if (item != nullptr) {
            wxXmlNode* ele = item->GetElement();
            if (ele->GetName() == "effectGroup")
                return wxString();
            presetName = ele->GetAttribute("name");
            wxTreeItemId parentID = TreeCtrl1->GetItemParent(itemID);

            if (itemID == treeRootID)
                return wxString();

            while (parentID != treeRootID) {
                MyTreeItemData* parData = (MyTreeItemData*)TreeCtrl1->GetItemData(parentID);
                if (parData != nullptr) {
                    presetName.Prepend("/");
                    wxXmlNode* parElm = parData->GetElement();
                    presetName.Prepend(parElm->GetAttribute("name"));
                }
                parentID = TreeCtrl1->GetItemParent(parentID);
            }
        }
    }
    return presetName;
}

void EffectTreeDialog::GenerateGifImage(wxTreeItemId itemID, bool regenerate)
{
    StopGifImage();
    wxString const fullName = generatePresetName(itemID);
    if (!fullName.IsEmpty()) {
        std::string filePath = xLightParent->GetPresetIconFilename(fullName);

        if (!wxFile::Exists(filePath) || regenerate) {
            wxWindowDisabler disableAll;
            wxBusyInfo wait(wxBusyInfoFlags()
                            .Parent(this)
                            .Text("Generating Effect Preview...")
                            .Icon(wxArtProvider::GetIcon(wxART_MAKE_ART_ID_FROM_STR(_T("xlART_EFFECTS")),wxART_OTHER, wxSize(64, 64))));
            
            xLightParent->WriteGIFForPreset(fullName);
        }
        LoadGifImage(filePath);
    }
}

#define GIF_DELAY 50
void EffectTreeDialog::LoadGifImage(wxString const& path)
{
    TimerGif.Stop();
    if(wxFile::Exists(path) && GIFImage::IsGIF(path)) {
        gifImage = std::make_unique<GIFImage>(path);

        if (!gifImage->IsOk())             {
            gifImage = nullptr;
            StaticBitmapGif->SetBitmap(*_blankGIFImage.get());
        }
        else {
            frameCount = 0;
            TimerGif.Start(GIF_DELAY);
        }
    } else {
        gifImage = nullptr;
    }
}

void EffectTreeDialog::PlayGifImage()
{
    if(gifImage) {
        int previewSize = GetOptimalPreviewSize();
        wxImage frame = gifImage->GetFrameForTime(frameCount * GIF_DELAY, true);
        frame.Rescale(previewSize, previewSize);
        StaticBitmapGif->SetBitmap(wxBitmap(frame));

        // Set MinSize same as gif size AFTER or resize doesn't work on MSW
        StaticBitmapGif->SetMinSize(wxSize(previewSize, previewSize));
    }
}

void EffectTreeDialog::OnTimerGifTrigger(wxTimerEvent& event)
{
    ++frameCount;
    PlayGifImage();
}

void EffectTreeDialog::StopGifImage()
{
    // reset blank image to current optimal size so dialog doesn't jump around
    int previewSize = GetOptimalPreviewSize();
    _blankGIFImage.reset(new wxBitmap(previewSize, previewSize, true));
    
    StaticBitmapGif->SetBitmap(*_blankGIFImage.get());
    TimerGif.Stop();
    gifImage = nullptr;
}

void EffectTreeDialog::DeleteGifImage(wxTreeItemId itemID)
{
    StopGifImage();
    wxString const fullName = generatePresetName(itemID);
    if (!fullName.IsEmpty()) {
        std::string filePath = xLightParent->GetPresetIconFilename(fullName);

        if (wxFile::Exists(filePath)) {
            wxRemoveFile(filePath);
        }
    }
}

#define PREVIEW_PROPORTION 0.25f
int EffectTreeDialog::GetOptimalPreviewSize() {
    
    // size based on proportion of current dialog size
    int currDialogWidth = GetSize().GetWidth();
    int size = std::floor(currDialogWidth * PREVIEW_PROPORTION);

    if (size >= MAX_PREVIEW_SIZE) {
        // Don't scale up above max
        return MAX_PREVIEW_SIZE;
    } else if (size <= MIN_PREVIEW_SIZE) {
        // Don't scale down below min
        return MIN_PREVIEW_SIZE;
    } else {
        // scale with new size
        return size;
    }
}
