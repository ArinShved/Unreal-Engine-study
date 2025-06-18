// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LMADemageActor.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class LEAVEMEALONE_API ALMADemageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALMADemageActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float Damage = 5.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage") 
	float SphereRadius = 100.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
