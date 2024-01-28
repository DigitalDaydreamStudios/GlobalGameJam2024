// Fill out your copyright notice in the Description page of Project Settings.


#include "SlothSentry.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/EngineTypes.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "AIController.h"
// #include "Runtime/UMG/Public/UMG.h"
#include "SlothInstance.h"

ASlothSentry::ASlothSentry()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASlothSentry::BeginPlay()
{
	Super::BeginPlay();
	currentPatrolLocationIndex = -1;
	//MoveToNextPatrolLocation();
}

// Called every frame
void ASlothSentry::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (SearchingForPlayer)
	{
		PerformRaycast();
	}
}

// Called to bind functionality to input
void ASlothSentry::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASlothSentry::PerformRaycast()
{
	int32 NumberOfRays = 20;
	FVector StartTrace = GetActorLocation();
	FVector ForwardDirection = GetActorForwardVector();
	FRotator BaseRotation = ForwardDirection.Rotation();
	FCollisionQueryParams TraceParams;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	for (int32 i = 0; i < NumberOfRays; i++)
	{
		 // Calculate the rotation for this ray
		float AdjustConeToFaceFront = 45.0f;
		float AngleDegrees = -SentryConeWidth + AdjustConeToFaceFront + (SentryConeWidth * i / (NumberOfRays - 1));
		FRotator RayRotation = BaseRotation + FRotator(0, AngleDegrees, 0);

		// Calculate the end point for this ray
		FVector EndLocation = StartTrace + RayRotation.Vector() * EnemyViewDistance;

		// Perform the line trace
		FHitResult HitResult;
		bool RaycastHit = UKismetSystemLibrary::LineTraceSingle(
			GetWorld(),
			StartTrace,
			EndLocation,
			UEngineTypes::ConvertToTraceType(ECC_Pawn),
			false,
			ActorsToIgnore,
			EDrawDebugTrace::ForOneFrame,
			HitResult,
			true,
			FLinearColor::Red,
			FLinearColor::Green,
			0.0f
		);

		// Check if the ray hit a player
		if (RaycastHit && HitResult.GetActor() != nullptr && HitResult.GetActor()->ActorHasTag("Player"))
		{	
			PlayerSpotted();
		}
	}
}

void ASlothSentry::PlayerSpotted()
{
	SearchingForPlayer = false;
	OnPlayerSpotted.Broadcast();

	// Get the SlothInstance
	USlothInstance* SlothInstance = Cast<USlothInstance>(GetGameInstance());
	if (SlothInstance != nullptr)
	{
		// Call the StartClenchMiniGame function
		SlothInstance->StartClenchMiniGame();
	}


	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Player Spotted")));
}

void ASlothSentry::MoveToNextPatrolLocation()
{
	if (PatrolLocations.Num() > 0)
	{
		AAIController* AIController = Cast<AAIController>(GetController());
		if (AIController)
		{
			UWorld* World = GetWorld();
			//MyObj = NewObject<UAIAsyncTaskBlueprintProxy>(World);

			bool bStopOnOverlap = true;

			FAIMoveRequest MoveReq;
			MoveReq.SetUsePathfinding(true);
			MoveReq.SetAcceptanceRadius(5.f);
			MoveReq.SetReachTestIncludesAgentRadius(bStopOnOverlap);
			if (currentPatrolLocationIndex >= (PatrolLocations.Num() - 1)) { currentPatrolLocationIndex = 0; }
			else { currentPatrolLocationIndex++; }
			//if (TargetActor)
			//{
			//	MoveReq.SetGoalActor(TargetActor);
			//}
			//else
			//{
			//	MoveReq.SetGoalLocation(Destination);
			//}
			MoveReq.SetGoalLocation(PatrolLocations[currentPatrolLocationIndex]->GetActorLocation());
			MoveReq.SetNavigationFilter(AIController->GetDefaultNavigationFilterClass());

			FPathFollowingRequestResult ResultData = AIController->MoveTo(MoveReq);
			//switch (ResultData.Code)
			//{
			//case EPathFollowingRequestResult::RequestSuccessful:
			//	MyObj->AIController = AIController;
			//	MyObj->AIController->ReceiveMoveCompleted.AddDynamic(MyObj, &UAIAsyncTaskBlueprintProxy::OnMoveCompleted);
			//	MyObj->MoveRequestId = ResultData.MoveId;
			//	break;

			//case EPathFollowingRequestResult::AlreadyAtGoal:
			//	World->GetTimerManager().SetTimer(MyObj->TimerHandle_OnInstantFinish, MyObj, &UAIAsyncTaskBlueprintProxy::OnAtGoal, 0.1f, false);
			//	break;

			//case EPathFollowingRequestResult::Failed:
			//default:
			//	World->GetTimerManager().SetTimer(MyObj->TimerHandle_OnInstantFinish, MyObj, &UAIAsyncTaskBlueprintProxy::OnNoPath, 0.1f, false);
			//	break;
			//}
		}
	}
	return;
}

FVector ASlothSentry::GetNextPatrolLocation()
{
	if (PatrolLocations.Num() == 0) { return GetActorLocation(); }

	if (currentPatrolLocationIndex >= (PatrolLocations.Num() - 1)) { currentPatrolLocationIndex = 0; }
	else { currentPatrolLocationIndex++; }

	return PatrolLocations[currentPatrolLocationIndex]->GetActorLocation();
}
