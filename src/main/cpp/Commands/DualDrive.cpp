#include "DualDrive.h"
#include "../Utilities/Log.h"
#include <math.h>
#include "../RobotMap.h"

/**
 *
 */
DualDrive::DualDrive()
{
	LOG("[DualDrive] Constructed");

	if (CommandBase::pDriveTrain != nullptr)
	{
		Requires(CommandBase::pDriveTrain);
	}
	else
	{
		LOG("[DualDrive] driveTrain is null!");
	}


	return;
}

/**
 *
 */
DualDrive::~DualDrive()
{
	LOG("[DualDrive] Destroyed");


	return;
}

/**
 *
 */
void DualDrive::Initialize()
{
	LOG("[DualDrive] Initialized");
	this->isReverse = false;
	this->isManual = false;

	return;
}

/**
 *
 */
void DualDrive::Execute()
{
	// Create "macro" to controller
	frc::XboxController* pJoyDrive = CommandBase::pOI->GetJoystickDrive();

	// Reverse mode
	if (pJoyDrive->GetXButtonReleased())
	{
		this->isReverse = !this->isReverse;
	}
	
	// Check if the mode should be switched
	if(pJoyDrive->GetPOV() == 90){
		if(pJoyDrive->GetX(XboxController::kRightHand) <= -0.8){
			this->isManual = true;
		}else if(pJoyDrive->GetX(XboxController::kRightHand) >= 0.8){
			this->isManual = true;
		}
	}
	
	if(isManual){
		// Drive with two joys
		// Takes raw data into the motors
		double rSpeed = pJoyDrive->GetY(XboxController::kRightHand);
		double lSpeed = pJoyDrive->GetY(XboxController::kLeftHand);
		
		if (fabs(rSpeed) <= XBOX_DEADZONE_LEFT_JOY)
		{
			rSpeed = 0.0;
		}
	
		if (fabs(lSpeed) <= XBOX_DEADZONE_LEFT_JOY)
		{
			lSpeed = 0.0;
		}
		// Use TankDrive to control each motor set
		CommandBase::pDriveTrain->TankDrive(lSpeed, rSpeed);
		
		
	}else{

		double xSpeed    = pJoyDrive->GetY(XboxController::kLeftHand);
		double zRotation = pJoyDrive->GetX(XboxController::kLeftHand);
	
		double dSlow = (pJoyDrive->GetBumper(XboxController::kRightHand)) ? 0.5 : 1;
		double dReverse = (this->isReverse) ? -1 : 1;
	
		if (fabs(xSpeed) <= XBOX_DEADZONE_LEFT_JOY)
		{
			xSpeed = 0.0;
		}
	
		if (fabs(zRotation) <= XBOX_DEADZONE_LEFT_JOY)
		{
			zRotation = 0.0;
		}
		CommandBase::pDriveTrain->ArcadeDrive((xSpeed * dSlow * dReverse), (zRotation  * dSlow));
	}
	

	
	return;
}

/**
 *
 */
bool DualDrive::IsFinished()
{
	return false;
}

/**
 *
 */
void DualDrive::End()
{
	return;
}

/**
 *
 */
void DualDrive::Interrupted()
{
	return;
}
