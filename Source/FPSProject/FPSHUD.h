// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "FPSHUD.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API AFPSHUD : public AHUD
{
	GENERATED_BODY()
	
	// crosshair asset pointer
    UTexture2D* CrosshairTex;
    
public:
    AFPSHUD(const FObjectInitializer& ObjectInitializer);
	
    virtual void DrawHUD() override;
};
