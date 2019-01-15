#ifndef __c1_car10_23_h__
#define __c1_car10_23_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc1_car10_23InstanceStruct
#define typedef_SFc1_car10_23InstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c1_sfEvent;
  boolean_T c1_doneDoubleBufferReInit;
  uint8_T c1_is_active_c1_car10_23;
  real_T c1_wait_flag;
  boolean_T c1_wait_flag_not_empty;
  real_T c1_steer;
  boolean_T c1_steer_not_empty;
  real_T c1_speed;
  boolean_T c1_speed_not_empty;
  real_T (*c1_str)[3];
  real_T *c1_speed_cmd;
  real_T *c1_steer_cmd;
  uint16_T *c1_len;
} SFc1_car10_23InstanceStruct;

#endif                                 /*typedef_SFc1_car10_23InstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c1_car10_23_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c1_car10_23_get_check_sum(mxArray *plhs[]);
extern void c1_car10_23_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
