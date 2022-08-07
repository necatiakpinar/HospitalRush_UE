// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EActionPerformerType : uint8
{
	Treatment UMETA(DisplayName = "Treatment"),
	Upgrade UMETA(DisplayName = "Upgrade")
};


UENUM(BlueprintType)
enum class ETreatmentType : uint8
{
	Treatment_Pill UMETA(DisplayName = "TreatmentPill"),
	Treatment_Syrup UMETA(DisplayName = "TreatmentSyrup")
};

UENUM(BlueprintType)
enum class EPatientStatus: uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Carrying UMETA(DisplayName = "Carrying"),
	Walking_To_WaitingArea UMETA(DisplayName = "WalkingToWaitingArea"),
	Admitted UMETA(DisplayName = "Admitted "),
	Treated UMETA(DisplayName = "Treated "),
	Walking_To_Exit UMETA(DisplayName = "WalkingToExit "),

};


