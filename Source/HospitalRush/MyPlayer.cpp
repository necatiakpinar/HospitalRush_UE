// Fill out your copyright notice in the Description page of Project Settings.

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Patient.h"
#include "Bed.h"
#include "ActionArea.h"
#include "Treatment.h"
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
		UE_LOG(LogTemp, Warning, TEXT("Catched!"));
		switch (patient->patientStatus)
		{
			case EPatientStatus::Idle:
				patient->Grapped(Cast<AActor>(this), holderComponent);
				CollectPatient(patient);
			break;

			case EPatientStatus::Admitted:
				if (IsTreatmentExist(patient->treatmentType))
					patient->TakeTreatment();
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

APatient* AMyPlayer::GetFirstAvailablePatient()
{
	if (listPatient.Num() > 0 && listPatient[listPatient.Num() - 1])
		return listPatient[listPatient.Num() - 1];

	return nullptr;
}
#pragma endregion


#pragma region Treatment

void AMyPlayer::AddTreatment(ATreatment* pTreatment)
{
	pTreatment->Grapped(Cast<AActor>(this), holderComponent);
	listTreatment.Add(pTreatment);
	holderComponent->SetRelativeLocation(FVector(holderComponent->GetRelativeLocation().X,
		holderComponent->GetRelativeLocation().Y,
		holderComponent->GetRelativeLocation().Z + treatmentHeightAmount));
}

void AMyPlayer::GiveTreatment(ATreatment* pTreatment)
{
	listTreatment.Remove(pTreatment);
	holderComponent->SetRelativeLocation(FVector(holderComponent->GetRelativeLocation().X,
		holderComponent->GetRelativeLocation().Y,
		holderComponent->GetRelativeLocation().Z - treatmentHeightAmount));
}

bool AMyPlayer::IsTreatmentExist(ETreatmentType pTreatmentType)
{
	ATreatment* treatmentInPlayerHands = nullptr;

	if (listTreatment.Num() > 0)
	{
		for (uint8 i = listTreatment.Num() - 1; i > -1; i--)
		{
			if (pTreatmentType == listTreatment[i]->treatmentType)
			{
				treatmentInPlayerHands = listTreatment[i];
				break;
			}
		}

		if (treatmentInPlayerHands != nullptr)
		{
			GiveTreatment(treatmentInPlayerHands);
			return true;
		}

	}

	return false;
}

#pragma endregion
