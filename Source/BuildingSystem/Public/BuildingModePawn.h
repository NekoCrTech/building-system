// Developed by Neko Creative Technologies

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BuildingModePawn.generated.h"

class USphereComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

UCLASS()
class BUILDINGSYSTEM_API ABuildingModePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABuildingModePawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void NotifyControllerChanged() override;
	
	/** Returns the camera component **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }

	/** Returns the Camera Boom component **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UFUNCTION(BlueprintCallable)
	void SetDisableCameraMovement(const bool bDisableMovement){bDisableCameraMovement=bDisableMovement;}
	FORCEINLINE bool IsDisableCameraMovement() const { return bDisableCameraMovement; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* BuildingMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ZoomCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ResetZoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* RotateCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SecondaryKeysEnabled;

	/** Input handlers */
	void OnMoveCamera(const FInputActionValue& Value);
	void OnZoomCamera(const FInputActionValue& Value);
	void OnZoomReset(const FInputActionValue& Value);
	void OnRotateCamera(const FInputActionValue& Value);
	void OnSecondaryKeysEnabled(const FInputActionValue& Value);


private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr <USphereComponent> SphereComponent;
	
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr <UCameraComponent> TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr <USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere)
	bool bDisableCameraMovement = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement Settings", meta = (AllowPrivateAccess = "true"))
	float MoveSpeed = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement Settings", meta = (AllowPrivateAccess = "true"))
	float MoveSpeedModifier = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement Settings", meta = (AllowPrivateAccess = "true"))
	UCurveFloat* ZoomCurve = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement Settings", meta = (AllowPrivateAccess = "true"))
	FVector2D ZoomLimits = FVector2D{300,1300};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement Settings", meta = (AllowPrivateAccess = "true"))
	float ZoomStep = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement Settings", meta = (AllowPrivateAccess = "true"))
	float RotateStep = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement Settings", meta = (AllowPrivateAccess = "true"))
	FVector2D ZoomRange = FVector2D(300.0f, 3000.0f);
	
	FVector MovementVector = FVector::ZeroVector;
	float DeltaZoomAmount = 0.5f;
	float ZoomAmount = 0.5f;

	void BasicCameraMovement(FVector2D AxisValue);
	
	void ZoomEvent();

	float GetMultipliedAxisValue(float AxisValue);
	void ZoomIn();
	void ZoomOut();
	float GetZoomFromCurve(float ZoomAlpha);

};
