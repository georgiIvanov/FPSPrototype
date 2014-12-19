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

