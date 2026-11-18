// Copyright 2026 Joseph's. All Rights Reserved.

// Corridor Platformer kit + ALS-Refactored - sample 2 of 2.
#include "AlsCorridorCharacter.h"

#include "AlsCorridorMovementComponent.h"
#include "CorridorHero.h"
#include "EnhancedInputComponent.h"

AAlsCorridorCharacter::AAlsCorridorCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UAlsCorridorMovementComponent>(CharacterMovementComponentName))
{
	CorridorHero = CreateDefaultSubobject<UCorridorHeroComponent>(TEXT("CorridorHero"));
}

void AAlsCorridorCharacter::Jump()
{
	if (!CorridorHero->MoveJump())
	{
		Super::Jump();
	}
}

bool AAlsCorridorCharacter::IsMantlingAllowedToStart_Implementation() const
{
	return !CorridorHero->IsSlamming() && Super::IsMantlingAllowedToStart_Implementation();
}

void AAlsCorridorCharacter::NotifyLocomotionModeChanged(const FGameplayTag PreviousLocomotionMode)
{
	if (CorridorHero->IsSlamming())
	{
		LocomotionState.Velocity.Z = 0.0; // the slam's own landing: a normal ALS landing, not its fall ragdoll / roll
	}
	Super::NotifyLocomotionModeChanged(PreviousLocomotionMode);
}

void AAlsCorridorCharacter::SetupPlayerInputComponent(UInputComponent* Input)
{
	Super::SetupPlayerInputComponent(Input);
	if (UEnhancedInputComponent* Enhanced = Cast<UEnhancedInputComponent>(Input))
	{
		if (SpinAction)
		{
			Enhanced->BindAction(SpinAction, ETriggerEvent::Started, CorridorHero.Get(), &UCorridorHeroComponent::MoveSpin);
		}
		if (SlideAction)
		{
			Enhanced->BindAction(SlideAction, ETriggerEvent::Started, CorridorHero.Get(), &UCorridorHeroComponent::MoveSlide);
		}
	}
}
