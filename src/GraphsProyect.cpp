#include "GraphsProyect.h"

GraphsProyect::GraphsProyect()
{
	sAppName = "Proyecto3 Aerolinea";
	state = PRESENTATION;
}

bool GraphsProyect::OnUserCreate()
{
	SetUpVertices();
	SetupDistanceMatrixEdges();
	SetUpTimeMatrixEdges();
	SetUpCostMatrixEdges();
	mainMenuOption = 1;
	return true;
}

bool GraphsProyect::OnUserUpdate(float deltaTime)
{
	
	if (state == PRESENTATION)
		DrawPresentation();
			
	if (state == MAIN_MENU)
		DrawMainMenu();
		
	if (state == DISTANCE_MATRIX)
		DrawDistanceMatrix();


	if (state == TIME_MATRIX)
		DrawTimeMatrix();

	if (state == COST_MATRIX)
		DrawCostMatrix();
	
	
	if (state == GRAPH_VISUAL)
		 DrawGraphVisual();


	if (GetKey(olc::ESCAPE).bPressed)
		return false;

	return true;
}


//////SETUP FUNTIONS///////////////
void GraphsProyect::SetUpVertices()
{
	//init the vertex
	
	//add vertices into array, for future drawing 
	locations[0] = Vertex("Cocle", 0);
	locations[1] = Vertex("Veraguas", 1);
	locations[2] = Vertex("LosSantos", 2);
	locations[3] = Vertex("Chiriqui", 3);
	locations[4] = Vertex("Panama", 4);
	locations[5] = Vertex("Colon", 5);
	locations[6] = Vertex("B.delToro", 6);
	locations[7] = Vertex("Herrera", 7);

	//load the 3 graph matrix (distance) that with all the vertices
	for (int i = 0; i < 8; i++)
	{
		DistanceMatrix.addVertex(locations[i]);
		TimeMatrix.addVertex(locations[i]);
		CostMatrix.addVertex(locations[i]);
	}
}

void GraphsProyect::ModifyEdge(Graph& g)
{
	if (GetMouse(0).bReleased)
	{
		int mouseX = GetMouseX();
		int mouseY = GetMouseY();
		
		for (int rows = 0; rows < g.size(); rows++)
		{
			for (int columns = 0; columns < g.size(); columns++)
			{
				if (mouseX > matrixX1 * (rows + 1) && mouseX <  (matrixX1 * (rows + 1)) + 10 && mouseY >
					matrixY1 * (columns + 1) && mouseY < (matrixY1 * (columns + 1)) + 10)
				{
					textManager.updateField();
					std::string textNum = textManager.getString();
					
					if (GetKey(olc::ENTER).bPressed)
					{
						g.addEdge(rows, columns,std::stof(textNum));
					}
				}
			}
		}
	}
}

void GraphsProyect::SetupDistanceMatrixEdges()
{

	//put the default values inside the distance matrix
	DistanceMatrix.addEdge(locations[0].vertexID, locations[1].vertexID, 2413);
	DistanceMatrix.addEdge(locations[1].vertexID, locations[2].vertexID, 3218);
	DistanceMatrix.addEdge(locations[1].vertexID, locations[7].vertexID, 2413);
	DistanceMatrix.addEdge(locations[2].vertexID, locations[3].vertexID, 3218);
	DistanceMatrix.addEdge(locations[3].vertexID, locations[1].vertexID, 2413);
	DistanceMatrix.addEdge(locations[4].vertexID, locations[0].vertexID, 2413);
	DistanceMatrix.addEdge(locations[4].vertexID, locations[1].vertexID, 3862);
	DistanceMatrix.addEdge(locations[4].vertexID, locations[5].vertexID, 2413);
	DistanceMatrix.addEdge(locations[5].vertexID, locations[0].vertexID, 1609);
	DistanceMatrix.addEdge(locations[5].vertexID, locations[3].vertexID, 3700);
	DistanceMatrix.addEdge(locations[5].vertexID, locations[6].vertexID, 3218);
}

