#pragma once

#include "UObject.h"

class UTexture;
class UMesh;
class UModel;
class USound;
class UPawn;
class UInventory;
class ULevelInfo;
class UAnimation;
class UPlayer;
class UMusic;
class UGameReplicationInfo;
class UPlayerReplicationInfo;
class UMutator;
class UMenu;
class UPlayerPawn;
class UStatLog;
class USkyZoneInfo;
class ULevelSummary;
class ULevel;
class UInventorySpot;
class UMover;
class UTrigger;
class UWarpZoneInfo;
class UZoneInfo;
class PackageManager;
class SweepHit;

enum class ActorDrawType
{
	NoDraw,
	Sprite,
	Mesh,
	Brush,
	RopeSprite,
	VerticalSprite,
	Terraform,
	SpriteAnimOnce
};

struct PointRegion
{
	UZoneInfo* Zone;
	int BspLeaf;
	uint8_t ZoneNumber;
};

enum EPhysics
{
	PHYS_None,
	PHYS_Walking,
	PHYS_Falling,
	PHYS_Swimming,
	PHYS_Flying,
	PHYS_Rotating,
	PHYS_Projectile,
	PHYS_Rolling,
	PHYS_Interpolating,
	PHYS_MovingBrush,
	PHYS_Spider,
	PHYS_Trailer
};

enum ENetRole
{
	ROLE_None,
	ROLE_DumbProxy,
	ROLE_SimulatedProxy,
	ROLE_AutonomousProxy,
	ROLE_Authority,
};

enum ESoundSlot
{
	SLOT_None,
	SLOT_Misc,
	SLOT_Pain,
	SLOT_Interact,
	SLOT_Ambient,
	SLOT_Talk,
	SLOT_Interface
};

enum EMusicTransition
{
	MTRAN_None,
	MTRAN_Instant,
	MTRAN_Segue,
	MTRAN_Fade,
	MTRAN_FastFade,
	MTRAN_SlowFade
};

class UActor : public UObject
{
public:
	using UObject::UObject;

	UActor* Spawn(UClass* SpawnClass, UActor* SpawnOwner, std::string SpawnTag, vec3* SpawnLocation, Rotator* SpawnRotation);
	bool Destroy();

	void SetBase(UActor* newBase, bool sendBaseChangeEvent);
	void SetOwner(UActor* newOwner);
	virtual void InitActorZone();
	virtual void UpdateActorZone();
	PointRegion FindRegion(const vec3& offset = vec3(0.0f));

	virtual void Tick(float elapsed, bool tickedFlag);

	void TickAnimation(float elapsed);

	void TickPhysics(float elapsed);
	void TickWalking(float elapsed);
	void TickFalling(float elapsed);
	void TickSwimming(float elapsed);
	void TickFlying(float elapsed);
	void TickRotating(float elapsed);
	void TickProjectile(float elapsed);
	void TickRolling(float elapsed);
	void TickInterpolating(float elapsed);
	void TickMovingBrush(float elapsed);
	void TickSpider(float elapsed);
	void TickTrailer(float elapsed);

	void SetPhysics(uint8_t newPhysics);
	void SetCollision(bool newColActors, bool newBlockActors, bool newBlockPlayers);

	bool SetLocation(const vec3& newLocation);
	bool SetRotation(const Rotator& newRotation);
	bool SetCollisionSize(float newRadius, float newHeight);

	UObject* Trace(vec3& hitLocation, vec3& hitNormal, const vec3& traceEnd, const vec3& traceStart, bool bTraceActors, const vec3& extent);
	bool FastTrace(const vec3& traceEnd, const vec3& traceStart);

	SweepHit TryMove(const vec3& delta);
	bool Move(const vec3& delta);
	bool MoveSmooth(const vec3& delta);

	bool HasAnim(const std::string& sequence);
	bool IsAnimating();
	std::string GetAnimGroup(const std::string& sequence);
	void PlayAnim(const std::string& sequence, float* rate, float* tweenTime);
	void LoopAnim(const std::string& sequence, float* rate, float* tweenTime, float* minRate);
	void TweenAnim(const std::string& sequence, float tweenTime);

	// Cached calculations needed by the renderer
	bool lightsCalculated = false;
	vec3 light = { 0.0f };
	vec3 fogcolor = { 0.0f };
	float brightness = -1.0f;
	float fog = -1.0f;
	float radius = -1.0f;
	float r2 = -1.0f;

	UTexture* GetMultiskin(int index)
	{
		if (index >= 0 && index < 8)
			return (&MultiSkins())[index];
		else
			return nullptr;
	}

	vec3& Acceleration() { return Value<vec3>(PropOffsets_Actor.Acceleration); }
	uint8_t& AmbientGlow() { return Value<uint8_t>(PropOffsets_Actor.AmbientGlow); }
	USound*& AmbientSound() { return Value<USound*>(PropOffsets_Actor.AmbientSound); }
	float& AnimFrame() { return Value<float>(PropOffsets_Actor.AnimFrame); }
	float& AnimLast() { return Value<float>(PropOffsets_Actor.AnimLast); }
	float& AnimMinRate() { return Value<float>(PropOffsets_Actor.AnimMinRate); }
	float& AnimRate() { return Value<float>(PropOffsets_Actor.AnimRate); }
	std::string& AnimSequence() { return Value<std::string>(PropOffsets_Actor.AnimSequence); }
	std::string& AttachTag() { return Value<std::string>(PropOffsets_Actor.AttachTag); }
	UActor*& ActorBase() { return Value<UActor*>(PropOffsets_Actor.Base); }
	UModel*& Brush() { return Value<UModel*>(PropOffsets_Actor.Brush); }
	float& Buoyancy() { return Value<float>(PropOffsets_Actor.Buoyancy); }
	vec3& ColLocation() { return Value<vec3>(PropOffsets_Actor.ColLocation); }
	float& CollisionHeight() { return Value<float>(PropOffsets_Actor.CollisionHeight); }
	float& CollisionRadius() { return Value<float>(PropOffsets_Actor.CollisionRadius); }
	int& CollisionTag() { return Value<int>(PropOffsets_Actor.CollisionTag); }
	UActor*& Deleted() { return Value<UActor*>(PropOffsets_Actor.Deleted); }
	Rotator& DesiredRotation() { return Value<Rotator>(PropOffsets_Actor.DesiredRotation); }
	uint8_t& DodgeDir() { return Value<uint8_t>(PropOffsets_Actor.DodgeDir); }
	float& DrawScale() { return Value<float>(PropOffsets_Actor.DrawScale); }
	uint8_t& DrawType() { return Value<uint8_t>(PropOffsets_Actor.DrawType); }
	std::string& Event() { return Value<std::string>(PropOffsets_Actor.Event); }
	int& ExtraTag() { return Value<int>(PropOffsets_Actor.ExtraTag); }
	uint8_t& Fatness() { return Value<uint8_t>(PropOffsets_Actor.Fatness); }
	std::string& Group() { return Value<std::string>(PropOffsets_Actor.Group); }
	UActor*& HitActor() { return Value<UActor*>(PropOffsets_Actor.HitActor); }
	std::string& InitialState() { return Value<std::string>(PropOffsets_Actor.InitialState); }
	UPawn*& Instigator() { return Value<UPawn*>(PropOffsets_Actor.Instigator); }
	UInventory*& Inventory() { return Value<UInventory*>(PropOffsets_Actor.Inventory); }
	float& LODBias() { return Value<float>(PropOffsets_Actor.LODBias); }
	UActor*& LatentActor() { return Value<UActor*>(PropOffsets_Actor.LatentActor); }
	uint8_t& LatentByte() { return Value<uint8_t>(PropOffsets_Actor.LatentByte); }
	float& LatentFloat() { return Value<float>(PropOffsets_Actor.LatentFloat); }
	int& LatentInt() { return Value<int>(PropOffsets_Actor.LatentInt); }
	ULevelInfo*& Level() { return Value<ULevelInfo*>(PropOffsets_Actor.Level); }
	float& LifeSpan() { return Value<float>(PropOffsets_Actor.LifeSpan); }
	uint8_t& LightBrightness() { return Value<uint8_t>(PropOffsets_Actor.LightBrightness); }
	uint8_t& LightCone() { return Value<uint8_t>(PropOffsets_Actor.LightCone); }
	uint8_t& LightEffect() { return Value<uint8_t>(PropOffsets_Actor.LightEffect); }
	uint8_t& LightHue() { return Value<uint8_t>(PropOffsets_Actor.LightHue); }
	uint8_t& LightPeriod() { return Value<uint8_t>(PropOffsets_Actor.LightPeriod); }
	uint8_t& LightPhase() { return Value<uint8_t>(PropOffsets_Actor.LightPhase); }
	uint8_t& LightRadius() { return Value<uint8_t>(PropOffsets_Actor.LightRadius); }
	uint8_t& LightSaturation() { return Value<uint8_t>(PropOffsets_Actor.LightSaturation); }
	uint8_t& LightType() { return Value<uint8_t>(PropOffsets_Actor.LightType); }
	int& LightingTag() { return Value<int>(PropOffsets_Actor.LightingTag); }
	vec3& Location() { return Value<vec3>(PropOffsets_Actor.Location); }
	float& Mass() { return Value<float>(PropOffsets_Actor.Mass); }
	UMesh*& Mesh() { return Value<UMesh*>(PropOffsets_Actor.Mesh); }
	uint8_t& MiscNumber() { return Value<uint8_t>(PropOffsets_Actor.MiscNumber); }
	UTexture*& MultiSkins() { return Value<UTexture*>(PropOffsets_Actor.MultiSkins); }
	float& NetPriority() { return Value<float>(PropOffsets_Actor.NetPriority); }
	int& NetTag() { return Value<int>(PropOffsets_Actor.NetTag); }
	float& NetUpdateFrequency() { return Value<float>(PropOffsets_Actor.NetUpdateFrequency); }
	float& OddsOfAppearing() { return Value<float>(PropOffsets_Actor.OddsOfAppearing); }
	float& OldAnimRate() { return Value<float>(PropOffsets_Actor.OldAnimRate); }
	vec3& OldLocation() { return Value<vec3>(PropOffsets_Actor.OldLocation); }
	int& OtherTag() { return Value<int>(PropOffsets_Actor.OtherTag); }
	UActor*& Owner() { return Value<UActor*>(PropOffsets_Actor.Owner); }
	UActor*& PendingTouch() { return Value<UActor*>(PropOffsets_Actor.PendingTouch); }
	float& PhysAlpha() { return Value<float>(PropOffsets_Actor.PhysAlpha); }
	float& PhysRate() { return Value<float>(PropOffsets_Actor.PhysRate); }
	uint8_t& Physics() { return Value<uint8_t>(PropOffsets_Actor.Physics); }
	vec3& PrePivot() { return Value<vec3>(PropOffsets_Actor.PrePivot); }
	PointRegion& Region() { return Value<PointRegion>(PropOffsets_Actor.Region); }
	uint8_t& RemoteRole() { return Value<uint8_t>(PropOffsets_Actor.RemoteRole); }
	// URenderIterator*& RenderInterface() { return Value<URenderIterator*>(PropOffsets_Actor.RenderInterface); }
	UClass*& RenderIteratorClass() { return Value<UClass*>(PropOffsets_Actor.RenderIteratorClass); }
	uint8_t& Role() { return Value<uint8_t>(PropOffsets_Actor.Role); }
	Rotator& Rotation() { return Value<Rotator>(PropOffsets_Actor.Rotation); }
	Rotator& RotationRate() { return Value<Rotator>(PropOffsets_Actor.RotationRate); }
	float& ScaleGlow() { return Value<float>(PropOffsets_Actor.ScaleGlow); }
	// Plane& SimAnim() { return Value<Plane>(PropOffsets_Actor.SimAnim); }
	UAnimation*& SkelAnim() { return Value<UAnimation*>(PropOffsets_Actor.SkelAnim); }
	UTexture*& Skin() { return Value<UTexture*>(PropOffsets_Actor.Skin); }
	uint8_t& SoundPitch() { return Value<uint8_t>(PropOffsets_Actor.SoundPitch); }
	uint8_t& SoundRadius() { return Value<uint8_t>(PropOffsets_Actor.SoundRadius); }
	uint8_t& SoundVolume() { return Value<uint8_t>(PropOffsets_Actor.SoundVolume); }
	int& SpecialTag() { return Value<int>(PropOffsets_Actor.SpecialTag); }
	UTexture*& Sprite() { return Value<UTexture*>(PropOffsets_Actor.Sprite); }
	float& SpriteProjForward() { return Value<float>(PropOffsets_Actor.SpriteProjForward); }
	uint8_t& StandingCount() { return Value<uint8_t>(PropOffsets_Actor.StandingCount); }
	uint8_t& Style() { return Value<uint8_t>(PropOffsets_Actor.Style); }
	std::string& Tag() { return Value<std::string>(PropOffsets_Actor.Tag); }
	UActor*& Target() { return Value<UActor*>(PropOffsets_Actor.Target); }
	UTexture*& Texture() { return Value<UTexture*>(PropOffsets_Actor.Texture); }
	float& TimerCounter() { return Value<float>(PropOffsets_Actor.TimerCounter); }
	float& TimerRate() { return Value<float>(PropOffsets_Actor.TimerRate); }
	UActor*& Touching() { return Value<UActor*>(PropOffsets_Actor.Touching); }
	float& TransientSoundRadius() { return Value<float>(PropOffsets_Actor.TransientSoundRadius); }
	float& TransientSoundVolume() { return Value<float>(PropOffsets_Actor.TransientSoundVolume); }
	float& TweenRate() { return Value<float>(PropOffsets_Actor.TweenRate); }
	vec3& Velocity() { return Value<vec3>(PropOffsets_Actor.Velocity); }
	float& VisibilityHeight() { return Value<float>(PropOffsets_Actor.VisibilityHeight); }
	float& VisibilityRadius() { return Value<float>(PropOffsets_Actor.VisibilityRadius); }
	uint8_t& VolumeBrightness() { return Value<uint8_t>(PropOffsets_Actor.VolumeBrightness); }
	uint8_t& VolumeFog() { return Value<uint8_t>(PropOffsets_Actor.VolumeFog); }
	uint8_t& VolumeRadius() { return Value<uint8_t>(PropOffsets_Actor.VolumeRadius); }
	ULevel*& XLevel() { return Value<ULevel*>(PropOffsets_Actor.XLevel); }
	bool& bActorShadows() { return Value<bool>(PropOffsets_Actor.bActorShadows); }
	bool& bAlwaysRelevant() { return Value<bool>(PropOffsets_Actor.bAlwaysRelevant); }
	bool& bAlwaysTick() { return Value<bool>(PropOffsets_Actor.bAlwaysTick); }
	bool& bAnimByOwner() { return Value<bool>(PropOffsets_Actor.bAnimByOwner); }
	bool& bAnimFinished() { return Value<bool>(PropOffsets_Actor.bAnimFinished); }
	bool& bAnimLoop() { return Value<bool>(PropOffsets_Actor.bAnimLoop); }
	bool& bAnimNotify() { return Value<bool>(PropOffsets_Actor.bAnimNotify); }
	bool& bAssimilated() { return Value<bool>(PropOffsets_Actor.bAssimilated); }
	bool& bBlockActors() { return Value<bool>(PropOffsets_Actor.bBlockActors); }
	bool& bBlockPlayers() { return Value<bool>(PropOffsets_Actor.bBlockPlayers); }
	bool& bBounce() { return Value<bool>(PropOffsets_Actor.bBounce); }
	bool& bCanTeleport() { return Value<bool>(PropOffsets_Actor.bCanTeleport); }
	bool& bCarriedItem() { return Value<bool>(PropOffsets_Actor.bCarriedItem); }
	bool& bClientAnim() { return Value<bool>(PropOffsets_Actor.bClientAnim); }
	bool& bClientDemoNetFunc() { return Value<bool>(PropOffsets_Actor.bClientDemoNetFunc); }
	bool& bClientDemoRecording() { return Value<bool>(PropOffsets_Actor.bClientDemoRecording); }
	bool& bCollideActors() { return Value<bool>(PropOffsets_Actor.bCollideActors); }
	bool& bCollideWhenPlacing() { return Value<bool>(PropOffsets_Actor.bCollideWhenPlacing); }
	bool& bCollideWorld() { return Value<bool>(PropOffsets_Actor.bCollideWorld); }
	bool& bCorona() { return Value<bool>(PropOffsets_Actor.bCorona); }
	bool& bDeleteMe() { return Value<bool>(PropOffsets_Actor.bDeleteMe); }
	bool& bDemoRecording() { return Value<bool>(PropOffsets_Actor.bDemoRecording); }
	bool& bDifficulty0() { return Value<bool>(PropOffsets_Actor.bDifficulty0); }
	bool& bDifficulty1() { return Value<bool>(PropOffsets_Actor.bDifficulty1); }
	bool& bDifficulty2() { return Value<bool>(PropOffsets_Actor.bDifficulty2); }
	bool& bDifficulty3() { return Value<bool>(PropOffsets_Actor.bDifficulty3); }
	bool& bDirectional() { return Value<bool>(PropOffsets_Actor.bDirectional); }
	bool& bDynamicLight() { return Value<bool>(PropOffsets_Actor.bDynamicLight); }
	bool& bEdLocked() { return Value<bool>(PropOffsets_Actor.bEdLocked); }
	bool& bEdShouldSnap() { return Value<bool>(PropOffsets_Actor.bEdShouldSnap); }
	bool& bEdSnap() { return Value<bool>(PropOffsets_Actor.bEdSnap); }
	bool& bFilterByVolume() { return Value<bool>(PropOffsets_Actor.bFilterByVolume); }
	bool& bFixedRotationDir() { return Value<bool>(PropOffsets_Actor.bFixedRotationDir); }
	bool& bForcePhysicsUpdate() { return Value<bool>(PropOffsets_Actor.bForcePhysicsUpdate); }
	bool& bForceStasis() { return Value<bool>(PropOffsets_Actor.bForceStasis); }
	bool& bGameRelevant() { return Value<bool>(PropOffsets_Actor.bGameRelevant); }
	bool& bHidden() { return Value<bool>(PropOffsets_Actor.bHidden); }
	bool& bHiddenEd() { return Value<bool>(PropOffsets_Actor.bHiddenEd); }
	bool& bHighDetail() { return Value<bool>(PropOffsets_Actor.bHighDetail); }
	bool& bHighlighted() { return Value<bool>(PropOffsets_Actor.bHighlighted); }
	bool& bHurtEntry() { return Value<bool>(PropOffsets_Actor.bHurtEntry); }
	bool& bInterpolating() { return Value<bool>(PropOffsets_Actor.bInterpolating); }
	bool& bIsItemGoal() { return Value<bool>(PropOffsets_Actor.bIsItemGoal); }
	bool& bIsKillGoal() { return Value<bool>(PropOffsets_Actor.bIsKillGoal); }
	bool& bIsMover() { return Value<bool>(PropOffsets_Actor.bIsMover); }
	bool& bIsPawn() { return Value<bool>(PropOffsets_Actor.bIsPawn); }
	bool& bIsSecretGoal() { return Value<bool>(PropOffsets_Actor.bIsSecretGoal); }
	bool& bJustTeleported() { return Value<bool>(PropOffsets_Actor.bJustTeleported); }
	bool& bLensFlare() { return Value<bool>(PropOffsets_Actor.bLensFlare); }
	bool& bLightChanged() { return Value<bool>(PropOffsets_Actor.bLightChanged); }
	bool& bMemorized() { return Value<bool>(PropOffsets_Actor.bMemorized); }
	bool& bMeshCurvy() { return Value<bool>(PropOffsets_Actor.bMeshCurvy); }
	bool& bMeshEnviroMap() { return Value<bool>(PropOffsets_Actor.bMeshEnviroMap); }
	bool& bMovable() { return Value<bool>(PropOffsets_Actor.bMovable); }
	bool& bNet() { return Value<bool>(PropOffsets_Actor.bNet); }
	bool& bNetFeel() { return Value<bool>(PropOffsets_Actor.bNetFeel); }
	bool& bNetHear() { return Value<bool>(PropOffsets_Actor.bNetHear); }
	bool& bNetInitial() { return Value<bool>(PropOffsets_Actor.bNetInitial); }
	bool& bNetOptional() { return Value<bool>(PropOffsets_Actor.bNetOptional); }
	bool& bNetOwner() { return Value<bool>(PropOffsets_Actor.bNetOwner); }
	bool& bNetRelevant() { return Value<bool>(PropOffsets_Actor.bNetRelevant); }
	bool& bNetSee() { return Value<bool>(PropOffsets_Actor.bNetSee); }
	bool& bNetSpecial() { return Value<bool>(PropOffsets_Actor.bNetSpecial); }
	bool& bNetTemporary() { return Value<bool>(PropOffsets_Actor.bNetTemporary); }
	bool& bNoDelete() { return Value<bool>(PropOffsets_Actor.bNoDelete); }
	bool& bNoSmooth() { return Value<bool>(PropOffsets_Actor.bNoSmooth); }
	bool& bOnlyOwnerSee() { return Value<bool>(PropOffsets_Actor.bOnlyOwnerSee); }
	bool& bOwnerNoSee() { return Value<bool>(PropOffsets_Actor.bOwnerNoSee); }
	bool& bParticles() { return Value<bool>(PropOffsets_Actor.bParticles); }
	bool& bProjTarget() { return Value<bool>(PropOffsets_Actor.bProjTarget); }
	bool& bRandomFrame() { return Value<bool>(PropOffsets_Actor.bRandomFrame); }
	bool& bReplicateInstigator() { return Value<bool>(PropOffsets_Actor.bReplicateInstigator); }
	bool& bRotateToDesired() { return Value<bool>(PropOffsets_Actor.bRotateToDesired); }
	bool& bScriptInitialized() { return Value<bool>(PropOffsets_Actor.bScriptInitialized); }
	bool& bSelected() { return Value<bool>(PropOffsets_Actor.bSelected); }
	bool& bShadowCast() { return Value<bool>(PropOffsets_Actor.bShadowCast); }
	bool& bSimFall() { return Value<bool>(PropOffsets_Actor.bSimFall); }
	bool& bSimulatedPawn() { return Value<bool>(PropOffsets_Actor.bSimulatedPawn); }
	bool& bSinglePlayer() { return Value<bool>(PropOffsets_Actor.bSinglePlayer); }
	bool& bSpecialLit() { return Value<bool>(PropOffsets_Actor.bSpecialLit); }
	bool& bStasis() { return Value<bool>(PropOffsets_Actor.bStasis); }
	bool& bStatic() { return Value<bool>(PropOffsets_Actor.bStatic); }
	bool& bTempEditor() { return Value<bool>(PropOffsets_Actor.bTempEditor); }
	bool& bTicked() { return Value<bool>(PropOffsets_Actor.bTicked); }
	bool& bTimerLoop() { return Value<bool>(PropOffsets_Actor.bTimerLoop); }
	bool& bTrailerPrePivot() { return Value<bool>(PropOffsets_Actor.bTrailerPrePivot); }
	bool& bTrailerSameRotation() { return Value<bool>(PropOffsets_Actor.bTrailerSameRotation); }
	bool& bTravel() { return Value<bool>(PropOffsets_Actor.bTravel); }
	bool& bUnlit() { return Value<bool>(PropOffsets_Actor.bUnlit); }
};

