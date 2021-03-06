// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSProject.h"
#include "FPSGameMode.h"
#include "Engine.h"
#include "FPSHUD.h"

AFPSGameMode::AFPSGameMode(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
    // set default pawn class to our Blueprinted character
    static ConstructorHelpers::FObjectFinder<UBlueprint> PlayerPawnObject(TEXT("Blueprint'/Game/Blueprints/Actors/BP_FPSCharacter.BP_FPSCharacter'"));
    if(PlayerPawnObject.Object != NULL)
    {
        DefaultPawnClass = (UClass*)PlayerPawnObject.Object->GeneratedClass;
    }
    
    HUDClass = AFPSHUD::StaticClass();
    
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


