#include "ControlElevator.h"
#include "../Utilities/Log.h"

/**
 *
 */
ControlElevator::ControlElevator()
{
	LOG("[ControlElevator] Constructed");

	if ( CommandBase::pElevator != nullptr )
	{
		Requires(CommandBase::pElevator);
	}
	else
	{
		LOG("[ControlElevator] elevator is NULL!");
	}

	return;
}

/**
 *
 */
void ControlElevator::Initialize()
{
	LOG("[ControlElevator] Initalized");
	this->bumperMode = false;
	return;
}

/**
 *
 *
 */
void ControlElevator::Execute()
{
	frc::XboxController* pJoyOperator = CommandBase::pOI->GetJoystickOperator();
	frc::XboxController* pJoyDrive = CommandBase::pOI->GetJoystickDrive();
	
	// Check what the bumpers should be used for
	if(pJoyDrive->GetPOV() == 0){ // UP
		this->bumperMode = true;
	}else if(pJoyDrive->GetPOV() == 270){ // LEFT
		this->bumperMode = false;
	}
	
	if(bumperMode){
		if(pJoyDrive->GetBumper(XboxController::kRightHand)){
			double rightOpTriggerAxis = 40.00;
		}else if(pJoyDrive->GetBumper(XboxController::kLeftHand)){
			double leftOpTriggerAxis = 40.00;
		}
	}else{
		double rightOpTriggerAxis = pJoyOperator->GetTriggerAxis(frc::XboxController::kRightHand);
		double leftOpTriggerAxis  = pJoyOperator->GetTriggerAxis(frc::XboxController::kLeftHand);
	}

	double dMotorSpeed = rightOpTriggerAxis - leftOpTriggerAxis;

	if (CommandBase::pElevator->IsTopSwitchAligned() && dMotorSpeed < 0.0)
	{
		dMotorSpeed = 0.0; // don't let the motor go passed the top switch
	}

	if (CommandBase::pElevator->IsBottomSwitchAligned() && dMotorSpeed > 0.0)
	{
		dMotorSpeed = 0.0; // don't let the motor go passed the bottom switch
	}

	CommandBase::pElevator->SetMotorSpeed(dMotorSpeed);

	return;
}

/**
 *
 */
bool ControlElevator::IsFinished()
{
	return false;
}

/**
 *
 */
void ControlElevator::End()
{
	LOG("[ControlElevator] Ended");

	return;
}

/**
 *
 */
void ControlElevator::Interrupted()
{
	LOG("[ControlElevator] Interrupted" );

	return;
}

/**
 *
 */
void ControlElevator::Trace(double dMotorSpeed)
{

	if (iCounter++ == 10)
	{
		SmartDashboard::PutNumber( "Elevator Motorspeed", dMotorSpeed );

		LOG("[ControlElevator] Switch: " << CommandBase::pElevator->IsTopSwitchAligned() << " Speed: " << dMotorSpeed);

		iCounter = 0;
	}

	return;
}
