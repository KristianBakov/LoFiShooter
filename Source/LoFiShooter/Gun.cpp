// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(!OwnerPawn) return;
	AController* OwnerController = OwnerPawn->GetController();
	if(!OwnerController) return;

	FVector BulletStartPoint;
	FRotator BulletStartRotation;
	OwnerController->GetPlayerViewPoint(BulletStartPoint, BulletStartRotation);

	FVector BulletEnd = BulletStartPoint + BulletStartRotation.Vector() * MaxRange;
	//TODO: ADD line trace
	FHitResult HitResult;
	bool bShotSuccess = GetWorld()->LineTraceSingleByChannel(HitResult, BulletStartPoint, BulletEnd, ECollisionChannel::ECC_GameTraceChannel1);
	if (bShotSuccess)
	{
		DrawDebugPoint(GetWorld(), HitResult.ImpactPoint, 20, FColor::Red, true);
	}
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

