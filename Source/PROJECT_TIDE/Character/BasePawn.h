// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/CapsuleComponent.h"

#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class PROJECT_TIDE_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, Category="Gravity")
	FVector GravityDirection = FVector(0.0f,0.0f,-1.0f);

	UPROPERTY(EditAnywhere, Category="Gravity")
	float GravitySpeed = 9.8f;

private:
	bool IsGrounded;
	
protected:
	
	void DoMove(FVector moveDirection, float moveSpeed);

	void DoTurn(float turnDirection, float turnSpeed);

	void AddGravity(FVector moveDirection, float moveSpeed);

};
