// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerSpawner.generated.h"

UCLASS()
class MYPROJECT_API ATowerSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATowerSpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TowerStats)
	bool SpawnMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TowerStats)
	int SpawnType;
	void SetSpawnType(int i) { SpawnType = i; }
	AActor* Tower;
	void SetTowerReference(AActor* _tower) { Tower = _tower; }
};
