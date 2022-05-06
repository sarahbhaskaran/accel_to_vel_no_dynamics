/*
 * accel_to_vel_no_dynamics.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "accel_to_vel_no_dynamics".
 *
 * Model version              : 2.13
 * Simulink Coder version : 9.6 (R2021b) 14-May-2021
 * C++ source code generated on : Fri May  6 00:31:08 2022
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "accel_to_vel_no_dynamics.h"
#include "accel_to_vel_no_dynamics_private.h"

/* Block signals (default storage) */
B_accel_to_vel_no_dynamics_T accel_to_vel_no_dynamics_B;

/* Continuous states */
X_accel_to_vel_no_dynamics_T accel_to_vel_no_dynamics_X;

/* Block states (default storage) */
DW_accel_to_vel_no_dynamics_T accel_to_vel_no_dynamics_DW;

/* Real-time model */
RT_MODEL_accel_to_vel_no_dyna_T accel_to_vel_no_dynamics_M_ =
  RT_MODEL_accel_to_vel_no_dyna_T();
RT_MODEL_accel_to_vel_no_dyna_T *const accel_to_vel_no_dynamics_M =
  &accel_to_vel_no_dynamics_M_;

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = static_cast<ODE3_IntgData *>(rtsiGetSolverData(si));
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 1;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                static_cast<uint_T>(nXc)*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  accel_to_vel_no_dynamics_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  accel_to_vel_no_dynamics_step();
  accel_to_vel_no_dynamics_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  accel_to_vel_no_dynamics_step();
  accel_to_vel_no_dynamics_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void accel_to_vel_no_dynamics_step(void)
{
  SL_Bus_accel_to_vel_no_dynamics_geometry_msgs_Twist rtb_BusAssignment;
  SL_Bus_accel_to_vel_no_dynamics_std_msgs_Float64 b_varargout_2;
  if (rtmIsMajorTimeStep(accel_to_vel_no_dynamics_M)) {
    /* set solver stop time */
    if (!(accel_to_vel_no_dynamics_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&accel_to_vel_no_dynamics_M->solverInfo,
                            ((accel_to_vel_no_dynamics_M->Timing.clockTickH0 + 1)
        * accel_to_vel_no_dynamics_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&accel_to_vel_no_dynamics_M->solverInfo,
                            ((accel_to_vel_no_dynamics_M->Timing.clockTick0 + 1)
        * accel_to_vel_no_dynamics_M->Timing.stepSize0 +
        accel_to_vel_no_dynamics_M->Timing.clockTickH0 *
        accel_to_vel_no_dynamics_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(accel_to_vel_no_dynamics_M)) {
    accel_to_vel_no_dynamics_M->Timing.t[0] = rtsiGetT
      (&accel_to_vel_no_dynamics_M->solverInfo);
  }

  /* BusAssignment: '<Root>/Bus Assignment' incorporates:
   *  Constant: '<S1>/Constant'
   *  TransferFcn: '<Root>/Transfer Fcn3'
   */
  rtb_BusAssignment = accel_to_vel_no_dynamics_P.Constant_Value;
  rtb_BusAssignment.Linear.X = accel_to_vel_no_dynamics_P.TransferFcn3_C *
    accel_to_vel_no_dynamics_X.TransferFcn3_CSTATE;

  /* Outputs for Atomic SubSystem: '<Root>/Publish' */
  /* MATLABSystem: '<S2>/SinkBlock' */
  Pub_accel_to_vel_no_dynamics_33.publish(&rtb_BusAssignment);

  /* End of Outputs for SubSystem: '<Root>/Publish' */
  if (rtmIsMajorTimeStep(accel_to_vel_no_dynamics_M)) {
    boolean_T b_varargout_1;

    /* Outputs for Atomic SubSystem: '<Root>/Subscribe' */
    /* MATLABSystem: '<S3>/SourceBlock' incorporates:
     *  Inport: '<S4>/In1'
     */
    b_varargout_1 = Sub_accel_to_vel_no_dynamics_27.getLatestMessage
      (&b_varargout_2);

    /* Outputs for Enabled SubSystem: '<S3>/Enabled Subsystem' incorporates:
     *  EnablePort: '<S4>/Enable'
     */
    if (b_varargout_1) {
      accel_to_vel_no_dynamics_B.In1 = b_varargout_2;
    }

    /* End of MATLABSystem: '<S3>/SourceBlock' */
    /* End of Outputs for SubSystem: '<S3>/Enabled Subsystem' */
    /* End of Outputs for SubSystem: '<Root>/Subscribe' */

    /* Saturate: '<Root>/Saturation' */
    if (accel_to_vel_no_dynamics_B.In1.Data >
        accel_to_vel_no_dynamics_P.Saturation_UpperSat) {
      /* Saturate: '<Root>/Saturation' */
      accel_to_vel_no_dynamics_B.Saturation =
        accel_to_vel_no_dynamics_P.Saturation_UpperSat;
    } else if (accel_to_vel_no_dynamics_B.In1.Data <
               accel_to_vel_no_dynamics_P.Saturation_LowerSat) {
      /* Saturate: '<Root>/Saturation' */
      accel_to_vel_no_dynamics_B.Saturation =
        accel_to_vel_no_dynamics_P.Saturation_LowerSat;
    } else {
      /* Saturate: '<Root>/Saturation' */
      accel_to_vel_no_dynamics_B.Saturation =
        accel_to_vel_no_dynamics_B.In1.Data;
    }

    /* End of Saturate: '<Root>/Saturation' */
  }

  if (rtmIsMajorTimeStep(accel_to_vel_no_dynamics_M)) {
    rt_ertODEUpdateContinuousStates(&accel_to_vel_no_dynamics_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++accel_to_vel_no_dynamics_M->Timing.clockTick0)) {
      ++accel_to_vel_no_dynamics_M->Timing.clockTickH0;
    }

    accel_to_vel_no_dynamics_M->Timing.t[0] = rtsiGetSolverStopTime
      (&accel_to_vel_no_dynamics_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.05s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.05, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      accel_to_vel_no_dynamics_M->Timing.clockTick1++;
      if (!accel_to_vel_no_dynamics_M->Timing.clockTick1) {
        accel_to_vel_no_dynamics_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void accel_to_vel_no_dynamics_derivatives(void)
{
  XDot_accel_to_vel_no_dynamics_T *_rtXdot;
  _rtXdot = ((XDot_accel_to_vel_no_dynamics_T *)
             accel_to_vel_no_dynamics_M->derivs);

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn3' */
  _rtXdot->TransferFcn3_CSTATE = 0.0;
  _rtXdot->TransferFcn3_CSTATE += accel_to_vel_no_dynamics_P.TransferFcn3_A *
    accel_to_vel_no_dynamics_X.TransferFcn3_CSTATE;
  _rtXdot->TransferFcn3_CSTATE += accel_to_vel_no_dynamics_B.Saturation;
}

/* Model initialize function */
void accel_to_vel_no_dynamics_initialize(void)
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&accel_to_vel_no_dynamics_M->solverInfo,
                          &accel_to_vel_no_dynamics_M->Timing.simTimeStep);
    rtsiSetTPtr(&accel_to_vel_no_dynamics_M->solverInfo, &rtmGetTPtr
                (accel_to_vel_no_dynamics_M));
    rtsiSetStepSizePtr(&accel_to_vel_no_dynamics_M->solverInfo,
                       &accel_to_vel_no_dynamics_M->Timing.stepSize0);
    rtsiSetdXPtr(&accel_to_vel_no_dynamics_M->solverInfo,
                 &accel_to_vel_no_dynamics_M->derivs);
    rtsiSetContStatesPtr(&accel_to_vel_no_dynamics_M->solverInfo, (real_T **)
                         &accel_to_vel_no_dynamics_M->contStates);
    rtsiSetNumContStatesPtr(&accel_to_vel_no_dynamics_M->solverInfo,
      &accel_to_vel_no_dynamics_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&accel_to_vel_no_dynamics_M->solverInfo,
      &accel_to_vel_no_dynamics_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&accel_to_vel_no_dynamics_M->solverInfo,
      &accel_to_vel_no_dynamics_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&accel_to_vel_no_dynamics_M->solverInfo,
      &accel_to_vel_no_dynamics_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&accel_to_vel_no_dynamics_M->solverInfo,
                          (&rtmGetErrorStatus(accel_to_vel_no_dynamics_M)));
    rtsiSetRTModelPtr(&accel_to_vel_no_dynamics_M->solverInfo,
                      accel_to_vel_no_dynamics_M);
  }

  rtsiSetSimTimeStep(&accel_to_vel_no_dynamics_M->solverInfo, MAJOR_TIME_STEP);
  accel_to_vel_no_dynamics_M->intgData.y = accel_to_vel_no_dynamics_M->odeY;
  accel_to_vel_no_dynamics_M->intgData.f[0] = accel_to_vel_no_dynamics_M->odeF[0];
  accel_to_vel_no_dynamics_M->intgData.f[1] = accel_to_vel_no_dynamics_M->odeF[1];
  accel_to_vel_no_dynamics_M->intgData.f[2] = accel_to_vel_no_dynamics_M->odeF[2];
  accel_to_vel_no_dynamics_M->contStates = ((X_accel_to_vel_no_dynamics_T *)
    &accel_to_vel_no_dynamics_X);
  rtsiSetSolverData(&accel_to_vel_no_dynamics_M->solverInfo, static_cast<void *>
                    (&accel_to_vel_no_dynamics_M->intgData));
  rtsiSetSolverName(&accel_to_vel_no_dynamics_M->solverInfo,"ode3");
  rtmSetTPtr(accel_to_vel_no_dynamics_M,
             &accel_to_vel_no_dynamics_M->Timing.tArray[0]);
  accel_to_vel_no_dynamics_M->Timing.stepSize0 = 0.05;

  /* block I/O */
  (void) memset((static_cast<void *>(&accel_to_vel_no_dynamics_B)), 0,
                sizeof(B_accel_to_vel_no_dynamics_T));

  /* states (continuous) */
  {
    (void) memset(static_cast<void *>(&accel_to_vel_no_dynamics_X), 0,
                  sizeof(X_accel_to_vel_no_dynamics_T));
  }

  /* states (dwork) */
  (void) memset(static_cast<void *>(&accel_to_vel_no_dynamics_DW), 0,
                sizeof(DW_accel_to_vel_no_dynamics_T));

  {
    int32_T i;
    char_T b_zeroDelimTopic_0[10];
    char_T b_zeroDelimTopic[6];
    static const char_T tmp[5] = { 'v', '_', 'a', 'c', 't' };

    static const char_T tmp_0[9] = { 'c', 'm', 'd', '_', 'a', 'c', 'c', 'e', 'l'
    };

    /* Start for Atomic SubSystem: '<Root>/Publish' */
    /* Start for MATLABSystem: '<S2>/SinkBlock' */
    accel_to_vel_no_dynamics_DW.obj.matlabCodegenIsDeleted = false;
    accel_to_vel_no_dynamics_DW.objisempty_c = true;
    accel_to_vel_no_dynamics_DW.obj.isInitialized = 1;
    for (i = 0; i < 5; i++) {
      b_zeroDelimTopic[i] = tmp[i];
    }

    b_zeroDelimTopic[5] = '\x00';
    Pub_accel_to_vel_no_dynamics_33.createPublisher(&b_zeroDelimTopic[0], 1);
    accel_to_vel_no_dynamics_DW.obj.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S2>/SinkBlock' */
    /* End of Start for SubSystem: '<Root>/Publish' */

    /* Start for Atomic SubSystem: '<Root>/Subscribe' */
    /* Start for MATLABSystem: '<S3>/SourceBlock' */
    accel_to_vel_no_dynamics_DW.obj_i.matlabCodegenIsDeleted = false;
    accel_to_vel_no_dynamics_DW.objisempty = true;
    accel_to_vel_no_dynamics_DW.obj_i.isInitialized = 1;
    for (i = 0; i < 9; i++) {
      b_zeroDelimTopic_0[i] = tmp_0[i];
    }

    b_zeroDelimTopic_0[9] = '\x00';
    Sub_accel_to_vel_no_dynamics_27.createSubscriber(&b_zeroDelimTopic_0[0], 1);
    accel_to_vel_no_dynamics_DW.obj_i.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S3>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Subscribe' */
  }

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn3' */
  accel_to_vel_no_dynamics_X.TransferFcn3_CSTATE = 0.0;

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subscribe' */
  /* SystemInitialize for Enabled SubSystem: '<S3>/Enabled Subsystem' */
  /* SystemInitialize for Outport: '<S4>/Out1' incorporates:
   *  Inport: '<S4>/In1'
   */
  accel_to_vel_no_dynamics_B.In1 = accel_to_vel_no_dynamics_P.Out1_Y0;

  /* End of SystemInitialize for SubSystem: '<S3>/Enabled Subsystem' */
  /* End of SystemInitialize for SubSystem: '<Root>/Subscribe' */
}

/* Model terminate function */
void accel_to_vel_no_dynamics_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/Publish' */
  /* Terminate for MATLABSystem: '<S2>/SinkBlock' */
  if (!accel_to_vel_no_dynamics_DW.obj.matlabCodegenIsDeleted) {
    accel_to_vel_no_dynamics_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S2>/SinkBlock' */
  /* End of Terminate for SubSystem: '<Root>/Publish' */

  /* Terminate for Atomic SubSystem: '<Root>/Subscribe' */
  /* Terminate for MATLABSystem: '<S3>/SourceBlock' */
  if (!accel_to_vel_no_dynamics_DW.obj_i.matlabCodegenIsDeleted) {
    accel_to_vel_no_dynamics_DW.obj_i.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S3>/SourceBlock' */
  /* End of Terminate for SubSystem: '<Root>/Subscribe' */
}
