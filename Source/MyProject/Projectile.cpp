// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/DecalActor.h"
#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("StaticMesh'/Game/Geometry/Meshes/Sphere'"));

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NomMesh"));
	MovementSphere = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("NomMovement"));

	if(StaticMesh.Succeeded())
	{
		SphereMesh->SetStaticMesh(StaticMesh.Object);
	}

	SphereMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	RootComponent = SphereMesh;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ADecalActor* Bullet = GetWorld()->SpawnActor<ADecalActor>(Hit.Location, FRotator(0, 0, 0));
	Destroy();
}
