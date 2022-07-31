// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class AMyPlayer;

UCLASS()
class HOSPITALRUSH_API AMyPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AMyPlayerController();
 
    
public:
    UPROPERTY(EditAnywhere)  TSubclassOf<AMyPlayer> playerBP;

private:
    AMyPlayer* player;

    //#Movement
    bool isPressed;
    FVector currentMousePosition;
    FVector pressedMousePosition;
    FVector movePosition;
    FVector mouseDirection;
    float moveOffset;
    float moveSpeed;
    float mouseStartToCurrentDistance;
    float touchMovementThreshold;
    FVector MovementVector;


private:

    // ~Overrides: APlayerController
    virtual void SetupInputComponent() override;

    void OnMousePressed();

    void OnMouseReleased();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    void PlayerMovement(float DeltaTime);

};

