#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <stack>
#include <queue>
#include <algorithm>
#include <iostream>
#define N 20

using namespace std;

typedef struct Flight	    //航班信息
{
	struct Flight *next,*prev;
	char Airways[N];      	//航空公司
	char Flight_ID[N];      //航班号
	char Aircraft_Type[N];  //机型
	
	char T_City[N];         //起飞城市缩写take off city...
	char L_City[N];         //到达城市缩写landing city...
	
	char T_Airport[N];      //起飞机场
	char L_Airport[N];      //到达机场
	
	char Date[N];    		//日期
	char T_Time[N];    		//起飞时刻
	char L_Time[N];    		//到达时刻
	
	float M_Discount;    	//最大折扣
	float Tic_Price;		//机票单价 
	
	int seat;				//座位数/满载人员
	int cur_order;			//当前已订座位数
	char sequence[N];		//机票流水号//？？有待商榷               
}Flight;

typedef struct Customer     //顾客信息
{
	struct Flight *next,*prev;
	char Customer_Name[N];  //顾客姓名
	char IDcard[N];			//身份证号
	int Tic_Bought;			//该顾客名下所购机票数
}Customer;

//——————函数声明部分——————//
Flight *nil; 
bool First = true;                       ///是否是第一次登录系统
bool flag = false;                       ///检查从文件读入的信息是否有误
void mainmenu();						 ///主菜单
void read_info();						 ///读入文件信息
void store_info(); 						 ///存储信息
typedef int (*PFUN)(char s[]);           ///函数指针
int max_sequence = 0, login_cnt = 3;     ///max_sequence 为最大流水号，login_cin 登录次数.
bool flag_info_match = false;            ///检查从键盘录入信息是否匹配
char read_file_path[N][5*N];             ///储存读入的文件路径
int read_cnt = 0;                        ///读入文件数量
Flight* listSearch(char sequence[]);
Flight* creatSequence(Flight *p);
void insert_info_sequence(Flight *p);
void moditfyFlight(Flight *p);
void deleteFlight(Flight *t);
void deleteSequence(char sequence[]);
void printFlight(Flight *p);
void printList();
void printDoc();
int getMaxsequence(char str[]);
int read_check(Flight *p);
int check_read_file_path(char path[]);
int check_doc(Flight *p);
int check_time_fomart(unsigned int time);
int identify_usr();
void init();
void mainmenu();
void add_info();
void moditfy_info();
void remove_info();
void doc_info();
void room_info();
void pat_info();
void all_info();
void wholesale_info();
void read_info();
void store_info();
void time_info();
void new_usr_info();
void add_doc_info();
void remove_doc_info();
void add_doc_info();
int fun(char s[],PFUN pfun);
int is_number(char c);
int is_alpha(char c);


