// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSProject.h"
#include "FPSGameMode.h"
#include "Engine.h"

AFPSGameMode::AFPSGameMode(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
    
}

void AFPSGameMode::StartPlay()
{
    Super::StartPlay();
    
    StartMatch();
    
    if(GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Hello Logging"));
    }
}


