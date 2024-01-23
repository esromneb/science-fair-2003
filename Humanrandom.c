#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>

#define TOPOFRANGE 100
#define NUMOFSEEDS 10000
#define NUMOFGENERATIONS 10000
#define VERBOSE 0


int getmearandomnumber(int, int);
int gettime(void);
int humanseeds[NUMOFSEEDS];


int
main(void)
{
  int i = 0;
  char ch;

  int numbertobetallied;
  int timestart, timeend;
  int rawdata[TOPOFRANGE];
  printf("Enter %d characters of your choice:\n", NUMOFSEEDS);
  for(i = 0; i < NUMOFSEEDS; i++)
    {
      initscr();
      cbreak();
      echo();
      nonl();
      intrflush(stdscr, FALSE);
      timestart = gettime();
      ch = getchar();
      endwin();
      timeend = gettime();
      printf("%3d", NUMOFSEEDS - i - 2);
      humanseeds[i] = timeend - timestart;
    }
  if(VERBOSE)
    {
      for(i = 1; i <= NUMOFSEEDS; i++)
	{
	  printf("Seed %3d = %d\n", i, humanseeds[i]);
	}
    }
  //init loop that sets all values to 0
  for(i = 0; i < TOPOFRANGE; i++)
    {
      rawdata[i] = 0;
    }
  for(i = 0; i < NUMOFGENERATIONS; i++)
    {
      numbertobetallied =  getmearandomnumber(0,TOPOFRANGE);
      rawdata[numbertobetallied]++;
    }
  printf("\n\n\n");
  for(i = 0; i < TOPOFRANGE; i++)
    {
      printf("%d\n", rawdata[i]);
    }


 
    //printf( "%d seconds, %d microseconds\n", tv.tv_sec, tv.tv_usec);
  return 0;
}

int gettime(void)
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  char buff[20];
  sprintf(buff, "%.0f",  (tv.tv_sec + (tv.tv_usec / 1000000.0))*1000000);
  int i;
  int j = 1;
  int reduced = 0;
  int lenofbuff;
  char ch;
  lenofbuff = strlen(buff);
  for(i = lenofbuff - 1; i >= (lenofbuff - 9); i--)
    {
      ch = buff[i];
      reduced += atoi(&ch) * j;
      j *= 10;
    }
  return reduced;
}


int
getmearandomnumber(int min, int max)
{
  static int timesrun;
  static int seeded;
  //unsigned long int test;
  timesrun++;
  if(timesrun % (NUMOFGENERATIONS / NUMOFSEEDS) == 0) 
  {
    seeded = 0;
    if(VERBOSE)
      {
	printf("SEEDING!!!!\n");
      }
  }									
     if(seeded == 0)							
  {									
    seeded = 1;
    if(VERBOSE)
      {
	int randomseed = gettime();
	srandom((unsigned int) randomseed);
	printf("Seeding on = randomseed");
      }
    srandom((unsigned int) gettime());   
  }
     return (max - min + 1.0) * (random() % RAND_MAX) / (RAND_MAX + 1.0) + min;
     
}