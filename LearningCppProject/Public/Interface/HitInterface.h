// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HitInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHitInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LEARNINGCPPPROJECT_API IHitInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void GetHit() = 0; // we use 0 to create this func as a pure virtual function

};
