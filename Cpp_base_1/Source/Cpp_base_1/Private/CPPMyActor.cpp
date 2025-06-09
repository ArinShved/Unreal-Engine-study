// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPMyActor.h"

// Sets default values
ACPPMyActor::ACPPMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

}

// Called when the game starts or when spawned
void ACPPMyActor::BeginPlay()
{
	Super::BeginPlay();
	ShowActorInformation();
	
}

void ACPPMyActor::ShowActorInformation() {
	PlayerName = GetName();
	UE_LOG(LogTemp, Display, TEXT("Player name: %s"), *PlayerName);

	UE_LOG(LogTemp, Display, TEXT("Enemy num: %d"), EnemyCount);

	UE_LOG(LogTemp, Display, TEXT("IsAlive: %d"), isAlive ? 1 : 0);

}

// Called every frame
void ACPPMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