class ULight : public UActor
{
public:
	using UActor::UActor;
};

class UDecal : public UActor
{
public:
	using UActor::UActor;

	float& LastRenderedTime() { return Value<float>(PropOffsets_Decal.LastRenderedTime); }
	int& MultiDecalLevel() { return Value<int>(PropOffsets_Decal.MultiDecalLevel); }
	std::vector<void*>& SurfList() { return Value<std::vector<void*>>(PropOffsets_Decal.SurfList); }
};

class USpawnNotify : public UActor
{
public:
	using UActor::UActor;

	UClass*& ActorClass() { return Value<UClass*>(PropOffsets_SpawnNotify.ActorClass); }
	USpawnNotify*& Next() { return Value<USpawnNotify*>(PropOffsets_SpawnNotify.Next); }
};

class UInventory : public UActor
{
public:
	using UActor::UActor;

	int& AbsorptionPriority() { return Value<int>(PropOffsets_Inventory.AbsorptionPriority); }
	USound*& ActivateSound() { return Value<USound*>(PropOffsets_Inventory.ActivateSound); }
	int& ArmorAbsorption() { return Value<int>(PropOffsets_Inventory.ArmorAbsorption); }
	uint8_t& AutoSwitchPriority() { return Value<uint8_t>(PropOffsets_Inventory.AutoSwitchPriority); }
	float& BobDamping() { return Value<float>(PropOffsets_Inventory.BobDamping); }
	int& Charge() { return Value<int>(PropOffsets_Inventory.Charge); }
	USound*& DeActivateSound() { return Value<USound*>(PropOffsets_Inventory.DeActivateSound); }
	uint8_t& FlashCount() { return Value<uint8_t>(PropOffsets_Inventory.FlashCount); }
	UTexture*& Icon() { return Value<UTexture*>(PropOffsets_Inventory.Icon); }
	uint8_t& InventoryGroup() { return Value<uint8_t>(PropOffsets_Inventory.InventoryGroup); }
	std::string& ItemArticle() { return Value<std::string>(PropOffsets_Inventory.ItemArticle); }
	UClass*& ItemMessageClass() { return Value<UClass*>(PropOffsets_Inventory.ItemMessageClass); }
	std::string& ItemName() { return Value<std::string>(PropOffsets_Inventory.ItemName); }
	std::string& M_Activated() { return Value<std::string>(PropOffsets_Inventory.M_Activated); }
	std::string& M_Deactivated() { return Value<std::string>(PropOffsets_Inventory.M_Deactivated); }
	std::string& M_Selected() { return Value<std::string>(PropOffsets_Inventory.M_Selected); }
	float& MaxDesireability() { return Value<float>(PropOffsets_Inventory.MaxDesireability); }
	UMesh*& MuzzleFlashMesh() { return Value<UMesh*>(PropOffsets_Inventory.MuzzleFlashMesh); }
	float& MuzzleFlashScale() { return Value<float>(PropOffsets_Inventory.MuzzleFlashScale); }
	uint8_t& MuzzleFlashStyle() { return Value<uint8_t>(PropOffsets_Inventory.MuzzleFlashStyle); }
	UTexture*& MuzzleFlashTexture() { return Value<UTexture*>(PropOffsets_Inventory.MuzzleFlashTexture); }
	UInventory*& NextArmor() { return Value<UInventory*>(PropOffsets_Inventory.NextArmor); }
	uint8_t& OldFlashCount() { return Value<uint8_t>(PropOffsets_Inventory.OldFlashCount); }
	std::string& PickupMessage() { return Value<std::string>(PropOffsets_Inventory.PickupMessage); }
	UClass*& PickupMessageClass() { return Value<UClass*>(PropOffsets_Inventory.PickupMessageClass); }
	USound*& PickupSound() { return Value<USound*>(PropOffsets_Inventory.PickupSound); }
	UMesh*& PickupViewMesh() { return Value<UMesh*>(PropOffsets_Inventory.PickupViewMesh); }
	float& PickupViewScale() { return Value<float>(PropOffsets_Inventory.PickupViewScale); }
	std::string& PlayerLastTouched() { return Value<std::string>(PropOffsets_Inventory.PlayerLastTouched); }
	UMesh*& PlayerViewMesh() { return Value<UMesh*>(PropOffsets_Inventory.PlayerViewMesh); }
	vec3& PlayerViewOffset() { return Value<vec3>(PropOffsets_Inventory.PlayerViewOffset); }
	float& PlayerViewScale() { return Value<float>(PropOffsets_Inventory.PlayerViewScale); }
	std::string& ProtectionType1() { return Value<std::string>(PropOffsets_Inventory.ProtectionType1); }
	std::string& ProtectionType2() { return Value<std::string>(PropOffsets_Inventory.ProtectionType2); }
	USound*& RespawnSound() { return Value<USound*>(PropOffsets_Inventory.RespawnSound); }
	float& RespawnTime() { return Value<float>(PropOffsets_Inventory.RespawnTime); }
	UTexture*& StatusIcon() { return Value<UTexture*>(PropOffsets_Inventory.StatusIcon); }
	UMesh*& ThirdPersonMesh() { return Value<UMesh*>(PropOffsets_Inventory.ThirdPersonMesh); }
	float& ThirdPersonScale() { return Value<float>(PropOffsets_Inventory.ThirdPersonScale); }
	bool& bActivatable() { return Value<bool>(PropOffsets_Inventory.bActivatable); }
	bool& bActive() { return Value<bool>(PropOffsets_Inventory.bActive); }
	bool& bAmbientGlow() { return Value<bool>(PropOffsets_Inventory.bAmbientGlow); }
	bool& bDisplayableInv() { return Value<bool>(PropOffsets_Inventory.bDisplayableInv); }
	bool& bFirstFrame() { return Value<bool>(PropOffsets_Inventory.bFirstFrame); }
	bool& bHeldItem() { return Value<bool>(PropOffsets_Inventory.bHeldItem); }
	bool& bInstantRespawn() { return Value<bool>(PropOffsets_Inventory.bInstantRespawn); }
	bool& bIsAnArmor() { return Value<bool>(PropOffsets_Inventory.bIsAnArmor); }
	bool& bMuzzleFlashParticles() { return Value<bool>(PropOffsets_Inventory.bMuzzleFlashParticles); }
	bool& bRotatingPickup() { return Value<bool>(PropOffsets_Inventory.bRotatingPickup); }
	bool& bSleepTouch() { return Value<bool>(PropOffsets_Inventory.bSleepTouch); }
	bool& bSteadyFlash3rd() { return Value<bool>(PropOffsets_Inventory.bSteadyFlash3rd); }
	bool& bSteadyToggle() { return Value<bool>(PropOffsets_Inventory.bSteadyToggle); }
	bool& bToggleSteadyFlash() { return Value<bool>(PropOffsets_Inventory.bToggleSteadyFlash); }
	bool& bTossedOut() { return Value<bool>(PropOffsets_Inventory.bTossedOut); }
	UInventorySpot*& myMarker() { return Value<UInventorySpot*>(PropOffsets_Inventory.myMarker); }
};

class UWeapon : public UInventory
{
public:
	using UInventory::UInventory;

