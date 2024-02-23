// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Simple_ShooterGameModeBase.h"


// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
	Gun = GetWorld()-> SpawnActor<AGun>(GunClass);
	GetMesh() -> HideBoneByName(TEXT("weapon_R"),EPhysBodyOp::PBO_None);
	Gun -> AttachToComponent(GetMesh(), FAttachmentTransformRules:: KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun -> SetOwner(this);

}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent -> BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent -> BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent -> BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent -> BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent -> BindAction(TEXT("Jump"),EInputEvent:: IE_Pressed, this, &ACharacter::Jump); 
	PlayerInputComponent -> BindAxis(TEXT("LookUpRate"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent -> BindAxis(TEXT("LookRightRate"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent -> BindAction(TEXT("Shoot"),EInputEvent:: IE_Pressed, this,  & AShooterCharacter::Shoot);

}

void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}


void AShooterCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld() -> GetDeltaSeconds());
}

void AShooterCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld() -> GetDeltaSeconds());
}

void AShooterCharacter::Shoot()
{
	Gun -> PullTrigger();
}

float AShooterCharacter::TakeDamage(
    	float DamageAmount,
    	struct FDamageEvent const & DamageEvent,
    	class AController * EventInstigator,
    	AActor * DamageCauser)
{
		float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
		DamageApplied = FMath::Min(Health, DamageApplied);
		Health -= DamageApplied;
			
		if(Ded())
		{
			ASimple_ShooterGameModeBase* GameMode = GetWorld() -> GetAuthGameMode<ASimple_ShooterGameModeBase>();
			if(GameMode != nullptr)
			{
				GameMode -> PawnKiller(this);
			}
			DetachFromControllerPendingDestroy();
			GetCapsuleComponent() -> SetCollisionEnabled(ECollisionEnabled :: NoCollision);
			
			
		}

		return DamageApplied;
}

bool AShooterCharacter:: Ded() const
{
	if(Health == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float AShooterCharacter::GetHealthPercent() const
{
	return Health/MaxHealth;
}

