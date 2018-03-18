#include "Application.h"
#include "Globals.h"
#include "MemLeaks.h"

enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

int main(int argc, char* argv[])
{
	ReportMemoryLeaks();

	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;
	Application* App = nullptr;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
			case MAIN_CREATION:
			{
				LOG("\nApplication Creation --------------");
				App = new Application();
				state = MAIN_START;
			}	break;

			case MAIN_START:
			{
				LOG("\nApplication Start --------------");
				if(App->Init() == false)
				{
					LOG("\nApplication Init exits with error -----");
					state = MAIN_EXIT;
				}
				else
					state = MAIN_UPDATE;

			}	break;

			case MAIN_UPDATE:
			{
				update_status status = App->Update();

				if (status == update_status::UPDATE_ERROR)
				{
					LOG("\nApplication Update exits with error -----");
					state = MAIN_EXIT;
				}
				else if (status == update_status::UPDATE_STOP)
					state = MAIN_FINISH;

			} break;

			// TODO 1: Implement case MAIN_FINISH
			// Remember to quit the game with EXIT_SUCCESS
			// if everything went well :)

			case MAIN_FINISH:
			{
				//App->CleanUp();
				LOG("\nApplication modules cleanUp----------");

				if (App->CleanUp() == false)
				{
					LOG("\nApplication cleanUp exit with errors");
					//state = MAIN_EXIT;
					//return EXIT_FAILURE;
				}
				else
				{
					LOG("\nApplication cleanUp exits success---------");
					//state = MAIN_EXIT;
					main_return = EXIT_SUCCESS;
				}
				state = MAIN_EXIT;
			} break;
		}
	}
	
	//App->~Application();
	delete(App);
	LOG("\nBye :)\n");
	// TODO 6: Remove ALL memory leaks
	return main_return;
}