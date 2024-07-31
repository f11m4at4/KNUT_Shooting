// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayer.h"
#include <CBullet.h>

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

	// 총구 컴포넌트 등록하기
	FirePosition = CreateDefaultSubobject<USceneComponent>(TEXT("FirePosition"));
	FirePosition->SetupAttachment(BodyMesh);
	FirePosition->SetRelativeLocation(FVector(0, 0, 80));
}
 
// Called when the game starts or when spawned
void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 사용자가 상하좌우키를 누르면 그 방향으로 이동하고 싶다.
	// 1. 사용자 입력에 따라
	// 2. 방향이 필요하다.
	// -> 오른쪽 방향
	FVector dir(0, h, v);
	// 3. 이동하고 싶다.
	// P = P0 + vt
	FVector P0 = GetActorLocation();
	FVector vt = dir * speed * DeltaTime;
	FVector P = P0 + vt;
	SetActorLocation(P);
}

// Called to bind functionality to input
void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// 좌우입력 Horizontal 입력이 들어오면 처리할 함수로 Horizontal 함수를 등록해주자
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &ACPlayer::Horizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &ACPlayer::Vertical);
	// 총알발사 버튼 입력과 처리함수를 엮어주자.
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ACPlayer::Fire);
}

void ACPlayer::Horizontal(float value)
{
	h = value;
}

void ACPlayer::Vertical(float value)
{
	v = value;
}

// 사용자가 발사 버튼을 눌렀을 때
void ACPlayer::Fire()
{
	// 총알을 발사하고 싶다.
	// 1. 총알이 있어야한다.
	// 2. 총알을 발사하고 싶다.
	// -> 총알을 만들고 총구위치에 배치한다.
	GetWorld()->SpawnActor<ACBullet>(bulletFactory, 
				FirePosition->GetComponentLocation(), FRotator());
}

