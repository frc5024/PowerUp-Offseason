#ifndef _DualDrive_HG_
#define _DualDrive_HG_

#include <WPILib.h>
#include "../CommandBase.h"



class DualDrive: public CommandBase
{
public:
	DualDrive();
	~DualDrive();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	StaticTurn* pStaticTurn;
	bool isReverse;
	bool slowLock;
	
	int driveMode; //!< Weather or not manual override is enabled
	// bool isCurve; //!< Weather or not cheesy drive is enabled
	
};

#endif
