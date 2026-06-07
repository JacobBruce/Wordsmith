/***************************************************************
 * Name:      WordsmithApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Bitfreak Software (contact@bitfreak.info)
 * Created:   2026-02-26
 * Copyright: Bitfreak Software (www.bitfreak.info)
 * License:   CC BY-NC-SA 4.0
 **************************************************************/

#include "WordsmithApp.h"

//(*AppHeaders
#include "WordsmithMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(WordsmithApp);

inline bool EnsureUtf8Ctype()
{
    const char* cur = std::setlocale(LC_CTYPE, nullptr);

    if (cur && (std::strstr(cur, "UTF-8") || std::strstr(cur, "utf8")))
        return true;

    return std::setlocale(LC_CTYPE, "en_US.UTF-8") != nullptr
        || std::setlocale(LC_CTYPE, "C.UTF-8") != nullptr
        || std::setlocale(LC_CTYPE, ".UTF-8") != nullptr;
}

bool WordsmithApp::OnInit()
{
    if (!EnsureUtf8Ctype()) {
        wxMessageBox(_("Invalid C locale detected. Closing application."), _("Invalid Locale"), wxOK | wxCENTER | wxICON_ERROR);
        return false;
    }

    std::string cwdPath = ParentPath(wxStandardPaths::Get().GetExecutablePath().utf8_string());
    GLOBALS::UserDataDir = wxStandardPaths::Get().GetUserDataDir().utf8_string();

    if (!DirExists(GLOBALS::UserDataDir) && !CreateDir(GLOBALS::UserDataDir))
        wxMessageBox(_("Failed to create user data directory. Check permissions."), _("Permission Error"), wxOK | wxCENTER | wxICON_ERROR);

    if (FileExists(GLOBALS::UserDataDir + "/settings.cfg")) {
        LoadConfigFile(GLOBALS::UserDataDir + "/settings.cfg", GLOBALS::Settings);
    } else if (FileExists("./files/settings.cfg")) {
        GLOBALS::Settings["CWD"] = cwdPath + "/files";
        LoadConfigFile("./files/settings.cfg", GLOBALS::Settings);
    }

    if (!GLOBALS::Settings.contains("CWD"))
        GLOBALS::Settings["CWD"] = cwdPath;
    if (!GLOBALS::Settings.contains("THEME"))
        GLOBALS::Settings["THEME"] = "0";
    if (!GLOBALS::Settings.contains("EOL"))
        GLOBALS::Settings["EOL"] = "0";
    if (!GLOBALS::Settings.contains("AC"))
        GLOBALS::Settings["AC"] = "1";
    if (!GLOBALS::Settings.contains("TB"))
        GLOBALS::Settings["TB"] = "1";
    if (!GLOBALS::Settings.contains("SB"))
        GLOBALS::Settings["SB"] = "1";
    if (!GLOBALS::Settings.contains("FONT"))
        GLOBALS::Settings["FONT"] = "default";
    if (!GLOBALS::Settings.contains("FONT_COLOR"))
        GLOBALS::Settings["FONT_COLOR"] = "default";
    if (!GLOBALS::Settings.contains("WIN_X"))
        GLOBALS::Settings["WIN_X"] = "default";
    if (!GLOBALS::Settings.contains("WIN_Y"))
        GLOBALS::Settings["WIN_Y"] = "default";
    if (!GLOBALS::Settings.contains("WIN_WIDTH"))
        GLOBALS::Settings["WIN_WIDTH"] = "800";
    if (!GLOBALS::Settings.contains("WIN_HEIGHT"))
        GLOBALS::Settings["WIN_HEIGHT"] = "600";

    if (GLOBALS::Settings["THEME"] == "0") {
        SetAppearance(wxApp::Appearance::System);
    } else if (GLOBALS::Settings["THEME"] == "1") {
        SetAppearance(wxApp::Appearance::Dark);
    } else {
        SetAppearance(wxApp::Appearance::Light);
    }

    if (DirExists(GLOBALS::Settings["CWD"]))
        std::filesystem::current_path(GLOBALS::Settings["CWD"]);

    if (!FileExists("./icons/app_icon.png")) {

        int answer = wxMessageBox(_("Unable to locate required app files. Are they already on your system?"), _("Missing Files"), wxYES_NO | wxCENTER | wxICON_ERROR);

        if (answer == wxYES || answer == wxOK) {

            wxString dir = wxDirSelector("Select folder with app files");

            if (dir.ends_with('/') || dir.ends_with('\\'))
                dir.RemoveLast();

            if (dir.EndsWith("/icons") || dir.EndsWith("\\icons"))
                dir.RemoveLast(6);

            std::string dirPath(dir.utf8_string());

            if (DirExists(dirPath)) {
                std::filesystem::current_path(dirPath);
                GLOBALS::Settings["CWD"] = dirPath;
            }

            if (!FileExists("./icons/app_icon.png")) {
                wxMessageBox(_("Failed to locate required files. Closing application."), _("Missing Files"), wxOK | wxCENTER | wxICON_ERROR);
                return false;
            }

        } else {
            wxMessageBox(_("The required app files are available on the Wordsmith releases page:\n\n") +
                           "https://github.com/JacobBruce/Wordsmith/releases", _("Missing Files"), wxOK | wxCENTER | wxICON_INFORMATION);
            return false;
        }
    }

    GLOBALS::ArgFiles.reserve(this->argc);

    for (int c=1; c < this->argc; ++c)
    {
        const std::string argStr(this->argv[c].utf8_string());

        if (FileExists(argStr))
            GLOBALS::ArgFiles.emplace_back(this->argv[c], argStr);
    }

    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
        WordsmithFrame* Frame = new WordsmithFrame(0);
        Frame->Show();
        SetTopWindow(Frame);
    }
    //*)

    return wxsOK;
}
