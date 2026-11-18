// Copyright 2026 Joseph's. All Rights Reserved.

// Corridor Platformer kit + ALS-Refactored - sample 1 of 2. Copy into your own game module (see README.md next to this file).
// ALS-Refactored's movement component with the kit's movement on top: rails, wall runs and ropes (MOVE_Custom), the slide speed
// and, if you raise the two scales below, the kit's jump gravity. Everything else stays ALS's.
#pragma once

#include "AlsCharacterMovementComponent.h"
#include "CorridorMoveSolver.h"
#include "AlsCorridorMovementComponent.generated.h"

UCLASS()
class UAlsCorridorMovementComponent : public UAlsCharacterMovementComponent, public FCorridorMoveSolver, public ICorridorMover
{
	GENERATED_BODY()

public:
	/** Gravity x this while rising / falling. 1 = ALS's own jump arc (the kit's hero uses 3.3 / 1.08 with its 1157 cm/s jump). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Corridor", meta=(ClampMin=0))
	float RiseGravityScale = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Corridor", meta=(ClampMin=0))
	float FallGravityScale = 1.f;

	virtual FCorridorMoveSolver* GetCorridorSolver() override { return this; }
	virtual UCharacterMovementComponent* SolverMover() const override { return const_cast<UAlsCorridorMovementComponent*>(this); }

	virtual float GetGravityZ() const override
	{
		return SolveGravityZ(Super::GetGravityZ(), RiseGravityScale, FallGravityScale);
	}

	virtual float GetMaxSpeed() const override
	{
		return SolveMaxSpeed(Super::GetMaxSpeed()); // x Slide Speed Scale while the kit's slide runs
	}

	virtual FVector NewFallVelocity(const FVector& InitialVelocity, const FVector& Gravity, float DeltaTime) const override
	{
		return SolveFallVelocity(Super::NewFallVelocity(InitialVelocity, Gravity, DeltaTime), InitialVelocity, DeltaTime);
	}

protected:
	virtual void PhysCustom(float DeltaTime, int32 Iterations) override
	{
		if (GetTraversal() != ECorridorTraversal::None)
		{
			SolvePhysCustom(DeltaTime); // on a rail / wall / rope
		}
		else
		{
			Super::PhysCustom(DeltaTime, Iterations); // ALS's own custom mode (mantling)
		}
	}

	virtual void PhysicsRotation(float DeltaTime) override
	{
		if (GetTraversal() == ECorridorTraversal::None)
		{
			Super::PhysicsRotation(DeltaTime); // a traversal faces along its path itself
		}
	}
};
