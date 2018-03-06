#include <tssim.h>
#include <stdlib.h>
#include <time.h>

int main() {

  // TODO: move this to an init func?
  TSSimContext* tsctx = (TSSimContext*)malloc(sizeof(TSSimContext));
  tsctx->nts = 100;
  tsctx->tss = (TSeries*)malloc((tsctx->nts)*sizeof(TSeries));

  for (int i=0; i<tsctx->nts; i++){
    (tsctx->tss[i]).nelem = 100;
    (tsctx->tss[i]).seed = i;
    (tsctx->tss[i]).id = i;
    (tsctx->tss[i]).save = true;

    //ts->save = true;
    /* TODO: generate n time series signals and optionally save */
    ts_gen(&tsctx->tss[i]);
    ts_tfr(&tsctx->tss[i]);
  }

  /* TODO: generate a similar time series as input and optionally save */
  // we plan to generate similar ts for every new ts 
  TSeries* tssim = (TSeries*)malloc(sizeof(TSeries));
  tssim->seed = 101;
  tssim->save = true;
  srand(time(NULL));
  tssim->id = rand()%tsctx->nts + 1;
  ts_gen_sim(tssim, &tsctx->tss[tssim->id]);

  // generate a lagged version
  TSeries* tslag = (TSeries*)malloc(sizeof(TSeries));
  tslag->save = true;
  ts_gen_lag(tslag, tssim, 5);
  ts_tfr(tssim);
  ts_tfr(tslag);
 
  /* TODO: generate a lagged version of a time series and opt. save */
  // ts_gen_lag();   

  /* TODO: transform time series given a transform func like dft and optionally compress */
  // ts_tfr(ts);

  /* TODO: index time series */
  IndexH idx = ts_index(tsctx);

  /* TODO: time series search given a search func e.g. knn */
  ts_search(idx, tssim);
  ts_search(idx, tslag);
  
  /* TODO: time series lag corr. calc. */
  ts_calc_lag(tssim, tslag);

  /* TODO: build lag graph ?? */
  // ts_lag_graph();
   
  // TODO: move this to deinit func?
  for(int i=0; i<tsctx->nts; i++){
    free(tsctx->tss[i].ts);
    free(tsctx->tss[i].fs);
  }
  free(tsctx->tss);
  free(tsctx);
  free(tssim->ts);
  free(tssim->fs);
  free(tssim);
  free(tslag->ts);
  free(tslag->fs);
  free(tslag);
  Index_Destroy(idx);

  return(0);
}
