#include "MainWindow.h"
#include "wx/msgdlg.h"
#include "TheDiceBag.h"
#include "Artificer.h"
#include "Barbarian.h"
#include "Bard.h"
#include "Cleric.h"
#include "Druid.h"
#include "Fighter.h"
#include "Monk.h"
#include "Paladin.h"
#include "Ranger.h"
#include "Rogue.h"
#include "Sorcerer.h"
#include "Warlock.h"
#include "Wizard.h"

//event table
wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
	EVT_TEXT(TextBoxes::CharacterName, MainWindow::OnNameEnter)
	EVT_MENU(MenuItemIDs::LightTheme, MainWindow::OnLightThemeClickie)
	EVT_MENU(MenuItemIDs::DarkTheme, MainWindow::OnDarkThemeClickie)
	EVT_SPINCTRL(ElementIDs::STR, MainWindow::onSpinCtrlEvent)
	EVT_SPINCTRL(ElementIDs::DEX, MainWindow::onSpinCtrlEvent)
	EVT_SPINCTRL(ElementIDs::CON, MainWindow::onSpinCtrlEvent)
	EVT_SPINCTRL(ElementIDs::INTEL, MainWindow::onSpinCtrlEvent)
	EVT_SPINCTRL(ElementIDs::WIS, MainWindow::onSpinCtrlEvent)
	EVT_SPINCTRL(ElementIDs::CHA, MainWindow::onSpinCtrlEvent)
	EVT_COMBOBOX(ElementIDs::ClassComboBox, MainWindow::OnClassSelect)
wxEND_EVENT_TABLE()

