#include "MainWindow.h"
#include "TheDiceBag.h"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
	EVT_TEXT(TextBoxes::CharacterName, MainWindow::OnNameEnter)
	EVT_MENU(MenuItemIDs::LightTheme, MainWindow::OnLightThemeClickie)
	EVT_MENU(MenuItemIDs::DarkTheme, MainWindow::OnDarkThemeClickie)
	EVT_SPINCTRL(SpinCtrlIDs::STR, MainWindow::onSpinCtrlEvent)
	EVT_SPINCTRL(SpinCtrlIDs::DEX, MainWindow::onSpinCtrlEvent)
	EVT_SPINCTRL(SpinCtrlIDs::CON, MainWindow::onSpinCtrlEvent)
	EVT_SPINCTRL(SpinCtrlIDs::INTEL, MainWindow::onSpinCtrlEvent)
	EVT_SPINCTRL(SpinCtrlIDs::WIS, MainWindow::onSpinCtrlEvent)
	EVT_SPINCTRL(SpinCtrlIDs::CHA, MainWindow::onSpinCtrlEvent)
wxEND_EVENT_TABLE()

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "NPC", wxPoint(100, 100), wxSize(1000, 1000))
{
	LoadSettings();
	if (mSettings.currentThemeChoice == ThemeChoice::Light) {
		Theme newTheme;
		mCurrentTheme = newTheme;
	}
	else {
		Theme newTheme(ThemeChoice::Dark);
		mCurrentTheme = newTheme;
	}
	pMenuBar = new wxMenuBar;		//menu bar and menus
	
	pFileMenu = new wxMenu;
	pMenuBar->Append(pFileMenu, "File");
	pViewMenu = new wxMenu;
	pMenuBar->Append(pViewMenu, "View");

	

	pLightTheme = new wxMenuItem(pViewMenu, MenuItemIDs::LightTheme, "Light Theme", "Sets the program to light theme");
	pLightTheme->SetCheckable(true);
	pViewMenu->Append(pLightTheme);				//theme menuoptions

	pDarkTheme = new wxMenuItem(pViewMenu, MenuItemIDs::DarkTheme, "Dark Theme", "Sets the program to dark theme");
	pDarkTheme->SetCheckable(true);
	pViewMenu->Append(pDarkTheme);

	if (mCurrentTheme.themeChoice == Dark) {
		pDarkTheme->Check();
	}
	else{
		pLightTheme->Check();
	}

	pMainSizer = new wxBoxSizer(wxVERTICAL);	//Sizer Definitions
	pNameTextSizer = new wxBoxSizer(wxHORIZONTAL);
	pScoreSizer = new wxBoxSizer(wxHORIZONTAL);
	pScoreInputVert1 = new wxBoxSizer(wxVERTICAL);
	pScoreInputVert2 = new wxBoxSizer(wxVERTICAL);
	pScorInputHor = new wxBoxSizer(wxHORIZONTAL);

	pMainSizer->AddSpacer(20);
	pMainSizer->Add(pNameTextSizer);
	pMainSizer->AddSpacer(20);
	pMainSizer->Add(pScoreSizer);
	pMainSizer->AddSpacer(20);
	pMainSizer->Add(pScorInputHor);
	pScorInputHor->AddSpacer(20);
	pScorInputHor->Add(pScoreInputVert1);
	pScorInputHor->AddSpacer(40);
	pScorInputHor->Add(pScoreInputVert2);

	nameLabel = new wxStaticText(this, wxID_ANY, "Character Name");
	pNameTextSizer->AddSpacer(20);
	nameLabel->SetMinSize(wxSize(150, 25));
	pNameTextSizer->Add(nameLabel);

	pNameTextBox = new wxTextCtrl(this, TextBoxes::CharacterName);
	pNameTextBox->SetMinSize(wxSize(150, 25));
	pNameTextSizer->Add(pNameTextBox);
													
	vector<int> scoreVec = Dice::RollAS();		//Roll Ability scores

	score1 = new wxStaticText(this, wxID_ANY, std::to_string(scoreVec[0]));
	score2 = new wxStaticText(this, wxID_ANY, std::to_string(scoreVec[1]));
	score3 = new wxStaticText(this, wxID_ANY, std::to_string(scoreVec[2]));
	score4 = new wxStaticText(this, wxID_ANY, std::to_string(scoreVec[3]));
	score5 = new wxStaticText(this, wxID_ANY, std::to_string(scoreVec[4]));
	score6 = new wxStaticText(this, wxID_ANY, std::to_string(scoreVec[5]));

	strText  = new wxStaticText(this, wxID_ANY, "STR");
	dexText	 = new wxStaticText(this, wxID_ANY, "DEX");
	conText	 = new wxStaticText(this, wxID_ANY, "CON");
	intelText = new wxStaticText(this, wxID_ANY, "INT");
	wisText	 = new wxStaticText(this, wxID_ANY, "WIS");
	chaText	 = new wxStaticText(this, wxID_ANY, "CHA");

	strSpin = new wxSpinCtrl(this, SpinCtrlIDs::STR, "10");
	dexSpin = new wxSpinCtrl(this, SpinCtrlIDs::DEX, "10");
	conSpin = new wxSpinCtrl(this, SpinCtrlIDs::CON, "10");
	intelSpin = new wxSpinCtrl(this, SpinCtrlIDs::INTEL, "10");
	wisSpin = new wxSpinCtrl(this, SpinCtrlIDs::WIS, "10");
	chaSpin = new wxSpinCtrl(this, SpinCtrlIDs::CHA, "10");

	
	nameLabel->SetForegroundColour(mCurrentTheme.foreGroundColor);		//text colors
	score1->SetForegroundColour(mCurrentTheme.foreGroundColor);
	score2->SetForegroundColour(mCurrentTheme.foreGroundColor);
	score3->SetForegroundColour(mCurrentTheme.foreGroundColor);
	score4->SetForegroundColour(mCurrentTheme.foreGroundColor);
	score5->SetForegroundColour(mCurrentTheme.foreGroundColor);
	score6->SetForegroundColour(mCurrentTheme.foreGroundColor);

	strText->SetForegroundColour(mCurrentTheme.foreGroundColor);
	dexText->SetForegroundColour(mCurrentTheme.foreGroundColor);
	conText->SetForegroundColour(mCurrentTheme.foreGroundColor);
	intelText->SetForegroundColour(mCurrentTheme.foreGroundColor);
	wisText->SetForegroundColour(mCurrentTheme.foreGroundColor);
	chaText->SetForegroundColour(mCurrentTheme.foreGroundColor);

	pScoreSizer->AddSpacer(20);
	pScoreSizer->Add(score1);
	pScoreSizer->AddSpacer(20);
	pScoreSizer->Add(score2);
	pScoreSizer->AddSpacer(20);
	pScoreSizer->Add(score3);
	pScoreSizer->AddSpacer(20);
	pScoreSizer->Add(score4);
	pScoreSizer->AddSpacer(20);
	pScoreSizer->Add(score5);
	pScoreSizer->AddSpacer(20);
	pScoreSizer->Add(score6);



	pScoreInputVert1->AddSpacer(20);
	pScoreInputVert1->Add(strText);
	pScoreInputVert1->AddSpacer(20);
	pScoreInputVert1->Add(dexText);
	pScoreInputVert1->AddSpacer(20);
	pScoreInputVert1->Add(conText);
	pScoreInputVert1->AddSpacer(30); //had to be set to 30 for display purposes
	pScoreInputVert1->Add(intelText);
	pScoreInputVert1->AddSpacer(20);
	pScoreInputVert1->Add(wisText);
	pScoreInputVert1->AddSpacer(20);
	pScoreInputVert1->Add(chaText);

	pScoreInputVert2->AddSpacer(15);
	pScoreInputVert2->Add(strSpin);
	pScoreInputVert2->AddSpacer(15);
	pScoreInputVert2->Add(dexSpin);
	pScoreInputVert2->AddSpacer(15);
	pScoreInputVert2->Add(conSpin);
	pScoreInputVert2->AddSpacer(15);
	pScoreInputVert2->Add(intelSpin);
	pScoreInputVert2->AddSpacer(15);
	pScoreInputVert2->Add(wisSpin);
	pScoreInputVert2->AddSpacer(15);
	pScoreInputVert2->Add(chaSpin);

	SetForegroundColour(mCurrentTheme.foreGroundColor);				//background and foreground colors
	SetBackgroundColour(mCurrentTheme.backGroundColor);
	SetSizer(pMainSizer);
	SetMenuBar(pMenuBar);
}

