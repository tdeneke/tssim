/* API implementation for tssim */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tssim.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <time.h>

/* TODO: generate n time series signals and optionally save */
double* ts_gen(TSeries* ts){
  printf("inside ts_gen\n");
  int res = sprintf (ts->name, "%lu-%d", (unsigned long)time(NULL),ts->id);
  printf("nts: %d, fname_prefix: %s\n", ts->nelem, ts->name);
  double* elems = (double*)malloc((ts->nelem)*sizeof(double));
  
  // fill ts using random walk
  const gsl_rng_type * T;
  gsl_rng * r;
  gsl_rng_env_setup();
  T = gsl_rng_default;
  // T = gsl_rng_mt19937_1998;
  r = gsl_rng_alloc (T);
  gsl_rng_set(r, ts->seed);
  double sum = 0.0;
  double rnd = 0.0;
  for(int i=0; i<ts->nelem; i++){
    rnd = gsl_ran_flat(r, -500.0, 500.0);
    elems[i] = sum + rnd;
    sum = elems[i];
    printf("elem[%d]: %f and rand: %f\n", i, elems[i], rnd);
  }
  gsl_rng_free (r);
  ts->ts = elems;

  // save to disk if required
  char fname[LEN_FNAME];
  strcpy(fname, "./db/");
  strcat(fname, ts->name);  
  FILE* pf = fopen(fname, "w");
  if(ts->save == true && pf != NULL){
    for(int i=0; i<ts->nelem; i++){
    	fprintf(pf, "%f\n", ts->ts[i]);
    }
    fclose(pf);
  } 
  return elems;
}

/* TODO: generate a similar time series as input and optionally save */
double* ts_gen_sim(TSeries* its, TSeries* ots){
  printf("inside ts_gen_sim\n");
    
  return ots->ts;
}

/* TODO: generate a lagged version of a time series and opt. save */
void ts_gen_lag(){
  printf("inside ts_gen_lag\n");
  return;
}   

/* TODO: transform time series given a transform func like dft and optionally compress */
void ts_tfr(){
  printf("inside ts_tfr \n");
  return;
}

/* TODO: index time series */
void ts_index(){
  printf("inside ts_index \n");
  return;
}

/* TODO: time series search given a search func e.g. knn */
void ts_search(){
  printf("inside ts_search \n");
  return;
}
  
/* TODO: time series lag corr. calc. */
void ts_calc_lag(){
  printf("inside ts_calc_lag \n");
  return;
}

/* TODO: build lag graph ?? */
void ts_lag_graph(){
  printf("inside ts_lag_graph \n");
  return;
}
 