//constructor
MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "NPC", wxPoint(100, 100), wxSize(1000, 1000))
{
	pCurrentCharacter = new Character();
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
	pScoreInputLabelSizer = new wxBoxSizer(wxVERTICAL);
	pScoreInputVertSizer = new wxBoxSizer(wxVERTICAL);
	pScoreInputHorSizer = new wxBoxSizer(wxHORIZONTAL);

	pMainSizer->AddSpacer(20);				//add sizers to main sizer
	pMainSizer->Add(pNameTextSizer);			
	pMainSizer->AddSpacer(20);
	pMainSizer->Add(pScoreSizer);
	pMainSizer->AddSpacer(20);
	pMainSizer->Add(pScoreInputHorSizer);

	pScoreInputHorSizer->AddSpacer(20);		//add vertical sizers to
	pScoreInputHorSizer->Add(pScoreInputLabelSizer); //score input sizer horizontal
	pScoreInputHorSizer->AddSpacer(40);
	pScoreInputHorSizer->Add(pScoreInputVertSizer);

	nameLabel = new wxStaticText(this, wxID_ANY, "Character Name");		
	pNameTextSizer->AddSpacer(20);
	nameLabel->SetMinSize(wxSize(150, 25));
	pNameTextSizer->Add(nameLabel);		

	pNameTextBox = new wxTextCtrl(this, TextBoxes::CharacterName);
	pNameTextBox->SetMinSize(wxSize(150, 25));
	pNameTextSizer->Add(pNameTextBox);


	classComboBoxLabel = new wxStaticText(this, wxID_ANY, "Class");
	classComboBoxLabel->SetMinSize(wxSize(50, 25));
	pNameTextSizer->AddSpacer(40);
	pNameTextSizer->Add(classComboBoxLabel);
	classComboBox = new wxComboBox(this, ElementIDs::ClassComboBox, wxString("Commoner"), wxPoint(0, 0), wxSize(100, 23), wxArrayString(), wxCB_READONLY);
	classComboBox->Set({ "Commoner", "Artificer", "Barbarian", "Bard", "Cleric", "Druid", "Fighter", "Monk",
						 "Paladin", "Ranger", "Rogue", "Sorcerer", "Warlock", "Wizard" });
	classComboBox->SetSelection(0);
	pNameTextSizer->AddSpacer(20);
	pNameTextSizer->Add(classComboBox);

	lvlText = new wxStaticText(this, wxID_ANY, "Level");
	lvlText->SetMinSize(wxSize(50, 25));
	pNameTextSizer->AddSpacer(40);
	pNameTextSizer->Add(lvlText);
	lvlSpin = new wxSpinCtrl(this, ElementIDs::LVL, "1", wxDefaultPosition, wxSize(50, 23));
	lvlSpin->SetRange(1, 20);
	pNameTextSizer->AddSpacer(20);
	pNameTextSizer->Add(lvlSpin);
													
	vector<int> scoreVec = Dice::RollAS();		//Roll Ability scores

	//define score labels
	score1 = new wxStaticText(this, wxID_ANY, std::to_string(scoreVec[0]));
	score2 = new wxStaticText(this, wxID_ANY, std::to_string(scoreVec[1]));
	score3 = new wxStaticText(this, wxID_ANY, std::to_string(scoreVec[2]));
	score4 = new wxStaticText(this, wxID_ANY, std::to_string(scoreVec[3]));
	score5 = new wxStaticText(this, wxID_ANY, std::to_string(scoreVec[4]));
	score6 = new wxStaticText(this, wxID_ANY, std::to_string(scoreVec[5]));
	//text for labels
	strText  = new wxStaticText(this, wxID_ANY, "STR");
	dexText	 = new wxStaticText(this, wxID_ANY, "DEX");
	conText	 = new wxStaticText(this, wxID_ANY, "CON");
	intelText = new wxStaticText(this, wxID_ANY, "INT");
	wisText	 = new wxStaticText(this, wxID_ANY, "WIS");
	chaText	 = new wxStaticText(this, wxID_ANY, "CHA");
	//spin controls for score entry
	strSpin = new wxSpinCtrl(this, ElementIDs::STR, "10", wxDefaultPosition, wxSize(50, 23));
	strSpin->SetRange(8, 20);		//min and max for spin ctrls
	dexSpin = new wxSpinCtrl(this, ElementIDs::DEX, "10", wxDefaultPosition, wxSize(50, 23));
	dexSpin->SetRange(8, 20);
	conSpin = new wxSpinCtrl(this, ElementIDs::CON, "10", wxDefaultPosition, wxSize(50, 23));
	conSpin->SetRange(8, 20);
	intelSpin = new wxSpinCtrl(this, ElementIDs::INTEL, "10", wxDefaultPosition, wxSize(50, 23));
	intelSpin->SetRange(8, 20);
	wisSpin = new wxSpinCtrl(this, ElementIDs::WIS, "10", wxDefaultPosition, wxSize(50, 23));
	wisSpin->SetRange(8, 20);
	chaSpin = new wxSpinCtrl(this, ElementIDs::CHA, "10", wxDefaultPosition, wxSize(50, 23));
	chaSpin->SetRange(8, 20);
	

	
	
	nameLabel->SetForegroundColour(mCurrentTheme.foreGroundColor);		//text colors
	classComboBoxLabel->SetForegroundColour(mCurrentTheme.foreGroundColor);
	lvlText->SetForegroundColour(mCurrentTheme.foreGroundColor);
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

	//add scores to sizer
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

	//add labels to score input sizer
	pScoreInputLabelSizer->AddSpacer(20);
	pScoreInputLabelSizer->Add(strText);		
	pScoreInputLabelSizer->AddSpacer(20);
	pScoreInputLabelSizer->Add(dexText);
	pScoreInputLabelSizer->AddSpacer(20);
	pScoreInputLabelSizer->Add(conText);
	pScoreInputLabelSizer->AddSpacer(30); //had to be set to 30 for display purposes
	pScoreInputLabelSizer->Add(intelText);
	pScoreInputLabelSizer->AddSpacer(20);
	pScoreInputLabelSizer->Add(wisText);
	pScoreInputLabelSizer->AddSpacer(20);
	pScoreInputLabelSizer->Add(chaText);

	//add spin controls to score input sizer
	pScoreInputVertSizer->AddSpacer(15);
	pScoreInputVertSizer->Add(strSpin);
	pScoreInputVertSizer->AddSpacer(15);
	pScoreInputVertSizer->Add(dexSpin);
	pScoreInputVertSizer->AddSpacer(15);
	pScoreInputVertSizer->Add(conSpin);
	pScoreInputVertSizer->AddSpacer(15);
	pScoreInputVertSizer->Add(intelSpin);
	pScoreInputVertSizer->AddSpacer(15);
	pScoreInputVertSizer->Add(wisSpin);
	pScoreInputVertSizer->AddSpacer(15);
	pScoreInputVertSizer->Add(chaSpin);

	SetForegroundColour(mCurrentTheme.foreGroundColor);				//background and foreground colors
	SetBackgroundColour(mCurrentTheme.backGroundColor);
	SetSizer(pMainSizer);
	SetMenuBar(pMenuBar);

	//errors
	classSelectErrorMessage = new wxMessageDialog(this, "Somehow you selected an option that we weren't prepared for!\nPlease debug the Source", "Error", wxOK | wxICON_ERROR);
	numberOverflowErrorMessage = new wxMessageDialog(this, "That number is invalid Please try again", "Error", wxOK | wxICON_ERROR);
}


