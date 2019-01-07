// Fill out your copyright notice in the Description page of Project Settings.

#include "Mannequin.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "Weapons/Gun.h"

// Sets default values
AMannequin::AMannequin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent	
	FPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCamera"));
	FPCamera->SetupAttachment((USceneComponent*)GetCapsuleComponent());
	FPCamera->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FPCamera->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	FPArms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPArms"));
	FPArms->SetOnlyOwnerSee(true);				// Set so only owner can see mesh
	FPArms->SetupAttachment(FPCamera);			// Attach mesh to FPCamera
	FPArms->bCastDynamicShadow = false;			// Disallow mesh to cast dynamic shadows
	FPArms->CastShadow = false;					// Disallow mesh to cast other shadows
	FPArms->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	FPArms->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);
}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();
	
	if (GunBlueprint == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Gun blueprint missing."));
		return;
	}
	// Create a gun actor
	GunActor = GetWorld()->SpawnActor<AGun>(GunBlueprint);
	if (IsPlayerControlled())
	{
		GunActor->AttachToComponent(FPArms, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));			// Attach gun to arms
	}
	else
	{
		GunActor->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));			// Attach gun to arms
	}
	GunActor->FPAnimInstance = FPArms->GetAnimInstance();
	GunActor->TPAnimInstance = GetMesh()->GetAnimInstance();

	if (InputComponent != NULL)
	{
		InputComponent->BindAction("Fire", IE_Pressed, this, &AMannequin::PullTrigger);
	}
}

// Called every frame
void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMannequin::UnPossessed()
{
	Super::UnPossessed();

	// Attach gun to arms
	GunActor->AttachToComponent(FPArms, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
}

void AMannequin::PullTrigger()
{
	GunActor->OnFire();
}