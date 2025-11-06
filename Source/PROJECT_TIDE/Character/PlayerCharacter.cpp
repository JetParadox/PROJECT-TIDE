// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

APlayerCharacter::APlayerCharacter()
{
	//Setting Up Camera
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComp->SetupAttachment(CapsuleComp);
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComp->SetupAttachment(SpringArmComp);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Setting Up Connection Between Player Controller and Mappings
	if (APlayerController* playerController = Cast<APlayerController>(Controller))
	{
		if (ULocalPlayer* localPlayer = Cast<ULocalPlayer>(playerController->GetLocalPlayer()))
		{
			if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(localPlayer))
			{
				subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);

	if (UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(playerInputComponent))
	{
		// //Move Action
		enhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::DoMoveAction);
		//Look Action
		enhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::DoLookAction);
	}
}

void APlayerCharacter::DoMoveAction(const FInputActionValue& actionValue)
{
	FVector inputVector = actionValue.Get<FVector>();
	DoMove(inputVector, MoveSpeed);
	// UE_LOG(LogTemp, Warning, TEXT("DoMoveAction (FVector): %s"), *InputVector.ToString());
}

void APlayerCharacter::DoLookAction(const FInputActionValue& actionValue)
{
	FVector inputVector = actionValue.Get<FVector>();
	float lookX = inputVector.X;
	float lookY = inputVector.Y;

	DoTurn(lookX,MouseSensitivity);
	DoMouseLook(lookY);
	UE_LOG(LogTemp, Warning, TEXT("DoLookAction X: %f & Y: %f"), lookX, lookY);
}

void APlayerCharacter::DoMouseLook(float turndirection)
{
	FRotator NewRotation = CameraComp->GetRelativeRotation();
	NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + turndirection * MouseSensitivity * GetWorld()->GetDeltaSeconds(), -1*MaxLookAngle, MaxLookAngle);
	CameraComp->SetRelativeRotation(NewRotation);
}


