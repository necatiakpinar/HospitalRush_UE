// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PaperSpriteComponent.h"
#include "MyEnums.h"
#include "Patient.generated.h"

class AMyPlayer;
class ABed;
class ATreatment;
class UDATreatmentIcons;

UCLASS()
class HOSPITALRUSH_API APatient : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APatient();

public:
	UPaperSpriteComponent*  spriteCompTreatment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) EPatientStatus patientStatus;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UDATreatmentIcons* daTreatmentIcons;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) ETreatmentType treatmentType;

private:
	AMyPlayer* player;
	ABed* bed;
public:
	UFUNCTION()
	void Grapped(AActor* pPlayer, USceneComponent* pHolder);

	UFUNCTION()
		void BossDied(FVector location);

	void SleepOnBed(AActor* pBed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetRandomTreatment();
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void SetPatientStatus(EPatientStatus pPatientStatus);
	void TakeTreatment();

	
};
