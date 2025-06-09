// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPPMyActor.generated.h"


UENUM(BlueprintType)
enum class EMovementState : uint8
{
	Mobility,
	Static
};

USTRUCT(BlueprintType)
struct FTransformStruct
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector CurrentLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator CurrentRotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector CurrentScale = FVector(1.0f, 1.0f, 1.0f);
};

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

	UFUNCTION(BlueprintCallable)
	void ShowActorInformation();

	UFUNCTION(BlueprintCallable)
	void SinMovement();

	UPROPERTY(VisibleAnywhere)

	UStaticMeshComponent* Mesh;

	FString PlayerName;

	UPROPERTY(EditAnywhere)
	int EnemyCount;

	UPROPERTY(EditAnywhere)
	bool isAlive;

	UPROPERTY(EditAnywhere)
	float Amplitude = 70;

	UPROPERTY(EditAnywhere)
	float Frequency = 4;

	FVector InitialLocation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
