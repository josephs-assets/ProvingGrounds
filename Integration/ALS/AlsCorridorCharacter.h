// Copyright 2026 Joseph's. All Rights Reserved.

// Corridor Platformer kit + ALS-Refactored - sample 2 of 2. Copy into your own game module (see README.md next to this file).
#pragma once

#include "AlsCharacterExample.h"
#include "AlsCorridorCharacter.generated.h"

class UCorridorHeroComponent;
class UInputAction;

/**
 * ALS-Refactored's example character + the Corridor kit. ALS keeps its locomotion, animation, camera and input; the kit adds
 * crates, enemies, checkpoints and kill volumes (the Corridor Hero component), its double jump, spin, slide and slam
 * (Corridor Hero > 4. Moves) and rails, wall runs and ropes (UAlsCorridorMovementComponent).
 */
UCLASS()
class AAlsCorridorCharacter : public AAlsCharacterExample
{
	GENERATED_BODY()

public:
	AAlsCorridorCharacter(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Corridor")
	TObjectPtr<UCorridorHeroComponent> CorridorHero;

	/** Optional: your Spin and Slide input actions (add their keys to your Input Mapping Context). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Corridor")
	TObjectPtr<UInputAction> SpinAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Corridor")
	TObjectPtr<UInputAction> SlideAction;

	/** ALS's jump input ends here: a rail hop / wall or rope leap or the kit's double jump first, else ALS's own jump. */
	virtual void Jump() override;

	/** No ALS mantle grab while the kit's slam drops (the slam would end on a ledge). */
	virtual bool IsMantlingAllowedToStart_Implementation() const override;

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* Input) override;

	/** The slam lands at 1286 cm/s: no ALS land ragdoll (above 1000 cm/s) or land roll (above 700) from that landing. */
	virtual void NotifyLocomotionModeChanged(FGameplayTag PreviousLocomotionMode) override;
};
