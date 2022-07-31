// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionArea.h"

// Sets default values
AActionArea::AActionArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TimerDuration = 2.0f;
	canActionPerform = true;
}

// Called when the game starts or when spawned
void AActionArea::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AActionArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AActionArea::StartAction()
{
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
	}
}
