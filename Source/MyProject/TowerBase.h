// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerBase.generated.h"

USTRUCT(BlueprintType)
struct FAttackStruct {

	GENERATED_USTRUCT_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack_Damage_Per_Second)
		bool dps_Enabled;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack_Damage_Per_Second)
		float dps_Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack_Damage_Per_Second)
		float dps_Duration;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack_Slow_Movement)
		bool slow_Enabled;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack_Slow_Movement)
		float slow_Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack_Slow_Movement)
		float slow_Length;


};

USTRUCT(BlueprintType)
struct FLevelupStruct {

	GENERATED_USTRUCT_BODY()

public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tower_LevelupStats)
		float BonusRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tower_LevelupStats)
		float BonusDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tower_LevelupStats)
		float BonusAttackSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tower_LevelupStats)
		FAttackStruct BonusAttackModifier;
	


};

UCLASS()
class MYPROJECT_API ATowerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATowerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SearchForTargets();
	void _attackTarget(AActor* target);
	void Reload();
	void ResetAttack();

	FTimerHandle MemberTimerHandle;

private: 
	bool _canAttack = true;
public:	
	// Called every frame

	virtual void Tick(float DeltaTime) override;
	bool CanAttack() { return _canAttack; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TowerStats)
		int MaxLevel = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TowerStats)
		float Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TowerStats)
		float Range;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TowerStats)
		float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TowerStats)
		float AttackSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TowerStats)
		int Projectile;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TowerStats)
		float Experience;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TowerStats)
		FAttackStruct AttackEffects;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TowerStats)
		FLevelupStruct BonusStats;

};
