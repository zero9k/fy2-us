
inherit ROOM;

void create()
{
        set("short", "神水宫分舵");
        set("long", @LONG
这里是神水宫密秘分舵之一，这里防卫不很严，但一般人也休想
踏上一步。
LONG
        );
        set("exits", ([ 
  "north" : __DIR__"bottom2",
]));
        set("objects", ([
                "/d/shenshui/npc/master" : 1,
		"/d/shenshui/npc/thousand_hand" : 1,
       ]) );

        setup();
}
