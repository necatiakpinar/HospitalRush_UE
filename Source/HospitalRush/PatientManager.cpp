// Fill out your copyright notice in the Description page of Project Settings.

#include "PatientManager.h"
#include "Patient.h"

// Sets default values
APatientManager::APatientManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APatientManager::BeginPlay()
{
	Super::BeginPlay();
    SpawnPatient();
   /* SpawnPatient();
    SpawnPatient();
   */
}

// Called every frame
void APatientManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APatientManager::SpawnPatient()
{
    if (patientBP == nullptr)      UE_LOG(LogTemp, Warning, TEXT("NULLLLL BP!!"));

    APatient* patient = patientBP.GetDefaultObject();

   FActorSpawnParameters SpawnInfo;
    SpawnInfo.Owner = NULL;
    const FTransform SpawnTransform(FQuat::Identity, FVector(0.0f, 10.0f, -30.0f));
    FAttachmentTransformRules attachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative,EAttachmentRule::KeepRelative ,EAttachmentRule::KeepRelative,false);


    patient  = GetWorld()->SpawnActor<APatient>(patientBP, SpawnTransform);
    patient->AttachToActor(this, attachmentRules);
    listPatient.Add(patient);

}
