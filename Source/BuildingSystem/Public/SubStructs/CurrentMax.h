// Developed by Neko Creative Technologies

#pragma once

#include "CoreMinimal.h"
#include "CurrentMax.generated.h"

USTRUCT(BlueprintType)
struct FCurrentMaxFloat : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Current = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Max = 0;	
};

USTRUCT(BlueprintType)
struct FCurrentMaxInt : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Current = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Max = 0;
};
