// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

//Camera
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

//Inputs
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"

#include "PlayerCharacter.generated.h"

UCLASS()
class PROJECT_TIDE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
    UCapsuleComponent* CapsuleComp;
	
    UPROPERTY(EditAnywhere, Category = "Visuals")
    UStaticMeshComponent* PlayerMesh;
	
    UPROPERTY(VisibleAnywhere, Category="Camera")
    USpringArmComponent* SpringArmComp;
   
    UPROPERTY(VisibleAnywhere, Category="Camera")
   	UCameraComponent* CameraComp;
	
    UPROPERTY(EditAnywhere, Category="Inputs")
    UInputMappingContext* DefaultMappingContext;


};
