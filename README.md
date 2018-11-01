# PowerUp Offseason
*"Does it compile yet?"*

Raider Robotics' 2018 offseason code. Forked from frc5024/PowerUp.

## Features
 - CameraServer
 - Macros for picking up a cube, and shooting a cube
 - Auto is disabled for saftey reasons. Just use our official PowerUp code if you need auto.

## Deploying to the robot
Make sure you are using the 2019 toolsuite and gradlerio. The run:
```sh
./gradlew deploy
```

You may have to set a team number

## Drive Menu
There is a hidden menu system built into the driver's controller. This can be accessed by holding the right Dpad button while moving the right hand joystick all the way in one of the following directions.

| Joystick Direction | What it Does |
| ------------------ | ------------ |
| Left | Switches to tank drive |
| Right | Switches to arcade drive |
| Up | Switches to cheesy drive |

### TankDrive
WHen the robot is in TankDrive mode, to move the robot, do the following.

The Y axis of the left joystick controls the left set of motors

The Y axis of the right joystick controls the right set of motors

Using a combanation of both, you can drive the robot with extreamly precise movements.

### ArcadeDrive
ArcadeDrive is the default mode that the robot starts in. To use this mode, just move the left joystick, and the robot moves like you are driving in a video game.

### CheesyDrive
When in CheesyDrive mode, the robot operates like ArcadeDrive when navigating with the left joystice. But when using the X axis of the right stick, you can control the curvature of the robot's driving. This is great for making auto look cool and be efficent.

## 1 Player Mode
To switch to 1 player mode, press the dPad up button on the driver's controller. This will do the following:
 - Disable the slow mode macro
 - Remap elevator controls to the driver's bumpers
 - Disable everything except climbing and compressor controls on the operator controller.

## 2 Player Mode
2 player mode is the default mode that the robot starts in. In this mode, all the controls are the same as in competitions. To switch to this mode from 1 player mode, press the left dPad button on the driver's controller.