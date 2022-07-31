// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Patient.generated.h"

class AMyPlayer;
class ABed;

UCLASS()
class HOSPITALRUSH_API APatient : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APatient();

public:
	AMyPlayer* player;
public:
	UFUNCTION()
	void Grapped(AActor* pPlayer, USceneComponent* pHolder);

	UFUNCTION()
		void BossDied(FVector location);

	void SleepOnBed(AActor* pBed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
