#include <tssim.h>
#include <stdlib.h>

int main() {

  // TODO: move this to an init func?
  TSeries* ts = (TSeries*)malloc(sizeof(TSeries));
  ts->name = "ts";
  ts->nelem = 100;
  ts->seed = 101;
  
  /* TODO: generate n time series signals and optionally save */
  ts_gen(ts);

  // TODO: move this to deinit func?
  free(ts->ts);
  free(ts);

  /* TODO: generate a similar time series as input and optionally save */
  ts_gen_sim();

  /* TODO: generate a lagged version of a time series and opt. save */
  ts_gen_lag();   

  /* TODO: transform time series given a transform func like dft and optionally compress */
  ts_tfr();

  /* TODO: index time series */
  ts_index();

  /* TODO: time series search given a search func e.g. knn */
  ts_search();
  
  /* TODO: time series lag corr. calc. */
  ts_calc_lag();

  /* TODO: build lag graph ?? */
  ts_lag_graph();
  

  return(0);
}
