#include<iostream>
#include <time.h> 
#include <stdlib.h> 
using namespace std;

#define true 1 
#define false 0
#define LH +1
#define EH 0
#define RH -1

bool shorter;
int N;
int* a;
clock_t start,stop;                   //clock_t内置数据类型，用来计时
double runtime;   //记录执行函数所用的时间


/* ********************************************数据结构*********************************************************** */


typedef struct ElemType{                //结点的数据类型
	int key;
}ElemType;

typedef struct BSTNode{             //二叉搜索树数据结构
	ElemType data;                   //结点的数据域	
	BSTNode *lchild,*rchild;         //结点的左右孩子
}BSTNode,*BSTree;

typedef struct AVLNode               //AVL树数据结构
{
	ElemType data;                    //结点的数据域
	int bf;                           //结点的平衡因子
	struct AVLNode *lchild,*rchild;   //结点的左右孩子
}AVLNode,*AVLTree;



/* ********************************************数据结构end********************************************************** */





/* ********************************************二叉搜索树算法********************************************************** */


void InsertBST(BSTree &T,ElemType e ) {       //递归插入结点
	if(!T) {                                      //结点为空时              			
		BSTree S = new BSTNode;                   //向系统申请空间，生成新的结点  
		S->data = e;                              //给S的数据域赋值               
		S->lchild = S->rchild = NULL;             //左右孩子置为空
		T=S;                                      //把新结点S作为当前位置的结点            				
	}
	else if (e.key< T->data.key)                 //待插入结点比当前结点的域小的话
		InsertBST(T->lchild, e );                 //将新结点插入左子树	
	else if (e.key> T->data.key)                 //待插入结点比当前结点的域大的话
		InsertBST(T->rchild, e);	              //将新结点插入右子树	
}


BSTree SearchBST(BSTree T,int key) {                       //二叉搜索树的查找
	if(!T)        return T;                                      //不能找到待查找的结点
	if(key==T->data.key)   return T;                             //找到待查找的结点
	else if (key<T->data.key)  return SearchBST(T->lchild,key);  //在左子树查找
	else return SearchBST(T->rchild,key);                        //在右子树查找  		   			
} 

void CreateBST(BSTree &T) {                        //按递增顺序给每个结点的关键字赋值，并调用 InsertBST()
	T=NULL;
	ElemType e;
	int k;
	for(k=0;k<N;k++){ 
		e.key=a[k];                                  //依次把数组a中的数赋给关键字
		InsertBST(T, e);                             //插入新结点
	}
	cout<<"【运行结果：】\n"<<endl;
	cout<<"\n二叉搜索树T1已建立!"<<endl;
}


void CreateBST_random(BSTree &T,int* b){        //按乱序给每个结点的关键字赋值，并调用 InsertBST()
	ElemType e;
	int n;
	int k;
	int j;
	T=NULL;
	srand( (unsigned)time( NULL ) );                //srand()函数产生以一个当前时间开始的随机种子 
	for(k=0;k<N;k++){                               //让数组b的数实现随机排序
		n=rand()%N;                                 //rand()产生大小为0~n-1的随机数作为数组a的下标
		b[k]=a[n];                                  //数组a中的随机的第n个数赋给数组b
		
	}
	
	for(j=0;j<N;j++){
		e.key=b[j];                                 //依次把数组b中的数赋给关键字
		InsertBST(T, e);                            //插入新结点
	}
	cout<<"【运行结果：】\n"<<endl;
	cout<<"二叉搜索树T3已建立!\n"<<endl;
}




void InOrderTraverse(BSTree &T)                     //中序遍历,与先序遍历一起用来自检树创建的正误
{
	if(T)
	{
		InOrderTraverse(T->lchild);
		cout<<T->data.key<<endl;
		InOrderTraverse(T->rchild);
	}
}
void ProTraverse(BSTree &T)                          //先序遍历，作用同上
{
	if(T)
	{
		cout<<T->data.key<<endl;
		ProTraverse(T->lchild);
		ProTraverse(T->rchild);
	}
}

/* ********************************************二叉搜索树算法END****************************************************** */





