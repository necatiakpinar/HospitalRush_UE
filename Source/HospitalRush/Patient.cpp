// Fill out your copyright notice in the Description page of Project Settings.

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "MyPlayer.h"
#include "MyEnums.h"
#include "DATreatmentIcons.h"
#include "Patient.h"

// Sets default values
APatient::APatient()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APatient::BeginPlay()
{
	Super::BeginPlay();
	spriteCompTreatment = Cast<UPaperSpriteComponent>(GetComponentByClass(UPaperSpriteComponent::StaticClass()));

	if (spriteCompTreatment)
	{
	//	treatmentType = ETreatmentType::Treatment_Syrup;
		UPaperSprite* treatmentSprite = daTreatmentIcons->GetPaperSprite(treatmentType);
		spriteCompTreatment->SetSprite(daTreatmentIcons->GetPaperSprite(treatmentType));
	}
}

// Called every frame
void APatient::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APatient::BossDied(FVector location)
{
	Destroy();
}

void APatient::Grapped(AActor* pPlayer, USceneComponent* pHolder)
{
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	this->AttachToActor(pPlayer, FAttachmentTransformRules::KeepRelativeTransform);
	SetActorRelativeLocation(pHolder->GetComponentTransform().GetLocation());
	SetActorRotation(FRotator(0.0f,0.0f, -90.0f));
}

void APatient::SleepOnBed(AActor* pBed)
{
	patientStatus = EPatientStatus::Admitted;
	this->AttachToActor(pBed, FAttachmentTransformRules::KeepRelativeTransform);
	SetActorRelativeLocation(FVector(0.0f,0.0f,50.0f));
	SetActorRotation(FRotator(0.0f, -90.0f, -90.0f));
	UE_LOG(LogTemp, Warning,TEXT("Worked!"));
}



