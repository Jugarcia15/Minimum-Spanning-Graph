#include <iostream>
#include <fstream>
#include "ArgumentManager.h"
using namespace std;

int numOfRows = 0;
int numOfPaths = -1;
bool pathTaken = false;
int tempNumOfPaths = 1;
int initialValue = 0;
int matrixSource = 0;
bool pathAdded = false;
int indicator;
int startSource = 0;//See below for implementation
int matrixDisplacement = 0;

#include "Handler.h" 

void sortList(int arr[], int num) // sorts least to greatest
{
	int i, j;
	for (i = 0; i < num - 1; i++)
  {
		for (j = 0; j < num - i - 1; j++)
    {
      if (arr[j] > arr[j + 1])
      {
        int temp = arr[j]; //All because of test case 2
        arr[j] = arr[j+1];
        arr[j+1] = temp;
      }
    }
  }
}


class Graph //Parts of this are from Dr.Toti.
{
public:

	int source;
  int *edges;
	double **weights;
	double *edgeWeights;
	int gSize;
  string inputFile;
  string outputFile;

	Graph(int size = 0)
  {
  	weights = new double*[size];

  	for (int i = 0; i < size; i++) weights[i] = new double[size];
  	edges = new int[size];
  	edgeWeights = new double[size];
  	gSize = size;
    //Don't forget to delete
  }

  //creates tree

	~Graph(){};
	//NEED TO IMPLEMENT LATER

	void minimumSpanningTree(int sVertex) //name self explanitory
  {
  	int beginningVertex;
    int endVertex;
  	int k = 0;
  	int j = 0;

  	source = sVertex;
    double minimumWeight;

  	bool *mstv;
  	mstv = new bool[gSize];//DELETE!!!

    edgeWeights[source] = 0;
  	for (int j = 0; j < gSize; j++)
  	{
  		mstv[j] = false;
  		edges[j] = source;
  		edgeWeights[j] = weights[source][j];
  	}

  	mstv[source] = true;
  	edgeWeights[source] = 0;

  	for (int i = 0; i < gSize - 1; i++)
  	{
  		minimumWeight = 100000; //set really high

  		for (j = 0; j < gSize; j++)
  		{

  			if (mstv[j])
  				for (k = 0; k < gSize; k++)
  				{
  					if (!mstv[k] && weights[j][k]  < minimumWeight)
  					{
  						if (weights[j][k] == -999 || weights[j][k] == 0) //infinite weights, or bad weights
  							continue;
  						endVertex = k;
  						beginningVertex = j;
  						minimumWeight = weights[j][k];
  					}
  				}
  		}

  		mstv[endVertex] = true;
  		edges[endVertex] = beginningVertex;
  		edgeWeights[endVertex] = minimumWeight;
  	}
  } //NEED TO WORK ON
  //NEED TO CLEAN UP MEMORY LEAKS!!!

	void process();// goes though the whole process of taking input, processing, and writing out
};


