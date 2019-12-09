// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerBase.h"
#include <string>
#include <sstream>
#include "Runtime/Engine/Public/WorldCollision.h"
// Sets default values
ATowerBase::ATowerBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ATowerBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATowerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SearchForTargets();
}

void ATowerBase::SearchForTargets()
{
	if (!CanAttack())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("Can't attack")));
		return;
	}
		

	TArray<FHitResult> hitResults = SphereTrace(GetAttackRange());


	if (hitResults.Num() == 0)
	{

		//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Green, FString::Printf(TEXT("no hit result")));
		return;
	}
	AActor* Target = nullptr;
	/* Search algorithm here*/
	
	for (auto& hit : hitResults)
	{
		if (hit.GetActor()->GetName().ToLower().Contains("sphere"))
		{
			Target = hit.GetActor();
			break;
		}
		
	}
	if (Target == nullptr)
	{
	//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("Target null")));
		return;
	}

	AttackTarget(Target);


}

TArray<FHitResult> ATowerBase::SphereTrace(float size) {
	TArray<FHitResult> OutHits;

	FVector SweepStart = GetActorLocation();
	FVector SweepEnd = GetActorLocation() + FVector(10,10,10);

	FCollisionShape MyColSphere = FCollisionShape::MakeSphere(size);

	//DrawDebugSphere(GetWorld(), GetActorLocation(), MyColSphere.GetSphereRadius(), 40, FColor::Purple, false, 1);
	FCollisionQueryParams searchParams;
	searchParams.AddIgnoredActor(this);

	bool isHit = GetWorld()->SweepMultiByChannel(OutHits, SweepStart, SweepEnd, FQuat::Identity, ECC_WorldStatic, MyColSphere, searchParams);


	return OutHits;

}

void ATowerBase::AttackTarget(AActor* target)
{
	DrawDebugLine(GetWorld(), this->GetActorLocation(), target->GetActorLocation(), FColor::Red, false, 2, 0, 4);
	_canAttack = false;

	GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Green, FString::Printf(TEXT("attack delay = %f"), GetAttackDelay()));
	/* Send projectile towards target's position */
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ATowerBase::Reload, 1.0f, true, GetAttackDelay());
}

void ATowerBase::Reload()
{
	//GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Green, FString::Printf(TEXT("Reload")));
	_canAttack = true;
	GetWorldTimerManager().ClearTimer(MemberTimerHandle);
}

float ATowerBase::GetAttackDelay()
{

	//GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Green, FString::Printf(TEXT("BAT = %f , AS = %f , BAS = %f ,  level = %f"), BaseAttackTimer, AttackSpeed, BonusStats.BonusAttackSpeed, Level));
	return BaseAttackTimer / ((AttackSpeed + (BonusStats.BonusAttackSpeed * Level)) / 100);
}

float ATowerBase::GetAttackRange()
{
	return Range + (BonusStats.BonusRange * Level);
}