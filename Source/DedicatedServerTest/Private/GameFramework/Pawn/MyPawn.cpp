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

	//send Client camera rotation to server for replicate pawn's rotation
	//CurrentTransform = GetActorTransform();
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(class UInputComponent* inputComponent)
{
	Super::SetupPlayerInputComponent(inputComponent);
	//inputComponent->BindAxis("MoveForward", this, &AMyPawn::MoveForward);
	//inputComponent->BindAxis("Turn", this, &AMyPawn::AddControllerYawInput);
	//inputComponent->BindAxis("LookUp", this, &AMyPawn::AddControllerPitchInput);
}



void AMyPawn::AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce) {

	if (!Controller || ScaleValue == 0.0f) return;
	//Super::AddMovementInput(WorldDirection, ScaleValue, bForce);
	// Make sure only the Client Version calls the ServerRPC
	//bool AActor::HasAuthority() const { return (Role == ROLE_Authority); }
	if (Role < ROLE_Authority && IsLocallyControlled()) {
		//run on client, call PRC to server
		Server_AddMovementInput(WorldDirection, ScaleValue, bForce);
	}
	else {
		//run on server
		Super::AddMovementInput(WorldDirection, ScaleValue, bForce);
		SetActorRotation(WorldDirection.Rotation());
		//will call OnRep_TransformChange
		CurrentTransform = GetActorTransform();
		//CurrentTransform.SetRotation(WorldDirection.ToOrientationQuat());
		
	}


	//if (GEngine->GetNetMode(GetWorld()) != NM_DedicatedServer)
	//{
		//code to run on non-dedicated servers
	//}



	

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
	///** Secondary condition to check before considering the replication of a lifetime property. */
	//enum ELifetimeCondition
	//{
	//	COND_None = 0,		// This property has no condition, and will send anytime it changes
	//	COND_InitialOnly = 1,		// This property will only attempt to send on the initial bunch
	//	COND_OwnerOnly = 2,		// This property will only send to the actor's owner
	//	COND_SkipOwner = 3,		// This property send to every connection EXCEPT the owner
	//	COND_SimulatedOnly = 4,		// This property will only send to simulated actors
	//	COND_AutonomousOnly = 5,		// This property will only send to autonomous actors
	//	COND_SimulatedOrPhysics = 6,		// This property will send to simulated OR bRepPhysics actors
	//	COND_InitialOrOwner = 7,		// This property will send on the initial packet, or to the actors owner
	//	COND_Custom = 8,		// This property has no particular condition, but wants the ability to toggle on/off via SetCustomIsActiveOverride
	//	COND_Max = 9,
	//};
	DOREPLIFETIME(AMyPawn, CurrentTransform);
	//DOREPLIFETIME_CONDITION( AMyPawn, CurrentTransform, COND_None );
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
