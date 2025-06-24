// LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "Weapon/LMABaseWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"


DEFINE_LOG_CATEGORY_STATIC(LogWeapon, All, All)

ALMABaseWeapon::ALMABaseWeapon()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	WeaponComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	SetRootComponent(WeaponComponent);

	CurrentAmmoWeapon = AmmoWeapon;

}

void ALMABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	ChangeClip();
	
}

void ALMABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALMABaseWeapon::Fire()
{
	IsFiring = true;
	Shoot();
}

void ALMABaseWeapon::StopShooting()
{
	IsFiring = false;
}

void ALMABaseWeapon::Shoot()
{
	if (!IsFiring)
	{
		return;
	}

	const FTransform SocketTransform = WeaponComponent->GetSocketTransform("Muzzle");
	const FVector TraceStart = SocketTransform.GetLocation();
	const FVector ShootDirection = SocketTransform.GetRotation().GetForwardVector();
	const FVector TraceEnd = TraceStart + ShootDirection * TraceDistance;
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);
	FVector TracerEnd = TraceEnd;
	if (HitResult.bBlockingHit)
	{
		TracerEnd = HitResult.ImpactPoint;
	}
	SpawnTrace(TraceStart, TracerEnd);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShootWave, TraceStart);

	DecrementBullets();
}

void ALMABaseWeapon::ChangeClip()
{
	CurrentAmmoWeapon.Bullets = AmmoWeapon.Bullets;
}

bool ALMABaseWeapon::IsCurrentClipEmpty() const
{
	return CurrentAmmoWeapon.Bullets == 0;
}

bool ALMABaseWeapon::IsCurrentClipFull() const 
{
	return CurrentAmmoWeapon.Bullets >= AmmoWeapon.Bullets;
}


void ALMABaseWeapon::DecrementBullets()
{
	if (IsCurrentClipEmpty())
	{
		OnClipEmpty.Broadcast(true);
		return;
	}
	
	CurrentAmmoWeapon.Bullets--;
	
	if (IsCurrentClipEmpty())
	{
		OnClipEmpty.Broadcast(true);
	}
}

void ALMABaseWeapon::AutoReload()
{
	if (IsCurrentClipEmpty() && !IsCurrentClipFull())
	{
		ChangeClip();
	}
}

void ALMABaseWeapon::SpawnTrace(const FVector& TraceStart, const FVector& TraceEnd)
{
	const auto TraceFX = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceEffect, TraceStart);
	if (TraceFX)
	{
		TraceFX->SetNiagaraVariableVec3(TraceName, TraceEnd);
	}
}

