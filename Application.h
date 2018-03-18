#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"
#include "Module.h"
#include "Dummy.h"
#include "DummyESC.h"
#include "QSS_module.h"

#define NUM_MODULES 3

class Application
{
public:

	Module* modules[NUM_MODULES];

public:

	Application()
	{
		modules[0] = new ModuleDummy();
		modules[1] = new ModuleDummyESC();
		modules[2] = new QSS_module();
		// TODO 7: Create your new module "DummyESC"
		// it should check if player it ESC key use kbhit()
		// http://www.cprogramming.com/fod/kbhit.html
	}
	~Application()
	{
		for (int i = NUM_MODULES - 1; i >= 0; --i)
		{
			delete modules[i];
		}
	}

	// INIT all modules
	bool Init() 
	{
		for (int i = 0; i < NUM_MODULES; ++i)
		{
			//modules[i]->Init();
			if (modules[i]->Init() == false)
			{
				LOG("\nApp Init error");
				return false;
			}
		}
		
	

		// TODO 5: Make sure that if Init() / PreUpdate/Update/PostUpdate/CleanUP return
		// an exit code App exits correctly.

		return true; 
	}

	// TODO 4: Add PreUpdate and PostUpdate calls
	
	// UPDATE all modules
	// TODO 2: Make sure all modules receive its update
	update_status Update() {

		for (int i = 0; i < NUM_MODULES; ++i) ////////////PreUpdate
		{
			//modules[i]->PreUpdate();
			if (modules[i]->PreUpdate() == UPDATE_STOP) return update_status::UPDATE_STOP;

		}
		for (int i = 0; i < NUM_MODULES; ++i) ///////////Update
		{
		
			//modules[i]->Update();
			if (modules[i]->Update() == UPDATE_STOP) return update_status::UPDATE_STOP;
		}
		for (int i = 0; i < NUM_MODULES; ++i) ////////////PostUpdate
		{
			//modules[i]->PostUpdate();
			if (modules[i]->PostUpdate() == UPDATE_STOP) return update_status::UPDATE_STOP;

		}

		return update_status::UPDATE_CONTINUE;
	}

	// EXIT Update 


	// TODO 3: Make sure all modules have a chance to cleanup
	bool CleanUp()
	{
		
		for (int i = NUM_MODULES - 1; i >= 0; --i) //inverse order than creation
		{
			if (modules[i]->CleanUp() == false) return false;
			//LOG("CleanUp Failed");
			
		}
		LOG("\nCleanUp complete");
		return true;
	}

};

#endif // __APPLICATION_H__