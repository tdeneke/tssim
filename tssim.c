/* API implementation for tssim */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tssim.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_fft_real.h>
#include <gsl/gsl_fft_halfcomplex.h>
#include <spatialindex/capi/sidx_api.h>
#include <time.h>
#include <math.h>

/* TODO: generate n time series signals and optionally save */
double* ts_gen(TSeries* ts){
  printf("inside ts_gen\n");
  int res = sprintf (ts->name, "%lu-%d", (unsigned long)(time(NULL)/86400),ts->id);
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
  // TODO: move this type of save blocks to own func.
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
double* ts_gen_sim(TSeries* ots, TSeries* its){
  printf("inside ts_gen_sim\n");
  ots->nelem = its->nelem;
  strcpy(ots->name, its->name);
  double* elems = (double*)malloc((ots->nelem)*sizeof(double));

  // fill output with input plus a small random noise
  const gsl_rng_type * T;
  gsl_rng * r;
  gsl_rng_env_setup();
  T = gsl_rng_default;
  r = gsl_rng_alloc (T);
  gsl_rng_set(r, ots->seed);
  double rnd = 0.0;
  for(int i=0; i<ots->nelem; i++){
    rnd = 0.05 * gsl_ran_flat(r, -500.0, 500.0);
    elems[i] = its->ts[i] + rnd;
    printf("elem[%d]: %f and rand: %f\n", i, elems[i], rnd);
  }
  gsl_rng_free (r);
  ots->ts = elems;

  // save to disk if required
  // TODO: move this type of save blocks to own func.
  char fname[LEN_FNAME];
  strcpy(fname, "./db/");
  strcat(fname, ots->name);
  strcat(fname, "-sim");  
  FILE* pf = fopen(fname, "w");
  if(ots->save == true && pf != NULL){
    for(int i=0; i<ots->nelem; i++){
    	fprintf(pf, "%f\n", ots->ts[i]);
    }
    fclose(pf);
  }

  return elems;
}

/* TODO: generate a lagged version of a time series and opt. save */
double* ts_gen_lag(TSeries* ots, TSeries* its, int lag){
  printf("inside ts_gen_lag\n");
  ots->nelem = its->nelem;
  // ots->seed = its->seed;
  ots->id = its->id;
  strcpy(ots->name, its->name);
  double* elems = (double*)malloc((ots->nelem)*sizeof(double));

  // pad the initial elements
  for(int i=0; i<lag; i++){
    elems[i] = 0;
  }
  for(int i=lag; i<ots->nelem; i++){
    elems[i] = its->ts[i-lag];
  }
  ots->ts = elems;

  // save to disk if required
  // TODO: move this type of save blocks to own func.
  char fname[LEN_FNAME];
  strcpy(fname, "./db/");
  strcat(fname, ots->name);
  strcat(fname, "-lag");  
  FILE* pf = fopen(fname, "w");
  if(ots->save == true && pf != NULL){
    for(int i=0; i<ots->nelem; i++){
    	fprintf(pf, "%f\n", ots->ts[i]);
    }
    fclose(pf);
  } 

  return elems;
}   

/* TODO: transform time series given a transform func like dft and optionally compress */
void ts_tfr(TSeries* ts){
  printf("inside ts_tfr \n");
  gsl_fft_real_wavetable * real;
  gsl_fft_real_workspace * work;

  work = gsl_fft_real_workspace_alloc (ts->nelem);
  real = gsl_fft_real_wavetable_alloc (ts->nelem);

  ts->fs = (double*)malloc((ts->nelem)*sizeof(double));
  for(int i=0; i<ts->nelem; i++){
    ts->fs[i] = ts->ts[i];
  }
  gsl_fft_real_transform (ts->fs, 1, ts->nelem, real, work);
  gsl_fft_real_wavetable_free (real);

  // just a test
  /* gsl_fft_halfcomplex_wavetable * hc;
  hc = gsl_fft_halfcomplex_wavetable_alloc (ts->nelem);

  for(int i = 11; i < ts->nelem; i++){
      ts->fs[i] = 0;
  }
  gsl_fft_halfcomplex_inverse (ts->fs, 1, ts->nelem, hc, work);
  gsl_fft_halfcomplex_wavetable_free (hc);

  FILE* pf = fopen("./db/idft.txt", "w");
  for (int i = 0; i < ts->nelem; i++){
      fprintf(pf, "%f\n", ts->fs[i]);
  }
  fclose(pf);
  */
  
  gsl_fft_real_workspace_free (work);
  return;
}

/* TODO: index time series */
IndexH ts_index(TSSimContext* tsctx){
  printf("inside ts_index \n");
  IndexPropertyH props = IndexProperty_Create();
   
   // create an in-memory r*-tree index
   IndexProperty_SetIndexType(props, RT_RTree);
   IndexProperty_SetDimension(props, LEN_IDX_DIM);
   IndexProperty_SetIndexStorage(props, RT_Memory);
   IndexH idx = Index_Create(props);
   IndexProperty_Destroy(props);
   
   if (Index_IsValid(idx))
   {   
     for(int i=0; i<tsctx->nts; i++){
      Index_InsertData(idx, tsctx->tss[i].id, tsctx->tss[i].fs, tsctx->tss[i].fs, 5, 0, 0);
     }
   }
   else
   {   
       printf("Failed to create valid index\n");
   }

  return idx;
}

/* TODO: time series search given a search func e.g. knn */
void ts_search(IndexH idx, TSeries* tssim){
  printf("inside ts_search \n");
  uint64_t nResults = 2;
  int64_t* ids;
  Index_NearestNeighbors_id(idx, tssim->fs, tssim->fs, 5, &ids, &nResults);
  if(nResults>0)
    printf("nResults is: %ld\nId of the most sim. is: %ld\nquery ts index is: %d\n", nResults, ids[0], tssim->id);
  return;
}
  
/* TODO: time series lag corr. calc. */
int ts_calc_lag(TSeries* ts1, TSeries* ts2){
  printf("inside ts_calc_lag \n");

  double corr = 0, maxcorr=0; 
  int lag = 0;
  double sum_tslag, sum_ts2, sum_tslagts2;
  double squareSum_tslag, squareSum_ts2;
  
  for (int j = 0; j < ts1->nelem; j++){
    TSeries* tslag = (TSeries*)malloc(sizeof(TSeries));
    tslag->save = false;
    ts_gen_lag(tslag, ts1, j);

    sum_tslag = 0, sum_ts2 = 0, sum_tslagts2 = 0;
    squareSum_tslag = 0, squareSum_ts2 = 0; 
    for (int i = 0; i < ts1->nelem; i++){
      // sum of elements of array tslag.
      sum_tslag = sum_tslag + tslag->ts[i];
 
      // sum of elements of array ts2.
      sum_ts2 = sum_ts2 + ts2->ts[i];
 
      // sum of tslag[i] * ts2[i].
      sum_tslagts2 = sum_tslagts2 + tslag->ts[i] * ts2->ts[i];
 
      // sum of square of array elements.
      squareSum_tslag = squareSum_tslag + tslag->ts[i] * tslag->ts[i];
      squareSum_ts2 = squareSum_ts2 + ts2->ts[i] * ts2->ts[i];
    }
 
    // use formula for calculating correlation coefficient.
    corr = (ts1->nelem * sum_tslagts2 - sum_tslag * sum_ts2) 
                / sqrt((ts1->nelem * squareSum_tslag - sum_tslag * sum_tslag) 
                      * (ts1->nelem * squareSum_ts2 - sum_ts2 * sum_ts2));
     
    printf("lag is: %d and corr is: %f\n", lag, corr);
    if(corr > maxcorr){
      maxcorr = corr;
      lag = j;
    }
    
    free(tslag->ts);
    // free(tslag->fs);
    free(tslag);
  }

  printf("lag is: %d\n", lag);

  return lag;
}

/* TODO: build lag graph ?? */
void ts_lag_graph(){
  printf("inside ts_lag_graph \n");
  return;
}
 
