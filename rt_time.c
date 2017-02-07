#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include "rt_time.h"
#include <iostream>
#define maxsize 2000
#define BILLION  1000000000L;
#define SEC     0
#define MILLI   1
#define MICRO   2
#define NANO    3
using namespace std;


struct  periodique
{
   double period;
   double deadline;
} ;



timespec timespec_add(const timespec *a, const timespec *b)
{
    timespec s;
    s.tv_nsec = a->tv_nsec + b->tv_nsec;
    s.tv_sec = a->tv_sec + b->tv_sec;
    while (s.tv_nsec >= 1000000000) {
    s.tv_nsec = s.tv_nsec - 1000000000;
    s.tv_sec += 1;
    }
    return s;
}


int timespec_cmp(const timespec *a, const timespec *b)
{
    if (a->tv_sec > b->tv_sec) return 1;
    else if (a->tv_sec < b->tv_sec) return -1;
    else if (a->tv_sec == b->tv_sec) {
    if (a->tv_nsec > b->tv_nsec) return 1;
    else if (a->tv_nsec == b->tv_nsec) return 0;
    else return -1;
    }
    return 0;
}


timespec timespec_sub(const timespec *a, const timespec *b)
{
    timespec d;

    d.tv_nsec = a->tv_nsec - b->tv_nsec;
    d.tv_sec =  a->tv_sec - b->tv_sec;
    if (a->tv_nsec < b->tv_nsec) {
    d.tv_nsec += 1000000000;
    d.tv_sec -= 1;
    }
    return d;//timespec_to(&d, unit);
}

struct unit_conv {
    long mul;
    long div;
    long add;
    long sub;
};

const struct unit_conv conv_table[] = {
    {1, 1000000000},  // SEC
    {1000, 1000000},  // MILLI
    {1000000, 1000},  // MICRO
    {1000000000, 1}   // NANO
};


struct timespec ms_tospec(double x)
{
  struct timespec  tp;
  tp.tv_sec = (int)(x/1000);
  tp.tv_nsec = (x-tp.tv_sec)*1000000 ;
  return tp;
}
double spec_toms(struct timespec x)
{
  return x.tv_sec * 1000+x.tv_nsec / 1000000;
}

//MÃ©thode main


int main(int argc, char const *argv[])
{

struct periodique cp={100,40};
struct timespec Begin;
struct timespec End;
struct timespec Period;
struct timespec Deadline ;

	long tab1 [maxsize] ; // = [maxsize];
	long tab2 [maxsize] ; // = [maxsize];
	long tab3 [maxsize] ; // = [maxsize];

  int j;


  int m=200;
        int i=0,c=0,d=0,k=0,sum=0;
        int first[m][m], second[m][m], multiply[m][m];
        for (c = 0; c < m; c++)
                for (d = 0; d < m; d++)
                {
                        first[c][d]=c*d+5;
                        second[d][c]=c+d+5;
                }

   //int MissedDeadlines = 0 ;
  i=0;
  int MissedDeadlines = 0 ;

  while(i<10){
    //
    clock_gettime(CLOCK_REALTIME, &Begin);

    struct timespec period_timespec = ms_tospec(cp.period);
    struct timespec NextActivation = timespec_add(&Begin,&period_timespec);

    struct timespec deadline_timespec = ms_tospec(cp.deadline);
    struct timespec Dij= timespec_add(&Begin,&deadline_timespec);


      // The real-time processing




         for (c = 0; c < m; c++) {
                                for (d = 0; d < m; d++) {
                                        for (k = 0; k < m; k++) {
                                                sum = sum + first[c][k]*second[k][d];
                                        }
                                        multiply[c][d] = sum;
                                        sum = 0;
                                }
                        }



    clock_gettime(CLOCK_REALTIME, &End);
    struct  timespec responseTime= timespec_sub(&End,&Begin);
    cout<<i<<"\t"<<spec_toms(responseTime)<<endl;
  //clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &NextActivation, NULL);
  //clock_nanosleep(CLOCK_REALTIME, 0, &TimeSleep, NULL);

  // vérifier si le deadligne est raté ou non plus ?!!

  int DR =timespec_cmp(&Dij,&End);
   {
     if(DR == 1)
     MissedDeadlines +=1;
    clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &NextActivation, NULL);

   }
    i++;
}


        printf("deadline raté est : ");
        cout<<"\t"<<MissedDeadlines<<endl;
  return 0;
}