void GraphsProyect::SetUpTimeMatrixEdges()
{
	TimeMatrix.addEdge(locations[0].vertexID, locations[1].vertexID, getTimeInMin(DistanceMatrix.getValueInMatrix(locations[0].vertexID, locations[1].vertexID)));
	TimeMatrix.addEdge(locations[1].vertexID, locations[2].vertexID, getTimeInMin(DistanceMatrix.getValueInMatrix(locations[1].vertexID, locations[2].vertexID)));
	TimeMatrix.addEdge(locations[1].vertexID, locations[7].vertexID, getTimeInMin(DistanceMatrix.getValueInMatrix(locations[1].vertexID, locations[7].vertexID)));
	TimeMatrix.addEdge(locations[2].vertexID, locations[3].vertexID, getTimeInMin(DistanceMatrix.getValueInMatrix(locations[2].vertexID, locations[3].vertexID)));
	TimeMatrix.addEdge(locations[3].vertexID, locations[1].vertexID, getTimeInMin(DistanceMatrix.getValueInMatrix(locations[3].vertexID, locations[1].vertexID)));
	TimeMatrix.addEdge(locations[4].vertexID, locations[0].vertexID, getTimeInMin(DistanceMatrix.getValueInMatrix(locations[4].vertexID, locations[0].vertexID)));
	TimeMatrix.addEdge(locations[4].vertexID, locations[1].vertexID, getTimeInMin(DistanceMatrix.getValueInMatrix(locations[4].vertexID, locations[1].vertexID)));
	TimeMatrix.addEdge(locations[4].vertexID, locations[5].vertexID, getTimeInMin(DistanceMatrix.getValueInMatrix(locations[4].vertexID, locations[5].vertexID)));
	TimeMatrix.addEdge(locations[5].vertexID, locations[0].vertexID, getTimeInMin(DistanceMatrix.getValueInMatrix(locations[5].vertexID, locations[0].vertexID)));
	TimeMatrix.addEdge(locations[5].vertexID, locations[3].vertexID, getTimeInMin(DistanceMatrix.getValueInMatrix(locations[5].vertexID, locations[3].vertexID)));
	TimeMatrix.addEdge(locations[5].vertexID, locations[6].vertexID, getTimeInMin(DistanceMatrix.getValueInMatrix(locations[5].vertexID, locations[6].vertexID)));
}

void GraphsProyect::SetUpCostMatrixEdges()
{
	CostMatrix.addEdge(locations[0].vertexID, locations[1].vertexID, getCostInDollars(TimeMatrix.getValueInMatrix(locations[0].vertexID, locations[1].vertexID)));
	CostMatrix.addEdge(locations[1].vertexID, locations[2].vertexID, getCostInDollars(TimeMatrix.getValueInMatrix(locations[1].vertexID, locations[2].vertexID)));
	CostMatrix.addEdge(locations[1].vertexID, locations[7].vertexID, getCostInDollars(TimeMatrix.getValueInMatrix(locations[1].vertexID, locations[7].vertexID)));
	CostMatrix.addEdge(locations[2].vertexID, locations[3].vertexID, getCostInDollars(TimeMatrix.getValueInMatrix(locations[2].vertexID, locations[3].vertexID)));
	CostMatrix.addEdge(locations[3].vertexID, locations[1].vertexID, getCostInDollars(TimeMatrix.getValueInMatrix(locations[3].vertexID, locations[1].vertexID)));
	CostMatrix.addEdge(locations[4].vertexID, locations[0].vertexID, getCostInDollars(TimeMatrix.getValueInMatrix(locations[4].vertexID, locations[0].vertexID)));
	CostMatrix.addEdge(locations[4].vertexID, locations[1].vertexID, getCostInDollars(TimeMatrix.getValueInMatrix(locations[4].vertexID, locations[1].vertexID)));
	CostMatrix.addEdge(locations[4].vertexID, locations[5].vertexID, getCostInDollars(TimeMatrix.getValueInMatrix(locations[4].vertexID, locations[5].vertexID)));
	CostMatrix.addEdge(locations[5].vertexID, locations[0].vertexID, getCostInDollars(TimeMatrix.getValueInMatrix(locations[5].vertexID, locations[0].vertexID)));
	CostMatrix.addEdge(locations[5].vertexID, locations[3].vertexID, getCostInDollars(TimeMatrix.getValueInMatrix(locations[5].vertexID, locations[3].vertexID)));
	CostMatrix.addEdge(locations[5].vertexID, locations[6].vertexID, getCostInDollars(TimeMatrix.getValueInMatrix(locations[5].vertexID, locations[6].vertexID)));
}


