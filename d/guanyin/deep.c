// Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.
inherit ROOM;
void create()
{
        set("short", "ʯ���");
        set("long", @LONG
��Щʯ�壬�����������������������е�·���������������˱仯
֮��������������İ���ͼһ�㣬���˾�����֮�����⣬���������
֮���������ǹ����񹦣������Ѳ⡣
LONG
        );
        set("exits", ([ /* sizeof() == 4 */
  "southeast" : __DIR__"road3",
  "south" : __DIR__"road4",
  "west" : __DIR__"narrow",
]));

        set("outdoors", "fengyun");
        setup();
        replace_program(ROOM);
}