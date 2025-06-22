// LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "Player/LMADefaultCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/DecalComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/LMAHealthComponent.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/LMAWeaponComponent.h"


// Sets default values
ALMADefaultCharacter::ALMADefaultCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	SpringArmComponent->TargetArmLength = ArmLength;
	SpringArmComponent->SetRelativeRotation(FRotator(YRotation, 0.0f, 0.0f));
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->CameraLagSpeed = 10.0f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetFieldOfView(FOV);
	CameraComponent->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CurrentZoomDistance = 500.0f;
	SpringArmComponent->TargetArmLength = CurrentZoomDistance;

	HealthComponent = CreateDefaultSubobject<ULMAHealthComponent>("HealthComponent");
	HealthComponent->OnDeath.AddUObject(this, &ALMADefaultCharacter::OnDeath);

	DefaultMaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	CurrentStamina = MaxStamina;

	WeaponComponent = CreateDefaultSubobject<ULMAWeaponComponent>("Weapon");
}


void ALMADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (CursorMaterial)
	{
		CurrentCursor = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), CursorMaterial, CursorSize, FVector(0));
	}

	OnHealthChanged(HealthComponent->GetHealth());
	HealthComponent->OnHealthChanged.AddUObject(this, &ALMADefaultCharacter::OnHealthChanged);
	
}


void ALMADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateStamina(DeltaTime);

	if (!(HealthComponent->IsDead()))
	{
		RotationPlayerOnCursor();
	}

	float CurrentArmLength = SpringArmComponent->TargetArmLength;
	float NewArmLength = FMath::FInterpTo(CurrentArmLength, CurrentZoomDistance, DeltaTime, ZoomInterpSpeed);
	SpringArmComponent->TargetArmLength = NewArmLength;

}

// Called to bind functionality to input
void ALMADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ALMADefaultCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALMADefaultCharacter::MoveRight);
	PlayerInputComponent->BindAxis("ZoomCamera", this, &ALMADefaultCharacter::HandleCameraZoom);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ALMADefaultCharacter::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ALMADefaultCharacter::StopSprint);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &ULMAWeaponComponent::Reload);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &ULMAWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &ULMAWeaponComponent::StopFire);
}

void ALMADefaultCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);

}

void ALMADefaultCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);

}

void ALMADefaultCharacter::HandleCameraZoom(float Value)
{
	if (Value != 0)
	{
		float ZoomDelta = Value * ZoomSpeed;
		CurrentZoomDistance = FMath::Clamp(CurrentZoomDistance - ZoomDelta, MinZoomDistance, MaxZoomDistance);
	}
}

void ALMADefaultCharacter::StartSprint()
{
	if (CurrentStamina > 0.0f)
	{
		CanSprint = true;
		GetCharacterMovement()->MaxWalkSpeed = DefaultMaxWalkSpeed * 1.5f;
	}
	
}

void ALMADefaultCharacter::StopSprint()
{
	CanSprint = false;
	GetCharacterMovement()->MaxWalkSpeed = DefaultMaxWalkSpeed;
}

void ALMADefaultCharacter::OnDeath()
{
	CurrentCursor->DestroyRenderState_Concurrent();
	PlayAnimMontage(DeathMontage);
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(5.0f);
	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}

void ALMADefaultCharacter::RotationPlayerOnCursor()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		FHitResult ResultHit;
		PC->GetHitResultUnderCursor(ECC_GameTraceChannel1, true, ResultHit);
		float FindRotatorResultYaw = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ResultHit.Location).Yaw;
		SetActorRotation(FQuat(FRotator(0.0f, FindRotatorResultYaw, 0.0f)));
		if (CurrentCursor)
		{
			CurrentCursor->SetWorldLocation(ResultHit.Location);
		}
	}
}

void ALMADefaultCharacter::OnHealthChanged(float NewHealth)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Health = %f"), NewHealth));
}

void ALMADefaultCharacter::UpdateStamina(float Value)
{
	if (CanSprint)
	{
		CurrentStamina = FMath::Clamp(CurrentStamina - 15.0f * Value, 0.0f, MaxStamina);

		if (CurrentStamina <= 0.0f)
		{
			StopSprint();
		}
	}
	else
	{
		CurrentStamina = FMath::Clamp(CurrentStamina + 10.0f * Value, 0.0f, MaxStamina);
	}

}

