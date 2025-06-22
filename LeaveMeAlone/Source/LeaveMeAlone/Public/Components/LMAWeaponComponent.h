// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LMAWeaponComponent.generated.h"

class ALMABaseWeapon;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEAVEMEALONE_API ULMAWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	ULMAWeaponComponent();

	void SpawnWeapon();

	void Fire();

	void StartFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void StopFire();

	void Reload();

	void InitAnimNotify();

	bool CanReload() const;

	void OnNotifyReloadFinished(USkeletalMeshComponent* SkeletalMesh);

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UAnimMontage* ReloadMontage;

	bool AnimReloading = false;

	UFUNCTION()
	void OnClipEmptyCallback(bool IsAvtoReload);

	void PerformReload();

	UFUNCTION(BlueprintCallable)
	bool GetCurrentWeaponAmmo(FAmmoWeapon& AmmoWeapon) const;
	

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ALMABaseWeapon> WeaponClass;

	UPROPERTY()
	ALMABaseWeapon* Weapon = nullptr;

	FTimerHandle FireTimerHandle;

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
