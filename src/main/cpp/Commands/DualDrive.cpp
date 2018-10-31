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
		if(pJoyDrive->GetX(XboxController::kRightHand) >= -0.8){
			this->isManual = !this->isManual;
		}
	}
	
	if(isManual){
		// Drive with two joys
		double xSpeed = pJoyDrive->GetY(XboxController::kRightHand);
		double zRotation = pJoyDrive->GetX(XboxController::kLeftHand);
		
		if (fabs(xSpeed) <= XBOX_DEADZONE_LEFT_JOY)
		{
			xSpeed = 0.0;
		}
	
		if (fabs(zRotation) <= XBOX_DEADZONE_LEFT_JOY)
		{
			zRotation = 0.0;
		}
		
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

	}
	CommandBase::pDriveTrain->ArcadeDrive((xSpeed * dSlow * dReverse), (zRotation  * dSlow));

	
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
