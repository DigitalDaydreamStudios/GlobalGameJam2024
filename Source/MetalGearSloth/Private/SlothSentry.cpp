// Fill out your copyright notice in the Description page of Project Settings.


#include "SlothSentry.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "AIController.h"

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
			//if (TargetActor)
			//{
			//	MoveReq.SetGoalActor(TargetActor);
			//}
			//else
			//{
			//	MoveReq.SetGoalLocation(Destination);
			//}
			MoveReq.SetGoalLocation(PatrolLocations[0]->GetActorLocation());
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

