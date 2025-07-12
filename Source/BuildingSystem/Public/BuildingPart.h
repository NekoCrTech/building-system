// Developed by Neko Creative Technologies

#pragma once

#include "CoreMinimal.h"
#include "Resources.h"
#include "GameFramework/Actor.h"
#include "BuildingPart.generated.h"


USTRUCT(BlueprintType)
struct FBuildingPartData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Name = FText();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCost Cost = FCost();
	
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