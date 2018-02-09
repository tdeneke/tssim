#include <tssim.h>

int main() {
  /* TODO: generate n time series signals and optionally save */
  ts_gen();

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
