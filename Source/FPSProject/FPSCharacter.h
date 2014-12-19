// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()
    
public:
    
    AFPSCharacter(const FObjectInitializer& ObjectInitializer);
    
    virtual void BeginPlay() override;
	
    UFUNCTION()
    void OnStartJump();
    
    UFUNCTION()
    void OnStopJump();
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    class UCameraComponent* FirstPersonCameraComponent;
    
    // Pawn mesh: 1st person view, arms seen only by self
    UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
    class USkeletalMeshComponent* FirstPersonMesh;
    
protected:
    
    virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
    
    UFUNCTION()
    void MoveForward(float Val);
    
    UFUNCTION()
    void MoveRight(float Val);
	
};
