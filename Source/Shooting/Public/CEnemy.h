// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEnemy.generated.h"

UCLASS()
class SHOOTING_API ACEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComp;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* BodyMesh;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings")
	float speed = 500;
	UPROPERTY()
	AActor* target;
	FVector dir;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// 적이 충돌했을 때 폭발효과를 재생하고 싶다.
	// 폭발효과 공장
	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UParticleSystem* bombFactory;
};
