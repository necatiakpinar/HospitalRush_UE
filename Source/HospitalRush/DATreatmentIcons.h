// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MyEnums.h"
#include "PaperSpriteComponent.h"
#include "DATreatmentIcons.generated.h"


USTRUCT(BlueprintType)
struct FTreatmentIcons
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere) ETreatmentType treatmentType;
		UPROPERTY(EditAnywhere) UPaperSprite* paperSpriteTreatment;
};

UCLASS()
class HOSPITALRUSH_API UDATreatmentIcons : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly) TArray<FTreatmentIcons> listTreatmentIcon;

public:
	UPaperSprite* GetPaperSprite(ETreatmentType pTreatmentType);
	
};
