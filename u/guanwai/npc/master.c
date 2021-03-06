
inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("葛伦", ({ "master gelun", "master","gelun" }) );
	set("gender", "男性" );
	set("age", 99);
	set("int", 30);
        set("apprentice_available", 20);
        create_family("大昭寺", 20, "主持");
	set("long",
		"葛伦高僧已在大昭寺主持多年。男女弟子遍布关外。\n"
		);
	set("inquiry", ([
		"舍利子": "嗯....舍利子.....在舍利塔里。\n",
		"普松": "普松在大昭寺的木屋里。",
	]) );
        set("combat_exp", 1000000);
        set("score", 90000);
        set_skill("unarmed", 50);
	set_skill("move", 100);
        set_skill("staff", 100);
        set_skill("force", 100);
        set_skill("parry", 100);
        set_skill("literate", 80);
	set_skill("iron-cloth", 150);

	set_skill("bloodystrike", 100);
	set_skill("cloudstaff", 100);
	set_skill("bolomiduo", 100);
	set_skill("buddhism", 200);
        set_skill("jin-gang", 150);


	map_skill("unarmed", "bloodystrike");
        map_skill("force", "bolomiduo");
        map_skill("literate", "buddhism");
        map_skill("iron-cloth", "jin-gang");
        map_skill("staff", "cloudstaff");
        map_skill("parry", "cloudstaff");
        set("agi",25);
        set("int",30);
        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: perform_action, "staff.longxianyuye" :),
        }) );
	setup();
	carry_object(__DIR__"obj/redcloth")->wear();
        carry_object(__DIR__"obj/9staff")->wield();
}
void reset()
{
        delete_temp("learned");
        set("apprentice_available", 20);
}
void attempt_apprentice(object ob)
{
        if( query("apprentice_available") ) {
                if( find_call_out("do_recruit") != -1 )
                        command("say 慢著，一个一个来。");
                else
                        call_out("do_recruit", 2, ob);
        } else {
                command("say 本主持今天已经收了二十个弟子，不想再收徒了。");
        }
}
void do_recruit(object ob)
{
                command("smile");
                command("say 很好，很好，很好。");
                command("recruit " + ob->query("id") );
}
int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "lama");
        add("apprentice_availavble", -1);
}
void init()
{
        add_action("give_quest", "quest");
}
void re_rank(object student)
{
        int exp;
        exp = (int) student->query("combat_exp");
        if( exp <= 32000 ) {
                student->set("title","大昭寺弟子");
                return ;
        } else if ( exp <= 128000 ) {
                student->set("title","大昭寺罗汉");
                return ;
        } else if ( exp <= 512000 ) {
                student->set("title","大昭寺高僧");
                return ;
        } else if ( exp <= 1536000 ) {
                student->set("title","大昭寺圣僧");
                return ;
        } else if ( exp <= 3456000 ) {
                student->set("title","大昭寺法王");
                return ;
        } else if ( exp <= 5187000 ) {
                student->set("title","大昭寺活佛");
                return ;
        } else if ( exp <= 26244000 ) {
                student->set("title","大昭寺副主持");
                return ;
        } else
                student->set("title","大昭寺主持");
                return ;

}
