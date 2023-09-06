// Fill out your copyright notice in the Description page of Project Settings.


#include "Charecters/MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Items/Item.h"
#include "Items/Weapons/Weapon.h"
#include "Animation/AnimInstance.h"
#include "Components/BoxComponent.h"
#include "Enemy\Enemy.h"

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// we set pitch roll and yaw for player movement
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	// In this we create default sub object and attach to root component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 400.f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>("ViewCamera");
	ViewCamera->SetupAttachment(SpringArm);
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

/*
	Set Collision Enable and Disable Of Weapon to avoid collision of weapon when player is not attacking
	I take reference of weapon and weapon box and the from that Set the collision Enable or disable from BP
*/
void AMainCharacter::SetBoxCollision(ECollisionEnabled::Type CollisionEnable)
{
	if (EquipedWeapon && EquipedWeapon->GetWeaponBox())
	{
		EquipedWeapon->GetWeaponBox()->SetCollisionEnabled(CollisionEnable);
	}
}

void AMainCharacter::MoveForward(float Value)
{
	//If playe equip sword and try to move forward then he cannt be move
	if (ActionState != EActionState::EAS_Unoccupied) return;

	if (Controller && Value != 0.f) {
		//here we take yaw rotation mean z rot to move forword direction
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); 
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::MoveRight(float Value)
{
	if (ActionState != EActionState::EAS_Unoccupied) return;

	if (Controller && Value != 0.f) {
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotaion(0.f, ControlRotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotaion).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::Turn(float Value)
{
	AddControllerYawInput(Value); //inbuild function from unreal
}

void AMainCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AMainCharacter::EKeyPressed()
{
	AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem);
	if (OverlappingWeapon) {
		OverlappingWeapon->Equip(GetMesh(), FName("RightHandSocket"));
		CharacterState = ECharecterState::ECS_EquippedOneHandedWeapon;
		EquipedWeapon = OverlappingWeapon;
		OverlappingItem = nullptr;// because onece the wepon equip it also run the else part to arm and disarm
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1, 10, FColor::Red, FString(TEXT("Else vala Part")));
		if (CanDisArm())
		{
			GEngine->AddOnScreenDebugMessage(1, 10, FColor::Red, FString(TEXT("if vala Part")));
			PlayEquipMontage(FName("Unequip"));
			CharacterState = ECharecterState::ECS_Unequipped;
			ActionState = EActionState::EAS_EquppingWeapon;
			ActionState =  EActionState::EAS_Unoccupied;
		}
		else if(CanArm())
		{
			GEngine->AddOnScreenDebugMessage(1, 10, FColor::Red, FString(TEXT("else if vala Part")));
			PlayEquipMontage(FName("Equip"));
			CharacterState = ECharecterState::ECS_EquippedOneHandedWeapon;
			ActionState = EActionState::EAS_EquppingWeapon;
			ActionState = EActionState::EAS_Unoccupied;
		}
	}

}

bool AMainCharacter::CanArm()
{
	return CharacterState == ECharecterState::ECS_Unequipped && 
		ActionState == EActionState::EAS_Unoccupied &&
		EquipedWeapon;
}

bool AMainCharacter::CanDisArm()
{
	return CharacterState != ECharecterState::ECS_Unequipped && 
		ActionState == EActionState::EAS_Unoccupied;
}

void AMainCharacter::Arm()
{
	if (EquipedWeapon)
	{
		//
		EquipedWeapon->AttachMeshToSocket(GetMesh(), FName("RightHandSocket"));
	}
	
}

void AMainCharacter::Disarm()
{
	if (EquipedWeapon)
	{
		EquipedWeapon->AttachMeshToSocket(GetMesh(), FName("SpineSocket"));
		
	}
}

void AMainCharacter::FinishEquipping()
{
	ActionState = EActionState::EAS_Unoccupied;
}

void AMainCharacter::Attack()
{	
	if (CanAttack()) {
		PlayAttackMontage();
		ActionState = EActionState::EAS_Attacking;
		if (Enemy)
		{
			Enemy->GetHit();
		}
		
	}
}
void AMainCharacter::EndAttack()
{
	//Once the attack end it return to unoccupide state dueto this repeat action can prevent to start
	ActionState = EActionState::EAS_Unoccupied;
}

bool AMainCharacter::CanAttack()
{
	return ActionState == EActionState::EAS_Unoccupied && CharacterState != ECharecterState::ECS_Unequipped;
}



void AMainCharacter::PlayAttackMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && AttackMontage) {
		AnimInstance->Montage_Play(AttackMontage);
		//PlayAnimMontage(AttackMontage);
		int32 Sections = FMath::RandRange(0, 1);
		FName SectionName;
		// Switch for randomly pic one attack section(animation) to attack
		switch (Sections) {
		case 0:
			SectionName = FName("Attack1");
			break;
		case 1:
			SectionName = FName("Attack2");
			break;
		default:
			break;
		}
		AnimInstance->Montage_JumpToSection(SectionName, AttackMontage);
	}
}

void AMainCharacter::PlayEquipMontage(FName SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && EquipMontage)
	{
		AnimInstance->Montage_Play(EquipMontage);
		AnimInstance->Montage_JumpToSection(SectionName);
	}
}





void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &AMainCharacter::MoveRight);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &AMainCharacter::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &AMainCharacter::LookUp);

	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(FName("Equip"), IE_Pressed, this, &AMainCharacter::EKeyPressed);
	PlayerInputComponent->BindAction(FName("Attack"), IE_Pressed, this, &AMainCharacter::Attack);
}



