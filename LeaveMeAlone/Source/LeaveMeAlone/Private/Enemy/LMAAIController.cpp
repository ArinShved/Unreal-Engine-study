// LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "Enemy/LMAAIController.h"
#include "Enemy/LMAEnemyClass.h"


void ALMAAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	const auto AICharacter = Cast<ALMAEnemyClass>(InPawn);
	if (AICharacter)
	{
		RunBehaviorTree(AICharacter->BehaviorTreeAsset);
	}
}