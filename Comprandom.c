#include <stdio.h>
#define VERBOSE 0
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <limits.h>
#include <string.h>

#define TOPOFRANGE 100
#define NUMOFSEEDS 10000
#define NUMOFGENERATIONS 10000

int getmearandomnumber(int, int);
bool string2int(char* digit, unsigned long long int& result);
int gettime(void);

int
main (void)
{
  int i;
  int numbertobetallied;
  int rawdata[TOPOFRANGE];

  int starttime, endtime = 0;

  //init loop that sets all values to 0
  for(i = 0; i < TOPOFRANGE; i++)
    {
      rawdata[i] = 0;
    }
  starttime = gettime();
  //this is the counting loop
  for(i = 0; i < NUMOFGENERATIONS; i++)
    {
      numbertobetallied =  getmearandomnumber(0,TOPOFRANGE);
      rawdata[numbertobetallied]++;
    }
  endtime = gettime();
  for(i = 0; i < TOPOFRANGE; i++)
    {
      printf("%d\n", rawdata[i]);
    }
  if(VERBOSE)
    {
      printf("starttime  = %d\nendtime    = %d\ndifference = %.9d\n", starttime, endtime, endtime - starttime);
    }
    return(0);
}


/*Get me a random number accepts
 *int values of the minimum value and
 *maximum values to be returned
 */
int
getmearandomnumber(int min, int max)
{
  static int timesrun;
  static int seeded;
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