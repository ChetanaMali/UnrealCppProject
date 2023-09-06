// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "LearningCppProject/DebugMacros.h"
#include "Components/SphereComponent.h"
#include "Charecters/MainCharacter.h"

// Sets default values
AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
	//Create static mesh in constructor
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	RootComponent = ItemMesh;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());
	Sphere->SetSphereRadius(150.f);
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereOverlapBegin);// Binding of callback function
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AItem::OnSphereOverlapEnd);
}


void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	runningTime += DeltaTime;
	
	if (ItemState == EItemState::EIS_Hovering)
	{
		AddActorWorldOffset(FVector(0.f, 0.f, TransformedSin()));
	}
	
}

float AItem::TransformedSin()
{
	return Ampletude * FMath::Sin(runningTime * TimeConstant);
}

float AItem::TransformedCos()
{
	return Ampletude * FMath::Cos(runningTime * TimeConstant);
}

void AItem::OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainCharacter* MainCharater = Cast<AMainCharacter>(OtherActor);
	if (MainCharater) {
		MainCharater->SetOverlapingItem(this);
	}

}

void AItem::OnSphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMainCharacter* MainCharater = Cast<AMainCharacter>(OtherActor);
	if (MainCharater) {
		MainCharater->SetOverlapingItem(nullptr);
	}
}

