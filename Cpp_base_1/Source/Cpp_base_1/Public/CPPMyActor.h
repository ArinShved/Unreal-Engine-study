// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPPMyActor.generated.h"

UCLASS()
class CPP_BASE_1_API ACPPMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPPMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ShowActorInformation();

	UPROPERTY(VisibleAnywhere)

	UStaticMeshComponent* Mesh;

	FString PlayerName;

	UPROPERTY(EditAnywhere)
	int EnemyCount;

	UPROPERTY(EditAnywhere)
	bool isAlive;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
