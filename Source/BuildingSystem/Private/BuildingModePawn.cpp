// Developed by Neko Creative Technologies

#include "Public/BuildingModePawn.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABuildingModePawn::ABuildingModePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent=CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComponent;

	// Create the camera boom component
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));

	CameraBoom->SetupAttachment(SphereComponent);
	CameraBoom->SetUsingAbsoluteRotation(false);
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;

	// Create the camera component
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));

	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;

	PanSensitivity = DefaultPanSensitivity;
	ZoomStep = DefaultZoomStep;
	MoveSpeedModifier = DefaultMoveSpeedModifier;

}

// Called when the game starts or when spawned
void ABuildingModePawn::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void ABuildingModePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ZoomEvent();
}

// Called to bind functionality to input
void ABuildingModePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		//Camera Movement
		EnhancedInputComponent->BindAction(MoveCamera, ETriggerEvent::Triggered, this, &ABuildingModePawn::OnMoveCamera);
		//Camera Zoom
		EnhancedInputComponent->BindAction(ZoomCamera,ETriggerEvent::Triggered, this, &ABuildingModePawn::OnZoomCamera);
		//Camera Rotation
		EnhancedInputComponent->BindAction(MouseMovement,ETriggerEvent::Triggered,this,&ABuildingModePawn::OnMouseMove);
		EnhancedInputComponent->BindAction(RotateCamera,ETriggerEvent::Started, this, &ABuildingModePawn::OnRotateCameraStarted);
		EnhancedInputComponent->BindAction(RotateCamera,ETriggerEvent::Completed, this, &ABuildingModePawn::OnRotateCameraFinished);
		
		//Secondary Keys
		EnhancedInputComponent->BindAction(SpeedUpEnabled,ETriggerEvent::Started, this, &ABuildingModePawn::OnSpeedUpStarted);
		EnhancedInputComponent->BindAction(SpeedUpEnabled,ETriggerEvent::Completed, this, &ABuildingModePawn::OnSpeedUpFinished);

		EnhancedInputComponent->BindAction(ResetCamera,ETriggerEvent::Triggered, this, &ABuildingModePawn::OnCameraReset);
	}
}

void ABuildingModePawn::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(BuildingMappingContext, 0);
		}
	}
}


//-------------------
/** Input handlers */
//-------------------


void ABuildingModePawn::OnMoveCamera(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementInput = Value.Get<FVector2D>();
	BasicCameraMovement(MovementInput);
}

void ABuildingModePawn::OnZoomCamera(const FInputActionValue& Value)
{
	float ZoomInput = Value.Get<float>();

	if (ZoomInput > 0.f)
	{
		ZoomIn();
	}
	else if (ZoomInput < 0.f)
	{
		ZoomOut();
	}
}

void ABuildingModePawn::OnCameraReset(const FInputActionValue& Value)
{
	// Reset Camera
	DeltaZoomAmount = 0.5f;
	// Reset Pan
	SetActorRotation(FRotator(0, 0, 0));
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
}

void ABuildingModePawn::OnMouseMove(const FInputActionValue& Value)
{
	FVector2D MouseInput = Value.Get<FVector2D>();
	if (bRotateEnabled==true)
	{
		FRotator CombinedRotation = UKismetMathLibrary::ComposeRotators(GetActorRotation(), FRotator(0,MouseInput.X*PanSensitivity,0));
		SetActorRotation(CombinedRotation);

		float BoomPitch = FMath::Clamp(GetCameraBoom()->GetRelativeRotation().Pitch + MouseInput.Y * PanSensitivity,-90,0);
		CameraBoom->SetRelativeRotation(FRotator(BoomPitch, 0.f, 0.f));
	}
}

void ABuildingModePawn::OnRotateCameraStarted()
{
	bRotateEnabled = true;
}

void ABuildingModePawn::OnRotateCameraFinished()
{
	bRotateEnabled = false;
}

void ABuildingModePawn::OnSpeedUpStarted()
{
	ZoomStep = 0.1 ;
	MoveSpeedModifier = 3 ;
}

void ABuildingModePawn::OnSpeedUpFinished()
{
	PanSensitivity = DefaultPanSensitivity;
	ZoomStep = DefaultZoomStep;
	MoveSpeedModifier = DefaultMoveSpeedModifier;
}


//--------------------
// Camera Effectors
//--------------------



void ABuildingModePawn::BasicCameraMovement(const FVector2D AxisValue)
{
	if (!bDisableCameraMovement)
	{
		if(AxisValue.X!=0 && AxisValue.Y!=0)
		{
			// Move in both Axis
			AddActorLocalOffset(FVector(GetMultipliedAxisValue(AxisValue.X), GetMultipliedAxisValue(AxisValue.Y), 0));
		}
		else if(AxisValue.X!=00)
		{
			//Move only in X Axis
			AddActorLocalOffset(FVector(GetMultipliedAxisValue(AxisValue.X), 0, 0));
		}
		else if(AxisValue.Y!=00)
		{
			//Move only in Y Axis
			AddActorLocalOffset(FVector(0,GetMultipliedAxisValue(AxisValue.Y), 0));
		}
	}
}

void ABuildingModePawn::ZoomEvent()
{
	ZoomAmount = FMath::Lerp(ZoomAmount, DeltaZoomAmount,0.1f);
	CameraBoom->TargetArmLength = GetZoomFromCurve(ZoomAmount);
}


//--------------------
// UTILITIES FUNCTIONS
//--------------------

float ABuildingModePawn::GetMultipliedAxisValue(float AxisValue)
{
	return AxisValue*MoveSpeed*MoveSpeedModifier;
}

void ABuildingModePawn::ZoomIn()
{
	DeltaZoomAmount += ZoomStep;
	if (DeltaZoomAmount > 1.0f)
	{
		DeltaZoomAmount = 1.0f;
	}
}

void ABuildingModePawn::ZoomOut()
{
	DeltaZoomAmount -= ZoomStep;
	if (DeltaZoomAmount < 0.f)
	{
		DeltaZoomAmount = 0.f;
	}
}

float ABuildingModePawn::GetZoomFromCurve(float ZoomAlpha)
{
	if (!ZoomCurve) return ZoomLimits.X;

	ZoomAlpha = FMath::Clamp(ZoomAlpha, 0, 1);

	float CurveValue = ZoomCurve->GetFloatValue(ZoomAlpha);

	return FMath::Lerp(ZoomLimits.X, ZoomLimits.Y, CurveValue);
}

