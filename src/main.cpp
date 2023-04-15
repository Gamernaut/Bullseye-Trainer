///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	Dec 2022
//
//	Purpose:    Main entry point for program
// 
// Coding Style:    Google C++ -> https://google.github.io/styleguide/cppguide.html
//
///////////////////////////////////////////////////////////////////////////////////////////////////////


// Include 3rd party code
#include <plog/Log.h>
#include "plog/Initializers/RollingFileInitializer.h"



// Add C runtime library (CRT) support for memory leak checking
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

// Include my code
#include "constants.h"
#include "bulls_trainer.h"

using namespace cpv;

int main(int argc, char* argv[]) {

	// Set automatic call to CRT memory debug at any exit point
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	// Create a logger and set logging level using plog -> https://github.com/SergiusTheBest/plog
	// Can also programmatically set the logging level with:	 plog::get()->setMaxSeverity(plog::warning);
	
	plog::init(plog::debug, kLogPath, 1000000, 5);
	PLOG_NONE << "Logger started";

	// Create application on the stack and start
	Bulls_Trainer trainer;

	// TODO: Better yet, use a smart pointer, but need a custom destructor to make this work
	//Bulls_Trainer trainerSmtPtr = std::make_unique<Bulls_Trainer>();
	if (trainer.Initialise()) {
		PLOG_INFO << "trainer.Initialise completed successfully";
		trainer.Run();
		trainer.CloseDown();
	}
	else {
		PLOG_ERROR << "trainer.Initialise() failed";
		trainer.CloseDown();
	};


	// Write out CRT memory leaks
	//_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);		// Set output window to debug window
	//_CrtDumpMemoryLeaks();									// Dump the report

	return 0;
}