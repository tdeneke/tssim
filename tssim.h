/*
API for tssim: an experimenatl code to do research on 
time series similarity search and and its applications.
*/


/* TODO: generate n time series signals and optionally save */
void ts_gen();

/* TODO: generate a similar time series as input and optionally save */
void ts_gen_sim();

/* TODO: generate a lagged version of a time series and opt. save */
void ts_gen_lag();   

/* TODO: transform time series given a transform func like dft and optionally compress */
void ts_tfr();

/* TODO: index time series */
void ts_index();

/* TODO: time series search given a search func e.g. knn */
void ts_search();
  
/* TODO: time series lag corr. calc. */
void ts_calc_lag();

/* TODO: build lag graph ?? */
void ts_lag_graph();
  
