#include "ContextMenu.h"
#include "ActorMgr.h"


ContextMenuEntry::ContextMenuEntry(int number)
	:ContextMenuEntry(number, -1)
{ }

ContextMenuEntry::ContextMenuEntry(int number, int range)
{
	if (number <= 0x7FFF) // Legacy code support
	{
		Number = 3000000 + number;
	}
	else
	{
		Number = number;
	}

	Range = range;
	Enabled = true;
	Color = 0xFFFF;
}

void ContextMenuEntry::Dispose()
{
	if (IsDisposed)
	{
		return;
	}

	IsDisposed = true;

	OnDispose();

	if (shared_ptr<ContextMenu> p = Owner.lock())
	{
		for (SContextMenuEntry &v :p->Entries)
		{
			if (v.get() == this)
			{
				v.reset();
			}
		}
	}

	Owner.reset();
}

ContextMenu::ContextMenu(Actor &from, IEntity &target)
	:From(from)
	,Target(target)
{

	if (Actor *actor = dynamic_cast<Actor *>(&target))
	{
		actor->GetContextMenuEntries(from, Entries);
	}
	else if (Item *item = dynamic_cast<Item *>(&target))
	{
		item->GetContextMenuEntries(from, Entries);
	}
	else
	{
		L_ERROR("unknow IEntity");
	}

	for (SContextMenuEntry &v : Entries)
	{
		if (v != nullptr)
		{
			v->Owner = *this;
		}
	}
}

bool ContextMenu::RequiresNewPacket()
{
	for (SContextMenuEntry &t : Entries)
	{
		if (t == nullptr)
		{
			continue;
		}
		if (t->Number < 3000000 || t->Number > 3032767)
		{
		}
		else
		{
			return false;
		}
	}
	return true;
}
