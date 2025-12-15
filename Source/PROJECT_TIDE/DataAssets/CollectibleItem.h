// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

#include "CollectibleItem.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	TypeA UMETA(DisplayName = "Fish"),
	TypeB UMETA(DisplayName = "Trash")
};

UCLASS()
class PROJECT_TIDE_API ACollectibleItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectibleItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Collectible Data")
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Collectible Data")
	FString ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Collectible Data")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Collectible Data")
	UStaticMeshComponent* ItemMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Collectible Data")
	UTexture2D* ItemIcon;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;

};
