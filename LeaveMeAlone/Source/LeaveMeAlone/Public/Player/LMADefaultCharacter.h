// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LMADefaultCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class LEAVEMEALONE_API ALMADefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALMADefaultCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY()
	UDecalComponent* CurrentCursor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	UMaterialInterface* CursorMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	FVector CursorSize = FVector(20.0f, 40.0f, 40.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings")
	float ZoomSpeed = 80.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings")
	float MinZoomDistance = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings")
	float MaxZoomDistance = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings")
	float ZoomInterpSpeed = 8.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	float CurrentZoomDistance;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	float YRotation = -75.0f;

	float ArmLength = 1400.0f;

	float FOV = 55.0f;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void HandleCameraZoom(float Value);


};
