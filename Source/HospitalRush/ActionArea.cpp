// Fill out your copyright notice in the Description page of Project Settings.


#include "Treatment.h"
#include "MyPlayer.h"
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
	//actionType = FindObject<UEnum>(ANY_PACKAGE, TEXT("EActionType"), true);
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *actionType->GetEnumName(0));
	/*if (actionType == EActionType::Treatment_Pill)
	{
		UE_LOG(LogTemp, Warning, TEXT("WORKING"));
	}*/
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

void AActionArea::EndAction()
{
	GetWorldTimerManager().ClearTimer(timeHandler);
}

void AActionArea::ActionFinished()
{
	if (canActionPerform)
	{	
		UE_LOG(LogTemp, Warning, TEXT("Action performed!"));
		/*if (player)
			player->BossDied.Broadcast(FVector(0.0f))*/;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Action CAN'T performed!"));
	}
}

