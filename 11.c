#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Singer{
    int num;  //选手编号
    char name[20]; //选手名称
    double sumScore ;    //选手总成绩
    double averScore;    //选手平均分
    struct Singer* next; //指针域
};

struct Singer* singer_Information(int n){      //本函数读入选手编号和姓名，使用链表进行存储
    struct Singer* head,*p,*q; 
    head=NULL;//头指针置空
    int i;// 计数变量
    for(i=1;i<=n;i++)
    {
        p=(struct Singer*)malloc(sizeof(struct Singer));   //创建当前结构体指针
        printf("请输入第%d位学生编号及姓名：(空格隔开)",i);	
        scanf("%d%s",&p->num,&p->name);  fflush(stdin);//此语句用来清空缓存区，如果输入多余的东西，自动舍弃
        p->averScore=-1.0;   //平均分不可能为负数，用此来标志用户是否输入选手分数，假如未输，无法进行排序或查询
        p->next=NULL;
        if(head==NULL) head=p; //如果head指针为空，即将它指向当前创建的指针p，同时让q也指向它p，
        else        q->next=p;// 否则让当前创建的指针p被q->next指向,而q就是上次创建的p
        q=p;
    }
    return head;  //将头指针返回到主函数
}

void singer_Score(struct Singer* head){     //此函数用来读取评委打分
    double arr[10];  //存储10个评委的给分
    int i,j;  //计数变量
    struct Singer* t;
    t=head;  //链表的头指针
    if(t==NULL ) puts("没有选手数据被输入，请先按1输入选手数据，再进行打分"); //没有选手数据被输入时，提醒先按1输入选手数据，再进行打分
    while(t != NULL ){    //直到t->next为NULL时停止
        printf("请输入编号为%d的学生的评委得分,共10个，请用空格隔开：",t->num);
        for( i=0;i<10;i++) scanf("%lf",&arr[i]);    fflush(stdin);//此语句用来清空缓存区，如果输入多个10的数，自动舍弃
        /*此处使用冒泡排序*/
        for( i=0;i<10;i++)
         for( j=1;j<10-i;j++)
                  if(arr[j]<arr[j-1])
                  {
                      int t=arr[j];arr[j]=arr[j-1];arr[j-1]=t;
                  }  
       //计算总分数和平均分数(去掉最高和最低)
        double sum=0.0;
        for( i=0;i<10;i++) sum+=arr[i];
        t->sumScore=sum;
        double aver=0.0;       
        for( i=1;i<9;i++) aver+=arr[i];
        t->averScore=aver/8.0;

        t=t->next;  //指向下一个节点
    }
}



void singer_Sort(struct Singer* head){     //此函数用于排序
   struct Singer *t,*t1,*t2;
   t=head;  
   if(t==NULL ||  t->averScore==-1.0) {puts("选手数据输入不完整，请先按1或2输入选手数据，再进行排序,");   return;}
   //没有选手数据被输入时，提醒先按1输入选手数据，再进行打分，或者averScore为负数时，代表使用者未输入分数，应先输入2
       t2=NULL;
       while(t2!=head){
        t1=t;
       while(t1->next!=t2){
           if(t1->averScore < t1->next->averScore)
           {
               int num1=t1->num; t1->num=t1->next->num;t1->next->num=num1;
               char name1[20];strcpy(name1,t1->name);strcpy(t1->name,t1->next->name);strcpy(t1->next->name,name1);
               double sumScore1=t1->sumScore;t1->sumScore=t1->next->sumScore;t1->next->sumScore=sumScore1;
               double averScore1=t1->averScore;t1->averScore=t1->next->averScore;t1->next->averScore=averScore1;
           }
             t1=t1->next;
        } 
       t2=t1; 
    }  
}



