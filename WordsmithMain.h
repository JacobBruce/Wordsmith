/***************************************************************
 * Name:      WordsmithMain.h
 * Purpose:   Defines Application Frame
 * Author:    Bitfreak Software (contact@bitfreak.info)
 * Created:   2026-02-26
 * Copyright: Bitfreak Software (www.bitfreak.info)
 * License:
 **************************************************************/

#ifndef WORDSMITHMAIN_H
#define WORDSMITHMAIN_H

#define APP_VER "0.0.2"

#pragma once
#include <set>
#include <mutex>
#include <thread>
#include <symspell/symspell.hpp>
#include "crc_32.h"
#include "md5.h"
#include "sha1.h"
#include "sha2_256.h"
#include "sha2_512.h"
#include "WordParser.h"

//(*Headers(WordsmithFrame)
#include <wx/aui/aui.h>
#include <wx/choicdlg.h>
#include <wx/colordlg.h>
#include <wx/filedlg.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/statusbr.h>
#include <wx/stopwatch.h>
#include <wx/textdlg.h>
#include <wx/toolbar.h>
//*)

#include <wx/html/htmprint.h>
#include <wx/html/htmlwin.h>
#include <wx/hyperlink.h>
#include <wx/webrequest.h>
#include <wx/webview.h>
#include <wx/utils.h>
#include <wx/clipbrd.h>
#include <wx/stdpaths.h>
#include <wx/dirdlg.h>
#include <wx/fdrepdlg.h>
#include <wx/wfstream.h>
#include <wx/fontdlg.h>
#include <wx/fontdata.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/statline.h>
#include <wx/statbmp.h>
#include <wx/choice.h>
#include <wx/fontpicker.h>
#include <wx/clrpicker.h>
#include <wx/stc/stc.h>
#include <wx/settings.h>

class wsHtmlWindow : public wxHtmlWindow
{
public:
    wsHtmlWindow(wxWindow* parent, wxWindowID id, const wxPoint& pos=wxDefaultPosition,
                 const wxSize& size=wxDefaultSize, long style=wxHW_SCROLLBAR_NEVER);
    void OnLinkClicked(const wxHtmlLinkInfo& info) override;
};

class HTMLFrame : public wxFrame
{
public:

    HTMLFrame();
    void OnClose(wxCloseEvent& event);
    void OnCloseClick(wxCommandEvent& event);
    void SetMode0(wxCommandEvent& event);
    void SetMode1(wxCommandEvent& event);
    void SetMode(const int& mode);
    void LoadFile(const wxString& file_path);
    void OnNavigationRequest(wxWebViewEvent& event);
    void ReloadPage();

private:

    int viewMode;
    std::string cssStr;
    wxString filePath;
    wxMenuItem* htmlMenuItem;
    wxMenuItem* mdMenuItem;
    wxWebView* webView;
};

class wsTextCtrl : public wxStyledTextCtrl
{
public:
    wsTextCtrl(wxWindow* parent, wxWindowID id, const wxPoint& pos,
            const wxSize& size, long style, const wxString& name);

    const bool IsChanged() const;
    const bool IsIndicated() const;
    void SetChanged(bool changed=true);
    void SetIndicated(bool indicated=true);
    void SetFilePath(const wxString& file_path);
    void SetFileName(const wxString& file_name);
    const wxString& GetFilePath() const;
    const wxString& GetFileName() const;
    const bool HasCustomFont() const;
    void SetCustomFont(const wxFont& font);
    void SetFontColor(const wxColor& color);
    void SetColoredFont(const wxFont& font, const wxColor& color);

private:

    wxString m_FilePath;
    wxString m_FileName;
    bool m_IsModified;
    bool m_IsIndicated;
    bool m_HasCustomFont;
};

class wsTextShowDialog : public wxDialog {
public:
    wsTextShowDialog(wxWindow* parent, const wxString& message, const wxString& caption,
                     const wxString& value, const wxPoint& pos=wxDefaultPosition, const wxSize sz=wxDefaultSize);

    wxString GetValue() const;
    void SetValue(const wxString& value);

private:
    wxTextCtrl* textCtrl;
};

