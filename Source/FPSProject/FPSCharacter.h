// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "FPSProjectile.h"
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
    
    UFUNCTION()
    void OnFire();
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    class UCameraComponent* FirstPersonCameraComponent;
    
    // Pawn mesh: 1st person view, arms seen only by self
    UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
    class USkeletalMeshComponent* FirstPersonMesh;
    
    // Gun muzzle's offset from the camera location
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    FVector MuzzleOffset;
    
    // Projectile class to spawn
    UPROPERTY(EditDefaultsOnly, Category = Projectile)
    TSubclassOf<class AFPSProjectile> ProjectileClass;
    
protected:
    
    virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
    
    UFUNCTION()
    void MoveForward(float Val);
    
    UFUNCTION()
    void MoveRight(float Val);
	
};
