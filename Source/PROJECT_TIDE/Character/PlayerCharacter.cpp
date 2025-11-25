// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"


#include "Components/CapsuleComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "GameFramework/CharacterMovementComponent.h"

#define LogOnScreen(x) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT(x)));

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Collision Capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationYaw = true;
    bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	//Create Spring Arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 1.0f;
	SpringArm->bUsePawnControlRotation = false;

	//Create Camera and attach to Spring Arm
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = true;
	

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		//Move Inputs
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		//Look Inputs
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}

}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	DoMove(MovementVector.X, MovementVector.Y);
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector LookVector = Value.Get<FVector>();
	float lookX = LookVector.X;
	float lookY = LookVector.Y;
	UE_LOG(LogTemp, Warning, TEXT("DoLookAction X: %f & Y: %f"), lookX, lookY);

	DoTurn(lookX);
	DoMouseLook(lookY);
}

void APlayerCharacter::DoMove(float Right, float Forward)
{
	if (GetController())
	{
		//Fins which way is facing forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation (0, Rotation.Yaw,0);

		//Get Forward and Right vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis( EAxis::X );
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis( EAxis::Y );

		//Add Movement
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void APlayerCharacter::DoMouseLook(float LookY)
{
	if (GetController())
	{
		AddControllerPitchInput(-LookY * MouseSensitivity * GetWorld()->GetDeltaSeconds());

		// Clamp pitch
		FRotator ControlRot = Controller->GetControlRotation();
		ControlRot.Pitch = FMath::ClampAngle(ControlRot.Pitch, -MaxLookYAngle, MaxLookYAngle);
		Controller->SetControlRotation(ControlRot);
	}
}

void APlayerCharacter::DoTurn(float LookX)
{
	if (GetController())
	{
		AddControllerYawInput(LookX * MouseSensitivity * GetWorld()->GetDeltaSeconds());
	}
}

void APlayerCharacter::DoJumpStart()
{
	Jump();
}

void APlayerCharacter::DoJumpEnd()
{
	StopJumping();
}

