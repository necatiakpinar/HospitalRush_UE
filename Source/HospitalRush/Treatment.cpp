// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "MyPlayer.h"
#include "TreatmentProduct.h"
#include "Treatment.h"


// Sets default values
ATreatment::ATreatment()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATreatment::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATreatment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATreatment::SpawnTreatment(AMyPlayer* pPlayer)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = NULL;
	const FTransform SpawnTransform(FQuat::Identity, FVector(0.0f, 10.0f, 100.0f));

	if (treatmentPillBP && treatmentType == ETreatmentType::Treatment_Pill)
	{
		treatmentObject = GetWorld()-> SpawnActor<AActor>(treatmentPillBP,SpawnTransform);
	}
	else if (treatmentSyrupBP && treatmentType == ETreatmentType::Treatment_Syrup)
	{
		treatmentObject = GetWorld()->SpawnActor<AActor>(treatmentSyrupBP, SpawnTransform);
	}

	if (treatmentObject)
	{
		pPlayer->AddTreatment(Cast<ATreatmentProduct>(treatmentObject));
	}
	
}


