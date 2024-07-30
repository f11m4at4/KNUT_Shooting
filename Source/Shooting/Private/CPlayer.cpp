// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayer.h"

// Sets default values
ACPlayer::ACPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// BodyMesh 그릇에 StaticMeshComponent 를 만들어서 담고 싶다.
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	// BodyMesh 를 Root 로 등록하고 싶다.
	RootComponent = BodyMesh;

	SpaceShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpaceShipMesh"));
	SpaceShipMesh->SetupAttachment(BodyMesh);

	// 사용할 Static Mesh 데이터를 읽어들여서 컴포넌트에 할당하고싶다.
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("/Script/Engine.StaticMesh'/Game/SpaceShip/Spaceship_ARA.Spaceship_ARA'"));
	// 로딩이 성공하면
	if(TempMesh.Succeeded())
	{
		// -> SpaceShipMesh 에 사용할 스태틱메시로 TempMesh 의 값을 넣어주고 싶다.
		SpaceShipMesh->SetStaticMesh(TempMesh.Object);
		// 위치값을 세팅하고 싶다.
		SpaceShipMesh->SetRelativeRotation(FRotator(0, 90, 90));
		// 크기값을 세팅하고 싶다.
		SpaceShipMesh->SetRelativeScale3D(FVector(6));
	}
}
 
// Called when the game starts or when spawned
void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	int32 number1 = 200;
	int32 number2 = 5;
	UE_LOG(LogTemp, Warning, TEXT("%d"), number1 + number2);
}

// Called every frame
void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

