// Project has been managed by Ali Durgun


#include "Actor/AuraEffectMana.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Components/SphereComponent.h"
#include "GameplayAbilitySystem/AuraAttributeSet.h"

// Sets default values
AAuraEffectMana::AAuraEffectMana()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void AAuraEffectMana::SphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		UAbilitySystemComponent* ASC = ASCInterface->GetAbilitySystemComponent();
		const UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(ASC->GetAttributeSet(UAuraAttributeSet::StaticClass()));
		UAuraAttributeSet* MutableAS = const_cast<UAuraAttributeSet*>(AS);
		MutableAS->SetMana(AS->GetMana() + 15.0f);
		Destroy();
	}	
}

void AAuraEffectMana::SphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

// Called when the game starts or when spawned
void AAuraEffectMana::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectMana::SphereBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectMana::SphereEndOverlap);
}
