// Fill out your copyright notice in the Description page of Project Settings.

#include "CruiserCommand.h"
#include "CruiserCommandCharacter.h"
#include "Ship.h"

AShip::AShip() {
	bReplicates = true;

	PrimaryActorTick.bCanEverTick = true;
	bMovingForward = false;
	TargetRotation = this->GetActorRotation();
	RotationSpeed = 50;
	MovementSpeed = 100;
	CurrentSpeed = 0.0f;
}

void AShip::SetupPlayerInputComponent(class UInputComponent* InputComponent) {
	// Set up gameplay key bindings. Currently none
	check(InputComponent);

	UE_LOG(LogTemp, Warning, TEXT("input components init"));
	InputComponent->BindAction("ShipAccelerate", IE_Pressed, this, &AShip::MoveForward);
	InputComponent->BindAction("ShipDecelerate", IE_Pressed, this, &AShip::StopMoveForward);
}

void AShip::Tick(float delta) {
	if (CurrentSpeed > 0) {
		if (Role == ROLE_Authority) {
			AddActorLocalOffset(FVector(CurrentSpeed * MovementSpeed * delta, 0, 0));
		}
		//		GetWorld()->GetNavigationSystem()->Build();		// This is probably pretty bad. For some reason the navmesh doesn't rebuild until you stop moving forward. 
																// When moving navmeshes is a thing, this will probably not be needed anymore
	}
	//FQuat nextRot = FQuat::Slerp(TargetRotation, GetActorQuat(), delta);
	FRotator nextRot = FMath::RInterpConstantTo(GetActorRotation(), TargetRotation, delta, RotationSpeed);
	if (Role == ROLE_Authority)	{
		//UE_LOG(LogTemp, Warning, TEXT("Rotation speed: %f"), TargetRotation.Yaw);
	}
	if (abs(GetTransform().GetRotation().Rotator().Yaw - nextRot.Yaw) > 0.001) {
		UE_LOG(LogTemp, Warning, TEXT("Rotating towards: %f"), nextRot.Yaw);
		FRotator oldRot = GetActorRotation();
		SetActorRotation(nextRot);
		for (TActorIterator<ACruiserCommandCharacter> ObstacleItr(GetWorld()); ObstacleItr; ++ObstacleItr) { // TODO: VERY STUPID, maybe?
			if (&(*ObstacleItr->CurrentShip) == this) {			// Only rotate if they're on this ship
				//(*ObstacleItr)->SetActorRotation((*ObstacleItr)->GetActorRotation() + (nextRot - oldRot));
			}
		}
	}
}

void AShip::MoveForward_Implementation() {
	UE_LOG(LogTemp, Warning, TEXT("Moving forward"));
	bMovingForward = true;
}

bool AShip::MoveForward_Validate() {
	return true;
}

void AShip::StopMoveForward_Implementation() {
	UE_LOG(LogTemp, Warning, TEXT("Stop Moving forward"));
	bMovingForward = false;
}

bool AShip::StopMoveForward_Validate() {
	return true;
}


void AShip::EnterShip(ACruiserCommandCharacter* character) {
	character->CurrentShip = this;
	//character->SetActorLocation = this->GetActorLocation + this->EnterPosition;
}

FRotator AShip::GetTargetRotation() {
	return TargetRotation;
}

/*void AShip::SetTargetRotation(FRotator newRot) {
	TargetRotation = newRot;
	UE_LOG(LogTemp, Warning, TEXT("Set rotation to: %f"), newRot.Yaw);
}*/
/*
void AShip::SetTargetRotation_Implementation(FRotator newRot){
	UE_LOG(LogTemp, Warning, TEXT("Set rotation to: %f"), newRot.Yaw);
	TargetRotation = newRot;
}

bool AShip::SetTargetRotation_Validate(FRotator newRot) {
	return true;
}*/

void AShip::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to Everyone
	DOREPLIFETIME(AShip, TargetRotation);
	DOREPLIFETIME(AShip, bMovingForward);
}