// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LMAEnemyClass.generated.h"

class ULMAHealthComponent;
class UBehaviorTree;

UCLASS()
class LEAVEMEALONE_API ALMAEnemyClass : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALMAEnemyClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	ULMAHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;
	
	

};
