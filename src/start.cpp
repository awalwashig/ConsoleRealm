﻿#include "Application.h"

int main(int argc, char** argv) {
	auto App = Realm::Application::CreateApplication();

	App->Init();

	App->Run();

	App->Quit();
}