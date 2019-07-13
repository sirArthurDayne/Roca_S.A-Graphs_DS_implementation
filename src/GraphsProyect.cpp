#include "GraphsProyect.h"

GraphsProyect::GraphsProyect()
{
	sAppName = "Proyecto3 Aerolinea";
	state = PRESENTATION;
}

bool GraphsProyect::OnUserCreate()
{
	SetUpVertices();
	mainMenuOption = 1;
	return true;
}

bool GraphsProyect::OnUserUpdate(float deltaTime)
{
	
	if (state == PRESENTATION)
		DrawPresentation();
			
	if (state == MAIN_MENU)
		DrawMainMenu();
		
	if (state == TRIP_DISTANCE)
		DrawTripDistance();
	if (state == TRIP_COST)
		DrawTripCost();
	if (state == TRIP_TIME)
		DrawTripTime();
	if (state == GRAPH_VISUAL)
		 DrawGraphVisual();


	if (GetKey(olc::ESCAPE).bPressed)
		return false;

	return true;
}

void GraphsProyect::SetUpVertices()
{
	//init the vertex
	//each vertex represent a location
	Vertex   cocle("Cocle", 0),
		veraguas("Veraguas", 1),
		losSantos("LosSantos", 2),
		chiriqui("Chiriqui", 3),
		panama("Panama", 4),
		colon("Colon", 5),
		bocas("BocasDelToro", 6),
		herrera("Herrera", 7);
	
	//add vertices into array, for future drawing a modify data
	locations[0] = cocle;
	locations[1] = veraguas;
	locations[2] = losSantos;
	locations[3] = chiriqui;
	locations[4] = panama;
	locations[5] = colon;
	locations[6] = bocas;
	locations[7] = herrera;
}

void GraphsProyect::SetupEdges()
{
	
}

void GraphsProyect::DrawPresentation()
{
	Clear(olc::BLACK);
	DrawString(ScreenWidth() / 2 - 90, 160, "DATA STRUCTURE PROYECT: GRAPHS");

	DrawString(ScreenWidth() / 2 - 80, 250, "DEVELOP BY: ");
	DrawString(ScreenWidth() / 2 - 100, 300, "LAMELA, XAVIER (SirArthurDayne)");
	//DrawString(ScreenWidth() / 2 - 100, 325, "HARBIN, CLYDE");
	//DrawString(ScreenWidth() / 2 - 100, 350, "CHAVEZ, LUIS");

	DrawString(ScreenWidth() / 2 - 120, ScreenHeight() - 50, "SPECIAL THANKS TO ZLEAPINGBEAR");
	DrawString(ScreenWidth() - 200, ScreenHeight() - 25, "'CLICK' TO CONTINUE...");

	if (GetMouse(0).bPressed)
		state = MAIN_MENU;
}

void GraphsProyect::DrawMainMenu()
{
	
	int textX1 = ScreenWidth() / 2 - 100;
	int textY1 = 100;

	//INPUT
	if (GetMouse(0).bReleased)
	{
		int mouseX = GetMouseX();
		int mouseY = GetMouseY();

		if (mouseX > textX1 && mouseX < textX1 + 200 && mouseY > textY1 && mouseY < textY1 + 20)
			state = TRIP_DISTANCE;

		else if (mouseX > textX1 && mouseX < textX1 + 200 && mouseY > textY1 + 40 && mouseY < (textY1 +40) + 20)
			state = TRIP_COST;
		
		else if (mouseX > textX1 && mouseX < textX1 + 200 && mouseY > textY1 + 80 && mouseY < (textY1 +80) + 20)
			state = TRIP_TIME;
		
		else if (mouseX > textX1 && mouseX < textX1 + 200 && mouseY > textY1 + 120 && mouseY < (textY1 +120)+ 20)
			state = GRAPH_VISUAL;

	}


	Clear(olc::BLACK);
	DrawString(ScreenWidth() / 2 - 50, 20, "MAIN MENU");
	FillRect(textX1,textY1, textX1 + 100, 20, olc::DARK_RED);
	DrawString(textX1, textY1, "1. SEE TRIP DISTANCE (KM)");

	FillRect(textX1, textY1 + 40, textX1 + 100, 20 , olc::DARK_GREEN);
	DrawString(textX1, textY1 + 40, "2. SEE COST OF TRAVEL ($)");

	FillRect(textX1, textY1 + 80, textX1 + 100, 20, olc::DARK_BLUE);
	DrawString(textX1, textY1 + 80, "3. SEE TIME OF TRAVEL (min)");

	FillRect(textX1, textY1 + 120, textX1 + 100, 20, olc::DARK_MAGENTA);
	DrawString(textX1, textY1 + 120, "4. SEE GRAPH");
	
	
	DrawString(textX1, ScreenHeight()  -  100, "CLICK TO SELECT...");

}


bool GraphsProyect::DrawTripDistance()
{
	Clear(olc::DARK_RED);

	if (GetKey(olc::M).bReleased)
		state = MAIN_MENU;
	return false;
}

bool GraphsProyect::DrawTripCost()
{
	Clear(olc::DARK_GREEN);

	if (GetKey(olc::M).bReleased)
		state = MAIN_MENU;

	return false;
}

bool GraphsProyect::DrawTripTime()
{
	Clear(olc::DARK_BLUE);

	if (GetKey(olc::M).bReleased)
		state = MAIN_MENU;

	return false;
}

bool GraphsProyect::DrawGraphVisual()
{
	Clear(olc::DARK_MAGENTA);

	if (GetKey(olc::M).bReleased)
		state = MAIN_MENU;

	return false;
}
