// Fill out your copyright notice in the Description page of Project Settings.


#include "CBullet.h"

// Sets default values
ACBullet::ACBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// BodyMesh �׸��� StaticMeshComponent �� ���� ��� �ʹ�.
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	// BodyMesh �� Root �� ����ϰ� �ʹ�.
	RootComponent = BodyMesh;
	// ũ�Ⱚ ����
	BodyMesh->SetRelativeScale3D(FVector(1, 0.25f, 0.75f));

	// ����� Static Mesh �����͸� �о�鿩�� ������Ʈ�� �Ҵ��ϰ�ʹ�.
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	// �ε��� �����ϸ�
	if (TempMesh.Succeeded())
	{
		// -> BodyMesh �� ����� ����ƽ�޽÷� TempMesh �� ���� �־��ְ� �ʹ�.
		BodyMesh->SetStaticMesh(TempMesh.Object);
	}

	// ��Ƽ���� �ε��ϱ�
	ConstructorHelpers::FObjectFinder<UMaterial> TempMat(TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	// �ε��� �����ϸ�
	if (TempMat.Succeeded())
	{
		// -> BodyMesh �� ����� ����ƽ�޽÷� TempMesh �� ���� �־��ְ� �ʹ�.
		BodyMesh->SetMaterial(0, TempMat.Object);
	}
}

// Called when the game starts or when spawned
void ACBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector dir(0, 0, 1);
	// 3. �̵��ϰ� �ʹ�.
	// P = P0 + vt
	FVector P0 = GetActorLocation();
	FVector vt = dir * speed * DeltaTime;
	FVector P = P0 + vt;
	SetActorLocation(P);
}