//————————链表操作函数————————//
Flight* listSearch(char sequence[])   ///   根据sequence搜索结点
{
    Flight *p = nil->next;
    while(p!=nil && strcmp(p->sequence,sequence)!=0)
    {
        p = p->next;
    }
    return p;
}
void init()                      ///   初始化List
{
    nil = (Flight* )malloc(sizeof(Flight));
    nil->next = nil;
    nil->prev = nil;
}
//———————————生成流水号部分———————————————//怎么算没想好
/*
int get_cur_order(char str[])      ///   更新当前航班订单数
{
    int cnt_sequence = 0,i=0;
    for(i=1;i<=2;i++)
        cnt_doc = cnt_doc*10 + int(str[i]-'0');
    if(cnt_doc > max_doc)
        max_doc = cnt_doc;

    for(i=3;i<=5;i++)
        cnt_sequence = cnt_sequence*10 + int(str[i]-'0');
    if(cnt_sequence > max_sequence)
        max_sequence = cnt_sequence;
}
Flight* creatSequence(Flight *p)        ///   生成一个新的序列号
{
    int i=0;
    ///清空字符串
    while(p->sequence[i]!='\0')
    {
        p->sequence[i]='\0';
        i++;
    }
    if(strcmp(p->room,"儿科")==0)
        p->sequence[0] = 'a';
    else if(strcmp(p->room,"神经科")==0)
        p->sequence[0] = 'b';
    else  if(strcmp(p->room,"五官科")==0)
        p->sequence[0] = 'c';
    else if(strcmp(p->room,"精神科")==0)
        p->sequence[0] = 'd';
    else if(strcmp(p->room,"骨科")==0)
        p->sequence[0] = 'e';
    else                           ///其他科室暂时设为z
        p->sequence[0] = 'z';
    ///2~3位的医生编号
    p->sequence[1] = p->doc_num / 10 + '0';
    p->sequence[2] = p->doc_num % 10 + '0';
    ///后三位的流水序号
    max_sequence++;
    p->sequence[3] = max_sequence / 100 + '0';
    p->sequence[4] = max_sequence / 10 %10 + '0';
    p->sequence[5] = max_sequence % 10 + '0';
    
    printf("\n\t\t\t  机票流水号:%s\n",p->sequence);
    return p;
}
*/
//———————基本操作部分————————//
int is_number(char c)                 ///判断数字
{
    return (c >= '0' && c <= '9')? 1:0;
}
int is_alpha(char c)                  ///判断字母
{
    return ((c >='a' && c <= 'z') || (c >= 'A' && c <= 'Z'))? 1:0;
}
//——————顾客用户登陆信息————————//
int identify_usr()                      ///确认使用者身份
{
    char usr[N],pwd[N];
    char u[N],p[N];
    int  result = 0;
    FILE *fp = fopen("urs_info.txt","r");
    fflush(stdin);
    printf("\n\n");
    printf("\t\t\t\t\t\t欢 迎 使 用 飞 机 订 票 系 统 \n");
    printf("\n\n\n\n\n");
    printf("\t\t\t\t用户名：");
	gets(usr);
    printf("\n\n\n");
    printf("\t\t\t\t密  码：");
	gets(pwd);
    fflush(stdin);
    while(fscanf(fp,"%s%s",u,p)!=EOF)
    {
        if(strcmp(u,usr)==0 && strcmp(p,pwd)==0)
        {
            cout<<"\n\t\t\t身 份 验 证 成 功 !\t\t\t\n";
            return 1;
        }
    }
    return 0;
}
int check_new_usr_info(char new_usr[])  ///检查新用户命名格式
{
    char old_usr[N],old_pwd[N];
    FILE *fp;
    int cnt = 0;
    if(strlen(new_usr) < 6)
    {
        cout<<("\n        用 户 名 长 度 少 于 6 位 !      \n");
        return 0;
    }
    fp = fopen("urs_info.txt","a");
    while(fscanf(fp,"%s%s",old_usr,old_pwd)!=EOF)
    {
        if(strcmp(new_usr,old_usr)==0)
        {
            cnt = 1;
            break;
        }
    }
    if(cnt)
    {
        cout<<("\n        用 户 名 已 存 在 !      \n");
        return 0;
    }
    else
        return 1;
}
int check_new_pwd_info(char new_pwd[])  ///检查新用户密码格式
{
    if(strlen(new_pwd) < 6)
    {
        cout<<("        密 码 长 度 少 于 6 位 !      ");
        return 0;
    }
    return 1;
}
void new_usr_info()              ///   注册新用户
{
    char new_usr[N],new_pwd[N],re_pwd[N];
    FILE *fp;
    int cnt = 0,result = 0;
    printf("\n\n\t\t\t\t\t\t\t新 用 户 注 册 窗 口 \n\n");
    printf("\t\t\t\t用户名：");
    printf("\n\n\t\t\t\t密  码：");
    printf("\n\n\t     \t\t\t重复密码:");
    scanf("%s",re_pwd);
    if(strcmp(new_pwd,re_pwd)!=0)
    {
        cout<<"\n两 次 输 入 密 码 不 一 致 , 请 重 新 输 入 ！";
        new_usr_info();
        return ;
    }
    fp = fopen("urs_info.txt","a");
    fprintf(fp,"%s %s\n",new_usr,new_pwd);
    fclose(fp);
    cout<<"\n        注 册 验 证 成 功 !       \n";
    system("pause");
    mainmenu();
}
int check_ID(char ID[])               ///检查顾客的身份证格式
{
    int i = 0;
    for(i=0;ID[i]!='\0';i++)
    {
        if((!is_number(ID[i])) && i < 17)
        {
            cout<<"\n          身 份 证 格 式 不 正 确!\n\n亲 , 你 可 能 输 入 了 假 的 身 份 证 哟 ~       \n";
            return 0;
        }
        if(is_alpha(ID[i]) && i==18 && (ID[i]!='X' && ID[i] !='x'))
        {
            cout<<"\n          身 份 证 格 式 不 正 确!\n\n亲 , 你 可 能 输 入 了 假 的 身 份 证 哟 ~       \n";
            return 0;
        }
        if((!is_alpha(ID[i])) && i == 18 && (!is_number(ID[i])))
        {
            cout<<"\n          身 份 证 格 式 不 正 确!\n\n亲 , 你 可 能 输 入 了 假 的 身 份 证 哟 ~       \n";
            return 0;
        }
    }
    if(strlen(ID)!=18)
    {
        cout<<("\n      亲 ， 你 的 身 份 证 漏 填 或 多 填 了 几 位 数 哟 ~      \n");
        return 0;
    }
    return 1;
}