void Graph::process()
{
	fstream Finput;
	ofstream Foutput;
	Finput.open(inputFile, ios::in);
	Foutput.open(outputFile, ios::out);
	int word[500][500]; string tempWord;
	int tempInt; //used in swapping, should make template for this
  string current; //get current current from inputFile
	stringstream ss; //fancy, but unneeded in c++11, handy to split strings
  int index; //for AM, see below
  int storageArray[3];
  int storageArray_2[3];
	int vertCount;
	int selectArray[500]; //adjancency matrix placed here until final processing
	int matrixConnect = 0;
  bool pathComparison = false;
	int horizontalCount[500]; //vertical not needed as we are sorted horzontally
	int horCounter = 0; //should make these dummy

  //to do: fix this crap
	getline(Finput, current); //reads line
	while (current != "" && !Finput.eof())
	{
		while (current != "" && !Finput.eof())
		{
			ss << current;
			for (int i = 0; ss >> tempWord; i++)
			{
        tempInt = stoi(tempWord);
				word[numOfRows][i] = tempInt;
				horizontalCount[horCounter] += 1;
			}
			ss.clear();
			numOfRows++;
			getline(Finput, current);
			horCounter++;

		}

	}
	int **adjacencyMatrix;
	adjacencyMatrix = new int*[numOfRows];
	for (int i = 0; i < numOfRows; i++)
		adjacencyMatrix[i] = new int[numOfRows];

	for (int edgeI = 0; edgeI < numOfRows; edgeI++)
		for (int edgeJ = 0; edgeJ < numOfRows; edgeJ++)
			adjacencyMatrix[edgeI][edgeJ] = 0;
	for (int i = 0; i < numOfRows; i++)
	{
		for (int j = 0; j < horizontalCount[i]; j++)
		{
			adjacencyMatrix[word[i][j]][i] = 1;
			adjacencyMatrix[i][word[i][j]] = 1;
		}
	}


	int numOfRows_2 = 0;
	int matrixRowTotal = 0;

	getline(Finput, current);
	while (current != "" && !Finput.eof())
	{
		ss.clear();
		ss << current;
		for (int i = 0; ss >> tempWord; i++)
		{
			tempInt = stoi(tempWord);
			word[numOfRows_2][i] = tempInt;
			matrixRowTotal++;
		}
		numOfRows_2++;
		if (matrixRowTotal != numOfRows)exit(0); //as instructed in instructions
		getline(Finput, current);
		ss.clear();
		matrixRowTotal = 0;
	}

	if (numOfRows_2 != numOfRows)exit(0); //same
	for (int edgeI = 0; edgeI < numOfRows; edgeI++)
		for (int edgeJ = 0; edgeJ < numOfRows; edgeJ++)
			weights[edgeI][edgeJ] = word[edgeI][edgeJ];

	getline(Finput, current);
	if (current == "")
		exit(0);
	int requiredClusters = stoi(current);
	if (requiredClusters < 1)	exit(0);
	else if (requiredClusters > numOfRows)exit(0);

	int r = 0; //Bringing this out to allow for 2nd if statement to work
	int chosenVertex = 0;
	for (int i = 0; i < numOfRows; i++)
	{
		for (r = 0; r < numOfRows; i++)
			if (adjacencyMatrix[i][r] == 1)
			{
				chosenVertex = i;
				break;
			}
		if (adjacencyMatrix[i][r] == 1)break;
	}

	minimumSpanningTree(chosenVertex); //output shared to global variable

	matrixConnect = true;
	int highestWeight = 0;
	int weightCoordinates[numOfRows][2];
	int weightCoordinatesCount = 0;
	int **history;
	history = new int*[requiredClusters];
	for (int i = 0; i < requiredClusters; i++)
		history[i] = new int[numOfRows];

	int *AMCounter;
	AMCounter = new int[requiredClusters];
	for (int i = 0; i < requiredClusters; i++)
		AMCounter[i] = 0;

	while (tempNumOfPaths != requiredClusters)
	{
		for (int i = 0; i < numOfRows; i++)
		{
			for (int j = 0; j < numOfRows; j++)
				cout << adjacencyMatrix[i][j] << " ";
			cout << endl;
		}

		for (int i = 0; i < numOfRows; i++)
			for (int j = 0; j < numOfRows; j++)// check if weights need to be removed
				if (weights[i][j] >= highestWeight)
				{
					highestWeight = weights[i][j];
				}
		//cout << highestWeight;
		for (int i = 0; i < numOfRows; i++)
			for (int j = 0; j < numOfRows; j++)// check if weights need to be removed
				if (weights[i][j] == highestWeight)
				{
					highestWeight = weights[i][j];
					//cout << weights[i][j] << endl;
					//highestWeight == 1;
					weightCoordinates[weightCoordinatesCount][0] = i;
					weightCoordinates[weightCoordinatesCount][1] = j;
					weightCoordinatesCount++;
				}
		//cout << highestWeight;
		bool proceed = false; //initialize before iterateMatrix

							  //while (numOfPaths + 1 != requiredClusters)
							  //

		for (int q = 0; q < weightCoordinatesCount; q++)
			for (int i = 0; edges[i]; i++)
			{
				if (weightCoordinates[q][0] != i)
					if (weightCoordinates[q][0] != edges[i])
						if (weightCoordinates[q][1] != i)
							if (weightCoordinates[q][1] != edges[i])
							{
								proceed = true;
								break;
							}
							else
								proceed = false;
			}

		if (proceed = true) //help taken from jackson
		{
			//cout << endl << weightCoordinates[0] << " " << weightCoordinates[1] << endl;
			for (int i = 0; i < weightCoordinatesCount; i++)
			{
				adjacencyMatrix[weightCoordinates[i][0]][weightCoordinates[i][1]] = 0;
				adjacencyMatrix[weightCoordinates[i][1]][weightCoordinates[i][0]] = 0;//check to see that double weights are removed
				weights[weightCoordinates[i][0]][weightCoordinates[i][1]] = -999;
				weights[weightCoordinates[i][1]][weightCoordinates[i][0]] = -999;//check to see that double weights are removed
			}

		}
		weightCoordinatesCount = 0;
		highestWeight = 0;

		int vertCount = 0;
		startSource = 0;
		index = 0; //reset due to axis swapping
		matrixSource = 0;
		if (initialValue == 0)
			matrixConnect = numOfRows;
		for (int j = 0; j <= tempNumOfPaths; j++)
			AMCounter[j] = 0;
		for (int i = 0; vertCount != numOfRows; i++) //DO NOT TOUCH!
		{
			pathAdded = false;
			pathTaken = false;
			matrixSource++;
			iterateMatrix(startSource, 0, adjacencyMatrix, history, AMCounter);

			for (int packingHeat = i; packingHeat < matrixSource; packingHeat++)
			{


				vertCount += AMCounter[i];
			}
			for (int j = 0; j < numOfRows; j++)
			{
				for (int xx = 0; xx < matrixSource; xx++)
				{
					for (int yy = 0; yy < AMCounter[xx]; yy++)
					{
						if (history[xx][yy] != j)
							pathComparison = false;
						else
						{
							pathComparison = true;
							break;
						}
					}if (pathComparison == true)
						break;
				}
				if (pathComparison == true)
					continue;
				if (pathComparison == false && j != 0)
				{
					selectArray[index] = j;
					index++;
				}

			}
			startSource = selectArray[0];
			for (int i = 0; i < index; i++)
			{
				if (startSource < selectArray[i])
					continue;
				else
					startSource = selectArray[i];
			}
			if (vertCount != numOfRows && vertCount != matrixConnect && i == tempNumOfPaths - 1)
				tempNumOfPaths++;

			pathAdded = false;
			for (int i = 0; i < numOfRows; i++)
				selectArray[i] = 10000000;
		}
		matrixConnect = vertCount;
		matrixDisplacement++;
		if (requiredClusters != tempNumOfPaths)
		{
			delete[] history; //reseting everything
			int ** history;
			history = new int*[requiredClusters];
			for (int i = 0; i < requiredClusters; i++)
				history[i] = new int[numOfRows];
		}
	}
	initialValue++;

	for (int p = 0; p < requiredClusters; p++)
	{
		int *testMatrix;
		testMatrix = new int[AMCounter[p]];

		for (int j = 0; j < AMCounter[p]; j++)
		{
			testMatrix[j] = history[p][j];
		}
		sortList(testMatrix, AMCounter[p]);
		for (int j = 0; j < AMCounter[p]; j++)
		{
			history[p][j] = testMatrix[j];
		}
		delete testMatrix;
	}
	for (int y = 0; y < requiredClusters; y++)storageArray[y] = history[y][0];
	sortList(storageArray, requiredClusters);

	for (int y = 0; y < requiredClusters; y++) //all that {} does is makes the following statement seem singular, meaning forloops can be done with indents
		for (int j = 0; j < requiredClusters; j++)
			if (history[j][0] == storageArray[y])
				storageArray_2[y] = j;

	for (int i = 0; i < requiredClusters; i++)
	{
		for (int j = 0; j < AMCounter[storageArray_2[i]]; j++)
			Foutput << history[storageArray_2[i]][j] << " ";
		Foutput << endl;
	}

} // DELETESSSS!!!!!