void singer_Search(struct Singer* head){  //简单的链表遍历，用编号查询
    struct Singer *t ;
    t=head;
    if(t==NULL ||  t->averScore==-1.0) {puts("选手数据输入不完整，请先按1或2将选手数据输完整，再进行查询,");   return;}
    //没有选手数据被输入时，提醒先按1输入选手数据，再进行打分，或者averScore为负数时，代表使用者未输入分数，应先输入2
    int search;
    int target=0; 
    printf("请输入要查询同学的编号：");
    scanf("%d",&search);
    while(t!=NULL)
    {
        if(t->num==search){
            printf("编号\t姓名\t总成绩\t平均分\n");
            printf("%d\t%s\t%.4f\t%.4f\n",t->num,t->name,t->sumScore,t->averScore);
            target=1;
        }
        t=t->next;
    }
    if(!target)
    printf("未查询到此同学");
}

void singer_Add(struct Singer* head){ //此函数用来追加数据
    int n;  //存储此次追加的个数
    struct Singer*t,*p,*q;
    t=head;
    if(t==NULL ) {puts("你是否从来没输入过选手数据，请先按1和2输入选手数据，再进行添加数据");return;}
    while(t->next!=NULL) t=t->next;//使链表来到尾节点     
    printf("请输入此次要追加选手的个数：");
    scanf("%d",&n);
    int i;  //计数变量
    for(i=1;i<=n;i++)
    {
        p=(struct Singer*)malloc(sizeof(struct Singer));
        printf("请输入第%d位学生编号及姓名：(空格隔开)",i);	
        scanf("%d%s",&p->num,&p->name);  fflush(stdin);//此语句用来清空缓存区，如果输入多余的东西，自动舍弃
        p->next=NULL;
        if(t->next==NULL) t->next=p;  //用来在尾节点添加节点
        else q->next=p;
        q=p;  
    }
     singer_Score(t->next);//将添加的节点 传入 ，并读取分数
}

void singer_Save(struct Singer* head){
    if(head==NULL) puts("未输入数据");
    FILE* pf;
    pf=fopen("数据.txt","w+");
    struct Singer*t;
    t=head;
    singer_Sort(t);
    fprintf(pf,"排名\t编号\t姓名\t总成绩\t平均分\n");
    int q=1;
    while(t!=NULL){
        fprintf(pf,"%d\t%d\t%s\t%.4f\t%.4f\n",q,t->num,t->name,t->sumScore,t->averScore);
        q++;
        t=t->next;
    }
    fclose(pf);
    printf("已按照平均分排序保存在当前目录中\n");

}

int main()
{
    puts("         歌手管理系统              ");
    puts("***********************************");
    puts("       1)输入选手数据              ");
    puts("       2)评委打分                  ");
    puts("       3)成绩排序(按平均分)         ");
    puts("       4)数据查询                  ");
    puts("       5)追加学生数据              ");
    puts("       6)写入数据文件              ");
    puts("       7)退出系统                  ");
    puts("**********************************");
    int choice; //保存输入的选项
    int flag=1;  //标志变量，使输入7时能顺利退出系统
    struct Singer *head; // 用来接收头指针
    head=NULL; //头指针置空
    int n;   //  保存选手个数(没进行追加学生数据时)

    while(flag)
    {
         printf("\n请输入数字选择你想要的操作:");
         scanf("%d",&choice);
         switch(choice)
        {
			case 1:
                printf("请输入选手个数：");
                scanf("%d",&n);
                head=singer_Information(n);
                /*struct Singer *t;
                t=head;
                while(t!=NULL){
                    printf("%d %s",t->num,t->name);
                    t=t->next;
                }
            */
				break;
			case 2:
                singer_Score(head);
                break;
			case 3:
				singer_Sort(head);
                struct Singer*t;
                t=head;
                printf("\t成绩排序(按平均分)：\n");
                printf("排名\t编号\t姓名\t总成绩\t平均分\n"); 
                int q=1;  //存取排名值
                while(t!=NULL){
                printf("%d\t%d\t%s\t%.4f\t%.4f\n",q,t->num,t->name,t->sumScore,t->averScore);
                q++;
                t=t->next;
                }
                break;
			case 4:
                singer_Search(head);	
				break;
			case 5:
                singer_Add(head);
				break;
			case 6:
                singer_Save(head);	
				break;
			case 7:
				flag=0;//while条件为假，退出系统
				break;
			default:
				printf(" \n请输入正确的数字\n");
                continue; //当输入的值不为正确的值时，能结束本次循环，进入下次循环
		}
 }
        return 0;
}
