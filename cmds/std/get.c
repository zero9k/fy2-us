// get.c

#include <ansi.h>

inherit F_CLEAN_UP;

int do_get(object me, object ob);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	string from, item;
	object obj, *inv, env, obj2;
	int i, amount;

	if( !arg ) return notify_fail("你要捡起什麽东西？\n");
	if( me->is_busy() )
		return notify_fail("你上一个动作还没有完成！\n");

	// Check if a container is specified.
	if( sscanf(arg, "%s from %s", arg, from)==2 ) {
		env = present(from, me);
		if(!env) env = present(from, environment(me));
		if(!env) return notify_fail("你找不到 " + from + " 这样东西。\n");
		if(living(env) && (wiz_level(me) <= wiz_level(env)))
			return notify_fail("你的巫师等级必须比对方高，才能搜身。\n");
	} else env = environment(me);
	// check if this thing is locked or whatsoever any tricks invovled
	if( (int) env->is_closed())
		return notify_fail( "你要先把" + env->name() + "打开。\n");
	// Check if a certain amount is specified.
	if(sscanf(arg, "%d %s", amount, item)==2) {
		if( !objectp(obj = present(item, env)) )
			return notify_fail("这里没有这样东西。\n");
		if( !obj->query_amount() )
			return notify_fail( obj->name() + "不能被分开拿走。\n");
		if( amount < 1 )
			return notify_fail("东西的个数至少是一个。\n");
		if( amount > obj->query_amount() )
			return notify_fail("这里没有那麽多的" + obj->name() + "。\n");
		else if( amount == (int)obj->query_amount() ) {
			return do_get(me, obj);
		} else {
			obj->set_amount( (int)obj->query_amount() - amount );
			obj2 = new(base_name(obj));
			obj2->move(env);			// For containers.
			obj2->set_amount(amount);
			// Counting precise amount costs more time.
			if( me->is_fighting() ) me->start_busy(3);
			return do_get(me, obj);
		}
	}

	// Check if we are makeing a quick get.
	if(arg=="all") {
		if( me->is_fighting() )	return notify_fail("你还在战斗中！只能一次拿一样。\n");
		if( !env->query_max_encumbrance() )	return notify_fail("那不是容器。\n");

		inv = all_inventory(env);
		if( !sizeof(inv) )
			return notify_fail("那里面没有任何东西。\n");

		for(i=0; i<sizeof(inv); i++) {
			if( (inv[i]->is_character() && !inv[i]->query("yes_carry")) || inv[i]->query("no_get") ) continue;
			do_get(me, inv[i]);
		}
		write("Ok。\n");
		return 1;
	}

	if( !objectp(obj = present(arg, env)) || (living(obj) && !(int)obj->query("yes_carry")))
		return notify_fail("你附近没有这样东西。\n");

	if( obj->query("no_get") )
		return notify_fail("这个东西拿不起来。\n");
	
	return do_get(me, obj);
}
	
int do_get(object me, object obj)
{
	object old_env, *enemy;
	int equipped;
	object target;
	string	prep;

	target = me;
	if( !obj ) return 0;
	old_env = environment(obj);
	if( obj->is_character()  && !obj->is_corpse()) {
				return notify_fail("你只能背负尸体。\n");
		// If we try to save someone from combat, take the risk :P
	} else {
		if( obj->query("no_get") ) return 0;
	}

	if( obj->query("equipped") ) equipped = 1;
	if( obj->query("yes_carry")) target = environment(me);
	if( obj->move(target) ) {
		if((int)obj->query("no_transfer")
		){obj->set("no_get",1); obj->set("no_drop",1);}
		if( me->is_fighting() ) me->start_busy(1);
		if( obj->is_character()  && !obj->query("yes_carry"))
			message_vision( "$N将$n扶了起来背在背上。\n", me, obj );
		else {
			if(old_env==environment(me)) prep =  "捡起";
			else if(old_env->is_character()) prep =  "从" + old_env->name() + "身上" + (equipped? "除下" : "搜出");
			else switch( old_env->query("prep") ) {
				case "on":
					prep = "从" + old_env->name() + "上拿起";
					break;
				case "under":
					prep = "从" + old_env->name() + "下拿出";
					break;
				case "behind":
					prep = "从" + old_env->name() + "后拿出";
					break;
				case "inside":
					prep = "从" + old_env->name() + "中拿出";
					break;
				default:
					prep = "从" + old_env->name() + "中拿出";
					break;
			};
			message_vision( sprintf("$N%s一%s$n。\n", prep,
				obj->query("unit")), me, obj );
		}
		return 1;
	}
	else return 0;
}

int help(object me)
{
	write(@HELP
指令格式 : get <物品名称> [from <容器名>]
 
这个指令可以让你捡起地上或容器内的某样物品.
 
HELP
    );
    return 1;
}
 
