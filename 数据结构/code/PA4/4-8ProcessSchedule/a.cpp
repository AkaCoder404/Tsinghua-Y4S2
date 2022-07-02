#include <iostream>
#define SIZE 100000
struct process {
  int id;
  int priority;
  int creationTime;
  int executionTime;
  process() : id(0), priority(0), creationTime(0), executionTime(0){};
  process(int _id, int _priority, int _creationTime, int _executionTime)
      : id(_id), priority(_priority), creationTime(_creationTime), executionTime(_executionTime){};
} processes[SIZE];

int main() {
  int n; // number of process
  scanf("%d", &n);
  int id, priority, creationTime, executionTime;
  int totalTime = 0;
  for (int i = 0; i < n; i++) {
    scanf("%d %d %d %d", &processes[i].id, &processes[i].priority, &processes[i].creationTime, &processes[i].executionTime);
    totalTime += processes[i].executionTime;
  }


  // brute force method
  totalTime += processes[0].creationTime; // first creation time + total execution time
  int currentProcess = 0;
  for (int i = processes[0].creationTime; i < totalTime; i++) {
    // find creation time that starts at time i
    int maxPriority = 0;
    int currentProcessId;
    int currentProcessTime;
    for (int j = 0; j < n; j++) {
      // creation time is ordered, so if process creation time exceed curr time, stop searching
      if (processes[j].creationTime > i) break;
      else { // if process creation time is equal to or less than
        // if processes runs out of execution time 
        if (processes[j].executionTime <= 0) continue;
        // if it has higher priority than current
        if (processes[j].priority >= maxPriority) {
          if (processes[j].priority == maxPriority) { 
            // if priority is same, compare creation time
            if (processes[j].creationTime <= processes[currentProcess].creationTime) {
              // if creation time is same, compare process number
              if (processes[j].id <= processes[currentProcess].id) {
                 maxPriority = processes[j].priority;
                 currentProcess = j;
              }
            }
          } else { // when priority is >
            maxPriority = processes[j].priority;
            currentProcess = j;
          }
        }
      }
    }
       
    // printf("T%d : %d: ", i, processes[currentProcess].id);
    
    // decrease remaining execution time for currentProcess
    processes[currentProcess].executionTime--;
    if (processes[currentProcess].executionTime == 0) {
      printf("%d %d\n", processes[currentProcess].id, i + 1);
    }
    // printf("\n");
  }

  // printf("Testing\n");
  // for (int i = 0; i < n; i++) {
  //   printf("%d %d %d %d\n", processes[i].id, processes[i].priority, processes[i].creationTime, processes[i].executionTime);
  // }

  return 0;
}