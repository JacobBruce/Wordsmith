/***************************************************************
 * Name:      WordsmithApp.h
 * Purpose:   Defines Application Class
 * Author:    Bitfreak Software (contact@bitfreak.info)
 * Created:   2026-02-26
 * Copyright: Bitfreak Software (www.bitfreak.info)
 * License:   CC BY-NC-SA 4.0
 **************************************************************/

#ifndef WORDSMITHAPP_H
#define WORDSMITHAPP_H

#include <wx/app.h>
#include <wx/snglinst.h>
#include <wx/ipc.h>

class WordsmithFrame;

class WordsmithApp : public wxApp
{
	public:
		virtual bool OnInit();
		virtual int OnExit();
		void HandleIpcOpen(const wxString& file_path);

	private:
		wxString IpcService() const;
		bool SendToRunningInstance();

		wxSingleInstanceChecker* m_checker = nullptr;
		wxServer* m_server = nullptr;
		WordsmithFrame* m_frame = nullptr;
};

wxDECLARE_APP(WordsmithApp);

#endif // WORDSMITHAPP_H
