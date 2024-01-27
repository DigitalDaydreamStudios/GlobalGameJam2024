// Fill out your copyright notice in the Description page of Project Settings.


#include "SlothSentry.h"

// Sets default values
ASlothSentry::ASlothSentry()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASlothSentry::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASlothSentry::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASlothSentry::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

