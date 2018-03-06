#include <string.h>
#include <spatialindex/capi/sidx_api.h>
/*
API for tssim: an experimenatl code to do research on 
time series similarity search and and its applications.
*/

#define LEN_FNAME 128
#define LEN_TSNAME 64
#define LEN_IDX_DIM 5

/**
 * @brief Identifies the timeseries as a query or 
 * stored.  
 */
enum TSType {STORED, QUERY};

typedef enum { false, true } bool;

/**
 * @brief Represents a single timeseries
 * 
 */
typedef struct TSeries{
    int nelem;
    unsigned long int seed;
    enum TSType type;
    char name[LEN_TSNAME];
    int id;
    bool save;
    // incase of query type
    int pid;
    double* ts;
    double* fs;
    double* (*create)(struct TSeries);
    int (*destroy)(struct TSeries);
    void* (*compress)(struct TSeries);
} TSeries;

/**
 * @brief An umbrella context for timeseries 
 * similarity experiment. we need to see if this
 * makes sense. This is kind of config. for the 
 * experiment. From clean api point of view this 
 * can be reconsidered.  
 */
typedef struct TSSimContext {
    int nts;
    char* prefix;
    TSeries* tss;
    void* (*index)(struct TSSimContext);    
} TSSimContext; 

/* TODO: generate n time series signals and optionally save */
double* ts_gen(TSeries*);

/* TODO: generate a similar time series as input and optionally save */
double* ts_gen_sim(TSeries*, TSeries*);

/* TODO: generate a lagged version of a time series and opt. save */
double* ts_gen_lag(TSeries*, TSeries*, int);   

/* TODO: transform time series given a transform func like dft and optionally compress */
void ts_tfr(TSeries* ts);

/* TODO: index time series */
IndexH ts_index(TSSimContext*);

/* TODO: time series search given a search func e.g. knn */
void ts_search(IndexH, TSeries*);
  
/* TODO: time series lag corr. calc. */
int ts_calc_lag(TSeries*, TSeries*);

/* TODO: build lag graph ?? */
void ts_lag_graph();
  
