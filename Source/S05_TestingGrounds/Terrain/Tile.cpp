// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::PlaceActors()
{
	for (int i = 0; i < 10; i++)
	{
		FVector SpawnPoint = FMath::RandPointInBox(FBox(FVector(0, -2000, 0), FVector(4000, 2000, 0)));
		UE_LOG(LogTemp, Warning, TEXT("Spawn Point: %s"), *SpawnPoint.ToCompactString());
	}
}
