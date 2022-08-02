// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActionArea.generated.h"


UENUM(BlueprintType)
enum class EActionType : uint8
{
	Treatment_Pill UMETA(DisplayName = "TreatmentPill"),
	Treatment_Syrup UMETA(DisplayName = "TreatmentSyrup")
};

class AMyPlayer;
UCLASS()
class HOSPITALRUSH_API AActionArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActionArea();

public:
	bool canActionPerform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EActionType actionType;

private:
	FTimerHandle timeHandler;
	float TimerDuration;
	AMyPlayer* player;
	FString actionTypeAsString;

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
