//iterates adjancency
int iterateMatrix(int start, int end, int * * & adjancencyArray, int * * & pathArray, int * & adjacencyMatrixCount) {
  bool contained=false;
  for (int i = start; i < start + 1; i++) { //DO NOT TOUCH!
    for (int i = 0; i < numOfRows; i++) {

      if (adjancencyArray[start][i] == 0)
        contained = true;
      else {
        contained = false;
        if (matrixDisplacement == 3)
          break;
      }
    }
    if (start == startSource && contained == true && !pathAdded) //goes though the matrix
    {
    pathAdded = true;
      pathArray[matrixSource - 1][0] = start;
      adjacencyMatrixCount[matrixSource - 1] += 1;
      if (matrixDisplacement == 3)  break;
    }
    for (int j = end; j < numOfRows; j++) {

      if (adjancencyArray[i][j] == 1) {

        for (int k = matrixSource - 1; k < matrixSource; k++) //DONT TOUCH
        {
          for (int l = 0; l < adjacencyMatrixCount[matrixSource - 1]; l++) {
            numOfPaths = l;
            if (j == pathArray[k][l])
              pathTaken = true;
            else
              pathTaken = false;
            if (pathTaken) break; //Not sure if needed
          }
          if (pathTaken) //or this
            break;
        }
        if (pathTaken) //or this
          continue;
        if (!pathTaken) //This is needed to make sure path always matches index
        {
          if (start == startSource && !pathAdded) //change to reflect current index
          {
            pathAdded = true;

            pathArray[matrixSource - 1][0] = start;
            adjacencyMatrixCount[matrixSource - 1] += 1;
          }
          pathArray[matrixSource - 1][adjacencyMatrixCount[matrixSource - 1]] = j;
          adjacencyMatrixCount[matrixSource - 1] += 1;
          iterateMatrix(j, 0, adjancencyArray, pathArray, adjacencyMatrixCount);//Recursive to iterate though
          indicator = i;
        }
      }
    }
  }

}
