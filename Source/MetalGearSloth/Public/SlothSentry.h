// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SlothSentry.generated.h"

class ATargetPoint;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ATargetPoint*> PatrolLocations;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
