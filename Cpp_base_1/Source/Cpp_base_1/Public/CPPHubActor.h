// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPPHubActor.generated.h"

class ACPPMyActor;

UCLASS()
class CPP_BASE_1_API ACPPHubActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACPPHubActor();

	UPROPERTY(EditAnywhere)
	float SpawnTimerRate = 2.0f;

	UPROPERTY(EditAnywhere)
	float DestroyTimerRate = 1.0f;

	FTimerHandle SpawnTimerHandle;
	FTimerHandle DestroyTimerHandle;

	void OnTimeToSpawn();
	void OnTimeToDestroy();

	const int32 TotalCount = 10;

	int32 CurrentTimerCount = 0;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ACPPMyActor> CppClass;

	UPROPERTY()
	TArray<ACPPMyActor*> SpawnedObjects;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
