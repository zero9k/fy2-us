
inherit ROOM;

void create()
{
        set("short", "����֮��");
        set("long", @LONG
�ڷ⽭��ǰ���죬���ݵľ��������׼���õ�ľ�������ɻ����У�����������ϵס��
�⽭�󣬸��ڽ����ϵ�ľ�ܶ������˸������������ڣ���ש���ߣ�����һ�������СС��
��ʽ�����ķ��ӣ����ڽ��ϸ���������
LONG
        );
        set("exits", ([ 
  "east" : __DIR__"town",
]));
        set("outdoors", "laowu");
       set("objects", ([
        __DIR__"npc/guan" : 2,
                        ]) );

        setup();
        replace_program(ROOM);

}
