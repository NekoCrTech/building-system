// Developed by Neko Creative Technologies


#include "BuildingPart.h"

#include "Components/BoxComponent.h"

// Sets default values
ABuildingPart::ABuildingPart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	BuildingMesh->SetupAttachment(RootComponent);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(BuildingMesh);
}

// Called when the game starts or when spawned
void ABuildingPart::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABuildingPart::SetHologramMat(const EHologramState HologramState)
{
	if (HologramState == EHologramState::Green)
	{
		BuildingMesh->SetMaterial(0,HologramGreen);
		return;
	}
	else if (HologramState == EHologramState::Red)
	{
		BuildingMesh->SetMaterial(0,HologramRed);
		return;
	}
	BuildingMesh->SetMaterial(0,HologramBlue);
}

bool ABuildingPart::SetBuildingPartData(const FBuildingPartData InBuildingPartData)
{
	if (InBuildingPartData.BaseMesh != nullptr)
	{
		BuildingPartData = InBuildingPartData;
		return true;
	}
	K2_DestroyActor();
	return false;
}

void ABuildingPart::InitializeBuildingPart()
{
	if (BuildingPartData.BaseMesh == nullptr)
	{
		Destroy();
		return;
	}
	if (ConstructionStatus == EConstructionStatus::Preview)
	{
		RunSetPreviewMesh();
	}

	if (ConstructionStatus == EConstructionStatus::Preview)
	{
		RunSetPreviewMesh();
	}
}

void ABuildingPart::SetBuildingMesh()
{
	if (BuildingPartData.BaseMesh != nullptr)
	{
		UStaticMesh* Mesh= BuildingPartData.BaseMesh;
		if (ConstructionStatus == EConstructionStatus::Preview)
		{
			
		}
		else if (ConstructionStatus == EConstructionStatus::UnderConstruction)
		{
			Mesh = BuildingPartData.ConstructionMesh;
		}
		else if (ConstructionStatus == EConstructionStatus::Built)
		{
			
		}
		else
		{
			Mesh = BuildingPartData.DamagedMesh;
		}
		BuildingMesh->SetStaticMesh(Mesh);
		SetCollisionArea();
	}
}

void ABuildingPart::SetCollisionArea()
{
	// Set collision box size from mesh bounds 
	FVector Min;
	FVector Max;
	BuildingMesh->GetLocalBounds(Min, Max);
	CollisionBox->SetBoxExtent(FVector(FMath::Abs(Min.X), FMath::Abs(Min.Y), Max.Z/2));
	// Set Collision Box local offset
	CollisionBox->SetRelativeLocation(FVector(0,0,Max.Z/2));
}

void ABuildingPart::RunSetPreviewMesh()
{
}