class wsSettingsDialog : public wxDialog {
public:
    wsSettingsDialog(wxWindow* parent, const wxString& caption, const wxPoint& pos=wxDefaultPosition, const wxSize sz=wxDefaultSize);

    void Reset(bool init=false);
    void ApplySettings(bool init=false);
    void FontButtonClick(wxCommandEvent& event);
    void SaveButtonClick(wxCommandEvent& event);
    void CloseButtonClick(wxCommandEvent& event);

private:
    wxStaticText* label1;
    wxStaticText* label2;
    wxStaticText* label3;
    wxStaticText* label4;

    wxChoice* themeChoice;
    wxChoice* eolChoice;
    wxChoice* acChoice;

    wxFont defaultFont;
    //wxFontPickerCtrl* fontPicker;
    wxColourPickerCtrl* colorPicker;

    wxButton* fontBtn;
    wxButton* applyBtn;
    wxButton* closeBtn;
};

class wsWordsDialog : public wxDialog {
public:
    wsWordsDialog(wxWindow* parent, const wxString& caption, const wxPoint& pos=wxDefaultPosition, const wxSize sz=wxDefaultSize);

    void SaveButtonClick(wxCommandEvent& event);
    void CloseButtonClick(wxCommandEvent& event);
    void AddWord(const std::string& word);
    void RemoveWord(const std::string& word);
    void UpdateLists(bool save=true);
    void LoadWords(std::u8string file_path);
    void SaveWords();
    void Reset();

private:
    wxStaticText* label1;
    wxStaticText* label2;

    wxTextCtrl* newWords;
    wxTextCtrl* badWords;

    wxButton* applyBtn;
    wxButton* closeBtn;
};

class wsPhrasesDialog : public wxDialog {
public:
    wsPhrasesDialog(wxWindow* parent, const wxString& caption, const wxPoint& pos=wxDefaultPosition, const wxSize sz=wxDefaultSize);

    void SaveButtonClick(wxCommandEvent& event);
    void CloseButtonClick(wxCommandEvent& event);
    void AddPhrase(const std::string& phrase);
    void UpdateList(bool save=true);
    void LoadPhrases(std::u8string file_path);
    void SavePhrases();
    void Reset();

private:
    wxStaticText* label1;
    wxStaticText* label2;
    wxTextCtrl* phrases;

    wxButton* applyBtn;
    wxButton* closeBtn;
};

class wsDictDialog : public wxDialog {
public:
    wsDictDialog(wxWindow* parent, const wxString& caption, const wxPoint& pos=wxDefaultPosition, const wxSize sz=wxDefaultSize);

    void CloseButtonClick(wxCommandEvent& event);
    void OnSearchWordChanged(wxCommandEvent& event);
    //void OnSearchEnter(wxCommandEvent& event);
    void DoSearch(const wxString& search_txt);
    void AddWordToAC(const std::string& word);
    void SetReady();

private:
    wxTextCtrl* defText;
    wxTextCtrl* exText;
    wxTextCtrl* searchBar;
    wxButton* closeBtn;
    wxArrayString autoWords;
    bool autoCompleted = false;
};

class wsTipsDialog : public wxDialog {
public:
    wsTipsDialog(wxWindow* parent, const wxString& caption, const wxPoint& pos=wxDefaultPosition, const wxSize sz=wxDefaultSize);

    void NextButtonClick(wxCommandEvent& event);
    void CloseButtonClick(wxCommandEvent& event);

private:
    wxStaticBitmap* infoIcon;
    wxStaticText* label1;

    wxButton* nextBtn;
    wxButton* closeBtn;

    uint32_t tipIndex;

    std::array<wxString,8> tips = {
        _("You can open the Web Viewer with the F9 key to preview Markdown and HTML documents."),
        _("Right click on a misspelled word to show a list of replacement word suggestions."),
        _("You can right click on a word to see a list of synonyms and other related words."),
        _("The app theme and other global options can be changed in Settings->Preferences."),
        _("You can apply Markdown formatting by highlighting text before using the Insert->Markdown menu."),
        _("Briefly hover the mouse over a word to show the possible definitions for that word."),
        _("The dictionary tool provides word definitions and usage examples from the Open English Wordnet."),
        _("Press Shift+Space to show an auto-complete list with your phrases (see Tools->Phrase Manager).")
    };
};