/* ************************************************AVL树算法********************************************************** */
void R_Rotate(AVLTree &p)                    //对结点P进行右旋操作
{
	AVLNode *lc;                                //新定义一个结点,作为结点p的左孩子地址的副本
	lc = p->lchild; 
	p->lchild = lc->rchild;                     //结点p的左孩子的右孩子交给p的左孩子
	lc->rchild = p;                             //结点P链接结点p的左孩子的右孩子
	p=lc;                                       //结点p的左孩子作为新的根结点
	
}
void L_Rotate(AVLTree &p)                   //左旋操作
{
	AVLNode *rc;                                //新定义一个结点,作为结点p的右孩子地址的副本
	rc=p->rchild;
	p->rchild=rc->lchild;                       //结点p的右孩子的左孩子交给p的右孩子
	rc->lchild=p;                               //结点P链接结点p的右孩子的左孩子
	p=rc;                                       //结点p的右孩子作为新的根结点
}

void LeftBalance(AVLTree &T)               //处理左子树失衡情况
{
	AVLNode *lc,*rd;
	lc=T->lchild;
	switch(lc->bf)                            //根据根结点的左孩子的平衡因子，做出相应的处理
	{
	case LH:                                  //当根结点的左孩子的左子树比右子树要高（LL情况）：                             
		R_Rotate(T);                              //对原根结点T进行右旋操作
		T->bf=lc->bf=EH;                          //修改根结点和根结点的左孩子的平衡因子为EH 
		break;
	case RH:                                  //当根结点的左孩子的右子树比左子树要高（LR情况）：
		rd=lc->rchild;
		switch(rd->bf)                            //根据根结点的左孩子的右孩子的平衡因子，修改平衡后结点的平衡因子
		{
		case LH:                                    //根结点的左孩子的右孩子的左子树高过右子树时：
			T->bf=RH;lc->bf=EH;break;                    //平衡后，原根结点T的平衡因子为RH,原根结点T的左孩子的平衡因子为EH
		case EH:                                    //根结点的左孩子的右孩子的左子树跟右子树同高时：
			T->bf=lc->bf=EH; break;                      //平衡后，原根结点T跟原根结点T的左孩子的平衡因子都为EH   
		case RH:                                    //根结点的左孩子的右孩子的右子树高过左子树时：
			T->bf=EH;lc->bf=LH;break;                    //平衡后，原根结点T的平衡因子为EH,原根结点T的左孩子的平衡因子为LH
		}
		rd->bf=EH;                                  //无论哪种情况,平衡后的原根结点的左孩子的右孩子的平衡因子都是EH
		L_Rotate(T->lchild);                        //对原根结点T的左孩子进行左旋操作
		R_Rotate(T);                                //对原根结点T进行右旋操作
		break;
	}
}
void RightBalance(AVLTree &T)              //处理右子树失衡情况
{
	AVLNode *rc,*ld;
	rc=T->rchild;
	switch(rc->bf)                              //根据根结点的右孩子的平衡因子，做出相应的处理
	{
	case LH:                                      //当根结点的右孩子的左子树比右子树要高（RL情况）： 
		ld=rc->lchild;
		switch(ld->bf)                                //根据根结点的右孩子的左孩子的平衡因子，修改平衡后结点的平衡因子
		{
		case LH:                                        //根结点的右孩子的左孩子的左子树高过右子树时：
			T->bf=EH; rc->bf=LH; break;                    //平衡后，原根结点T的平衡因子为EH,原根结点T的右孩子的平衡因子为LH
		case EH:                                        //根结点的左孩子的右孩子的左子树跟右子树同高时：
			T->bf=rc->bf=EH; break;                        //平衡后，原根结点T跟原根结点T的左孩子的平衡因子都为EH   
		case RH:                                        //根结点的右孩子的左孩子的右子树高过左子树时：
			T->bf=RH;rc->bf=EH; break;                     //平衡后，原根结点T的平衡因子为RH,原根结点T的左孩子的平衡因子为EH
		}
		ld->bf=EH;                                    //无论哪种情况,平衡后的原根结点的右孩子的左孩子的平衡因子都是EH
		R_Rotate(T->rchild);                          //对原根结点T的右孩子进行右旋操作
		L_Rotate(T); break;                           //对原根结点T进行左旋操作
	case RH:                                      //当根结点的右孩子的右子树比左子树要高（RR情况）：
	    L_Rotate(T);                                  //对原根结点T进行左旋操作
	    T->bf=rc->bf=EH;                             //修改根结点和根结点的右孩子的平衡因子为EH 

				break;
	}
}


