#include <stdio.h>
#include <stdlib.h>
#include "problem1_2s.h"
#include "problem1_2s_private.h"
#include "rtwtypes.h"
#include "limits.h"
#include "rt_nonfinite.h"
#include "MW_raspi_init.h"
#include "MW_Pyserver_control.h"
#include "linuxinitialize.h"
#define UNUSED(x)                      x = x
#define NAMELEN                        16

/* Function prototype declaration*/
void exitFcn(int sig);
void *terminateTask(void *arg);
void *baseRateTask(void *arg);
void *subrateTask(void *arg);
volatile boolean_T stopRequested = false;
volatile boolean_T runModel = true;
sem_t stopSem;
sem_t baserateTaskSem;
pthread_t schedulerThread;
pthread_t baseRateThread;
void *threadJoinStatus;
int terminatingmodel = 0;
void *baseRateTask(void *arg)
{
  runModel = (rtmGetErrorStatus(problem1_2s_M) == (NULL)) &&
    !rtmGetStopRequested(problem1_2s_M);
  while (runModel) {
    sem_wait(&baserateTaskSem);

    /* External mode */
    {
      boolean_T rtmStopReq = false;
      rtExtModePauseIfNeeded(problem1_2s_M->extModeInfo, 2, &rtmStopReq);
      if (rtmStopReq) {
        rtmSetStopRequested(problem1_2s_M, true);
      }

      if (rtmGetStopRequested(problem1_2s_M) == true) {
        rtmSetErrorStatus(problem1_2s_M, "Simulation finished");
        break;
      }
    }

    /* External mode */
    {
      boolean_T rtmStopReq = false;
      rtExtModeOneStep(problem1_2s_M->extModeInfo, 2, &rtmStopReq);
      if (rtmStopReq) {
        rtmSetStopRequested(problem1_2s_M, true);
      }
    }

    problem1_2s_step();

    /* Get model outputs here */
    rtExtModeCheckEndTrigger();
    stopRequested = !((rtmGetErrorStatus(problem1_2s_M) == (NULL)) &&
                      !rtmGetStopRequested(problem1_2s_M));
    runModel = !stopRequested;
  }

  runModel = 0;
  terminateTask(arg);
  pthread_exit((void *)0);
  return NULL;
}

void exitFcn(int sig)
{
  UNUSED(sig);
  rtmSetErrorStatus(problem1_2s_M, "stopping the model");
  runModel = 0;
}

void *terminateTask(void *arg)
{
  UNUSED(arg);
  terminatingmodel = 1;

  {
    runModel = 0;
  }

  MW_killPyserver();
  mwRaspiTerminate();

  /* Disable rt_OneStep() here */

  /* Terminate model */
  problem1_2s_terminate();
  rtExtModeShutdown(2);
  sem_post(&stopSem);
  return NULL;
}

int main(int argc, char **argv)
{
  UNUSED(argc);
  UNUSED(argv);
  mwRaspiInit();
  MW_launchPyserver();
  rtmSetErrorStatus(problem1_2s_M, 0);
  rtExtModeParseArgs(argc, (const char_T **)argv, NULL);

  /* Initialize model */
  problem1_2s_initialize();

  /* External mode */
  rtSetTFinalForExtMode(&rtmGetTFinal(problem1_2s_M));
  rtExtModeCheckInit(2);

  {
    boolean_T rtmStopReq = false;
    rtExtModeWaitForStartPkt(problem1_2s_M->extModeInfo, 2, &rtmStopReq);
    if (rtmStopReq) {
      rtmSetStopRequested(problem1_2s_M, true);
    }
  }

  rtERTExtModeStartMsg();

  /* Call RTOS Initialization function */
  myRTOSInit(0.001, 0);

  /* Wait for stop semaphore */
  sem_wait(&stopSem);

#if (MW_NUMBER_TIMER_DRIVEN_TASKS > 0)

  {
    int i;
    for (i=0; i < MW_NUMBER_TIMER_DRIVEN_TASKS; i++) {
      CHECK_STATUS(sem_destroy(&timerTaskSem[i]), 0, "sem_destroy");
    }
  }

#endif

  return 0;
}
