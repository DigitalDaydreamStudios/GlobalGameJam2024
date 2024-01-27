// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SlothSentry.generated.h"

UCLASS()
class METALGEARSLOTH_API ASlothSentry : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASlothSentry();

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//UPawnMovementComponent* PawnMovementComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void PerformRaycast();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Create an float distance for the raycast to be able to travel
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Raycast")
	float EnemyViewDistance = 1000.0f;
};
