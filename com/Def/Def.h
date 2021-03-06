/*
	公共定义 以及 静态配置 
*/
#pragma once


//c#适配
#define byte uint8_t

using TimeSpan = uint32;
namespace
{
	//svr group id
	const uint16 CENTER_GROUP_ID = 10; 
	const uint16 ZONE_GROUP_ID = 1;  //zone svr id = [ZONE_GROUP_ID,MAX_ZONE_GROUP_ID] 
	const uint16 MAX_ZONE_GROUP_ID = 9;

	const uint32 SAVE_INTERVAL_SEC = 60 * 1;//save db interval 
	const uint32 MAX_CHAR_NUM_IN_ACC = 7; //CHAR NUM IN ACC
	const uint32 MAX_CHAR_NAME = 30;

}

enum class CMEFlags
{
	None = 0x00,
	Disabled = 0x01,
	Arrow = 0x02,
	Highlighted = 0x04,
	Colored = 0x20
};

enum class LootType : byte
{
	/// <summary>
	///     Stealable. Lootable.
	/// </summary>
	Regular = 0,

	/// <summary>
	///     Unstealable. Unlootable, unless owned by a murderer.
	/// </summary>
	Newbied = 1,

	/// <summary>
	///     Unstealable. Unlootable, always.
	/// </summary>
	Blessed = 2,

	/// <summary>
	///     Stealable. Lootable, always.
	/// </summary>
	Cursed = 3
};

enum class Notoriety
{
	Innocent = 1,
	Ally = 2,
	CanBeAttacked = 3,
	Criminal = 4,
	Enemy = 5,
	Murderer = 6,
	Invulnerable = 7,
};
enum class HueColor
{
	Normal = 0x3B2,
	YELLOW = 0x35,
	Red1 = 0x22,
	Red2 = 0x20,
	RedDark = 0x484,
	Write = 0x482,
	Blue1 = 0x59

};
enum class MessageType
{
	Regular = 0x00,
	System = 0x01,
	Emote = 0x02,
	Label = 0x06,
	Focus = 0x07,
	Whisper = 0x08,
	Yell = 0x09,
	Spell = 0x0A,

	Guild = 0x0D,
	Alliance = 0x0E,
	Command = 0x0F,

	Encoded = 0xC0
};

enum class AccessLevel
{
	Player,
	VIP,
	Counselor,
	Decorator,
	Spawner,
	GameMaster,
	Seer,
	Administrator,
	Developer,
	CoOwner,
	Owner
};

enum class StatLockType : uint8_t
{
	Up,
	Down,
	Locked
};
enum class SkillLock : uint8_t
{
	Up = 0,
	Down = 1,
	Locked = 2
};

enum class StatType
{
	Str = 1,
	Dex = 2,
	Int = 4,
	All = 7
};

enum class MapId
{
	Felucca=0,													
	Trammel	  ,//Trammel新世界,安全，资源少	
	Ilshenar  ,								
	Malas	  ,								
	Tokuno	  ,								
	TerMur	  ,								
	Internal  = 0x7F,
};

//((int)Direction & 0x1) == 0x1;//true indicate diagonals. right,left,down,up
//(((int) Direction - 1) & 0x7)  逆时针 偏移一个方向
//(((int) Direction + 1) & 0x7) 表示顺时针 偏移一个方向
//[CustomEnum(new[] {"North", "Right", "East", "Down", "South", "Left", "West", "Up"})]
enum class Direction : uint8_t
{
	North = 0x0,
	Right = 0x1,
	East = 0x2,
	Down = 0x3,
	South = 0x4,
	Left = 0x5,
	West = 0x6,
	Up = 0x7,

	Mask = 0x7,
	Running = 0x80,
	ValueMask = 0x87
};
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

//一种对应一个ItemBase 派生类.
//注意：新物品往后加，不然需要清库
enum class ItemType
{
	Base=0, //普通物，没什么特别属性
	Container=1,
	Weapon=2,
	Equip=3,
	ItemTool =4,
};
//所有 ItemType,其他代码会自动定义构造器
#define ALL_ITEM_TYPE_NAME\
	ITEM_TYPE_NAME(Container)\
	ITEM_TYPE_NAME(Weapon)\
	ITEM_TYPE_NAME(Equip)\
	ITEM_TYPE_NAME(ItemTool)\

