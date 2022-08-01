// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "Treatment.h"

// Sets default values
ATreatment::ATreatment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATreatment::BeginPlay()
{
	Super::BeginPlay();
	//SpawnTreatment();
	
}

// Called every frame
void ATreatment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATreatment::SpawnTreatment()
{
	UE_LOG(LogTemp, Warning, TEXT("WORKING"));
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = NULL;
	const FTransform SpawnTransform(FQuat::Identity, FVector(0.0f, 10.0f, 100.0f));

	if (treatmentPillBP && treatmentType == ETreatmentType::Treatment_Pill)
	{
		treatmentPill = GetWorld()-> SpawnActor<AActor>(treatmentPillBP,SpawnTransform);
	}
	else if (treatmentSyrupBP && treatmentType == ETreatmentType::Treatment_Syrup)
	{
		treatmentSyrup = GetWorld()->SpawnActor<AActor>(treatmentSyrupBP, SpawnTransform);
	}
	
}

