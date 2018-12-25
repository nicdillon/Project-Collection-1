
/* Program that implements run-length encoding of a given data file.

   Author: Nic Dillon
*/

#include <stdio.h>
#include <stdlib.h>

/* Run-length encodes the specified file.

   Parameters:
       filename - the name of the file to be compressed.
       numElements - the number of elements in the run-length compressed
                     array is returned via this parameter.

   Returns:
       The run-length compression of the data that was read in
       from the given file. This is a 2d array where each row contains
       exactly two columns: the first column denotes the value to be
       repeated and the second column specifies the number of
       repetitions of that value. The length of this array is returned
       to the caller via the pointer numElements.
*/
int* encode(char* fileName, int* numRows) {
  FILE * ipf = fopen(fileName, "r");
  int rows;
  int currentValue;
  int consecutiveValue;
  int occurences;
  int counter = 0;
  if(ipf == NULL) {
    printf("File Error. \n");
    exit(-1);
  }
  if(fscanf(ipf, "%d", &rows) == 0) {
    printf("File Error. \n");
    exit(-3);
  }
  int* runLength = (int*) malloc(sizeof(int) * (2 * rows));
  if(runLength == NULL) {
    printf("Memory Error.");
    exit(-3);
  }
  while(!feof(ipf)) {
    if(fscanf(ipf, "%d", &currentValue) == 0) {
      printf("File Error. Scan could not be completed. \n");
      exit(-3);
    }
    if(counter == 0) {
      occurences = 0;
      consecutiveValue = currentValue;
      counter++;
    }
    if(currentValue != consecutiveValue) {
      runLength[2 * (counter - 1) + 0] = consecutiveValue;
      runLength[2 * (counter - 1) + 1] = occurences;
      consecutiveValue = currentValue;
      occurences = 1;
      counter++;
      continue;
    }
    occurences++;
  }
  occurences--;
  *numRows = counter;
  runLength[2 * (counter - 1) + 0] = currentValue;
  runLength[2 * (counter - 1) + 1] = occurences;
  int * newArray = (int*) malloc(sizeof(int) * (2 * counter));
  if(newArray == NULL) {
    printf("Memory Error.");
    exit(-3);
  }
  for(int i = 0; i < counter * 2; i++) {
    newArray[i] = runLength[i];
  }
  free(runLength);
  fclose(ipf);
  return newArray;
}

/* Tester function. */
int main() {

    int numRows = 0;

    // ---------------------------------------------

    // Test case 1
    int* compressed = encode("data1.txt", &numRows);

    printf("%d\n", numRows); // should be 3

    // following should print 0 5 1 3 2 8
    for (int i = 0; i < numRows*2; i++) {
        printf("%d ", compressed[i]);
    }
    printf("\n");
    free(compressed);

    // ---------------------------------------------

    // Test case 2
    compressed = encode("data2.txt", &numRows);
    printf("%d\n", numRows); // should be 1

    // should print 5 34
    for (int i = 0; i < numRows*2; i++) {
        printf("%d ", compressed[i]);
    }
    printf("\n");
    free(compressed);

    return 0;
}
