#pragma once

enum class CraftResource
{
	None = 0,
	Iron = 1,
	DullCopper,
	ShadowIron,
	Copper,
	Bronze,
	Gold,
	Agapite,
	Verite,
	Valorite,

	RegularLeather = 101,
	SpinedLeather,
	HornedLeather,
	BarbedLeather,

	RedScales = 201,
	YellowScales,
	BlackScales,
	GreenScales,
	WhiteScales,
	BlueScales,

	RegularWood = 301,
	OakWood,
	AshWood,
	YewWood,
	Heartwood,
	Bloodwood,
	Frostwood
};

enum class CraftResourceType
{
	None,
	Metal,
	Leather,
	Scales,
	Wood
};