// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterType.h"
#include "MainCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AItem;
class UAnimMontage;
class AWeapon;
class AEnemy;

UCLASS()
class LEARNINGCPPPROJECT_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void SetBoxCollision(ECollisionEnabled::Type CollisionEnable);

protected:
	virtual void BeginPlay() override;

	/*
	* Callbacks for Input Function
	*Movement Variable use in protected brecause we can only acces by this class or inhereded class
	*/
	void MoveForward(float Value); // Axis Mapping
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void EKeyPressed();		// Action mapping no need of any float value
	void Attack();

	/*
	* Play Montage Function
	*/
	void PlayAttackMontage();
	UFUNCTION(BlueprintCallable)
	void EndAttack();
	bool CanAttack();

	void PlayEquipMontage(FName SectionName);
	bool CanArm();
	bool CanDisArm();

	UFUNCTION(BlueprintCallable)
	void Arm();

	UFUNCTION(BlueprintCallable)
	void Disarm();

	UFUNCTION(BlueprintCallable)
	void FinishEquipping();


private:
	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* SpringArm; //spring arm for Third person controller camera

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* ViewCamera;

	UPROPERTY(VisibleInstanceOnly) // we can only see in instance means detail panal of actor
		AItem* OverlappingItem; 

	ECharecterState CharacterState = ECharecterState::ECS_Unequipped;		//Enum state

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EActionState ActionState = EActionState::EAS_Unoccupied;

	/*
	*	Animation Montages
	*/
	UPROPERTY(EditDefaultsOnly , Category = Montages)
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* EquipMontage;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
		AWeapon* EquipedWeapon;

	AEnemy* Enemy;
public:
	//FORCEINLINE means its a inline function in unreal means rite whole functiom in one line
	FORCEINLINE void SetOverlapingItem(AItem* Item) { OverlappingItem = Item; }		
	FORCEINLINE ECharecterState GetCharecterState() const { return CharacterState; }
};
