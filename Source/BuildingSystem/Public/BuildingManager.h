// Developed by Neko Creative Technologies

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingPart.h"
#include "BuildingManager.generated.h"



UCLASS()
class BUILDINGSYSTEM_API ABuildingManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildingManager();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UDataTable> BuildingPartData = nullptr;

	UFUNCTION(BlueprintCallable)
	FBuildingPartData GetBuildingPartData(FName RowName);
	
	UFUNCTION(BlueprintCallable)
	void SetPreview(FName RowName);

	UFUNCTION(BlueprintCallable)
	void SpawnPreviewMesh(FName RowName);

	UFUNCTION(BlueprintCallable)
	void DestroyPreview();

	FORCEINLINE bool GetIsPreviewing() const { return bIsPreviewing; }
	FORCEINLINE void SetIsPreviewing(const bool bValue) { bIsPreviewing = bValue; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	FTransform PreviewTransform = FTransform::Identity;
	
	bool bIsPreviewing = false;
};
