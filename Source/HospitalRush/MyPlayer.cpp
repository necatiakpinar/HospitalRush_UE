// Fill out your copyright notice in the Description page of Project Settings.

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Patient.h"
#include "Bed.h"
#include "ActionArea.h"
#include "Treatment.h"
#include "TreatmentProduct.h"
#include "MyPlayer.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	holderComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Actor"));
	//root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	//RootComponent = root;
	//meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	//capsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Custom Capsule"));
}


// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMyPlayer::OnOverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AMyPlayer::OnOverlapEnd);
}

void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyPlayer::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
//	UE_LOG(LogTemp, Warning, TEXT("STARTED!"));
	APatient* patient = Cast<APatient>(OtherActor);
	ABed* bed = Cast<ABed>(OtherActor);
	AActionArea* actionArea= Cast<AActionArea>(OtherActor);

	if (patient)
	{

		switch (patient->patientStatus)
		{
			case EPatientStatus::Idle:
				patient->Grapped(Cast<AActor>(this), holderComponent);
				CollectPatient(patient);
			break;

			case EPatientStatus::Admitted:
				int patientTreatmentIndex = GetTreatmentIndex(patient->treatmentType);
				if (patientTreatmentIndex != -1)
				{
					GiveTreatment(patientTreatmentIndex);
					patient->TakeTreatment();
				}
				else
					return;
			break;
		}
	}
	
	if (bed)
	{
		if (bed->IsBedAvailable() && listPatient.Num() > 0)
		{
			bed->CollectPatient(GetFirstAvailablePatient());
			RemovePatient(GetFirstAvailablePatient());
		}
	}

	if (actionArea)
	{
		actionArea->StartAction(this);
	}
}

void AMyPlayer::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//UE_LOG(LogTemp, Warning, TEXT("ENDED!"));
	AActionArea* actionArea = Cast<AActionArea>(OtherActor);
	if (actionArea)
	{
		actionArea->CancelAction();
	}
}

void AMyPlayer::OnBossDied(FVector location)
{
	//UE_LOG(LogTemp, Warning, TEXT("BOSS DIED!"));
}


#pragma region Patient

void AMyPlayer::CollectPatient(APatient* pPatient)
{
	if (listTreatment.Num() > 0)
		RemoveAllTreatments();

	listPatient.Add(pPatient);
	holderComponent->SetRelativeLocation(FVector(holderComponent->GetRelativeLocation().X,
		holderComponent->GetRelativeLocation().Y,
		holderComponent->GetRelativeLocation().Z + patientHeightAmount));
}

void AMyPlayer::RemovePatient(APatient* pPatient)
{
	listPatient.Remove(pPatient);
	holderComponent->SetRelativeLocation(FVector(holderComponent->GetRelativeLocation().X,
		holderComponent->GetRelativeLocation().Y,
		holderComponent->GetRelativeLocation().Z - patientHeightAmount));
}

void AMyPlayer::RemoveAllPatients()
{
	for (APatient* patient : listPatient)
	{
		holderComponent->SetRelativeLocation(FVector(holderComponent->GetRelativeLocation().X,
			holderComponent->GetRelativeLocation().Y,
			holderComponent->GetRelativeLocation().Z - patientHeightAmount));
		
		patient->Destroy();
	}

	listPatient.Empty();
}

APatient* AMyPlayer::GetFirstAvailablePatient()
{
	if (listPatient.Num() > 0 && listPatient[listPatient.Num() - 1])
		return listPatient[listPatient.Num() - 1];

	return nullptr;
}
#pragma endregion


#pragma region Treatment

void AMyPlayer::AddTreatment(ATreatmentProduct* pTreatment)
{
	if (listPatient.Num() > 0)
		RemoveAllPatients();


	pTreatment->Grapped(Cast<AActor>(this), holderComponent);
	listTreatment.Add(pTreatment);
	holderComponent->SetRelativeLocation(FVector(holderComponent->GetRelativeLocation().X,
		holderComponent->GetRelativeLocation().Y,
		holderComponent->GetRelativeLocation().Z + treatmentHeightAmount));
}

void AMyPlayer::GiveTreatment(int pTreatmentIndex)
{
	listTreatment[pTreatmentIndex]->Destroy();
	listTreatment.RemoveAt(pTreatmentIndex);
	holderComponent->SetRelativeLocation(FVector(holderComponent->GetRelativeLocation().X,
		holderComponent->GetRelativeLocation().Y,
		holderComponent->GetRelativeLocation().Z - treatmentHeightAmount));
}

int AMyPlayer::GetTreatmentIndex(ETreatmentType pTreatmentType)
{
	int treatmentIndex = -1;
	
	if (listTreatment.Num() > 0)
	{
		for (int i = listTreatment.Num() - 1; i >= 0; i--)
		{
			if (pTreatmentType == listTreatment[i]->treatmentType)
			{
				return i;
			}
		}
	}
	return treatmentIndex;
}
void AMyPlayer::RemoveAllTreatments()
{
	for (ATreatmentProduct* treatment : listTreatment)
	{
		holderComponent->SetRelativeLocation(FVector(holderComponent->GetRelativeLocation().X,
			holderComponent->GetRelativeLocation().Y,
			holderComponent->GetRelativeLocation().Z - treatmentHeightAmount));
		treatment->Destroy();
	}

	listTreatment.Empty();
}

#pragma endregion
