// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Collider as the Root Component
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComp);

	//StaticMesh
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	BaseMesh->SetupAttachment(CapsuleComp);

	//Just in case the pawn spawns above the floor
	IsGrounded = false;

}

void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!IsGrounded)
	{
		AddGravity(GravityDirection, GravitySpeed);
	}
	
}

void ABasePawn::DoMove(FVector moveDirection, float moveSpeed)
{
	UE_LOG(LogTemp, Log, TEXT("DoMove from BasePawn (moveDirection = %s , moveSpeed = %f)"),*moveDirection.ToString(), moveSpeed);
	FVector moveVector = moveDirection.GetSafeNormal() * moveSpeed * GetWorld()->GetDeltaSeconds();
	AddActorLocalOffset(moveVector, true);
}

void ABasePawn::DoTurn(float turnDirection, float turnSpeed)
{
	FRotator deltaRotation = FRotator(0, 0.0f, 0);
	deltaRotation.Yaw = turnDirection * turnSpeed * GetWorld()->GetDeltaSeconds();
	AddActorLocalRotation(deltaRotation, false);
	UE_LOG(LogTemp, Log, TEXT("DoTurn(turnDirection = %f , turnSpeed = %f)"),turnDirection, turnSpeed);
}

void ABasePawn::AddGravity(FVector moveDirection, float moveSpeed)
{
	// UE_LOG(LogTemp, Log, TEXT("AddGravity from BasePawn (moveDirection = %s , moveSpeed = %f)"),*moveDirection.ToCompactString(), moveSpeed);
	FVector moveVector = moveDirection.GetSafeNormal() * moveSpeed;
	FHitResult hitResult;
	AddActorLocalOffset(moveVector, true, &hitResult);
	if (UStaticMeshComponent* meshComp = Cast<UStaticMeshComponent>(hitResult.GetComponent()))
	{
		if (meshComp->ComponentHasTag("Ground"))
		{
			IsGrounded = true;
		}
	}
}