class wsAboutDialog : public wxDialog {
public:
    wsAboutDialog(wxWindow* parent, const wxString& caption, const wxPoint& pos=wxDefaultPosition, const wxSize sz=wxDefaultSize);

    void CheckButtonClick(wxCommandEvent& event);
    void CloseButtonClick(wxCommandEvent& event);
    void OnStateChange(wxWebRequestEvent& event);
    void ShowDialog();

private:
    uint64_t lastCheck = 0;
    wxWebRequest webReq;

    wxStaticBitmap* appIcon;
    wsHtmlWindow* aboutHTML;

    wxButton* checkBtn;
    wxButton* closeBtn;
};

namespace GLOBALS {

    inline wxString WordChars = wxString::FromUTF8(WordParser::U32ToU8(U"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'-àáâãäåæçèéêëìíîïðñòóôõöøùúûüýÿþÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝÞß"));
    inline wxString LastPhrase = wxEmptyString;
    inline wxChar LastKeyPress = WXK_NONE;
    inline bool GotPhraseKeys = false;
    inline std::atomic<bool> GotWordData = false;
    inline std::thread* LoadThread = nullptr;
    inline wsTextCtrl* TabPageSTC = nullptr;
    inline phmap::parallel_flat_hash_set<std::string> UserWords;
    inline phmap::parallel_flat_hash_set<std::string> SkipWords;
    inline phmap::parallel_flat_hash_set<std::string> UserPhrases;
    inline phmap::parallel_flat_hash_map<std::string, WordEntry> WordNet;
    inline phmap::parallel_flat_hash_map<std::string, std::vector<std::string>> WordSyn;
	inline phmap::parallel_flat_hash_map<std::string, std::vector<std::pair<uint32_t,float>>> SimWords;
    inline phmap::parallel_flat_hash_map<std::string, std::pair<uint32_t,AfterLinks>> WordMap;
	inline phmap::parallel_flat_hash_map<std::string, uint32_t> WebIndices;
    inline std::vector<std::pair<std::string, uint32_t>> WordVec;
    inline std::vector<std::pair<wxString, std::u8string>> ArgFiles;
    inline std::unordered_map<std::string, std::string> Settings;
    inline std::u8string UserDataDir;
    inline std::string LineEndStr = "\n";
    inline int LineEndMode = wxSTC_EOL_LF;
    inline int AutoCompMode = 0;
    inline wxFont DefaultFont = wxNullFont;
    inline wxColor DefFontColor;
};

class WordsmithFrame: public wxFrame
{
    friend wsSettingsDialog;
    friend wsWordsDialog;

    public:

        WordsmithFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~WordsmithFrame();

    private:

        int findPos = 0;
        uint64_t charsTyped = 0;
        bool searchMode = 0;
        yams::symspell::SymSpell spellChecker;
        wsSettingsDialog* settingsDialog;
        wsWordsDialog* wordsDialog;
        wsPhrasesDialog* phrasesDialog;
        wsDictDialog* dictDialog;
        wsTipsDialog* tipsDialog;
        wsAboutDialog* aboutDialog;
        wxFindReplaceDialog* findDialog;
        wxFindReplaceData findData;
        wxTimer initTimer;
        wxTimer toolsTimer;
        wxTimer statsTimer;
        wxTimer ackeyTimer;
        wxTimer spellTimer;
        wxTimer infoTimer;
        wxHtmlEasyPrinting easyPrint;
        HTMLFrame* docViewer;

        void NewPadTab(int wrap=wxSTC_WRAP_WORD, int zoom=0);
        void UpdateStatusBar();
        void UpdateToolBar();
        void BindTextCtrl(wsTextCtrl* stc);
        void ShowFontDialog();
        void ShowPrintDialog(bool preview=false);
        void ShowPageDialog();
        void ShowOpenDialog();
        void ShowSaveDialog(bool force_show=false);
        void ShowFindDialog();
        void ShowReplaceDialog();
        void ShowSearchDialog(bool show_replace=false);
        void FindNext(const wxString& find_str, const int& flags);
        void SetStatusBarText(const wxString& txt);
        void LoadDocument(const wxString& file_path, const wxString& file_name);
        bool SelectTabPage(const wxString& file_name);
        bool LoadWebViewer(bool show_msg=true);
        bool IsNotWord(const std::string& word);