	float& AIRating() { return Value<float>(PropOffsets_Weapon.AIRating); }
	Rotator& AdjustedAim() { return Value<Rotator>(PropOffsets_Weapon.AdjustedAim); }
	std::string& AltDamageType() { return Value<std::string>(PropOffsets_Weapon.AltDamageType); }
	USound*& AltFireSound() { return Value<USound*>(PropOffsets_Weapon.AltFireSound); }
	UClass*& AltProjectileClass() { return Value<UClass*>(PropOffsets_Weapon.AltProjectileClass); }
	float& AltProjectileSpeed() { return Value<float>(PropOffsets_Weapon.AltProjectileSpeed); }
	float& AltRefireRate() { return Value<float>(PropOffsets_Weapon.AltRefireRate); }
	UClass*& AmmoName() { return Value<UClass*>(PropOffsets_Weapon.AmmoName); }
	// UAmmo*& AmmoType() { return Value<UAmmo*>(PropOffsets_Weapon.AmmoType); }
	USound*& CockingSound() { return Value<USound*>(PropOffsets_Weapon.CockingSound); }
	std::string& DeathMessage() { return Value<std::string>(PropOffsets_Weapon.DeathMessage); }
	vec3& FireOffset() { return Value<vec3>(PropOffsets_Weapon.FireOffset); }
	USound*& FireSound() { return Value<USound*>(PropOffsets_Weapon.FireSound); }
	float& FiringSpeed() { return Value<float>(PropOffsets_Weapon.FiringSpeed); }
	float& FlareOffset() { return Value<float>(PropOffsets_Weapon.FlareOffset); }
	float& FlashC() { return Value<float>(PropOffsets_Weapon.FlashC); }
	float& FlashLength() { return Value<float>(PropOffsets_Weapon.FlashLength); }
	float& FlashO() { return Value<float>(PropOffsets_Weapon.FlashO); }
	int& FlashS() { return Value<int>(PropOffsets_Weapon.FlashS); }
	float& FlashTime() { return Value<float>(PropOffsets_Weapon.FlashTime); }
	float& FlashY() { return Value<float>(PropOffsets_Weapon.FlashY); }
	UTexture*& MFTexture() { return Value<UTexture*>(PropOffsets_Weapon.MFTexture); }
	float& MaxTargetRange() { return Value<float>(PropOffsets_Weapon.MaxTargetRange); }
	std::string& MessageNoAmmo() { return Value<std::string>(PropOffsets_Weapon.MessageNoAmmo); }
	USound*& Misc1Sound() { return Value<USound*>(PropOffsets_Weapon.Misc1Sound); }
	USound*& Misc2Sound() { return Value<USound*>(PropOffsets_Weapon.Misc2Sound); }
	USound*& Misc3Sound() { return Value<USound*>(PropOffsets_Weapon.Misc3Sound); }
	UTexture*& MuzzleFlare() { return Value<UTexture*>(PropOffsets_Weapon.MuzzleFlare); }
	float& MuzzleScale() { return Value<float>(PropOffsets_Weapon.MuzzleScale); }
	std::string& MyDamageType() { return Value<std::string>(PropOffsets_Weapon.MyDamageType); }
	Color& NameColor() { return Value<Color>(PropOffsets_Weapon.NameColor); }
	int& PickupAmmoCount() { return Value<int>(PropOffsets_Weapon.PickupAmmoCount); }
	UClass*& ProjectileClass() { return Value<UClass*>(PropOffsets_Weapon.ProjectileClass); }
	float& ProjectileSpeed() { return Value<float>(PropOffsets_Weapon.ProjectileSpeed); }
	float& RefireRate() { return Value<float>(PropOffsets_Weapon.RefireRate); }
	uint8_t& ReloadCount() { return Value<uint8_t>(PropOffsets_Weapon.ReloadCount); }
	USound*& SelectSound() { return Value<USound*>(PropOffsets_Weapon.SelectSound); }
	float& aimerror() { return Value<float>(PropOffsets_Weapon.aimerror); }
	bool& bAltInstantHit() { return Value<bool>(PropOffsets_Weapon.bAltInstantHit); }
	bool& bAltWarnTarget() { return Value<bool>(PropOffsets_Weapon.bAltWarnTarget); }
	bool& bCanThrow() { return Value<bool>(PropOffsets_Weapon.bCanThrow); }
	bool& bChangeWeapon() { return Value<bool>(PropOffsets_Weapon.bChangeWeapon); }
	bool& bDrawMuzzleFlash() { return Value<bool>(PropOffsets_Weapon.bDrawMuzzleFlash); }
	bool& bHideWeapon() { return Value<bool>(PropOffsets_Weapon.bHideWeapon); }
	bool& bInstantHit() { return Value<bool>(PropOffsets_Weapon.bInstantHit); }
	bool& bLockedOn() { return Value<bool>(PropOffsets_Weapon.bLockedOn); }
	bool& bMeleeWeapon() { return Value<bool>(PropOffsets_Weapon.bMeleeWeapon); }
	uint8_t& bMuzzleFlash() { return Value<uint8_t>(PropOffsets_Weapon.bMuzzleFlash); }
	bool& bOwnsCrosshair() { return Value<bool>(PropOffsets_Weapon.bOwnsCrosshair); }
	bool& bPointing() { return Value<bool>(PropOffsets_Weapon.bPointing); }
	bool& bRapidFire() { return Value<bool>(PropOffsets_Weapon.bRapidFire); }
	bool& bRecommendAltSplashDamage() { return Value<bool>(PropOffsets_Weapon.bRecommendAltSplashDamage); }
	bool& bRecommendSplashDamage() { return Value<bool>(PropOffsets_Weapon.bRecommendSplashDamage); }
	bool& bSetFlashTime() { return Value<bool>(PropOffsets_Weapon.bSetFlashTime); }
	bool& bSpecialIcon() { return Value<bool>(PropOffsets_Weapon.bSpecialIcon); }
	bool& bSplashDamage() { return Value<bool>(PropOffsets_Weapon.bSplashDamage); }
	bool& bWarnTarget() { return Value<bool>(PropOffsets_Weapon.bWarnTarget); }
	bool& bWeaponStay() { return Value<bool>(PropOffsets_Weapon.bWeaponStay); }
	bool& bWeaponUp() { return Value<bool>(PropOffsets_Weapon.bWeaponUp); }
	float& shakemag() { return Value<float>(PropOffsets_Weapon.shakemag); }
	float& shaketime() { return Value<float>(PropOffsets_Weapon.shaketime); }
	float& shakevert() { return Value<float>(PropOffsets_Weapon.shakevert); }
};

class UNavigationPoint : public UActor
{
public:
	using UActor::UActor;

	int& ExtraCost() { return Value<int>(PropOffsets_NavigationPoint.ExtraCost); }
	int& Paths() { return Value<int>(PropOffsets_NavigationPoint.Paths); }
	int& PrunedPaths() { return Value<int>(PropOffsets_NavigationPoint.PrunedPaths); }
	UActor*& RouteCache() { return Value<UActor*>(PropOffsets_NavigationPoint.RouteCache); }
	UNavigationPoint*& VisNoReachPaths() { return Value<UNavigationPoint*>(PropOffsets_NavigationPoint.VisNoReachPaths); }
	bool& bAutoBuilt() { return Value<bool>(PropOffsets_NavigationPoint.bAutoBuilt); }
	bool& bEndPoint() { return Value<bool>(PropOffsets_NavigationPoint.bEndPoint); }
	bool& bEndPointOnly() { return Value<bool>(PropOffsets_NavigationPoint.bEndPointOnly); }
	bool& bNeverUseStrafing() { return Value<bool>(PropOffsets_NavigationPoint.bNeverUseStrafing); }
	bool& bOneWayPath() { return Value<bool>(PropOffsets_NavigationPoint.bOneWayPath); }
	bool& bPlayerOnly() { return Value<bool>(PropOffsets_NavigationPoint.bPlayerOnly); }
	bool& bSpecialCost() { return Value<bool>(PropOffsets_NavigationPoint.bSpecialCost); }
	bool& bTwoWay() { return Value<bool>(PropOffsets_NavigationPoint.bTwoWay); }
	int& bestPathWeight() { return Value<int>(PropOffsets_NavigationPoint.bestPathWeight); }
	int& cost() { return Value<int>(PropOffsets_NavigationPoint.cost); }
	UNavigationPoint*& nextNavigationPoint() { return Value<UNavigationPoint*>(PropOffsets_NavigationPoint.nextNavigationPoint); }
	UNavigationPoint*& nextOrdered() { return Value<UNavigationPoint*>(PropOffsets_NavigationPoint.nextOrdered); }
	std::string& ownerTeam() { return Value<std::string>(PropOffsets_NavigationPoint.ownerTeam); }
	UNavigationPoint*& prevOrdered() { return Value<UNavigationPoint*>(PropOffsets_NavigationPoint.prevOrdered); }
	UNavigationPoint*& previousPath() { return Value<UNavigationPoint*>(PropOffsets_NavigationPoint.previousPath); }
	UNavigationPoint*& startPath() { return Value<UNavigationPoint*>(PropOffsets_NavigationPoint.startPath); }
	bool& taken() { return Value<bool>(PropOffsets_NavigationPoint.taken); }
	int& upstreamPaths() { return Value<int>(PropOffsets_NavigationPoint.upstreamPaths); }
	int& visitedWeight() { return Value<int>(PropOffsets_NavigationPoint.visitedWeight); }
};

class ULiftExit : public UNavigationPoint
{
public:
	using UNavigationPoint::UNavigationPoint;

	float& LastTriggerTime() { return Value<float>(PropOffsets_LiftExit.LastTriggerTime); }
	std::string& LiftTag() { return Value<std::string>(PropOffsets_LiftExit.LiftTag); }
	std::string& LiftTrigger() { return Value<std::string>(PropOffsets_LiftExit.LiftTrigger); }
	UMover*& MyLift() { return Value<UMover*>(PropOffsets_LiftExit.MyLift); }
	UTrigger*& RecommendedTrigger() { return Value<UTrigger*>(PropOffsets_LiftExit.RecommendedTrigger); }
};

class ULiftCenter : public UNavigationPoint
{
public:
	using UNavigationPoint::UNavigationPoint;

	float& LastTriggerTime() { return Value<float>(PropOffsets_LiftCenter.LastTriggerTime); }
	vec3& LiftOffset() { return Value<vec3>(PropOffsets_LiftCenter.LiftOffset); }
	std::string& LiftTag() { return Value<std::string>(PropOffsets_LiftCenter.LiftTag); }
	std::string& LiftTrigger() { return Value<std::string>(PropOffsets_LiftCenter.LiftTrigger); }
	float& MaxDist2D() { return Value<float>(PropOffsets_LiftCenter.MaxDist2D); }
	float& MaxZDiffAdd() { return Value<float>(PropOffsets_LiftCenter.MaxZDiffAdd); }
	UMover*& MyLift() { return Value<UMover*>(PropOffsets_LiftCenter.MyLift); }
	UTrigger*& RecommendedTrigger() { return Value<UTrigger*>(PropOffsets_LiftCenter.RecommendedTrigger); }
};

class UWarpZoneMarker : public UNavigationPoint
{
public:
	using UNavigationPoint::UNavigationPoint;

	UActor*& TriggerActor() { return Value<UActor*>(PropOffsets_WarpZoneMarker.TriggerActor); }
	UActor*& TriggerActor2() { return Value<UActor*>(PropOffsets_WarpZoneMarker.TriggerActor2); }
	UWarpZoneInfo*& markedWarpZone() { return Value<UWarpZoneInfo*>(PropOffsets_WarpZoneMarker.markedWarpZone); }
};

class UInventorySpot : public UNavigationPoint
{
public:
	using UNavigationPoint::UNavigationPoint;

	UInventory*& markedItem() { return Value<UInventory*>(PropOffsets_InventorySpot.markedItem); }
};

class UTriggerMarker : public UNavigationPoint
{
public:
	using UNavigationPoint::UNavigationPoint;
};

class UButtonMarker : public UNavigationPoint
{
public:
	using UNavigationPoint::UNavigationPoint;
};

class UPlayerStart : public UNavigationPoint
{
public:
	using UNavigationPoint::UNavigationPoint;

	uint8_t& TeamNumber() { return Value<uint8_t>(PropOffsets_PlayerStart.TeamNumber); }
	bool& bCoopStart() { return Value<bool>(PropOffsets_PlayerStart.bCoopStart); }
	bool& bEnabled() { return Value<bool>(PropOffsets_PlayerStart.bEnabled); }
	bool& bSinglePlayerStart() { return Value<bool>(PropOffsets_PlayerStart.bSinglePlayerStart); }
};

class UTeleporter : public UNavigationPoint
{
public:
	using UNavigationPoint::UNavigationPoint;

	float& LastFired() { return Value<float>(PropOffsets_Teleporter.LastFired); }
	std::string& ProductRequired() { return Value<std::string>(PropOffsets_Teleporter.ProductRequired); }
	vec3& TargetVelocity() { return Value<vec3>(PropOffsets_Teleporter.TargetVelocity); }
	UActor*& TriggerActor() { return Value<UActor*>(PropOffsets_Teleporter.TriggerActor); }
	UActor*& TriggerActor2() { return Value<UActor*>(PropOffsets_Teleporter.TriggerActor2); }
	std::string& URL() { return Value<std::string>(PropOffsets_Teleporter.URL); }
	bool& bChangesVelocity() { return Value<bool>(PropOffsets_Teleporter.bChangesVelocity); }
	bool& bChangesYaw() { return Value<bool>(PropOffsets_Teleporter.bChangesYaw); }
	bool& bEnabled() { return Value<bool>(PropOffsets_Teleporter.bEnabled); }
	bool& bReversesX() { return Value<bool>(PropOffsets_Teleporter.bReversesX); }
	bool& bReversesY() { return Value<bool>(PropOffsets_Teleporter.bReversesY); }
	bool& bReversesZ() { return Value<bool>(PropOffsets_Teleporter.bReversesZ); }
};

class UPathNode : public UNavigationPoint
{
public:
	using UNavigationPoint::UNavigationPoint;
};

class UDecoration : public UActor
{
public:
	using UActor::UActor;

	UClass*& EffectWhenDestroyed() { return Value<UClass*>(PropOffsets_Decoration.EffectWhenDestroyed); }
	USound*& EndPushSound() { return Value<USound*>(PropOffsets_Decoration.EndPushSound); }
	USound*& PushSound() { return Value<USound*>(PropOffsets_Decoration.PushSound); }
	bool& bBobbing() { return Value<bool>(PropOffsets_Decoration.bBobbing); }
	bool& bOnlyTriggerable() { return Value<bool>(PropOffsets_Decoration.bOnlyTriggerable); }
	bool& bPushSoundPlaying() { return Value<bool>(PropOffsets_Decoration.bPushSoundPlaying); }
	bool& bPushable() { return Value<bool>(PropOffsets_Decoration.bPushable); }
	bool& bSplash() { return Value<bool>(PropOffsets_Decoration.bSplash); }
	bool& bWasCarried() { return Value<bool>(PropOffsets_Decoration.bWasCarried); }
	UClass*& content2() { return Value<UClass*>(PropOffsets_Decoration.content2); }
	UClass*& content3() { return Value<UClass*>(PropOffsets_Decoration.content3); }
	UClass*& contents() { return Value<UClass*>(PropOffsets_Decoration.contents); }
	int& numLandings() { return Value<int>(PropOffsets_Decoration.numLandings); }
};

class UCarcass : public UDecoration
{
public:
	using UDecoration::UDecoration;

	UPawn*& Bugs() { return Value<UPawn*>(PropOffsets_Carcass.Bugs); }
	int& CumulativeDamage() { return Value<int>(PropOffsets_Carcass.CumulativeDamage); }
	UPlayerReplicationInfo*& PlayerOwner() { return Value<UPlayerReplicationInfo*>(PropOffsets_Carcass.PlayerOwner); }
	bool& bDecorative() { return Value<bool>(PropOffsets_Carcass.bDecorative); }
	bool& bPlayerCarcass() { return Value<bool>(PropOffsets_Carcass.bPlayerCarcass); }
	bool& bReducedHeight() { return Value<bool>(PropOffsets_Carcass.bReducedHeight); }
	bool& bSlidingCarcass() { return Value<bool>(PropOffsets_Carcass.bSlidingCarcass); }
	uint8_t& flies() { return Value<uint8_t>(PropOffsets_Carcass.flies); }
	uint8_t& rats() { return Value<uint8_t>(PropOffsets_Carcass.rats); }
};

class UProjectile : public UActor
{
public:
	using UActor::UActor;

	float& Damage() { return Value<float>(PropOffsets_Projectile.Damage); }
	float& ExploWallOut() { return Value<float>(PropOffsets_Projectile.ExploWallOut); }
	UClass*& ExplosionDecal() { return Value<UClass*>(PropOffsets_Projectile.ExplosionDecal); }
	USound*& ImpactSound() { return Value<USound*>(PropOffsets_Projectile.ImpactSound); }
	float& MaxSpeed() { return Value<float>(PropOffsets_Projectile.MaxSpeed); }
	USound*& MiscSound() { return Value<USound*>(PropOffsets_Projectile.MiscSound); }
	int& MomentumTransfer() { return Value<int>(PropOffsets_Projectile.MomentumTransfer); }
	std::string& MyDamageType() { return Value<std::string>(PropOffsets_Projectile.MyDamageType); }
	USound*& SpawnSound() { return Value<USound*>(PropOffsets_Projectile.SpawnSound); }
	float& speed() { return Value<float>(PropOffsets_Projectile.speed); }
};

class UKeypoint : public UActor
{
public:
	using UActor::UActor;
};

class Ulocationid : public UKeypoint
{
public:
	using UKeypoint::UKeypoint;