enum class ItemQuality
{
	Low,
	Normal,
	Exceptional,
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

/// <summary>
  ///     Enumeration of item layer values.
  /// </summary>
enum class Layer : uint8
{
	/// <summary>
	///     Invalid layer.
	/// </summary>
	Invalid = 0x00,

	/// <summary>
	///     First valid layer. Equivalent to <c>Layer.OneHanded</c>.
	/// </summary>
	FirstValid = 0x01,

	/// <summary>
	///     One handed weapon.
	/// </summary>
	OneHanded = 0x01,

	/// <summary>
	///     Two handed weapon or shield.
	/// </summary>
	TwoHanded = 0x02,

	/// <summary>
	///     Shoes.
	/// </summary>
	Shoes = 0x03,

	/// <summary>
	///     Pants.
	/// </summary>
	Pants = 0x04,

	/// <summary>
	///     Shirts.
	/// </summary>
	Shirt = 0x05,

	/// <summary>
	///     Helmets, hats, and masks.
	/// </summary>
	Helm = 0x06,

	/// <summary>
	///     Gloves.
	/// </summary>
	Gloves = 0x07,

	/// <summary>
	///     Rings.
	/// </summary>
	Ring = 0x08,

	/// <summary>
	///     Talismans.
	/// </summary>
	Talisman = 0x09,

	/// <summary>
	///     Gorgets and necklaces.
	/// </summary>
	Neck = 0x0A,

	/// <summary>
	///     Hair.
	/// </summary>
	Hair = 0x0B,

	/// <summary>
	///     Half aprons.
	/// </summary>
	Waist = 0x0C,

	/// <summary>
	///     Torso, inner layer.
	/// </summary>
	InnerTorso = 0x0D,

	/// <summary>
	///     Bracelets.
	/// </summary>
	Bracelet = 0x0E,

	/// <summary>
	///     Face.
	/// </summary>
	Face = 0x0F,

	/// <summary>
	///     Beards and mustaches.
	/// </summary>
	FacialHair = 0x10,

	/// <summary>
	///     Torso, outer layer.
	/// </summary>
	MiddleTorso = 0x11,

	/// <summary>
	///     Earings.
	/// </summary>
	Earrings = 0x12,

	/// <summary>
	///     Arms and sleeves.
	/// </summary>
	Arms = 0x13,

	/// <summary>
	///     Cloaks.
	/// </summary>
	Cloak = 0x14,

	/// <summary>
	///     Backpacks.
	/// </summary>
	Backpack = 0x15, //背包物品本身 穿戴的 layer，不是背包里面物品的layer

	/// <summary>
	///     Torso, outer layer.
	/// </summary>
	OuterTorso = 0x16,

	/// <summary>
	///     Leggings, outer layer.
	/// </summary>
	OuterLegs = 0x17,

	/// <summary>
	///     Leggings, inner layer.
	/// </summary>
	InnerLegs = 0x18,

	/// <summary>
	///     Last valid non-internal layer. Equivalent to <c>Layer.InnerLegs</c>.
	/// </summary>
	LastUserValid = 0x18,

	/// <summary>
	///     Mount item layer.
	/// </summary>
	Mount = 0x19,

	/// <summary>
	///     Vendor 'buy pack' layer.
	/// </summary>
	ShopBuy = 0x1A,

	/// <summary>
	///     Vendor 'resale pack' layer.
	/// </summary>
	ShopResale = 0x1B,

	/// <summary>
	///     Vendor 'sell pack' layer.
	/// </summary>
	ShopSell = 0x1C,

	/// <summary>
	///     Bank box layer.
	/// </summary>
	Bank = 0x1D,

	/// <summary>
	/// Unused, using this layer makes you invisible to other players. Strange.
	/// </summary>
	/// 
	Reserved_1 = 0x1E,

	/// <summary>
	///     Secure Trade Layer
	/// </summary>
	SecureTrade = 0x1F,
	Max,
};



#undef byte 