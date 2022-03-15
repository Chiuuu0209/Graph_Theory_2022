#include <iostream>
#include <time.h>

using namespace std;

// for calculating the execution time of this program
struct timespec diff(struct timespec start, struct timespec end) {
  struct timespec temp;
  if ((end.tv_nsec-start.tv_nsec)<0) {
    temp.tv_sec = end.tv_sec-start.tv_sec-1;
    temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
  } else {
    temp.tv_sec = end.tv_sec-start.tv_sec;
    temp.tv_nsec = end.tv_nsec-start.tv_nsec;
  }
  return temp;
}

int main(int argc, char *argv[]){
  // to calculate the total execution time of one case
  struct timespec time_start, time_end;
  double time_used_total;
  clock_gettime(CLOCK_MONOTONIC, &time_start);

  struct timespec time_sub_1, time_sub_2;
  double time_used_sub;

  unsigned int n = 0;

  while(n < 10){
    // to calculate the execution time
    clock_gettime(CLOCK_MONOTONIC, &time_sub_1);

    cout << "The value of variable n is now: " << n << endl;

    // to calculate the execution time of graph
    clock_gettime(CLOCK_MONOTONIC, &time_sub_2);
    struct timespec temp = diff(time_sub_1, time_sub_2);
    time_used_sub = temp.tv_sec + (double) temp.tv_nsec / 1000000.0;
    cout << "The program execution time of this case is: " << time_used_sub << "ms" << endl;
    cout << "-----------------------------------------------------" << endl;
    n++;
  }
  
  // to calculate the total execution time
  cout << endl;
  clock_gettime(CLOCK_MONOTONIC, &time_end);
  struct timespec temp = diff(time_start, time_end);
  time_used_total = temp.tv_sec + (double) temp.tv_nsec / 1000000.0;
  cout << "The program execution time of this program is: " << time_used_total << "ms" << endl;

  return 0;
}
