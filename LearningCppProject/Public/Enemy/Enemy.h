// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class LEARNINGCPPPROJECT_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemy();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void GetHit();


private:
	/*
	*	Animation Montages
	*/
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* HitReactMontage;


protected:
	virtual void BeginPlay() override;
	/*
	* Play Montage Function
	*/
	void PlayHitReactMontage(const FName& SectionName);

	
public:	
	//At the bottem we create the getter and setter using FORCEINLINE

};
