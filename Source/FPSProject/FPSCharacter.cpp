// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSProject.h"
#include "FPSCharacter.h"

AFPSCharacter::AFPSCharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
    
}

void AFPSCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    if(GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("We are using FPSCharacter."));
    }
}

void AFPSCharacter::SetupPlayerInputComponent(class UInputComponent *InputComponent)
{
    InputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
    InputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);
    InputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
    InputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);
}

void AFPSCharacter::MoveForward(float Value)
{
    if(Controller != nullptr && Value != 0.f)
    {
        // find out which way is forward
        FRotator Rotation = Controller->GetControlRotation();
        
        // limit pitch when walking or falling
        if(GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
        {
            Rotation.Pitch = 0.f;
        }
        
        // add movement in that direction
        const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void AFPSCharacter::MoveRight(float Value)
{
    if(Controller != nullptr && Value != 0.f)
    {
        // find out which way is right
        FRotator Rotation = Controller->GetControlRotation();
        // add movement in that direction
        const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
        AddMovementInput(Direction, Value);
    }
}