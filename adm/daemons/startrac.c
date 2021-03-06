// race.c
#include <ansi.h>
#include <command.h>
#include <globals.h>
#define R_MIN 30
#define R_HOUR 5
#define R_DAY 1
void race_warning();
object make_body(object ob);
void init_race();
void kickplayerout();
int rmhirdir(string dir);
void findthem();
void create()
{
 	seteuid( ROOT_UID );
	init_race();
}
void init_race()
{
	mixed *local;

	local = localtime(time());
	{
// lock mud
	message("system", "\n整理玩家资料开始．．．\n", users());
	LOGIN_D->set_wizlock(3);
// kick out all players
	kickplayerout();
// search through all player data file and fine 1st, 2nd and 3rd & reward them
// reset score for all players
	findthem();
// unlock mud
	LOGIN_D->set_wizlock(0);
	message("system", "\n．．．整理玩家资料结束。\n", users());
	}	
}
void findthem()
{
        int statss,i, j, ppl_cnt, count;
        string *dir, *ppls, name;
	object ob , user, reward;
	string first_p, second_p, third_p;
	int  first_s=0, second_s=0, third_s = 0;
	int score = 0;
        count = 0;
        ppl_cnt = 0;
        dir = get_dir(DATA_DIR + "login/");
        for(i=0; i<sizeof(dir); i++) {
                reset_eval_cost();
                ppls = get_dir(DATA_DIR + "login/" + dir[i] + "/");
                ppl_cnt += sizeof(ppls);
                for(j=0; j<sizeof(ppls); j++) {
                        if( sscanf(ppls[j], "%s", name)==1 )
                                if( (string)SECURITY_D->get_status(name)!="(player)" )
                                        continue;
			user = new(LOGIN_OB);
		        user->set("id", name);
			if( user->restore() && user)
				if(objectp(ob = make_body(user))) 
					if( ob->restore())	
			{
				ob->set("title_race", 0);
                                score = (int) ob->query("score");
				score = (int) ob->query("score");
	if( score > first_s) { 
				third_s = second_s;
				third_p = second_p;
				second_s = first_s;
				second_p = first_p;
				first_s = score;
				first_p = name;
				}	
	else if( score > second_s) {
				third_s = second_s;
                                third_p = second_p;
                                second_s = score;
                                second_p = name;
				}
	     else if( score > third_s) {third_s = score; third_p = name;} 

				ob->set("score", 0);
				ob->save();
                                count ++;
				destruct(ob);
				destruct(user);
			}		
                }
        }

        log_file("RACE_LOG", sprintf("%s
风云第一：%s (%d)
风云第二：%s (%d)
风云第三：%s (%d)\n", ctime(time()),first_p, first_s, second_p, second_s, third_p, third_s));
//time to reward our good guys
 if(first_p) {
 user = new(LOGIN_OB);
 user->set("id", first_p);
 if( user->restore() && user)
 if(objectp(ob = make_body(user)))
 if( ob->restore())
 {
	ob->set("title_race",1);
	ob->save();
	destruct(ob);
	destruct(user);
 }}
if(second_p) {
 user = new(LOGIN_OB);
 user->set("id", second_p);
 if( user->restore() && user)
 if(objectp(ob = make_body(user)))
 if( ob->restore())
 {
        ob->set("title_race",2);
        ob->save();
        destruct(ob);
        destruct(user);
 }}
if(third_p) {
 user = new(LOGIN_OB);
 user->set("id", third_p);
 if( user->restore() && user)
 if(objectp(ob = make_body(user)))
 if( ob->restore())
 {
        ob->set("title_race",3);
        destruct(ob);
        destruct(user);
 }}

        return ;
}
void kickplayerout()
{
 object *user, *inv, link_ob;
 object me;
 int i;
         user = users();
        for(i=0; i<sizeof(user); i++) {
                if( !environment(user[i]) || wizardp(user[i])) continue;
	me = user[i];
               inv = all_inventory(me);
                for(i=0; i<sizeof(inv); i++)
                        if( !inv[i]->query_autoload() )
                                DROP_CMD->do_drop(me, inv[i]);
        link_ob = me->query_temp("link_ob");

        // We might be called on a link_dead player, so check this.
        if( link_ob ) {
                link_ob->set("last_on", time());
                link_ob->set("last_from", query_ip_name(me));
                link_ob->save();
                destruct(link_ob);
		      }
        me->save();
        destruct(me);
				}
	return;
}

void race_warning()
{
	mixed *local;
	string warning_msg;
	local = localtime(time());
	warning_msg = sprintf("\n玩家资料整理将在%s分中后开始，请准备暂时离开风云。\n",
			chinese_number(R_MIN - local[1] - 1));
	message("system", warning_msg, users());
	if( R_MIN - local[1] > 2 )
	call_out("race_warning", 60);
	return;
}
object make_body(object ob)
{
        string err;
        object user;
        int n;
	if (! ob->query("id")) return 0;
        user = new(USER_OB);
        if(!user) return 0;
        seteuid(ob->query("id"));
        export_uid(user);
        export_uid(ob);
        seteuid(getuid());
        user->set("id", ob->query("id"));
        user->set_name( ob->query("name"), ({ ob->query("id")}) );
        return user;
}

int rmhirdir(string dirstr)
{
string *dir;
int i;
dir = get_dir(dirstr+"/");
        for(i=0; i<sizeof(dir); i++) {
                if(file_size(dirstr+"/"+dir[i]) == -2 ) {
                                rmhirdir( dirstr +"/"+dir[i]);
                                rmdir(dirstr+"/"+dir[i]);
                                                }
                rm(dirstr+"/"+dir[i]);
        }
rmdir(dirstr);

return 1;
}
