// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "DrawDebugHelpers.h"
#include "EngineGlobals.h"
#include "Engine/EngineTypes.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"

#include "EnemyBase.generated.h"
/**
 *
 */
USTRUCT(BlueprintType)
struct FDebuffStrct {

	GENERATED_USTRUCT_BODY()
	bool debuff_damagepersecond_enabled;
	float debuff_damagepersecond;
	float debuff_damagepersecond_time;

	bool debuff_movementspeed_enabled;
	float debuff_movementspeed;
	float debuff_movementspeed_time;
};

USTRUCT(BlueprintType)
struct FStatsStruct {
	GENERATED_USTRUCT_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BonusEnemyStats)
	float bonus_movespeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BonusEnemyStats)
	float bonus_health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BonusEnemyStats)
	float bonus_maxhealth;

};

UCLASS()
class MYPROJECT_API AEnemyBase : public AActor
{

	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyStats)
	float maxhealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyStats)
	float health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyStats)
	float movementspeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyStats)
	int level = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyStats)
	float experience;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyStats)
	float totalexpneeded = 86;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyStats)
	int maxlevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyStats)
	FStatsStruct EnemyStats;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyStats)
	TArray<FDebuffStrct> debuffs;


public:
	AEnemyBase();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


	void AddExperience(float XP_toadd)
	{
		experience += XP_toadd;
		if (experience >= totalexpneeded)
		{
			totalexpneeded += GetNextLevelExperience();
			level++;
		}
	}

	float GetNextLevelExperience()
	{
		return ((level) + 300 * pow(2, level / 7.0f));
	}
	float GetHealth() { return health + (EnemyStats.bonus_health * level); }
	float GetMovementSpeed() { return movementspeed + (EnemyStats.bonus_movespeed * level) - GetMovementSpeedDebuf(); }
	float GetMaxHealth() { return maxhealth + (EnemyStats.bonus_maxhealth * level); }
	void Heal(float healamount) { 
		health += healamount;
		if (health > GetMaxHealth())
			health = GetMaxHealth();
	}
	void _TakeDamage(float damageamount) {
		health -= damageamount; 
		if (health < 0)
			Kill();

		//GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Green, FString::Printf(TEXT("Remaining health = %f , damage ammount %f"), health, damageamount));
	}
	void Kill()
	{
		/* ADD POINTS*/
		/* ADD MONEY*/
		Destroy();
	}
	float GetMovementSpeedDebuf() 
	{ 
		float DebuffSpeed = 0.0f;
		for (auto& hit : debuffs)
		{
			if (hit.debuff_movementspeed_enabled)
			{
				DebuffSpeed += hit.debuff_movementspeed;
			}
		}
	return DebuffSpeed;
	}

	void ApplyDebuff(bool dps, float dps_damage, float dps_time, bool movespeed, float movespeed_amount, float movespeed_time) {

		FDebuffStrct Debuff;
		Debuff.debuff_damagepersecond = dps_damage;
		Debuff.debuff_damagepersecond_enabled = dps;	
		Debuff.debuff_damagepersecond_time = dps_time;

		Debuff.debuff_movementspeed = movespeed_amount;
		Debuff.debuff_movementspeed_enabled = movespeed;
		Debuff.debuff_movementspeed_time = movespeed_time;
		debuffs.Add(Debuff);

	}

	void CheckDebuff()
	{
		for (int i = debuffs.Num() - 1; i > 0; i--)//--
		{
			FDebuffStrct Debuff = debuffs[i];
			if (Debuff.debuff_damagepersecond_time < GetWorld()->GetTimeSeconds() && Debuff.debuff_damagepersecond_enabled)
			{
				Debuff.debuff_damagepersecond_enabled = false;
			}
			if (Debuff.debuff_damagepersecond_time < GetWorld()->GetTimeSeconds() && Debuff.debuff_damagepersecond_enabled)
			{
				Debuff.debuff_damagepersecond_enabled = false;
			}
			if (!Debuff.debuff_damagepersecond_enabled && !Debuff.debuff_movementspeed_enabled)
			{
				debuffs.RemoveAt(i);
			}
		}
	}


};
