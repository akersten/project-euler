#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char** argv) {
  int i, j;

  if (argc != 2) {
    printf("Usage: ./main #rounds");
    exit(1);
  }

  int rounds = atoi(argv[1]) + 1;

  //Dynamic programming approach to problem 121. See the reference diagram
  //to visualize this triangle.
  double statTriangle[rounds][rounds + 1];
  for (i = 0; i < rounds; i++) {
    for (j = 0; j < rounds; j++) {
      statTriangle[i][j] = 0.0;
    }
  }
  statTriangle[0][0] = 1.0; //The odds of reaching the initial state is 1.


  //The calculation is as follows:
  //The triangle keeps track of the odds of reaching any state within the
  //triangle, since the problem basically results in sum(i, i = 1, #rounds)
  //different states of how many discs one can have collected (where each of
  //these states has a distinct probability associated with it). This is _not_
  //a mapping of #discs -> probability; there may be more than one state with
  //the same number of blue discs, but different probability. See the diagram
  //and it will be more clear.

  //The probability of being in a certain spot is the sum of the probability
  //of being one above and coming straight down, and the probability of being
  //one above and to the left and coming diagonally.
  //From above, the probability is probabilityOfBeingAbove * 1/(row + 1).
  //From above and to the left, the probability is probabilityOfBeingAboveAnd
  //toTheLeft * row/(row+1).

  for (i = 1; i < rounds; i++) {
    // j < i + 1 because we go one further over every row.
    for (j = 0; j < i + 1; j++) {
      //Add the top-straight, unless we're too far to the right.
      if (j < i) {
        statTriangle[i][j] += statTriangle[i - 1][j] * 1.0 / (i + 1.0);
      }
      //Add the top-diagonal-left, unless we're too far to the left.
      if (j > 0) {
        statTriangle[i][j] += statTriangle[i - 1][j - 1] * (i + 0.0) / (i + 1.0);
      }
    }
  }

  //Print the stat triangle!
  for (i = 0; i < rounds; i++) {
    for (j = 0; j < i + 1; j++) {
      printf("%10.9f ", statTriangle[i][j]);
    }
    printf("\n");
  }

  //And the odds of winning.
  double neverTellMeTheOdds = 0.0;
  for (i = 0; i < rounds / 2; i++) {
    neverTellMeTheOdds += statTriangle[rounds - 1][i];
  }
  printf("Odds of winning: %20.19f\n", neverTellMeTheOdds);
  printf("Maximum prize pool to not expect loss: %2.0f\n", ceil(1.0/neverTellMeTheOdds) - 1);
}