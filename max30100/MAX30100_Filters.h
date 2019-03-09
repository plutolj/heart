#ifndef MAX30100_FILTERS_H
#define MAX30100_FILTERS_H
extern float v[2];

typedef struct 
{
	float alpha;
	float dcw;	
}DCRemover;

float FBstep(float x);
void FilterBuLp(void);
float getDCW(float *dcw);
float step(float x,float *alpha,float *dcw);
void DCRemover1(float alpha_,float *alpha,float *dcw);
void DCRemover_init(float *alpha,float *dcw);

#endif

