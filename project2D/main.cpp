#include "Application2D.h"

int main() {
	
	// allocation
	auto app = new Application2D();

	// initialise and loop
#ifdef _DEBUG
	app->run("AIE", 1920, 1080, false);
#else
	app->run("AIE", 1920, 1080, true);
#endif


	// deallocation
	delete app;

	return 0;
}