// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SlothInstance.generated.h"

/**
 * 
 */
UCLASS()
class METALGEARSLOTH_API USlothInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Clench Mini Game")
	void StartClenchMiniGame();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Clench Mini Game")
	void GameOver();
};
