#include <tssim.h>
#include <stdlib.h>

int main() {

  // TODO: move this to an init func?
  TSeries* ts = (TSeries*)malloc(sizeof(TSeries));
  ts->nelem = 100;
  ts->seed = 101;
  ts->save = true;
  /* TODO: generate n time series signals and optionally save */
  ts_gen(ts);

  /* TODO: generate a similar time series as input and optionally save */
  // we plan to generate similar ts for every new ts 
  TSeries* tss = (TSeries*)malloc(sizeof(TSeries));
  tss->seed = 101;
  tss->save = true;
  ts_gen_sim(tss, ts);
  
  /* TODO: generate a lagged version of a time series and opt. save */
  ts_gen_lag();   

  /* TODO: transform time series given a transform func like dft and optionally compress */
  ts_tfr(ts);

  /* TODO: index time series */
  ts_index();

  /* TODO: time series search given a search func e.g. knn */
  ts_search();
  
  /* TODO: time series lag corr. calc. */
  ts_calc_lag();

  /* TODO: build lag graph ?? */
  ts_lag_graph();
   
  // TODO: move this to deinit func?
  free(ts->ts);
  free(ts);
  free(tss->ts);
  free(tss);

 

  return(0);
}
