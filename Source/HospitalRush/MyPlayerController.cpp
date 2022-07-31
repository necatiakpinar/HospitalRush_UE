// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "MyPlayer.h"
#include "Kismet/GameplayStatics.h"
//#include "UObject/ConstructorHelpers.h"

AMyPlayerController::AMyPlayerController()
{
    isPressed = false;
    moveSpeed = 100.0f;
    moveOffset = 6.0f;
    touchMovementThreshold = 1.0f;

}

void AMyPlayerController::BeginPlay()
{

    if (playerBP == nullptr)      UE_LOG(LogTemp, Warning, TEXT("NULLLLL BP!!"));

    //player = playerBP.GetDefaultObject();

  /*  FActorSpawnParameters SpawnInfo;
    SpawnInfo.Owner = NULL;
    const FTransform SpawnTransform(FQuat::Identity, FVector(0.0f, 10.0f, 100.0f));

    player = GetWorld()->SpawnActor<AMyPlayer>(playerBP,SpawnTransform);
    */

    if (UWorld* world = GetWorld())
    {
        TArray<AActor*> outputActors;
        UGameplayStatics::GetAllActorsOfClass(world, AMyPlayer::StaticClass(), outputActors);

        if (outputActors.Num() > 0 && outputActors[0] != nullptr)
            player = Cast<AMyPlayer>(outputActors[0]);


        //  ActivateTouchInterface()
    }


    if (player)
        Possess(player);

    SetShowMouseCursor(true);
}

void AMyPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //DeprojectMousePositionToWorld(currentMousePosition, mouseDirection);
    GetMousePosition(currentMousePosition.X, currentMousePosition.Z);
    //PlayerMovement(DeltaTime);
    //UE_LOG(LogTemp, Warning, TEXT("%s"), *currentMousePosition.ToString());

}

void AMyPlayerController::PlayerMovement(float DeltaTime)
{
    if (isPressed)
    {

        mouseStartToCurrentDistance = FVector::Distance(pressedMousePosition, currentMousePosition);
        //UE_LOG(LogTemp, Warning, TEXT("%f"), mouseStartToCurrentDistance);
        if (mouseStartToCurrentDistance > touchMovementThreshold)
        {
            FVector direction = currentMousePosition - pressedMousePosition;
            MovementVector = FVector(-direction.Z, direction.X,0.0f ).GetSafeNormal();
            player-> SetActorLocation(MovementVector * moveSpeed * DeltaTime);
            UE_LOG(LogTemp, Warning, TEXT("%s"), *MovementVector.ToString());
        }

    }
}

void AMyPlayerController::SetupInputComponent()
{
    // Always call this.
    Super::SetupInputComponent();

    InputComponent->BindAction("MousePressed", IE_Pressed, this, &AMyPlayerController::OnMousePressed);
    InputComponent->BindAction("MouseReleased", IE_Released, this, &AMyPlayerController::OnMouseReleased);

}

void AMyPlayerController::OnMousePressed()
{
    isPressed = true;
    pressedMousePosition = currentMousePosition;

}

void AMyPlayerController::OnMouseReleased()
{
    isPressed = false;
    movePosition = FVector(0.0f);

}