	std::string& LocationName() { return Value<std::string>(PropOffsets_locationid.LocationName); }
	Ulocationid*& NextLocation() { return Value<Ulocationid*>(PropOffsets_locationid.NextLocation); }
	float& Radius() { return Value<float>(PropOffsets_locationid.Radius); }
};

class UInterpolationPoint : public UKeypoint
{
public:
	using UKeypoint::UKeypoint;

	float& FovModifier() { return Value<float>(PropOffsets_InterpolationPoint.FovModifier); }
	float& GameSpeedModifier() { return Value<float>(PropOffsets_InterpolationPoint.GameSpeedModifier); }
	UInterpolationPoint*& Next() { return Value<UInterpolationPoint*>(PropOffsets_InterpolationPoint.Next); }
	int& Position() { return Value<int>(PropOffsets_InterpolationPoint.Position); }
	UInterpolationPoint*& Prev() { return Value<UInterpolationPoint*>(PropOffsets_InterpolationPoint.Prev); }
	float& RateModifier() { return Value<float>(PropOffsets_InterpolationPoint.RateModifier); }
	vec3& ScreenFlashFog() { return Value<vec3>(PropOffsets_InterpolationPoint.ScreenFlashFog); }
	float& ScreenFlashScale() { return Value<float>(PropOffsets_InterpolationPoint.ScreenFlashScale); }
	bool& bEndOfPath() { return Value<bool>(PropOffsets_InterpolationPoint.bEndOfPath); }
	bool& bSkipNextPath() { return Value<bool>(PropOffsets_InterpolationPoint.bSkipNextPath); }
};

class UTriggers : public UActor
{
public:
	using UActor::UActor;
};

class UTrigger : public UTriggers
{
public:
	using UTriggers::UTriggers;

	UClass*& ClassProximityType() { return Value<UClass*>(PropOffsets_Trigger.ClassProximityType); }
	float& DamageThreshold() { return Value<float>(PropOffsets_Trigger.DamageThreshold); }
	std::string& Message() { return Value<std::string>(PropOffsets_Trigger.Message); }
	float& ReTriggerDelay() { return Value<float>(PropOffsets_Trigger.ReTriggerDelay); }
	float& RepeatTriggerTime() { return Value<float>(PropOffsets_Trigger.RepeatTriggerTime); }
	UActor*& TriggerActor() { return Value<UActor*>(PropOffsets_Trigger.TriggerActor); }
	UActor*& TriggerActor2() { return Value<UActor*>(PropOffsets_Trigger.TriggerActor2); }
	float& TriggerTime() { return Value<float>(PropOffsets_Trigger.TriggerTime); }
	uint8_t& TriggerType() { return Value<uint8_t>(PropOffsets_Trigger.TriggerType); }
	bool& bInitiallyActive() { return Value<bool>(PropOffsets_Trigger.bInitiallyActive); }
	bool& bTriggerOnceOnly() { return Value<bool>(PropOffsets_Trigger.bTriggerOnceOnly); }
};

class UHUD : public UActor
{
public:
	using UActor::UActor;

	int& Crosshair() { return Value<int>(PropOffsets_HUD.Crosshair); }
	std::string& HUDConfigWindowType() { return Value<std::string>(PropOffsets_HUD.HUDConfigWindowType); }
	UMutator*& HUDMutator() { return Value<UMutator*>(PropOffsets_HUD.HUDMutator); }
	int& HudMode() { return Value<int>(PropOffsets_HUD.HudMode); }
	UMenu*& MainMenu() { return Value<UMenu*>(PropOffsets_HUD.MainMenu); }
	UClass*& MainMenuType() { return Value<UClass*>(PropOffsets_HUD.MainMenuType); }
	UPlayerPawn*& PlayerOwner() { return Value<UPlayerPawn*>(PropOffsets_HUD.PlayerOwner); }
	Color& WhiteColor() { return Value<Color>(PropOffsets_HUD.WhiteColor); }
};

class UMenu : public UActor
{
public:
	using UActor::UActor;

	std::string& CenterString() { return Value<std::string>(PropOffsets_Menu.CenterString); }
	std::string& DisabledString() { return Value<std::string>(PropOffsets_Menu.DisabledString); }
	std::string& EnabledString() { return Value<std::string>(PropOffsets_Menu.EnabledString); }
	std::string& HelpMessage() { return Value<std::string>(PropOffsets_Menu.HelpMessage); }
	std::string& LeftString() { return Value<std::string>(PropOffsets_Menu.LeftString); }
	int& MenuLength() { return Value<int>(PropOffsets_Menu.MenuLength); }
	std::string& MenuList() { return Value<std::string>(PropOffsets_Menu.MenuList); }
	std::string& MenuTitle() { return Value<std::string>(PropOffsets_Menu.MenuTitle); }
	std::string& NoString() { return Value<std::string>(PropOffsets_Menu.NoString); }
	UMenu*& ParentMenu() { return Value<UMenu*>(PropOffsets_Menu.ParentMenu); }
	UPlayerPawn*& PlayerOwner() { return Value<UPlayerPawn*>(PropOffsets_Menu.PlayerOwner); }
	std::string& RightString() { return Value<std::string>(PropOffsets_Menu.RightString); }
	int& Selection() { return Value<int>(PropOffsets_Menu.Selection); }
	std::string& YesString() { return Value<std::string>(PropOffsets_Menu.YesString); }
	bool& bConfigChanged() { return Value<bool>(PropOffsets_Menu.bConfigChanged); }
	bool& bExitAllMenus() { return Value<bool>(PropOffsets_Menu.bExitAllMenus); }
};

class UInfo : public UActor
{
public:
	using UActor::UActor;
};

class UMutator : public UInfo
{
public:
	using UInfo::UInfo;

	UClass*& DefaultWeapon() { return Value<UClass*>(PropOffsets_Mutator.DefaultWeapon); }
	UMutator*& NextDamageMutator() { return Value<UMutator*>(PropOffsets_Mutator.NextDamageMutator); }
	UMutator*& NextHUDMutator() { return Value<UMutator*>(PropOffsets_Mutator.NextHUDMutator); }
	UMutator*& NextMessageMutator() { return Value<UMutator*>(PropOffsets_Mutator.NextMessageMutator); }
	UMutator*& NextMutator() { return Value<UMutator*>(PropOffsets_Mutator.NextMutator); }
	bool& bHUDMutator() { return Value<bool>(PropOffsets_Mutator.bHUDMutator); }
};

class UGameInfo : public UInfo
{
public:
	using UInfo::UInfo;

	std::string& AdminPassword() { return Value<std::string>(PropOffsets_GameInfo.AdminPassword); }
	float& AutoAim() { return Value<float>(PropOffsets_GameInfo.AutoAim); }
	UMutator*& BaseMutator() { return Value<UMutator*>(PropOffsets_GameInfo.BaseMutator); }
	std::string& BeaconName() { return Value<std::string>(PropOffsets_GameInfo.BeaconName); }
	std::string& BotMenuType() { return Value<std::string>(PropOffsets_GameInfo.BotMenuType); }
	int& CurrentID() { return Value<int>(PropOffsets_GameInfo.CurrentID); }
	UClass*& DMMessageClass() { return Value<UClass*>(PropOffsets_GameInfo.DMMessageClass); }
	UMutator*& DamageMutator() { return Value<UMutator*>(PropOffsets_GameInfo.DamageMutator); }
	UClass*& DeathMessageClass() { return Value<UClass*>(PropOffsets_GameInfo.DeathMessageClass); }
	UClass*& DefaultPlayerClass() { return Value<UClass*>(PropOffsets_GameInfo.DefaultPlayerClass); }
	std::string& DefaultPlayerName() { return Value<std::string>(PropOffsets_GameInfo.DefaultPlayerName); }
	std::string& DefaultPlayerState() { return Value<std::string>(PropOffsets_GameInfo.DefaultPlayerState); }
	UClass*& DefaultWeapon() { return Value<UClass*>(PropOffsets_GameInfo.DefaultWeapon); }
	int& DemoBuild() { return Value<int>(PropOffsets_GameInfo.DemoBuild); }
	int& DemoHasTuts() { return Value<int>(PropOffsets_GameInfo.DemoHasTuts); }
	uint8_t& Difficulty() { return Value<uint8_t>(PropOffsets_GameInfo.Difficulty); }
	std::string& EnabledMutators() { return Value<std::string>(PropOffsets_GameInfo.EnabledMutators); }
	std::string& EnteredMessage() { return Value<std::string>(PropOffsets_GameInfo.EnteredMessage); }
	std::string& FailedPlaceMessage() { return Value<std::string>(PropOffsets_GameInfo.FailedPlaceMessage); }
	std::string& FailedSpawnMessage() { return Value<std::string>(PropOffsets_GameInfo.FailedSpawnMessage); }
	std::string& FailedTeamMessage() { return Value<std::string>(PropOffsets_GameInfo.FailedTeamMessage); }
	UClass*& GameMenuType() { return Value<UClass*>(PropOffsets_GameInfo.GameMenuType); }
	std::string& GameName() { return Value<std::string>(PropOffsets_GameInfo.GameName); }
	std::string& GameOptionsMenuType() { return Value<std::string>(PropOffsets_GameInfo.GameOptionsMenuType); }
	std::string& GamePassword() { return Value<std::string>(PropOffsets_GameInfo.GamePassword); }
	UGameReplicationInfo*& GameReplicationInfo() { return Value<UGameReplicationInfo*>(PropOffsets_GameInfo.GameReplicationInfo); }
	UClass*& GameReplicationInfoClass() { return Value<UClass*>(PropOffsets_GameInfo.GameReplicationInfoClass); }
	float& GameSpeed() { return Value<float>(PropOffsets_GameInfo.GameSpeed); }
	std::string& GameUMenuType() { return Value<std::string>(PropOffsets_GameInfo.GameUMenuType); }
	UClass*& HUDType() { return Value<UClass*>(PropOffsets_GameInfo.HUDType); }
	std::string& IPBanned() { return Value<std::string>(PropOffsets_GameInfo.IPBanned); }
	std::string& IPPolicies() { return Value<std::string>(PropOffsets_GameInfo.IPPolicies); }
	int& ItemGoals() { return Value<int>(PropOffsets_GameInfo.ItemGoals); }
	int& KillGoals() { return Value<int>(PropOffsets_GameInfo.KillGoals); }
	std::string& LeftMessage() { return Value<std::string>(PropOffsets_GameInfo.LeftMessage); }
	UStatLog*& LocalLog() { return Value<UStatLog*>(PropOffsets_GameInfo.LocalLog); }
	std::string& LocalLogFileName() { return Value<std::string>(PropOffsets_GameInfo.LocalLogFileName); }
	UClass*& MapListType() { return Value<UClass*>(PropOffsets_GameInfo.MapListType); }
	std::string& MapPrefix() { return Value<std::string>(PropOffsets_GameInfo.MapPrefix); }
	int& MaxPlayers() { return Value<int>(PropOffsets_GameInfo.MaxPlayers); }
	int& MaxSpectators() { return Value<int>(PropOffsets_GameInfo.MaxSpectators); }
	std::string& MaxedOutMessage() { return Value<std::string>(PropOffsets_GameInfo.MaxedOutMessage); }
	UMutator*& MessageMutator() { return Value<UMutator*>(PropOffsets_GameInfo.MessageMutator); }
	std::string& MultiplayerUMenuType() { return Value<std::string>(PropOffsets_GameInfo.MultiplayerUMenuType); }
	UClass*& MutatorClass() { return Value<UClass*>(PropOffsets_GameInfo.MutatorClass); }
	std::string& NameChangedMessage() { return Value<std::string>(PropOffsets_GameInfo.NameChangedMessage); }
	std::string& NeedPassword() { return Value<std::string>(PropOffsets_GameInfo.NeedPassword); }
	int& NumPlayers() { return Value<int>(PropOffsets_GameInfo.NumPlayers); }
	int& NumSpectators() { return Value<int>(PropOffsets_GameInfo.NumSpectators); }
	std::string& RulesMenuType() { return Value<std::string>(PropOffsets_GameInfo.RulesMenuType); }
	UClass*& ScoreBoardType() { return Value<UClass*>(PropOffsets_GameInfo.ScoreBoardType); }
	int& SecretGoals() { return Value<int>(PropOffsets_GameInfo.SecretGoals); }
	int& SentText() { return Value<int>(PropOffsets_GameInfo.SentText); }
	std::string& ServerLogName() { return Value<std::string>(PropOffsets_GameInfo.ServerLogName); }
	std::string& SettingsMenuType() { return Value<std::string>(PropOffsets_GameInfo.SettingsMenuType); }
	std::string& SpecialDamageString() { return Value<std::string>(PropOffsets_GameInfo.SpecialDamageString); }
	float& StartTime() { return Value<float>(PropOffsets_GameInfo.StartTime); }
	UClass*& StatLogClass() { return Value<UClass*>(PropOffsets_GameInfo.StatLogClass); }
	std::string& SwitchLevelMessage() { return Value<std::string>(PropOffsets_GameInfo.SwitchLevelMessage); }
	UClass*& WaterZoneType() { return Value<UClass*>(PropOffsets_GameInfo.WaterZoneType); }
	UStatLog*& WorldLog() { return Value<UStatLog*>(PropOffsets_GameInfo.WorldLog); }
	std::string& WorldLogFileName() { return Value<std::string>(PropOffsets_GameInfo.WorldLogFileName); }
	std::string& WrongPassword() { return Value<std::string>(PropOffsets_GameInfo.WrongPassword); }
	bool& bAllowFOV() { return Value<bool>(PropOffsets_GameInfo.bAllowFOV); }
	bool& bAlternateMode() { return Value<bool>(PropOffsets_GameInfo.bAlternateMode); }
	bool& bBatchLocal() { return Value<bool>(PropOffsets_GameInfo.bBatchLocal); }
	bool& bCanChangeSkin() { return Value<bool>(PropOffsets_GameInfo.bCanChangeSkin); }
	bool& bCanViewOthers() { return Value<bool>(PropOffsets_GameInfo.bCanViewOthers); }
	bool& bClassicDeathMessages() { return Value<bool>(PropOffsets_GameInfo.bClassicDeathMessages); }
	bool& bCoopWeaponMode() { return Value<bool>(PropOffsets_GameInfo.bCoopWeaponMode); }
	bool& bDeathMatch() { return Value<bool>(PropOffsets_GameInfo.bDeathMatch); }
	bool& bExternalBatcher() { return Value<bool>(PropOffsets_GameInfo.bExternalBatcher); }
	bool& bGameEnded() { return Value<bool>(PropOffsets_GameInfo.bGameEnded); }
	bool& bHumansOnly() { return Value<bool>(PropOffsets_GameInfo.bHumansOnly); }
	bool& bLocalLog() { return Value<bool>(PropOffsets_GameInfo.bLocalLog); }
	bool& bLoggingGame() { return Value<bool>(PropOffsets_GameInfo.bLoggingGame); }
	bool& bLowGore() { return Value<bool>(PropOffsets_GameInfo.bLowGore); }
	bool& bMuteSpectators() { return Value<bool>(PropOffsets_GameInfo.bMuteSpectators); }
	bool& bNoCheating() { return Value<bool>(PropOffsets_GameInfo.bNoCheating); }
	bool& bNoMonsters() { return Value<bool>(PropOffsets_GameInfo.bNoMonsters); }
	bool& bOverTime() { return Value<bool>(PropOffsets_GameInfo.bOverTime); }
	bool& bPauseable() { return Value<bool>(PropOffsets_GameInfo.bPauseable); }
	bool& bRestartLevel() { return Value<bool>(PropOffsets_GameInfo.bRestartLevel); }
	bool& bTeamGame() { return Value<bool>(PropOffsets_GameInfo.bTeamGame); }
	bool& bVeryLowGore() { return Value<bool>(PropOffsets_GameInfo.bVeryLowGore); }
	bool& bWorldLog() { return Value<bool>(PropOffsets_GameInfo.bWorldLog); }
};

class USavedMove : public UInfo
{
public:
	using UInfo::UInfo;

