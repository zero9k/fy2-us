
inherit ROOM;

void create()
{
	set("short", "街道");
	set("long", @LONG
用青石板铺成的道路，打扫得干乾净净。几个小童在街道上互相
追逐玩耍。街道两旁是红砖砌成的房屋，两位老者悠闲地坐在家门前
吸烟聊天。
LONG
	);
	set("exits", ([ 
		"north" : __DIR__"xzroad1",
		"south" : __DIR__"xzroad3",
		"east" : __DIR__"xzhouse1",
		"west" : __DIR__"xzstore1",
	]));
	set("outdoors", "wudang");
        set("objects", ([
                __DIR__"npc/xiaotong" : 2,
                __DIR__"npc/oldman" : 2,
        ]) );
	setup();
replace_program(ROOM);

}
