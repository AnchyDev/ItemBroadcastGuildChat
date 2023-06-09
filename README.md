# Item Broadcast Guild Chat
This module broadcasts items you receive to the guild chat if it has the flag `ITEM_FLAG_REPORT_TO_GUILD_CHAT`.

![Item Broadcast](https://cdn.discordapp.com/attachments/814444289181351968/1111087334100844594/image.png)

## Install
- Clone the module into the modules folder.
- Re-run cmake.
- Recompile the core.
- Enable the module in the module config.
- Use Keira to add the `ITEM_FLAG_REPORT_TO_GUILD_CHAT` flag to an item.
- Be in a guild.
- Loot the item and observe the broadcast to guild.

## Example Queries
### Flag all mounts
#### Add Flags
```sql
SET @ITEM_FLAG_REPORT_TO_GUILD_CHAT := 1073741824;
UPDATE item_template SET item_template.Flags = (item_template.Flags + @ITEM_FLAG_REPORT_TO_GUILD_CHAT) WHERE item_template.class = 15 AND item_template.subclass = 5 AND (item_template.Flags & @ITEM_FLAG_REPORT_TO_GUILD_CHAT) = 0;
```
#### Remove Flags
```sql
SET @ITEM_FLAG_REPORT_TO_GUILD_CHAT := 1073741824;
UPDATE item_template SET item_template.Flags = (item_template.Flags - @ITEM_FLAG_REPORT_TO_GUILD_CHAT) WHERE item_template.class = 15 AND item_template.subclass = 5 AND (item_template.Flags & @ITEM_FLAG_REPORT_TO_GUILD_CHAT) = @ITEM_FLAG_REPORT_TO_GUILD_CHAT;
```

## Contact
If you would like to help out with the mod or just need help there is a [Discord Server](https://discord.gg/xdVPGcpJ8C) you can join.