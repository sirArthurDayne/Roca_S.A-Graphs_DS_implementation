#include "GraphsProyect.h"

GraphsProyect::GraphsProyect()
{
	sAppName = "Proyecto3 Aerolinea";
	state = PRESENTATION;
}

bool GraphsProyect::OnUserCreate()
{
	//set defaults matrices for visualize the airline information
	SetupDefaultVertices();
	SetupDistanceMatrixEdges();
	SetUpTimeMatrixEdges();
	SetUpCostMatrixEdges();
	
	return true;
}

bool GraphsProyect::OnUserUpdate(float deltaTime)
{
	
	if (state == PRESENTATION)
		DrawPresentation();
			
	if (state == MAIN_MENU)
		DrawMainMenu();	
	
	if (state == DISTANCE_ROUTES)
		DrawAirlineMatrix(DistanceMatrix, olc::VERY_DARK_RED, "DISTANCE MATRIX (KM)");

	if (state == TIME_ROUTES)
		DrawAirlineMatrix(TimeMatrix, olc::DARK_BLUE, "TIME MATRIX (minutes)");

	if (state == COST_ROUTES)
		DrawAirlineMatrix(CostMatrix, olc::VERY_DARK_YELLOW, "COST MATRIX ($)");

	//ALL THE STATES FOR CALCULATING PATH AND DRAW MATRICES
	if (state == CONSULTING_MENU)
		DrawConsultingMenu();

	if (state == INSERT_PATH)
	{
		DrawInsertPathMenu();
	}

	if (state == PATH_DISTANCE)
	{
		//TO DO PATH FOR DISTANCE
		Clear(olc::CYAN);
		
	}
	if (state == PATH_TIME)
	{
		//TO DO PATH FOR TIME
		Clear(olc::DARK_GREY);
	}
	if (state == PATH_COST)
	{
		//TO DO PATH FOR COST
		Clear(olc::DARK_BLUE);
	}


	if (GetKey(olc::ESCAPE).bPressed)
		return false;

	return true;
}


//////SETUP FUNTIONS///////////////
void GraphsProyect::SetupDefaultVertices()
{
	//add the 8 vertices(name, id) into array with some defaults names
	locations[0] = Vertex("COC", 0);
	locations[1] = Vertex("VER", 1);
	locations[2] = Vertex("LST", 2);
	locations[3] = Vertex("CHI", 3);
	locations[4] = Vertex("PAN", 4);
	locations[5] = Vertex("COL", 5);
	locations[6] = Vertex("BOC", 6);
	locations[7] = Vertex("HER", 7);

	//load each graphs with all the vertices
	for (int i = 0; i < 8; i++)
	{
		DistanceMatrix.addVertex(locations[i]);
		TimeMatrix.addVertex(locations[i]);
		CostMatrix.addVertex(locations[i]);
	}
}

void GraphsProyect::SetupDistanceMatrixEdges()
{
	//this edges cannot change
	DistanceMatrix.addEdge(locations[0].vertexID, locations[1].vertexID, 2413);
	DistanceMatrix.addEdge(locations[1].vertexID, locations[2].vertexID, 3218);
	DistanceMatrix.addEdge(locations[1].vertexID, locations[7].vertexID, 2413);
	DistanceMatrix.addEdge(locations[2].vertexID, locations[3].vertexID, 3218);
	DistanceMatrix.addEdge(locations[1].vertexID, locations[3].vertexID, 2413);
	DistanceMatrix.addEdge(locations[4].vertexID, locations[0].vertexID, 2413);
	DistanceMatrix.addEdge(locations[4].vertexID, locations[1].vertexID, 3862);
	DistanceMatrix.addEdge(locations[4].vertexID, locations[5].vertexID, 2413);
	DistanceMatrix.addEdge(locations[5].vertexID, locations[0].vertexID, 1609);
	DistanceMatrix.addEdge(locations[5].vertexID, locations[3].vertexID, 3700);
	DistanceMatrix.addEdge(locations[5].vertexID, locations[6].vertexID, 3218);
}