MainWindow::~MainWindow()
{
	delete pCurrentCharacter;
}

void MainWindow::OnNameEnter(wxCommandEvent& event)
{
	pCurrentCharacter->Name(pNameTextBox->GetLineText(pNameTextBox->GetNumberOfLines()).ToStdString());
	pNameTextBox->SetModified(true);
}

void MainWindow::OnLightThemeClickie(wxCommandEvent& event)
{															//Light theme event
	if (pDarkTheme->IsChecked()) {
		pDarkTheme->Check(false);
	}
	mSettings.currentThemeChoice = ThemeChoice::Light;
	Theme newTheme;
	mCurrentTheme = newTheme;
	nameLabel->SetForegroundColour(mCurrentTheme.foreGroundColor);
	score1->SetForegroundColour(mCurrentTheme.foreGroundColor);
	score2->SetForegroundColour(mCurrentTheme.foreGroundColor);
	score3->SetForegroundColour(mCurrentTheme.foreGroundColor);
	score4->SetForegroundColour(mCurrentTheme.foreGroundColor);
	score5->SetForegroundColour(mCurrentTheme.foreGroundColor);
	score6->SetForegroundColour(mCurrentTheme.foreGroundColor);
	strText->SetForegroundColour(mCurrentTheme.foreGroundColor);
	dexText->SetForegroundColour(mCurrentTheme.foreGroundColor);
	conText->SetForegroundColour(mCurrentTheme.foreGroundColor);
	intelText->SetForegroundColour(mCurrentTheme.foreGroundColor);
	wisText->SetForegroundColour(mCurrentTheme.foreGroundColor);
	chaText->SetForegroundColour(mCurrentTheme.foreGroundColor);
	SetForegroundColour(mCurrentTheme.foreGroundColor);
	SetBackgroundColour(mCurrentTheme.backGroundColor);
	pMenuBar->Refresh();
	pMenuBar->Update();
	this->Refresh();
	this->Update();
	SaveSettings();
}

