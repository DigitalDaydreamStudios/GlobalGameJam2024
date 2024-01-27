// Fill out your copyright notice in the Description page of Project Settings.


#include "SlothSentry.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/EngineTypes.h"

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

	PerformRaycast();
}

// Called to bind functionality to input
void ASlothSentry::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASlothSentry::PerformRaycast()
{
	FHitResult HitResult;
	FVector StartTrace = GetActorLocation();
	FVector EndLocation = StartTrace + (GetActorForwardVector() * EnemyViewDistance);
	FCollisionQueryParams TraceParams;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	bool RaycastHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), StartTrace, EndLocation, UEngineTypes::ConvertToTraceType(ECC_Pawn), false, ActorsToIgnore, EDrawDebugTrace::ForOneFrame, HitResult, true, FLinearColor::Red, FLinearColor::Green, 0.0f);
	if (RaycastHit && HitResult.GetActor() != nullptr && HitResult.GetActor()->ActorHasTag("Player"))
	{
		PlayerSpotted();
	}
}

void ASlothSentry::PlayerSpotted()
{
	SearchingForPlayer = false;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Player Spotted")));
}