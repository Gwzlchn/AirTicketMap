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
	printf("\t\t*\t\t\t��ӭʹ�÷ɻ���Ʊϵͳ\t\t\t*");
	printf("\n\t\t*****************************************************************\n");
	printf("\t\t*\t\t\t��ѡ���½ͨ����\t\t\t*\n");
	printf("\t\t*\t\t\t1:����Աͨ��\t\t\t\t*\n");
	printf("\t\t*\t\t\t2:�û�ͨ��\t\t\t\t*\n");
	printf("\t\t*\t\t\t0:�˳��ɻ���Ʊϵͳ\t\t\t*\n");
	printf("\t\t*****************************************************************\n");
	while(1)
	{
		printf("\n\t\t\t\t����������ѡ�񡫣�");
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
			printf("\n����������(ѡ��1����2)\n");
        }
			if(choi==0)
			{
				printf("��������������Ҫ�˳�ϵͳ������ӭ�´�ʹ�á�");
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
		printf("\n\n\t\t\t\t�û�����admin\n");
		printf("\t\t\t\t�� �룺");
		scanf("%s",admin_pwd);
		fscanf(fp,"%s",admin_p);
        if(strcmp(admin_p,admin_pwd)==0)
        {
            printf("\n\t\t\t�� �� �� ֤ �� �� !\t\t\t\n");
            break;
        }
        else
        {
        	printf("\n�������%d�Σ�\n",cnt);
        	cnt++;
        	if(cnt==4)
        	{
        		printf("\n\t\t\t\t���������ˣ�\n");
        		printf("\n\t\t\t\t0.����������\n");
        		printf("\n\t\t\t\t1.�Ҳ�֪������\n");
        		printf("\n\t\t\t\t2.��Ҫ��������\n");
        		while(1)
				{
					printf("\n\t\t\t\t����������ѡ�񡫣�");
					scanf("%d",&choi);
					if(choi == 0)
					{
						cnt=1;
						identify_admin();
						break;
					}
					else if (choi == 1)
					{
						printf("\n�ܺ��Ӳ�֪�����뻹����½����Աͨ��...\n�ף��ҽ��Զ�Ϊ����ת�û�ͨ����\n");
						identify_user();
						break;
					}
					else if(choi == 2)
					{
						printf("\n������������֤�룺");
						int yzm;
						scanf("%d",&yzm);
						if(yzm == 159)
						{
							printf("\n��֤�ɹ����������������룺");
							scanf("%s",admin_new_pwd);
							printf("\n�ظ�����:");
    						scanf("%s",admin_re_pwd);
    						if(strcmp(admin_new_pwd,admin_re_pwd)!=0)
						    {
						        printf("\n�� �� �� �� �� �� �� һ �� , �� �� �� �� ��");
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
						printf("\n���������롫��\n");
						if(choi==159)
						{
							printf("��������������Ҫ�˳�ϵͳ������ӭ�´�ʹ�á�");
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
    printf("\t\t\t\t\t\t�� ӭ ʹ �� �� �� �� Ʊ ϵ ͳ \n");
    printf("\n\n\n\n\n");
    while(1)
    {
		printf("\n\t\t\t\t1.�������˺�\n\t\t\t\t0.���û�ע��\n");
		printf("\n\t\t\t\t����������ѡ��\n");
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
			printf("\n���������롫��\n");
			if(result==159)
			{
				printf("��������������Ҫ�˳�ϵͳ������ӭ�´�ʹ�á�");
				exit(0);
				break;
			}
		}
	}
	printf("\t\t\t\t�û�����");
	scanf("%s",usr);
	printf("\n\n\n");
	printf("\t\t\t\t��  �룺");
	scanf("%s",pwd);
	fflush(stdin);
	while(fscanf(fp,"%s%s",u,p)!=EOF)
	{
		if(strcmp(u,usr)==0 && strcmp(p,pwd)==0)
		{
		    printf("\n\t\t\t�� �� �� ֤ �� �� !\t\t\t\n");
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

void new_usr_info()              ///   ע�����û�
{
    char new_usr[N],new_pwd[N],re_pwd[N];
    FILE *fp;
    int cnt = 0,result = 0;
    printf("\n\n\t\t\t\t\t\t\t�� �� �� ע �� �� �� \n\n");
    printf("\t\t\t\t�û�����");
    scanf("%s",new_usr);
    printf("\n\n\t\t\t\t��  �룺");
    scanf("%s",new_pwd);
    printf("\n\n\t     \t\t\t�ظ�����:");
    scanf("%s",re_pwd);
    if(strcmp(new_pwd,re_pwd)!=0)
    {
        printf("\n�� �� �� �� �� �� �� һ �� , �� �� �� �� �� ��");
        new_usr_info();
        return ;
    }
    fp = fopen("urs_info.txt","a");
    fprintf(fp,"%s %s\n",new_usr,new_pwd);
    fclose(fp);
    printf("\n        ע �� �� ֤ �� �� !       \n");
    mainmenu_user();
}

int main()
{
    system("color 5E");
	identify();
}