void MainWindow::OnDarkThemeClickie(wxCommandEvent& event)
{															//Dark theme event
	if (pLightTheme->IsChecked()) {
		pLightTheme->Check(false);
	}
	mSettings.currentThemeChoice = ThemeChoice::Dark;
	Theme newTheme(ThemeChoice::Dark);
	mCurrentTheme = newTheme;
	nameLabel->SetForegroundColour(mCurrentTheme.foreGroundColor);
	score1->SetForegroundColour(mCurrentTheme.foreGroundColor);
	score2->SetForegroundColour(mCurrentTheme.foreGroundColor);
	score3->SetForegroundColour(mCurrentTheme.foreGroundColor);
	score4->SetForegroundColour(mCurrentTheme.foreGroundColor);
	score5->SetForegroundColour(mCurrentTheme.foreGroundColor);
	score6->SetForegroundColour(mCurrentTheme.foreGroundColor);
	strText->SetForegroundColour(mCurrentTheme.foreGroundColor);
	dexText->SetForegroundColour(mCurrentTheme.foreGroundColor);
	conText->SetForegroundColour(mCurrentTheme.foreGroundColor);
	intelText->SetForegroundColour(mCurrentTheme.foreGroundColor);
	wisText->SetForegroundColour(mCurrentTheme.foreGroundColor);
	chaText->SetForegroundColour(mCurrentTheme.foreGroundColor);
	SetForegroundColour(mCurrentTheme.foreGroundColor);
	SetBackgroundColour(mCurrentTheme.backGroundColor);
	pMenuBar->Refresh();
	pMenuBar->Update();
	this->Refresh();
	this->Update();
	SaveSettings();
}

void MainWindow::onSpinCtrlEvent(wxSpinEvent& event) {
	int ID = event.GetId();
	switch (ID) {
	case SpinCtrlIDs::STR:
		pCurrentCharacter->Str(strSpin->GetValue());
		break;
	case SpinCtrlIDs::DEX:
		pCurrentCharacter->Dex(dexSpin->GetValue());
		break;
	case SpinCtrlIDs::CON:
		pCurrentCharacter->Con(conSpin->GetValue());
		break;
	case SpinCtrlIDs::INTEL:
		pCurrentCharacter->Intel(intelSpin->GetValue());
		break;
	case SpinCtrlIDs::WIS:
		pCurrentCharacter->Wis(wisSpin->GetValue());
		break;
	case SpinCtrlIDs::CHA:
		pCurrentCharacter->Cha(chaSpin->GetValue());
		break;
	
	}
}

