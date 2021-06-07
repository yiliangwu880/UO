/*
	代码公共配置
*/
#pragma once

namespace
{
	//svr group id
	const uint16 CENTER_GROUP_ID = 10; 
	const uint16 ZONE_GROUP_ID = 1;  //zone svr id = [ZONE_GROUP_ID,MAX_ZONE_GROUP_ID] 
	const uint16 MAX_ZONE_GROUP_ID = 9;

	const uint32 SAVE_INTERVAL_SEC = 60 * 1;//save db interval 
	const uint32 MAX_CHAR_NUM_IN_ACC = 2; //CHAR NUM IN ACC
	const uint32 MAX_CHAR_NAME = 30;
}

enum class ResistanceType
{
	Physical = 0,
	Fire,
	Cold,
	Poison,
	Energy,
	Max
};

enum class EntityType
{
	None, 
	Item,//物品等，actor以外的东西
	Player,
	Npc,
	Monster,
	Max,
};

enum class SkillName
{
	Alchemy = 0,
	Anatomy = 1,
	AnimalLore = 2,
	ItemID = 3,
	ArmsLore = 4,
	Parry = 5,
	Begging = 6,
	Blacksmith = 7,
	Fletching = 8,
	Peacemaking = 9,
	Camping = 10,
	Carpentry = 11,
	Cartography = 12,
	Cooking = 13,
	DetectHidden = 14,
	Discordance = 15,
	EvalInt = 16,
	Healing = 17,
	Fishing = 18,
	Forensics = 19,
	Herding = 20,
	Hiding = 21,
	Provocation = 22,
	Inscribe = 23,
	Lockpicking = 24,
	Magery = 25,
	MagicResist = 26,
	Tactics = 27,
	Snooping = 28,
	Musicianship = 29,
	Poisoning = 30,
	Archery = 31,
	SpiritSpeak = 32,
	Stealing = 33,
	Tailoring = 34,
	AnimalTaming = 35,
	TasteID = 36,
	Tinkering = 37,
	Tracking = 38,
	Veterinary = 39,
	Swords = 40,
	Macing = 41,
	Fencing = 42,
	Wrestling = 43,
	Lumberjacking = 44,
	Mining = 45,
	Meditation = 46,
	Stealth = 47,
	RemoveTrap = 48,
	Necromancy = 49,
	Focus = 50,
	Chivalry = 51,
	Bushido = 52,
	Ninjitsu = 53,
	Spellweaving = 54,
	Mysticism = 55,
	Imbuing = 56,
	Throwing = 57,
	Max
};