void GraphsProyect::SetUpTimeMatrixEdges()
{
	//this edges cannot change
	TimeMatrix.addEdge(locations[0].vertexID, locations[1].vertexID, getTimeInMin(DistanceMatrix.getValueInMatrix(locations[0].vertexID, locations[1].vertexID)));
	TimeMatrix.addEdge(locations[1].vertexID, locations[2].vertexID, getTimeInMin(DistanceMatrix.getValueInMatrix(locations[1].vertexID, locations[2].vertexID)));
	TimeMatrix.addEdge(locations[1].vertexID, locations[7].vertexID, getTimeInMin(DistanceMatrix.getValueInMatrix(locations[1].vertexID, locations[7].vertexID)));
	TimeMatrix.addEdge(locations[2].vertexID, locations[3].vertexID, getTimeInMin(DistanceMatrix.getValueInMatrix(locations[2].vertexID, locations[3].vertexID)));
	TimeMatrix.addEdge(locations[1].vertexID, locations[3].vertexID, getTimeInMin(DistanceMatrix.getValueInMatrix(locations[1].vertexID, locations[3].vertexID)));
	TimeMatrix.addEdge(locations[4].vertexID, locations[0].vertexID, getTimeInMin(DistanceMatrix.getValueInMatrix(locations[4].vertexID, locations[0].vertexID)));
	TimeMatrix.addEdge(locations[4].vertexID, locations[1].vertexID, getTimeInMin(DistanceMatrix.getValueInMatrix(locations[4].vertexID, locations[1].vertexID)));
	TimeMatrix.addEdge(locations[4].vertexID, locations[5].vertexID, getTimeInMin(DistanceMatrix.getValueInMatrix(locations[4].vertexID, locations[5].vertexID)));
	TimeMatrix.addEdge(locations[5].vertexID, locations[0].vertexID, getTimeInMin(DistanceMatrix.getValueInMatrix(locations[5].vertexID, locations[0].vertexID)));
	TimeMatrix.addEdge(locations[5].vertexID, locations[3].vertexID, getTimeInMin(DistanceMatrix.getValueInMatrix(locations[5].vertexID, locations[3].vertexID)));
	TimeMatrix.addEdge(locations[5].vertexID, locations[6].vertexID, getTimeInMin(DistanceMatrix.getValueInMatrix(locations[5].vertexID, locations[6].vertexID)));
}

void GraphsProyect::SetUpCostMatrixEdges()
{
	//this edges cannot change
	CostMatrix.addEdge(locations[0].vertexID, locations[1].vertexID, getCostInDollars(TimeMatrix.getValueInMatrix(locations[0].vertexID, locations[1].vertexID)));
	CostMatrix.addEdge(locations[1].vertexID, locations[2].vertexID, getCostInDollars(TimeMatrix.getValueInMatrix(locations[1].vertexID, locations[2].vertexID)));
	CostMatrix.addEdge(locations[1].vertexID, locations[7].vertexID, getCostInDollars(TimeMatrix.getValueInMatrix(locations[1].vertexID, locations[7].vertexID)));
	CostMatrix.addEdge(locations[2].vertexID, locations[3].vertexID, getCostInDollars(TimeMatrix.getValueInMatrix(locations[2].vertexID, locations[3].vertexID)));
	CostMatrix.addEdge(locations[1].vertexID, locations[3].vertexID, getCostInDollars(TimeMatrix.getValueInMatrix(locations[1].vertexID, locations[3].vertexID)));
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

	//DrawString(ScreenWidth() / 2 - 120, ScreenHeight() - 50, "SPECIAL THANKS TO ZLEAPINGBEAR");
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
			state = DISTANCE_ROUTES;

		else if (mouseX > textX1 && mouseX < textX1 + 200 && mouseY > textY1 + 40 && mouseY < (textY1 + 40) + 20)
			state = TIME_ROUTES;

		else if (mouseX > textX1 && mouseX < textX1 + 200 && mouseY > textY1 + 80 && mouseY < (textY1 + 80) + 20)
			state = COST_ROUTES;

		else if (mouseX > textX1 && mouseX < textX1 + 200 && mouseY > textY1 + 120 && mouseY < (textY1 + 120) + 20)
			state = CONSULTING_MENU;

	}


	Clear(olc::BLACK);
	DrawString(ScreenWidth() / 2 - 50, 20, "AIRLINE INFORMATION");
	FillRect(textX1, textY1, textX1 + 100, 20, olc::DARK_RED);
	DrawString(textX1, textY1, "1. SEE DISTANCE MATRIX (Kilometers)");

	FillRect(textX1, textY1 + 40, textX1 + 100, 20, olc::DARK_BLUE);
	DrawString(textX1, textY1 + 40, "2. SEE TIME TRAVEL MATRIX (minutes)");

	FillRect(textX1, textY1 + 80, textX1 + 100, 20, olc::DARK_GREEN);
	DrawString(textX1, textY1 + 80, "3. SEE COST MATRIX ($)");

	FillRect(textX1, textY1 + 120, textX1 + 100, 20, olc::DARK_MAGENTA);
	DrawString(textX1, textY1 + 120, "4. CONSULT INFO ABOUT ROUTES");


	DrawString(textX1, ScreenHeight() - 100, "CLICK TO SELECT...");

}

