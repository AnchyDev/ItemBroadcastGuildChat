#ifndef MODULE_ITEM_BROADCAST_GUILD_CHAT_H
#define MODULE_ITEM_BROADCAST_GUILD_CHAT_H

#include "ScriptMgr.h"

enum ItemBroadcastGuildChatConstants
{
    LANG_GUILD_REPORT_ITEM = 35410
};

class ItemBroadcastGuildChatPlayerScript : public PlayerScript
{
public:
    ItemBroadcastGuildChatPlayerScript() : PlayerScript("ItemBroadcastGuildChatPlayerScript") { }

private:
    std::string GetItemLink(Player* /*player*/, Item* /*item*/);
    void BroadcastItemToGuild(Player* /*player*/, Item* /*item*/);
    void OnStoreNewItem(Player* /*player*/, Item* /*item*/, uint32 /*count*/) override;
};

#endif // MODULE_ITEM_BROADCAST_GUILD_CHAT_H
