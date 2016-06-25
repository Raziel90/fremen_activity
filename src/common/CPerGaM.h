#ifndef CPERGAM_H
#define CPERGAM_H

#include <iostream>
#include <vector>
#include <complex>	
#include <algorithm> 
#include <iterator> 
#include <string.h>
#include "CTimer.h"
#include "CTemporal.h"
	
/**
@author Tom Krajnik
*/

#define MAX_ID_LENGTH 100

using namespace std;

typedef struct
{
	float mean;
	float sigma;
	float weight;
	float *estimate;
	unsigned int frequency;
}SPerGaM;

class CPerGaM: public CTemporal
{
public:
  CPerGaM(const char* id);
  ~CPerGaM();

  //adds a serie of measurements to the data
  int add(uint32_t time,float state);
  void init(int iMaxPeriod,int elements);

  //estimates the probability for the given times - using stored histogram 
  float estimate(uint32_t time);

  //predicts the probability for the given times - using updated histogram 
  float predict(uint32_t time);

  void update(int modelOrder);
  void print(bool verbose=true);

  char id[MAX_ID_LENGTH];
  int save(FILE* file,bool lossy = false);
  int load(FILE* file);
  int save(char* name,bool lossy = false);
  int load(char* name);
  int loadTxt(FILE* file);

  SPerGaM *gaussian;
  float *storedHistogram;
  int offset;
  float gain;
  int numBins; 
};

#endif
