
inherit ROOM;

void create()
{
	set("short", "小镇");
	set("long", @LONG
这里是武当山下唯一的一个小镇。小镇不是很大，但却很繁华。
因其在武当山脚，镇中既使几岁小童，也会几招太极拳。过了这个小
镇，就是武当派的起源地—武当山。
LONG
	);
	set("exits", ([ 
		"south" : __DIR__"xzroad1",
		"north" : __DIR__"bwuroad2",
	]));
	set("outdoors", "wudang");
	setup();
	replace_program(ROOM);
}
