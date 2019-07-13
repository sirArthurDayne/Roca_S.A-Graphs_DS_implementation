#define OLC_PGE_APPLICATION
#include"olcPixelGameEngine.h"
#include"ScreenSetUP.h"
#include"GraphsProyect.h"

int main()
{
	//AKS FOR DIMENSIONS
	ScreenSetUP setupPGE;
	if (setup && setupPGE.Construct(300, 150, 2, 2))
		setupPGE.Start();

	//CONSTRUCT AND RUN MAIN APP
	GraphsProyect app;
	if (!setup && app.Construct(screenW, screenH, 2, 2, fullScreen))
		app.Start();


	return 0;
}