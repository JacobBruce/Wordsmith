/***************************************************************
 * Name:      WordsmithMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Bitfreak Software (contact@bitfreak.info)
 * Created:   2026-02-26
 * Copyright: Bitfreak Software (www.bitfreak.info)
 * License:
 **************************************************************/

#include "WordsmithMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(WordsmithFrame)
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(WordsmithFrame)
const wxWindowID WordsmithFrame::ID_AUINOTEBOOK1 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM2 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM3 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM4 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM5 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM30 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM25 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM26 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM1 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM6 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM7 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM8 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM9 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM10 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM11 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM39 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM12 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM13 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM47 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM48 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM49 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM46 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM14 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM15 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM28 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM31 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM32 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM33 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM34 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM35 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM36 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM38 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM37 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM16 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM50 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM29 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM17 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM18 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM22 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM23 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM52 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM41 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM27 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM42 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM43 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM44 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM40 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM19 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM45 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM20 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM51 = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM21 = wxNewId();
const wxWindowID WordsmithFrame::idMenuAbout = wxNewId();
const wxWindowID WordsmithFrame::ID_MENUITEM24 = wxNewId();
const wxWindowID WordsmithFrame::ID_STATUSBAR1 = wxNewId();
const wxWindowID WordsmithFrame::new_btn = wxNewId();
const wxWindowID WordsmithFrame::open_btn = wxNewId();
const wxWindowID WordsmithFrame::save_btn = wxNewId();
const wxWindowID WordsmithFrame::saveas_btn = wxNewId();
const wxWindowID WordsmithFrame::undo_btn = wxNewId();
const wxWindowID WordsmithFrame::redo_btn = wxNewId();
const wxWindowID WordsmithFrame::cut_btn = wxNewId();
const wxWindowID WordsmithFrame::copy_btn = wxNewId();
const wxWindowID WordsmithFrame::paste_btn = wxNewId();
const wxWindowID WordsmithFrame::find_btn = wxNewId();
const wxWindowID WordsmithFrame::dict_btn = wxNewId();
const wxWindowID WordsmithFrame::tips_btn = wxNewId();
const wxWindowID WordsmithFrame::ID_TOOLBAR1 = wxNewId();
const wxWindowID WordsmithFrame::ID_MESSAGEDIALOG1 = wxNewId();
const wxWindowID WordsmithFrame::ID_MESSAGEDIALOG2 = wxNewId();
const wxWindowID WordsmithFrame::ID_MESSAGEDIALOG3 = wxNewId();
const wxWindowID WordsmithFrame::ID_TEXTENTRYDIALOG1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(WordsmithFrame,wxFrame)
    //(*EventTable(WordsmithFrame)
    //*)
END_EVENT_TABLE()

/// START wsTextCtrl

wsTextCtrl::wsTextCtrl(wxWindow* parent,
		wxWindowID id = wxID_ANY,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0,
		const wxString& name = wxSTCNameStr) :

        wxStyledTextCtrl(parent, id, pos, size, style, name),
        m_FileName(_("New File")),
        m_IsModified(false),
        m_IsIndicated(false),
        m_HasCustomFont(false)
{
    SetEOLMode(GLOBALS::LineEndMode);
    SetWordChars(GLOBALS::WordChars);
    SetWrapMode(wxSTC_WRAP_WORD);
    SetMarginWidth(wxSTC_MARGIN_SYMBOL,0);
    SetMarginWidth(wxSTC_MARGIN_NUMBER,0);
    SetMarginLeft(12);
    SetMarginRight(8);
    SetMouseDwellTime(1000);
    SetLexer(wxSTC_LEX_NULL);
    SetIndicatorCurrent(0);
    //SetViewEOL(true);

    SetModEventMask(wxSTC_MOD_CONTAINER | wxSTC_MOD_INSERTTEXT | wxSTC_MOD_DELETETEXT);

    if (wxSystemSettings::GetAppearance().IsDark()) {
        StyleSetForeground(wxSTC_STYLE_DEFAULT, *wxWHITE);
        IndicatorSetForeground(0, wxColor(232,37,51));
    } else {
        StyleSetForeground(wxSTC_STYLE_DEFAULT, *wxBLACK);
        IndicatorSetForeground(0, wxColor(184,22,33));
    }

    StyleSetFont(wxSTC_STYLE_DEFAULT, GLOBALS::DefaultFont);
    StyleSetForeground(wxSTC_STYLE_DEFAULT, GLOBALS::DefFontColor);
    //StyleSetSize(wxSTC_STYLE_DEFAULT, StyleGetSize(wxSTC_STYLE_DEFAULT)+1);
    StyleClearAll();

    //AutoCompSetChooseSingle(true);
    //AutoCompSetIgnoreCase(true);
    AutoCompSetSeparator('\n');
    AutoCompSetAutoHide(true);
    AutoCompSetOrder(wxSTC_ORDER_CUSTOM);
    IndicatorSetStyle(0, wxSTC_INDIC_SQUIGGLE);
    UsePopUp(wxSTC_POPUP_NEVER);

    SetFocus();
}

const bool wsTextCtrl::IsChanged() const
{ return m_IsModified; }

void wsTextCtrl::SetChanged(bool changed)
{ m_IsModified = changed; }

void wsTextCtrl::SetFilePath(const wxString& file_path)
{ m_FilePath = file_path; }

const wxString& wsTextCtrl::GetFilePath() const
{ return m_FilePath; }

void wsTextCtrl::SetFileName(const wxString& file_name)
{ m_FileName = file_name; }

const wxString& wsTextCtrl::GetFileName() const
{ return m_FileName; }

const bool wsTextCtrl::IsIndicated() const
{ return m_IsIndicated; }

void wsTextCtrl::SetIndicated(bool indicated)
{ m_IsIndicated = indicated; }

const bool wsTextCtrl::HasCustomFont() const
{ return m_HasCustomFont; }

void wsTextCtrl::SetCustomFont(const wxFont& font)
{
    m_HasCustomFont = true;
    StyleSetFont(wxSTC_STYLE_DEFAULT, font);
    StyleClearAll();
}

void wsTextCtrl::SetFontColor(const wxColor& color)
{
    m_HasCustomFont = true;
    StyleSetForeground(wxSTC_STYLE_DEFAULT, color);
    StyleClearAll();
}

void wsTextCtrl::SetColoredFont(const wxFont& font, const wxColor& color)
{
    m_HasCustomFont = true;
    StyleSetFont(wxSTC_STYLE_DEFAULT, font);
    StyleSetForeground(wxSTC_STYLE_DEFAULT, color);
    StyleClearAll();
}

/// START wsTextShowDialog

wsTextShowDialog::wsTextShowDialog(wxWindow* parent, const wxString& message, const wxString& caption,
                                   const wxString& value, const wxPoint& pos, const wxSize sz) :
    wxDialog(parent, wxID_ANY, caption, pos, sz)
{
    int tcWidth = std::min((int)value.length() * 10, 520);
    textCtrl = new wxTextCtrl(this, wxID_ANY, value);
    textCtrl->SetMinSize(wxSize(tcWidth,textCtrl->GetBestHeight(tcWidth)));
    textCtrl->SetEditable(false);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(new wxStaticText(this, wxID_ANY, message), 0, wxALL, 5);
    sizer->Add(textCtrl, 0, wxEXPAND | wxALL, 5);
    sizer->Add(CreateButtonSizer(wxOK), 0, wxALIGN_CENTER | wxALL, 5);

    SetSizerAndFit(sizer);
}

wxString wsTextShowDialog::GetValue() const
{ return textCtrl->GetValue(); }

void wsTextShowDialog::SetValue(const wxString& value)
{ return textCtrl->SetValue(value); }

/// START wsSettingsDialog

wsSettingsDialog::wsSettingsDialog(wxWindow* parent, const wxString& caption, const wxPoint& pos, const wxSize sz) :
    wxDialog(parent, wxID_ANY, caption, pos, sz)
{
    label1 = new wxStaticText(this, wxID_ANY, _("App Theme"));
    label2 = new wxStaticText(this, wxID_ANY, _("End of Line"));
    label3 = new wxStaticText(this, wxID_ANY, _("Auto-complete"));
    label4 = new wxStaticText(this, wxID_ANY, _("Default Font"));

    themeChoice = new wxChoice(this, wxID_ANY);
    themeChoice->SetMinSize(wxSize(200,themeChoice->GetBestHeight(200)));
    themeChoice->Append(_("System"));
    themeChoice->Append(_("Dark"));
    themeChoice->Append(_("Light"));

    eolChoice = new wxChoice(this, wxID_ANY);
    eolChoice->SetMinSize(wxSize(200,eolChoice->GetBestHeight(200)));
    eolChoice->Append(_("Windows (CR LF)"));
    eolChoice->Append(_("Unix (LF)"));
    eolChoice->Append(_("Macintosh (CR)"));

    acChoice = new wxChoice(this, wxID_ANY);
    acChoice->SetMinSize(wxSize(200,acChoice->GetBestHeight(200)));
    acChoice->Append(_("Disabled"));
    acChoice->Append(_("Enabled"));
    acChoice->Append(_("Enabled (auto-space)"));

    //fontPicker = new wxFontPickerCtrl(this, wxID_ANY);
    //fontPicker->SetMinSize(wxSize(100,fontPicker->GetBestHeight(100)));

    colorPicker = new wxColourPickerCtrl(this, wxID_ANY);
    colorPicker->SetMinSize(wxSize(30,colorPicker->GetBestHeight(30)));

    fontBtn = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBU_LEFT);
    fontBtn->SetMinSize(wxSize(125,fontBtn->GetBestHeight(125)));
    fontBtn->Bind(wxEVT_BUTTON, &FontButtonClick, this);

    applyBtn = new wxButton(this, wxID_ANY, _("Apply"));
    applyBtn->SetMinSize(wxSize(75,applyBtn->GetBestHeight(75)));
    applyBtn->Bind(wxEVT_BUTTON, &SaveButtonClick, this);

    closeBtn = new wxButton(this, wxID_ANY, _("Close"));
    closeBtn->SetMinSize(wxSize(75,closeBtn->GetBestHeight(75)));
    closeBtn->Bind(wxEVT_BUTTON, &CloseButtonClick, this);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(label1, 0, wxALIGN_LEFT | wxALL, 5);
    sizer->Add(themeChoice, 0, wxALIGN_LEFT | wxALL, 5);
    sizer->Add(label2, 0, wxALIGN_LEFT | wxALL, 5);
    sizer->Add(eolChoice, 0, wxALIGN_LEFT | wxALL, 5);
    sizer->Add(label3, 0, wxALIGN_LEFT | wxALL, 5);
    sizer->Add(acChoice, 0, wxALIGN_LEFT | wxALL, 5);
    sizer->Add(label4, 0, wxALIGN_LEFT | wxALL, 5);

    wxBoxSizer* sizer2 = new wxBoxSizer(wxHORIZONTAL);
    //sizer2->Add(fontPicker, 1);
    sizer2->Add(fontBtn, 1);
    sizer2->Add(colorPicker, 0);
    sizer->Add(sizer2, 0, wxEXPAND | wxALL, 5);

    wxBoxSizer* sizer3 = new wxBoxSizer(wxHORIZONTAL);
    sizer3->Add(applyBtn);
    sizer3->AddStretchSpacer();
    sizer3->Add(closeBtn);

    sizer->AddSpacer(10);
    sizer->Add(sizer3, 0, wxEXPAND | wxALL, 5);

    SetSizerAndFit(sizer);

    Reset();

    ApplySettings(true);
}

void wsSettingsDialog::Reset()
{
    themeChoice->SetSelection(stoi(GLOBALS::Settings["THEME"]));
    eolChoice->SetSelection(stoi(GLOBALS::Settings["EOL"]));
    acChoice->SetSelection(stoi(GLOBALS::Settings["AC"]));

    if (GLOBALS::Settings["FONT"] != "default") {
        auto fontData(ExplodeStr(GLOBALS::Settings["FONT"], "|"));
        if (fontData.size() == 4) {
            defaultFont.SetFaceName(fontData[0]);
            defaultFont.SetPointSize(8);
            defaultFont.SetWeight(wxFontWeight(stoi(fontData[2])));
            defaultFont.SetStyle(wxFontStyle(stoi(fontData[3])));
            fontBtn->SetFont(defaultFont);
            defaultFont.SetPointSize(stoi(fontData[1]));
        }
    } else {
        defaultFont = fontBtn->GetFont();
    }

    fontBtn->SetLabel(fontBtn->GetFont().GetFaceName());

    if (GLOBALS::Settings["FONT_COLOR"] != "default") {
        colorPicker->SetColour(GLOBALS::Settings["FONT_COLOR"]);
    } else {
        if (wxSystemSettings::GetAppearance().IsDark()) {
            colorPicker->SetColour(*wxWHITE);
        } else {
            colorPicker->SetColour(*wxBLACK);
        }
    }
}

void wsSettingsDialog::ApplySettings(bool init)
{
    WordsmithFrame* parent = static_cast<WordsmithFrame*>(GetParent());

    std::string newTheme(std::to_string(themeChoice->GetSelection()));

    if (!init && newTheme != GLOBALS::Settings["THEME"])
        wxMessageBox(_("The theme will change next time the app is restarted."));

    GLOBALS::Settings["THEME"] = newTheme;
    GLOBALS::Settings["EOL"] = std::to_string(eolChoice->GetSelection());
    GLOBALS::Settings["AC"] = std::to_string(acChoice->GetSelection());
    GLOBALS::Settings["FONT_COLOR"] = colorPicker->GetColour().GetAsString();

    GLOBALS::Settings["FONT"] = defaultFont.GetFaceName().utf8_string() + "|" +
                                std::to_string(defaultFont.GetPointSize()) + "|" +
                                std::to_string((int)defaultFont.GetWeight()) + "|" +
                                std::to_string((int)defaultFont.GetStyle());

    GLOBALS::DefaultFont = defaultFont;
    GLOBALS::DefFontColor = colorPicker->GetColour();
    GLOBALS::AutoCompMode = acChoice->GetSelection();

    switch (eolChoice->GetSelection())
    {
        case 0:
            GLOBALS::LineEndMode = wxSTC_EOL_CRLF;
            GLOBALS::LineEndStr = "\r\n";
            break;
        case 1:
            GLOBALS::LineEndMode = wxSTC_EOL_LF;
            GLOBALS::LineEndStr = "\n";
            break;
        case 2:
            GLOBALS::LineEndMode = wxSTC_EOL_CR;
            GLOBALS::LineEndStr = "\r";
            break;
    }

    for (size_t i=0; i < parent->AuiNotebook1->GetPageCount(); ++i)
    {
        wsTextCtrl* stc((wsTextCtrl*)parent->AuiNotebook1->GetPage(i)->GetChildren().GetFirst()->GetData());

        stc->SetEOLMode(GLOBALS::LineEndMode);

        if (!stc->HasCustomFont()) {
            stc->StyleSetForeground(wxSTC_STYLE_DEFAULT, colorPicker->GetColour());
            stc->StyleSetFont(wxSTC_STYLE_DEFAULT, defaultFont);
            stc->StyleClearAll();
            stc->ConvertEOLs(GLOBALS::LineEndMode);
        }
    }

    if (!init) SaveConfigFile(u8"./files/settings.cfg", GLOBALS::Settings);
}

void wsSettingsDialog::FontButtonClick(wxCommandEvent& event)
{
    wxFontData fontData;
    fontData.EnableEffects(false);
    fontData.SetAllowSymbols(false);
    fontData.SetInitialFont(defaultFont);

    wxFontDialog fontDialog(this, fontData);

    if (fontDialog.ShowModal() == wxID_CANCEL) return;

    wxFont newFont(fontDialog.GetFontData().GetChosenFont());
    defaultFont = newFont;
    newFont.SetPointSize(8);

    fontBtn->SetFont(newFont);
    fontBtn->SetLabel(newFont.GetFaceName());
}

void wsSettingsDialog::SaveButtonClick(wxCommandEvent& event)
{
    ApplySettings();
}

void wsSettingsDialog::CloseButtonClick(wxCommandEvent& event)
{
    Hide();
}

/// START wsWordsDialog

wsWordsDialog::wsWordsDialog(wxWindow* parent, const wxString& caption, const wxPoint& pos, const wxSize sz) :
    wxDialog(parent, wxID_ANY, caption, pos, sz, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
    label1 = new wxStaticText(this, wxID_ANY, _("Add words (one per line)"));
    label2 = new wxStaticText(this, wxID_ANY, _("Remove words (one per line)"));

    applyBtn = new wxButton(this, wxID_ANY, _("Apply"));
    applyBtn->SetMinSize(wxSize(80,applyBtn->GetBestHeight(80)));
    applyBtn->Bind(wxEVT_BUTTON, &SaveButtonClick, this);

    closeBtn = new wxButton(this, wxID_ANY, _("Close"));
    closeBtn->SetMinSize(wxSize(80,closeBtn->GetBestHeight(80)));
    closeBtn->Bind(wxEVT_BUTTON, &CloseButtonClick, this);

    newWords = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    newWords->SetMinSize(wxSize(220,300));

    badWords = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    badWords->SetMinSize(wxSize(220,300));

    wxBoxSizer* sizerLeft = new wxBoxSizer(wxVERTICAL);
    sizerLeft->Add(label1, 0, wxALIGN_LEFT | wxALL, 5);
    sizerLeft->Add(newWords, 1, wxEXPAND | wxALL, 5);

    wxBoxSizer* sizerRight = new wxBoxSizer(wxVERTICAL);
    sizerRight->Add(label2, 0, wxALIGN_LEFT | wxALL, 5);
    sizerRight->Add(badWords, 1, wxEXPAND | wxALL, 5);

    wxBoxSizer* sizerRow = new wxBoxSizer(wxHORIZONTAL);
    sizerRow->Add(sizerLeft, 1, wxEXPAND);
    sizerRow->Add(sizerRight, 1, wxEXPAND);

    wxBoxSizer* sizerBtns = new wxBoxSizer(wxHORIZONTAL);
    sizerBtns->AddStretchSpacer();
    sizerBtns->Add(applyBtn, 0, wxALL, 5);
    sizerBtns->Add(closeBtn, 0, wxALL, 5);
    sizerBtns->AddStretchSpacer();

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->AddSpacer(5);
    sizer->Add(sizerRow, 1, wxEXPAND);
    sizer->Add(sizerBtns, 0, wxEXPAND);
    sizer->AddSpacer(5);

    SetSizerAndFit(sizer);

    LoadWords(u8"./files/custom_words.txt");
}

