// Fill out your copyright notice in the Description page of Project Settings.

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Treatment.h"
#include "MyPlayer.h"
#include "MyEnums.h"
#include "ActionArea.h"

// Sets default values
AActionArea::AActionArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TimerDuration = 1.0f;
	canActionPerform = true;
}

// Called when the game starts or when spawned
void AActionArea::BeginPlay()
{
	Super::BeginPlay();
	
	if (actionPerformer && actionPerformerType == EActionPerformerType::Treatment)
	{
		treatmentObject = Cast<ATreatment>(actionPerformer);
	}
}


// Called every frame
void AActionArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AActionArea::StartAction(AMyPlayer* pPlayer)
{
	player = pPlayer;
	GetWorldTimerManager().SetTimer(timeHandler, this, &AActionArea::ActionFinished, TimerDuration, true, TimerDuration);
}

void AActionArea::CancelAction()
{
	GetWorldTimerManager().ClearTimer(timeHandler);
}

void AActionArea::ActionFinished()
{
	if (canActionPerform)
	{
		if (treatmentObject)
			treatmentObject->SpawnTreatment(player);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Action CAN'T performed!"));
	}
}

