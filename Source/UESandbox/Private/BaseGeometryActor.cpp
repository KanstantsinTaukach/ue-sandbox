//Unreal Engine Sandbox. Copyright Taukach K. All Rights Reserved.


#include "BaseGeometryActor.h"
#include "Engine/Engine.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All, All)

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();
	
	//PrintTypes();
	//PrintStringtypes();
	
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseGeometryActor::PrintTypes()
{
	UE_LOG(LogTemp, Display, TEXT("Hello Unreal!"));
	UE_LOG(LogTemp, Warning, TEXT("Hello Unreal!"));
	UE_LOG(LogTemp, Error, TEXT("Hello Unreal!"));

	int WeaponsNum = 4;
	int KillsNum = 7;
	float Health = 33.22113f;
	bool IsDead = false;
	bool HasWeapon = true;

	UE_LOG(LogTemp, Display, TEXT("Weapons num: %d, kills num: %i"), WeaponsNum, KillsNum);
	UE_LOG(LogTemp, Display, TEXT("Health: %f"), Health);
	UE_LOG(LogTemp, Display, TEXT("Health: %.2f"), Health);
	UE_LOG(LogTemp, Display, TEXT("IsDead: %d"), IsDead);
	UE_LOG(LogTemp, Display, TEXT("HasWeapon: %d"), static_cast<int>(HasWeapon));
}

void ABaseGeometryActor::PrintStringtypes()
{
	FString Name = "John Connor";
	UE_LOG(LogBaseGeometry, Display, TEXT("Name: %s"), *Name);

	int WeaponsNum = 4;
	float Health = 33.22113f;
	bool IsDead = false;

	FString WeaponsNumStr = "Weapons num = " + FString::FromInt(WeaponsNum);
	FString HealthStr = "Health = " + FString::SanitizeFloat(Health);
	FString IsDeadStr = "Is dead = " + FString(IsDead ? "true" : "false");

	FString Stat = FString::Printf(TEXT("\n ==== All Stat ==== \n %s \n %s \n %s"), *WeaponsNumStr, *HealthStr, *IsDeadStr);
	UE_LOG(LogBaseGeometry, Warning, TEXT("%s"), *Stat);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Name);
	GEngine->AddOnScreenDebugMessage(-1, 7.0f, FColor::Red, Stat, true, FVector2D(1.5f, 1.5f));
}

