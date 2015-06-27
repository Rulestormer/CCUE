// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "CruiserCommand.h"
#include "CruiserCommandCharacter.h"
#include "CCPlayerController.h"
#include "Ship.h"
#include "PlayerProxy.h"

//////////////////////////////////////////////////////////////////////////
// ACruiserCommandCharacter
// -- Currently just a visual class or something. It's weird.

ACruiserCommandCharacter::ACruiserCommandCharacter() {
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera. If this is removed, the turning will be instant.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	bReplicates = true;
	
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;


}

void ACruiserCommandCharacter::BeginPlay() {
	Super::BeginPlay();
	for (TActorIterator<AShip> ObstacleItr(GetWorld()); ObstacleItr; ++ObstacleItr) { // TODO: VERY STUPID
		UE_LOG(LogTemp, Warning, TEXT("Set ship"));
		CurrentShip = *ObstacleItr;
	}
}

void ACruiserCommandCharacter::Tick(float DeltaTime) {
	//SetActorRotation(CurrentShip->GetTransform().GetRotation().Rotator());
}

ACCPlayerController* ACruiserCommandCharacter::GetPlayerController() {
	return PC;
}

void ACruiserCommandCharacter::SetPlayerController(ACCPlayerController* pc) {
	PC = pc;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ACruiserCommandCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent) {
	// Set up gameplay key bindings. Currently none
	check(InputComponent);
}


void ACruiserCommandCharacter::TurnAtRate(float Rate) {
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}


