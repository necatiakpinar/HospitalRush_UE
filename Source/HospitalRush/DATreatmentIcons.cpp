// Fill out your copyright notice in the Description page of Project Settings.


#include "DATreatmentIcons.h"

UPaperSprite* UDATreatmentIcons::GetPaperSprite(ETreatmentType pTreatmentType)
{
	for (FTreatmentIcons treatmentIcon : listTreatmentIcon)
	{
		if (treatmentIcon.treatmentType == pTreatmentType)
			return treatmentIcon.paperSpriteTreatment;
	}

	return nullptr;
}
