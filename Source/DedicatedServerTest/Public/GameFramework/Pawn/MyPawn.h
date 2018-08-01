// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"
//https://answers.unrealengine.com/questions/43869/pawn-replication.html
UCLASS()
class DEDICATEDSERVERTEST_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* inputComponent) override;


		virtual void AddMovementInput(FVector WorldDirection, float ScaleValue = 1.0f, bool bForce = false) override;


	UFUNCTION(Server, Reliable, WithValidation)
		void Server_AddMovementInput(FVector WorldDirection, float ScaleValue = 1.0f, bool bForce = false);

	//UFUNCTION(NetMulticast, unreliable)
		//void Multicast_AddMovementInput(FVector WorldDirection, float ScaleValue = 1.0f, bool bForce = false);
public: //actor: network
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void OnRep_ReplicatedMovement() override;
public:
	virtual UPawnMovementComponent* GetMovementComponent() const override;
private:


	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* StaticMeshComponent;
	/** Movement component used for movement logic in various movement modes (walking, falling, etc), containing relevant settings and functions to control movement. */
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCharacterMovementComponent* CharacterMovement;


	//UProjectileMovementComponent

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UFloatingPawnMovement* FloatingPawnMovement;


private: //replicate transform
	UPROPERTY(Transient, ReplicatedUsing = OnRep_TransformChange)
		FTransform CurrentTransform;


	UFUNCTION()
		void OnRep_TransformChange();
};