int InsertAVL(AVLTree &T,ElemType e,bool &taller)     //递归插入结点
{
	if(!T)                                             //当当前指向结点不存在的时候
	{ 
		T=(AVLTree)malloc(sizeof(AVLNode));              //向系统申请空间，生成新的结点
		T->data.key=e.key;                               //把元素赋给结点的数据域
		T->lchild=T->rchild=NULL;                        //左右孩子置空
		T->bf=EH;                                        //把平衡因子置为0
		taller=true;                                     //默认树的状态：长高了
	}
	else 
	{
		if(e.key==T->data.key)                         //当待插入结点的值等于已有结点的值时
		{
			taller=false;                                 //树的状态：没变化
			return 0;                                     //插入失败
		}
		if(e.key<T->data.key)                          //当待插入结点的值小于当前结点的值时
		{ 
			if(!InsertAVL(T->lchild,e,taller))            //把待插入结点插入到左子树
				return 0; 
			if(taller==true)                              //当成功插入一个新结点后
				switch(T->bf)                             //根据根结点的平衡因子,对树进行调整
			{
            case LH:                                       //当原本树的状态是左子树高的情况：
				LeftBalance(T);                               //插入后,使得左子树失衡,需要调用LeftBalance()进行左平衡处理
				taller=false;                                 //调用LeftBalance()后，树平衡了，修改树的状态为没变化
				break;          
			case EH:                                       //当原本树的状态是左右子树等高的情况： 
				T->bf=LH;                                     //插入后,使得树的左子树高了,修改根结点的平衡因子为LH
				taller=true;                                  //修改树的状态为变高了
				break;                   
			case RH:                                       //当原本树的状态是右子树高的情况： 
				T->bf=EH;                                     //插入后,使得左右子树等高，修改根结点的平衡因子为EH
				taller=false;                                 //修改树的状态为没变化
				break;
			}
		}
		else                                          //当待插入结点的值大于当前结点的值时
		{ 
			if(!InsertAVL(T->rchild,e,taller))            //把待插入结点插入到右子树
				return 0;
			if(taller==true)                              //当成功插入一个新结点后
				switch(T->bf)                             //根据根结点的平衡因子,对树进行调整
			{ 
            case LH:                                      //当原本树的状态是左子树高的情况：
				T->bf=EH;                                     //插入后,使得左右子树等高，修改根结点的平衡因子为EH                                
				taller=false;                                 //修改树的状态为没变化
				break;
			case EH:                                      //当原本树的状态是左右子树等高的情况： 
				T->bf=RH;                                     //插入后,使得树的右子树高了,修改根结点的平衡因子为RH
				taller=true;                                  //修改树的状态为变高了 
				break;
			case RH:                                       //当原本树的状态是右子树高的情况：
				RightBalance(T);                              //插入后,使得右子树失衡,需要调用RightBalance()进行右平衡处理
				taller=false;                                 //调用RightBalance()后，树平衡了，修改树的状态为没变化
				break; 
			}
		}
	}
	return 1;
}
void CreateAVL(AVLTree &T){                        //给每个结点的关键字赋值，并调用 InsertBST()
	bool m; 
	ElemType e;
	int k;
	T=NULL;
	e.key=0;
	for(k=0;k<N;k++){ 
		e.key=a[k];                                    //依次把数组a中的数赋给关键字
		InsertAVL(T, e,m);                             //插入新结点
	}
	cout<<"【运行结果：】\n"<<endl;
	cout<<"二叉平衡树T2已建立!"<<endl;
}


AVLTree SearchAVL(AVLTree T,int key) {             //AVL查找算法
		
	if(!T) 	return T;
	if(key==T->data.key) return T;     	            	
	else if (key<T->data.key)  return SearchAVL(T->lchild,key);	  //在左子树查找
	else return SearchAVL(T->rchild,key);                         //在右子树查找 		   			
} 



void InOrderTraverse_AVL(AVLTree &T)                 //中序遍历,用来自检树创建的正误
{
	if(T)
	{
		InOrderTraverse_AVL(T->lchild);
		cout<<T->data.key<<endl;
		InOrderTraverse_AVL(T->rchild);
	}
}
void ProTraverse_AVL(AVLTree &T)                     //先序遍历，作用同上
{
	if(T)
	{
		cout<<T->data.key<<endl;
		ProTraverse_AVL(T->lchild);
		ProTraverse_AVL(T->rchild);
	}
}



