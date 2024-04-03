# PainterGraph

C++ university project for drawing graph from file.
## Introduction
  Hi, this is a university project in C++ for drawing a graph from a file. For example, in the file graph_example_1.txt The number of nodes and links is specified, and then each row represents the link between the nodes. The program reads the file and builds the graph accordingly. After that, we get images of graphs, as shown in the images on the links

## Graph example
graph_example_1.txt
5 4       - how Nodes + how links (but it's no necessary how links here, becouse program read all of them)
1 2       - link (1-2)
2 3       - link (2-3)
3 4       - link (3-4)
4 5       - link (4-5)

## Paint exapmples
---
![GraphTest1](https://github.com/heroi17/graphicsOnCPU/assets/146620896/bce12ca2-5e5c-4070-8a74-ce5182af082a)
![GraphTest2](https://github.com/heroi17/graphicsOnCPU/assets/146620896/a2b75ddc-93f6-458f-8ea0-3a9e24dd0707)
![GraphTest3](https://github.com/heroi17/graphicsOnCPU/assets/146620896/e5934106-8bc0-4aa3-900f-551cf1c78831)
![GraphTest4](https://github.com/heroi17/graphicsOnCPU/assets/146620896/6e584e2f-fbea-45e4-a5e6-3e525cddeaf3)
![GraphTest5](https://github.com/heroi17/graphicsOnCPU/assets/146620896/80b576c3-b8e5-4d5e-959c-a41a39248b84)
---
## Code examples
```
int test()
{

	//make buffer for plotting
	auto myBuf = bufferLib::Buffer2D<colorLib::RGBA8>(250, 250);
	myBuf.init(250, 250);

	//load graph.txt into graph object
	auto myGraph = GraphObjectLib::GraphObject();
	std::string outfilename = "GraphExamples/GraphTest1.txt";

	if (GraphObjectLib::ERROR_GRAPH_FILE ans; GraphObjectLib::ERROR_GRAPH_FILE::GRAPH_FILE_OK != (ans = myGraph.loadGraph(outfilename)))
	{
		std::cout << outfilename << "(problem with graph contains): exceptions(" << ans << ")\n";
		return 0;
	}
	

	//solve nodes position
	graphToolsLib::GraphSolver solwerGraph;

	solwerGraph.init(std::move(myGraph));
	for (int iter = 0; iter < 40; iter++) solwerGraph.solve();
	myGraph = std::move(solwerGraph);


	//save graph.txt
	auto settings = graphDrawLib::GraphDrawSettings<colorLib::RGBA8>(graphDrawLib::settings::NO_DRAW_NUMIRATION);//flags for draw(graph).
	graphDrawLib::drawGraph(myBuf, myGraph, settings);
	sBufLib::save(myBuf, "GraphExamples/bufferExample.bmp");
	std::cout << "\"" << outfilename << "\"is saved." << std::endl;
	return 0;
}
```

## Dependencies

https://github.com/marc-q/libbmp/tree/master