void wsWordsDialog::Reset()
{
    UpdateLists(false);
}

void wsWordsDialog::LoadWords(std::u8string file_path)
{
    std::string err;
    if (!FileExists(file_path)) return;
    auto lines = ReadFileLines(file_path, err);

    if (!err.empty()) return;

    int wordCnt = stoi(lines[0]);

    for (int i=1; i <= wordCnt; ++i)
        if (!lines[i].empty()) GLOBALS::UserWords.emplace(lines[i]);

    for (size_t i=wordCnt+1; i < lines.size(); ++i)
        if (!lines[i].empty()) GLOBALS::SkipWords.emplace(lines[i]);

    UpdateLists(false);
}

void wsWordsDialog::SaveWords()
{
    std::string wordsStr = std::to_string(GLOBALS::UserWords.size()) + "\n";

    for (const std::string& word : GLOBALS::UserWords)
        wordsStr += word + "\n";

    for (const std::string& word : GLOBALS::SkipWords)
        wordsStr += word + "\n";

    WriteFileStr(u8"./files/custom_words.txt", wordsStr);

    static_cast<WordsmithFrame*>(GetParent())->spellTimer.Start(1, true);
}

void wsWordsDialog::SaveButtonClick(wxCommandEvent& event)
{
    GLOBALS::UserWords.clear();
    GLOBALS::SkipWords.clear();

    for (int i=0; i < newWords->GetNumberOfLines(); ++i)
    {
        wxString word(newWords->GetLineText(i).Trim());

        if (!word.empty())
            GLOBALS::UserWords.emplace(WordParser::LowerWord(word).utf8_string());
    }

    for (int i=0; i < badWords->GetNumberOfLines(); ++i)
    {
        wxString word(badWords->GetLineText(i).Trim());

        if (!word.empty())
            GLOBALS::SkipWords.emplace(WordParser::LowerWord(word).utf8_string());
    }

    SaveWords();
}

void wsWordsDialog::CloseButtonClick(wxCommandEvent& event)
{
    Hide();
}

void wsWordsDialog::UpdateLists(bool save)
{
    std::string userWords, skipWords;

    for (const std::string& word : GLOBALS::UserWords)
        userWords += word + "\n";

    for (const std::string& word : GLOBALS::SkipWords)
        skipWords += word + "\n";

    newWords->SetValue(wxString::FromUTF8(userWords).Trim());
    badWords->SetValue(wxString::FromUTF8(skipWords).Trim());

    if (save) SaveWords();
}

void wsWordsDialog::AddWord(const std::string& word)
{
    GLOBALS::UserWords.emplace(word);

    if (GLOBALS::SkipWords.contains(word))
        GLOBALS::SkipWords.erase(word);

    UpdateLists();
}

void wsWordsDialog::RemoveWord(const std::string& word)
{
    GLOBALS::SkipWords.emplace(word);

    if (GLOBALS::UserWords.contains(word))
        GLOBALS::UserWords.erase(word);

    UpdateLists();
}

/// START wsPhrasesDialog

wsPhrasesDialog::wsPhrasesDialog(wxWindow* parent, const wxString& caption, const wxPoint& pos, const wxSize sz) :
    wxDialog(parent, wxID_ANY, caption, pos, sz, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
    label1 = new wxStaticText(this, wxID_ANY, _("Add phrases/sentences (one per line)"));
    label2 = new wxStaticText(this, wxID_ANY, _(" ? "));
    label2->SetToolTip(_("Press Shift+Space to show an auto-complete list with these phrases."));

    wxFont qFont(label2->GetFont());
    qFont.SetWeight(wxFONTWEIGHT_BOLD);
    label2->SetFont(qFont);

    applyBtn = new wxButton(this, wxID_ANY, _("Apply"));
    applyBtn->SetMinSize(wxSize(80,applyBtn->GetBestHeight(80)));
    applyBtn->Bind(wxEVT_BUTTON, &SaveButtonClick, this);

    closeBtn = new wxButton(this, wxID_ANY, _("Close"));
    closeBtn->SetMinSize(wxSize(80,closeBtn->GetBestHeight(80)));
    closeBtn->Bind(wxEVT_BUTTON, &CloseButtonClick, this);

    phrases = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_DONTWRAP);
    phrases->SetMinSize(wxSize(400,400));

    wxBoxSizer* sizerRow = new wxBoxSizer(wxHORIZONTAL);
    sizerRow->Add(label1, 1, wxALL, 5);
    sizerRow->Add(label2, 0, wxALL, 5);

    wxBoxSizer* sizerCon = new wxBoxSizer(wxVERTICAL);
    sizerCon->Add(sizerRow, 0, wxEXPAND | wxALIGN_LEFT);
    sizerCon->Add(phrases, 1, wxEXPAND | wxALL, 5);

    wxBoxSizer* sizerBtns = new wxBoxSizer(wxHORIZONTAL);
    sizerBtns->AddStretchSpacer();
    sizerBtns->Add(applyBtn, 0, wxALL, 5);
    sizerBtns->Add(closeBtn, 0, wxALL, 5);
    sizerBtns->AddStretchSpacer();

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->AddSpacer(5);
    sizer->Add(sizerCon, 1, wxEXPAND);
    sizer->Add(sizerBtns, 0, wxEXPAND);
    sizer->AddSpacer(5);

    SetSizerAndFit(sizer);

    LoadPhrases(u8"./files/custom_phrases.txt");
}

void wsPhrasesDialog::Reset()
{
    UpdateList(false);
}

void wsPhrasesDialog::LoadPhrases(std::u8string file_path)
{
    std::string err;
    if (!FileExists(file_path)) return;
    auto lines = ReadFileLines(file_path, err);

    if (!err.empty()) return;

    for (const std::string& line : lines)
        if (!line.empty()) GLOBALS::UserPhrases.emplace(line);

    UpdateList(false);
}

void wsPhrasesDialog::SavePhrases()
{
    std::string phraseStr;

    for (const std::string& phrase : GLOBALS::UserPhrases)
        phraseStr += phrase + "\n";

    WriteFileStr(u8"./files/custom_phrases.txt", phraseStr);
}

void wsPhrasesDialog::SaveButtonClick(wxCommandEvent& event)
{
    GLOBALS::UserPhrases.clear();

    for (int i=0; i < phrases->GetNumberOfLines(); ++i)
    {
        wxString phrase(phrases->GetLineText(i).Trim());

        if (!phrase.empty())
            GLOBALS::UserPhrases.emplace(phrase.utf8_string());
    }

    SavePhrases();
}

void wsPhrasesDialog::CloseButtonClick(wxCommandEvent& event)
{
    Hide();
}

void wsPhrasesDialog::UpdateList(bool save)
{
    std::string userPhrases;

    for (const std::string& phrase : GLOBALS::UserPhrases)
        userPhrases += phrase + "\n";

    phrases->SetValue(wxString::FromUTF8(userPhrases).Trim());

    if (save) SavePhrases();
}

void wsPhrasesDialog::AddPhrase(const std::string& phrase)
{
    GLOBALS::UserPhrases.emplace(phrase);

    UpdateList();
}

/// START wsDictDialog

wsDictDialog::wsDictDialog(wxWindow* parent, const wxString& caption, const wxPoint& pos, const wxSize sz) :
    wxDialog(parent, wxID_ANY, caption, pos, sz, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
    defText = new wxTextCtrl(this, wxID_ANY, _("Loading word files ..."), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY | wxBORDER_NONE);
    defText->SetMargins(4,3);
    defText->SetMinSize(wxSize(350,150));
    defText->SetBackgroundColour(GetBackgroundColour());

    exText = new wxTextCtrl(this, wxID_ANY, _(""), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY | wxBORDER_NONE);
    exText->SetMargins(4,3);
    exText->SetMinSize(wxSize(350,150));
    exText->SetBackgroundColour(GetBackgroundColour());

    wxStaticBoxSizer* sizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("DEFINITIONS"));
    sizer1->Add(defText, 1,  wxEXPAND);

    wxStaticBoxSizer* sizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("EXAMPLES"));
    sizer2->Add(exText, 1,  wxEXPAND);

    searchBar = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    searchBar->SetHint(_("Start typing a word"));
    searchBar->SetMinSize(wxSize(400,searchBar->GetBestHeight(400)));
    searchBar->Bind(wxEVT_TEXT, &OnSearchWordChanged, this);
    //searchBar->Bind(wxEVT_TEXT_ENTER, &OnSearchEnter, this);

    closeBtn = new wxButton(this, wxID_ANY, _("Close"));
    closeBtn->SetMinSize(wxSize(80,closeBtn->GetBestHeight(80)));
    closeBtn->Bind(wxEVT_BUTTON, &CloseButtonClick, this);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(searchBar, 0, wxEXPAND | wxALL, 5);
    sizer->Add(sizer1, 1, wxEXPAND | wxLEFT | wxRIGHT, 5);
    sizer->AddSpacer(5);
    sizer->Add(sizer2, 1, wxEXPAND | wxLEFT | wxRIGHT, 5);
    sizer->Add(closeBtn, 0, wxCENTER | wxALL, 10);

    SetSizerAndFit(sizer);
}

void wsDictDialog::DoSearch(const wxString& search_txt)
{
    std::string word(search_txt.utf8_string());
    if (!GLOBALS::GotWordData || word.empty()) return;

    wxString definitions, examples, wordType;

    if (!GLOBALS::WordSyn.contains(word)) {
        WordParser::LowerWord(word);
        if (!GLOBALS::WordSyn.contains(word))
            WordParser::UpperWord(word);
    }

    if (GLOBALS::WordSyn.contains(word)) {

        const auto& syns(GLOBALS::WordSyn.at(word));

        for (const std::string& syn : syns)
        {
            const WordEntry& entry(GLOBALS::WordNet.at(syn));

            if (!entry.definitions.empty()) {

                if (syn.ends_with('n')) {
                    wordType = _("Noun: ");
                } else if (syn.ends_with('v')) {
                    wordType = _("Verb: ");
                } else if (syn.ends_with('a')) {
                    wordType = _("Adjective: ");
                } else if (syn.ends_with('s')) {
                    wordType = _("Adjective: ");
                } else if (syn.ends_with('r')) {
                    wordType = _("Adverb: ");
                }

                for (const std::string& def: entry.definitions)
                    definitions += wordType + wxString::FromUTF8(def) + "\n\n";

                for (const std::string& example: entry.examples)
                    examples += wordType + wxString::FromUTF8(example) + "\n\n";
            }
        }
    }

    if (definitions.empty()) {
        defText->SetValue(_("No definitions available."));
    } else {
        defText->SetValue(definitions.Trim());
    }

    if (examples.empty()) {
        exText->SetValue(_("No examples available."));
    } else {
        exText->SetValue(examples.Trim());
    }
}

void wsDictDialog::SetReady()
{
    wxString searchTxt(searchBar->GetValue());

    searchBar->AutoComplete(autoWords);

    if (searchTxt.empty()) {
        defText->SetValue(_("No definitions available."));
        exText->SetValue(_("No examples available."));
    } else {
        DoSearch(searchTxt);
    }
}

void wsDictDialog::OnSearchWordChanged(wxCommandEvent& event)
{
    /*if (autoCompleted) {
        searchBar->AutoComplete(autoWords);
        autoCompleted = false;
    }*/

    DoSearch(searchBar->GetValue());

    event.Skip();
}

/*void wsDictDialog::OnSearchEnter(wxCommandEvent& event)
{
    searchBar->AutoComplete({});
    autoCompleted = true;

    event.Skip();
}*/

void wsDictDialog::AddWordToAC(const std::string& word)
{
    autoWords.Add(wxString::FromUTF8(word));
}

void wsDictDialog::CloseButtonClick(wxCommandEvent& event)
{
    Hide();
}

/// START wsTipsDialog

wsTipsDialog::wsTipsDialog(wxWindow* parent, const wxString& caption, const wxPoint& pos, const wxSize sz) :
    wxDialog(parent, wxID_ANY, caption, pos, sz)
{
    label1 = new wxStaticText(this, wxID_ANY, wxEmptyString);
    label1->SetMinSize(wxSize(300,label1->GetBestHeight(300)));
    tipIndex = std::abs(rand()) % tips.size();
    label1->SetLabelText(tips[tipIndex]);

    nextBtn = new wxButton(this, wxID_ANY, _("Next"));
    nextBtn->SetMinSize(wxSize(80,nextBtn->GetBestHeight(80)));
    nextBtn->Bind(wxEVT_BUTTON, &NextButtonClick, this);

    closeBtn = new wxButton(this, wxID_ANY, _("Close"));
    closeBtn->SetMinSize(wxSize(80,closeBtn->GetBestHeight(80)));
    closeBtn->Bind(wxEVT_BUTTON, &CloseButtonClick, this);

    wxBitmap bmp(wxImage(_T("./files/icons/tips.png")));
    infoIcon = new wxStaticBitmap(this, wxID_ANY, bmp);

    wxStaticBoxSizer* sizerRow = new wxStaticBoxSizer(wxHORIZONTAL, this, _("TIP"));
    sizerRow->Add(infoIcon, 0, wxALL, 5);
    sizerRow->Add(label1, 1,  wxEXPAND | wxALL, 5);

    wxBoxSizer* sizerBtns = new wxBoxSizer(wxHORIZONTAL);
    sizerBtns->AddStretchSpacer();
    sizerBtns->Add(nextBtn, 0, wxALL, 5);
    sizerBtns->Add(closeBtn, 0, wxALL, 5);
    sizerBtns->AddStretchSpacer();

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->AddSpacer(5);
    sizer->Add(sizerRow, 1, wxEXPAND | wxALL, 5);
    sizer->Add(sizerBtns, 0, wxEXPAND);
    sizer->AddSpacer(5);

    SetSizerAndFit(sizer);
}

void wsTipsDialog::NextButtonClick(wxCommandEvent& event)
{
    if (++tipIndex >= tips.size()) tipIndex = 0;
    label1->SetLabelText(tips[tipIndex]);
    Layout();
}

void wsTipsDialog::CloseButtonClick(wxCommandEvent& event)
{
    Hide();
}

/// START wsAboutDialog

wsAboutDialog::wsAboutDialog(wxWindow* parent, const wxString& caption, const wxPoint& pos, const wxSize sz) :
    wxDialog(parent, wxID_ANY, caption, pos, sz)
{
    wxString bgCol = GetBackgroundColour().GetAsString();
    wxString ver = std::string(APP_VER) + "<br>" + wxbuildinfo(long_f);
    wxString msg = "<html><body style='background-color:"+bgCol+"'><b>Wordsmith Text Editor</b><br><br>Windows Release Build v" +
                    ver + "<br><br>© Bitfreak Software - <a href='https://bitfreak.info'>www.bitfreak.info</a></body></html>";

    aboutHTML = new wsHtmlWindow(this, wxID_ANY);
    aboutHTML->SetMinSize(wxSize(360,136));
    aboutHTML->SetPage(msg);

    checkBtn = new wxButton(this, wxID_ANY, _("Check for Update"));
    checkBtn->SetMinSize(wxSize(150,checkBtn->GetBestHeight(150)));
    checkBtn->Bind(wxEVT_BUTTON, &CheckButtonClick, this);

    closeBtn = new wxButton(this, wxID_ANY, _("Close"));
    closeBtn->SetMinSize(wxSize(80,closeBtn->GetBestHeight(80)));
    closeBtn->Bind(wxEVT_BUTTON, &CloseButtonClick, this);

    wxBitmap bmp(wxImage(_T("./files/icons/app_icon_x48.png")));
    appIcon = new wxStaticBitmap(this, wxID_ANY, bmp);

    wxBoxSizer* sizerRow = new wxBoxSizer(wxHORIZONTAL);
    sizerRow->Add(appIcon, 0, wxALL, 5);
    sizerRow->Add(aboutHTML, 1,  wxEXPAND | wxALL, 5);

    wxBoxSizer* sizerBtns = new wxBoxSizer(wxHORIZONTAL);
    sizerBtns->Add(checkBtn, 0, wxALL, 5);
    sizerBtns->AddStretchSpacer();
    sizerBtns->Add(closeBtn, 0, wxALL, 5);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->AddSpacer(5);
    sizer->Add(sizerRow, 1, wxEXPAND | wxALL, 5);
    sizer->Add(new wxStaticLine(this), 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
    sizer->Add(sizerBtns, 0, wxEXPAND | wxALL, 5);

    SetSizerAndFit(sizer);
}

void wsAboutDialog::CheckButtonClick(wxCommandEvent& event)
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    lastCheck = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();

    checkBtn->Enable(false);
    checkBtn->SetLabel(_("Checking ..."));

    webReq = wxWebSession::GetDefault().CreateRequest(this,
        "https://github.com/JacobBruce/Wordsmith/raw/refs/heads/main/version.txt"
    );

    if (!webReq.IsOk()) return;

    Bind(wxEVT_WEBREQUEST_STATE, OnStateChange, this);

    webReq.Start();
}

