#pragma once
#include "wx/wx.h"
#include "wx/spinctrl.h"
#include "Settings.h"
#include "Character.h"

#include <fstream>

enum TextBoxes {
	CharacterName = 10001
};

enum ElementIDs {
	STR = 11001,
	DEX,
	CON,
	INTEL,
	WIS,
	CHA,
	LVL,
	ClassComboBox
};

enum MenuItemIDs {
	LightTheme = 20000,
	DarkTheme
};

struct Theme {					//theme struct
	wxColor backGroundColor;
	wxColor foreGroundColor;
	ThemeChoice themeChoice = ThemeChoice::Light;

	Theme(ThemeChoice choice = ThemeChoice::Light) {		//Theme Constructor
		if (choice == ThemeChoice::Dark) {
			wxColor newBackground(wxColor(0, 0, 25));
			wxColor newForeground(wxColor(*wxWHITE));
			backGroundColor = newBackground;
			foreGroundColor = newForeground;			//included a dark mode for all my dark mode users out there
			themeChoice = ThemeChoice::Dark;
		}
		else {
			wxColor newBackground(wxColor(174, 198, 207));
			wxColor newForeground(wxColor(*wxBLACK));
			backGroundColor = newBackground;
			foreGroundColor = newForeground;
		}
	}
	~Theme() {
	}
};

class MainWindow :
    public wxFrame
{
private:	
	Character* pCurrentCharacter = nullptr; //the character

	wxMenuBar* pMenuBar = nullptr;		//menu bar and menus
	wxMenu* pFileMenu = nullptr;
	wxMenu* pViewMenu = nullptr;

	wxMenuItem* pLightTheme = nullptr;	//menu items
	wxMenuItem* pDarkTheme = nullptr;

	wxBoxSizer* pMainSizer = nullptr;			//sizers
	wxBoxSizer* pNameTextSizer = nullptr;
	wxBoxSizer* pScoreSizer = nullptr;
	wxBoxSizer* pScoreInputLabelSizer = nullptr;
	wxBoxSizer* pScoreInputVertSizer = nullptr;
	wxBoxSizer* pScoreInputHorSizer = nullptr;


	wxTextCtrl* pNameTextBox = nullptr;		//text ctrls

	wxSpinCtrl* strSpin = nullptr;
	wxSpinCtrl* dexSpin = nullptr;
	wxSpinCtrl* conSpin = nullptr;
	wxSpinCtrl* intelSpin = nullptr;
	wxSpinCtrl*	wisSpin = nullptr;
	wxSpinCtrl*	chaSpin = nullptr;
	wxSpinCtrl* lvlSpin = nullptr;

	wxStaticText* nameLabel = nullptr; //text
	wxStaticText* classComboBoxLabel = nullptr;
	wxStaticText* lvlText = nullptr;
	wxStaticText* score1 = nullptr;
	wxStaticText* score2 = nullptr;
	wxStaticText* score3 = nullptr;
	wxStaticText* score4 = nullptr;
	wxStaticText* score5 = nullptr;
	wxStaticText* score6 = nullptr;
	
	wxStaticText* strText = nullptr;
	wxStaticText* dexText = nullptr;
	wxStaticText* conText = nullptr;
	wxStaticText* intelText = nullptr;
	wxStaticText* wisText = nullptr;
	wxStaticText* chaText = nullptr;
	
	//class pulldown tab
	wxComboBox* classComboBox = nullptr;


	Settings mSettings;				//settings

	Theme mCurrentTheme;			//theme
	wxMessageDialog* numberOverflowErrorMessage = nullptr;
	//error windows
	wxMessageDialog* classSelectErrorMessage = nullptr;

public:
	MainWindow();

	~MainWindow();
	
	//events
	void OnNameEnter(wxCommandEvent& event);

	void OnClassSelect(wxCommandEvent& event);

	void OnLightThemeClickie(wxCommandEvent& event);

	void OnDarkThemeClickie(wxCommandEvent& event);

	void onSpinCtrlEvent(wxSpinEvent& event);

	

	void SaveSettings() {	//Save settings
		std::ofstream fileOut("settings.bin", ios::binary);
		if (fileOut.is_open())
			fileOut.write((char*)&mSettings, sizeof(Settings));
		fileOut.close();
	}

	void LoadSettings() {	//load settings
		std::ifstream fileIn("settings.bin", ios::binary);
		if (fileIn.is_open())
			fileIn.read((char*)&mSettings, sizeof(Settings));
		fileIn.close();
	}

	wxDECLARE_EVENT_TABLE();
};

