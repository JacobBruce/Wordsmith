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
    if (FileExists(u8"./files/settings.cfg")) {
        LoadConfigFile(u8"./files/settings.cfg", GLOBALS::Settings);
    } else {
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
