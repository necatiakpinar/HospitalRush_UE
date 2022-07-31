// Fill out your copyright notice in the Description page of Project Settings.

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "MyPlayer.h"
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
	if (UWorld* world = GetWorld())
	{
		TArray<AActor*> outputActors;
		UGameplayStatics::GetAllActorsOfClass(world, AMyPlayer::StaticClass(), outputActors);

		if (outputActors.Num() > 0 && outputActors[0] != nullptr)
			player = Cast<AMyPlayer>(outputActors[0]);
	}

	if (player)
		player->BossDied.AddDynamic(this, &APatient::BossDied);
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
	this->AttachToActor(pBed, FAttachmentTransformRules::KeepRelativeTransform);
	SetActorRelativeLocation(FVector(0.0f,0.0f,50.0f));
	SetActorRotation(FRotator(0.0f, -90.0f, -90.0f));
	UE_LOG(LogTemp, Warning,TEXT("Worked!"));

}



