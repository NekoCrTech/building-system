// Developed by Neko Creative Technologies

#pragma once

#include "CoreMinimal.h"
#include "Resources.h"
#include "GameFramework/Actor.h"
#include "SubStructs/CurrentMax.h"
#include "BuildingPart.generated.h"

UENUM(BlueprintType)
enum class EBuildingPartType : uint8
{
	None UMETA(DisplayName = "None"),
	Floor UMETA(DisplayName = "Floor"),
	Wall UMETA(DisplayName = "Wall"),
};

USTRUCT(BlueprintType)
struct FBuildingPartData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText Name = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EBuildingPartType Type = EBuildingPartType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCurrentMaxInt Stability = FCurrentMaxInt();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FCost Cost = FCost();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UStaticMesh> ConstructionMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UStaticMesh> BaseMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UStaticMesh> DamagedMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText Description = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float ConstructionTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCurrentMaxInt WorkingOccupants = FCurrentMaxInt();
};

UCLASS()
class BUILDINGSYSTEM_API ABuildingPart : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildingPart();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FBuildingPartData GetBuildingPartData(){return BuildingPartData;}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FBuildingPartData BuildingPartData = FBuildingPartData();
};