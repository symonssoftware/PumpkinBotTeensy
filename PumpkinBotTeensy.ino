/**************************************************************
   DFRobot
 **************************************************************/
#include <Arduino.h>
#include <TeensyThreads.h>

static const int ROBOT_STATE_DISABLED = 0;
static const int ROBOT_STATE_TELEOP_ENABLED = 1;
static const int ROBOT_STATE_AUTONOMOUS_ENABLED = 2;

int robotState = ROBOT_STATE_DISABLED;

/**************************************************************
   setup()
 **************************************************************/
void setup()
{
  //Serial.begin(9600);

  ros2HandlerSetup();
  motorControlSetup();
  controllerHandlingSetup();
  imuSetup();

  threads.addThread(ros2HandlerLoop);
}

/**************************************************************
   loop()
 **************************************************************/
void loop()
{  
  switch (robotState)
  {
    case ROBOT_STATE_DISABLED:
      imuLoop();
      stopMotors();
      break;

    case ROBOT_STATE_TELEOP_ENABLED:
      imuLoop();
      controllerHandlingLoop();
      break;

    case ROBOT_STATE_AUTONOMOUS_ENABLED:
      imuLoop();
      break;

    default:
      stopMotors();
  }
}