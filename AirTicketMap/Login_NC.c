#include <stdio.h>
#include <string.h>
#include <windows.h>
#define N 20

void identify_admin();
int identify_user();
void mainmenu_admin();
void mainmenu_user();
void new_usr_info();
int cnt=1;

int identify()
{
	int choi=0;
	printf("\n\n\t\t*****************************************************************\n");
	printf("\t\t*\t\t\t欢迎使用飞机订票系统\t\t\t*");
	printf("\n\t\t*****************************************************************\n");
	printf("\t\t*\t\t\t请选择登陆通道：\t\t\t*\n");
	printf("\t\t*\t\t\t1:管理员通道\t\t\t\t*\n");
	printf("\t\t*\t\t\t2:用户通道\t\t\t\t*\n");
	printf("\t\t*\t\t\t0:退出飞机订票系统\t\t\t*\n");
	printf("\t\t*****************************************************************\n");
	while(1)
	{
		printf("\n\t\t\t\t请输入您的选择～：");
		scanf("%d",&choi);
		if(choi == 1)
		{
			identify_admin();
			break;
		}
		else if (choi == 2)
		{
			identify_user();
			//mainmenu_user();
			break;
		}
		else
		{
			printf("\n请重新输入(选择1或者2)\n");
        }
			if(choi==0)
			{
				printf("看来你是铁了心要退出系统啦～欢迎下次使用～");
				exit(0);
				break;
			}

	}
	return 0;
}


void identify_admin()
{
	char admin_pwd[N];
	char admin_new_pwd[N];
	char admin_re_pwd[N];
	char admin_p[N];

	int choi=0;
	//FILE *fp = fopen("admin_info.txt","r");
	FILE *fp = fopen("admin_pwd.txt","w");
	fflush(stdin);

	while(1)
	{
		printf("\n\n\t\t\t\t用户名：admin\n");
		printf("\t\t\t\t密 码：");
		scanf("%s",admin_pwd);
		fscanf(fp,"%s",admin_p);
        if(strcmp(admin_p,admin_pwd)==0)
        {
            printf("\n\t\t\t身 份 验 证 成 功 !\t\t\t\n");
            break;
        }
        else
        {
        	printf("\n密码错误%d次！\n",cnt);
        	cnt++;
        	if(cnt==4)
        	{
        		printf("\n\t\t\t\t忘记密码了？\n");
        		printf("\n\t\t\t\t0.我想再试试\n");
        		printf("\n\t\t\t\t1.我不知道密码\n");
        		printf("\n\t\t\t\t2.我要重置密码\n");
        		while(1)
				{
					printf("\n\t\t\t\t请输入您的选择～：");
					scanf("%d",&choi);
					if(choi == 0)
					{
						cnt=1;
						identify_admin();
						break;
					}
					else if (choi == 1)
					{
						printf("\n熊孩子不知道密码还来登陆管理员通道...\n亲，我将自动为您跳转用户通道～\n");
						identify_user();
						break;
					}
					else if(choi == 2)
					{
						printf("\n请输入重置验证码：");
						int yzm;
						scanf("%d",&yzm);
						if(yzm == 159)
						{
							printf("\n验证成功！请输入重置密码：");
							scanf("%s",admin_new_pwd);
							printf("\n重复密码:");
    						scanf("%s",admin_re_pwd);
    						if(strcmp(admin_new_pwd,admin_re_pwd)!=0)
						    {
						        printf("\n两 次 输 入 密 码 不 一 致 , 稍 后 再 见 ！");
						        identify_admin();
						        return ;
						    }
							//fp = fopen("admin_info.txt","a");
    						fprintf(fp,"%s\n",admin_new_pwd);
    						//fclose(fp);
						}
					}
					else
					{
						printf("\n请重新输入～～\n");
						if(choi==159)
						{
							printf("看来你是铁了心要退出系统啦～欢迎下次使用～");
							exit(0);
							break;
						}
					}
        		}
        	}
    	}
    }
    fclose(fp);
}
int identify_user()
{
	char usr[N],pwd[N];
    char u[N],p[N];
    int  result = 0;
    FILE *fp = fopen("urs_info.txt","r");
    fflush(stdin);
    printf("\n\n");
    printf("\t\t\t\t\t\t欢 迎 使 用 飞 机 订 票 系 统 \n");
    printf("\n\n\n\n\n");
    while(1)
    {
		printf("\n\t\t\t\t1.我已有账号\n\t\t\t\t0.新用户注册\n");
		printf("\n\t\t\t\t请输入您的选择：\n");
		scanf("%d",&result);
		if(result == 1)
		{
			break;
		}
		else if(result == 0)
		{
			new_usr_info();
			break;
		}
		else
		{
			printf("\n请重新输入～～\n");
			if(result==159)
			{
				printf("看来你是铁了心要退出系统啦～欢迎下次使用～");
				exit(0);
				break;
			}
		}
	}
	printf("\t\t\t\t用户名：");
	scanf("%s",usr);
	printf("\n\n\n");
	printf("\t\t\t\t密  码：");
	scanf("%s",pwd);
	fflush(stdin);
	while(fscanf(fp,"%s%s",u,p)!=EOF)
	{
		if(strcmp(u,usr)==0 && strcmp(p,pwd)==0)
		{
		    printf("\n\t\t\t身 份 验 证 成 功 !\t\t\t\n");
		    mainmenu_user();
		    return 1;
		}
	}
    return 0;
}

void mainmenu_admin()
{
	printf("\nnow you are in mainmenu_admin\n");
}
void mainmenu_user()
{
	printf("\nnow you are in mainmenu_user\n");
}

void new_usr_info()              ///   注册新用户
{
    char new_usr[N],new_pwd[N],re_pwd[N];
    FILE *fp;
    int cnt = 0,result = 0;
    printf("\n\n\t\t\t\t\t\t\t新 用 户 注 册 窗 口 \n\n");
    printf("\t\t\t\t用户名：");
    scanf("%s",new_usr);
    printf("\n\n\t\t\t\t密  码：");
    scanf("%s",new_pwd);
    printf("\n\n\t     \t\t\t重复密码:");
    scanf("%s",re_pwd);
    if(strcmp(new_pwd,re_pwd)!=0)
    {
        printf("\n两 次 输 入 密 码 不 一 致 , 请 重 新 输 入 ！");
        new_usr_info();
        return ;
    }
    fp = fopen("urs_info.txt","a");
    fprintf(fp,"%s %s\n",new_usr,new_pwd);
    fclose(fp);
    printf("\n        注 册 验 证 成 功 !       \n");
    mainmenu_user();
}

//int main()
//{
//    system("color 5E");
//	identify();
//}
