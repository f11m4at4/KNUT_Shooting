// Fill out your copyright notice in the Description page of Project Settings.


#include "CBullet.h"

// Sets default values
ACBullet::ACBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// BodyMesh 그릇에 StaticMeshComponent 를 만들어서 담고 싶다.
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	// BodyMesh 를 Root 로 등록하고 싶다.
	RootComponent = BodyMesh;
	// 크기값 설정
	BodyMesh->SetRelativeScale3D(FVector(1, 0.25f, 0.75f));

	// 사용할 Static Mesh 데이터를 읽어들여서 컴포넌트에 할당하고싶다.
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	// 로딩이 성공하면
	if (TempMesh.Succeeded())
	{
		// -> BodyMesh 에 사용할 스태틱메시로 TempMesh 의 값을 넣어주고 싶다.
		BodyMesh->SetStaticMesh(TempMesh.Object);
	}

	// 머티리얼 로드하기
	ConstructorHelpers::FObjectFinder<UMaterial> TempMat(TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	// 로딩이 성공하면
	if (TempMat.Succeeded())
	{
		// -> BodyMesh 에 사용할 스태틱메시로 TempMesh 의 값을 넣어주고 싶다.
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
	// 3. 이동하고 싶다.
	// P = P0 + vt
	FVector P0 = GetActorLocation();
	FVector vt = dir * speed * DeltaTime;
	FVector P = P0 + vt;
	SetActorLocation(P);
}

