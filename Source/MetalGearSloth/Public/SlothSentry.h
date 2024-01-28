// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SlothSentry.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerSpottedDelegate);

class ATargetPoint;
class AAIController;

UCLASS()
class METALGEARSLOTH_API ASlothSentry : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASlothSentry();

	UPROPERTY(BlueprintAssignable)
	FPlayerSpottedDelegate OnPlayerSpotted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ATargetPoint*> PatrolLocations;

protected:
	int currentPatrolLocationIndex = 0;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void PerformRaycast();
	void PlayerSpotted();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Create an float distance for the raycast to be able to travel
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sentry")
	float EnemyViewDistance = 1000.0f;

	// Set the width of the sentry cone based on this float in degrees
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sentry")
	float SentryConeWidth = 90.0f;

	// A Boolean to check if the Sentry is searching for the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sentry")
	bool SearchingForPlayer = true;

	UFUNCTION(BlueprintCallable)
	void MoveToNextPatrolLocation();

	UFUNCTION(BlueprintCallable)
	FVector GetNextPatrolLocation();
};
