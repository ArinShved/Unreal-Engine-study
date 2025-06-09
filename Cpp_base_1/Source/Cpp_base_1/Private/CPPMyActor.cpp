


#include "CPPMyActor.h"


ACPPMyActor::ACPPMyActor()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	 InitialLocation = GetActorLocation();

}


void ACPPMyActor::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetActorLocation();
	
}

void ACPPMyActor::ShowActorInformation() {
	PlayerName = GetName();
	UE_LOG(LogTemp, Display, TEXT("Player name: %s"), *PlayerName);

	UE_LOG(LogTemp, Display, TEXT("Enemy num: %d"), EnemyCount);

	UE_LOG(LogTemp, Display, TEXT("IsAlive: %d"), isAlive ? 1 : 0);

}


void ACPPMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPPMyActor::SinMovement()
{
	float Time = GetWorld()->GetTimeSeconds();

	float NewZ = InitialLocation.Z + FMath::Sin(Frequency * Time) * Amplitude;

	FVector NewLocation = GetActorLocation();
	NewLocation.Z = NewZ;
	SetActorLocation(NewLocation);
}

