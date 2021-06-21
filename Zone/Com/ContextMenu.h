#pragma once
#include "InsEvent.h"
#include "Geometry.h"


class ContextMenuEntry;
class Actor;
class ContextMenu;
class IEntity;


/// <summary>
///     Represents a single entry of a <see cref="ContextMenu">context menu</see>.
///     <seealso cref="ContextMenu" />
/// </summary>
class ContextMenuEntry 
{
public:
	bool IsDisposed = false;

		/// <summary>
		///     Gets or sets additional <see cref="CMEFlags">flags</see> used in client communication.
		/// </summary>
	CMEFlags Flags = CMEFlags::None;

		/// <summary>
		///     Gets or sets the <see cref="ContextMenu" /> that owns this entry.
		/// </summary>
	 weak_ptr<ContextMenu>  Owner;

		/// <summary>
		///     Gets or sets the localization number containing the name of this entry.
		/// </summary>
	int Number = 0;

		/// <summary>
		///     Gets or sets the maximum range at which this entry may be used, in tiles. A value of -1 signifies no maximum range.
		/// </summary>
	int Range = 0;

		/// <summary>
		///     Gets or sets the color for this entry. Format is A1-R5-G5-B5.
		/// </summary>
	int Color = 0;

		/// <summary>
		///     Gets or sets whether this entry is enabled. When false, the entry will appear in a gray hue and <see cref="OnClick" /> will never be invoked.
		/// </summary>
	bool Enabled = false;

		/// <summary>
		///     Gets a value indicating if non local use of this entry is permitted.
		/// </summary>
	virtual bool NonLocalUse(){ return false; }

		/// <summary>
		///     Instantiates a new ContextMenuEntry with a given <see cref="Number">localization number</see> (
		///     <paramref
		///         name="number" />
		///     ). No <see cref="Range">maximum range</see> is used.
		/// </summary>
		/// <param name="number">
		///     The localization number containing the name of this entry.
		///     <seealso cref="Number" />
		/// </param>
	ContextMenuEntry(int number);

	/// <summary>
	///     Instantiates a new ContextMenuEntry with a given <see cref="Number">localization number</see> (
	///     <paramref
	///         name="number" />
	///     ) and <see cref="Range">maximum range</see> (<paramref name="range" />).
	/// </summary>
	/// <param name="number">
	///     The localization number containing the name of this entry.
	///     <seealso cref="Number" />
	/// </param>
	/// <param name="range">
	///     The maximum range at which this entry can be used.
	///     <seealso cref="Range" />
	/// </param>
	ContextMenuEntry(int number, int range);

	~ContextMenuEntry(){Dispose();}

	/// <summary>
	///     Overridable. Virtual event invoked when the entry is clicked.
	/// </summary>
	virtual void OnClick(){ }

	void Dispose();

	virtual void OnDispose(){ }
};

using SContextMenuEntry = shared_ptr<ContextMenuEntry>;
/// <summary>
///     Represents the state of an active context menu. This includes who opened the menu, the menu's focus object, and a list of
///     <see
///         cref="ContextMenuEntry">
///         entries
///     </see>
///     that the menu is composed of.
///     <seealso cref="ContextMenuEntry" />
/// </summary>
class ContextMenu : public WeakPtr<ContextMenu>
{
public:
	bool IsDisposed = false;

		/// <summary>
		///     Gets the <see cref="Mobile" /> who opened this ContextMenu.
		/// </summary>
	Actor &From;

		/// <summary>
		///     Gets an object of the <see cref="Mobile" /> or <see cref="Item" /> for which this ContextMenu is on.
		/// </summary>
		IEntity &Target;

		/// <summary>
		///     Gets the list of <see cref="ContextMenuEntry">entries</see> contained in this ContextMenu.
		/// </summary>
		vector<SContextMenuEntry> Entries;

		/// <summary>
		///     Instantiates a new ContextMenu instance.
		/// </summary>
		/// <param name="from">
		///     The <see cref="Mobile" /> who opened this ContextMenu.
		///     <seealso cref="From" />
		/// </param>
		/// <param name="target">
		///     The <see cref="Mobile" /> or <see cref="Item" /> for which this ContextMenu is on.
		///     <seealso cref="Target" />
		/// </param>
		ContextMenu(Actor &from, IEntity &target);

	~ContextMenu()
	{
		Dispose();
	}

