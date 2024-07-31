// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CPlayer.generated.h"

UCLASS()
class SHOOTING_API ACPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* BodyMesh;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* SpaceShipMesh;
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* FirePosition;

public:
	// 필요속성 : 좌우, 상하 방향, 이동속도
	float h = 0;
	float v = 0;
	float speed = 500;

	// 좌우입력 처리 함수
	void Horizontal(float value);
	// 상하입력 처리 함수
	void Vertical(float value);

	// 발사버튼입력 처리 함수
	void Fire();

	// 필요속성 : 총알공장
	UPROPERTY(EditAnywhere, Category="Bullet")
	TSubclassOf<class ACBullet> bulletFactory;
};
