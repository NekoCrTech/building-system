// Developed by Neko Creative Technologies

#pragma once

#include "CoreMinimal.h"
#include "Resources.generated.h"

UENUM(BlueprintType)
enum EResource : int32
{
	None UMETA(DisplayName = "None"),
	Wood UMETA(DisplayName = "Wood"),
	Stone UMETA(DisplayName = "Stone"),
	Metal UMETA(DisplayName = "Metal"),
};

USTRUCT(BlueprintType)
struct FResourceCount : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ResourceCount=0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EResource Resource=EResource::None;

	// Default constructor
	FResourceCount()
		: ResourceCount(0), Resource(EResource::None)
	{}
};

USTRUCT(BlueprintType)
struct FCost : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FResourceCount> Cost;
};
