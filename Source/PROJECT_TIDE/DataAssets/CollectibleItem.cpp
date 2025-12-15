// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectibleItem.h"

// Sets default values
ACollectibleItem::ACollectibleItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Gets Data From Data Asset to Create the Collectible Item
	SphereComp = CreateDefaultSubobject<USphereComponent>(FName("CapsuleComp"));
	SetRootComponent(SphereComp);
	SphereComp->InitSphereRadius(20.0f);
	
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	ItemMesh->SetupAttachment(SphereComp);
	
	
}

// Called when the game starts or when spawned
void ACollectibleItem::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACollectibleItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

