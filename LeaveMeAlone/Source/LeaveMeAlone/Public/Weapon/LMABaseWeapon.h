// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LMABaseWeapon.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmpty, bool)

USTRUCT(BlueprintType)
struct FAmmoWeapon
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Bullets;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Clips;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool Infinite;
};

UCLASS()
class LEAVEMEALONE_API ALMABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	

	ALMABaseWeapon();

	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void StopShooting();

	void ChangeClip();

	void DecrementBullets();

	bool IsCurrentClipEmpty() const;

	FOnClipEmpty OnClipEmpty;

	bool IsCurrentClipFull() const;

	void AutoReload();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FAmmoWeapon AmmoWeapon{30, 0, true};

	FAmmoWeapon GetCurrentAmmoWeapon() const { return CurrentAmmoWeapon; }


protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TraceDistance = 800.0f;

	FAmmoWeapon CurrentAmmoWeapon;

	void Shoot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsFiring = false;
	

public:	
	virtual void Tick(float DeltaTime) override;	

};
