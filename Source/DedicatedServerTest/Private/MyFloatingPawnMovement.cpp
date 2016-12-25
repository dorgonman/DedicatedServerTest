// Fill out your copyright notice in the Description page of Project Settings.

#include "DedicatedServerTest.h"
#include "MyFloatingPawnMovement.h"
#include "MyBlueprintFunctionLibrary.h"


void UMyFloatingPawnMovement::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {

	if (GetNetMode() == ENetMode::NM_DedicatedServer)
	{
		//UMyBlueprintFunctionLibrary::AddOnScreenDebugMessage("NM_DedicatedServer");
		//UMyBlueprintFunctionLibrary::AddOnScreenDebugMessage(
			////"NM_DedicatedServer(%d) GetActorLocation: (%f, %f, %f)",
		//	(int)GetNetMode(), Velocity.X, Velocity.Y, Velocity.Z);

		if (!Velocity.IsZero()) {
			auto actorLocation = UpdatedComponent->GetComponentLocation();
			UMyBlueprintFunctionLibrary::AddOnScreenDebugMessage("NM_DedicatedServer(%d) GetActorLocation: (%f, %f, %f)",
				(int)GetNetMode(), actorLocation.X, actorLocation.Y, actorLocation.Z);
		}
		//UE_LOG(LogTemp, Log, TEXT("NM_DedicatedServer(%d) GetActorLocation: (%f, %f, %f"), 
			//(int)GetNetMode(), actorLocation.X, actorLocation.Y, actorLocation.Z);
	}
	else 
	{
		//UMyBlueprintFunctionLibrary::AddOnScreenDebugMessage("NM_Client");
		if (!Velocity.IsZero()) {
			auto actorLocation = UpdatedComponent->GetComponentLocation();
			UMyBlueprintFunctionLibrary::AddOnScreenDebugMessage("NM_Client(%d) GetActorLocation: (%f, %f, %f)",
				(int)GetNetMode(), actorLocation.X, actorLocation.Y, actorLocation.Z);
		}
		//UE_LOG(LogTemp, Log, TEXT("NM_Client(%d) GetActorLocation: (%f, %f, %f"), 
			//(int)GetNetMode(), actorLocation.X, actorLocation.Y, actorLocation.Z);
	}
	if (ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	Super::Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent)
	{
		return;
	}

	const AController* Controller = PawnOwner->GetController();
	if (Controller)
	{
		// apply input for local players but also for AI that's not following a navigation path at the moment
		if (Controller->IsFollowingAPath() == false)
		{
			ApplyControlInputToVelocity(DeltaTime);
		}
		// if it's not player controller, but we do have a controller, then it's AI
		// (that's not following a path) and we need to limit the speed
		else if (IsExceedingMaxSpeed(MaxSpeed) == true)
		{
			Velocity = Velocity.GetUnsafeNormal() * MaxSpeed;
		}

		LimitWorldBounds();
		bPositionCorrected = false;

		// Move actor
		FVector Delta = Velocity * DeltaTime;

		if (!Delta.IsNearlyZero(1e-6f))
		{
			const FVector OldLocation = UpdatedComponent->GetComponentLocation();
			const FQuat Rotation = UpdatedComponent->GetComponentQuat();

			FHitResult Hit(1.f);
			SafeMoveUpdatedComponent(Delta, Rotation, true, Hit);

			if (Hit.IsValidBlockingHit())
			{
				HandleImpact(Hit, DeltaTime, Delta);
				// Try to slide the remaining distance along the surface.
				SlideAlongSurface(Delta, 1.f - Hit.Time, Hit.Normal, Hit, true);
			}

			// Update velocity
			// We don't want position changes to vastly reverse our direction (which can happen due to penetration fixups etc)
			if (!bPositionCorrected)
			{
				const FVector NewLocation = UpdatedComponent->GetComponentLocation();
				Velocity = ((NewLocation - OldLocation) / DeltaTime);
			}
		}

		// Finalize
		UpdateComponentVelocity();
	}

}