	float& Delta() { return Value<float>(PropOffsets_SavedMove.Delta); }
	uint8_t& DodgeMove() { return Value<uint8_t>(PropOffsets_SavedMove.DodgeMove); }
	USavedMove*& NextMove() { return Value<USavedMove*>(PropOffsets_SavedMove.NextMove); }
	float& TimeStamp() { return Value<float>(PropOffsets_SavedMove.TimeStamp); }
	bool& bAltFire() { return Value<bool>(PropOffsets_SavedMove.bAltFire); }
	bool& bDuck() { return Value<bool>(PropOffsets_SavedMove.bDuck); }
	bool& bFire() { return Value<bool>(PropOffsets_SavedMove.bFire); }
	bool& bForceAltFire() { return Value<bool>(PropOffsets_SavedMove.bForceAltFire); }
	bool& bForceFire() { return Value<bool>(PropOffsets_SavedMove.bForceFire); }
	bool& bPressedJump() { return Value<bool>(PropOffsets_SavedMove.bPressedJump); }
	bool& bRun() { return Value<bool>(PropOffsets_SavedMove.bRun); }
};

class UInternetInfo : public UInfo
{
public:
	using UInfo::UInfo;
};

class UZoneInfo : public UInfo
{
public:
	using UInfo::UInfo;

	uint8_t& AmbientBrightness() { return Value<uint8_t>(PropOffsets_ZoneInfo.AmbientBrightness); }
	uint8_t& AmbientHue() { return Value<uint8_t>(PropOffsets_ZoneInfo.AmbientHue); }
	uint8_t& AmbientSaturation() { return Value<uint8_t>(PropOffsets_ZoneInfo.AmbientSaturation); }
	int& CutoffHz() { return Value<int>(PropOffsets_ZoneInfo.CutoffHz); }
	int& DamagePerSec() { return Value<int>(PropOffsets_ZoneInfo.DamagePerSec); }
	std::string& DamageString() { return Value<std::string>(PropOffsets_ZoneInfo.DamageString); }
	std::string& DamageType() { return Value<std::string>(PropOffsets_ZoneInfo.DamageType); }
	uint8_t& Delay() { return Value<uint8_t>(PropOffsets_ZoneInfo.Delay); }
	UClass*& EntryActor() { return Value<UClass*>(PropOffsets_ZoneInfo.EntryActor); }
	USound*& EntrySound() { return Value<USound*>(PropOffsets_ZoneInfo.EntrySound); }
	UTexture*& EnvironmentMap() { return Value<UTexture*>(PropOffsets_ZoneInfo.EnvironmentMap); }
	UClass*& ExitActor() { return Value<UClass*>(PropOffsets_ZoneInfo.ExitActor); }
	USound*& ExitSound() { return Value<USound*>(PropOffsets_ZoneInfo.ExitSound); }
	Color& FogColor() { return Value<Color>(PropOffsets_ZoneInfo.FogColor); }
	float& FogDistance() { return Value<float>(PropOffsets_ZoneInfo.FogDistance); }
	uint8_t& Gain() { return Value<uint8_t>(PropOffsets_ZoneInfo.Gain); }
	UTexture*& LensFlare() { return Value<UTexture*>(PropOffsets_ZoneInfo.LensFlare); }
	float& LensFlareOffset() { return Value<float>(PropOffsets_ZoneInfo.LensFlareOffset); }
	float& LensFlareScale() { return Value<float>(PropOffsets_ZoneInfo.LensFlareScale); }
	uint8_t& MasterGain() { return Value<uint8_t>(PropOffsets_ZoneInfo.MasterGain); }
	int& MaxCarcasses() { return Value<int>(PropOffsets_ZoneInfo.MaxCarcasses); }
	uint8_t& MaxLightCount() { return Value<uint8_t>(PropOffsets_ZoneInfo.MaxLightCount); }
	int& MaxLightingPolyCount() { return Value<int>(PropOffsets_ZoneInfo.MaxLightingPolyCount); }
	uint8_t& MinLightCount() { return Value<uint8_t>(PropOffsets_ZoneInfo.MinLightCount); }
	int& MinLightingPolyCount() { return Value<int>(PropOffsets_ZoneInfo.MinLightingPolyCount); }
	int& NumCarcasses() { return Value<int>(PropOffsets_ZoneInfo.NumCarcasses); }
	USkyZoneInfo*& SkyZone() { return Value<USkyZoneInfo*>(PropOffsets_ZoneInfo.SkyZone); }
	float& SpeedOfSound() { return Value<float>(PropOffsets_ZoneInfo.SpeedOfSound); }
	float& TexUPanSpeed() { return Value<float>(PropOffsets_ZoneInfo.TexUPanSpeed); }
	float& TexVPanSpeed() { return Value<float>(PropOffsets_ZoneInfo.TexVPanSpeed); }
	vec3& ViewFlash() { return Value<vec3>(PropOffsets_ZoneInfo.ViewFlash); }
	vec3& ViewFog() { return Value<vec3>(PropOffsets_ZoneInfo.ViewFog); }
	float& ZoneFluidFriction() { return Value<float>(PropOffsets_ZoneInfo.ZoneFluidFriction); }
	vec3& ZoneGravity() { return Value<vec3>(PropOffsets_ZoneInfo.ZoneGravity); }
	float& ZoneGroundFriction() { return Value<float>(PropOffsets_ZoneInfo.ZoneGroundFriction); }
	std::string& ZoneName() { return Value<std::string>(PropOffsets_ZoneInfo.ZoneName); }
	int& ZonePlayerCount() { return Value<int>(PropOffsets_ZoneInfo.ZonePlayerCount); }
	std::string& ZonePlayerEvent() { return Value<std::string>(PropOffsets_ZoneInfo.ZonePlayerEvent); }
	std::string& ZoneTag() { return Value<std::string>(PropOffsets_ZoneInfo.ZoneTag); }
	float& ZoneTerminalVelocity() { return Value<float>(PropOffsets_ZoneInfo.ZoneTerminalVelocity); }
	vec3& ZoneVelocity() { return Value<vec3>(PropOffsets_ZoneInfo.ZoneVelocity); }
	bool& bBounceVelocity() { return Value<bool>(PropOffsets_ZoneInfo.bBounceVelocity); }
	bool& bDestructive() { return Value<bool>(PropOffsets_ZoneInfo.bDestructive); }
	bool& bFogZone() { return Value<bool>(PropOffsets_ZoneInfo.bFogZone); }
	bool& bGravityZone() { return Value<bool>(PropOffsets_ZoneInfo.bGravityZone); }
	bool& bKillZone() { return Value<bool>(PropOffsets_ZoneInfo.bKillZone); }
	bool& bMoveProjectiles() { return Value<bool>(PropOffsets_ZoneInfo.bMoveProjectiles); }
	bool& bNeutralZone() { return Value<bool>(PropOffsets_ZoneInfo.bNeutralZone); }
	bool& bNoInventory() { return Value<bool>(PropOffsets_ZoneInfo.bNoInventory); }
	bool& bPainZone() { return Value<bool>(PropOffsets_ZoneInfo.bPainZone); }
	bool& bRaytraceReverb() { return Value<bool>(PropOffsets_ZoneInfo.bRaytraceReverb); }
	bool& bReverbZone() { return Value<bool>(PropOffsets_ZoneInfo.bReverbZone); }
	bool& bWaterZone() { return Value<bool>(PropOffsets_ZoneInfo.bWaterZone); }
	Ulocationid*& locationid() { return Value<Ulocationid*>(PropOffsets_ZoneInfo.locationid); }
};

class UnrealURL
{
public:
	UnrealURL() = default;
	UnrealURL(const UnrealURL& base, const std::string& url)
	{
		// To do: this also needs to be able to handle fully qualified URLs for network support

		*this = base;

		size_t pos = url.find('?');
		if (pos == std::string::npos)
		{
			Map = url;
		}
		else
		{
			Map = url.substr(0, pos);

			pos++;
			while (pos < url.size())
			{
				size_t endpos = url.find('?', pos);
				if (endpos == std::string::npos)
					endpos = url.size();
				AddOrReplaceOption(url.substr(pos, endpos - pos));
				pos = endpos + 1;
			}
		}
	}

	std::string Protocol = "unreal";
	std::string ProtocolDescription = "Unreal Protocol";
	std::string Name = "Player";
	std::string Map = "Index.unr";
	std::string Host;
	std::string Portal;
	std::string MapExt = "unr";
	std::string SaveExt = "usa";
	int Port = 7777;
	std::vector<std::string> Options;

	void AddOrReplaceOption(const std::string& newvalue)
	{
		size_t pos = newvalue.find('=');
		if (pos != std::string::npos)
		{
			std::string name = newvalue.substr(0, pos);
			for (char& c : name) c = std::tolower(c);
			for (std::string& option : Options)
			{
				if (option.size() >= name.size() + 1 && option[name.size()] == '=')
				{
					std::string key = option.substr(0, name.size());
					for (char& c : key) c = std::tolower(c);
					if (key == name)
					{
						option = newvalue;
						return;
					}
				}
			}
			Options.push_back(newvalue);
		}
		else
		{
			std::string name = newvalue;
			for (char& c : name) c = std::tolower(c);
			for (std::string& option : Options)
			{
				if (option.size() == name.size())
				{
					std::string key = option;
					for (char& c : key) c = std::tolower(c);
					if (key == name)
					{
						option = newvalue;
						return;
					}
				}
			}
			Options.push_back(newvalue);
		}
	}

	bool HasOption(const std::string& name) const
	{
		for (const std::string& option : Options)
		{
			if ((option.size() >= name.size() + 1 && option[name.size()] == '=') || option.size() == name.size())
			{
				std::string key = option.substr(0, name.size());
				for (char& c : key) c = std::tolower(c);
				if (key == name)
					return true;
			}
		}
		return false;
	}

	std::string GetOption(const std::string& name) const
	{
		for (const std::string& option : Options)
		{
			if (option.size() >= name.size() + 1 && option[name.size()] == '=')
			{
				std::string key = option.substr(0, name.size());
				for (char& c : key) c = std::tolower(c);
				if (key == name)
					return option.substr(name.size() + 1);
			}
		}
		return {};
	}

	std::string GetAddressURL() const
	{
		return Host + ":" + std::to_string(Port);
	}

	std::string GetOptions() const
	{
		std::string result;
		for (const std::string& option : Options)
		{
			result += "?";
			result += option;
		}
		return result;
	}

	std::string GetPortal() const
	{
		if (!Portal.empty())
			return "#" + Portal;
		else
			return std::string();
	}

	std::string ToString() const
	{
		std::string result;

		if (Protocol != "unreal")
		{
			result += Protocol;
			result += ":";
			if (!Host.empty())
				result += "//";
		}

		if (!Host.empty() || Port != 7777)
		{
			result += Host;
			result += ":";
			result += std::to_string(Port);
			result += "/";
		}

		result += Map;
		result += GetOptions();
		result += GetPortal();

		return result;
	}
};

class ULevelInfo : public UZoneInfo
{
public:
	using UZoneInfo::UZoneInfo;

	void UpdateActorZone() override;

	UnrealURL URL;

	int& AIProfile() { return Value<int>(PropOffsets_LevelInfo.AIProfile); }
	std::string& Author() { return Value<std::string>(PropOffsets_LevelInfo.Author); }
	float& AvgAITime() { return Value<float>(PropOffsets_LevelInfo.AvgAITime); }
	float& Brightness() { return Value<float>(PropOffsets_LevelInfo.Brightness); }
	uint8_t& CdTrack() { return Value<uint8_t>(PropOffsets_LevelInfo.CdTrack); }
	std::string& ComputerName() { return Value<std::string>(PropOffsets_LevelInfo.ComputerName); }
	int& Day() { return Value<int>(PropOffsets_LevelInfo.Day); }
	int& DayOfWeek() { return Value<int>(PropOffsets_LevelInfo.DayOfWeek); }
	UClass*& DefaultGameType() { return Value<UClass*>(PropOffsets_LevelInfo.DefaultGameType); }
	UTexture*& DefaultTexture() { return Value<UTexture*>(PropOffsets_LevelInfo.DefaultTexture); }
	std::string& EngineVersion() { return Value<std::string>(PropOffsets_LevelInfo.EngineVersion); }
	UGameInfo*& Game() { return Value<UGameInfo*>(PropOffsets_LevelInfo.Game); }
	int& Hour() { return Value<int>(PropOffsets_LevelInfo.Hour); }
	int& HubStackLevel() { return Value<int>(PropOffsets_LevelInfo.HubStackLevel); }
	std::string& IdealPlayerCount() { return Value<std::string>(PropOffsets_LevelInfo.IdealPlayerCount); }
	uint8_t& LevelAction() { return Value<uint8_t>(PropOffsets_LevelInfo.LevelAction); }
	std::string& LevelEnterText() { return Value<std::string>(PropOffsets_LevelInfo.LevelEnterText); }
	std::string& LocalizedPkg() { return Value<std::string>(PropOffsets_LevelInfo.LocalizedPkg); }
	int& Millisecond() { return Value<int>(PropOffsets_LevelInfo.Millisecond); }
	std::string& MinNetVersion() { return Value<std::string>(PropOffsets_LevelInfo.MinNetVersion); }
	int& Minute() { return Value<int>(PropOffsets_LevelInfo.Minute); }
	int& Month() { return Value<int>(PropOffsets_LevelInfo.Month); }
	UNavigationPoint*& NavigationPointList() { return Value<UNavigationPoint*>(PropOffsets_LevelInfo.NavigationPointList); }
	uint8_t& NetMode() { return Value<uint8_t>(PropOffsets_LevelInfo.NetMode); }
	float& NextSwitchCountdown() { return Value<float>(PropOffsets_LevelInfo.NextSwitchCountdown); }
	std::string& NextURL() { return Value<std::string>(PropOffsets_LevelInfo.NextURL); }
	std::string& Pauser() { return Value<std::string>(PropOffsets_LevelInfo.Pauser); }
	UPawn*& PawnList() { return Value<UPawn*>(PropOffsets_LevelInfo.PawnList); }
	float& PlayerDoppler() { return Value<float>(PropOffsets_LevelInfo.PlayerDoppler); }
	int& RecommendedEnemies() { return Value<int>(PropOffsets_LevelInfo.RecommendedEnemies); }
	int& RecommendedTeammates() { return Value<int>(PropOffsets_LevelInfo.RecommendedTeammates); }
	UTexture*& Screenshot() { return Value<UTexture*>(PropOffsets_LevelInfo.Screenshot); }
	int& Second() { return Value<int>(PropOffsets_LevelInfo.Second); }
	UMusic*& Song() { return Value<UMusic*>(PropOffsets_LevelInfo.Song); }
	uint8_t& SongSection() { return Value<uint8_t>(PropOffsets_LevelInfo.SongSection); }
	USpawnNotify*& SpawnNotify() { return Value<USpawnNotify*>(PropOffsets_LevelInfo.SpawnNotify); }
	ULevelSummary*& Summary() { return Value<ULevelSummary*>(PropOffsets_LevelInfo.Summary); }
	float& TimeDilation() { return Value<float>(PropOffsets_LevelInfo.TimeDilation); }
	float& TimeSeconds() { return Value<float>(PropOffsets_LevelInfo.TimeSeconds); }
	std::string& Title() { return Value<std::string>(PropOffsets_LevelInfo.Title); }
	std::string& VisibleGroups() { return Value<std::string>(PropOffsets_LevelInfo.VisibleGroups); }
	int& Year() { return Value<int>(PropOffsets_LevelInfo.Year); }
	bool& bAggressiveLOD() { return Value<bool>(PropOffsets_LevelInfo.bAggressiveLOD); }
	bool& bAllowFOV() { return Value<bool>(PropOffsets_LevelInfo.bAllowFOV); }
	bool& bBegunPlay() { return Value<bool>(PropOffsets_LevelInfo.bBegunPlay); }
	bool& bCheckWalkSurfaces() { return Value<bool>(PropOffsets_LevelInfo.bCheckWalkSurfaces); }
	bool& bDropDetail() { return Value<bool>(PropOffsets_LevelInfo.bDropDetail); }
	bool& bHighDetailMode() { return Value<bool>(PropOffsets_LevelInfo.bHighDetailMode); }
	bool& bHumansOnly() { return Value<bool>(PropOffsets_LevelInfo.bHumansOnly); }
	bool& bLonePlayer() { return Value<bool>(PropOffsets_LevelInfo.bLonePlayer); }
	bool& bLowRes() { return Value<bool>(PropOffsets_LevelInfo.bLowRes); }
	bool& bNeverPrecache() { return Value<bool>(PropOffsets_LevelInfo.bNeverPrecache); }
	bool& bNextItems() { return Value<bool>(PropOffsets_LevelInfo.bNextItems); }
	bool& bNoCheating() { return Value<bool>(PropOffsets_LevelInfo.bNoCheating); }
	bool& bPlayersOnly() { return Value<bool>(PropOffsets_LevelInfo.bPlayersOnly); }
	bool& bStartup() { return Value<bool>(PropOffsets_LevelInfo.bStartup); }
};

