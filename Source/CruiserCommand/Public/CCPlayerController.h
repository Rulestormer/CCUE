// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "CCPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CRUISERCOMMAND_API ACCPlayerController : public APlayerController
{
	GENERATED_BODY()

	ACCPlayerController(const FObjectInitializer& ObjectInitializer);

public:
	FVector targetPos;		// Local position on the ship to path towards.
	class APlayerCamera* camera;
	APawn* OrigPawn;		// The player's normal pawn that is controlled when the player isn't controlling a ship.

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	void PlayerTick(float DeltaTime);
	// Had to override SetViewTarget to prevent it being overwritten at the start of the game.
	virtual void SetViewTarget(class AActor* NewViewTarget, FViewTargetTransitionParams TransitionParams = FViewTargetTransitionParams()) override;

	/** Sets up the player camera. Spawns the camera class and sets the view target */
	void SetupCamera();

	/** Called when you right click in the world to order the character to move */
	void OrderMove();
	
	/** Navigate player to the given world location (Server Version) */
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetNewMoveDestination(const FVector DestLocation);

	/** Temporary function to change control from unit to ship. Might be used in the future but called by entering a console. */
	void ControlShip();

	// Player camera functions. These exist because binding an axis input directly to the camera function seemed to fail.
	void PlayerZoomIn();
	void PlayerZoomOut();
	void PlayerCameraForward(float f);
	void PlayerCameraRight(float f);
};
