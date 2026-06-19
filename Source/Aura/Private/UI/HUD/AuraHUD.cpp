// Copyright Masters


#include "UI/HUD/AuraHUD.h"
#include "UI/Widgets/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/Widgets/AuraUserWidget.h"
#include "Blueprint/UserWidget.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (!OverlayWidgetController) {
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PlayerSt, UAbilitySystemComponent* AbilitySystemComp, UAttributeSet* AttributeSt)
{
	checkf(OverlayWidgetClass, TEXT("Overlay class uninitialised, please fill BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay widget controller class uninitialised, please fill BP_AuraHUD"));

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);
	const FWidgetControllerParams WidgetControllerParams(PC, PlayerSt, AbilitySystemComp, AttributeSt);
	UOverlayWidgetController* WidgetCont = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetCont);
	WidgetCont->BroadcastInitialValues();
	Widget->AddToViewport();
}