class UWarpZoneInfo : public UZoneInfo
{
public:
	using UZoneInfo::UZoneInfo;

	std::string& Destinations() { return Value<std::string>(PropOffsets_WarpZoneInfo.Destinations); }
	UWarpZoneInfo*& OtherSideActor() { return Value<UWarpZoneInfo*>(PropOffsets_WarpZoneInfo.OtherSideActor); }
	UObject*& OtherSideLevel() { return Value<UObject*>(PropOffsets_WarpZoneInfo.OtherSideLevel); }
	std::string& OtherSideURL() { return Value<std::string>(PropOffsets_WarpZoneInfo.OtherSideURL); }
	std::string& ThisTag() { return Value<std::string>(PropOffsets_WarpZoneInfo.ThisTag); }
	// Coords& WarpCoords() { return Value<Coords>(PropOffsets_WarpZoneInfo.WarpCoords); }
	bool& bNoTeleFrag() { return Value<bool>(PropOffsets_WarpZoneInfo.bNoTeleFrag); }
	int& iWarpZone() { return Value<int>(PropOffsets_WarpZoneInfo.iWarpZone); }
	int& numDestinations() { return Value<int>(PropOffsets_WarpZoneInfo.numDestinations); }
};

class USkyZoneInfo : public UZoneInfo
{
public:
	using UZoneInfo::UZoneInfo;
};

class UReplicationInfo : public UInfo
{
public:
	using UInfo::UInfo;
};

class UPlayerReplicationInfo : public UReplicationInfo
{
public:
	using UReplicationInfo::UReplicationInfo;

	float& Deaths() { return Value<float>(PropOffsets_PlayerReplicationInfo.Deaths); }
	UDecoration*& HasFlag() { return Value<UDecoration*>(PropOffsets_PlayerReplicationInfo.HasFlag); }
	std::string& OldName() { return Value<std::string>(PropOffsets_PlayerReplicationInfo.OldName); }
	uint8_t& PacketLoss() { return Value<uint8_t>(PropOffsets_PlayerReplicationInfo.PacketLoss); }
	int& Ping() { return Value<int>(PropOffsets_PlayerReplicationInfo.Ping); }
	int& PlayerID() { return Value<int>(PropOffsets_PlayerReplicationInfo.PlayerID); }
	Ulocationid*& PlayerLocation() { return Value<Ulocationid*>(PropOffsets_PlayerReplicationInfo.PlayerLocation); }
	std::string& PlayerName() { return Value<std::string>(PropOffsets_PlayerReplicationInfo.PlayerName); }
	UZoneInfo*& PlayerZone() { return Value<UZoneInfo*>(PropOffsets_PlayerReplicationInfo.PlayerZone); }
	float& Score() { return Value<float>(PropOffsets_PlayerReplicationInfo.Score); }
	int& StartTime() { return Value<int>(PropOffsets_PlayerReplicationInfo.StartTime); }
	UTexture*& TalkTexture() { return Value<UTexture*>(PropOffsets_PlayerReplicationInfo.TalkTexture); }
	uint8_t& Team() { return Value<uint8_t>(PropOffsets_PlayerReplicationInfo.Team); }
	int& TeamID() { return Value<int>(PropOffsets_PlayerReplicationInfo.TeamID); }
	std::string& TeamName() { return Value<std::string>(PropOffsets_PlayerReplicationInfo.TeamName); }
	int& TimeAcc() { return Value<int>(PropOffsets_PlayerReplicationInfo.TimeAcc); }
	UClass*& VoiceType() { return Value<UClass*>(PropOffsets_PlayerReplicationInfo.VoiceType); }
	bool& bAdmin() { return Value<bool>(PropOffsets_PlayerReplicationInfo.bAdmin); }
	bool& bFeigningDeath() { return Value<bool>(PropOffsets_PlayerReplicationInfo.bFeigningDeath); }
	bool& bIsABot() { return Value<bool>(PropOffsets_PlayerReplicationInfo.bIsABot); }
	bool& bIsFemale() { return Value<bool>(PropOffsets_PlayerReplicationInfo.bIsFemale); }
	bool& bIsSpectator() { return Value<bool>(PropOffsets_PlayerReplicationInfo.bIsSpectator); }
	bool& bWaitingPlayer() { return Value<bool>(PropOffsets_PlayerReplicationInfo.bWaitingPlayer); }
};

class UGameReplicationInfo : public UReplicationInfo
{
public:
	using UReplicationInfo::UReplicationInfo;

	std::string& AdminEmail() { return Value<std::string>(PropOffsets_GameReplicationInfo.AdminEmail); }
	std::string& AdminName() { return Value<std::string>(PropOffsets_GameReplicationInfo.AdminName); }
	int& ElapsedTime() { return Value<int>(PropOffsets_GameReplicationInfo.ElapsedTime); }
	std::string& GameClass() { return Value<std::string>(PropOffsets_GameReplicationInfo.GameClass); }
	std::string& GameEndedComments() { return Value<std::string>(PropOffsets_GameReplicationInfo.GameEndedComments); }
	std::string& GameName() { return Value<std::string>(PropOffsets_GameReplicationInfo.GameName); }
	std::string& MOTDLine1() { return Value<std::string>(PropOffsets_GameReplicationInfo.MOTDLine1); }
	std::string& MOTDLine2() { return Value<std::string>(PropOffsets_GameReplicationInfo.MOTDLine2); }
	std::string& MOTDLine3() { return Value<std::string>(PropOffsets_GameReplicationInfo.MOTDLine3); }
	std::string& MOTDLine4() { return Value<std::string>(PropOffsets_GameReplicationInfo.MOTDLine4); }
	int& NumPlayers() { return Value<int>(PropOffsets_GameReplicationInfo.NumPlayers); }
	UPlayerReplicationInfo*& PRIArray() { return Value<UPlayerReplicationInfo*>(PropOffsets_GameReplicationInfo.PRIArray); }
	int& Region() { return Value<int>(PropOffsets_GameReplicationInfo.Region); }
	int& RemainingMinute() { return Value<int>(PropOffsets_GameReplicationInfo.RemainingMinute); }
	int& RemainingTime() { return Value<int>(PropOffsets_GameReplicationInfo.RemainingTime); }
	float& SecondCount() { return Value<float>(PropOffsets_GameReplicationInfo.SecondCount); }
	std::string& ServerName() { return Value<std::string>(PropOffsets_GameReplicationInfo.ServerName); }
	std::string& ShortName() { return Value<std::string>(PropOffsets_GameReplicationInfo.ShortName); }
	int& SumFrags() { return Value<int>(PropOffsets_GameReplicationInfo.SumFrags); }
	float& UpdateTimer() { return Value<float>(PropOffsets_GameReplicationInfo.UpdateTimer); }
	bool& bClassicDeathMessages() { return Value<bool>(PropOffsets_GameReplicationInfo.bClassicDeathMessages); }
	bool& bStopCountDown() { return Value<bool>(PropOffsets_GameReplicationInfo.bStopCountDown); }
	bool& bTeamGame() { return Value<bool>(PropOffsets_GameReplicationInfo.bTeamGame); }
};

class UStatLog : public UInfo
{
public:
	using UInfo::UInfo;

	int& Context() { return Value<int>(PropOffsets_StatLog.Context); }
	std::string& DecoderRingURL() { return Value<std::string>(PropOffsets_StatLog.DecoderRingURL); }
	std::string& GameCreator() { return Value<std::string>(PropOffsets_StatLog.GameCreator); }
	std::string& GameCreatorURL() { return Value<std::string>(PropOffsets_StatLog.GameCreatorURL); }
	std::string& GameName() { return Value<std::string>(PropOffsets_StatLog.GameName); }
	std::string& LocalBatcherParams() { return Value<std::string>(PropOffsets_StatLog.LocalBatcherParams); }
	std::string& LocalBatcherURL() { return Value<std::string>(PropOffsets_StatLog.LocalBatcherURL); }
	std::string& LocalLogDir() { return Value<std::string>(PropOffsets_StatLog.LocalLogDir); }
	std::string& LocalStandard() { return Value<std::string>(PropOffsets_StatLog.LocalStandard); }
	std::string& LocalStatsURL() { return Value<std::string>(PropOffsets_StatLog.LocalStatsURL); }
	std::string& LogInfoURL() { return Value<std::string>(PropOffsets_StatLog.LogInfoURL); }
	std::string& LogVersion() { return Value<std::string>(PropOffsets_StatLog.LogVersion); }
	float& TimeStamp() { return Value<float>(PropOffsets_StatLog.TimeStamp); }
	std::string& WorldBatcherParams() { return Value<std::string>(PropOffsets_StatLog.WorldBatcherParams); }
	std::string& WorldBatcherURL() { return Value<std::string>(PropOffsets_StatLog.WorldBatcherURL); }
	std::string& WorldLogDir() { return Value<std::string>(PropOffsets_StatLog.WorldLogDir); }
	std::string& WorldStandard() { return Value<std::string>(PropOffsets_StatLog.WorldStandard); }
	std::string& WorldStatsURL() { return Value<std::string>(PropOffsets_StatLog.WorldStatsURL); }
	bool& bWorld() { return Value<bool>(PropOffsets_StatLog.bWorld); }
	bool& bWorldBatcherError() { return Value<bool>(PropOffsets_StatLog.bWorldBatcherError); }
};

class UStatLogFile : public UStatLog
{
public:
	using UStatLog::UStatLog;

	int& LogAr() { return Value<int>(PropOffsets_StatLogFile.LogAr); }
	std::string& StatLogFile() { return Value<std::string>(PropOffsets_StatLogFile.StatLogFile); }
	std::string& StatLogFinal() { return Value<std::string>(PropOffsets_StatLogFile.StatLogFinal); }
	bool& bWatermark() { return Value<bool>(PropOffsets_StatLogFile.bWatermark); }
};

class UBrush : public UActor
{
public:
	using UActor::UActor;

	Color& BrushColor() { return Value<Color>(PropOffsets_Brush.BrushColor); }
	uint8_t& CsgOper() { return Value<uint8_t>(PropOffsets_Brush.CsgOper); }
	// Scale& MainScale() { return Value<Scale>(PropOffsets_Brush.MainScale); }
	int& PolyFlags() { return Value<int>(PropOffsets_Brush.PolyFlags); }
	vec3& PostPivot() { return Value<vec3>(PropOffsets_Brush.PostPivot); }
	// Scale& PostScale() { return Value<Scale>(PropOffsets_Brush.PostScale); }
	// Scale& TempScale() { return Value<Scale>(PropOffsets_Brush.TempScale); }
	UObject*& UnusedLightMesh() { return Value<UObject*>(PropOffsets_Brush.UnusedLightMesh); }
	bool& bColored() { return Value<bool>(PropOffsets_Brush.bColored); }
};

class UMover : public UBrush
{
public:
	using UBrush::UBrush;

	vec3& BasePos() { return Value<vec3>(PropOffsets_Mover.BasePos); }
	Rotator& BaseRot() { return Value<Rotator>(PropOffsets_Mover.BaseRot); }
	uint8_t& BrushRaytraceKey() { return Value<uint8_t>(PropOffsets_Mover.BrushRaytraceKey); }
	std::string& BumpEvent() { return Value<std::string>(PropOffsets_Mover.BumpEvent); }
	uint8_t& BumpType() { return Value<uint8_t>(PropOffsets_Mover.BumpType); }
	int& ClientUpdate() { return Value<int>(PropOffsets_Mover.ClientUpdate); }
	USound*& ClosedSound() { return Value<USound*>(PropOffsets_Mover.ClosedSound); }
	USound*& ClosingSound() { return Value<USound*>(PropOffsets_Mover.ClosingSound); }
	float& DamageThreshold() { return Value<float>(PropOffsets_Mover.DamageThreshold); }
	float& DelayTime() { return Value<float>(PropOffsets_Mover.DelayTime); }
	int& EncroachDamage() { return Value<int>(PropOffsets_Mover.EncroachDamage); }
	UMover*& Follower() { return Value<UMover*>(PropOffsets_Mover.Follower); }
	uint8_t& KeyNum() { return Value<uint8_t>(PropOffsets_Mover.KeyNum); }
	vec3& KeyPos() { return Value<vec3>(PropOffsets_Mover.KeyPos); }
	Rotator& KeyRot() { return Value<Rotator>(PropOffsets_Mover.KeyRot); }
	UMover*& Leader() { return Value<UMover*>(PropOffsets_Mover.Leader); }
	USound*& MoveAmbientSound() { return Value<USound*>(PropOffsets_Mover.MoveAmbientSound); }
	float& MoveTime() { return Value<float>(PropOffsets_Mover.MoveTime); }
	uint8_t& MoverEncroachType() { return Value<uint8_t>(PropOffsets_Mover.MoverEncroachType); }
	uint8_t& MoverGlideType() { return Value<uint8_t>(PropOffsets_Mover.MoverGlideType); }
	uint8_t& NumKeys() { return Value<uint8_t>(PropOffsets_Mover.NumKeys); }
	vec3& OldPos() { return Value<vec3>(PropOffsets_Mover.OldPos); }
	vec3& OldPrePivot() { return Value<vec3>(PropOffsets_Mover.OldPrePivot); }
	Rotator& OldRot() { return Value<Rotator>(PropOffsets_Mover.OldRot); }
	USound*& OpenedSound() { return Value<USound*>(PropOffsets_Mover.OpenedSound); }
	USound*& OpeningSound() { return Value<USound*>(PropOffsets_Mover.OpeningSound); }
	float& OtherTime() { return Value<float>(PropOffsets_Mover.OtherTime); }
	std::string& PlayerBumpEvent() { return Value<std::string>(PropOffsets_Mover.PlayerBumpEvent); }
	uint8_t& PrevKeyNum() { return Value<uint8_t>(PropOffsets_Mover.PrevKeyNum); }
	vec3& RealPosition() { return Value<vec3>(PropOffsets_Mover.RealPosition); }
	Rotator& RealRotation() { return Value<Rotator>(PropOffsets_Mover.RealRotation); }
	UTrigger*& RecommendedTrigger() { return Value<UTrigger*>(PropOffsets_Mover.RecommendedTrigger); }
	std::string& ReturnGroup() { return Value<std::string>(PropOffsets_Mover.ReturnGroup); }
	vec3& SavedPos() { return Value<vec3>(PropOffsets_Mover.SavedPos); }
	Rotator& SavedRot() { return Value<Rotator>(PropOffsets_Mover.SavedRot); }
	UActor*& SavedTrigger() { return Value<UActor*>(PropOffsets_Mover.SavedTrigger); }
	vec3& SimInterpolate() { return Value<vec3>(PropOffsets_Mover.SimInterpolate); }
	vec3& SimOldPos() { return Value<vec3>(PropOffsets_Mover.SimOldPos); }
	int& SimOldRotPitch() { return Value<int>(PropOffsets_Mover.SimOldRotPitch); }
	int& SimOldRotRoll() { return Value<int>(PropOffsets_Mover.SimOldRotRoll); }
	int& SimOldRotYaw() { return Value<int>(PropOffsets_Mover.SimOldRotYaw); }
	float& StayOpenTime() { return Value<float>(PropOffsets_Mover.StayOpenTime); }
	UActor*& TriggerActor() { return Value<UActor*>(PropOffsets_Mover.TriggerActor); }
	UActor*& TriggerActor2() { return Value<UActor*>(PropOffsets_Mover.TriggerActor2); }
	UPawn*& WaitingPawn() { return Value<UPawn*>(PropOffsets_Mover.WaitingPawn); }
	uint8_t& WorldRaytraceKey() { return Value<uint8_t>(PropOffsets_Mover.WorldRaytraceKey); }
	bool& bClientPause() { return Value<bool>(PropOffsets_Mover.bClientPause); }
	bool& bDamageTriggered() { return Value<bool>(PropOffsets_Mover.bDamageTriggered); }
	bool& bDelaying() { return Value<bool>(PropOffsets_Mover.bDelaying); }
	bool& bDynamicLightMover() { return Value<bool>(PropOffsets_Mover.bDynamicLightMover); }
	bool& bOpening() { return Value<bool>(PropOffsets_Mover.bOpening); }
	bool& bPlayerOnly() { return Value<bool>(PropOffsets_Mover.bPlayerOnly); }
	bool& bSlave() { return Value<bool>(PropOffsets_Mover.bSlave); }
	bool& bTriggerOnceOnly() { return Value<bool>(PropOffsets_Mover.bTriggerOnceOnly); }
	bool& bUseTriggered() { return Value<bool>(PropOffsets_Mover.bUseTriggered); }
	UNavigationPoint*& myMarker() { return Value<UNavigationPoint*>(PropOffsets_Mover.myMarker); }
	int& numTriggerEvents() { return Value<int>(PropOffsets_Mover.numTriggerEvents); }
};

