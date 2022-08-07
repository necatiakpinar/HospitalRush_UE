// Fill out your copyright notice in the Description page of Project Settings.


#include "TreatmentProduct.h"

// Sets default values
ATreatmentProduct::ATreatmentProduct()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATreatmentProduct::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATreatmentProduct::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ATreatmentProduct::Grapped(AActor* pPlayer, USceneComponent* pHolder)
{
	AttachToActor(pPlayer, FAttachmentTransformRules::KeepRelativeTransform);
	SetActorRelativeLocation(pHolder->GetComponentTransform().GetLocation());
	SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}

