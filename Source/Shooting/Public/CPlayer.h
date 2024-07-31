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
	// �ʿ�Ӽ� : �¿�, ���� ����, �̵��ӵ�
	float h = 0;
	float v = 0;
	float speed = 500;

	// �¿��Է� ó�� �Լ�
	void Horizontal(float value);
	// �����Է� ó�� �Լ�
	void Vertical(float value);

	// �߻��ư�Է� ó�� �Լ�
	void Fire();

	// �ʿ�Ӽ� : �Ѿ˰���
	UPROPERTY(EditAnywhere, Category="Bullet")
	TSubclassOf<class ACBullet> bulletFactory;
};
