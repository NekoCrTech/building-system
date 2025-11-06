// Developed by Neko Creative Technologies

#pragma once

#include "CoreMinimal.h"
#include "Resources.h"
#include "GameFramework/Actor.h"
#include "SubStructs/CurrentMax.h"
#include "BuildingPart.generated.h"

class UBoxComponent;

UENUM(BlueprintType)
enum class EBuildingPartType : uint8
{
	None UMETA(DisplayName = "None"),
	Floor UMETA(DisplayName = "Floor"),
	Wall UMETA(DisplayName = "Wall"),
};

UENUM(BlueprintType)
enum EHologramState : uint8
{
	None UMETA(DisplayName = "None"),
	Blue UMETA(DisplayName = "Blue"),
	Green UMETA(DisplayName = "Green"),
	Red UMETA(DisplayName = "Red"),
};

UENUM(BlueprintType)
enum class EConstructionStatus : uint8
{
	Preview UMETA(DisplayName = "Preview"),
	UnderConstruction UMETA(DisplayName = "UnderConstruction"),
	Built UMETA(DisplayName = "Built"),
	Damaged UMETA(DisplayName = "Damaged")	
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Preview Materials")
	TObjectPtr<UMaterialInstance> HologramGreen = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Preview Materials")
	TObjectPtr<UMaterialInstance> HologramRed = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Preview Materials")
	TObjectPtr<UMaterialInstance> HologramBlue = nullptr;

	UFUNCTION(BlueprintCallable)
	void SetHologramMat(EHologramState HologramState = EHologramState::Blue);
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE EConstructionStatus GetConstructionStatus() const { return ConstructionStatus; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FBuildingPartData GetBuildingPartData(){return BuildingPartData;}

	UFUNCTION(BlueprintCallable)
	bool SetBuildingPartData(FBuildingPartData InBuildingPartData);

	UFUNCTION(BlueprintCallable)
	void InitializeBuildingPart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> BuildingMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> CollisionBox;

	UPROPERTY()
	EConstructionStatus ConstructionStatus = EConstructionStatus::Preview;
	
	FBuildingPartData BuildingPartData = FBuildingPartData();

	
	void SetBuildingMesh();
	void SetCollisionArea();
	void RunSetPreviewMesh();
	void RunSetConstructionStatus(const EConstructionStatus InConstructionStatus){ ConstructionStatus = InConstructionStatus; }
};