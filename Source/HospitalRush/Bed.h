// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Bed.generated.h"


class APatient;
class UStaticMeshComponent;
UCLASS()
class HOSPITALRUSH_API ABed : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABed();

public:
	UPROPERTY(EditAnywhere) UStaticMeshComponent* meshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")) USceneComponent* holderComponent;
	UPROPERTY(EditAnywhere) int totalCapacity;
	UPROPERTY(EditAnywhere) int currentCapacity;
	UPROPERTY(EditAnywhere) bool isFull;

private:
	TArray<APatient*> listPatient;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void CollectPatient(APatient* pPatient);
	void RemovePatient(APatient* pPatient);
	bool IsBedAvailable();

};
