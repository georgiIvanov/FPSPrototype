// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSProject.h"
#include "FPSHUD.h"

AFPSHUD::AFPSHUD(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
    static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("Texture2D'/Game/Props/crosshair.crosshair'"));
    CrosshairTex = CrosshairTexObj.Object;
    
}

void AFPSHUD::DrawHUD()
{
    Super::DrawHUD();
    
    // draw very simple crosshair
    // find center of the Canvas
    const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
    
    // offset by half the texture's dimensions so that the center of
    // the texture aligns with the texture of the canvas
    const FVector2D CrosshairDrawPosition(Center.X - (CrosshairTex->GetSurfaceWidth() * 0.5f),
                                          Center.Y - (CrosshairTex->GetSurfaceHeight() * 0.5f));
    
    // draw the crosshair
    FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
    // from tutorial mode is SE_BLEND_Translucent
    TileItem.BlendMode = SE_BLEND_Translucent;
    Canvas->DrawItem(TileItem);
}


