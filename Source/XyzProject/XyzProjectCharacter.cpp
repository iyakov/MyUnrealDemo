// Copyright Epic Games, Inc. All Rights Reserved.

#include "XyzProjectCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "WheeledVehiclePawn.h"
#include "XyzProjectGameInstance.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AXyzProjectCharacter

AXyzProjectCharacter::AXyzProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AXyzProjectCharacter::SetActiveCar(AWheeledVehiclePawn* ActiveCar_In)
{
	CurrentAvailableCar = ActiveCar_In;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AXyzProjectCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AXyzProjectCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Sitting in a car
		EnhancedInputComponent->BindAction(SitInACarAction, ETriggerEvent::Triggered, this, &AXyzProjectCharacter::SitInACar);
		
		// Throwing cubes
		EnhancedInputComponent->BindAction(ThrowCubeAction, ETriggerEvent::Triggered, this, &AXyzProjectCharacter::ThrowCube);
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AXyzProjectCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AXyzProjectCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AXyzProjectCharacter::BeginPlay()
{
	Super::BeginPlay();

	UXyzProjectGameInstance* GameInstance = Cast<UXyzProjectGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (IsValid(GameInstance))
	{
		const int MainMaterialIndex = 0;
		const int SecondaryMaterialIndex = 1;
		FLinearColor PlayerColor(GameInstance->GetPlayerColor());
		
		UMaterialInstanceDynamic* MainMaterialInstance = GetMesh()->CreateDynamicMaterialInstance(MainMaterialIndex);
		if (IsValid(MainMaterialInstance))
		{
			MainMaterialInstance->SetVectorParameterValue(FName("Tint"), PlayerColor);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create material instance"));
		}

		UMaterialInstanceDynamic* SecondaryMaterialInstance = GetMesh()->CreateDynamicMaterialInstance(SecondaryMaterialIndex);
		if (IsValid(SecondaryMaterialInstance))
		{
			SecondaryMaterialInstance->SetVectorParameterValue(FName("Tint"), PlayerColor);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create material instance"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get game instance"));
	}
}

void AXyzProjectCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AXyzProjectCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AXyzProjectCharacter::SitInACar()
{
	AController* CurrentController = GetController();

	if (IsValid(CurrentController))
	{
		CurrentController->Possess(CurrentAvailableCar);
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Attaching a third person pawn to the vehicle"));
	AttachToActor(CurrentAvailableCar, FAttachmentTransformRules::KeepRelativeTransform);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetVisibility(false);
	SetActorRelativeLocation(FVector(0.0f, 0.0f, 500.0f));
}

void AXyzProjectCharacter::ThrowCube()
{
	if (!IsValid(ThrowItemType))
	{
		UE_LOG(LogTemp, Error, TEXT("ThrowingItemType is not valid"));
		return;
	}

	FRotator SpawningRotation = GetActorRotation();
	FVector SpawningLocation = GetActorLocation() + SpawningRotation.RotateVector(ThrowOffset);

	AActor* SpawnedActor = GetWorld()->SpawnActor(ThrowItemType, &SpawningLocation, &SpawningRotation);
	UPrimitiveComponent* SpawnedRootPrimitive = Cast<UPrimitiveComponent>(SpawnedActor->GetRootComponent());

	if (IsValid(SpawnedRootPrimitive))
	{
		const bool IgnoreMassFlag = true;
		SpawnedRootPrimitive->AddImpulse(RootComponent->GetForwardVector() * ThrowStartSpeed, NAME_None, IgnoreMassFlag);
	}
}
