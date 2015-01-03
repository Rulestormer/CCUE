// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "CCHUD.generated.h"

/**
 * 
 */
UCLASS()
class CRUISERCOMMAND_API ACCHUD : public AHUD
{
	GENERATED_BODY()

	ACCHUD(const FObjectInitializer& ObjectInitializer);

	// The edge of the border of edge scrolling hitboxes to add around the screen. 
	// Effectively determining how close to the edge you can move your cursor before the camera starts moving.
	float CameraEdge;

	/** Creates all the hitboxes for handling edge scrolling */
	void CreateCameraHitboxes();
	/** Helper function to add a hitbox and optionally draw a rect at the same position for debugging purposes */
	void DrawHitBox(FVector2D pos, FVector2D size, FName name, bool showOverlay, FLinearColor color);

	virtual void DrawHUD() override;

	virtual void ReceiveHitBoxBeginCursorOver(const FName BoxName) override;
	virtual void ReceiveHitBoxEndCursorOver(const FName BoxName) override;
	
};
