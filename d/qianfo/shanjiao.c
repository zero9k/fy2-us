// Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.
#include <room.h>
inherit ROOM;
void create()
{
  set("short","ǧ��ɽ��");
  set("long",@LONG
ǧ��ɽ��������ɽ�����й������ɽ֮һ���Ӵ���������
һ����ɽ�������ϱ������Ӳ�����ɽ������Լ�ɼ������߷�����
���ɴ�ص���ӳ�¸��ⳬ�����ס�������һ�����ش����������
���������ŵı�����
LONG
  );
  set("exits",([
//         "north":__DIR__"shungeng.c",
         "east" :__DIR__"tanghuai.c",
         "west" :__DIR__"road1.c"
               ]));
        set("objects", ([
                __DIR__"npc/bonze" : 1,
       ]) );
        set("outdoors", "qianfo");
  setup();
  replace_program(ROOM);
}