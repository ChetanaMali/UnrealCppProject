#pragma once

UENUM(BlueprintType) //usable in blueprint
enum class ECharecterState: uint8 //unsign int 8 bit
{
	ECS_Unequipped UMETA(DisplayName = "Unequipped"),		// to set BP displaye name of this enum state use UMETA
	ECS_EquippedOneHandedWeapon UMETA(DisplayName = "Equipped One Handed Weapon"),
	ECS_EquippedTwoHandedWeapon UMETA(DisplayName = "Equipped Two Handed Weapon")
};

UENUM(BlueprintType)
enum class EActionState: uint8
{
	EAS_Unoccupied UMETA(DisplayName = "Occupied"),
	EAS_Attacking UMETA(DisplayName = "Attcking"),
	EAS_EquppingWeapon UMETA(DisplayName = "EquppingWeapon")
};