void wsAboutDialog::OnStateChange(wxWebRequestEvent& event)
{
    switch (event.GetState())
    {
        case wxWebRequest::State_Completed:
        {
            wxString appVer(event.GetResponse().AsString());

            if (appVer.length() > 4 && appVer.length() < 16) {
                if (appVer == APP_VER) {
                    wxMessageBox(_("Wordsmith is up to date."));
                } else {
                    wxMessageDialog* updateDialog = new wxMessageDialog(this, wxEmptyString, _("Update Available"), wxYES_NO|wxICON_QUESTION);
                    updateDialog->SetMessage(_("There is a new version of Wordsmith available. Do you want to visit the releases page?"));
                    int answer = updateDialog->ShowModal();

                    if (answer == wxID_CANCEL) return;
                    if (answer == wxID_YES) wxLaunchDefaultBrowser("https://github.com/JacobBruce/Wordsmith/releases");
                }
            } else {
                checkBtn->SetLabel(_("Error Occurred"));
            }

            checkBtn->SetLabel(_("Check for Update"));
            break;
        }
        case wxWebRequest::State_Active:
        case wxWebRequest::State_Idle:
            break;
        case wxWebRequest::State_Cancelled:
        case wxWebRequest::State_Unauthorized:
        case wxWebRequest::State_Failed:
            //event.GetErrorDescription()
            checkBtn->SetLabel(_("Request Failed"));
            break;
    }
}

void wsAboutDialog::CloseButtonClick(wxCommandEvent& event)
{
    Hide();
    checkBtn->SetLabel(_("Check for Update"));
}

void wsAboutDialog::ShowDialog()
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::int64_t timestamp = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();

    if (timestamp - lastCheck > 1000) {
        checkBtn->Enable(true);
    } else {
        checkBtn->Enable(false);
    }

    ShowModal();
}

/// START wsHtmlWindow

wsHtmlWindow::wsHtmlWindow(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style) :
    wxHtmlWindow(parent, id, pos, size, style)
{
    Bind(wxEVT_HTML_LINK_CLICKED, &wsHtmlWindow::OnLinkClicked, this);
}

void wsHtmlWindow::OnLinkClicked(const wxHtmlLinkEvent& event)
{
    wxHtmlLinkInfo info = event.GetLinkInfo();
    wxString url = info.GetHref();
    wxLaunchDefaultBrowser(url);
}

/// START HTMLFrame

HTMLFrame::HTMLFrame() :
    wxFrame(NULL, wxID_ANY, _("Web Document Viewer"), wxDefaultPosition, wxSize(700, 1000), wxDEFAULT_FRAME_STYLE),
    viewMode(0)
{
    wxMenuBar* MenuBar1 = new wxMenuBar();

    wxMenu* fileMenu = new wxMenu();
    wxMenuItem* newMenuItem = new wxMenuItem(fileMenu, wxNewId(), _("Close"), wxEmptyString, wxITEM_NORMAL);
    Connect(newMenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&OnCloseClick);
    fileMenu->Append(newMenuItem);
    MenuBar1->Append(fileMenu, _("&File"));

    wxMenu* viewMenu = new wxMenu();
    mdMenuItem = new wxMenuItem(viewMenu, wxNewId(), _("Markdown"), wxEmptyString, wxITEM_CHECK);
    Connect(mdMenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&SetMode0);
    viewMenu->Append(mdMenuItem);
    mdMenuItem->Check(true);

    htmlMenuItem = new wxMenuItem(viewMenu, wxNewId(), _("HTML"), wxEmptyString, wxITEM_CHECK);
    Connect(htmlMenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&SetMode1);
    viewMenu->Append(htmlMenuItem);
    htmlMenuItem->Check(false);
    viewMenu->AppendSeparator();

    newMenuItem = new wxMenuItem(viewMenu, wxNewId(), _("Refresh"), wxEmptyString, wxITEM_NORMAL);
    Connect(newMenuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&ReloadPage);
    viewMenu->Append(newMenuItem);
    MenuBar1->Append(viewMenu, _("&View"));

    SetMenuBar(MenuBar1);

    webView = wxWebView::New(this, wxID_ANY, wxWebViewDefaultURLStr, wxDefaultPosition, wxDefaultSize, wxWebViewBackendDefault, wxBORDER_NONE);
    webView->EnableContextMenu(false);
    //webView->EnableAccessToDevTools(true);
    webView->Bind(wxEVT_WEBVIEW_NAVIGATING, OnNavigationRequest, this);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(webView, 1, wxEXPAND);
    SetSizer(sizer);

    CenterOnScreen();

    Bind(wxEVT_CLOSE_WINDOW, &OnClose, this);

    std::string errStr;

    if (wxSystemSettings::GetAppearance().IsDark()) {
        cssStr = ReadFileStr(u8"./files/css/md_dark.css", errStr);
    } else {
        cssStr = ReadFileStr(u8"./files/css/md_light.css", errStr);
    }

    if (!errStr.empty()) wxMessageBox(errStr, _("Error"), wxOK|wxICON_ERROR|wxCENTER);
}

void HTMLFrame::OnClose(wxCloseEvent& event)
{
    event.Veto();
    Hide();
}

void HTMLFrame::OnCloseClick(wxCommandEvent& event)
{
    Hide();
}

void HTMLFrame::OnNavigationRequest(wxWebViewEvent& event)
{
    wxString url = event.GetURL();

    if (url.starts_with("http://") || url.starts_with("https://")) {
        event.Veto();
        wxLaunchDefaultBrowser(url);
    }
}

void HTMLFrame::ReloadPage()
{
    if (viewMode == 0) {
        std::string errStr;
        std::u8string fpu8((const char8_t*)filePath.utf8_string().c_str());
        std::string fileDir(ParentPath(fpu8) + "/");
        std::string textStr(ReadFileStr(fpu8, errStr));

        if (errStr.empty()) {
            std::string htmlStr = "<!DOCTYPE html><html><head><base href='" + EncodeUriPath(fileDir) +
                                "'><style>" + cssStr + "</style></head><body>" + MDtoHTML(textStr) + "</body></html>";

            wxString tmpFile = wxStandardPaths::Get().GetTempDir() + "/temp_wordsmith_doc.md.html";
            errStr = WriteFileStr((const char8_t*)tmpFile.utf8_string().c_str(), htmlStr);

            if (errStr.empty())
                webView->LoadURL(tmpFile);
        } else {
            wxMessageBox(errStr, _("Error"), wxOK|wxICON_ERROR|wxCENTER);
        }
    } else {
        webView->LoadURL(filePath);
    }
}

void HTMLFrame::SetMode0(wxCommandEvent& event)
{
    viewMode = 0;
    htmlMenuItem->Check(false);
    mdMenuItem->Check(true);
    ReloadPage();
}

void HTMLFrame::SetMode1(wxCommandEvent& event)
{
    viewMode = 1;
    htmlMenuItem->Check(true);
    mdMenuItem->Check(false);
    ReloadPage();
}

void HTMLFrame::SetMode(const int& mode)
{
    if (mode == 0) {
        viewMode = 0;
        htmlMenuItem->Check(false);
        mdMenuItem->Check(true);
    } else {
        viewMode = 1;
        htmlMenuItem->Check(true);
        mdMenuItem->Check(false);
    }
}

void HTMLFrame::LoadFile(const wxString& file_path)
{
    wxString lowFile(file_path.Lower());

    if (lowFile.EndsWith(".md")) {
        SetMode(0);
    } else if (lowFile.EndsWith(".html") || lowFile.EndsWith(".htm")) {
        SetMode(1);
    }

    filePath = file_path;
    ReloadPage();
}

/// START WordsmithFrame

