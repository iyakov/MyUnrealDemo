// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XYZProject/Data/Types/MyNewStruct.h"
#include "MyFirstActor.generated.h"

UCLASS()
class XYZPROJECT_API AMyFirstActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyFirstActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetRandomRotationRate();
	
	UPROPERTY(EditAnywhere)
	int MyFirstProperty = 100;
	
	UPROPERTY(EditAnywhere)
	FColor TextColor = FColor::Red;
	
	UPROPERTY(EditAnywhere)
	float MinimumRotationRate = 20.0f;
	
	UPROPERTY(EditAnywhere)
	float MaximumRotationRate = 200.0f;

	UPROPERTY(EditAnywhere, Category = "AXYZ")
	FMyNewStruct MyStruct;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	float CurrentRotationRate = 0.0f;
};
