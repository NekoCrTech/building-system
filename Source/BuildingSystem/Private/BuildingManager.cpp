// Developed by Neko Creative Technologies


#include "BuildingManager.h"
#include "Engine/DataTable.h"


// Sets default values
ABuildingManager::ABuildingManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABuildingManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuildingManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FBuildingPartData ABuildingManager::GetBuildingPartData(const FName RowName)
{
	FBuildingPartData EmptyData; // fallback if not found

	if (BuildingPartData == nullptr)
	{
		return EmptyData;
	}

	if (FBuildingPartData* FoundRow = BuildingPartData->FindRow<FBuildingPartData>(RowName, TEXT("GetBuildingPartFromTable")))
	{
		return *FoundRow;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Row '%s' not found in DataTable."), *RowName.ToString());
		return EmptyData;
	}
}


void ABuildingManager::SetPreview(const FName RowName)
{
	if (GetIsPreviewing())
	{
		DestroyPreview();
	}
	SpawnPreviewMesh(RowName);
	SetIsPreviewing(true);
}

void ABuildingManager::SpawnPreviewMesh(FName RowName)
{
	PreviewTransform = FTransform::Identity;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	
	GetWorld()->SpawnActor<ABuildingPart>(ABuildingPart::StaticClass(),PreviewTransform,SpawnParams);
}

void ABuildingManager::DestroyPreview()
{
}

