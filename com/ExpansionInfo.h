#pragma once
#include "log_def.h"


enum class FeatureFlags
{
	None = 0x00000000,
	T2A = 0x00000001,
	UOR = 0x00000002,
	UOTD = 0x00000004,
	LBR = 0x00000008,
	AOS = 0x00000010,
	SixthCharacterSlot = 0x00000020,
	SE = 0x00000040,
	ML = 0x00000080,
	EigthAge = 0x00000100,
	NinthAge = 0x00000200, /* Crystal/Shadow Custom House Tiles */
	TenthAge = 0x00000400,
	IncreasedStorage = 0x00000800, /* Increased Housing/Bank Storage */
	SeventhCharacterSlot = 0x00001000,
	RoleplayFaces = 0x00002000,
	TrialAccount = 0x00004000,
	LiveAccount = 0x00008000,
	SA = 0x00010000,
	HS = 0x00020000,
	Gothic = 0x00040000,
	Rustic = 0x00080000,
	Jungle = 0x00100000,
	Shadowguard = 0x00200000,
	TOL = 0x00400000,
	EJ = 0x00800000, // TODO: Verify value

	ExpansionNone = None,
	ExpansionT2A = T2A,
	ExpansionUOR = ExpansionT2A | UOR,
	ExpansionUOTD = ExpansionUOR | UOTD,
	ExpansionLBR = ExpansionUOTD | LBR,
	ExpansionAOS = ExpansionLBR | AOS | LiveAccount,
	ExpansionSE = ExpansionAOS | SE,
	ExpansionML = ExpansionSE | ML | NinthAge,
	ExpansionSA = ExpansionML | SA | Gothic | Rustic,
	ExpansionHS = ExpansionSA | HS,
	ExpansionTOL = ExpansionHS | TOL | Jungle | Shadowguard,
	ExpansionEJ = ExpansionTOL | EJ
};


enum class CharacterListFlags
{
	None = 0x00000000,
	Unk1 = 0x00000001,
	OverwriteConfigButton = 0x00000002,
	OneCharacterSlot = 0x00000004,
	ContextMenus = 0x00000008,
	SlotLimit = 0x00000010,
	AOS = 0x00000020,
	SixthCharacterSlot = 0x00000040,
	SE = 0x00000080,
	ML = 0x00000100,
	Unk2 = 0x00000200,
	UO3DClientType = 0x00000400,
	KR = 0x00000600, // uo:kr support flags
	Unk3 = 0x00000800,
	SeventhCharacterSlot = 0x00001000,
	Unk4 = 0x00002000,
	NewMovementSystem = 0x00004000,
	NewFeluccaAreas = 0x00008000,

	ExpansionNone = ContextMenus, //
	ExpansionT2A = ContextMenus, //
	ExpansionUOR = ContextMenus, // None
	ExpansionUOTD = ContextMenus, //
	ExpansionLBR = ContextMenus, //
	ExpansionAOS = ContextMenus | AOS,
	ExpansionSE = ExpansionAOS | SE,
	ExpansionML = ExpansionSE | ML,
	ExpansionSA = ExpansionML,
	ExpansionHS = ExpansionSA,
	ExpansionTOL = ExpansionHS,
	ExpansionEJ = ExpansionTOL
};

