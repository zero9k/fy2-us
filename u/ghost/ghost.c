
inherit ROOM;

void create()
{
	set("short", "幽灵山庄");
	set("long", @LONG
这是一个死人的世界。放眼四望，一片空蒙，什么都看不见。左
面有一间灰白色的小木屋，在这迷雾般的白云里，一定要很注意才看
得到。
LONG
	);
	set("exits", ([
                "north" : __DIR__"house",
                "west" : __DIR__"bridge",
                "east" : __DIR__"groad1",
	]));
	setup();
        replace_program(ROOM);
}
