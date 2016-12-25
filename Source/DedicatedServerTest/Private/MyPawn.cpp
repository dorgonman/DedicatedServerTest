// Fill out your copyright notice in the Description page of Project Settings.

#include "DedicatedServerTest.h"
#include "MyPawn.h"
#include "Net/UnrealNetwork.h"

#include "MyBlueprintFunctionLibrary.h"
#include "MyFloatingPawnMovement.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//CharacterMovement = CreateDefaultSubobject<UCharacterMovementComponent>(TEXT("CharMoveComp"));
	if (CharacterMovement)
	{
		//CharacterMovement->PrimaryComponentTick.bCanEverTick = true;
		//RootComponent->
		//CharacterMovement->UpdatedComponent = RootComponent;
		//CharacterMovement->SetUpdatedComponent(RootComponent);
		//CharacterMovement->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}


	//FloatingPawnMovement = CreateDefaultSubobject<UMyFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
	//UFloatingPawnMovement only support local control, so we implement UMyFloatingPawnMovement to remove the restriction
	FloatingPawnMovement = CreateDefaultSubobject<UMyFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
	//FloatingPawnMovement->UpdatedComponent = nullptr;
	//void UMovementComponent::OnRegister()
	// Auto-register owner's root component if no update component set.



}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	//this->SetActorLocation(ReplicatedMovement.Location);
	//CharacterMovement->TickComponent(DeltaTime);
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(class UInputComponent* inputComponent)
{
	Super::SetupPlayerInputComponent(inputComponent);

}



void AMyPawn::AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce) {

	if (!Controller || ScaleValue == 0.0f) return;
	//Super::AddMovementInput(WorldDirection, ScaleValue, bForce);
	// Make sure only the Client Version calls the ServerRPC

	//if (Role == ROLE_Authority) {
	//
	//}
	//else {
	//
	//	Super::AddMovementInput(WorldDirection, ScaleValue, bForce);
	//}
	//Super::AddMovementInput(WorldDirection, ScaleValue, bForce);
	if (Role < ROLE_Authority && IsLocallyControlled()) {
		Server_AddMovementInput(WorldDirection, ScaleValue, bForce);
	}
	else {
		//run on server
		Super::AddMovementInput(WorldDirection, ScaleValue, bForce);
		CurrentTransform = GetActorTransform();

	}



	

}



bool AMyPawn::Server_AddMovementInput_Validate(FVector WorldDirection, float ScaleValue, bool bForce) {
	return true;
}

void AMyPawn::Server_AddMovementInput_Implementation(FVector WorldDirection, float ScaleValue, bool bForce) {
	//AddMovementInput(WorldDirection, ScaleValue, bForce);
	AddMovementInput(WorldDirection, ScaleValue, bForce);

}



UPawnMovementComponent* AMyPawn::GetMovementComponent() const
{
	//auto test = Super::GetMovementComponent();
	return FloatingPawnMovement;
}


void AMyPawn::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyPawn, CurrentTransform);
}

void AMyPawn::OnRep_ReplicatedMovement()
{
	Super::OnRep_ReplicatedMovement();
	// Skip standard position correction if we are playing root motion, OnRep_RootMotion will handle it.
	//if (!IsPlayingNetworkedRootMotionMontage()) // animation root motion
	//{
	//	if (!CharacterMovement || !CharacterMovement->CurrentRootMotion.HasActiveRootMotionSources()) // root motion sources
	//	{
	//		Super::OnRep_ReplicatedMovement();
	//	}
	//}
}



void AMyPawn::OnRep_TransformChange() {
	SetActorTransform(CurrentTransform);
	//SetActorRotation(CurrentRotation);
}