/* ************************************************AVL树算法END****************************************************** */
void show(){
	cout<<"\n***********************************************************************"<<endl;
    cout<<"********************** 请输入你要进行的操作: **************************"<<endl;
	cout<<"***********************************************************************"<<endl;
	cout<<"***************        1:二叉搜索树T1的创建和查找      ****************"<<endl;
	cout<<"***************        2:AVL树T2的创建和查找           ****************"<<endl;
	cout<<"***************        3:二叉搜索树T3的创建和查找      ****************"<<endl;
	cout<<"***************        4:重新建立数据集                ****************"<<endl;
	cout<<"***************        5:退出程序                      ****************"<<endl;
    cout<<"***********************************************************************"<<endl;
	cout<<"【您的选择：】"<<endl;
}


int main()
{   
	done:
	int M;
	int j;
	int i;
	int k,k2,k3;
	int l;
	int s;
	cout<<"指定树的结点数N:"<<endl;
    cin>>N;

    while(N<1000||N>10000)           //异常处理
	{                                  
		cout<<"输入的数超出范围！请重新输入不小于1000且不大于10000的整型数N"<<endl;
		cin>>N;
	}

	cout<<"指定待查找的结点数M:"<<endl;
	cin>>M;

	while(M>N)
	{                             //异常处理
		cout<<"输入的数超出范围！请重新输入小于N的整型数M"<<endl;
		cin>>M;
	}
    
    cout<<"指定算法重复次数k(建议范围：10-500):"<<endl;
	cin>>k;
		while(k<1)
	{                             //异常处理
		cout<<"k应是不小于1的整数,请重新输入!"<<endl;
		cin>>k;
	}

	cout<<"为避免T2，T3查找时间出现0s的情况,设置T2和T3的重复次数k为T1时的100倍"<<endl;
    k2=k*100;
	k3=k*100;
    a=new int[N];
	int* b=new int[N];
	
	for(i=0;i<N;i++){
		a[i]=i+1;
	}                            //生成数据集
	

	show();
    while(1){
	cin>>s;
    if(s!=1&&s!=2&&s!=3&&s!=4&&s!=5)
		{
			cout<<"您的输入有误，请重新输入！"<<endl;
			cin>>s;
		}

	switch(s)
	{
	/**************二叉搜索树T1的创建和查找****************/
	case 1:
    BSTree T1;
	CreateBST(T1);               //创建二叉搜索树T1	

    start=clock();               //在T1上查找
	for(l=0;l<k;l++){
	j=N/M-1;
    while(j<N){
		SearchBST(T1,a[j]);
		j=j+N/M;
		
	} 
	}
	stop=clock();
	runtime=((double)stop-start)/CLK_TCK;
	cout<<"二叉搜索树T1查找完毕!"<<endl;
	cout<<"在T1上查找:"<<endl;
    cout<<"重复次数k:"<<k<<endl;
    cout<<"总时间："<<runtime<<"(s)"<<endl;
 	cout<<"平均时间："<<runtime/k<<"(s)\n"<<endl;
	break;



	/****************AVL树T2的创建和查找******************/
	case 2:
	AVLTree T2;
	CreateAVL(T2);              //创建AVL树T2
    
	start=clock();              //在T2上查找
	for(l=0;l<k2;l++){
	j=N/M-1;
    while(j<N){
		SearchAVL(T2,a[j]);
		j=j+N/M;
	} 
	}
	stop=clock();
	runtime=((double)stop-start)/CLK_TCK;
	cout<<"二叉平衡树T2查找完毕!"<<endl;
    cout<<"在T2上查找:"<<endl;
    cout<<"重复次数k:"<<k2<<endl;
	cout<<"总时间："<<runtime<<"(s)"<<endl;
 	cout<<"平均时间："<<runtime/k2<<"(s)\n"<<endl;
    break;

	/**************二叉搜索树T3的创建和查找****************/
	case 3:
	BSTree T3;
	CreateBST_random(T3,b);     //创建二叉搜索树T3
	
	start=clock();              //在T3上查找
	for(l=0;l<k3;l++){
	j=N/M-1;
    while(j<N){
		
		SearchBST(T3,a[j]);
		j=j+N/M;
	} 
	}
	stop=clock();
	runtime=((double)(stop-start))/CLK_TCK;
	cout<<"二叉搜索树T3查找完毕!\n"<<endl;
	cout<<"在T3上查找:"<<endl;
    cout<<"重复次数k:"<<k3<<endl;
	cout<<"总时间："<<runtime<<"(s)"<<endl;
 	cout<<"平均时间："<<runtime/k3<<"(s)\n"<<endl;
    break;

	case 4:
	    goto done;
		break;
		
	case 5:
		exit(0);
		break;

	}
	show();
	}
    system("pause"); 
	return 0;
}