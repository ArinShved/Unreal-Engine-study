// LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "Enemy/LMAEnemyClass.h"
#include "Components/LMAHealthComponent.h"

// Sets default values
ALMAEnemyClass::ALMAEnemyClass()
{

	PrimaryActorTick.bCanEverTick = true;
	HealthComponent = CreateDefaultSubobject<ULMAHealthComponent>("HealthComponent");
 	

}

// Called when the game starts or when spawned
void ALMAEnemyClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALMAEnemyClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