//———————系统功能部分———————//
void add_info()                  ///   添加信息
{
    int result = 0;
    Flight *p;
    char p_num[N],p_age[N];
    int i = 0,len = 0;
    flag_info_match = false;    ///    医生信息匹配
    p = (Flight* )malloc(sizeof(Flight));
    printDoc();
    fflush(stdin);
    printf("\n\t\t请按照系统提示输入对应信息:\n\n");
    printf("\t\t\t    科室：");
    goto_prev(p->room,check_room);

    printf("\n\t\t\t医生姓名：");
    goto_prev(p->doc_name,check_doc_exit);

    printf("\n\t\t\t医生编号：");
    goto_prev(p_num,check_doc_num);
    p->doc_num = atoi(p_num);

    check_doc_info_match(p);

    if(flag_info_match)
    {
        flag_info_match = false;
        creatSequence(p);
        printf("\n\t     时间(例:2017-01-01):");
        goto_prev(p->time,check_time_fomart);

        printf("\n\t\t\t患者姓名：");
        goto_prev(p->pat_name,check_name_format);

        printf("\n\t\t     患者身份证号：");
        goto_prev(p->ID,check_ID);

        printf("\n\t\t\t患者年龄：");
        goto_prev(p->pat_age,check_age);

        printf("\n\t\t\t诊疗花费：\t元\t角\t分\n\t\t\t\t\t");
        scanf("%f",&exp.yuan);
        scanf("%1f",&exp.jiao);
        scanf("%1f",&exp.fen);
        p->cost = exp.yuan + ((float)(exp.jiao))/10 + ((float)(exp.fen))/100;
        result = MessageBox( NULL , TEXT("确 认 添 加 信 息?") , TEXT("通 知") , MB_ICONINFORMATION|MB_YESNO);
        switch(result)
        {
            case IDYES:
                    insert_info_sequence(p);
                    store_info();
                    MessageBox(NULL,TEXT("信 息 已 添 加!"),TEXT("通 知"),MB_OK);
                    break;
            case IDNO:MessageBox(NULL,TEXT("添 加 已 取 消!"),TEXT("通 知"),MB_OK);break;
        }
        result = MessageBox( NULL , TEXT("是 否 继 续 添 加 信 息?") , TEXT("通 知") , MB_ICONINFORMATION|MB_YESNO);
        switch(result)
        {
            case IDYES:
                add_info();
                break;
            case IDNO:
                mainmenu();
                break;
        }
    }
}
void mainmenu()                  ///   主菜单
{
    char cmd[20];
    int cnt = 3,i=0,result = 0;
    ///输入命令清空
    while(cmd[i]!='\0')
    {
        cmd[i]= '\0';
        i++;
    }
    if(First)
    {
        read_info();
        while(!identify_usr())
        {
            cout<<"\n输入的用户名与密码不正确!\n";
            if(!--cnt)exit(0);
        }
        First = false;
    }
    printf("\n\n\n\n\n");
    printf("\t\t\t\t\t\t1.添加信息.\n\n");//需要管理员权限
    printf("\t\t\t\t\t\t12.修改信息.\n\n");
    printf("\t\t\t\t\t\t13.删除信息.\n\n");    
    printf("\t\t\t\t\t\t1.航班浏览.\n\n");//正常顾客权限
    printf("\t\t\t\t\t\t2.查询信息.\n\n");
    printf("\t\t\t\t\t\t3.我的订单.\n\n");
    printf("\t\t\t\t\t\t4.查询信息.\n\n");
    printf("\t\t\t\t\t\ts.储存信息.\n\n");
    printf("\t\t\t\t\t\ta.添加用户\n\n");
    printf("\t\t\t\t\t\t0.退出系统\n\n");
    printf("\t\t\t\t\t\t请从键盘输入所选择的功能前的对应数字:");
    fflush(stdin);
    scanf("%s",cmd);
    if(cmd[1]!='\0')
    {
        printf("\n输入的命令无效,是否重新输入?\n");
        printf("\n1:yes\t0:no\n");
        scanf("%d",&result);
        switch(result)
        {
            case 1:mainmenu();break;
            case 0:exit(0);break;
            default:exit(0);break;
        }
    }
    while(cmd[1]=='\0')
    {
        switch(cmd[0])
        {
            case '0':exit(0);break;
            case '1':add_info();break;
            case '2':printList();moditfy_info();break;
            case '3':remove_info();break;
            case '4':doc_info();break;
            case '5':room_info();break;
            case '6':pat_info();break;
            case '7':all_info();break;
            case '8':wholesale_info();break;
            case '9':time_info();break;
            case 's':store_info();break;
            case 'r':read_info();break;
            case 'a':new_usr_info();break;
            case 'b':add_doc_info();break;
            case 'c':remove_doc_info();break;
        }
    }
}
void time_info()                 ///   查询时间范围内的信息
{
    char Star[N],End[N];
    system("cls");
    Flight *p = nil->next;
    printf("\n\n");
    printf("\t\tTip:跳过输入请输入EOF(Ctrl+Z).\n\n");
    printf("\t\tTip:日期正确格式:2017-01-01(xxxx-xx-xx).\n\n");
    printf("\t\t请输入开始时间:");
    goto_prev(Star,check_time_fomart);
    printf("\n\n");
    printf("\t\t请输入结束时间:");
    goto_prev(End,check_time_fomart);
    if(!check_star_to_end(Star,End))
    {
        MessageBox(NULL,TEXT("        开始时间晚于结束时间!      "),TEXT("Warning!"),MB_OK);
        printf("\n\n");
        system("pause");
        mainmenu();
    }
    else
    {
        printf("\t序号\t\t时间\t\t科室\t医生姓名\t患者姓名\t患者年龄\t诊疗花费\n\n");
        if(End[0] != '\0' && Star[0] != '\0')
        {
            while(p!=nil)
            {
                if(strcmp(Star,p->time) <=0 && strcmp(End, p->time)>=0)
                   printf("\t%s\t\t%s\t%s\t%s\t\t%s\t\t%s\t\t%.2f\n",p->sequence,p->time,
                        p->room,p->doc_name,p->pat_name,p->pat_age,p->cost);
                p = p->next;
            }
        }
        else if(End[0] == '\0' && Star[0] != '\0')
        {
            while(p!=nil)
            {
                if(strcmp(Star,p->time) <= 0)
                    printf("\t%s\t\t%s\t%s\t%s\t\t%s\t\t%s\t\t%.2f\n",p->sequence,p->time,
                        p->room,p->doc_name,p->pat_name,p->pat_age,p->cost);
                p = p->next;
            }
        }
        else if(End[0] != '\0' && Star[0] == '\0')
        {
            while(p!=nil)
            {
                if(strcmp(End,p->time) >= 0)
                    printf("\t%s\t\t%10s\t%s\t%s\t\t%s\t\t%s\t\t%.2f\n",p->sequence,p->time,
                        p->room,p->doc_name,p->pat_name,p->pat_age,p->cost);
                p = p->next;
            }
        }
        else
            all_info();
        printf("\n\n");
        system("pause");
        mainmenu();
    }
}
/*void read_info()
{
	printf("\nnow you are in read_info\n");
}*///假的read
void read_info()                 ///   读入文件信息
{
    FILE *fp;
    FILE *fp_doc;
    int num = 0,result = 0,n=0;
    char str_n;
    char name[N],room[N];
    char path[5*N];
    Flight *p = (Flight*)malloc(sizeof(Flight));

    //读入医生编号信息
    fp_doc = fopen("doc_info.txt","r");
    while(fscanf(fp_doc,"%s%d%s",room,&num,name)!=EOF)
    {
        if(Doc[num].doc_name[0]!='\0' && strcmp(name,Doc[num].doc_name)!=0)
        {
            MessageBox(NULL,TEXT("        医生编号重复!      "),TEXT("Warning!"),MB_OK);
        }
        strcpy(Doc[num].doc_name,name);
        Doc[num].doc_num = num;
        strcpy(Doc[num].doc_room,room);

        if(num > max_doc)
            max_doc = num;
    }
    fclose(fp_doc);
    if(!First)
    {
        printf("\n\n\n\t\t\t输入文件路径：\n\t\t\t\t  >>");
        goto_prev(path,check_read_file_path);
        fp = fopen(path,"r");
        //读入医疗信息
        if(fp == 0)
        {
            result = MessageBox( NULL , TEXT("打开文件失败，是否重新输入文件路径?\n") , TEXT("Error!") , MB_ICONINFORMATION|MB_YESNO);
            switch(result)
            {
                case IDYES:read_info();break;
                case IDNO:system("cls");mainmenu();exit(0);
            }
        }
        else
        {
            strcpy(read_file_path[read_cnt++],path);
            result = MessageBox( NULL , TEXT("是 否 录 入 该 文 件 中 的 所 有 信 息？") , TEXT("通 知") , MB_ICONINFORMATION|MB_YESNO);
            switch(result)
            {
                case IDYES:
                    printf("\n");
                    while(fscanf(fp,"%s%s%s%s%s%s%f%s",p->sequence,&p->time,p->room,
                                 p->doc_name,p->pat_name,&p->pat_age,&p->cost,p->ID)!=EOF)
                    {
                        read_check(p);
                        if(flag)
                        {
                            result = MessageBox( NULL , TEXT("\n读 入 无 效 数 据 !\n\n是 否 继 续 读 入 ?\n") , TEXT("Data Error!") , MB_ICONINFORMATION|MB_YESNO);
                            switch(result)
                            {
                                case IDYES:
                                    flag = false;
                                    break;
                                case IDNO:
                                    flag = false;
                                    system("pause");
                                    mainmenu();
                                    return ;
                            }
                        }
                        getMaxsequence(p->sequence);
                        insert_info_sequence(p);
                    };
                    break;
                case IDNO:
                    printf("\n\t\t输入您需要读入信息的次数:");
                    scanf("%d",&n);
                    while(n && fscanf(fp,"%s%s%s%s%s%s%f%s",p->sequence,&p->time,p->room,
                             p->doc_name,p->pat_name,&p->pat_age,&p->cost,p->ID)!=EOF)
                    {
                         read_check(p);
                        if(flag)
                        {
                            result = MessageBox( NULL , TEXT("\n 读 入 无 效 数 据 !\n\n 是 否 继 续 读 入 ?\n") , TEXT("Data Error!") , MB_ICONINFORMATION|MB_YESNO);
                            switch(result)
                            {
                                case IDYES:
                                    flag = false;
                                    break;
                                case IDNO:
                                    flag = false;
                                    system("pause");
                                    mainmenu();
                                    return ;
                            }
                        }
                         getMaxsequence(p->sequence);
                         insert_info_sequence(p);
                         n--;
                         if(!n)
                             MessageBox(NULL,TEXT("        文 件 中 的 信 息 已 读 取 完 毕       "),TEXT("Warning!"),MB_OK);
                    };
                    break;
            }
        }
        fclose(fp);
        //检查读入数据是否有误
        result = MessageBox( NULL , TEXT("\n\t数 据 读 入 完 毕 !\n\n 是 否 继 续 读 入 其 他 文 件 信 息 ?\n") , TEXT("Message") , MB_ICONINFORMATION|MB_YESNO);
        switch(result)
        {
            case IDYES:
                flag = false;
                read_info();
                break;
            case IDNO:
                flag = false;
                system("pause");
                mainmenu();
                return ;
        }
    }
}
void store_info()                ///   储存信息
{
    Flight *p = nil->next;
    char path[5*N];
    FILE *fp;
    system("cls");
    printList();
    printf("\n\n\n\t\t\t输入保存文件路径：\n\t\t\t\t  >>");
    goto_prev(path,check_path_open);
    fp = fopen(path,"w");
    while(p!=nil)
    {
        fprintf(fp,"%6s\t%10s\t%20s\t%20s\t%20s\t%3s\t%.2f\t%18s\n",p->sequence,p->time,p->room,
        p->doc_name,p->pat_name,p->pat_age,p->cost,p->ID);
        p = p->next;
    }
    fclose(fp);
    printf("\n信 息 已 保 存\n");
    printf("\n\n");
    system("pause");
    mainmenu();
}
int main()
{
    init();
    while(1)
        mainmenu();
    return 0;
}



