//destructor
MainWindow::~MainWindow()
{
	delete pCurrentCharacter;
}

void MainWindow::OnNameEnter(wxCommandEvent& event)
{
	pCurrentCharacter->Name(pNameTextBox->GetLineText(pNameTextBox->GetNumberOfLines()).ToStdString());
	pNameTextBox->SetModified(true);
}

void MainWindow::OnClassSelect(wxCommandEvent& event)
{
	std::string currentValue = classComboBox->GetValue().ToStdString();
	int commonerComp = _stricmp("Commoner", currentValue.c_str());
	int artiComp = _stricmp("Artificer", currentValue.c_str());
	int barbComp = _stricmp("barbarian", currentValue.c_str());
	int bardComp = _stricmp("bard", currentValue.c_str());
	int clericComp = _stricmp("cleric", currentValue.c_str());
	int druidComp = _stricmp("druid", currentValue.c_str());
	int fightComp = _stricmp("fighter", currentValue.c_str());
	int monkComp = _stricmp("monk", currentValue.c_str());
	int palComp = _stricmp("paladin", currentValue.c_str());
	int rangComp = _stricmp("ranger", currentValue.c_str());
	int rogComp = _stricmp("rogue", currentValue.c_str());
	int sorcComp = _stricmp("Sorcerer", currentValue.c_str());
	int warComp = _stricmp("warlock", currentValue.c_str());
	int wizComp = _stricmp("wizard", currentValue.c_str());

	if (commonerComp == 0) {
		pCurrentCharacter = new Character(strSpin->GetValue(),
										  dexSpin->GetValue(),
										  conSpin->GetValue(),
										  intelSpin->GetValue(),
										  wisSpin->GetValue(),
										  chaSpin->GetValue(),
										  1, 4,
										  pNameTextBox->GetValue().ToStdString());
	}
	else if (artiComp == 0) {
		pCurrentCharacter = new Artificer(strSpin->GetValue(),
										  dexSpin->GetValue(),
										  conSpin->GetValue(),
										  intelSpin->GetValue(),
										  wisSpin->GetValue(),
										  chaSpin->GetValue(),
										  1, 4,
										  pNameTextBox->GetValue().ToStdString());
	}
	else if (barbComp == 0) {
		pCurrentCharacter =  new Barbarian(strSpin->GetValue(),
											dexSpin->GetValue(),
											conSpin->GetValue(),
											intelSpin->GetValue(),
											wisSpin->GetValue(),
											chaSpin->GetValue(),
											1, 4,
											pNameTextBox->GetValue().ToStdString());
	}
	else if (bardComp == 0) {
		pCurrentCharacter = new Bard(strSpin->GetValue(),
									 dexSpin->GetValue(),
									 conSpin->GetValue(),
									 intelSpin->GetValue(),
									 wisSpin->GetValue(),
									 chaSpin->GetValue(),
									 1, 4,
									 pNameTextBox->GetValue().ToStdString());
	}
	else if (clericComp == 0) {
		pCurrentCharacter = new Cleric(strSpin->GetValue(),
									 dexSpin->GetValue(),
									 conSpin->GetValue(),
									 intelSpin->GetValue(),
									 wisSpin->GetValue(),
									 chaSpin->GetValue(),
									 1, 4,
									 pNameTextBox->GetValue().ToStdString());
	}
	else if (druidComp == 0) {
		pCurrentCharacter = new Druid(strSpin->GetValue(),
									 dexSpin->GetValue(),
									 conSpin->GetValue(),
									 intelSpin->GetValue(),
									 wisSpin->GetValue(),
									 chaSpin->GetValue(),
									 1, 4,
									 pNameTextBox->GetValue().ToStdString());
	}
	else if (fightComp == 0) {
		pCurrentCharacter = new Fighter(strSpin->GetValue(),
									  dexSpin->GetValue(),
									  conSpin->GetValue(),
									  intelSpin->GetValue(),
									  wisSpin->GetValue(),
									  chaSpin->GetValue(),
									  1, 4,
									  pNameTextBox->GetValue().ToStdString());
	}
	else if (monkComp == 0) {
		pCurrentCharacter = new Monk(strSpin->GetValue(),
									 dexSpin->GetValue(),
									 conSpin->GetValue(),
									 intelSpin->GetValue(),
									 wisSpin->GetValue(),
									 chaSpin->GetValue(),
									 1, 4,
									 pNameTextBox->GetValue().ToStdString());
	}
	else if (palComp == 0) {
		pCurrentCharacter = new Paladin(strSpin->GetValue(),
										dexSpin->GetValue(),
										conSpin->GetValue(),
										intelSpin->GetValue(),
										wisSpin->GetValue(),
										chaSpin->GetValue(),
										1, 4,
										pNameTextBox->GetValue().ToStdString());
	}
	else if (rangComp == 0) {
		pCurrentCharacter = new Ranger(strSpin->GetValue(),
									   dexSpin->GetValue(),
									   conSpin->GetValue(),
									   intelSpin->GetValue(),
									   wisSpin->GetValue(),
									   chaSpin->GetValue(),
									   1, 4,
									   pNameTextBox->GetValue().ToStdString());
	}
	else if (rogComp == 0) {
		pCurrentCharacter = new Rogue(strSpin->GetValue(),
									  dexSpin->GetValue(),
									  conSpin->GetValue(),
									  intelSpin->GetValue(),
									  wisSpin->GetValue(),
									  chaSpin->GetValue(),
									  1, 4,
									  pNameTextBox->GetValue().ToStdString());
	}
	else if (sorcComp == 0) {
		pCurrentCharacter = new Sorcerer(strSpin->GetValue(),
										 dexSpin->GetValue(),
										 conSpin->GetValue(),
										 intelSpin->GetValue(),
										 wisSpin->GetValue(),
										 chaSpin->GetValue(),
										 1, 4,
										 pNameTextBox->GetValue().ToStdString());
	}
	else if (warComp == 0) {
		pCurrentCharacter = new Warlock(strSpin->GetValue(),
										dexSpin->GetValue(),
										conSpin->GetValue(),
										intelSpin->GetValue(),
										wisSpin->GetValue(),
										chaSpin->GetValue(),
										1, 4,
										pNameTextBox->GetValue().ToStdString());
	}
	else if (wizComp == 0) {
		pCurrentCharacter = new Wizard(strSpin->GetValue(),
									   dexSpin->GetValue(),
									   conSpin->GetValue(),
									   intelSpin->GetValue(),
									   wisSpin->GetValue(),
									   chaSpin->GetValue(),
									   1, 4,
									   pNameTextBox->GetValue().ToStdString());
	}
	else {
		int result = classSelectErrorMessage->ShowModal();
		if (result == wxID_OK) {
			pCurrentCharacter = new Character(strSpin->GetValue(),
											  dexSpin->GetValue(),
											  conSpin->GetValue(),
											  intelSpin->GetValue(),
											  wisSpin->GetValue(),
											  chaSpin->GetValue(),
											  1, 4,
											  pNameTextBox->GetValue().ToStdString());
		}
		else {
			this->Close();
		}

	}
	

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
	classComboBoxLabel->SetForegroundColour(mCurrentTheme.foreGroundColor);
	lvlText->SetForegroundColour(mCurrentTheme.foreGroundColor);
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
	classComboBoxLabel->SetForegroundColour(mCurrentTheme.foreGroundColor);
	lvlText->SetForegroundColour(mCurrentTheme.foreGroundColor);
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
	case ElementIDs::STR:
		pCurrentCharacter->Str(strSpin->GetValue());
		break;
	case ElementIDs::DEX:
		pCurrentCharacter->Dex(dexSpin->GetValue());
		break;
	case ElementIDs::CON:
		pCurrentCharacter->Con(conSpin->GetValue());
		break;
	case ElementIDs::INTEL:
		pCurrentCharacter->Intel(intelSpin->GetValue());
		break;
	case ElementIDs::WIS:
		pCurrentCharacter->Wis(wisSpin->GetValue());
		break;
	case ElementIDs::CHA:
		pCurrentCharacter->Cha(chaSpin->GetValue());
		break;
	}
}