void GraphsProyect::DrawConsultingMenu()
{
	int textX1 = ScreenWidth() / 2 - 100;
	int textY1 = 100;

	//INPUT
	if (GetMouse(0).bReleased)
	{
		int mouseX = GetMouseX();
		int mouseY = GetMouseY();

		if (mouseX > textX1 && mouseX < textX1 + 200 && mouseY > textY1 && mouseY < textY1 + 20)
			state = PATH_DISTANCE;

		else if (mouseX > textX1 && mouseX < textX1 + 200 && mouseY > textY1 + 40 && mouseY < (textY1 + 40) + 20)
			state = PATH_TIME;

		else if (mouseX > textX1 && mouseX < textX1 + 200 && mouseY > textY1 + 80 && mouseY < (textY1 + 80) + 20)
			state = PATH_COST;

		else if (mouseX > textX1 && mouseX < textX1 + 200 && mouseY > textY1 + 160 && mouseY < (textY1 + 160) + 20)
			state = INSERT_PATH;
	}

	Clear(olc::BLACK);
	DrawString(ScreenWidth() / 2 - 50, 20, "CONSULTING THE AIRLINE...");
	FillRect(textX1, textY1, textX1 + 150, 20, olc::DARK_RED);
	DrawString(textX1, textY1, "1. SEE PATH BY SOME START, DESTINY AND DISTANCE(km)");

	FillRect(textX1, textY1 + 40, textX1 + 150, 20, olc::DARK_BLUE);
	DrawString(textX1, textY1 + 40, "2. SEE PATH BY SOME START, DESTINY AND TIME(minutes)");

	FillRect(textX1, textY1 + 80, textX1 + 150, 20, olc::DARK_GREEN);
	DrawString(textX1, textY1 + 80, "3. SEE PATH BY SOME START, DESTINY AND COST($)");

	FillRect(textX1, textY1 + 160, textX1 + 150, 20, olc::DARK_YELLOW);
	DrawString(textX1, textY1 + 160, "4.ADD PATH");

	DrawString(textX1, ScreenHeight() - 100, "CLICK TO SELECT...");

	if (GetKey(olc::M).bReleased)
		state = MAIN_MENU;
}

void GraphsProyect::DrawInsertPathMenu()
{
	if (GetMouse(0).bReleased)
	{
		int mouseX = GetMouseX();
		int mouseY = GetMouseY();
		
		//select locations
		for (int j = 0; j < 8; j++)
		{
			if (mouseX > 25 && mouseX < 100 && mouseY > 50 * (j + 1) && mouseY < (50 * (j + 1)) + 20)
			{
				userVertexSelected = j;
			}
		}

		for (int k = 0; k < 3; k++)
		{
			if (mouseX > 200 && mouseX < 250 && mouseY > 50 *(k+1)&& mouseY < (50 *(k+1))+ 10)
			{
				valueType = k;
			}
			else if(mouseX > 400 && mouseX < 450 && mouseY > 50 * (k + 1) && mouseY < (50 * (k + 1)) + 10)
			{
				greaterOrSmaller = k;
			}
		}
	}
	Clear(olc::BLACK);

	static bool reading = true;
	static std::string testExpression = "";
	if (reading)
	{
		textManager.updateField();
		testExpression = textManager.getString();
		DrawString(ScreenWidth()/2, ScreenHeight()/2, testExpression, olc::WHITE);
	}
	else
	{
		userComparisonValue = std::stof(testExpression);
		DrawString(ScreenWidth() / 2, ScreenHeight() / 2 + 50, "VALID EXPRESSION!", olc::DARK_GREEN);
	}

	if (GetKey(olc::ENTER).bReleased)
	{
		reading = false;
		UserNodePick = locations[userVertexSelected];//set vertex
	}
	if (GetKey(olc::B).bPressed)
	{
		testExpression = "";
		state = CONSULTING_MENU;
	}


	for (int i = 0; i < 8; i++)
		DrawString(25, 50 * (i + 1), locations[i].name + ": " + std::to_string(locations[i].vertexID));
	
	DrawString(200, 50, "1. Distance");
	DrawString(200, 100, "2. Time");
	DrawString(200, 150, "3. Cost");

	DrawString(400, 50, "1. Greater");
	DrawString(400, 100, "2. Less");
	DrawString(400, 150, "3. Equal");

	DrawString(ScreenWidth() / 2 -150, ScreenHeight() / 2, "Compasion Value:", olc::WHITE);
	DrawString(ScreenWidth() / 2, ScreenHeight() / 2, testExpression, olc::DARK_GREEN);
	//text selections
	DrawString( 25, 25, "Ver. Pick: " + locations[userVertexSelected].name, olc::DARK_GREEN);
	
	if (valueType == 0)
		DrawString( 200, 25, "Value Type: Distance", olc::DARK_GREEN);
	else if (valueType == 1)
		DrawString(200, 25, "Value Type: Time", olc::DARK_GREEN);
	else if (valueType == 2)
		DrawString(200, 25, "Value Type: Cost", olc::DARK_GREEN);

	if (greaterOrSmaller == 0)
		DrawString(400, 25, "Greater >", olc::DARK_GREEN);
	else if (greaterOrSmaller == 1)
		DrawString(400, 25, "Smaller < ", olc::DARK_GREEN);
	else if (greaterOrSmaller == 2)
		DrawString(400, 25, "Equal =", olc::DARK_GREEN);
}


