// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/Weapon.h"
#include "Charecters/MainCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AWeapon::AWeapon()
{
	/*
	* Create and Set collision presets for Weapon Box
	*/
	WeaponBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Box"));
	WeaponBox->SetupAttachment(GetRootComponent());
	WeaponBox->SetCollisionEnabled(ECollisionEnabled::NoCollision); //set the collision enable 
	WeaponBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);	// set collision object type
	WeaponBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap); // set All channel on overlap
	WeaponBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore); /// set pawn to isgnore

	/*
	* Create And Set to root Start and End Box traces for weapon line trace to detact collision
	*/
	BoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace Start"));
	BoxTraceStart->SetupAttachment(GetRootComponent());

	BoxTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace End"));
	BoxTraceEnd->SetupAttachment(GetRootComponent());
	
}



void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	//We bind the Overlaping Function
	WeaponBox->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnBoxOverlap);
}

void AWeapon::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FVector Start = BoxTraceStart->GetComponentLocation(); 
	FVector End = BoxTraceEnd->GetComponentLocation();

	/*
		Dinamic Array we can add or remove Actors dinamicaly in this array
	*/
	TArray<AActor*> ActorsToIgnore;		
	ActorsToIgnore.Add(this);
	FHitResult OutHit; //its a Structure 

	/*
		Line trace function 
		On overlap the weapon to detect collision On enemy or other things 
		we trace line fron weapon start point to end point
	*/
	UKismetSystemLibrary::BoxTraceSingle(
		this,
		Start,
		End,
		FVector(5.f, 5.f, 5.f),
		BoxTraceStart->GetComponentRotation(),
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		OutHit,
		true
	);
}



void AWeapon::OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AWeapon::OnSphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}


void AWeapon::Equip(USceneComponent* Parent, FName SockateName)
{
	AttachMeshToSocket(Parent, SockateName);
	ItemState = EItemState::EIS_Equiped;
	if (EquipSound)
	{
		/*
			we use to Play a sound on equiping weapon
		*/
		UGameplayStatics::PlaySoundAtLocation(
			this,
			EquipSound,
			GetActorLocation()
		);
	}
	if (Sphere)
	{
		Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

}

void AWeapon::AttachMeshToSocket(USceneComponent* Parent, const FName& SockateName)
{
	FAttachmentTransformRules TransFormRule(EAttachmentRule::SnapToTarget, true);
	ItemMesh->AttachToComponent(Parent, TransFormRule, SockateName);
}


