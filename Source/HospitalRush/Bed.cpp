// Fill out your copyright notice in the Description page of Project Settings.


#include "Patient.h"
#include "Bed.h"

// Sets default values
ABed::ABed()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	holderComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Of"));
	AddInstanceComponent(holderComponent);
	//SetRootComponent(meshComponent);
}

// Called when the game starts or when spawned
void ABed::BeginPlay()
{
	Super::BeginPlay();
	currentCapacity = 0;
	isFull = false;
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *holderComponent->GetRelativeLocation().ToString());

	
}

// Called every frame
void ABed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABed::CollectPatient(APatient* pPatient)
{
	if (pPatient)
	{
		currentCapacity++;
		if (currentCapacity == totalCapacity)
		{
			meshComponent->SetCollisionProfileName(TEXT("NoCollision"));
			isFull = true;
		}

		listPatient.Add(pPatient);

		pPatient->SleepOnBed(Cast<AActor>(this));
	}
}

void ABed::RemovePatient(APatient* pPatient)
{
	if (pPatient)
	{
		currentCapacity--;
		if (currentCapacity < totalCapacity)
		{

			meshComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
			isFull = false;
		}
		
		listPatient.Remove(pPatient);
	}
}

bool ABed::IsBedAvailable()
{
	return (!isFull && currentCapacity < totalCapacity) ? true : false;
}

