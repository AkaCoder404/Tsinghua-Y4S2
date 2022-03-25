#include "stdio.h"
#include "cstring"
#include <iostream>

bool pause[1000000];

struct Queue {
  int *queue;
  int start;
  int end; 
  int capacity;

  Queue() {
    capacity = 1000000;
    queue = new int[capacity];
    start = 1;
    end = 1; 
  }

  ~Queue() {
    delete[] queue;
  }

  bool empty() {
    if (start == end) return true;
    else return false;
  }

  void push(int value) {
    queue[end++] = value;
  }

  void front_push(int value) {
    queue[--start] = value;
  }

  int front() {
    // if (pause[queue[start]] == true) 
    // return queue[start];
    printf("front %d\n", queue[start]);
    while(pause[queue[start]]) {
      start++;
    }
    return queue[start];
  }

  int pop() {
    if (!empty()) {
      return queue[start++];
    }
    else return false;
  } 
} dispatch;

int main() {
  int N;
  scanf("%d", &N);
  std::cin.ignore();

  char process[100];
  int pid;
  for (int i = 0; i < N; i++) {
    std::cin.getline(process, 100);
    int pos_space = -1;
    int len = strlen(process);
    char *space_ptr = (strchr(process, ' '));
    if (space_ptr != NULL)
      pos_space = space_ptr - process;

    char command[10];
    int pid;
    // get inputs
    if (pos_space == -1) {
      memcpy(command, &process[0], len);
      command[len] = '\0';
    } else {
      memcpy(command, &process[0], pos_space);
      command[pos_space] = '\0';
      
      int pid_len = strlen(process) - pos_space;
      char c_pid[pid_len];
      memcpy(c_pid, &process[pos_space + 1], pid_len);
      c_pid[pid_len] = '\0';
      pid = atoi(c_pid);
    }


    // printf("LOG: %s, %d\n", command, pid);
    // printf("%d\n", int(strlen("Create")));
  
    // logic
    if (strcmp(command,"Create") == 0) {
      // pushback into queue
      dispatch.push(pid);
    } else if (strcmp(command, "Tick") == 0) {
      // print the front of the queue and push back onto end
      int tick = dispatch.front();                      // get front
      printf("%d\n", tick);
      dispatch.pop();                                   // remove from front
      dispatch.push(tick);                              // push to back
    } else if (strcmp(command, "Pause") == 0) {
      pause[pid] = true;
    } else if (strcmp(command, "Resume") == 0) {
      pause[pid] = false;
      dispatch.front_push(pid);                        // add to front
    } else {
      printf("LOG mistake\n");  
    }
  }
}