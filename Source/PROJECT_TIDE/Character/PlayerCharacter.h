// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"

//PreProcessor Derivatives for Inputs
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Quaternion.h"

#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class PROJECT_TIDE_API APlayerCharacter : public ABasePawn
{
	GENERATED_BODY()
	
public:
	APlayerCharacter();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;

private:

	UPROPERTY(VisibleAnywhere, Category="Camrera")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category="Camrera")
	UCameraComponent* CameraComp;

	//Values for Inputs
	UPROPERTY(EditAnywhere, Category="Inputs")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category="Inputs")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category="Inputs")
	UInputAction* LookAction;

	//Values for Mouse Looks
	UPROPERTY(EditAnywhere, Category = "Player Movement")
	float MouseSensitivity = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Player Movement")
	float  MaxLookAngle = 80.0f;
	//Values for Players
	UPROPERTY(EditAnywhere, Category = "Player Movement")
	float MoveSpeed = 100.0f;

public:
	//Input Functions
	void DoMoveAction(const FInputActionValue& actionValue);
	
	void DoLookAction(const FInputActionValue& actionValue);

	void DoMouseLook (float turndirection);
	
	
};
