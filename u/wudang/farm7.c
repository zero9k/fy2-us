
inherit ROOM;

void create()
{
	set("short", "ׯ�ڵ�");
	set("long", @LONG
һ�������͵�������а��˸ߵ���˶������������罭����
���㣬��������֮����ӿ�Ĳ��Σ��Ĵ�Ʈҡ�����뵽�����е�����,
������Ȼ���¡� 
LONG
	);
	set("exits", ([
		"north" : __DIR__"farm3",
		"south" : __DIR__"farm5",
		"east" : __DIR__"farm9",
		"west" : __DIR__"farm3",
	]));
	set("objects", ([
		__DIR__"npc/bird" : 2,
	]));
	set("outdoors", "wudang");
	setup();
replace_program(ROOM);

}