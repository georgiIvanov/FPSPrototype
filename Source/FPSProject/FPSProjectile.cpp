// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSProject.h"
#include "FPSProjectile.h"

AFPSProjectile::AFPSProjectile(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
    CollisionComp = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("SphereComp"));
    CollisionComp->InitSphereRadius(15.0f);
    CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
    CollisionComp->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHit);
    RootComponent = CollisionComp;
    
    ProjectileMovement = ObjectInitializer.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("ProjectileComp"));
    ProjectileMovement->UpdatedComponent = CollisionComp;
    ProjectileMovement->InitialSpeed = 3000.f;
    ProjectileMovement->MaxSpeed = 3000.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = true;
    ProjectileMovement->Bounciness = 0.3;
    
    InitialLifeSpan = 3.f;
}

void AFPSProjectile::InitVelocity(const FVector &ShootDirection)
{
    if(ProjectileMovement)
    {
        // set the projectile's velocity to the desired direction
        ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;
    }
}

void AFPSProjectile::OnHit(class AActor *OtherActor, class UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
    if(OtherActor && (OtherActor != this) && OtherComp)
    {
        OtherComp->AddImpulseAtLocation(ProjectileMovement->Velocity * 100.f, Hit.ImpactPoint);
    }
}