WordsmithFrame::WordsmithFrame(wxWindow* parent,wxWindowID id) :
    spellChecker(std::make_unique<yams::symspell::MemoryStore>(), 2, 7),
    findDialog(nullptr),
    easyPrint("Printing", this)
{
    //(*Initialize(WordsmithFrame)
    wxMenu* FileMenu;
    wxMenu* HelpMenu;
    wxMenuBar* MenuBar1;
    wxMenuItem* AboutMenuItem;
    wxMenuItem* QuitMenuItem;

    Create(parent, wxID_ANY, _("Wordsmith Text Editor"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetMinSize(wxSize(500,350));
    {
        wxIcon FrameIcon;
        FrameIcon.CopyFromBitmap(wxBitmap(wxImage(_T("./files/icons/app_icon.png"))));
        SetIcon(FrameIcon);
    }
    AuiManager1 = new wxAuiManager(this, wxAUI_MGR_DEFAULT);
    AuiNotebook1 = new wxAuiNotebook(this, ID_AUINOTEBOOK1, wxDefaultPosition, wxDefaultSize, wxAUI_NB_DEFAULT_STYLE|wxBORDER_NONE);
    MenuBar1 = new wxMenuBar();
    FileMenu = new wxMenu();
    NewMenuItem = new wxMenuItem(FileMenu, ID_MENUITEM2, _("New\tCtrl-N"), _("Create new file"), wxITEM_NORMAL);
    FileMenu->Append(NewMenuItem);
    OpenMenuItem = new wxMenuItem(FileMenu, ID_MENUITEM3, _("Open\tCtrl-O"), _("Open file"), wxITEM_NORMAL);
    FileMenu->Append(OpenMenuItem);
    SaveMenuItem = new wxMenuItem(FileMenu, ID_MENUITEM4, _("Save\tCtrl-S"), _("Save file"), wxITEM_NORMAL);
    FileMenu->Append(SaveMenuItem);
    SaveAsMenuItem = new wxMenuItem(FileMenu, ID_MENUITEM5, _("Save As\tCtrl-Shift-S"), _("Save file with new name"), wxITEM_NORMAL);
    FileMenu->Append(SaveAsMenuItem);
    FileMenu->AppendSeparator();
    PageMenuItem = new wxMenuItem(FileMenu, ID_MENUITEM30, _("Page Setup"), _("Printer page setup"), wxITEM_NORMAL);
    FileMenu->Append(PageMenuItem);
    PreviewMenuItem = new wxMenuItem(FileMenu, ID_MENUITEM25, _("Preview"), _("Print preview"), wxITEM_NORMAL);
    FileMenu->Append(PreviewMenuItem);
    PrintMenuItem = new wxMenuItem(FileMenu, ID_MENUITEM26, _("Print\tCtrl-P"), _("Print document"), wxITEM_NORMAL);
    FileMenu->Append(PrintMenuItem);
    FileMenu->AppendSeparator();
    QuitMenuItem = new wxMenuItem(FileMenu, ID_MENUITEM1, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    FileMenu->Append(QuitMenuItem);
    MenuBar1->Append(FileMenu, _("&File"));
    EditMenu = new wxMenu();
    UndoMenuItem = new wxMenuItem(EditMenu, ID_MENUITEM6, _("Undo\tCtrl-Z"), _("Undo action"), wxITEM_NORMAL);
    EditMenu->Append(UndoMenuItem);
    RedoMenuItem = new wxMenuItem(EditMenu, ID_MENUITEM7, _("Redo\tCtrl-Y"), _("Redo action"), wxITEM_NORMAL);
    EditMenu->Append(RedoMenuItem);
    EditMenu->AppendSeparator();
    CutMenuItem = new wxMenuItem(EditMenu, ID_MENUITEM8, _("Cut\tCtrl-X"), _("Cut text"), wxITEM_NORMAL);
    EditMenu->Append(CutMenuItem);
    CopyMenuItem = new wxMenuItem(EditMenu, ID_MENUITEM9, _("Copy\tCtrl-C"), _("Copy text"), wxITEM_NORMAL);
    EditMenu->Append(CopyMenuItem);
    PasteMenuItem = new wxMenuItem(EditMenu, ID_MENUITEM10, _("Paste\tCtrl-V"), _("Paste text"), wxITEM_NORMAL);
    EditMenu->Append(PasteMenuItem);
    EditMenu->AppendSeparator();
    FindMenuItem = new wxMenuItem(EditMenu, ID_MENUITEM11, _("Find\tCtrl-F"), _("Find text"), wxITEM_NORMAL);
    EditMenu->Append(FindMenuItem);
    NextMenuItem = new wxMenuItem(EditMenu, ID_MENUITEM39, _("Find Next\tF3"), _("Find next match"), wxITEM_NORMAL);
    EditMenu->Append(NextMenuItem);
    ReplaceMenuItem = new wxMenuItem(EditMenu, ID_MENUITEM12, _("Replace\tCtrl-R"), _("Replace text"), wxITEM_NORMAL);
    EditMenu->Append(ReplaceMenuItem);
    EditMenu->AppendSeparator();
    SelectMenuItem = new wxMenuItem(EditMenu, ID_MENUITEM13, _("Select All\tCtrl-A"), _("Select all text"), wxITEM_NORMAL);
    EditMenu->Append(SelectMenuItem);
    MenuBar1->Append(EditMenu, _("&Edit"));
    ViewMenu = new wxMenu();
    ZoomMenuItem = new wxMenu();
    MenuItem49 = new wxMenuItem(ZoomMenuItem, ID_MENUITEM47, _("Zoom In\tCtrl-+"), wxEmptyString, wxITEM_NORMAL);
    ZoomMenuItem->Append(MenuItem49);
    MenuItem50 = new wxMenuItem(ZoomMenuItem, ID_MENUITEM48, _("Zoom Out\tCtrl--"), wxEmptyString, wxITEM_NORMAL);
    ZoomMenuItem->Append(MenuItem50);
    MenuItem51 = new wxMenuItem(ZoomMenuItem, ID_MENUITEM49, _("Reset\tCtrl-0"), wxEmptyString, wxITEM_NORMAL);
    ZoomMenuItem->Append(MenuItem51);
    ViewMenu->Append(ID_MENUITEM46, _("Zoom"), ZoomMenuItem, _("Change zoom level"));
    ViewMenu->AppendSeparator();
    ToolBarMenuItem = new wxMenuItem(ViewMenu, ID_MENUITEM14, _("Tool Bar"), _("Toggle tool bar"), wxITEM_NORMAL);
    ViewMenu->Append(ToolBarMenuItem);
    StatusBarMenuItem = new wxMenuItem(ViewMenu, ID_MENUITEM15, _("Status Bar"), _("Toggle status bar"), wxITEM_NORMAL);
    ViewMenu->Append(StatusBarMenuItem);
    ViewMenu->AppendSeparator();
    WebViewMenuItem = new wxMenuItem(ViewMenu, ID_MENUITEM28, _("Web Viewer\tF9"), _("Preview Markdown and HTML documents"), wxITEM_NORMAL);
    ViewMenu->Append(WebViewMenuItem);
    MenuBar1->Append(ViewMenu, _("&View"));
    InsertMenu = new wxMenu();
    MarkdownMenuItem = new wxMenu();
    MenuItem33 = new wxMenuItem(MarkdownMenuItem, ID_MENUITEM31, _("Title"), wxEmptyString, wxITEM_NORMAL);
    MarkdownMenuItem->Append(MenuItem33);
    MenuItem34 = new wxMenuItem(MarkdownMenuItem, ID_MENUITEM32, _("Link"), wxEmptyString, wxITEM_NORMAL);
    MarkdownMenuItem->Append(MenuItem34);
    MenuItem35 = new wxMenuItem(MarkdownMenuItem, ID_MENUITEM33, _("Image"), wxEmptyString, wxITEM_NORMAL);
    MarkdownMenuItem->Append(MenuItem35);
    MenuItem36 = new wxMenuItem(MarkdownMenuItem, ID_MENUITEM34, _("Quote"), wxEmptyString, wxITEM_NORMAL);
    MarkdownMenuItem->Append(MenuItem36);
    MenuItem37 = new wxMenuItem(MarkdownMenuItem, ID_MENUITEM35, _("Code"), wxEmptyString, wxITEM_NORMAL);
    MarkdownMenuItem->Append(MenuItem37);
    MenuItem38 = new wxMenuItem(MarkdownMenuItem, ID_MENUITEM36, _("List"), wxEmptyString, wxITEM_NORMAL);
    MarkdownMenuItem->Append(MenuItem38);
    MenuItem40 = new wxMenuItem(MarkdownMenuItem, ID_MENUITEM38, _("Rule"), wxEmptyString, wxITEM_NORMAL);
    MarkdownMenuItem->Append(MenuItem40);
    MenuItem39 = new wxMenuItem(MarkdownMenuItem, ID_MENUITEM37, _("Styled Text"), wxEmptyString, wxITEM_NORMAL);
    MarkdownMenuItem->Append(MenuItem39);
    InsertMenu->Append(ID_MENUITEM16, _("Markdown"), MarkdownMenuItem, wxEmptyString);
    DateTimeMenuItem = new wxMenuItem(InsertMenu, ID_MENUITEM50, _("Date Time\tF5"), _("Insert current time and date"), wxITEM_NORMAL);
    InsertMenu->Append(DateTimeMenuItem);
    TimestampMenuItem = new wxMenuItem(InsertMenu, ID_MENUITEM29, _("Timestamp\tF6"), _("Insert unix timestamp"), wxITEM_NORMAL);
    InsertMenu->Append(TimestampMenuItem);
    MenuBar1->Append(InsertMenu, _("&Insert"));
    ToolsMenu = new wxMenu();
    TextStatsMenuItem = new wxMenuItem(ToolsMenu, ID_MENUITEM17, _("Text Stats"), _("Show text stats"), wxITEM_NORMAL);
    ToolsMenu->Append(TextStatsMenuItem);
    SessionMenuItem = new wxMenuItem(ToolsMenu, ID_MENUITEM18, _("Session Stats"), _("Show session stats"), wxITEM_NORMAL);
    ToolsMenu->Append(SessionMenuItem);
    ToolsMenu->AppendSeparator();
    DictionaryMenuItem = new wxMenuItem(ToolsMenu, ID_MENUITEM22, _("Dictionary"), _("Show dictionary"), wxITEM_NORMAL);
    ToolsMenu->Append(DictionaryMenuItem);
    WordsMenuItem = new wxMenuItem(ToolsMenu, ID_MENUITEM23, _("Word Manager"), _("Add or remove words"), wxITEM_NORMAL);
    ToolsMenu->Append(WordsMenuItem);
    MenuItem1 = new wxMenuItem(ToolsMenu, ID_MENUITEM52, _("Phrase Manager"), _("Add or remove phrases"), wxITEM_NORMAL);
    ToolsMenu->Append(MenuItem1);
    ToolsMenu->AppendSeparator();
    HashMenuItem = new wxMenu();
    MenuItem43 = new wxMenuItem(HashMenuItem, ID_MENUITEM41, _("MD5"), wxEmptyString, wxITEM_NORMAL);
    HashMenuItem->Append(MenuItem43);
    CryptoMenuItem = new wxMenuItem(HashMenuItem, ID_MENUITEM27, _("CRC-32"), wxEmptyString, wxITEM_NORMAL);
    HashMenuItem->Append(CryptoMenuItem);
    MenuItem44 = new wxMenuItem(HashMenuItem, ID_MENUITEM42, _("SHA-1"), wxEmptyString, wxITEM_NORMAL);
    HashMenuItem->Append(MenuItem44);
    MenuItem45 = new wxMenuItem(HashMenuItem, ID_MENUITEM43, _("SHA2-256"), wxEmptyString, wxITEM_NORMAL);
    HashMenuItem->Append(MenuItem45);
    MenuItem46 = new wxMenuItem(HashMenuItem, ID_MENUITEM44, _("SHA2-512"), wxEmptyString, wxITEM_NORMAL);
    HashMenuItem->Append(MenuItem46);
    ToolsMenu->Append(ID_MENUITEM40, _("Hash"), HashMenuItem, _("Calculate document hash"));
    MenuBar1->Append(ToolsMenu, _("&Tools"));
    SettingsMenu = new wxMenu();
    FontStyleMenuItem = new wxMenuItem(SettingsMenu, ID_MENUITEM19, _("Font Style"), _("Show font settings"), wxITEM_NORMAL);
    SettingsMenu->Append(FontStyleMenuItem);
    FontColorMenuItem = new wxMenuItem(SettingsMenu, ID_MENUITEM45, _("Font Color"), _("Pick font color"), wxITEM_NORMAL);
    SettingsMenu->Append(FontColorMenuItem);
    SettingsMenu->AppendSeparator();
    WordWrapMenuItem = new wxMenuItem(SettingsMenu, ID_MENUITEM20, _("Word Wrap"), _("Toggle word wrap"), wxITEM_CHECK);
    SettingsMenu->Append(WordWrapMenuItem);
    WordWrapMenuItem->Check(true);
    SpellCheckMenuItem = new wxMenuItem(SettingsMenu, ID_MENUITEM51, _("Spell Check"), _("Toggle spell check"), wxITEM_CHECK);
    SettingsMenu->Append(SpellCheckMenuItem);
    SpellCheckMenuItem->Check(true);
    SettingsMenu->AppendSeparator();
    PreferencesMenuItem = new wxMenuItem(SettingsMenu, ID_MENUITEM21, _("Preferences"), _("Edit preferences"), wxITEM_NORMAL);
    SettingsMenu->Append(PreferencesMenuItem);
    MenuBar1->Append(SettingsMenu, _("&Settings"));
    HelpMenu = new wxMenu();
    AboutMenuItem = new wxMenuItem(HelpMenu, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    HelpMenu->Append(AboutMenuItem);
    TipsMenuItem = new wxMenuItem(HelpMenu, ID_MENUITEM24, _("Tips\tF12"), _("Show helpful tips"), wxITEM_NORMAL);
    HelpMenu->Append(TipsMenuItem);
    MenuBar1->Append(HelpMenu, _("&Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, wxBORDER_NONE, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[4] = { -15, -5, -5, -5 };
    int __wxStatusBarStyles_1[4] = { wxSB_NORMAL, wxSB_NORMAL, wxSB_NORMAL, wxSB_NORMAL };
    StatusBar1->SetFieldsCount(4,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(4,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    ToolBar1 = new wxToolBar(this, ID_TOOLBAR1, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL, _T("ID_TOOLBAR1"));
    NewToolBarBtn = ToolBar1->AddTool(new_btn, _("New"), wxBitmap(wxImage(_T("./files/icons/new_file_x32.png"))), wxNullBitmap, wxITEM_NORMAL, _("New file"), _("Create new file"));
    OpenToolBarBtn = ToolBar1->AddTool(open_btn, _("Open"), wxBitmap(wxImage(_T("./files/icons/open_file_x32.png"))), wxNullBitmap, wxITEM_NORMAL, _("Open file"), _("Open file"));
    SaveToolBarBtn = ToolBar1->AddTool(save_btn, _("Save"), wxBitmap(wxImage(_T("./files/icons/save_file_x32.png"))), wxNullBitmap, wxITEM_NORMAL, _("Save file"), _("Save file"));
    SaveAsToolBarBtn = ToolBar1->AddTool(saveas_btn, _("Save As"), wxBitmap(wxImage(_T("./files/icons/saveas_file_x32.png"))), wxNullBitmap, wxITEM_NORMAL, _("Save file as"), _("Save file with new name"));
    UndoToolBarBtn = ToolBar1->AddTool(undo_btn, _("Undo"), wxBitmap(wxImage(_T("./files/icons/undo_x32.png"))), wxNullBitmap, wxITEM_NORMAL, _("Undo action"), _("Undo last action"));
    RedoToolBarBtn = ToolBar1->AddTool(redo_btn, _("Redo"), wxBitmap(wxImage(_T("./files/icons/redo_x32.png"))), wxNullBitmap, wxITEM_NORMAL, _("Redo action"), _("Redo last action"));
    CutToolBarBtn = ToolBar1->AddTool(cut_btn, _("Cut"), wxBitmap(wxImage(_T("./files/icons/cut_x32.png"))), wxNullBitmap, wxITEM_NORMAL, _("Cut text"), _("Cut text"));
    CopyToolBarBtn = ToolBar1->AddTool(copy_btn, _("Copy"), wxBitmap(wxImage(_T("./files/icons/copy_x32.png"))), wxNullBitmap, wxITEM_NORMAL, _("Copy text"), _("Copy text"));
    PasteToolBarBtn = ToolBar1->AddTool(paste_btn, _("Paste"), wxBitmap(wxImage(_T("./files/icons/paste_x32.png"))), wxNullBitmap, wxITEM_NORMAL, _("Paste text"), _("Paste text"));
    FindToolBarBtn = ToolBar1->AddTool(find_btn, _("Find"), wxBitmap(wxImage(_T("./files/icons/search_x32.png"))), wxNullBitmap, wxITEM_NORMAL, _("Find text"), _("Find text"));
    DictToolBarBtn = ToolBar1->AddTool(dict_btn, _("Dict"), wxBitmap(wxImage(_T("./files/icons/book_x32.png"))), wxNullBitmap, wxITEM_NORMAL, _("Show dictionary"), _("Show dictionary"));
    TipsToolBarBtn = ToolBar1->AddTool(tips_btn, _("Tips"), wxBitmap(wxImage(_T("./files/icons/tips_x32.png"))), wxNullBitmap, wxITEM_NORMAL, _("Show tips"), _("Show helpful tips"));
    ToolBar1->Realize();
    SetToolBar(ToolBar1);
    FileDialog1 = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    ErrorDialog1 = new wxMessageDialog(this, wxEmptyString, _("Error"), wxOK|wxICON_ERROR, wxDefaultPosition);
    wxString __wxSingleChoiceDialogChoices_1[3] =
    {
        _("Text"),
        _("HTML"),
        _("Markdown")
    };
    SingleChoiceDialog1 = new wxSingleChoiceDialog(this, _("Document Type"), _("Choose"), 3, __wxSingleChoiceDialogChoices_1, 0, wxCHOICEDLG_STYLE, wxDefaultPosition);
    MessageDialog1 = new wxMessageDialog(this, wxEmptyString, _("Message"), wxOK|wxICON_INFORMATION, wxDefaultPosition);
    QuestionDialog1 = new wxMessageDialog(this, wxEmptyString, _("Question"), wxYES_NO|wxICON_QUESTION, wxDefaultPosition);
    ColourDialog1 = new wxColourDialog(this);
    TextEntryDialog1 = new wxTextEntryDialog(this, _("test"), wxEmptyString, wxEmptyString, wxOK|wxCANCEL|wxCENTRE|wxWS_EX_VALIDATE_RECURSIVELY, wxDefaultPosition);

    Connect(ID_AUINOTEBOOK1, wxEVT_COMMAND_AUINOTEBOOK_PAGE_CLOSE, (wxObjectEventFunction)&WordsmithFrame::OnTabPageClose);
    Connect(ID_AUINOTEBOOK1, wxEVT_COMMAND_AUINOTEBOOK_PAGE_CLOSED, (wxObjectEventFunction)&WordsmithFrame::OnTabPageClosed);
    Connect(ID_AUINOTEBOOK1, wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, (wxObjectEventFunction)&WordsmithFrame::OnTabPageChanged);
    Connect(ID_MENUITEM2, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnNewFileClick);
    Connect(ID_MENUITEM3, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnOpenFileClick);
    Connect(ID_MENUITEM4, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnSaveClick);
    Connect(ID_MENUITEM5, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnSaveAsClick);
    Connect(ID_MENUITEM30, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnPageClick);
    Connect(ID_MENUITEM25, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnPreviewClick);
    Connect(ID_MENUITEM26, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnPrintClick);
    Connect(ID_MENUITEM1, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnQuit);
    Connect(ID_MENUITEM6, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnUndoClick);
    Connect(ID_MENUITEM7, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnRedoClick);
    Connect(ID_MENUITEM8, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnCutClick);
    Connect(ID_MENUITEM9, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnCopyClick);
    Connect(ID_MENUITEM10, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnPasteClick);
    Connect(ID_MENUITEM11, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnFindClick);
    Connect(ID_MENUITEM39, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnFindNextClick);
    Connect(ID_MENUITEM12, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnReplaceClick);
    Connect(ID_MENUITEM13, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnSelectAllClick);
    Connect(ID_MENUITEM47, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnZoomInClick);
    Connect(ID_MENUITEM48, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnZoomOutClick);
    Connect(ID_MENUITEM49, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnZoomResetClick);
    Connect(ID_MENUITEM14, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnToggleToolBar);
    Connect(ID_MENUITEM15, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnToggleStatusBar);
    Connect(ID_MENUITEM28, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnDocViewClick);
    Connect(ID_MENUITEM31, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnAddMarkdownClick);
    Connect(ID_MENUITEM32, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnAddMarkdownClick);
    Connect(ID_MENUITEM33, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnAddMarkdownClick);
    Connect(ID_MENUITEM34, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnAddMarkdownClick);
    Connect(ID_MENUITEM35, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnAddMarkdownClick);
    Connect(ID_MENUITEM36, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnAddMarkdownClick);
    Connect(ID_MENUITEM38, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnAddMarkdownClick);
    Connect(ID_MENUITEM37, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnAddMarkdownClick);
    Connect(ID_MENUITEM50, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnDateTimeClick);
    Connect(ID_MENUITEM29, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnTimestampClick);
    Connect(ID_MENUITEM17, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnTextStatsClick);
    Connect(ID_MENUITEM18, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnSessionStatsClick);
    Connect(ID_MENUITEM22, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnDictionaryClick);
    Connect(ID_MENUITEM23, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnWordManagerClick);
    Connect(ID_MENUITEM52, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnPhraseManagerClick);
    Connect(ID_MENUITEM41, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnHashClick);
    Connect(ID_MENUITEM27, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnHashClick);
    Connect(ID_MENUITEM42, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnHashClick);
    Connect(ID_MENUITEM43, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnHashClick);
    Connect(ID_MENUITEM44, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnHashClick);
    Connect(ID_MENUITEM19, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnFontClick);
    Connect(ID_MENUITEM45, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnFontColorClick);
    Connect(ID_MENUITEM20, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnToggleWordWrap);
    Connect(ID_MENUITEM51, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnToggleSpellCheck);
    Connect(ID_MENUITEM21, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnPreferencesClick);
    Connect(idMenuAbout, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnAboutClick);
    Connect(ID_MENUITEM24, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&WordsmithFrame::OnTipsClick);
    Connect(new_btn, wxEVT_COMMAND_TOOL_CLICKED, (wxObjectEventFunction)&WordsmithFrame::OnNewFileClick);
    Connect(open_btn, wxEVT_COMMAND_TOOL_CLICKED, (wxObjectEventFunction)&WordsmithFrame::OnOpenFileClick);
    Connect(save_btn, wxEVT_COMMAND_TOOL_CLICKED, (wxObjectEventFunction)&WordsmithFrame::OnSaveClick);
    Connect(saveas_btn, wxEVT_COMMAND_TOOL_CLICKED, (wxObjectEventFunction)&WordsmithFrame::OnSaveAsClick);
    Connect(undo_btn, wxEVT_COMMAND_TOOL_CLICKED, (wxObjectEventFunction)&WordsmithFrame::OnUndoClick);
    Connect(redo_btn, wxEVT_COMMAND_TOOL_CLICKED, (wxObjectEventFunction)&WordsmithFrame::OnRedoClick);
    Connect(cut_btn, wxEVT_COMMAND_TOOL_CLICKED, (wxObjectEventFunction)&WordsmithFrame::OnCutClick);
    Connect(copy_btn, wxEVT_COMMAND_TOOL_CLICKED, (wxObjectEventFunction)&WordsmithFrame::OnCopyClick);
    Connect(paste_btn, wxEVT_COMMAND_TOOL_CLICKED, (wxObjectEventFunction)&WordsmithFrame::OnPasteClick);
    Connect(find_btn, wxEVT_COMMAND_TOOL_CLICKED, (wxObjectEventFunction)&WordsmithFrame::OnFindClick);
    Connect(dict_btn, wxEVT_COMMAND_TOOL_CLICKED, (wxObjectEventFunction)&WordsmithFrame::OnDictionaryClick);
    Connect(tips_btn, wxEVT_COMMAND_TOOL_CLICKED, (wxObjectEventFunction)&WordsmithFrame::OnTipsClick);
    Connect(wxID_ANY, wxEVT_CLOSE_WINDOW, (wxObjectEventFunction)&WordsmithFrame::OnClose);
    //*)

    SetClientSize(wxSize(stoi(GLOBALS::Settings["WIN_WIDTH"]), stoi(GLOBALS::Settings["WIN_HEIGHT"])));

    if (GLOBALS::Settings["WIN_X"] != "default")
        SetPosition(wxPoint(stoi(GLOBALS::Settings["WIN_X"]), stoi(GLOBALS::Settings["WIN_Y"])));

    if (GLOBALS::Settings["TB"] == "0") ToolBar1->Hide();
    if (GLOBALS::Settings["SB"] == "0") StatusBar1->Hide();

    SessionWatch.Start();

    Connect(wxID_ANY, wxEVT_FIND_CLOSE, (wxObjectEventFunction)&OnFindClose);
    Connect(wxID_ANY, wxEVT_FIND, (wxObjectEventFunction)&OnFindFirst);
    Connect(wxID_ANY, wxEVT_FIND_NEXT, (wxObjectEventFunction)&OnFindNext);
    Connect(wxID_ANY, wxEVT_FIND_REPLACE, (wxObjectEventFunction)&OnFindReplace);
    Connect(wxID_ANY, wxEVT_FIND_REPLACE_ALL, (wxObjectEventFunction)&OnFindReplaceAll);

    ToolBar1->Bind(wxEVT_TOOL_ENTER, &OnMenuHover, this);

    FileMenu->Bind(wxEVT_MENU_CLOSE, &OnMenuClose, this);
    EditMenu->Bind(wxEVT_MENU_CLOSE, &OnMenuClose, this);
    ViewMenu->Bind(wxEVT_MENU_CLOSE, &OnMenuClose, this);
    InsertMenu->Bind(wxEVT_MENU_CLOSE, &OnMenuClose, this);
    ToolsMenu->Bind(wxEVT_MENU_CLOSE, &OnMenuClose, this);
    SettingsMenu->Bind(wxEVT_MENU_CLOSE, &OnMenuClose, this);
    HelpMenu->Bind(wxEVT_MENU_CLOSE, &OnMenuClose, this);

    FileMenu->Bind(wxEVT_MENU_OPEN, &OnMenuOpen, this);
    EditMenu->Bind(wxEVT_MENU_OPEN, &OnMenuOpen, this);
    ViewMenu->Bind(wxEVT_MENU_OPEN, &OnMenuOpen, this);
    InsertMenu->Bind(wxEVT_MENU_OPEN, &OnMenuOpen, this);
    ToolsMenu->Bind(wxEVT_MENU_OPEN, &OnMenuOpen, this);
    SettingsMenu->Bind(wxEVT_MENU_OPEN, &OnMenuOpen, this);
    HelpMenu->Bind(wxEVT_MENU_OPEN, &OnMenuOpen, this);

    initTimer.Bind(wxEVT_TIMER, &OnInitTimerTrigger, this);
    infoTimer.Bind(wxEVT_TIMER, &OnInfoTimerTrigger, this);
    toolsTimer.Bind(wxEVT_TIMER, &OnToolsTimerTrigger, this);
    statsTimer.Bind(wxEVT_TIMER, &OnStatsTimerTrigger, this);
    ackeyTimer.Bind(wxEVT_TIMER, &OnACKeyTimerTrigger, this);
    spellTimer.Bind(wxEVT_TIMER, &OnSpellCheckTrigger, this);

    docViewer = new HTMLFrame();
    docViewer->Hide();

    settingsDialog = new wsSettingsDialog(this, _("Preferences"));
    wordsDialog = new wsWordsDialog(this, _("Word Manager"));
    phrasesDialog = new wsPhrasesDialog(this, _("Phrase Manager"));
    dictDialog = new wsDictDialog(this, _("Dictionary Tool"));
    tipsDialog = new wsTipsDialog(this, _("Tips"));
    aboutDialog = new wsAboutDialog(this, _("About"));

    AuiNotebook1->SetArtProvider(new wxAuiDefaultTabArt());
    //AuiManager1->Update();

    std::string errStr, selFile;
    std::string tabFiles = ReadFileStr(u8"./files/open_files_list.ws", errStr);

    if (errStr.empty() && !tabFiles.empty()) {

        auto filePaths(ExplodeStr(tabFiles, "\n"));

        for (const std::string& filePath : filePaths)
        {
            std::vector<std::string> settings(ExplodeStr(filePath, "\r"));

            if (settings.size() != 5) continue;
            if (settings[4] == "1") selFile = settings[0];

            if (FileExists((const char8_t*)settings[0].c_str())) {

                NewPadTab(stoi(settings[2]), stoi(settings[3]));
                LoadDocument(wxString::FromUTF8(settings[0]), wxString::FromUTF8(FileName((const char8_t*)settings[0].c_str())));

                if (settings[1] != "default") {
                    std::vector<std::string> fontData(ExplodeStr(settings[1], "|"));
                    if (fontData.size() == 5) {
                        wxFont customFont;
                        wxColor fontColor(fontData[4]);
                        customFont.SetFaceName(fontData[0]);
                        customFont.SetPointSize(stoi(fontData[1]));
                        customFont.SetWeight(wxFontWeight(stoi(fontData[2])));
                        customFont.SetStyle(wxFontStyle(stoi(fontData[3])));
                        GLOBALS::TabPageSTC->SetColoredFont(customFont, fontColor);
                    }
                }
            }
        }
    }

    if (GLOBALS::TabPageSTC == nullptr) {
        NewPadTab();
    } else if (!selFile.empty()) {
        SelectTabPage(selFile);
    }

    auto loadFunc = [this] () {

        if (!(WordParser::LoadWordNet(GLOBALS::WordNet, GLOBALS::WordSyn, "./files/wordnet.txt") &&
        WordParser::LoadWordWeb(GLOBALS::WordMap, GLOBALS::WordVec, "./files/wordweb.txt") &&
        WordParser::LoadSimWords(GLOBALS::SimWords, "./files/wordsims.txt")))
        {
            ErrorDialog1->SetMessage(_("Failed to load word files. Ensure there's a folder called 'files' along with the executable."));
            ErrorDialog1->ShowModal();
            return;
        }

        for (const auto& entry : GLOBALS::WordVec)
            spellChecker.createDictionaryEntry(entry.first, entry.second);

        for (const auto& entry : GLOBALS::WordSyn)
        {
            dictDialog->AddWordToAC(entry.first);

            if (entry.first.find(' ') == std::string::npos && !GLOBALS::WordMap.contains(entry.first))
                spellChecker.createDictionaryEntry(entry.first, 1);
        }

        WordParser::GenDictMap(GLOBALS::WordVec, GLOBALS::WebIndices);
        GLOBALS::GotWordData = true;
    };

    StatusBar1->SetStatusText(_("Loading word files ..."), 0);

    GLOBALS::LoadThread = new std::thread(loadFunc);

    GLOBALS::LoadThread->detach();

    initTimer.Start(500, true);

    UpdateStatusBar();
}

WordsmithFrame::~WordsmithFrame()
{
    //(*Destroy(WordsmithFrame)
    FileDialog1->Destroy();
    ErrorDialog1->Destroy();
    SingleChoiceDialog1->Destroy();
    MessageDialog1->Destroy();
    QuestionDialog1->Destroy();
    ColourDialog1->Destroy();
    TextEntryDialog1->Destroy();
    //*)
    docViewer->Destroy();
    settingsDialog->Destroy();
    wordsDialog->Destroy();
    phrasesDialog->Destroy();
    dictDialog->Destroy();
    tipsDialog->Destroy();
    aboutDialog->Destroy();
}

void WordsmithFrame::ShowFontDialog()
{
    if (GLOBALS::TabPageSTC != nullptr) {

        wxFontData fontData;
        fontData.EnableEffects(false);
        fontData.SetAllowSymbols(false);
        fontData.SetInitialFont(GLOBALS::TabPageSTC->StyleGetFont(wxSTC_STYLE_DEFAULT));

        wxFontDialog fontDialog(this, fontData);

        if (fontDialog.ShowModal() == wxID_CANCEL) return;

        GLOBALS::TabPageSTC->SetCustomFont(fontDialog.GetFontData().GetChosenFont());
    }
}

void WordsmithFrame::ShowPrintDialog(bool preview)
{
    if (SingleChoiceDialog1->ShowModal() == wxID_CANCEL) return;

    wxString printTxt(GLOBALS::TabPageSTC->GetText());

    if (SingleChoiceDialog1->GetSelection() == 0) {
        EncodeHTML(printTxt);
        printTxt.Replace("\r\n", "<br>");
        printTxt.Replace("\r", "<br>");
        printTxt.Replace("\n", "<br>");
        printTxt = "<html><body><p>" + printTxt + "</p></body></html>";
    } else if (SingleChoiceDialog1->GetSelection() == 2) {
        std::string htmlStr(MDtoHTML(printTxt.utf8_string()));
        ReplaceStr(htmlStr, "<ul>", "<br><br><ul>");
        ReplaceStr(htmlStr, "<ol>", "<br><br><ol>");
        ReplaceStr(htmlStr, "<table>", "<br><br><table>");
        printTxt = wxString::FromUTF8("<html><body>" + htmlStr + "</body></html>");
    }

	//easyPrint.SetHeader("Page @PAGENUM@/@PAGESCNT@", wxPAGE_ALL);

	if (preview) {
        easyPrint.PreviewText(printTxt);
	} else {
        easyPrint.PrintText(printTxt);
	}
}

void WordsmithFrame::ShowPageDialog()
{
    easyPrint.PageSetup();
}

void WordsmithFrame::ShowOpenDialog()
{
    FileDialog1->SetWindowStyleFlag(wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (FileDialog1->ShowModal() == wxID_CANCEL) return;
    const wxString filePath(FileDialog1->GetPath());

    if (SelectTabPage(filePath)) return;

    if (GLOBALS::TabPageSTC == nullptr) {
        NewPadTab();
    } else if (!GLOBALS::TabPageSTC->GetFilePath().empty()) {
        NewPadTab();
    } else if (GLOBALS::TabPageSTC->GetLength() > 0) {
        NewPadTab();
    }

    try {
        const std::uintmax_t fileSize = FileSize((const char8_t*)filePath.utf8_string().c_str());
        const wxString fileName(FileDialog1->GetFilename());

        if (fileSize > INT_MAX) {
            ErrorDialog1->SetMessage(_("The file cannot be loaded because it is too large."));
            ErrorDialog1->ShowModal();
        }

        LoadDocument(filePath, fileName);

        if (!WordParser::IsUTF8orASCII(GLOBALS::TabPageSTC->GetRange(0,2).utf8_string()) || (std::uintmax_t)GLOBALS::TabPageSTC->GetLength() != fileSize) {
            ErrorDialog1->SetMessage(_("Only UTF8 and ASCII files are supported. Editing the file may corrupt it."));
            ErrorDialog1->ShowModal();
        }
    } catch (...) {
        ErrorDialog1->SetMessage(_("Failed to load file: ") + filePath);
        ErrorDialog1->ShowModal();
    }
}

void WordsmithFrame::ShowSaveDialog(bool force_show)
{
    if (GLOBALS::TabPageSTC == nullptr) return;

    try {
        if (force_show || GLOBALS::TabPageSTC->GetFilePath().empty()) {
            FileDialog1->SetWindowStyleFlag(wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
            if (FileDialog1->ShowModal() == wxID_CANCEL) return;
            GLOBALS::TabPageSTC->SetFilePath(FileDialog1->GetPath());
            GLOBALS::TabPageSTC->SetFileName(FileDialog1->GetFilename());
            AuiNotebook1->SetPageText(AuiNotebook1->GetSelection(), GLOBALS::TabPageSTC->GetFileName());
        }

        if (GLOBALS::TabPageSTC->SaveFile(GLOBALS::TabPageSTC->GetFilePath())) {
            GLOBALS::TabPageSTC->SetChanged(false);
            AuiNotebook1->SetPageText(AuiNotebook1->GetSelection(), GLOBALS::TabPageSTC->GetFileName());
            if (docViewer->IsShown())
                docViewer->LoadFile(GLOBALS::TabPageSTC->GetFilePath());
        } else {
            ErrorDialog1->SetMessage(_("Failed to save file: ") + GLOBALS::TabPageSTC->GetFilePath());
            ErrorDialog1->ShowModal();
        }
    } catch (...) {
        ErrorDialog1->SetMessage(_("Error saving file: ") + GLOBALS::TabPageSTC->GetFilePath());
        ErrorDialog1->ShowModal();
    }
    /*wxFileOutputStream outputStream(FileDialog1->GetPath());
    if (outputStream.IsOk())
        outputStream.WriteAll(GLOBALS::TabPageSTC->GetText().data(), GLOBALS::TabPageSTC->GetLength());
    outputStream.Close();*/
}

void WordsmithFrame::ShowSearchDialog(bool show_replace)
{
    if (findDialog == nullptr) {
        findDialog = new wxFindReplaceDialog(this, &findData, wxEmptyString, 0);
        if (show_replace) {
            findDialog->SetWindowStyleFlag(wxFR_REPLACEDIALOG);
            findDialog->SetTitle(_("Find & Replace"));
        } else {
            findDialog->SetTitle(_("Find"));
        }
        findDialog->Show();
    }

    findDialog->Raise();
    findDialog->SetFocus();
}

bool WordsmithFrame::SelectTabPage(const wxString& file_name)
{
    for (size_t i=0; i < AuiNotebook1->GetPageCount(); ++i)
    {
        wsTextCtrl* stc((wsTextCtrl*)AuiNotebook1->GetPage(i)->GetChildren().GetFirst()->GetData());

        if (file_name == stc->GetFilePath()) {
            AuiNotebook1->SetSelection(i);
            stc->SetFocus();
            return true;
        }
    }

    return false;
}

void WordsmithFrame::LoadDocument(const wxString& file_path, const wxString& file_name)
{
    GLOBALS::TabPageSTC->LoadFile(file_path);
    GLOBALS::TabPageSTC->SetFileName(file_name);
    GLOBALS::TabPageSTC->SetFilePath(file_path);
    GLOBALS::TabPageSTC->SetChanged(false);
    AuiNotebook1->SetPageText(AuiNotebook1->GetSelection(), file_name);
}

void WordsmithFrame::BindTextCtrl(wsTextCtrl* stc)
{
    stc->Bind(wxEVT_STC_AUTOCOMP_COMPLETED, &OnAutoCompleted, this);
    stc->Bind(wxEVT_STC_MODIFIED, &OnTextChanged, this);
    stc->Bind(wxEVT_STC_DWELLSTART, &OnMouseHover, this);
    stc->Bind(wxEVT_STC_DWELLEND, &OnMouseHoverEnd, this);
    stc->Bind(wxEVT_LEFT_UP, &OnMouseUp, this);
    stc->Bind(wxEVT_RIGHT_UP, &OnMouseUp, this);
    stc->Bind(wxEVT_RIGHT_DOWN, &OnMouseRightDown, this);
    stc->Bind(wxEVT_CHAR, &OnKeyPress, this);
    stc->Bind(wxEVT_KEY_UP, &OnKeyUp, this);
    stc->Bind(wxEVT_CONTEXT_MENU, &OnContextMenu, this);
    stc->Bind(wxEVT_KILL_FOCUS, &OnTabLoseFocus, this);
}

void WordsmithFrame::NewPadTab(int wrap, int zoom)
{
    static uint64_t TabID = 1;
    std::wstring TabIDS(std::to_wstring(TabID++));

    wxPanel* NewPanel = new wxPanel(AuiNotebook1, wxNewId(), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE|wxTAB_TRAVERSAL, _T("ID_PANEL"+TabIDS));
    wsTextCtrl* newTextCtrl = new wsTextCtrl(NewPanel, wxNewId(), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE|wxWANTS_CHARS, _T("ID_STCTEXTCTRL"+TabIDS));
    BindTextCtrl(newTextCtrl);

    wxBoxSizer* BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer1->Add(newTextCtrl, 1, wxEXPAND);
    NewPanel->SetSizer(BoxSizer1);

    AuiNotebook1->AddPage(NewPanel, _("New File"), true);
    AuiManager1->AddPane(AuiNotebook1, wxAuiPaneInfo().Name(_T("WS_PANE"+TabIDS)).DefaultPane().CaptionVisible(false).CloseButton(false).Center().Floatable(false).PaneBorder(false));
    AuiManager1->Update();

    newTextCtrl->SetWrapMode(wrap);
    newTextCtrl->SetZoom(zoom);

    GLOBALS::TabPageSTC = newTextCtrl;
}

void WordsmithFrame::UpdateStatusBar()
{
    if (GLOBALS::TabPageSTC == nullptr) return;
    wsTextCtrl& stc(*GLOBALS::TabPageSTC);

    StatusBar1->SetStatusText(_("Length: ")+std::to_string(stc.GetTextLength()), 1);
    StatusBar1->SetStatusText(_("Lines: ")+std::to_string(stc.GetNumberOfLines()), 2);
    StatusBar1->SetStatusText(_("Line Len: ")+std::to_string(stc.GetLineLength(stc.GetCurrentLine())), 3);
}

void WordsmithFrame::UpdateToolBar()
{
    if (GLOBALS::TabPageSTC != nullptr) {
        SaveAsToolBarBtn->Enable(true);
        SaveToolBarBtn->Enable(GLOBALS::TabPageSTC->IsChanged());
        UndoToolBarBtn->Enable(GLOBALS::TabPageSTC->CanUndo());
        RedoToolBarBtn->Enable(GLOBALS::TabPageSTC->CanRedo());
        CutToolBarBtn->Enable(GLOBALS::TabPageSTC->CanCut());
        CopyToolBarBtn->Enable(GLOBALS::TabPageSTC->CanCopy());
        PasteToolBarBtn->Enable(GLOBALS::TabPageSTC->CanPaste());
        FindToolBarBtn->Enable(true);
    } else {
        SaveToolBarBtn->Enable(false);
        SaveAsToolBarBtn->Enable(false);
        UndoToolBarBtn->Enable(false);
        RedoToolBarBtn->Enable(false);
        CutToolBarBtn->Enable(false);
        CopyToolBarBtn->Enable(false);
        PasteToolBarBtn->Enable(false);
        FindToolBarBtn->Enable(false);
    }

    ToolBar1->Realize();
}

bool WordsmithFrame::LoadWebViewer(bool show_msg)
{
    if (GLOBALS::TabPageSTC != nullptr) {

        if (FileExists((const char8_t*)GLOBALS::TabPageSTC->GetFilePath().utf8_string().c_str())) {
            docViewer->LoadFile(GLOBALS::TabPageSTC->GetFilePath());
            return true;
        } else if (show_msg) {
            MessageDialog1->SetMessage(_("You must save your document before using the web viewer."));
            MessageDialog1->ShowModal();
            return false;
        }
    }

    return false;
}

bool WordsmithFrame::IsNotWord(const std::string& word)
{
    return GLOBALS::SkipWords.contains(word) ||
           !(GLOBALS::WordMap.contains(word) ||
             GLOBALS::WordSyn.contains(word) ||
             GLOBALS::UserWords.contains(word));
}

void WordsmithFrame::OnTextStatsClick(wxCommandEvent& event)
{
    wxString text(GLOBALS::TabPageSTC->GetText());
    std::pair<size_t,float> textInfo(WordParser::CountWords(text));
    std::stringstream ss;

    ss << _("Paragraphs: ") << CountParagraphs(text) << std::endl;
    ss << _("Words: ") << textInfo.first << std::endl;
    ss << _("Avg Word Length: ") << std::setprecision(3) << textInfo.second << std::endl;
    ss << _("Characters: ") << CountCharacters(text) << std::endl;
    ss << _("Bytes: ") << GLOBALS::TabPageSTC->GetLength();

    wxMessageBox(ss.str(), _("Text Stats"), wxOK | wxICON_INFORMATION);
}

void WordsmithFrame::OnSessionStatsClick(wxCommandEvent& event)
{
    wxString text(GLOBALS::TabPageSTC->GetText());
    std::pair<size_t,float> textInfo(WordParser::CountWords(text));
    float sessSecs = SessionWatch.Time() / 1000.f;
    float sessMins = sessSecs / 60.f;
    float sessTime = sessSecs;
    wxString timeStr = _(" secs");
    std::stringstream ss;

    if (sessTime > 60.f) {
        sessTime = sessMins;
        timeStr = _(" mins");
        if (sessTime > 60.f) {
            sessTime /= 60.f;
            timeStr = _(" hours");
        }
    }

    ss << _("Session duration: ") << std::setprecision(3) << sessTime << timeStr << std::endl;
    ss << _("Characters typed: ") << charsTyped << std::endl;
    ss << _("Chars per minute: ") << std::setprecision(3) << (charsTyped / sessMins);

    wxMessageBox(ss.str(), _("Session Stats"), wxOK | wxICON_INFORMATION);
}

void WordsmithFrame::OnFontClick(wxCommandEvent& event)
{
    ShowFontDialog();
}

void WordsmithFrame::OnPageClick(wxCommandEvent& event)
{
    ShowPageDialog();
}

void WordsmithFrame::OnPrintClick(wxCommandEvent& event)
{
    if (GLOBALS::TabPageSTC == nullptr) return;
    ShowPrintDialog();
}

void WordsmithFrame::OnPreviewClick(wxCommandEvent& event)
{
    if (GLOBALS::TabPageSTC == nullptr) return;
    ShowPrintDialog(true);
}

void WordsmithFrame::OnNewFileClick(wxCommandEvent& event)
{
    NewPadTab();
}

void WordsmithFrame::OnOpenFileClick(wxCommandEvent& event)
{
    ShowOpenDialog();
}

void WordsmithFrame::OnSaveClick(wxCommandEvent& event)
{
    if (GLOBALS::TabPageSTC == nullptr) return;
    ShowSaveDialog();

    if (!toolsTimer.IsRunning())
        toolsTimer.Start(10, true);
}

void WordsmithFrame::OnSaveAsClick(wxCommandEvent& event)
{
    if (GLOBALS::TabPageSTC == nullptr) return;
    ShowSaveDialog(true);

    if (!toolsTimer.IsRunning())
        toolsTimer.Start(10, true);
}

void WordsmithFrame::OnFindClick(wxCommandEvent& event)
{
    if (GLOBALS::TabPageSTC == nullptr) return;
    ShowSearchDialog();
}

void WordsmithFrame::OnReplaceClick(wxCommandEvent& event)
{
    if (GLOBALS::TabPageSTC == nullptr) return;
    ShowSearchDialog(true);
}

void WordsmithFrame::OnUndoClick(wxCommandEvent& event)
{
    if (GLOBALS::TabPageSTC == nullptr) return;

    if (GLOBALS::TabPageSTC->CanUndo()) {
        GLOBALS::TabPageSTC->Undo();

        if (GLOBALS::TabPageSTC->AutoCompActive())
            GLOBALS::TabPageSTC->AutoCompCancel();

        if (!toolsTimer.IsRunning())
            toolsTimer.Start(10, true);
    }
}

void WordsmithFrame::OnRedoClick(wxCommandEvent& event)
{
    if (GLOBALS::TabPageSTC == nullptr) return;

    if (GLOBALS::TabPageSTC->CanRedo()) {
        GLOBALS::TabPageSTC->Redo();

        if (GLOBALS::TabPageSTC->AutoCompActive())
            GLOBALS::TabPageSTC->AutoCompCancel();

        if (!toolsTimer.IsRunning())
            toolsTimer.Start(10, true);
    }
}

void WordsmithFrame::OnCutClick(wxCommandEvent& event)
{
    if (GLOBALS::TabPageSTC == nullptr) return;

    if (GLOBALS::TabPageSTC->CanCut()) {
        GLOBALS::TabPageSTC->Cut();

        if (GLOBALS::TabPageSTC->AutoCompActive())
            GLOBALS::TabPageSTC->AutoCompCancel();

        if (!toolsTimer.IsRunning())
            toolsTimer.Start(10, true);
    }
}

void WordsmithFrame::OnCopyClick(wxCommandEvent& event)
{
    if (GLOBALS::TabPageSTC == nullptr) return;

    if (GLOBALS::TabPageSTC->CanCopy()) {
        GLOBALS::TabPageSTC->Copy();

        if (!toolsTimer.IsRunning())
            toolsTimer.Start(10, true);
    }
}

void WordsmithFrame::OnPasteClick(wxCommandEvent& event)
{
    if (GLOBALS::TabPageSTC == nullptr) return;

    if (GLOBALS::TabPageSTC->CanPaste()) {
        GLOBALS::TabPageSTC->Paste();

        if (GLOBALS::TabPageSTC->AutoCompActive())
            GLOBALS::TabPageSTC->AutoCompCancel();

        if (!toolsTimer.IsRunning())
            toolsTimer.Start(10, true);
    }
}

void WordsmithFrame::OnSelectAllClick(wxCommandEvent& event)
{
    if (GLOBALS::TabPageSTC == nullptr) return;

    GLOBALS::TabPageSTC->SelectAll();

    if (!toolsTimer.IsRunning())
        toolsTimer.Start(10, true);
}

void WordsmithFrame::OnDeleteClick(wxCommandEvent& event)
{
    if (GLOBALS::TabPageSTC == nullptr) return;
    GLOBALS::TabPageSTC->RemoveSelection();

    if (GLOBALS::TabPageSTC->AutoCompActive())
        GLOBALS::TabPageSTC->AutoCompCancel();

    if (!toolsTimer.IsRunning())
        toolsTimer.Start(10, true);
}

void WordsmithFrame::OnHashClick(wxCommandEvent& event)
{
    if (GLOBALS::TabPageSTC == nullptr) return;
    std::string text(GLOBALS::TabPageSTC->GetText().utf8_string());

    wxString selLabel(((wxMenu*)event.GetEventObject())->GetLabelText(event.GetId()));
    std::string hashStr, capStr;

    if (selLabel == _("MD5")) {
        Chocobo1::MD5 md5;
        md5.addData(text.data(), text.length());
        md5.finalize();
        hashStr = md5.toString();
        capStr = "MD5 Hash";
    } else if (selLabel == _("CRC-32")) {
        Chocobo1::CRC_32 crc32;
        crc32.addData(text.data(), text.length());
        crc32.finalize();
        hashStr = crc32.toString();
        capStr = "CRC-32 Hash";
    } else if (selLabel == _("SHA-1")) {
        Chocobo1::SHA1 sha1;
        sha1.addData(text.data(), text.length());
        sha1.finalize();
        hashStr = sha1.toString();
        capStr = "SHA-1 Hash";
    } else if (selLabel == _("SHA2-256")) {
        Chocobo1::SHA2_256 sha256;
        sha256.addData(text.data(), text.length());
        sha256.finalize();
        hashStr = sha256.toString();
        capStr = "SHA2-256 Hash";
    } else if (selLabel == _("SHA2-512")) {
        Chocobo1::SHA2_512 sha512;
        sha512.addData(text.data(), text.length());
        sha512.finalize();
        hashStr = sha512.toString();
        capStr = "SHA2-512 Hash";
    }

    wsTextShowDialog hashDialog(this, "Hash value:", capStr, hashStr);
    hashDialog.ShowModal();
}

void WordsmithFrame::OnDocViewClick(wxCommandEvent& event)
{
    if (GLOBALS::TabPageSTC == nullptr) return;

    if (docViewer->IsShown()) {
        docViewer->Hide();
    } else if (LoadWebViewer()) {
        if (GLOBALS::TabPageSTC->GetModify()) {
            MessageDialog1->SetMessage(_("Save your document to see the changes appear in the web viewer."));
            MessageDialog1->ShowModal();
        }
        docViewer->Show();
    }
}

void WordsmithFrame::OnDateTimeClick(wxCommandEvent& event)
{
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm_struct = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm_struct, "%Y-%m-%d %H:%M:%S");

    GLOBALS::TabPageSTC->WriteText(oss.str());

    if (GLOBALS::TabPageSTC->AutoCompActive())
        GLOBALS::TabPageSTC->AutoCompCancel();
}

void WordsmithFrame::OnTimestampClick(wxCommandEvent& event)
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    std::int64_t unix_timestamp = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();

    std::ostringstream oss;
    oss << unix_timestamp;

    GLOBALS::TabPageSTC->WriteText(oss.str());

    if (GLOBALS::TabPageSTC->AutoCompActive())
        GLOBALS::TabPageSTC->AutoCompCancel();
}

void WordsmithFrame::OnPreferencesClick(wxCommandEvent& event)
{
    if (settingsDialog->IsShown()) {
        settingsDialog->SetFocus();
        settingsDialog->Raise();
    } else {
        settingsDialog->Reset();
        settingsDialog->Show();
        settingsDialog->Center();
    }
}

void WordsmithFrame::OnWordManagerClick(wxCommandEvent& event)
{
    if (wordsDialog->IsShown()) {
        wordsDialog->SetFocus();
        wordsDialog->Raise();
    } else {
        wordsDialog->Reset();
        wordsDialog->Show();
        wordsDialog->Center();
    }
}

void WordsmithFrame::OnPhraseManagerClick(wxCommandEvent& event)
{
    if (phrasesDialog->IsShown()) {
        phrasesDialog->SetFocus();
        phrasesDialog->Raise();
    } else {
        phrasesDialog->Reset();
        phrasesDialog->Show();
        phrasesDialog->Center();
    }
}

void WordsmithFrame::OnDictionaryClick(wxCommandEvent& event)
{
    if (dictDialog->IsShown()) {
        dictDialog->SetFocus();
        dictDialog->Raise();
    } else {
        dictDialog->Show();
        dictDialog->Center();
    }
}

void WordsmithFrame::OnTipsClick(wxCommandEvent& event)
{
    if (tipsDialog->IsShown()) {
        tipsDialog->SetFocus();
        tipsDialog->Raise();
    } else {
        tipsDialog->Show();
        tipsDialog->Center();
    }
}

void WordsmithFrame::OnAboutClick(wxCommandEvent& event)
{
    if (!aboutDialog->IsShown()) {
        aboutDialog->Center();
        aboutDialog->ShowDialog();
    }
}

void WordsmithFrame::OnAutoCompleted(wxStyledTextEvent& event)
{
    if (GLOBALS::TabPageSTC == nullptr) return;

    if (GLOBALS::AutoCompMode == 2 && !GLOBALS::GotPhraseKeys) {
        GLOBALS::TabPageSTC->WriteText(" ");

        if (!ackeyTimer.IsRunning()) {
            GLOBALS::LastKeyPress = WXK_SPACE;
            ackeyTimer.Start(10, true);
        }
    }

    event.Skip();
}

void WordsmithFrame::OnTextChanged(wxStyledTextEvent& event)
{
    //wxBitmap TabImage_BMP(wxImage(_T("./files/icons/edit_icon.png")));
    //AuiNotebook1->SetPageBitmap(AuiNotebook1->GetSelection(), *TabImage_BMP);

    if (!GLOBALS::TabPageSTC->IsChanged()) {
        GLOBALS::TabPageSTC->SetChanged();
        AuiNotebook1->SetPageText(AuiNotebook1->GetSelection(), "*" + GLOBALS::TabPageSTC->GetFileName());
    }

    if (!spellTimer.IsRunning())
        spellTimer.Start(500, true);

    if (!statsTimer.IsRunning())
        statsTimer.Start(10, true);

    if (!toolsTimer.IsRunning())
        toolsTimer.Start(10, true);

    event.Skip();
}

void WordsmithFrame::OnMouseHover(wxStyledTextEvent& event)
{
    if (GLOBALS::TabPageSTC == nullptr || !GLOBALS::TabPageSTC->IsMouseInWindow()) return;

    int pos = GLOBALS::TabPageSTC->PositionFromPoint(wxPoint(event.GetX(), event.GetY()));

    if (pos != wxSTC_INVALID_POSITION && pos != GLOBALS::TabPageSTC->GetTextLength()) {

        int wordStart = GLOBALS::TabPageSTC->WordStartPosition(pos,true);
        int wordEnd = GLOBALS::TabPageSTC->WordEndPosition(pos,true);

        if (wordStart == wordEnd || wordStart == wxSTC_INVALID_POSITION || wordEnd == wxSTC_INVALID_POSITION) return;

        wxString hovWord(GLOBALS::TabPageSTC->GetTextRange(wordStart, wordEnd));
        std::string word(hovWord.utf8_string());

        if (!GLOBALS::WordSyn.contains(word)) {
            WordParser::LowerWord(hovWord);
            word = hovWord.utf8_string();
        }

        if (!GLOBALS::WordSyn.contains(word)) {
            WordParser::UpperWord(hovWord);
            word = hovWord.utf8_string();
        }

        if (!GLOBALS::WordSyn.contains(word)) return;

        std::string tooltipStr;
        uint32_t defCount = 0;

        const auto& syns(GLOBALS::WordSyn.at(word));

        for (const std::string& syn : syns)
        {
            const WordEntry& entry(GLOBALS::WordNet.at(syn));

            if (!entry.definitions.empty()) {

                if (syn.ends_with('n')) {
                    tooltipStr += _("Noun: ");
                } else if (syn.ends_with('v')) {
                    tooltipStr += _("Verb: ");
                } else if (syn.ends_with('a')) {
                    tooltipStr += _("Adjective: ");
                } else if (syn.ends_with('s')) {
                    tooltipStr += _("Adjective: ");
                } else if (syn.ends_with('r')) {
                    tooltipStr += _("Adverb: ");
                }

                tooltipStr += entry.definitions[0] + "\n";
                defCount++;
            }
        }

        if (!tooltipStr.empty()) {
            if (defCount > 1) {
                tooltipStr = _("Definitions for \"") + word + "\": \n\n" + tooltipStr;
            } else {
                tooltipStr = _("Definition of \"") + word + "\": \n\n" + tooltipStr;
            }

            tooltipStr.resize(tooltipStr.length()-1);
            GLOBALS::TabPageSTC->CallTipShow(pos, wxString::FromUTF8(tooltipStr));
        }
    }

    event.Skip();
}

void WordsmithFrame::OnMouseHoverEnd(wxStyledTextEvent& event)
{
    if (GLOBALS::TabPageSTC == nullptr) return;

    if (GLOBALS::TabPageSTC->CallTipActive())
        GLOBALS::TabPageSTC->CallTipCancel();

    event.Skip();
}

void WordsmithFrame::OnTabPageChanged(wxAuiNotebookEvent& event)
{
    if (AuiNotebook1->GetPageCount() > 0) {

        GLOBALS::TabPageSTC = (wsTextCtrl*)AuiNotebook1->GetCurrentPage()->GetChildren().GetFirst()->GetData();

        if (docViewer->IsShown()) LoadWebViewer(false);
        if (!spellTimer.IsRunning()) spellTimer.Start(1, true);

        UpdateStatusBar();

    } else {

        GLOBALS::TabPageSTC = nullptr;
        StatusBar1->SetStatusText("", 0);
        StatusBar1->SetStatusText("", 1);
        StatusBar1->SetStatusText("", 2);
        StatusBar1->SetStatusText("", 3);
    }

    if (!toolsTimer.IsRunning())
        toolsTimer.Start(10, true);

    event.Skip();
}

void WordsmithFrame::OnTabPageClose(wxAuiNotebookEvent& event)
{
    if (GLOBALS::TabPageSTC->IsChanged() && (!GLOBALS::TabPageSTC->GetFilePath().empty() || GLOBALS::TabPageSTC->GetLength() > 0)) {

        QuestionDialog1->SetMessage(_("Do you want to save the document before closing it?"));
        int answer = QuestionDialog1->ShowModal();

        if (answer == wxID_CANCEL) return;
        if (answer == wxID_YES) ShowSaveDialog();
    }

    event.Skip();
}

void WordsmithFrame::OnTabPageClosed(wxAuiNotebookEvent& event)
{
    OnTabPageChanged(event);
    event.Skip();
}

void WordsmithFrame::OnSpellCheckTrigger(wxTimerEvent& event)
{
    if (GLOBALS::TabPageSTC == nullptr || !GLOBALS::GotWordData) return;
    wsTextCtrl& stc(*GLOBALS::TabPageSTC);

    stc.SetUndoCollection(false);

    if (!SpellCheckMenuItem->IsChecked()) {
        if (stc.IsIndicated()) {
            stc.IndicatorClearRange(0, stc.GetTextLength());
            stc.SetIndicated(false);
        }

        stc.SetUndoCollection(true);
        return;
    }

    stc.SetIndicated(true);

    int firstLine = stc.GetFirstVisibleLine();
    int visLines = stc.LinesOnScreen();
    int lastLine = firstLine + visLines;

    int wordPos = 0;
    int curPos, endPos;
    bool gotWord, gotDigit;

    for (int line = firstLine; line < lastLine; ++line)
    {
        curPos = stc.PositionFromLine(line);
        endPos = stc.GetLineEndPosition(line);

        if (curPos == endPos) continue;

        stc.IndicatorClearRange(curPos, stc.LineLength(line));

        wxString lineText(stc.GetTextRange(curPos, endPos));
        wxString word;
        gotWord = false;
        gotDigit = false;

        for (const wxUniChar& c : lineText)
        {
            if (WordParser::IsDigit(c)) {
                gotDigit = true;
                word.clear();
            } else if (WordParser::IsJoin(c)) {
                if (!gotDigit) {
                    if (!word.empty() && WordParser::IsAlpha(word[word.length()-1])) {
                        word.append(c);
                    } else {
                        gotWord = true;
                    }
                }
            } else if (WordParser::IsAlpha(c) || (c > 255 && !WordParser::IsWhiteSpace(c))) {
                if (!gotDigit) {
                    if (word.empty()) wordPos = curPos;
                    word.append(c);
                }
            } else {
                gotDigit = false;
                gotWord = true;
            }

            if (gotWord) {
                if (word.length() > 1) {
                    if (WordParser::IsJoin(word[word.length()-1]))
                        word.RemoveLast();

                    std::string wordStr(WordParser::LowerWord(word).utf8_string());

                    if (IsNotWord(wordStr))
                        stc.IndicatorFillRange(wordPos, wordStr.length());
                }

                word.clear();
                gotWord = false;
            }

            curPos += WordParser::UTF8CharLen(c);
        }

        if (word.length() > 1) {
            if (WordParser::IsJoin(word[word.length()-1]))
                word.RemoveLast();

            std::string wordStr(WordParser::LowerWord(word).utf8_string());

            if (IsNotWord(wordStr))
                stc.IndicatorFillRange(wordPos, wordStr.length());
        }
    }

    stc.SetUndoCollection(true);
}

void WordsmithFrame::OnACKeyTimerTrigger(wxTimerEvent& event)
{
    static std::set<std::pair<uint32_t,std::string>, std::greater<std::pair<uint32_t,std::string>>> autoWords;
    static std::set<std::string> autoPhrases;
    static std::vector<const char*> matchWords;
    static std::vector<const char*> matchPhrases;
    static std::string subWord;
    static std::string preWord;
    static wxString preChars;
    static uint32_t wordIndex;
    static int wordPos;

    if (!GLOBALS::GotWordData) return;
    wsTextCtrl& stc(*GLOBALS::TabPageSTC);

    wordPos = stc.WordStartPosition(stc.GetCurrentPos(), true);
    preChars = stc.GetTextRange(wordPos, stc.GetCurrentPos());
    preWord = preChars.utf8_string();

    matchWords.clear();
    matchPhrases.clear();

    if (stc.AutoCompActive()) {

        stc.AutoCompCancel();

        if (GLOBALS::LastKeyPress != WXK_SPACE) {

            matchWords.reserve(autoWords.size());
            matchPhrases.reserve(autoPhrases.size());

            for (const auto& entry : autoWords)
            {
                if (entry.second.starts_with(preWord)) {
                    matchWords.emplace_back(entry.second.data());
                    if (matchWords.size() > 99) break;
                }
            }

            for (const std::string& phrase : autoPhrases)
            {
                if (phrase.starts_with(preWord)) {
                    matchPhrases.emplace_back(phrase.data());
                    if (matchPhrases.size() > 99) break;
                }
            }
        }
    }

    if (GLOBALS::GotPhraseKeys) {

        std::stringstream ss;
        autoWords.clear();
        autoPhrases.clear();

        if (preWord.empty()) {
            for (const std::string& phrase : GLOBALS::UserPhrases)
            {
                autoPhrases.emplace(phrase);
                ss << phrase << "\n";
            }
        } else {
            for (const std::string& phrase : GLOBALS::UserPhrases)
            {
                if (phrase.length() >= preWord.length() && phrase.starts_with(preWord)) {
                    autoPhrases.emplace(phrase);
                    ss << phrase << "\n";
                }
            }
        }

        if (!autoPhrases.empty())
            stc.AutoCompShow(preChars.length(), wxString::FromUTF8(TrimLast(ss.str(), '\n')));

    } else if (!matchPhrases.empty()) {

        std::stringstream ss;

        for (const char* phrase : matchPhrases) ss << phrase << "\n";

        stc.AutoCompShow(preChars.length(), wxString::FromUTF8(TrimLast(ss.str(), '\n')));

    } else if (matchWords.size() > 4) {

        std::stringstream ss;

        for (const char* word : matchWords) ss << word << "\n";

        stc.AutoCompShow(preChars.length(), wxString::FromUTF8(TrimLast(ss.str(), '\n')));

    } else if (preChars.length() > 1) {

        subWord = preChars.substr(0,2).utf8_string();
        wordPos = GLOBALS::UserWords.size();

        autoWords.clear();
        autoPhrases.clear();

        if (GLOBALS::WebIndices.contains(subWord)) {

            wordIndex = GLOBALS::WebIndices[subWord];

            for (; wordIndex < GLOBALS::WordVec.size(); ++wordIndex)
            {
                const auto& entry(GLOBALS::WordVec[wordIndex]);

                if (entry.first.length() <= preChars.length() || !entry.first.starts_with(preWord)) continue;

                if (!GLOBALS::SkipWords.contains(entry.first))
                    autoWords.emplace(std::make_pair(entry.second, entry.first));
            }
        }

        for (const std::string& word : GLOBALS::UserWords)
        {
            if (word.length() <= preChars.length() || !word.starts_with(preWord)) continue;
            autoWords.emplace(std::make_pair(wordPos--, word));
        }

        if (!autoWords.empty()) {
            std::stringstream ss;
            wordIndex = 0;

            for (const auto& entry : autoWords) {
                if (wordIndex++ > 99) break;
                ss << entry.second << "\n";
            }

            stc.AutoCompShow(preChars.length(), wxString::FromUTF8(TrimLast(ss.str(), '\n')));
        }

    } else if (GLOBALS::LastKeyPress == WXK_SPACE) {

        wordPos = std::max(0, stc.GetCurrentPos() - 2);

        if (WordParser::IsEnd2(stc.GetCharAt(stc.GetCurrentPos()-1), stc.GetCharAt(wordPos))) return;

        preChars = stc.GetTextRange(stc.WordStartPosition(wordPos,true),  stc.WordEndPosition(wordPos,true));
        preWord = preChars.utf8_string();

        if (preWord.empty()) {
            return;
        } else if (!GLOBALS::WordMap.contains(preWord)) {
            preWord = WordParser::LowerWord(preChars).utf8_string();
            if (!GLOBALS::WordMap.contains(preWord)) return;
        }

        const auto& links(GLOBALS::WordMap.at(preWord).second);
        std::stringstream ss;

        autoWords.clear();
        autoPhrases.clear();

        for (const auto& entry : links)
        {
            const std::string& word(GLOBALS::WordVec[entry.first].first);

            if (!GLOBALS::SkipWords.contains(word)) {
                autoWords.emplace(std::make_pair(entry.second, word));
                ss << word << "\n";
            }
        }

        if (!autoWords.empty())
            stc.AutoCompShow(0, wxString::FromUTF8(TrimLast(ss.str(), '\n')));
    }
}

void WordsmithFrame::OnKeyPress(wxKeyEvent& event)
{
    if (event.GetUnicodeKey() != WXK_NONE) {

        GLOBALS::LastKeyPress = event.GetUnicodeKey();

        if (GLOBALS::AutoCompMode && !ackeyTimer.IsRunning())
            ackeyTimer.Start(10, true);

        charsTyped++;
    }

    if (event.ShiftDown() && GLOBALS::LastKeyPress == WXK_SPACE) {
        GLOBALS::GotPhraseKeys = true;
    } else {
        GLOBALS::GotPhraseKeys = false;
        event.Skip();
    }
}

void WordsmithFrame::OnKeyUp(wxKeyEvent& event)
{
    switch (event.GetKeyCode()) {
        case WXK_LEFT:
        case WXK_UP:
        case WXK_RIGHT:
        case WXK_DOWN:
        case WXK_NUMPAD_LEFT:
        case WXK_NUMPAD_UP:
        case WXK_NUMPAD_RIGHT:
        case WXK_NUMPAD_DOWN:
            UpdateStatusBar();
            break;
        default: break;
    }

    if (!toolsTimer.IsRunning())
        toolsTimer.Start(10, true);

    event.Skip();
}

void WordsmithFrame::OnMouseUp(wxMouseEvent& event)
{
    if (!statsTimer.IsRunning())
        statsTimer.Start(10, true);

    if (!toolsTimer.IsRunning())
        toolsTimer.Start(10, true);

    event.Skip();
}

void WordsmithFrame::OnMouseRightDown(wxMouseEvent& event)
{
    if (GLOBALS::TabPageSTC->GetSelectionEmpty()) event.Skip();
}

void WordsmithFrame::OnInitTimerTrigger(wxTimerEvent& event)
{
    if (!GLOBALS::GotWordData) {
        initTimer.Start(100, true);
    } else {
        if (StatusBar1->GetStatusText(0) == _("Loading word files ..."))
            StatusBar1->SetStatusText("", 0);

        if (!spellTimer.IsRunning())
            spellTimer.Start(1, true);

        dictDialog->SetReady();
    }
}

void WordsmithFrame::OnStatsTimerTrigger(wxTimerEvent& event)
{
    UpdateStatusBar();
}

void WordsmithFrame::OnToolsTimerTrigger(wxTimerEvent& event)
{
    UpdateToolBar();
}

void WordsmithFrame::OnToggleToolBar(wxCommandEvent& event)
{
    if (ToolBar1->IsShown()) {
        ToolBar1->Hide();
    } else {
        ToolBar1->Show();
    }

    AuiManager1->Update();
}

void WordsmithFrame::OnToggleStatusBar(wxCommandEvent& event)
{
    if (StatusBar1->IsShown()) {
        StatusBar1->Hide();
    } else {
        StatusBar1->Show();
    }

    AuiManager1->Update();
}

void WordsmithFrame::OnToggleWordWrap(wxCommandEvent& event)
{
    if (GLOBALS::TabPageSTC == nullptr) return;

    bool doWrap = GLOBALS::TabPageSTC->GetWrapMode() == wxSTC_WRAP_NONE;

    WordWrapMenuItem->Check(doWrap);

    if (doWrap) {
        GLOBALS::TabPageSTC->SetWrapMode(wxSTC_WRAP_WORD);
    } else {
        GLOBALS::TabPageSTC->SetWrapMode(wxSTC_WRAP_NONE);
    }
}

void WordsmithFrame::OnToggleSpellCheck(wxCommandEvent& event)
{
    if (!spellTimer.IsRunning())
        spellTimer.Start(1, true);
}

void WordsmithFrame::FindNext(const wxString& find_str, const int& flags)
{
    static int selpos, endpos, stcFlags;
    findPos = wxSTC_INVALID_POSITION;

    if (GLOBALS::TabPageSTC == nullptr || find_str.empty()) return;
    wsTextCtrl& textCtrl(*GLOBALS::TabPageSTC);

    if (flags & wxFR_WHOLEWORD) {
        stcFlags = wxSTC_FIND_WHOLEWORD;
    } else {
        stcFlags = wxSTC_FIND_NONE;
    }

    if (flags & wxFR_MATCHCASE)
        stcFlags |= wxSTC_FIND_MATCHCASE;

    textCtrl.SetAnchor(textCtrl.GetCurrentPos());
    textCtrl.SearchAnchor();

    if (flags & wxFR_DOWN) {
        findPos = textCtrl.SearchNext(stcFlags, find_str);
        if (findPos == wxSTC_INVALID_POSITION)
            findPos = textCtrl.FindText(0, textCtrl.GetTextLength(), find_str, stcFlags);
        endpos = findPos + find_str.length();
        selpos = findPos;
    } else {
        findPos = textCtrl.SearchPrev(stcFlags, find_str);
        if (findPos == wxSTC_INVALID_POSITION)
            findPos = textCtrl.FindText(textCtrl.GetTextLength(), 0, find_str, stcFlags);
        endpos = findPos;
        selpos = findPos + find_str.length();
    }

    if (findPos == wxSTC_INVALID_POSITION) {
        MessageDialog1->SetMessage(_("Text not found."));
        MessageDialog1->ShowModal();
        return;
    }

    //textCtrl.SetSelection(selpos, endpos);
    textCtrl.SetAnchor(selpos);
    textCtrl.SetInsertionPoint(endpos);
    textCtrl.ScrollToLine(textCtrl.GetCurrentLine());

    if (flags & wxFR_DOWN) {
        textCtrl.ScrollToColumn(textCtrl.GetColumn(selpos));
    } else {
        textCtrl.ScrollToColumn(textCtrl.GetColumn(endpos));
    }
}

void WordsmithFrame::OnFindFirst(wxFindDialogEvent& event)
{
    FindNext(event.GetFindString(), event.GetFlags());
}

void WordsmithFrame::OnFindNext(wxFindDialogEvent& event)
{
    FindNext(event.GetFindString(), event.GetFlags());
}

void WordsmithFrame::OnFindNextClick(wxCommandEvent& event)
{
    FindNext(findData.GetFindString(), findData.GetFlags());
}

void WordsmithFrame::OnFindReplace(wxFindDialogEvent& event)
{
    if (GLOBALS::TabPageSTC == nullptr) return;
    wsTextCtrl& textCtrl(*GLOBALS::TabPageSTC);

    if (textCtrl.GetSelectedText() != event.GetFindString())
        OnFindNext(event);

    if (findPos == wxSTC_INVALID_POSITION) return;

    QuestionDialog1->SetMessage(_("Replace this occurrence?"));
    int answer = QuestionDialog1->ShowModal();

    if (answer == wxID_NO || answer == wxID_CANCEL) {
        textCtrl.SetAnchor(textCtrl.GetCurrentPos());
        return;
    }

    textCtrl.ReplaceSelection(event.GetReplaceString());
}

void WordsmithFrame::OnInfoTimerTrigger(wxTimerEvent& event)
{
    if (StatusBar1->GetStatusText(0) == _("Loading word files ...")) {
        if (GLOBALS::GotWordData) {
            StatusBar1->SetStatusText("", 0);
        } else {
            infoTimer.Start(100, true);
        }
    } else {
        StatusBar1->SetStatusText("", 0);
    }
}

void WordsmithFrame::SetStatusBarText(const wxString& txt)
{
    StatusBar1->SetStatusText(txt, 0);
    infoTimer.Start(5000, true);
}

void WordsmithFrame::OnFindReplaceAll(wxFindDialogEvent& event)
{
    if (GLOBALS::TabPageSTC == nullptr) return;

    wxString repText(GLOBALS::TabPageSTC->GetText());
    size_t repNum = repText.Replace(event.GetFindString(), event.GetReplaceString(), true);
    if (repNum > 0) GLOBALS::TabPageSTC->SetText(repText);
    repText = _("Replaced %u occurrences");
    repText.Replace("%u", std::to_string(repNum), true);
    SetStatusBarText(repText);
}

void WordsmithFrame::OnFindClose(wxFindDialogEvent& event)
{
    findDialog->Destroy();
    findDialog = nullptr;
    event.Skip();
}

void WordsmithFrame::OnFontColorClick(wxCommandEvent& event)
{
    if (ColourDialog1->ShowModal() == wxID_CANCEL) return;

    GLOBALS::TabPageSTC->SetFontColor(ColourDialog1->GetColourData().GetColour());
}

void WordsmithFrame::OnZoomInClick(wxCommandEvent& event)
{
    GLOBALS::TabPageSTC->ZoomIn();
}

void WordsmithFrame::OnZoomOutClick(wxCommandEvent& event)
{
    GLOBALS::TabPageSTC->ZoomOut();
}

void WordsmithFrame::OnZoomResetClick(wxCommandEvent& event)
{
    GLOBALS::TabPageSTC->SetZoom(0);
}

void WordsmithFrame::OnSwapWordClick(wxCommandEvent& event)
{
    if (GLOBALS::TabPageSTC == nullptr) return;
    wsTextCtrl& stc(*GLOBALS::TabPageSTC);

    if (stc.GetSelectedText().empty()) {
        stc.Replace(
            stc.WordStartPosition(stc.GetCurrentPos(),true), stc.WordEndPosition(stc.GetCurrentPos(),true),
            ((wxMenu*)event.GetEventObject())->GetLabelText(event.GetId())
        );
    } else {
        stc.ReplaceSelection(((wxMenu*)event.GetEventObject())->GetLabelText(event.GetId()));
    }

    event.Skip();
}

void WordsmithFrame::OnMenuHover(wxCommandEvent& event)
{
    if (event.GetSelection() < 0)
        infoTimer.Start(10, true);

    event.Skip();
}

void WordsmithFrame::OnMenuClose(wxMenuEvent& event)
{
    infoTimer.Start(10, true);

    event.Skip();
}

void WordsmithFrame::OnMenuOpen(wxMenuEvent& event)
{
    wxMenu* menu(event.GetMenu());
    bool tb(GLOBALS::TabPageSTC != nullptr);

    if (menu->GetTitle() == _("&File")) {
        SaveMenuItem->Enable(tb && (GLOBALS::TabPageSTC->IsChanged() || GLOBALS::TabPageSTC->GetFilePath().empty()));
        SaveAsMenuItem->Enable(tb);
        PreviewMenuItem->Enable(tb);
        PrintMenuItem->Enable(tb);
    } else if (menu->GetTitle() == _("&Edit")) {
        UndoMenuItem->Enable(tb && GLOBALS::TabPageSTC->CanUndo());
        RedoMenuItem->Enable(tb && GLOBALS::TabPageSTC->CanRedo());
        CutMenuItem->Enable(tb && GLOBALS::TabPageSTC->CanCut());
        CopyMenuItem->Enable(tb && GLOBALS::TabPageSTC->CanCopy());
        PasteMenuItem->Enable(tb && GLOBALS::TabPageSTC->CanPaste());
        FindMenuItem->Enable(tb);
        NextMenuItem->Enable(tb);
        ReplaceMenuItem->Enable(tb);
        SelectMenuItem->Enable(tb);
    } else if (menu->GetTitle() == _("&View")) {
        wxMenuItemList& menuItems(ZoomMenuItem->GetMenuItems());
        for (wxMenuItem* menuItem : menuItems) menuItem->Enable(tb);
        WebViewMenuItem->Enable(tb);
    } else if (menu->GetTitle() == _("&Insert")) {
        wxMenuItemList& menuItems(MarkdownMenuItem->GetMenuItems());
        for (wxMenuItem* menuItem : menuItems) menuItem->Enable(tb);
        DateTimeMenuItem->Enable(tb);
        TimestampMenuItem->Enable(tb);
    } else if (menu->GetTitle() == _("&Tools")) {
        TextStatsMenuItem->Enable(tb);
        wxMenuItemList& menuItems(HashMenuItem->GetMenuItems());
        for (wxMenuItem* menuItem : menuItems) menuItem->Enable(tb);
    } else if (menu->GetTitle() == _("&Settings")) {
        WordWrapMenuItem->Enable(tb);
        if (tb) WordWrapMenuItem->Check(GLOBALS::TabPageSTC->GetWrapMode());
    }

    event.Skip();
}

void WordsmithFrame::OnRemoveWord(wxCommandEvent& event)
{
    wxString word(((wxMenu*)event.GetEventObject())->GetLabelText(event.GetId()));
    word = word.substr(1 + word.Find(wxUniChar('"')));
    wordsDialog->RemoveWord(word.substr(0, word.Find(wxUniChar('"'))).utf8_string());
    event.Skip();
}

void WordsmithFrame::OnAddWord(wxCommandEvent& event)
{
    wxString word(((wxMenu*)event.GetEventObject())->GetLabelText(event.GetId()));
    word = word.substr(1 + word.Find(wxUniChar('"')));
    wordsDialog->AddWord(word.substr(0, word.Find(wxUniChar('"'))).utf8_string());
    event.Skip();
}

void WordsmithFrame::OnAddPhrase(wxCommandEvent& event)
{
    phrasesDialog->AddPhrase(GLOBALS::LastPhrase.utf8_string());
    event.Skip();
}

void WordsmithFrame::OnContextMenu(wxContextMenuEvent& event)
{
    static phmap::flat_hash_set<std::string> comWords = {
        "which", "whose", "while", "where", "those", "should", "would", "could", "else", "like", "some", "been", "will", "your", "there", "their", "them", "they",
        "said", "very", "with", "what", "when", "have", "were", "went", "well", "much", "this", "that", "then", "than", "and", "the", "but", "can", "not", "one", "out",
        "from", "also", "just", "into", "has", "for", "any", "get", "who", "you", "had", "our", "why", "how", "own", "too", "its", "did", "are", "was", "his", "him",
        "her", "she", "he", "am", "on", "to", "be", "do", "it", "is", "at", "in", "or", "so", "my", "of", "we", "as", "by", "if", "me", "an", "us", "up", "no",
        "shouldn't", "wouldn't", "couldn't", "wasn't", "didn't", "you're", "don't", "can't", "that's", "it's", "he'd", "she'd", "i'll", "i'm", "i'd"
    };

    if (GLOBALS::TabPageSTC == nullptr) return;

    wsTextCtrl& stc(*GLOBALS::TabPageSTC);
    std::string selWord, lowWord, synWord, simWord;
    wxString selText;
    wxMenu menu;
    wxMenu* synMenu;
    wxMenu* simMenu;
    bool addSep = false;
    bool isUpperWord = false;

    if (stc.GetSelectionEmpty()) {
        int pos = stc.GetCurrentPos();
        selText = stc.GetTextRange(stc.WordStartPosition(pos,true), stc.WordEndPosition(pos,true));
    } else {
        selText = stc.GetSelectedText();
    }

    if (GLOBALS::GotWordData && !selText.empty()) {

        std::set<std::string> simWords, lowWords;
        std::set<std::string> syns;

        selText.Trim(false).Trim();
        selWord = selText.utf8_string();

        synWord = selWord;
        simWord = selWord;

        if (selWord.empty() || HasLineBreak(selText)) {
            goto SETUP_MENU;
        } else if (HasWhiteSpace(selText)) {

            auto menuID = wxNewId();
            menu.Append(menuID, _("Add selection to phrases"));
            Connect(menuID, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&OnAddPhrase);

            GLOBALS::LastPhrase = selText;
            addSep = true;

            goto SETUP_MENU;
        }

        lowWord = WordParser::LowerWord(selText).utf8_string();

        if (selWord != lowWord) {
            isUpperWord = true;
            if (!GLOBALS::WordSyn.contains(selWord)) synWord = lowWord;
            if (!GLOBALS::SimWords.contains(selWord)) simWord = lowWord;
        }

        if ((GLOBALS::SimWords.contains(simWord) || GLOBALS::WordSyn.contains(synWord) || GLOBALS::UserWords.contains(lowWord)) && !GLOBALS::SkipWords.contains(lowWord)) {

            wxString menuText(_("Remove \"%s\" from dictionary"));
            menuText.Replace("%s", wxString::FromUTF8(lowWord), false);

            addSep = true;
            auto menuID = wxNewId();

            menu.Append(menuID, menuText);
            Connect(menuID, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&OnRemoveWord);

        } else {

            wxString menuText(_("Add \"%s\" to dictionary"));
            menuText.Replace("%s", wxString::FromUTF8(lowWord), false);

            addSep = true;
            auto menuID = wxNewId();

            menu.Append(menuID, menuText);
            Connect(menuID, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&OnAddWord);

            auto suggestions = spellChecker.lookup(lowWord, yams::symspell::Verbosity::Closest);

            if (!suggestions.empty()) {

                simMenu = new wxMenu();

                for (auto& s : suggestions) {
                    if (!s.term.empty()) {
                        wxString suggestion(wxString::FromUTF8(s.term));
                        if (isUpperWord) WordParser::UpperWord(suggestion);
                        simMenu->Append(new wxMenuItem(simMenu, wxNewId(), suggestion));
                    }
                }

                menu.Append(wxNewId(), _("Suggestions"), simMenu);
                simMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, &OnSwapWordClick, this);

                goto SETUP_MENU;
            }
        }

        if (GLOBALS::WordSyn.contains(synWord)) {
            const std::vector<std::string>& synVec(GLOBALS::WordSyn.at(synWord));

            for (const auto& synset : synVec)
            {
                for (const std::string& member : GLOBALS::WordNet.at(synset).members)
                    if (synWord != member && !GLOBALS::SkipWords.contains(member)) syns.emplace(member);
            }

            if (syns.size() < 16) {

                for (const auto& synset : synVec)
                {
                    for (const std::string& ssID : GLOBALS::WordNet.at(synset).related)
                    {
                        for (const std::string& member : GLOBALS::WordNet.at(ssID).members)
                        {
                            if (member.empty()) continue;
                            if (synWord != member && !GLOBALS::SkipWords.contains(member)) syns.emplace(member);
                            if (syns.size() >= 16) goto BREAK_OUT;
                        }
                    }
                }
            }
            BREAK_OUT:

            if (!syns.empty()) {
                synMenu = new wxMenu();
                addSep = true;

                for (const std::string& syn : syns)
                    synMenu->Append(new wxMenuItem(synMenu, wxNewId(), wxString::FromUTF8(syn)));

                synMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, &OnSwapWordClick, this);
                menu.Append(wxNewId(), _("Synonyms"), synMenu);
            }
        }

        if (GLOBALS::SimWords.contains(selWord)) {

            const std::vector<std::pair<uint32_t,float>>& words(GLOBALS::SimWords[selWord]);

            for (const auto& entry : words)
            {
                std::string word(GLOBALS::WordVec[entry.first].first);
                WordParser::LowerWord(word);

                if (word.length() > 1 && word != lowWord && !syns.contains(word))
                    if (!comWords.contains(word) && !GLOBALS::SkipWords.contains(word)) simWords.emplace(word);
            }
        }

        if (selWord != lowWord && GLOBALS::SimWords.contains(lowWord)) {

            const std::vector<std::pair<uint32_t,float>>& words(GLOBALS::SimWords[lowWord]);

            for (const auto& entry : words)
            {
                std::string word(GLOBALS::WordVec[entry.first].first);
                WordParser::LowerWord(word);

                if (word.length() > 1 && word != lowWord && !simWords.contains(word) && !syns.contains(word))
                    if (!comWords.contains(word) && !GLOBALS::SkipWords.contains(word)) lowWords.emplace(word);
            }
        }

        if (!simWords.empty() || !lowWords.empty()) {

            simMenu = new wxMenu();
            addSep = true;

            for (const auto& word : simWords)
                simMenu->Append(new wxMenuItem(simMenu, wxNewId(), wxString::FromUTF8(word)));

            for (const auto& word : lowWords)
                simMenu->Append(new wxMenuItem(simMenu, wxNewId(), wxString::FromUTF8(word)));

            simMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, &OnSwapWordClick, this);
            menu.Append(wxNewId(), _("Related"), simMenu);
        }
    }

    SETUP_MENU:

    if (addSep) menu.AppendSeparator();

    menu.Append(wxID_UNDO, _("Undo"));
    menu.Enable(wxID_UNDO, stc.CanUndo());
    menu.Append(wxID_REDO, _("Redo"));
    menu.Enable(wxID_REDO, stc.CanRedo());
    menu.AppendSeparator();
    menu.Append(wxID_CUT, _("Cut"));
    menu.Enable(wxID_CUT, stc.CanCut());
    menu.Append(wxID_COPY, _("Copy"));
    menu.Enable(wxID_COPY, stc.CanCopy());
    menu.Append(wxID_PASTE, _("Paste"));
    menu.Enable(wxID_PASTE, stc.CanPaste());
    menu.Append(wxID_DELETE, _("Delete"));
    menu.Enable(wxID_DELETE, !stc.GetSelectionEmpty());
    menu.AppendSeparator();
    menu.Append(wxID_SELECTALL, _("Select All"));

    menu.Bind(wxEVT_COMMAND_MENU_SELECTED, &OnUndoClick, this, wxID_UNDO);
    menu.Bind(wxEVT_COMMAND_MENU_SELECTED, &OnRedoClick, this, wxID_REDO);
    menu.Bind(wxEVT_COMMAND_MENU_SELECTED, &OnCutClick, this, wxID_CUT);
    menu.Bind(wxEVT_COMMAND_MENU_SELECTED, &OnCopyClick, this, wxID_COPY);
    menu.Bind(wxEVT_COMMAND_MENU_SELECTED, &OnPasteClick, this, wxID_PASTE);
    menu.Bind(wxEVT_COMMAND_MENU_SELECTED, &OnDeleteClick, this, wxID_DELETE);
    menu.Bind(wxEVT_COMMAND_MENU_SELECTED, &OnSelectAllClick, this, wxID_SELECTALL);

    stc.PopupMenu(&menu);
    event.Skip();
}

void WordsmithFrame::OnAddMarkdownClick(wxCommandEvent& event)
{
    if (GLOBALS::TabPageSTC == nullptr) return;

    wxString selLabel(((wxMenu*)event.GetEventObject())->GetLabelText(event.GetId()));
    int curPos = GLOBALS::TabPageSTC->GetCurrentPos();
    wxString inText;
    bool gotSel = false;

    if (curPos != GLOBALS::TabPageSTC->GetAnchor()) {
        gotSel = true;
        inText = GLOBALS::TabPageSTC->GetSelectedText();
    }

    if (selLabel == _("Title")) {

        TextEntryDialog1->Destroy();
        TextEntryDialog1 = new wxTextEntryDialog(this, _("Enter the title text:"), _("Markdown Title"));
        if (gotSel) TextEntryDialog1->SetValue(inText);
        if (TextEntryDialog1->ShowModal() == wxID_CANCEL) return;
        inText = TextEntryDialog1->GetValue();

        wxString headerSizes[3] = { _("Large"), _("Medium"), _("Small") };
        wxSingleChoiceDialog* newChoiceDialog = new wxSingleChoiceDialog(this, _("Markdown Title"), _("Select heading size:"), 3, headerSizes, 0, wxCHOICEDLG_STYLE);
        if (newChoiceDialog->ShowModal() == wxID_CANCEL) return;
        wxString selStr = newChoiceDialog->GetStringSelection();
        inText = (selStr == _("Large") ? "# " : (selStr == _("Small") ? "### " : "## ")) + inText;
        newChoiceDialog->Destroy();

    } else if (selLabel == _("Link")) {

        TextEntryDialog1->Destroy();
        TextEntryDialog1 = new wxTextEntryDialog(this, _("Enter the link text:"), _("Markdown Link"));
        if (gotSel) TextEntryDialog1->SetValue(inText);
        if (TextEntryDialog1->ShowModal() == wxID_CANCEL) return;
        inText = "[" + TextEntryDialog1->GetValue() + "]";

        TextEntryDialog1->Destroy();
        TextEntryDialog1 = new wxTextEntryDialog(this, _("Enter the URL:"), _("Markdown Link"));
        if (TextEntryDialog1->ShowModal() == wxID_CANCEL) return;
        inText += "(" + TextEntryDialog1->GetValue() + ")";

    } else if (selLabel == _("Image")) {

        TextEntryDialog1->Destroy();
        TextEntryDialog1 = new wxTextEntryDialog(this, _("Enter the image description:"), _("Markdown Image"));
        if (gotSel) TextEntryDialog1->SetValue(inText);
        if (TextEntryDialog1->ShowModal() == wxID_CANCEL) return;
        inText = "![" + TextEntryDialog1->GetValue() + "]";

        TextEntryDialog1->Destroy();
        TextEntryDialog1 = new wxTextEntryDialog(this, _("Enter the image URL:"), _("Markdown Image"));
        if (TextEntryDialog1->ShowModal() == wxID_CANCEL) return;
        inText += "(" + TextEntryDialog1->GetValue() + ")";

    } else if (selLabel == _("Quote")) {

        if (!gotSel) {
            TextEntryDialog1->Destroy();
            TextEntryDialog1 = new wxTextEntryDialog(this, _("Enter the quote text:"), _("Markdown Quote"), wxEmptyString, wxOK|wxCANCEL|wxCENTRE|wxTE_MULTILINE|wxWS_EX_VALIDATE_RECURSIVELY);
            if (TextEntryDialog1->ShowModal() == wxID_CANCEL) return;
            inText = TextEntryDialog1->GetValue();
        }

        inText.Trim().Replace(GLOBALS::LineEndStr, GLOBALS::LineEndStr + ">");
        inText = ">" + inText;
        //GLOBALS::TabPageSTC->SetCurrentPos(curPos+inText.length());

    } else if (selLabel == _("Code")) {

        if (!gotSel) {
            TextEntryDialog1->Destroy();
            TextEntryDialog1 = new wxTextEntryDialog(this, _("Enter the code:"), _("Markdown Code"), wxEmptyString, wxOK|wxCANCEL|wxCENTRE|wxTE_MULTILINE|wxWS_EX_VALIDATE_RECURSIVELY);
            if (TextEntryDialog1->ShowModal() == wxID_CANCEL) return;
            inText = TextEntryDialog1->GetValue();
        }

        inText = inText.Find(GLOBALS::LineEndStr) == wxNOT_FOUND ? "`" + inText + "`" : "```" + GLOBALS::LineEndStr + inText + GLOBALS::LineEndStr + "```";
        //GLOBALS::TabPageSTC->SetCurrentPos(curPos+inText.length());

    } else if (selLabel == _("List")) {

        TextEntryDialog1->Destroy();
        TextEntryDialog1 = new wxTextEntryDialog(this, _("Enter list items (one per line):"), _("Markdown List"), wxEmptyString, wxOK|wxCANCEL|wxCENTRE|wxTE_MULTILINE|wxWS_EX_VALIDATE_RECURSIVELY);
        if (gotSel) TextEntryDialog1->SetValue(inText);
        if (TextEntryDialog1->ShowModal() == wxID_CANCEL) return;

        inText = TextEntryDialog1->GetValue();
        inText.Replace("\r\n", "\n");
        inText.Replace("\r", "\n");

        wxString listTypes[2] = { _("Unordered"), _("Ordered") };
        wxSingleChoiceDialog* newChoiceDialog = new wxSingleChoiceDialog(this, _("Markdown List"), _("Select list type:"), 2, listTypes, 0, wxCHOICEDLG_STYLE);
        if (newChoiceDialog->ShowModal() == wxID_CANCEL) return;
        wxString selStr = newChoiceDialog->GetStringSelection();

        auto lines(ExplodeStr(inText.utf8_string(), "\n"));
        inText = "";

        if (selStr == _("Ordered")) {
            for (size_t i=0; i < lines.size(); ++i) {
                const std::string& line(lines[i]);
                if (line.empty()) continue;
                inText += wxString::FromUTF8(std::to_string(i+1)+". "+line+GLOBALS::LineEndStr);
            }
        } else {
            for (const std::string& line : lines) {
                if (line.empty()) continue;
                inText += wxString::FromUTF8("* "+line+GLOBALS::LineEndStr);
            }
        }

        if (!inText.empty()) inText.resize(inText.size()-GLOBALS::LineEndStr.length());

        newChoiceDialog->Destroy();

    } else if (selLabel == _("Styled Text")) {

        TextEntryDialog1->Destroy();
        TextEntryDialog1 = new wxTextEntryDialog(this, _("Enter some text:"), _("Markdown Text"));
        if (gotSel) TextEntryDialog1->SetValue(inText);
        if (TextEntryDialog1->ShowModal() == wxID_CANCEL) return;
        inText = TextEntryDialog1->GetValue();

        wxString textStyles[3] = { _("Bold"), _("Italic"), _("Strikethrough") };
        wxSingleChoiceDialog* newChoiceDialog = new wxSingleChoiceDialog(this, _("Markdown Text"), _("Select text style:"), 3, textStyles, 0, wxCHOICEDLG_STYLE);
        if (newChoiceDialog->ShowModal() == wxID_CANCEL) return;
        wxString selStr = newChoiceDialog->GetStringSelection();

        if (selStr == _("Bold")) {
            inText = "**" + inText + "**";
        } else if (selStr == _("Italic")) {
            inText = "*" + inText + "*";
        } else if (selStr == _("Strikethrough")) {
            inText = "~~" + inText + "~~";
        }

        newChoiceDialog->Destroy();

    } else if (selLabel == _("Rule")) {

        GLOBALS::TabPageSTC->InsertText(curPos, "---");
        //GLOBALS::TabPageSTC->SetCurrentPos(curPos+3);
        return;
    }

    if (gotSel) {
        GLOBALS::TabPageSTC->ReplaceSelection(inText);
    } else {
        GLOBALS::TabPageSTC->InsertText(curPos, inText);
    }

    if (GLOBALS::TabPageSTC->AutoCompActive())
        GLOBALS::TabPageSTC->AutoCompCancel();

    //GLOBALS::TabPageSTC->SetAnchor(GLOBALS::TabPageSTC->GetCurrentPos());
}

void WordsmithFrame::OnTabLoseFocus(wxFocusEvent& event)
{
    if (GLOBALS::TabPageSTC->AutoCompActive())
        GLOBALS::TabPageSTC->AutoCompCancel();

    event.Skip();
}

void WordsmithFrame::OnQuit(wxCommandEvent& event)
{
    Close(true);
}

void WordsmithFrame::OnClose(wxCloseEvent& event)
{
    bool unsaved = false;
    wxString tabFiles, selStr, fontStr;

    for (size_t i=0; i < AuiNotebook1->GetPageCount(); ++i)
    {
        wsTextCtrl* stc((wsTextCtrl*)AuiNotebook1->GetPage(i)->GetChildren().GetFirst()->GetData());

        if (stc->IsChanged() && (!stc->GetFilePath().empty() || stc->GetLength() > 0)) unsaved = true;

        if (!stc->GetFilePath().empty()) {
            selStr = (GLOBALS::TabPageSTC == stc) ? "1" : "0";

            if (stc->HasCustomFont()) {

                wxColor fontClr(stc->StyleGetForeground(wxSTC_STYLE_DEFAULT));
                wxFont stcFont(stc->StyleGetFont(wxSTC_STYLE_DEFAULT));

                fontStr = stcFont.GetFaceName() + "|" +
                          std::to_string(stcFont.GetPointSize()) + "|" +
                          std::to_string((int)stcFont.GetWeight()) + "|" +
                          std::to_string((int)stcFont.GetStyle()) + "|" +
                          fontClr.GetAsString();
            } else {
                fontStr = "default";
            }

            tabFiles += stc->GetFilePath() + "\r" + fontStr + "\r" +
                        std::to_string(stc->GetWrapMode()) + "\r" +
                        std::to_string(stc->GetZoom()) + "\r" + selStr + "\n";
        }
    }

    if (unsaved) {
        QuestionDialog1->SetMessage(_("There are unsaved files still open. Do you really want to close the app?"));
        int answer = QuestionDialog1->ShowModal();
        if (answer == wxID_NO || answer == wxID_CANCEL) return;
    }

    wxPoint pos(GetScreenPosition());
    wxSize sz(GetClientSize());

    GLOBALS::Settings["TB"] = ToolBar1->IsShown() ? "1" : "0";
    GLOBALS::Settings["SB"] = StatusBar1->IsShown() ? "1" : "0";
    GLOBALS::Settings["WIN_X"] = std::to_string(pos.x);
    GLOBALS::Settings["WIN_Y"] = std::to_string(pos.y);
    GLOBALS::Settings["WIN_WIDTH"] = std::to_string(sz.GetWidth());
    GLOBALS::Settings["WIN_HEIGHT"] = std::to_string(sz.GetHeight());

    SaveConfigFile(u8"./files/settings.cfg", GLOBALS::Settings);

    WriteFileStr(u8"./files/open_files_list.ws", tabFiles.utf8_string());

    wxTheClipboard->Flush();

    event.Skip();
}
