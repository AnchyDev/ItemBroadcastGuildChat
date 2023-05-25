#include "ItemBroadcastGuildChat.h"

#include "Chat.h"
#include "Config.h"
#include "Guild.h"
#include "Player.h"

std::string ItemBroadcastGuildChatPlayerScript::GetItemLink(Player* player, Item* item)
{
    auto itemProto = item->GetTemplate();

    // Retrieve the locale name.
    int localeIndex = player->GetSession()->GetSessionDbLocaleIndex();
    if (localeIndex >= 0)
    {
        uint8 ulocaleIndex = uint8(localeIndex);
        if (ItemLocale const* il = sObjectMgr->GetItemLocale(itemProto->ItemId))
        {
            // Set locale name, or default name if locale = 0.
            std::string name = (il->Name.size() > ulocaleIndex && !il->Name[ulocaleIndex].empty()) ? il->Name[ulocaleIndex] : itemProto->Name1;

            if (!name.empty())
            {
                std::ostringstream oss;

                // Build item link.
                oss << "|c" << std::hex << ItemQualityColors[itemProto->Quality] << std::dec << "|Hitem:" << itemProto->ItemId;

                oss << ":";
                auto enchantId = item->GetEnchantmentId(PERM_ENCHANTMENT_SLOT);
                if (enchantId)
                {
                    oss << enchantId;
                }

                oss << ":::::";
                auto randProp = item->GetItemRandomPropertyId();
                if (randProp != 0)
                {
                    oss << randProp;
                }
                oss << "::";
                oss << player->GetLevel();
                oss << "|h[";
                oss << name;
                oss << "]|h|r";

                return oss.str();
            }
        }
    }

    return "";
}

void ItemBroadcastGuildChatPlayerScript::BroadcastItemToGuild(Player* player, Item* item)
{
    if (!player || !item)
    {
        return;
    }

    auto itemProto = item->GetTemplate();
    auto guild = player->GetGuild();

    if (!guild)
    {
        return;
    }

    auto itemLink = GetItemLink(player, item);

    // Failed to get hyperlink/locale.
    if (itemLink.empty())
    {
        return;
    }

    auto handler = ChatHandler(player->GetSession());

    // Fetch guild broadcast string locale.
    auto msg = handler.PGetParseString(LANG_GUILD_REPORT_ITEM, player->GetName(), player->GetName(), itemLink);

    WorldPacket data;
    handler.BuildChatPacket(data, CHAT_MSG_GUILD_ACHIEVEMENT, LANG_UNIVERSAL, nullptr, nullptr, msg);

    guild->BroadcastPacket(&data);
}

void ItemBroadcastGuildChatPlayerScript::OnStoreNewItem(Player* player, Item* item, uint32 /*count*/)
{
    if (!sConfigMgr->GetOption<bool>("ItemBroadcastGuildChat.Enable", false))
    {
        return;
    }

    // Transmit item to guild chat if it has the appropriate flag.
    if (player->GetGuild() && item->GetTemplate()->Flags & ITEM_FLAG_REPORT_TO_GUILD_CHAT)
    {
        BroadcastItemToGuild(player, item);
    }
}

void SC_AddItemBroadcastGuildChatScripts()
{
    new ItemBroadcastGuildChatPlayerScript();
}
