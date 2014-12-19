// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSProject.h"
#include "FPSCharacter.h"

AFPSCharacter::AFPSCharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
    // create camera component
    FirstPersonCameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
    FirstPersonCameraComponent->AttachParent = GetCapsuleComponent();
    
    // position the camera a bit above the eyes
    FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, BaseEyeHeight);
    // allow the pawn to control rotation
    FirstPersonCameraComponent->bUsePawnControlRotation = true;
    
    FirstPersonMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("FirstPersonMesh"));
    FirstPersonMesh->SetOnlyOwnerSee(true);
    FirstPersonMesh->AttachParent = FirstPersonCameraComponent;
    FirstPersonMesh->bCastDynamicShadow = false;
    FirstPersonMesh->CastShadow = false;
    
    // full sized mesh cannot be seen by owner
    GetMesh()->SetOwnerNoSee(true);
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
    InputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::OnStartJump);
    InputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::OnStopJump);
    InputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::OnFire);
}

void AFPSCharacter::OnStartJump()
{
    bPressedJump = true;
}

void AFPSCharacter::OnStopJump()
{
    bPressedJump = false;
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

void AFPSCharacter::OnFire()
{
    if(ProjectileClass == nullptr)
    {
        return;
    }
    
    // get camera transform
    FVector CameraLoc;
    FRotator CameraRot;
    GetActorEyesViewPoint(CameraLoc, CameraRot);
    
    // MuzzleOffset is in camera space, so transform it to world space
    // before offsetting from the camera to find the final muzzle position
    FVector const MuzzleLocation = CameraLoc + FTransform(CameraRot).TransformVector(MuzzleOffset);
    FRotator MuzzleRotation = CameraRot;
    // skew the aim a bit upwards
    MuzzleRotation.Pitch += 10.f;
    UWorld* const World = GetWorld();
    if(World)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = Instigator;
        // spawn projectile at muzzle
        AFPSProjectile* const Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
        if(Projectile)
        {
            // find launch direction
            FVector const LaunchDir = MuzzleRotation.Vector();
            Projectile->InitVelocity(LaunchDir);
        }
    }
}