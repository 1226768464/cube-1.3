#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <dirent.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/socket.h>

#include "../include/data_type.h"
#include "alloc.h"
#include "string.h"
#include "basefunc.h"
#include "../include/struct_deal.h"
#include "../include/crypto_func.h"
#include "../include/memdb.h"
#include "../include/message.h"
#include "../include/sec_entity.h"

extern struct timeval time_val={0,50*1000};

int echo_plugin_init(void * sub_proc,void * para)
{
	int ret;
	// add youself's plugin init func here
	return 0;
}

int echo_plugin_start(void * sub_proc,void * para)
{
	int ret;
	void * recv_msg;
	int i;
	int type;
	int subtype;


	for(i=0;i<3000*1000;i++)
	{
		usleep(time_val.tv_usec);
		ret=ex_module_recvmsg(sub_proc,&recv_msg);
		if(ret<0)
			continue;
		if(recv_msg==NULL)
			continue;
		type=message_get_type(recv_msg);
		subtype=message_get_subtype(recv_msg);
		if(type==0)
		{
			printf("message format error!\n");
			continue;
		}
//		if(!find_record_type(type))
//		{
//			printf("message format is not registered!\n");
//			continue;
//		}
		proc_echo_message(sub_proc,recv_msg);
	}

	return 0;
};

int proc_echo_message(void * sub_proc,void * message)
{
	int type;
	int subtype;
	int i;
	int ret;
	printf("begin proc echo \n");
	struct message_box * msg_box=message;
	type=message_get_type(message);
	subtype=message_get_subtype(message);

	struct message_box * new_msg;
	void * record;
	new_msg=message_create(type,subtype,message);
	
	i=0;


	ret=message_get_record(message,&record,i++);
	if(ret<0)
		return ret;
	while(record!=NULL)
	{
		message_add_record(new_msg,record);
		ret=message_get_record(message,&record,i++);
		if(ret<0)
			return ret;
	}

	ex_module_sendmsg(sub_proc,new_msg);

	return ret;
}
