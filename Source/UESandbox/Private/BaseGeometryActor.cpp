//Unreal Engine Sandbox. Copyright Taukach K. All Rights Reserved.


#include "BaseGeometryActor.h"
#include "Engine/Engine.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All, All)

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	SetRootComponent(BaseMesh);

}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetActorLocation();
//	InitialLocation = GetTransform().GetLocation();
	
	//PrintTransform();
	//PrintTypes();
	//PrintStringtypes();

	SetColor(GeometryData.Color);
	
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseGeometryActor::OnTimerFired, GeometryData.TimerRate, true);

	PrintGeometryData();
}

void ABaseGeometryActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UE_LOG(LogBaseGeometry, Error, TEXT("%s actor is dead."), *GetName());
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleMovement();
	
}

void ABaseGeometryActor::PrintTypes()
{
	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor name: %s"), *GetName());
	UE_LOG(LogBaseGeometry, Display, TEXT("Weapons num: %d, kills num: %i"), WeaponsNum, KillsNum);
	UE_LOG(LogBaseGeometry, Display, TEXT("Health: %f"), Health);
	UE_LOG(LogBaseGeometry, Display, TEXT("Health: %.2f"), Health);
	UE_LOG(LogBaseGeometry, Display, TEXT("IsDead: %d"), IsDead);
	UE_LOG(LogBaseGeometry, Display, TEXT("HasWeapon: %d"), static_cast<int>(HasWeapon));
}

void ABaseGeometryActor::PrintStringtypes()
{
	FString Name = "John Connor";
	UE_LOG(LogBaseGeometry, Display, TEXT("Name: %s"), *Name);
		
	FString WeaponsNumStr = "Weapons num = " + FString::FromInt(WeaponsNum);
	FString HealthStr = "Health = " + FString::SanitizeFloat(Health);
	FString IsDeadStr = "Is dead = " + FString(IsDead ? "true" : "false");

	FString Stat = FString::Printf(TEXT("\n ==== All Stat ==== \n %s \n %s \n %s"), *WeaponsNumStr, *HealthStr, *IsDeadStr);
	UE_LOG(LogBaseGeometry, Warning, TEXT("%s"), *Stat);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Name);
		GEngine->AddOnScreenDebugMessage(-1, 7.0f, FColor::Red, Stat, true, FVector2D(1.5f, 1.5f));
	}
}

void ABaseGeometryActor::PrintTransform()
{
	FTransform Transform = GetActorTransform();
	FVector Location = Transform.GetLocation();
	FRotator Rotation = Transform.Rotator();
	FVector Scale = Transform.GetScale3D();

	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor name: %s"), *GetName());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Transform: %s"), *Transform.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Location: %s"), *Location.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Rotator: %s"), *Rotation.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Scale: %s"), *Scale.ToString());


	UE_LOG(LogBaseGeometry, Error, TEXT("Human transform: %s"), *Transform.ToHumanReadableString());
}

void ABaseGeometryActor::PrintGeometryData()
{

	FString AmplitudeStr = "Amplitude = " + FString::SanitizeFloat(GeometryData.Amplitude);
	FString FrequencyStr = "Frequency = " + FString::SanitizeFloat(GeometryData.Frequency);

	FString MoveTypeStr = "";
	if (GeometryData.MoveType == EMovementType::Static)
	{
		MoveTypeStr = "EMovementType - Static";
	}
	else if (GeometryData.MoveType == EMovementType::Sin)
	{
		MoveTypeStr = "EMovementType - Sin";
	}

	FString ColorStr = "Color " + GeometryData.Color.ToString();
	FString TimerRateStr = "TimerRate is: " + FString::SanitizeFloat(GeometryData.TimerRate);

	FString GeometryDataStr = 
		FString::Printf(TEXT("\n ===== GeometryData ===== \n %s \n %s \n %s \n %s \n %s"), 
		*AmplitudeStr, 
		*FrequencyStr, 
		*MoveTypeStr, 
		*ColorStr, 
		*TimerRateStr);

	UE_LOG(LogBaseGeometry, Error, TEXT("Actor name: %s"), *GetName());
	UE_LOG(LogBaseGeometry, Error, TEXT("%s"), *GeometryDataStr);

}

void ABaseGeometryActor::HandleMovement()
{
	switch (GeometryData.MoveType)
	{
	case EMovementType::Sin:
	{
		FVector CurrentLocation = GetActorLocation();
		
		if (GetWorld())
		{
			float Time = GetWorld()->GetTimeSeconds();
			CurrentLocation.Z = InitialLocation.Z + GeometryData.Amplitude * FMath::Sin(GeometryData.Frequency * Time);

			SetActorLocation(CurrentLocation);
		}
	}
	break;

	case EMovementType::Static:	break;
	default: break;
	}
}

void ABaseGeometryActor::SetColor(const FLinearColor& Color)
{
	if (!BaseMesh)
	{
		return;
	}

	UMaterialInstanceDynamic* DynMaterial = BaseMesh->CreateAndSetMaterialInstanceDynamic(0);
	if (DynMaterial)
	{
		DynMaterial->SetVectorParameterValue("Color", Color);
	}
}

void ABaseGeometryActor::OnTimerFired()
{
	if (++TimerCount <= MaxTimerCount)
	{
		const FLinearColor NewColor = FLinearColor::MakeRandomColor();
		UE_LOG(LogBaseGeometry, Warning, TEXT("Timer count: %i, Color to set up: %s"), TimerCount, *NewColor.ToString());
		SetColor(NewColor);
		OnColorChanged.Broadcast(NewColor, GetName());
	}
	else
	{
		UE_LOG(LogBaseGeometry, Error, TEXT("Timer has been stopped!"));
		GetWorldTimerManager().ClearTimer(TimerHandle);
		OnTimerFinished.Broadcast(this);
	}
}

