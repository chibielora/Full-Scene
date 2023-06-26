#include <iostream>
#include <application.h>

int main(int argc, char** argv) {
	Application app{ "CS33-ShowcaseApp", 800, 600 };
	
	app.Run();

	return 0;
}