class UPawn : public UActor
{
public:
	using UActor::UActor;

	void Tick(float elapsed, bool tickedFlag) override;

	void InitActorZone() override;
	void UpdateActorZone() override;

	float& AccelRate() { return Value<float>(PropOffsets_Pawn.AccelRate); }
	float& AirControl() { return Value<float>(PropOffsets_Pawn.AirControl); }
	float& AirSpeed() { return Value<float>(PropOffsets_Pawn.AirSpeed); }
	std::string& AlarmTag() { return Value<std::string>(PropOffsets_Pawn.AlarmTag); }
	float& Alertness() { return Value<float>(PropOffsets_Pawn.Alertness); }
	uint8_t& AttitudeToPlayer() { return Value<uint8_t>(PropOffsets_Pawn.AttitudeToPlayer); }
	float& AvgPhysicsTime() { return Value<float>(PropOffsets_Pawn.AvgPhysicsTime); }
	float& BaseEyeHeight() { return Value<float>(PropOffsets_Pawn.BaseEyeHeight); }
	float& CombatStyle() { return Value<float>(PropOffsets_Pawn.CombatStyle); }
	float& DamageScaling() { return Value<float>(PropOffsets_Pawn.DamageScaling); }
	float& DesiredSpeed() { return Value<float>(PropOffsets_Pawn.DesiredSpeed); }
	vec3& Destination() { return Value<vec3>(PropOffsets_Pawn.Destination); }
	USound*& Die() { return Value<USound*>(PropOffsets_Pawn.Die); }
	int& DieCount() { return Value<int>(PropOffsets_Pawn.DieCount); }
	UClass*& DropWhenKilled() { return Value<UClass*>(PropOffsets_Pawn.DropWhenKilled); }
	UPawn*& Enemy() { return Value<UPawn*>(PropOffsets_Pawn.Enemy); }
	float& EyeHeight() { return Value<float>(PropOffsets_Pawn.EyeHeight); }
	UActor*& FaceTarget() { return Value<UActor*>(PropOffsets_Pawn.FaceTarget); }
	vec3& Floor() { return Value<vec3>(PropOffsets_Pawn.Floor); }
	vec3& Focus() { return Value<vec3>(PropOffsets_Pawn.Focus); }
	PointRegion& FootRegion() { return Value<PointRegion>(PropOffsets_Pawn.FootRegion); }
	float& FovAngle() { return Value<float>(PropOffsets_Pawn.FovAngle); }
	float& GroundSpeed() { return Value<float>(PropOffsets_Pawn.GroundSpeed); }
	PointRegion& HeadRegion() { return Value<PointRegion>(PropOffsets_Pawn.HeadRegion); }
	int& Health() { return Value<int>(PropOffsets_Pawn.Health); }
	float& HearingThreshold() { return Value<float>(PropOffsets_Pawn.HearingThreshold); }
	USound*& HitSound1() { return Value<USound*>(PropOffsets_Pawn.HitSound1); }
	USound*& HitSound2() { return Value<USound*>(PropOffsets_Pawn.HitSound2); }
	uint8_t& Intelligence() { return Value<uint8_t>(PropOffsets_Pawn.Intelligence); }
	int& ItemCount() { return Value<int>(PropOffsets_Pawn.ItemCount); }
	float& JumpZ() { return Value<float>(PropOffsets_Pawn.JumpZ); }
	int& KillCount() { return Value<int>(PropOffsets_Pawn.KillCount); }
	USound*& Land() { return Value<USound*>(PropOffsets_Pawn.Land); }
	float& LastPainSound() { return Value<float>(PropOffsets_Pawn.LastPainSound); }
	vec3& LastSeeingPos() { return Value<vec3>(PropOffsets_Pawn.LastSeeingPos); }
	vec3& LastSeenPos() { return Value<vec3>(PropOffsets_Pawn.LastSeenPos); }
	float& LastSeenTime() { return Value<float>(PropOffsets_Pawn.LastSeenTime); }
	float& MaxDesiredSpeed() { return Value<float>(PropOffsets_Pawn.MaxDesiredSpeed); }
	float& MaxStepHeight() { return Value<float>(PropOffsets_Pawn.MaxStepHeight); }
	float& MeleeRange() { return Value<float>(PropOffsets_Pawn.MeleeRange); }
	std::string& MenuName() { return Value<std::string>(PropOffsets_Pawn.MenuName); }
	float& MinHitWall() { return Value<float>(PropOffsets_Pawn.MinHitWall); }
	UActor*& MoveTarget() { return Value<UActor*>(PropOffsets_Pawn.MoveTarget); }
	float& MoveTimer() { return Value<float>(PropOffsets_Pawn.MoveTimer); }
	std::string& NameArticle() { return Value<std::string>(PropOffsets_Pawn.NameArticle); }
	std::string& NextLabel() { return Value<std::string>(PropOffsets_Pawn.NextLabel); }
	std::string& NextState() { return Value<std::string>(PropOffsets_Pawn.NextState); }
	float& OldMessageTime() { return Value<float>(PropOffsets_Pawn.OldMessageTime); }
	float& OrthoZoom() { return Value<float>(PropOffsets_Pawn.OrthoZoom); }
	float& PainTime() { return Value<float>(PropOffsets_Pawn.PainTime); }
	UWeapon*& PendingWeapon() { return Value<UWeapon*>(PropOffsets_Pawn.PendingWeapon); }
	float& PeripheralVision() { return Value<float>(PropOffsets_Pawn.PeripheralVision); }
	std::string& PlayerReStartState() { return Value<std::string>(PropOffsets_Pawn.PlayerReStartState); }
	UPlayerReplicationInfo*& PlayerReplicationInfo() { return Value<UPlayerReplicationInfo*>(PropOffsets_Pawn.PlayerReplicationInfo); }
	UClass*& PlayerReplicationInfoClass() { return Value<UClass*>(PropOffsets_Pawn.PlayerReplicationInfoClass); }
	float& ReducedDamagePct() { return Value<float>(PropOffsets_Pawn.ReducedDamagePct); }
	std::string& ReducedDamageType() { return Value<std::string>(PropOffsets_Pawn.ReducedDamageType); }
	UNavigationPoint*& RouteCache() { return Value<UNavigationPoint*>(PropOffsets_Pawn.RouteCache); }
	int& SecretCount() { return Value<int>(PropOffsets_Pawn.SecretCount); }
	UInventory*& SelectedItem() { return Value<UInventory*>(PropOffsets_Pawn.SelectedItem); }
	std::string& SelectionMesh() { return Value<std::string>(PropOffsets_Pawn.SelectionMesh); }
	UDecal*& Shadow() { return Value<UDecal*>(PropOffsets_Pawn.Shadow); }
	std::string& SharedAlarmTag() { return Value<std::string>(PropOffsets_Pawn.SharedAlarmTag); }
	float& SightCounter() { return Value<float>(PropOffsets_Pawn.SightCounter); }
	float& SightRadius() { return Value<float>(PropOffsets_Pawn.SightRadius); }
	float& Skill() { return Value<float>(PropOffsets_Pawn.Skill); }
	float& SoundDampening() { return Value<float>(PropOffsets_Pawn.SoundDampening); }
	UActor*& SpecialGoal() { return Value<UActor*>(PropOffsets_Pawn.SpecialGoal); }
	std::string& SpecialMesh() { return Value<std::string>(PropOffsets_Pawn.SpecialMesh); }
	float& SpecialPause() { return Value<float>(PropOffsets_Pawn.SpecialPause); }
	float& SpeechTime() { return Value<float>(PropOffsets_Pawn.SpeechTime); }
	float& SplashTime() { return Value<float>(PropOffsets_Pawn.SplashTime); }
	int& Spree() { return Value<int>(PropOffsets_Pawn.Spree); }
	float& Stimulus() { return Value<float>(PropOffsets_Pawn.Stimulus); }
	float& UnderWaterTime() { return Value<float>(PropOffsets_Pawn.UnderWaterTime); }
	Rotator& ViewRotation() { return Value<Rotator>(PropOffsets_Pawn.ViewRotation); }
	uint8_t& Visibility() { return Value<uint8_t>(PropOffsets_Pawn.Visibility); }
	uint8_t& VoicePitch() { return Value<uint8_t>(PropOffsets_Pawn.VoicePitch); }
	std::string& VoiceType() { return Value<std::string>(PropOffsets_Pawn.VoiceType); }
	vec3& WalkBob() { return Value<vec3>(PropOffsets_Pawn.WalkBob); }
	float& WaterSpeed() { return Value<float>(PropOffsets_Pawn.WaterSpeed); }
	USound*& WaterStep() { return Value<USound*>(PropOffsets_Pawn.WaterStep); }
	UWeapon*& Weapon() { return Value<UWeapon*>(PropOffsets_Pawn.Weapon); }
	bool& bAdvancedTactics() { return Value<bool>(PropOffsets_Pawn.bAdvancedTactics); }
	uint8_t& bAltFire() { return Value<uint8_t>(PropOffsets_Pawn.bAltFire); }
	bool& bAutoActivate() { return Value<bool>(PropOffsets_Pawn.bAutoActivate); }
	bool& bAvoidLedges() { return Value<bool>(PropOffsets_Pawn.bAvoidLedges); }
	bool& bBehindView() { return Value<bool>(PropOffsets_Pawn.bBehindView); }
	bool& bCanDoSpecial() { return Value<bool>(PropOffsets_Pawn.bCanDoSpecial); }
	bool& bCanFly() { return Value<bool>(PropOffsets_Pawn.bCanFly); }
	bool& bCanJump() { return Value<bool>(PropOffsets_Pawn.bCanJump); }
	bool& bCanOpenDoors() { return Value<bool>(PropOffsets_Pawn.bCanOpenDoors); }
	bool& bCanStrafe() { return Value<bool>(PropOffsets_Pawn.bCanStrafe); }
	bool& bCanSwim() { return Value<bool>(PropOffsets_Pawn.bCanSwim); }
	bool& bCanWalk() { return Value<bool>(PropOffsets_Pawn.bCanWalk); }
	bool& bCountJumps() { return Value<bool>(PropOffsets_Pawn.bCountJumps); }
	bool& bDrowning() { return Value<bool>(PropOffsets_Pawn.bDrowning); }
	uint8_t& bDuck() { return Value<uint8_t>(PropOffsets_Pawn.bDuck); }
	uint8_t& bExtra0() { return Value<uint8_t>(PropOffsets_Pawn.bExtra0); }
	uint8_t& bExtra1() { return Value<uint8_t>(PropOffsets_Pawn.bExtra1); }
	uint8_t& bExtra2() { return Value<uint8_t>(PropOffsets_Pawn.bExtra2); }
	uint8_t& bExtra3() { return Value<uint8_t>(PropOffsets_Pawn.bExtra3); }
	uint8_t& bFire() { return Value<uint8_t>(PropOffsets_Pawn.bFire); }
	bool& bFixedStart() { return Value<bool>(PropOffsets_Pawn.bFixedStart); }
	uint8_t& bFreeLook() { return Value<uint8_t>(PropOffsets_Pawn.bFreeLook); }
	bool& bFromWall() { return Value<bool>(PropOffsets_Pawn.bFromWall); }
	bool& bHitSlopedWall() { return Value<bool>(PropOffsets_Pawn.bHitSlopedWall); }
	bool& bHunting() { return Value<bool>(PropOffsets_Pawn.bHunting); }
	bool& bIsFemale() { return Value<bool>(PropOffsets_Pawn.bIsFemale); }
	bool& bIsHuman() { return Value<bool>(PropOffsets_Pawn.bIsHuman); }
	bool& bIsMultiSkinned() { return Value<bool>(PropOffsets_Pawn.bIsMultiSkinned); }
	bool& bIsPlayer() { return Value<bool>(PropOffsets_Pawn.bIsPlayer); }
	bool& bIsWalking() { return Value<bool>(PropOffsets_Pawn.bIsWalking); }
	bool& bJumpOffPawn() { return Value<bool>(PropOffsets_Pawn.bJumpOffPawn); }
	bool& bJustLanded() { return Value<bool>(PropOffsets_Pawn.bJustLanded); }
	bool& bLOSflag() { return Value<bool>(PropOffsets_Pawn.bLOSflag); }
	uint8_t& bLook() { return Value<uint8_t>(PropOffsets_Pawn.bLook); }
	bool& bNeverSwitchOnPickup() { return Value<bool>(PropOffsets_Pawn.bNeverSwitchOnPickup); }
	bool& bReducedSpeed() { return Value<bool>(PropOffsets_Pawn.bReducedSpeed); }
	uint8_t& bRun() { return Value<uint8_t>(PropOffsets_Pawn.bRun); }
	bool& bShootSpecial() { return Value<bool>(PropOffsets_Pawn.bShootSpecial); }
	uint8_t& bSnapLevel() { return Value<uint8_t>(PropOffsets_Pawn.bSnapLevel); }
	bool& bStopAtLedges() { return Value<bool>(PropOffsets_Pawn.bStopAtLedges); }
	uint8_t& bStrafe() { return Value<uint8_t>(PropOffsets_Pawn.bStrafe); }
	bool& bUpAndOut() { return Value<bool>(PropOffsets_Pawn.bUpAndOut); }
	bool& bUpdatingDisplay() { return Value<bool>(PropOffsets_Pawn.bUpdatingDisplay); }
	bool& bViewTarget() { return Value<bool>(PropOffsets_Pawn.bViewTarget); }
	bool& bWarping() { return Value<bool>(PropOffsets_Pawn.bWarping); }
	uint8_t& bZoom() { return Value<uint8_t>(PropOffsets_Pawn.bZoom); }
	UDecoration*& carriedDecoration() { return Value<UDecoration*>(PropOffsets_Pawn.carriedDecoration); }
	UNavigationPoint*& home() { return Value<UNavigationPoint*>(PropOffsets_Pawn.home); }
	UPawn*& nextPawn() { return Value<UPawn*>(PropOffsets_Pawn.nextPawn); }
	float& noise1loudness() { return Value<float>(PropOffsets_Pawn.noise1loudness); }
	UPawn*& noise1other() { return Value<UPawn*>(PropOffsets_Pawn.noise1other); }
	vec3& noise1spot() { return Value<vec3>(PropOffsets_Pawn.noise1spot); }
	float& noise1time() { return Value<float>(PropOffsets_Pawn.noise1time); }
	float& noise2loudness() { return Value<float>(PropOffsets_Pawn.noise2loudness); }
	UPawn*& noise2other() { return Value<UPawn*>(PropOffsets_Pawn.noise2other); }
	vec3& noise2spot() { return Value<vec3>(PropOffsets_Pawn.noise2spot); }
	float& noise2time() { return Value<float>(PropOffsets_Pawn.noise2time); }
};

