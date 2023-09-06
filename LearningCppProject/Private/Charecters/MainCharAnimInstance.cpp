// Fill out your copyright notice in the Description page of Project Settings.


#include "Charecters/MainCharAnimInstance.h"
#include "Charecters/MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "kismet/kismetMathLibrary.h"

void UMainCharAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	//it happen in intetialize state its like an begine function so we add the all properties and function into that maincharecter variable 
	MainCharacter = Cast<AMainCharacter>(TryGetPawnOwner()); // we cast the maim charecter 
	if (MainCharacter) {
		MainCharacterMovement = MainCharacter->GetCharacterMovement();  // and from that casting we take getcharectermovement()
	}
}

void UMainCharAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);	// its like tick function
	if (MainCharacterMovement) {
		
		GroundSpeed = UKismetMathLibrary::VSizeXY(MainCharacterMovement->Velocity); //assign the velocity or speed in Ground speed variable
		IsFalling = MainCharacterMovement->IsFalling();	// 
		CharectarState = MainCharacter->GetCharecterState();	//get charecter state like equip or unequip sword or mainy things
	}
}
