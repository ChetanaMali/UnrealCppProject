// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterType.h"	// header file of enum
#include "MainCharAnimInstance.generated.h"		// this generated header file is alwase in end of all header file


UCLASS()
class LEARNINGCPPPROJECT_API UMainCharAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;	// its a overrided virtual function by default script
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly)
	class AMainCharacter* MainCharacter;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	class UCharacterMovementComponent* MainCharacterMovement;		//Uscene component

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float GroundSpeed;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool IsFalling;
	       
	UPROPERTY(BlueprintReadOnly, Category = "Movement | Charecter State") // we use'|' this to make subtopic
	ECharecterState CharectarState;
};