	/// <summary>
	///     Returns true if this ContextMenu requires packet version 2.
	/// </summary>
	bool RequiresNewPacket();

	void Dispose()
	{
#if 0

		if (IsDisposed)
		{
			return;
		}

		IsDisposed = true;

		if (Entries != null)
		{
			foreach(var e in Entries.Where(e = > e != null))
			{
				e.Dispose();
			}

			Entries = null;
		}

		if (From != null)
		{
			if (From.ContextMenu == this)
			{
				From.ContextMenu = null;
			}

			From = null;
		}

		Target = null;

#endif
	}

#if 0
	static bool Display(Mobile m, IEntity target)
	{

		if (m == null || target == null || m.Map != target.Map || !m.CanSee(target))
		{
			return false;
		}

		if (target is Mobile && !Utility.InUpdateRange(m, target.Location))
		{
			return false;
		}

		if (target is Item && !Utility.InUpdateRange(m, ((Item)target).GetWorldLocation()))
		{
			return false;
		}

		if (!m.CheckContextMenuDisplay(target))
		{
			return false;
		}

		var c = new ContextMenu(m, target);

		if (c.Entries.Length <= 0)
		{
			return false;
		}

		if (target is Item)
		{
			var root = ((Item)target).RootParent;

			if (root is Mobile && root != m && ((Mobile)root).AccessLevel >= m.AccessLevel)
			{
				foreach(var e in c.Entries.Where(e = > !e.NonLocalUse))
				{
					e.Enabled = false;
				}
			}
		}

		m.ContextMenu = c;

		return true;
	}

	/// <summary>
	/// Returns the proper index of Enhanced Client Context Menu when sent from the icon on 
	/// the vendors status bar. Only known are Bank, Bulk Order Info and Bribe
	/// </summary>
	/// <param name="index">pre-described index sent by client. Must be 0x64 or higher</param>
	/// <returns>actual index of pre-desribed index from client</returns>
	int GetIndexEC(int index)
	{
		int number = index;

		switch (index)
		{
		case 0x0078:
			number = 3006105;
			break;   // Bank
		case 0x0193:
			number = 3006152;
			break;   // Bulk Order Info
		case 0x01A3:
			number = 1152294;
			break;   // Bribe
		case 0x032A:
			number = 3000197;
			break;   // Add Party Member
		case 0x032B:
			number = 3000198;
			break;   // Remove Party Member
		case 0x012D:
			number = 3006130;
			break;   // Tame
		case 0x082:
			number = 3006107;
			break;    // Command: Guard
		case 0x083:
			number = 3006108;
			break;    // Command: Follow
		case 0x086:
			number = 3006111;
			break;    // Command: Kill
		case 0x087:
			number = 3006114;
			break;    // Command: Stay
		case 0x089:
			number = 3006112;
			break;    // Command: Stop
		case 0x0140:
			number = 1113797;
			break;   // Enable PVP Warning TODO: Not Enabled
		case 0x025A:
			number = 3006205;
			break;   // Release Co-Ownership TODO: Not Enabled
		case 0x025C:
			number = 3006207;
			break;   // Leave House
		case 0x0196:
			number = 3006156;
			break;   // Quest Conversation
		case 0x0194:
			number = 3006154;
			break;   // View Quest Log
		case 0x0195:
			number = 3006155;
			break;   // Cancel Quest
		case 0x0321:
			number = 3006169;
			break;   // Toggle Quest Item
		case 0x01A0:
			number = 1114299;
			break;   // Open Item Insurance Menu
		case 0x01A2:
			number = 3006201;
			break;   // Toggle Item Insurance
		case 0x0396:
			number = 1115022;
			break;   // Open Titles Menu
		case 0x0393:
			number = 1049594;
			break;   // Loyalty Rating
		case 0x0134:
			number = 3006157;
			break;   // Cancel Protection
		case 0x03F2:
			number = 1152531;
			break;   // Void Pool
		case 0x03F5:
			number = 1154112;
			break;   // Allow Trades
		case 0x03F6:
			number = 1154113;
			break;   // Refuse Trades
		case 0x0334:
			number = 3006168;
			break;   // Siege Bless Item
		}

		if (index >= 0x64)
		{
			for (int i = 0; i < Entries.Length; i++)
			{
				if (Entries[i].Number == number)
				{
					return i;
				}
			}
		}

		return index;
	}

#endif
};