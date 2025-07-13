// Developed by Neko Creative Technologies

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingManager.generated.h"

UENUM(BlueprintType)
enum EConstructionStatus : int32
{
	Preview UMETA(DisplayName = "Preview"),
	UnderConstruction UMETA(DisplayName = "UnderConstruction"),
	Built UMETA(DisplayName = "Built"),
	Damaged UMETA(DisplayName = "Damaged"),
};

UCLASS()
class BUILDINGSYSTEM_API ABuildingManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildingManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
