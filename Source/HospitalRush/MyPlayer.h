// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/CapsuleComponent.h"
#include "MyEnums.h"
#include "MyPlayer.generated.h"


//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBossDied, FVector, location);


class UStaticMeshComponent;
class AActionArea;
class APatient;
class ABed;
class ATreatment;
UCLASS()
class HOSPITALRUSH_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayer();
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare overlap end function
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void OnBossDied(FVector location);

	//UPROPERTY(BlueprintAssignable, Category = "EventDispatchers") FOnBossDied BossDied;


public:
	USceneComponent* root;
	UPROPERTY(Category = MeshComp, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")) UStaticMeshComponent* meshComponent;
	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = true)) FVector Bullet_SpawnLocation;
	UPROPERTY(EditAnywhere) USceneComponent* holderComponent;
	UPROPERTY(VisibleAnywhere) TArray<APatient*> listPatient;
	UPROPERTY(VisibleAnywhere) TArray<ATreatment*> listTreatment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Enery;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Mood;

private:
	float currentZHeight;
	float patientHeightAmount = 50.0f;
	float treatmentHeightAmount = 50.0f;

	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	void AddTreatment(ATreatment* pTreatment);
	void GiveTreatment(ATreatment* pTreatment);
	bool IsTreatmentExist(ETreatmentType pTreatmentType);

private:
	void CollectPatient(APatient* pPatient);
	void RemovePatient(APatient* pPatient);
	APatient* GetFirstAvailablePatient();

};
