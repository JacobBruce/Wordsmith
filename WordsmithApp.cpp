/***************************************************************
 * Name:      WordsmithApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Bitfreak Software (contact@bitfreak.info)
 * Created:   2026-02-26
 * Copyright: Bitfreak Software (www.bitfreak.info)
 * License:
 **************************************************************/

#include "WordsmithApp.h"

//(*AppHeaders
#include "WordsmithMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(WordsmithApp);

bool WordsmithApp::OnInit()
{
    std::string exePath = wxStandardPaths::Get().GetExecutablePath().utf8_string();
    std::string cwdPath = ParentPath((const char8_t*)exePath.data());
    std::string dataDir = wxStandardPaths::Get().GetUserDataDir().utf8_string();
    GLOBALS::UserDataDir = (const char8_t*)dataDir.data();

    if (!DirExists(GLOBALS::UserDataDir) && !CreateDir(GLOBALS::UserDataDir))
        wxMessageBox(_("Failed to create user data directory. Check permissions."), _("Permission Error"), wxOK | wxCENTER | wxICON_ERROR);

    if (FileExists(GLOBALS::UserDataDir + u8"/settings.cfg")) {
        LoadConfigFile(GLOBALS::UserDataDir + u8"/settings.cfg", GLOBALS::Settings);
    } else if (FileExists(u8"./files/settings.cfg")) {
        GLOBALS::Settings["CWD"] = cwdPath + "/files";
        LoadConfigFile(u8"./files/settings.cfg", GLOBALS::Settings);
    } else {
        GLOBALS::Settings["CWD"] = cwdPath;
        GLOBALS::Settings["THEME"] = "0";
        GLOBALS::Settings["EOL"] = "0";
        GLOBALS::Settings["AC"] = "1";
        GLOBALS::Settings["TB"] = "1";
        GLOBALS::Settings["SB"] = "1";
        GLOBALS::Settings["FONT"] = "default";
        GLOBALS::Settings["FONT_COLOR"] = "default";
        GLOBALS::Settings["WIN_X"] = "default";
        GLOBALS::Settings["WIN_Y"] = "default";
        GLOBALS::Settings["WIN_WIDTH"] = "800";
        GLOBALS::Settings["WIN_HEIGHT"] = "600";
    }

    if (GLOBALS::Settings["THEME"] == "0") {
        SetAppearance(wxApp::Appearance::System);
    } else if (GLOBALS::Settings["THEME"] == "1") {
        SetAppearance(wxApp::Appearance::Dark);
    } else {
        SetAppearance(wxApp::Appearance::Light);
    }

    std::u8string cwdU8 = (const char8_t*)GLOBALS::Settings["CWD"].data();
    if (DirExists(cwdU8)) std::filesystem::current_path(cwdU8);

    if (!FileExists(u8"./icons/app_icon.png")) {

        int answer = wxMessageBox(_("Unable to locate required app files. Are they already on your system?"), _("Missing Files"), wxYES_NO | wxCENTER | wxICON_ERROR);

        if (answer == wxYES || answer == wxOK) {

            wxString dir = wxDirSelector("Select folder with app files");

            if (dir.ends_with('/') || dir.ends_with('\\'))
                dir.RemoveLast();

            if (dir.EndsWith("/icons") || dir.EndsWith("\\icons"))
                dir.RemoveLast(6);

            std::string dirStr(dir.utf8_string());
            const std::u8string& dirPath((const char8_t*)dirStr.data());

            if (DirExists(dirPath)) {
                std::filesystem::current_path(dirPath);
                GLOBALS::Settings["CWD"] = dirStr;
            }

            if (!FileExists(u8"./icons/app_icon.png")) {
                wxMessageBox(_("Failed to locate required files. Closing application."), _("Missing Files"), wxOK | wxCENTER | wxICON_ERROR);
                exit(EXIT_FAILURE);
            }

        } else {
            wxMessageBox(_("The required app files are available on the Wordsmith releases page:\n\n") +
                           "https://github.com/JacobBruce/Wordsmith/releases", _("Missing Files"), wxOK | wxCENTER | wxICON_INFORMATION);
            exit(EXIT_FAILURE);
        }
    }

    GLOBALS::ArgFiles.reserve(this->argc);

    for (int c=1; c < this->argc; ++c)
    {
        const std::string argStr(this->argv[c].utf8_string());
        const std::u8string& filePath((const char8_t*)argStr.data());

        if (FileExists(filePath))
            GLOBALS::ArgFiles.emplace_back(this->argv[c], filePath);
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
