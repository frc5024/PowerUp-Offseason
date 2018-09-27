#include "ControlIntake.h"
#include "../SubSystems/IntakeMap.h"
#include "../Utilities/Log.h"
#include <math.h>
#include "../RobotMap.h"

/**
 *
 */
ControlIntake::ControlIntake()
{
	LOG("[ControlIntake] Constructed");

	if ( CommandBase::pIntake != nullptr )
	{
		Requires(CommandBase::pIntake);
	}
	else
	{
		LOG("[ControlIntake] intake is NULL!");
	}

	return;
}

/**
 *
 */
void ControlIntake::Initialize()
{
	LOG("[ControlIntake] Initialize");

	return;
}

/**
 *
 */
void ControlIntake::Execute()
{
	frc::XboxController* pJoyDrive = CommandBase::pOI->GetJoystickDrive();

	double dInSpeed  = pJoyDrive->GetTriggerAxis(frc::XboxController::kLeftHand);
	double dOutSpeed = pJoyDrive->GetTriggerAxis(frc::XboxController::kRightHand);
	
	// Auto Cube Up Control
	if(pJoyDrive->GetYButton()){
		// Set intake speed
		dOutSpeed = CUBEUP_INTAKE_SLOW;
		dInSpeed = 0.0;
		
		// Open Grippers
		CommandBase::pIntake->OpenGripper();
	} else if(pJoyDrive->GetYButtonReleased()) {
		// Set intake speed
		dOutSpeed = CUBEUP_INTAKE_FAST;
		dInSpeed = 0.0;
		
		// Close Grippers
		CommandBase::pIntake->CloseGripper();
	} else if(pJoyDrive->GetBumper(frc::XboxController::kLeftHand)){ // Make sure you cant intake and output at the same time
		// Set intake speed
		dOutSpeed = 0.0;
		dInSpeed = CUBEUP_OUTPUT_SPEED;
	} else if(pJoyDrive->GetBumperReleased(frc::XboxController::kLeftHand)){
		CommandBase::pIntake->OpenGripper();
	}
	
	
	double dSpeed = (dInSpeed - dOutSpeed) * GRIPPER_SPEED_ADJUSTMENT_RATIO;
	CommandBase::pIntake->SetSpeed(dSpeed);

	if (pJoyDrive->GetAButton())
	{
		CommandBase::pIntake->CloseGripper();
	}
	else if ( pJoyDrive->GetBButton() )
	{
		CommandBase::pIntake->OpenGripper();
	}

	return;
}

/**
 *
 */
bool ControlIntake::IsFinished()
{
	return false;
}

/**
 *
 */
void ControlIntake::End()
{
	LOG("[ControlIntake] Ended");

	return;
}

/**
 *
 */
void ControlIntake::Interrupted()
{
	LOG("[ControlIntake] Interrupted");

	return;
}
