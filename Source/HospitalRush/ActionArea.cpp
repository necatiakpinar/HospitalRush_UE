// Fill out your copyright notice in the Description page of Project Settings.

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Treatment.h"
#include "MyPlayer.h"
#include "ActionArea.h"

// Sets default values
AActionArea::AActionArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TimerDuration = 1.0f;
	canActionPerform = true;
}

// Called when the game starts or when spawned
void AActionArea::BeginPlay()
{
	Super::BeginPlay();
	const TEnumAsByte<EActionType> ActionEnum = actionType;
	actionTypeAsString = UEnum::GetValueAsString(ActionEnum.GetValue());

}


// Called every frame
void AActionArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AActionArea::StartAction(AMyPlayer* pPlayer)
{
	player = pPlayer;
	GetWorldTimerManager().SetTimer(timeHandler, this, &AActionArea::ActionFinished, TimerDuration, true, TimerDuration);
}

void AActionArea::CancelAction()
{
	GetWorldTimerManager().ClearTimer(timeHandler);
}

void AActionArea::ActionFinished()
{
	if (canActionPerform)
	{
		UE_LOG(LogTemp, Warning, TEXT("Action performed!"));
		/*if (player)
			player->BossDied.Broadcast(FVector(0.0f))*/;
			//ATreatment:: OnSpawnTreatment.Broadcast(FVector(0.0f));
			//ATreatment::OnSpawnTreatment.Broadcast(FVector(0.0f));
			if (UWorld* world = GetWorld())
			{
				ATreatment* treatment;
				TArray<AActor*> outputActors;
				UGameplayStatics::GetAllActorsOfClass(world, ATreatment::StaticClass(), outputActors);

				for (AActor* outputActor : outputActors)
				{
					treatment = Cast<ATreatment>(outputActor);
					const TEnumAsByte<ETreatmentType> TreatmentEnum = treatment->treatmentType;
					FString	stringTreatmentType = UEnum::GetValueAsString(TreatmentEnum.GetValue());
					UE_LOG(LogTemp, Warning, TEXT("%s"),*actionTypeAsString);
					UE_LOG(LogTemp, Warning, TEXT("%s"), *stringTreatmentType);
					if (actionTypeAsString == stringTreatmentType)
					{
						treatment->SpawnTreatment();
					}
				}
			
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Action CAN'T performed!"));
			}
	}
}

