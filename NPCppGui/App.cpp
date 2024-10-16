#include "App.h"
#include "MainWindow.h"

wxIMPLEMENT_APP(App);

App::App() {

}

App::~App() {

}

bool App::OnInit() {
	_CrtSetBreakAlloc(-1); // DO NOT COMMENT OUT THIS LINE SET TO 
	MainWindow* window = new MainWindow();
	window->Show();
	return true;
}