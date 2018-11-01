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
	delete this->isReverse;
	delete this->driveMode;
	delete this->slowLock;

	return;
}

/**
 *
 */
void DualDrive::Initialize()
{
	LOG("[DualDrive] Initialized");
	this->isReverse = false;
	this->driveMode = 0;
	this->slowLock = false;

	return;
}

/**
 *
 */
void DualDrive::Execute()
{
	// Create "macro" to controller
	frc::XboxController* pJoyDrive = CommandBase::pOI->GetJoystickDrive();
	
	// Check what the bumpers should be used for
	if(pJoyDrive->GetPOV() == 0){ // UP
		this->slowLock = true;
	}else if(pJoyDrive->GetPOV() == 270){ // LEFT
		this->slowLock = false;
	}
	
	// Reverse mode
	
		if (pJoyDrive->GetXButtonReleased())
		{
			this->isReverse = !this->isReverse;
		}
	
	
	// Check if the mode should be switched
	if(pJoyDrive->GetPOV() == 90){
		if(pJoyDrive->GetX(XboxController::kRightHand) <= -0.8){ // Left
			// Tank Drive
			this->driveMode = -1;
		}else if(pJoyDrive->GetX(XboxController::kRightHand) >= 0.8){ // Right (default)
			// ArcadeDrive
			this->driveMode = 0;
		}else if(pJoyDrive->GetY(XboxController::kRightHand) >= 0.8){ // Up
			// Cheesy Drive
			this->driveMode = 1;
		}
		
	}
	
	if(driveMode == -1){
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
		CommandBase::pDriveTrain->TankDrive(lSpeed, rSpeed * -1);
		
		
	}else if(driveMode == 0){

		double xSpeed    = pJoyDrive->GetY(XboxController::kLeftHand);
		double zRotation = pJoyDrive->GetX(XboxController::kLeftHand);
	
		if(!slowLock){
		double dSlow = (pJoyDrive->GetBumper(XboxController::kRightHand)) ? 0.5 : 1;
		}
		
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
	} else if(drivemode == 1){
		
		// Speed
		double xSpeed = pJoyDrive->GetY(XboxController::kLeftHand);
		
		// Curvature
		double rawCurve = pJoyDrive->GetX(XboxController::kRightHand);
		
		// Quick Rotation
		double modCurve = pJoyDrive->GetX(XboxController::kLeftHand);
		
		// Decide what turn mode to use
		if(fabs(modCurve) >= XBOX_DEADZONE_LEFT_JOY){
			bool quickTurn = true;
			double zCurve = modCurve;
		}else{
			bool quickTurn = false;
			double zCurve = rawCurve;
		}
		CommandBase::pDriveTrain->CurvatureDrive(xSpeed, zCurve, quickTurn);
		
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
