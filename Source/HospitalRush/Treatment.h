// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Treatment.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpawnTreatment, FVector, location);


UENUM(BlueprintType)
enum class ETreatmentType: uint8
{
	Treatment_Pill UMETA(DisplayName = "TreatmentPill"),
	Treatment_Syrup UMETA(DisplayName = "TreatmentSyrup")
};


UCLASS()
class HOSPITALRUSH_API ATreatment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATreatment();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TSubclassOf<AActor> treatmentPillBP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TSubclassOf<AActor> treatmentSyrupBP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) ETreatmentType treatmentType;

private:
	AActor* treatmentPill;
	AActor* treatmentSyrup;
//public:
//	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers") FSpawnTreatment SpawnTreatment;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void SpawnTreatment();

};