//////// DRAW AIRLINES ROUTES FUNCTION////////////////
void GraphsProyect::DrawAirlineMatrix(Graph& g, olc::Pixel bg_color, std::string title)
{
	Clear(bg_color);

	DrawString(10, 5, title);

	for (int rows = 0; rows < g.size(); rows++)
	{
		DrawString(5, matrixY1 * (rows + 1), locations[rows].name, olc::WHITE);
		DrawString(matrixX1 * (rows + 1) - 5, matrixY1 - 15, locations[rows].name + " ", olc::WHITE);
		for (int columns = 0; columns < g.size(); columns++)
		{
			int value = (int)g.getValueInMatrix(columns, rows);

			if (value == INF)
				DrawString(matrixX1 * (rows + 1) + 25, matrixY1 * (columns + 1), "--", olc::GREEN);
			else if (value == 0.0)
				DrawString(matrixX1 * (rows + 1) + 25, matrixY1 * (columns + 1), "0.0", olc::GREEN);
			else
				DrawString(matrixX1 * (rows + 1) + 25, matrixY1 * (columns + 1), std::to_string(value), olc::GREEN);
		}
	}


	if (GetKey(olc::M).bReleased)
		state = MAIN_MENU;
}


//implementation of diskstra algorithm
void GraphsProyect::FindPathsByDistance(Graph& g, int vertexOrigin, int value)
{
	int distancesArray[8];
	bool sptSet[8];
	
	for (int i = 0; i < 8; i++)
	{
		distancesArray[i] = INF;
		sptSet[i] = false;
	}
	distancesArray[vertexOrigin] = 0;

	for (int i = 0; i < 7; i++)//7: MAXSIZE - 1
	{
		int u = minDistance(distancesArray, sptSet);

		sptSet[i] = true;

		for (int v = 0; v < 8; v++)
		{
			if (!sptSet[v] && g.getValueInMatrix(u,v) != 0.0 && distancesArray[u] != INF
				&& distancesArray[u] + g.getValueInMatrix(u,v) < distancesArray[v])
				distancesArray[v] = distancesArray[u] + g.getValueInMatrix(u,v);
		}
	}
}

//function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree 
int GraphsProyect::minDistance(int distances[], bool sptSet[])
{
	//Init min value
	int min = INF;
	int minIndex;

	for (int i = 0; i < 8; i++)
	{
		if (sptSet[i] == false && distances[i] <= min)
		{
			min = distances[i];
			minIndex = i;
		}
	}

	return minIndex;
}

/////////AUX FUNCTIONS////////
float GraphsProyect::getTimeInMin(float distance)
{
	return (distance / flightSpeed) * 60.0;
}

float GraphsProyect::getCostInDollars(float minutes)
{
	return pricePerMinute * minutes;
}
