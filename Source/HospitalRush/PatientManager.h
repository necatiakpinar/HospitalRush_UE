// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatientManager.generated.h"

class APatient;
UCLASS()
class HOSPITALRUSH_API APatientManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APatientManager();

public:
	UPROPERTY(EditAnywhere)  TSubclassOf<APatient> patientBP;
	UPROPERTY(EditAnywhere) TArray<APatient*> listPatient;
	UPROPERTY(EditAnywhere) USceneComponent* sceneComponent;
	//UPROPERTY(EditAnywhere) patientParent;;
private:
	void SpawnPatient();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
