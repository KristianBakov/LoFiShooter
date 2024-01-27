// Fill out your copyright notice in the Description page of Project Settings.


#include "LoFiPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include <EnhancedInputSubsystems.h>
#include "Components/CapsuleComponent.h"
#include "LoFiShooterGameModeBase.h"
#include "Gun.h"

// Sets default values
ALoFiPlayerCharacter::ALoFiPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALoFiPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	LoFiPlayerController = Cast<APlayerController>(Controller);
	//Setup input mapping context
	if (LoFiPlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LoFiPlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
			UE_LOG(LogTemp, Warning, TEXT("Setup input successfully"));
		}
	}

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
}

// Called every frame
void ALoFiPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALoFiPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(InputMove, ETriggerEvent::Triggered, this, &ALoFiPlayerCharacter::Move);
	EnhancedInputComponent->BindAction(InputLook, ETriggerEvent::Triggered, this, &ALoFiPlayerCharacter::Look);
	EnhancedInputComponent->BindAction(InputJump, ETriggerEvent::Started, this, &ALoFiPlayerCharacter::Jump);
	EnhancedInputComponent->BindAction(InputShoot, ETriggerEvent::Triggered, this, &ALoFiPlayerCharacter::Shoot);
}

float ALoFiPlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health left: %f"), Health);

	if (IsDead())
	{
		ALoFiShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ALoFiShooterGameModeBase>();
		if (GameMode)
		{
			GameMode->PawnKilled(this);
		}

		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	return DamageToApply;
}

void ALoFiPlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D InputVector = Value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), InputVector.X);
	AddMovementInput(GetActorRightVector(), InputVector.Y);
}

void ALoFiPlayerCharacter::Look(const FInputActionValue& Value)
{
	AddControllerPitchInput(Value.Get<FVector2D>().Y);
	AddControllerYawInput(Value.Get<FVector2D>().X);
}

void ALoFiPlayerCharacter::Jump(const FInputActionValue& Value)
{
}

void ALoFiPlayerCharacter::Shoot()
{
	Gun->PullTrigger();
}

bool ALoFiPlayerCharacter::IsDead() const
{
	return Health <= 0;
}