        //(*Handlers(WordsmithFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAboutClick(wxCommandEvent& event);
        void OnNewFileClick(wxCommandEvent& event);
        void OnFontClick(wxCommandEvent& event);
        void OnPrintClick(wxCommandEvent& event);
        void OnOpenFileClick(wxCommandEvent& event);
        void OnFindClick(wxCommandEvent& event);
        void OnReplaceClick(wxCommandEvent& event);
        void OnPageClick(wxCommandEvent& event);
        void OnSaveClick(wxCommandEvent& event);
        void OnSaveAsClick(wxCommandEvent& event);
        void OnUndoClick(wxCommandEvent& event);
        void OnRedoClick(wxCommandEvent& event);
        void OnCutClick(wxCommandEvent& event);
        void OnCopyClick(wxCommandEvent& event);
        void OnPasteClick(wxCommandEvent& event);
        void OnHashClick(wxCommandEvent& event);
        void OnTipsClick(wxCommandEvent& event);
        void OnSelectAllClick(wxCommandEvent& event);
        void OnDeleteClick(wxCommandEvent& event);
        void OnTimestampClick(wxCommandEvent& event);
        void OnAutoCompleted(wxStyledTextEvent& event);
        void OnTextChanged(wxStyledTextEvent& event);
        void OnMouseHover(wxStyledTextEvent& event);
        void OnMouseHoverEnd(wxStyledTextEvent& event);
        void OnTabPageChanged(wxAuiNotebookEvent& event);
        void OnTabPageClosed(wxAuiNotebookEvent& event);
        void OnKeyPress(wxKeyEvent& event);
        void OnKeyUp(wxKeyEvent& event);
        void OnInitTimerTrigger(wxTimerEvent& event);
        void OnInfoTimerTrigger(wxTimerEvent& event);
        void OnToolsTimerTrigger(wxTimerEvent& event);
        void OnStatsTimerTrigger(wxTimerEvent& event);
        void OnACKeyTimerTrigger(wxTimerEvent& event);
        void OnSpellCheckTrigger(wxTimerEvent& event);
        void OnMouseUp(wxMouseEvent& event);
        void OnMouseRightDown(wxMouseEvent& event);
        void OnToggleToolBar(wxCommandEvent& event);
        void OnToggleStatusBar(wxCommandEvent& event);
        void OnToggleWordWrap(wxCommandEvent& event);
        void OnPreviewClick(wxCommandEvent& event);
        void OnDocViewClick(wxCommandEvent& event);
        void OnFindFirst(wxFindDialogEvent& event);
        void OnFindNext(wxFindDialogEvent& event);
        void OnFindReplace(wxFindDialogEvent& event);
        void OnFindReplaceAll(wxFindDialogEvent& event);
        void OnFindClose(wxFindDialogEvent& event);
        void OnFindNextClick(wxCommandEvent& event);
        void OnFontColorClick(wxCommandEvent& event);
        void OnZoomInClick(wxCommandEvent& event);
        void OnZoomOutClick(wxCommandEvent& event);
        void OnZoomResetClick(wxCommandEvent& event);
        void OnSwapWordClick(wxCommandEvent& event);
        void OnMenuHover(wxCommandEvent& event);
        void OnMenuClose(wxMenuEvent& event);
        void OnMenuOpen(wxMenuEvent& event);
        void OnTabPageClose(wxAuiNotebookEvent& event);
        void OnContextMenu(wxContextMenuEvent& event);
        void OnTabLoseFocus(wxFocusEvent& event);
        void OnAddMarkdownClick(wxCommandEvent& event);
        void OnDateTimeClick(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnToggleSpellCheck(wxCommandEvent& event);
        void OnTextStatsClick(wxCommandEvent& event);
        void OnSessionStatsClick(wxCommandEvent& event);
        void OnDictionaryClick(wxCommandEvent& event);
        void OnPreferencesClick(wxCommandEvent& event);
        void OnWordManagerClick(wxCommandEvent& event);
        void OnPhraseManagerClick(wxCommandEvent& event);
        void OnRemoveWord(wxCommandEvent& event);
        void OnAddWord(wxCommandEvent& event);
        void OnAddPhrase(wxCommandEvent& event);
        //*)

        //(*Identifiers(WordsmithFrame)
        static const wxWindowID ID_AUINOTEBOOK1;
        static const wxWindowID ID_MENUITEM2;
        static const wxWindowID ID_MENUITEM3;
        static const wxWindowID ID_MENUITEM4;
        static const wxWindowID ID_MENUITEM5;
        static const wxWindowID ID_MENUITEM30;
        static const wxWindowID ID_MENUITEM25;
        static const wxWindowID ID_MENUITEM26;
        static const wxWindowID ID_MENUITEM1;
        static const wxWindowID ID_MENUITEM6;
        static const wxWindowID ID_MENUITEM7;
        static const wxWindowID ID_MENUITEM8;
        static const wxWindowID ID_MENUITEM9;
        static const wxWindowID ID_MENUITEM10;
        static const wxWindowID ID_MENUITEM11;
        static const wxWindowID ID_MENUITEM39;
        static const wxWindowID ID_MENUITEM12;
        static const wxWindowID ID_MENUITEM13;
        static const wxWindowID ID_MENUITEM47;
        static const wxWindowID ID_MENUITEM48;
        static const wxWindowID ID_MENUITEM49;
        static const wxWindowID ID_MENUITEM46;
        static const wxWindowID ID_MENUITEM14;
        static const wxWindowID ID_MENUITEM15;
        static const wxWindowID ID_MENUITEM28;
        static const wxWindowID ID_MENUITEM31;
        static const wxWindowID ID_MENUITEM32;
        static const wxWindowID ID_MENUITEM33;
        static const wxWindowID ID_MENUITEM34;
        static const wxWindowID ID_MENUITEM35;
        static const wxWindowID ID_MENUITEM36;
        static const wxWindowID ID_MENUITEM38;
        static const wxWindowID ID_MENUITEM37;
        static const wxWindowID ID_MENUITEM16;
        static const wxWindowID ID_MENUITEM50;
        static const wxWindowID ID_MENUITEM29;
        static const wxWindowID ID_MENUITEM17;
        static const wxWindowID ID_MENUITEM18;
        static const wxWindowID ID_MENUITEM22;
        static const wxWindowID ID_MENUITEM23;
        static const wxWindowID ID_MENUITEM52;
        static const wxWindowID ID_MENUITEM41;
        static const wxWindowID ID_MENUITEM27;
        static const wxWindowID ID_MENUITEM42;
        static const wxWindowID ID_MENUITEM43;
        static const wxWindowID ID_MENUITEM44;
        static const wxWindowID ID_MENUITEM40;
        static const wxWindowID ID_MENUITEM19;
        static const wxWindowID ID_MENUITEM45;
        static const wxWindowID ID_MENUITEM20;
        static const wxWindowID ID_MENUITEM51;
        static const wxWindowID ID_MENUITEM21;
        static const wxWindowID idMenuAbout;
        static const wxWindowID ID_MENUITEM24;
        static const wxWindowID ID_STATUSBAR1;
        static const wxWindowID new_btn;
        static const wxWindowID open_btn;
        static const wxWindowID save_btn;
        static const wxWindowID saveas_btn;
        static const wxWindowID undo_btn;
        static const wxWindowID redo_btn;
        static const wxWindowID cut_btn;
        static const wxWindowID copy_btn;
        static const wxWindowID paste_btn;
        static const wxWindowID find_btn;
        static const wxWindowID dict_btn;
        static const wxWindowID tips_btn;
        static const wxWindowID ID_TOOLBAR1;
        static const wxWindowID ID_MESSAGEDIALOG1;
        static const wxWindowID ID_MESSAGEDIALOG2;
        static const wxWindowID ID_MESSAGEDIALOG3;
        static const wxWindowID ID_TEXTENTRYDIALOG1;
        //*)

        //(*Declarations(WordsmithFrame)
        wxAuiManager* AuiManager1;
        wxAuiNotebook* AuiNotebook1;
        wxColourDialog* ColourDialog1;
        wxFileDialog* FileOpenDialog1;
        wxFileDialog* FileSaveDialog1;
        wxMenu* EditMenu;
        wxMenu* HashMenuItem;
        wxMenu* InsertMenu;
        wxMenu* MarkdownMenuItem;
        wxMenu* SettingsMenu;
        wxMenu* ToolsMenu;
        wxMenu* ViewMenu;
        wxMenu* ZoomMenuItem;
        wxMenuItem* CopyMenuItem;
        wxMenuItem* CryptoMenuItem;
        wxMenuItem* CutMenuItem;
        wxMenuItem* DateTimeMenuItem;
        wxMenuItem* DictionaryMenuItem;
        wxMenuItem* FindMenuItem;
        wxMenuItem* FontColorMenuItem;
        wxMenuItem* FontStyleMenuItem;
        wxMenuItem* MenuItem1;
        wxMenuItem* MenuItem33;
        wxMenuItem* MenuItem34;
        wxMenuItem* MenuItem35;
        wxMenuItem* MenuItem36;
        wxMenuItem* MenuItem37;
        wxMenuItem* MenuItem38;
        wxMenuItem* MenuItem39;
        wxMenuItem* MenuItem40;
        wxMenuItem* MenuItem43;
        wxMenuItem* MenuItem44;
        wxMenuItem* MenuItem45;
        wxMenuItem* MenuItem46;
        wxMenuItem* MenuItem49;
        wxMenuItem* MenuItem50;
        wxMenuItem* MenuItem51;
        wxMenuItem* NewMenuItem;
        wxMenuItem* NextMenuItem;
        wxMenuItem* OpenMenuItem;
        wxMenuItem* PageMenuItem;
        wxMenuItem* PasteMenuItem;
        wxMenuItem* PreferencesMenuItem;
        wxMenuItem* PreviewMenuItem;
        wxMenuItem* PrintMenuItem;
        wxMenuItem* RedoMenuItem;
        wxMenuItem* ReplaceMenuItem;
        wxMenuItem* SaveAsMenuItem;
        wxMenuItem* SaveMenuItem;
        wxMenuItem* SelectMenuItem;
        wxMenuItem* SessionMenuItem;
        wxMenuItem* SpellCheckMenuItem;
        wxMenuItem* StatusBarMenuItem;
        wxMenuItem* TextStatsMenuItem;
        wxMenuItem* TimestampMenuItem;
        wxMenuItem* TipsMenuItem;
        wxMenuItem* ToolBarMenuItem;
        wxMenuItem* UndoMenuItem;
        wxMenuItem* WebViewMenuItem;
        wxMenuItem* WordWrapMenuItem;
        wxMenuItem* WordsMenuItem;
        wxMessageDialog* ErrorDialog1;
        wxMessageDialog* MessageDialog1;
        wxMessageDialog* QuestionDialog1;
        wxSingleChoiceDialog* SingleChoiceDialog1;
        wxStatusBar* StatusBar1;
        wxStopWatch SessionWatch;
        wxTextEntryDialog* TextEntryDialog1;
        wxToolBar* ToolBar1;
        wxToolBarToolBase* CopyToolBarBtn;
        wxToolBarToolBase* CutToolBarBtn;
        wxToolBarToolBase* DictToolBarBtn;
        wxToolBarToolBase* FindToolBarBtn;
        wxToolBarToolBase* NewToolBarBtn;
        wxToolBarToolBase* OpenToolBarBtn;
        wxToolBarToolBase* PasteToolBarBtn;
        wxToolBarToolBase* RedoToolBarBtn;
        wxToolBarToolBase* SaveAsToolBarBtn;
        wxToolBarToolBase* SaveToolBarBtn;
        wxToolBarToolBase* TipsToolBarBtn;
        wxToolBarToolBase* UndoToolBarBtn;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // WORDSMITHMAIN_H
