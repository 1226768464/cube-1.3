#ifndef MAIN_PROC_FUNC_H
#define MAIN_PROC_FUNC_H

struct main_config
{
	char proc_name[DIGEST_SIZE];
	char * init_dlib;
	char * init_func;
	char * init_para;	
}__attribute__((packed));

static struct struct_elem_attr main_config_desc[]=
{
        {"proc_name",CUBE_TYPE_STRING,DIGEST_SIZE,NULL,NULL},
        {"init_dlib",CUBE_TYPE_ESTRING,DIGEST_SIZE*4,NULL,NULL},
        {"init_func",CUBE_TYPE_ESTRING,DIGEST_SIZE*2,NULL,NULL},
        {"init_para",CUBE_TYPE_ESTRING,DIGEST_SIZE*2,NULL,NULL},
	{NULL,CUBE_TYPE_ENDDATA,0,NULL,NULL}
};

struct plugin_config
{
	char name[DIGEST_SIZE];
//	enum proc_type type;
	char * plugin_dlib;
	char * init;
	char * start;	
	void * init_para;
}__attribute__((packed));

static struct struct_elem_attr plugin_config_desc[]=
{
        {"name",CUBE_TYPE_STRING,DIGEST_SIZE,NULL,NULL},
//        {"type",CUBE_TYPE_ENUM,sizeof(int),&sec_subject_type_valuelist},
        {"plugin_dlib",CUBE_TYPE_ESTRING,DIGEST_SIZE*4,NULL,NULL},
        {"init",CUBE_TYPE_ESTRING,DIGEST_SIZE*2,NULL,NULL},
        {"start",CUBE_TYPE_ESTRING,DIGEST_SIZE*2,NULL,NULL},
	{NULL,CUBE_TYPE_ENDDATA,0,NULL,NULL}
};

static struct timeval time_val={0,50*1000};
#endif
