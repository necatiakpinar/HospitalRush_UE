// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyEnums.h"
#include "TreatmentProduct.generated.h"

UCLASS()
class HOSPITALRUSH_API ATreatmentProduct : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATreatmentProduct();
	UPROPERTY(EditAnywhere, BlueprintReadWrite) ETreatmentType treatmentType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Grapped(AActor* pPlayer, USceneComponent* pHolder);

};