///////DRAW FUNCTIONS////////////
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
			state = DISTANCE_MATRIX;

		else if (mouseX > textX1 && mouseX < textX1 + 200 && mouseY > textY1 + 40 && mouseY < (textY1 +40) + 20)
			state = TIME_MATRIX;
		
		else if (mouseX > textX1 && mouseX < textX1 + 200 && mouseY > textY1 + 80 && mouseY < (textY1 +80) + 20)
			state = COST_MATRIX;
		
		else if (mouseX > textX1 && mouseX < textX1 + 200 && mouseY > textY1 + 120 && mouseY < (textY1 +120)+ 20)
			state = GRAPH_VISUAL;

	}


	Clear(olc::BLACK);
	DrawString(ScreenWidth() / 2 - 50, 20, "MAIN MENU");
	FillRect(textX1,textY1, textX1 + 100, 20, olc::DARK_RED);
	DrawString(textX1, textY1, "1. SEE DISTANCE MATRIX (KM)");

	FillRect(textX1, textY1 + 40, textX1 + 100, 20 , olc::DARK_BLUE);
	DrawString(textX1, textY1 + 40, "2. SEE TIME MATRIX (min)");

	FillRect(textX1, textY1 + 80, textX1 + 100, 20, olc::DARK_GREEN);
	DrawString(textX1, textY1 + 80, "3. SEE COST MATRIX (BL/.)");

	FillRect(textX1, textY1 + 120, textX1 + 100, 20, olc::DARK_MAGENTA);
	DrawString(textX1, textY1 + 120, "4. SEE GRAPH");
	
	
	DrawString(textX1, ScreenHeight()  -  100, "CLICK TO SELECT...");

}


bool GraphsProyect::DrawDistanceMatrix()
{
		Clear(olc::DARK_RED);

		DrawString(10, 5, "DISTANCE MATRIX (KM)");
	
		for (int rows = 0; rows < DistanceMatrix.size(); rows++)
		{
			DrawString(5, matrixY1 * (rows + 1), locations[rows].name, olc::WHITE);
			DrawString(matrixX1 * (rows +1) - 5, matrixY1 - 15, locations[rows].name + " ", olc::WHITE);
			for (int columns = 0; columns < DistanceMatrix.size(); columns++)
			{
				int value = (int)DistanceMatrix.getValueInMatrix(columns, rows);
		
				if (value != 0)
				DrawString(matrixX1 * (rows + 1) + 25, matrixY1 * (columns + 1), std::to_string(value), olc::GREEN);
				else 
				DrawString(matrixX1 * (rows + 1) + 25, matrixY1 * (columns + 1), "--", olc::GREEN);
			}
		}


	if (GetKey(olc::M).bReleased)
		state = MAIN_MENU;
	
	return false;
}

bool GraphsProyect::DrawTimeMatrix()
{
	Clear(olc::DARK_BLUE);
		DrawString(10, 5, "TIME MATRIX (min)");
	
		for (int rows = 0; rows < TimeMatrix.size(); rows++)
		{
			DrawString(5, matrixY1 * (rows + 1), locations[rows].name, olc::WHITE);
			DrawString(matrixX1 * (rows +1) - 5, matrixY1 - 15, locations[rows].name + " ", olc::WHITE);
			for (int columns = 0; columns < TimeMatrix.size(); columns++)
			{
				int value = (int)TimeMatrix.getValueInMatrix(columns, rows);
				if (value != 0.0)
				DrawString(matrixX1 * (rows + 1) + 25, matrixY1 * (columns + 1), std::to_string(value), olc::GREEN);
				else 
				DrawString(matrixX1 * (rows + 1) + 25, matrixY1 * (columns + 1), "--", olc::GREEN);
			}
		}

	if (GetKey(olc::M).bReleased)
		state = MAIN_MENU;

	return false;
}

bool GraphsProyect::DrawCostMatrix()
{
	Clear(olc::VERY_DARK_GREEN);
	DrawString(10, 5, "COST MATRIX (B/.)");
	
		for (int rows = 0; rows < CostMatrix.size(); rows++)
		{
			DrawString(5, matrixY1 * (rows + 1), locations[rows].name, olc::WHITE);
			DrawString(matrixX1 * (rows +1) - 5, matrixY1 - 15, locations[rows].name + " ", olc::WHITE);
			for (int columns = 0; columns < CostMatrix.size(); columns++)
			{
				int value = (int)CostMatrix.getValueInMatrix(columns, rows);
				if (value != 0.0)
				DrawString(matrixX1 * (rows + 1) + 25, matrixY1 * (columns + 1), std::to_string(value) + ".0", olc::DARK_YELLOW);
				else 
				DrawString(matrixX1 * (rows + 1) + 25, matrixY1 * (columns + 1), "--", olc::RED);
			}
		}


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

float GraphsProyect::getTimeInMin(float distance)
{
	return (distance / flightSpeed) * 60.0;
}

float GraphsProyect::getCostInDollars(float minutes)
{
	return pricePerMinute * minutes;
}
