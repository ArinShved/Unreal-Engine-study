// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPHubActor.h"
#include "TimerManager.h"
#include "CPPMyActor.h"


// Sets default values
ACPPHubActor::ACPPHubActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPPHubActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPPHubActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPPHubActor::OnTimeToSpawn()
{
	if (++CurrentTimerCount <= TotalCount)
	{
		const FVector Location = GetActorLocation() + FVector(FMath::FRandRange(200.0f, 1000.0f), FMath::FRandRange(200.0f, 1000.0f), 0.0f);
		const FRotator Rotation = FRotator::ZeroRotator;
		ACPPMyActor* SpawnObject = GetWorld()->SpawnActor<ACPPMyActor>(CppClass, Location, Rotation);
		if (SpawnObject)
		{
			SpawnedObjects.Add(SpawnObject);
		}
	}
	else
	{
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
		for (int i = TotalCount; i >= 1; --i)
		{
			GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &ACPPHubActor::OnTimeToDestroy, DestroyTimerRate, true);
		}
	}
}


void ACPPHubActor::OnTimeToDestroy()
{
	if (!SpawnedObjects.IsEmpty())
	{
		SpawnedObjects.Top()->Destroy();
		SpawnedObjects.Pop();
	}
	else
	{
		GetWorldTimerManager().ClearTimer(DestroyTimerHandle);
	}
}