class UScout : public UPawn
{
public:
	using UPawn::UPawn;
};

class UPlayerPawn : public UPawn
{
public:
	using UPawn::UPawn;

	void Tick(float elapsed, bool tickedFlag) override;

	float& AppliedBob() { return Value<float>(PropOffsets_PlayerPawn.AppliedBob); }
	float& Bob() { return Value<float>(PropOffsets_PlayerPawn.Bob); }
	float& BorrowedMouseX() { return Value<float>(PropOffsets_PlayerPawn.BorrowedMouseX); }
	float& BorrowedMouseY() { return Value<float>(PropOffsets_PlayerPawn.BorrowedMouseY); }
	UClass*& CarcassType() { return Value<UClass*>(PropOffsets_PlayerPawn.CarcassType); }
	uint8_t& CdTrack() { return Value<uint8_t>(PropOffsets_PlayerPawn.CdTrack); }
	float& ClientUpdateTime() { return Value<float>(PropOffsets_PlayerPawn.ClientUpdateTime); }
	vec3& ConstantGlowFog() { return Value<vec3>(PropOffsets_PlayerPawn.ConstantGlowFog); }
	float& ConstantGlowScale() { return Value<float>(PropOffsets_PlayerPawn.ConstantGlowScale); }
	float& CurrentTimeStamp() { return Value<float>(PropOffsets_PlayerPawn.CurrentTimeStamp); }
	float& DefaultFOV() { return Value<float>(PropOffsets_PlayerPawn.DefaultFOV); }
	std::string& DelayedCommand() { return Value<std::string>(PropOffsets_PlayerPawn.DelayedCommand); }
	int& DemoViewPitch() { return Value<int>(PropOffsets_PlayerPawn.DemoViewPitch); }
	int& DemoViewYaw() { return Value<int>(PropOffsets_PlayerPawn.DemoViewYaw); }
	float& DesiredFOV() { return Value<float>(PropOffsets_PlayerPawn.DesiredFOV); }
	vec3& DesiredFlashFog() { return Value<vec3>(PropOffsets_PlayerPawn.DesiredFlashFog); }
	float& DesiredFlashScale() { return Value<float>(PropOffsets_PlayerPawn.DesiredFlashScale); }
	float& DodgeClickTime() { return Value<float>(PropOffsets_PlayerPawn.DodgeClickTime); }
	float& DodgeClickTimer() { return Value<float>(PropOffsets_PlayerPawn.DodgeClickTimer); }
	std::string& FailedView() { return Value<std::string>(PropOffsets_PlayerPawn.FailedView); }
	vec3& FlashFog() { return Value<vec3>(PropOffsets_PlayerPawn.FlashFog); }
	vec3& FlashScale() { return Value<vec3>(PropOffsets_PlayerPawn.FlashScale); }
	USavedMove*& FreeMoves() { return Value<USavedMove*>(PropOffsets_PlayerPawn.FreeMoves); }
	UGameReplicationInfo*& GameReplicationInfo() { return Value<UGameReplicationInfo*>(PropOffsets_PlayerPawn.GameReplicationInfo); }
	UClass*& HUDType() { return Value<UClass*>(PropOffsets_PlayerPawn.HUDType); }
	float& Handedness() { return Value<float>(PropOffsets_PlayerPawn.Handedness); }
	float& InstantFlash() { return Value<float>(PropOffsets_PlayerPawn.InstantFlash); }
	vec3& InstantFog() { return Value<vec3>(PropOffsets_PlayerPawn.InstantFog); }
	USound*& JumpSound() { return Value<USound*>(PropOffsets_PlayerPawn.JumpSound); }
	float& LandBob() { return Value<float>(PropOffsets_PlayerPawn.LandBob); }
	float& LastMessageWindow() { return Value<float>(PropOffsets_PlayerPawn.LastMessageWindow); }
	float& LastPlaySound() { return Value<float>(PropOffsets_PlayerPawn.LastPlaySound); }
	float& LastUpdateTime() { return Value<float>(PropOffsets_PlayerPawn.LastUpdateTime); }
	float& MaxTimeMargin() { return Value<float>(PropOffsets_PlayerPawn.MaxTimeMargin); }
	int& Misc1() { return Value<int>(PropOffsets_PlayerPawn.Misc1); }
	int& Misc2() { return Value<int>(PropOffsets_PlayerPawn.Misc2); }
	float& MouseSensitivity() { return Value<float>(PropOffsets_PlayerPawn.MouseSensitivity); }
	float& MouseSmoothThreshold() { return Value<float>(PropOffsets_PlayerPawn.MouseSmoothThreshold); }
	float& MouseZeroTime() { return Value<float>(PropOffsets_PlayerPawn.MouseZeroTime); }
	float& MyAutoAim() { return Value<float>(PropOffsets_PlayerPawn.MyAutoAim); }
	std::string& NoPauseMessage() { return Value<std::string>(PropOffsets_PlayerPawn.NoPauseMessage); }
	std::string& OwnCamera() { return Value<std::string>(PropOffsets_PlayerPawn.OwnCamera); }
	std::string& Password() { return Value<std::string>(PropOffsets_PlayerPawn.Password); }
	USavedMove*& PendingMove() { return Value<USavedMove*>(PropOffsets_PlayerPawn.PendingMove); }
	UPlayer*& Player() { return Value<UPlayer*>(PropOffsets_PlayerPawn.Player); }
	Color& ProgressColor() { return Value<Color>(PropOffsets_PlayerPawn.ProgressColor); }
	std::string& ProgressMessage() { return Value<std::string>(PropOffsets_PlayerPawn.ProgressMessage); }
	float& ProgressTimeOut() { return Value<float>(PropOffsets_PlayerPawn.ProgressTimeOut); }
	std::string& QuickSaveString() { return Value<std::string>(PropOffsets_PlayerPawn.QuickSaveString); }
	bool& ReceivedSecretChecksum() { return Value<bool>(PropOffsets_PlayerPawn.ReceivedSecretChecksum); }
	int& RendMap() { return Value<int>(PropOffsets_PlayerPawn.RendMap); }
	USavedMove*& SavedMoves() { return Value<USavedMove*>(PropOffsets_PlayerPawn.SavedMoves); }
	// UScoreBoard*& Scoring() { return Value<UScoreBoard*>(PropOffsets_PlayerPawn.Scoring); }
	UClass*& ScoringType() { return Value<UClass*>(PropOffsets_PlayerPawn.ScoringType); }
	float& ServerTimeStamp() { return Value<float>(PropOffsets_PlayerPawn.ServerTimeStamp); }
	int& ShowFlags() { return Value<int>(PropOffsets_PlayerPawn.ShowFlags); }
	float& SmoothMouseX() { return Value<float>(PropOffsets_PlayerPawn.SmoothMouseX); }
	float& SmoothMouseY() { return Value<float>(PropOffsets_PlayerPawn.SmoothMouseY); }
	UMusic*& Song() { return Value<UMusic*>(PropOffsets_PlayerPawn.Song); }
	uint8_t& SongSection() { return Value<uint8_t>(PropOffsets_PlayerPawn.SongSection); }
	UClass*& SpecialMenu() { return Value<UClass*>(PropOffsets_PlayerPawn.SpecialMenu); }
	float& TargetEyeHeight() { return Value<float>(PropOffsets_PlayerPawn.TargetEyeHeight); }
	Rotator& TargetViewRotation() { return Value<Rotator>(PropOffsets_PlayerPawn.TargetViewRotation); }
	vec3& TargetWeaponViewOffset() { return Value<vec3>(PropOffsets_PlayerPawn.TargetWeaponViewOffset); }
	float& TimeMargin() { return Value<float>(PropOffsets_PlayerPawn.TimeMargin); }
	uint8_t& Transition() { return Value<uint8_t>(PropOffsets_PlayerPawn.Transition); }
	UActor*& ViewTarget() { return Value<UActor*>(PropOffsets_PlayerPawn.ViewTarget); }
	std::string& ViewingFrom() { return Value<std::string>(PropOffsets_PlayerPawn.ViewingFrom); }
	std::string& WeaponPriority() { return Value<std::string>(PropOffsets_PlayerPawn.WeaponPriority); }
	float& ZoomLevel() { return Value<float>(PropOffsets_PlayerPawn.ZoomLevel); }
	float& aBaseX() { return Value<float>(PropOffsets_PlayerPawn.aBaseX); }
	float& aBaseY() { return Value<float>(PropOffsets_PlayerPawn.aBaseY); }
	float& aBaseZ() { return Value<float>(PropOffsets_PlayerPawn.aBaseZ); }
	float& aExtra0() { return Value<float>(PropOffsets_PlayerPawn.aExtra0); }
	float& aExtra1() { return Value<float>(PropOffsets_PlayerPawn.aExtra1); }
	float& aExtra2() { return Value<float>(PropOffsets_PlayerPawn.aExtra2); }
	float& aExtra3() { return Value<float>(PropOffsets_PlayerPawn.aExtra3); }
	float& aExtra4() { return Value<float>(PropOffsets_PlayerPawn.aExtra4); }
	float& aForward() { return Value<float>(PropOffsets_PlayerPawn.aForward); }
	float& aLookUp() { return Value<float>(PropOffsets_PlayerPawn.aLookUp); }
	float& aMouseX() { return Value<float>(PropOffsets_PlayerPawn.aMouseX); }
	float& aMouseY() { return Value<float>(PropOffsets_PlayerPawn.aMouseY); }
	float& aStrafe() { return Value<float>(PropOffsets_PlayerPawn.aStrafe); }
	float& aTurn() { return Value<float>(PropOffsets_PlayerPawn.aTurn); }
	float& aUp() { return Value<float>(PropOffsets_PlayerPawn.aUp); }
	bool& bAdmin() { return Value<bool>(PropOffsets_PlayerPawn.bAdmin); }
	bool& bAlwaysMouseLook() { return Value<bool>(PropOffsets_PlayerPawn.bAlwaysMouseLook); }
	bool& bAnimTransition() { return Value<bool>(PropOffsets_PlayerPawn.bAnimTransition); }
	bool& bBadConnectionAlert() { return Value<bool>(PropOffsets_PlayerPawn.bBadConnectionAlert); }
	bool& bCenterView() { return Value<bool>(PropOffsets_PlayerPawn.bCenterView); }
	bool& bCheatsEnabled() { return Value<bool>(PropOffsets_PlayerPawn.bCheatsEnabled); }
	bool& bDelayedCommand() { return Value<bool>(PropOffsets_PlayerPawn.bDelayedCommand); }
	bool& bEdgeBack() { return Value<bool>(PropOffsets_PlayerPawn.bEdgeBack); }
	bool& bEdgeForward() { return Value<bool>(PropOffsets_PlayerPawn.bEdgeForward); }
	bool& bEdgeLeft() { return Value<bool>(PropOffsets_PlayerPawn.bEdgeLeft); }
	bool& bEdgeRight() { return Value<bool>(PropOffsets_PlayerPawn.bEdgeRight); }
	bool& bFixedCamera() { return Value<bool>(PropOffsets_PlayerPawn.bFixedCamera); }
	bool& bFrozen() { return Value<bool>(PropOffsets_PlayerPawn.bFrozen); }
	bool& bInvertMouse() { return Value<bool>(PropOffsets_PlayerPawn.bInvertMouse); }
	bool& bIsCrouching() { return Value<bool>(PropOffsets_PlayerPawn.bIsCrouching); }
	bool& bIsTurning() { return Value<bool>(PropOffsets_PlayerPawn.bIsTurning); }
	bool& bIsTyping() { return Value<bool>(PropOffsets_PlayerPawn.bIsTyping); }
	bool& bJumpStatus() { return Value<bool>(PropOffsets_PlayerPawn.bJumpStatus); }
	bool& bJustAltFired() { return Value<bool>(PropOffsets_PlayerPawn.bJustAltFired); }
	bool& bJustFired() { return Value<bool>(PropOffsets_PlayerPawn.bJustFired); }
	bool& bKeyboardLook() { return Value<bool>(PropOffsets_PlayerPawn.bKeyboardLook); }
	bool& bLookUpStairs() { return Value<bool>(PropOffsets_PlayerPawn.bLookUpStairs); }
	bool& bMaxMouseSmoothing() { return Value<bool>(PropOffsets_PlayerPawn.bMaxMouseSmoothing); }
	bool& bMessageBeep() { return Value<bool>(PropOffsets_PlayerPawn.bMessageBeep); }
	bool& bMouseZeroed() { return Value<bool>(PropOffsets_PlayerPawn.bMouseZeroed); }
	bool& bNeverAutoSwitch() { return Value<bool>(PropOffsets_PlayerPawn.bNeverAutoSwitch); }
	bool& bNoFlash() { return Value<bool>(PropOffsets_PlayerPawn.bNoFlash); }
	bool& bNoVoices() { return Value<bool>(PropOffsets_PlayerPawn.bNoVoices); }
	bool& bPressedJump() { return Value<bool>(PropOffsets_PlayerPawn.bPressedJump); }
	bool& bReadyToPlay() { return Value<bool>(PropOffsets_PlayerPawn.bReadyToPlay); }
	bool& bReducedVis() { return Value<bool>(PropOffsets_PlayerPawn.bReducedVis); }
	bool& bRising() { return Value<bool>(PropOffsets_PlayerPawn.bRising); }
	bool& bShakeDir() { return Value<bool>(PropOffsets_PlayerPawn.bShakeDir); }
	bool& bShowMenu() { return Value<bool>(PropOffsets_PlayerPawn.bShowMenu); }
	bool& bShowScores() { return Value<bool>(PropOffsets_PlayerPawn.bShowScores); }
	bool& bSinglePlayer() { return Value<bool>(PropOffsets_PlayerPawn.bSinglePlayer); }
	bool& bSnapToLevel() { return Value<bool>(PropOffsets_PlayerPawn.bSnapToLevel); }
	bool& bSpecialMenu() { return Value<bool>(PropOffsets_PlayerPawn.bSpecialMenu); }
	bool& bUpdatePosition() { return Value<bool>(PropOffsets_PlayerPawn.bUpdatePosition); }
	bool& bUpdating() { return Value<bool>(PropOffsets_PlayerPawn.bUpdating); }
	bool& bWasBack() { return Value<bool>(PropOffsets_PlayerPawn.bWasBack); }
	bool& bWasForward() { return Value<bool>(PropOffsets_PlayerPawn.bWasForward); }
	bool& bWasLeft() { return Value<bool>(PropOffsets_PlayerPawn.bWasLeft); }
	bool& bWasRight() { return Value<bool>(PropOffsets_PlayerPawn.bWasRight); }
	bool& bWokeUp() { return Value<bool>(PropOffsets_PlayerPawn.bWokeUp); }
	bool& bZooming() { return Value<bool>(PropOffsets_PlayerPawn.bZooming); }
	float& bobtime() { return Value<float>(PropOffsets_PlayerPawn.bobtime); }
	float& maxshake() { return Value<float>(PropOffsets_PlayerPawn.maxshake); }
	UHUD*& myHUD() { return Value<UHUD*>(PropOffsets_PlayerPawn.myHUD); }
	bool& ngSecretSet() { return Value<bool>(PropOffsets_PlayerPawn.ngSecretSet); }
	std::string& ngWorldSecret() { return Value<std::string>(PropOffsets_PlayerPawn.ngWorldSecret); }
	int& shakemag() { return Value<int>(PropOffsets_PlayerPawn.shakemag); }
	float& shaketimer() { return Value<float>(PropOffsets_PlayerPawn.shaketimer); }
	float& shakevert() { return Value<float>(PropOffsets_PlayerPawn.shakevert); }
	float& verttimer() { return Value<float>(PropOffsets_PlayerPawn.verttimer); }
};

class UCamera : public UPlayerPawn
{
public:
	using UPlayerPawn::UPlayerPawn;
};
