//至多只允许四位哲学家同时去拿左筷子，如果有四位哲学家拿到了筷子，则所有哲学家都饿了，不能进餐
#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
int chops[5]={0};//5只筷子的状态
int phil[5]={1,2,3,4,5};//5位哲学家
void *philos(void *);
int main()
{
	srand(time(NULL));
	int i;
	pthread_t  pthnum[5];//5个线程，5位哲学家
	void *stat;//线程返回值
	for(i=0;i<5;i++)
		if(pthread_create(&pthnum[i],NULL,philos,(void *)&phil[i])==-1)//创建线程
		{
			printf("creat error!\n");
			exit(1);
		}
	for(i=0;i<5;i++)
		if(pthread_join(pthnum[i],(void **)&stat)==-1)//等待线程结束
		{
			printf("pthread-join  error!\n");
			exit(1);
		}
	return 0;
}
void *philos(void *arg)//arg为哲学家编号的地址
{
	int m=*(int *)arg;//哲学家编号
	int left=m,right=(m+1)%5;
	while(1)
	{
		printf("哲学家%d正在思考问题\n",m);
		sleep(rand()%5);//思考时间,随机
		printf("哲学家%d饿了\n",m);
		while(1)//判断是否有4位哲学家拿到了筷子,sum为拿到筷子的哲学家数,如果有4位哲学家拿到了筷子，则所有哲学家都饿了，不能进餐
		{
			int sum=chops[0]+chops[1]+chops[2]+chops[3]+chops[4];
			if(sum<4)//如果sum<4,则有哲学家没有拿到筷子，可以进餐
				break;
		}
		while(chops[left]==1);//判断左筷子是否被拿起
		chops[left]==1;//拿起左筷子
		printf("哲学家%d拿起了%d号筷子,现在只有一只筷子，不能进餐\n",m,left);
		while(chops[right]==1);//判断右筷子是否被拿起
		chops[right]=1;//拿起右筷子
		printf("\033[0;45;47m哲学家%d拿起了%d号筷子，现在有两只筷子，开始进餐\033[0m\n",m,right);
		sleep(rand()%3);//进餐时间,随机
		printf("\033[0;33;47m哲学家%d进餐完毕\033[0m\n",m);
		//进餐完毕，放下左右筷子
		chops[left]=0;
		printf("哲学家%d放下了%d号筷子\n",m,left);
		chops[right]=0;
		printf("哲学家%d放下了%d号筷子\n",m,right);
	}
}
