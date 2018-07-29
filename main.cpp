#include "graphType.h"

int main(int argc, char* argv[])
{
	Graph graph = Graph(10);

	if (argc < 2)
	{
		cout << "Usage: ./cluster 'A=<file>;C=<file>'" << endl;
    cout << "Exiting" << endl;
		return -1;
	}

	ArgumentManager am(argc, argv);

	graph.inputFile = am.get("A");
	graph.outputFile = am.get("C");

	graph.process();

}
