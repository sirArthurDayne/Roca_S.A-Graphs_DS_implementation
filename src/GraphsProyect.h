#pragma once
#include"Graph.h"

///////////////////////TEXT FIELD MANAGER////////////
class TextField {
private:
	int maxLetters = 25, screenW = 240, screenH = 220;
	std::string fieldTxt = "";
	bool isInvisible = false;
	bool isHidden = false;
	const char keyLayout[37] = { ' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9' };
	const char shiftLayout[37] = { ' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',')','!','@','#','$','%','^','&','*','(' };
	const char numLayout[15] = { '0','1','2','3','4','5','6','7','8','9','*','/','+','-','.' };


	char  lGetLetterPressed() {
		if (Canvas->GetKey(olc::Key(63)).bPressed) return '<';
		else if (Canvas->GetKey(olc::Key(53)).bPressed) return ' ';
		for (int i = 1; i < 37; i++) {
			if (Canvas->GetKey(olc::Key::SHIFT).bHeld) {
				if (Canvas->GetKey(olc::Key(i)).bPressed) return shiftLayout[i];
			}
			else if (Canvas->GetKey(olc::Key(i)).bPressed) return keyLayout[i];
		}
		for (int i = 69; i <= 83; i++) {
			if (Canvas->GetKey(olc::Key(i)).bPressed) return numLayout[i - 69];
		}
		return 'å';
	}


public:
	TextField(olc::PixelGameEngine& Canvas) {
		this->Canvas = &Canvas;
		fieldTxt = "";
	}

	void updateField() {
		bool aClick = false;
		if (Canvas->GetMouse(0).bPressed) aClick = true;
		else if (Canvas->GetMouse(0).bHeld) aClick = true;
		else if (Canvas->GetMouse(0).bReleased) aClick = true;
		bool tEnter = false;
		if (Canvas->GetKey(olc::ENTER).bPressed) tEnter = true;
		else if (Canvas->GetKey(olc::ENTER).bHeld) tEnter = true;
		else if (Canvas->GetKey(olc::ENTER).bReleased) tEnter = true;
		if (true) {
			char newLetter = lGetLetterPressed();
			if (newLetter == '<' && fieldTxt.length() > 0) {
				std::string tempString = "";
				for (int i = 0; i < fieldTxt.length() - 1; i++) tempString += fieldTxt[i];
				fieldTxt.clear();
				fieldTxt = tempString;
				fieldTxt.shrink_to_fit();
			}
			else if (newLetter != 'å' && newLetter != '<' && fieldTxt.size() <= maxLetters) fieldTxt += newLetter;
		}
	}

	olc::PixelGameEngine* Canvas;

	std::string getString() { return fieldTxt; }

};

//////////////////////STATE MACHINE//////////////////
enum STATES { PRESENTATION, MAIN_MENU, DISTANCE_ROUTES, TIME_ROUTES, 
	COST_ROUTES, CONSULTING_MENU, INSERT_PATH, PATH_DISTANCE, PATH_TIME, PATH_COST};



//////////////////////MAIN APP CLASS////////////////////
class GraphsProyect : public olc::PixelGameEngine
{
private:
	STATES state;
	Vertex locations[8];//holds al vertex that will be using in the graphs
	//default graphs
	Graph DistanceMatrix;
	Graph CostMatrix;
	Graph TimeMatrix;

	//path related
	Graph UserPathDistanceMatrix;

	//user node path
	int userVertexSelected;
	Vertex UserNodePick;
	float userComparisonValue;
	int valueType;//0: distance, 1: time, 2:costs
	int greaterOrSmaller;//0: greater, 1: smaller, 2: equal

	//handles the input on screen
	TextField textManager = TextField(*this);
	

	//constants for drawing
	const int matrixX1 = 70;
	const int matrixY1 = 50;
	//constants for units convertion
	const int flightSpeed = 945;
	const float pricePerMinute = 1.56;
	
public:
	GraphsProyect();
private:
	bool OnUserCreate() override;
	bool OnUserUpdate(float deltaTime) override;
	
	//AIRLINE LOCATIONS
	void SetupDefaultVertices();
	//AIRLINE DISTANCE MATRIX 
	void SetupDistanceMatrixEdges();
	//AIRLINE TIME MATRIX 
	void SetUpTimeMatrixEdges();
	//AIRLINE COST MATRIX
	void SetUpCostMatrixEdges();

	//DRAW MENUS
	void DrawPresentation();                 
	void DrawMainMenu();
	void DrawConsultingMenu();
	void DrawInsertPathMenu();
	//DRAW DEFAULT AIRLINE INFO MATRICES
	void DrawAirlineMatrix(Graph& g, olc::Pixel bg_color, std::string title);
	
	//FUNCTIONS FOR PATHS
	void FindPathsByDistance(Graph& g, int vertexOrigin, int value);

	//aux methods
	int minDistance(int distances[], bool sptSet[]);
	float getTimeInMin(float distance);
	float getCostInDollars(float minutes);

};

