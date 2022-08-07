// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyEnums.h"
#include "Treatment.generated.h"


class FTreatmentHandler
{
public:
	void OnTreatmentSpawn();
};

class AMyPlayer;
class ATreatmentProduct;

UCLASS()
class HOSPITALRUSH_API ATreatment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATreatment();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TSubclassOf<ATreatmentProduct> treatmentPillBP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TSubclassOf<ATreatmentProduct> treatmentSyrupBP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) ETreatmentType treatmentType;


private:
	AActor* treatmentObject;
public:
	//static FSpawnTreatment OnSpawnTreatment;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void SpawnTreatment(AMyPlayer* pPlayer);
	
};
