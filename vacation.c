
/* Program that determines the minimal number of meetings that would have to
   be rescheduled to accommodate a royal vacation.

   Author: Nic Dillon
*/

#include <stdio.h>
#include "io.h"
#include "io.c"

/* Returns a list of the days between each work day.

   Parameters:
       vacationLength - the number of days for which the royals wish to holiday
       lastDay - the last possible date for the last day of the vacation.
       numWorkingDays - the length of the array workingDays.

   Returns:
       A list of the number of free days between each workday.
*/
int* findTime(int lastDay, int* busyDays, int numWorkingDays) {
  int* freeDays = (int*) malloc(sizeof(int) * (numWorkingDays + 1));
  if(freeDays == NULL) {
    printf("Memory Error.");
    exit(-1);
  }
  if(numWorkingDays == 1) {
    freeDays[0] = busyDays[0];
    freeDays[1] = (lastDay - busyDays[0]);
  }
  for(int i = 1; i < numWorkingDays; i++) {
    if(i == 1) {
      freeDays[0] = busyDays[0];
    }
    freeDays[i] = (busyDays[i] - busyDays[i - 1]);
    if(i == numWorkingDays - 1) {
      freeDays[i + 1] = (lastDay - busyDays[i]);
    }
  }
  return freeDays;
}

/* Returns the minimal number of meetings that would have to be moved to allow
   the royals to have a happy vacation.

   Parameters:
       vacationLength - the number of days for which the royals wish to holiday
       numWorkingDays - the length of the array workingDays.
       freeTime - a list of the number of free days between each work day

   Returns:
       The smallest number of meetings that the King would have to move so he
       can enjoy his desired vacation.
*/
int moveMeetings(int vacationLength, int* freeTime, int numWorkingDays) {
  int movedMeetings;
  int combinedFreeTime;
  int minMeetingsMoved = numWorkingDays + 1;
  for(int i = 0; i <= numWorkingDays; i++) {
    if(i == numWorkingDays) {
      if(freeTime[i] >= vacationLength) {
        minMeetingsMoved = 0;
        return minMeetingsMoved;
      }
    }
    if(freeTime[i] - 1 >= vacationLength) {
      minMeetingsMoved = 0;
      return minMeetingsMoved;
    }
    combinedFreeTime = freeTime[i];
    movedMeetings = 1;
    for(int j = 1; i + j <= numWorkingDays; j++) {
      combinedFreeTime += freeTime[i + j];
      if(combinedFreeTime >= vacationLength) {
        if(movedMeetings < minMeetingsMoved) {
          minMeetingsMoved = movedMeetings;
        }
        break;
      }
      movedMeetings++;
    }
  }
  return minMeetingsMoved;
}

/* Returns the minimal number of meetings that would have to be moved to allow
   the royals to have a happy vacation.

   Parameters:
       vacationLength - the number of days for which the royals wish to holiday
       lastDay - the last possible date for the last day of the vacation.
       workingDays - an array containing the days on which the King has
                     meetings.
       numWorkingDays - the length of the array workingDays.

   Returns:
       The smallest number of meetings that the King would have to move so he
       can enjoy his desired vacation.
*/
int numMeetingsToMove(int vacationLength, int lastDay, int workingDays[],
                      int numWorkingDays) {
    int currentDay;
    // Place sorted work days from first appearing to last in busyDays
    for(int i = 0; i < numWorkingDays; i++) {
      int nearestDay = 0;
      for(int j = 0; j + i < numWorkingDays; j++) {
        if(workingDays[j + i] < nearestDay || nearestDay == 0) {
          nearestDay = workingDays[j + i];
          currentDay = j + i;
        }
      }
      workingDays[currentDay] = workingDays[i];
      workingDays[i] = nearestDay;
    }
    int* freeTime = findTime(lastDay, workingDays, numWorkingDays);
    int movedMeetings = moveMeetings(vacationLength, freeTime, numWorkingDays);
    free(freeTime);
    return movedMeetings;
}

/* Tester function. */
int main() {
    int testCase0[] = {2};
    printf("%d\n", numMeetingsToMove(3, 3, testCase0, 1)); // 1

    int testCase1[] = {3, 1, 2};
    printf("%d\n", numMeetingsToMove(3, 4, testCase1, 3)); // 2

    int testCase2[] = {4, 1};
    printf("%d\n", numMeetingsToMove(3, 5, testCase2, 2)); // 1

    int testCase3[] = {7, 4, 5, 6, 2};
    printf("%d\n", numMeetingsToMove(2, 9, testCase3, 5)); // 0

    int testCase4[] = {808, 459, 792, 863, 715, 70, 336, 731};
    printf("%d\n", numMeetingsToMove(513, 1000, testCase4, 8)); // 2

    return 0;
}
