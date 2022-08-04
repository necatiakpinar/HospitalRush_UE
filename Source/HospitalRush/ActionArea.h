// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyEnums.h"
#include "ActionArea.generated.h"


class AMyPlayer;
class MyEnums;
class ATreatment;

UCLASS()
class HOSPITALRUSH_API AActionArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActionArea();

public:
	bool canActionPerform;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)	 AActor* actionPerformer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EActionPerformerType actionPerformerType;
	ATreatment* treatmentObject;


private:
	FTimerHandle timeHandler;
	float TimerDuration;
	AMyPlayer* player;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void StartAction(AMyPlayer* pPlayer);
	void CancelAction();
	void ActionFinished();

};
