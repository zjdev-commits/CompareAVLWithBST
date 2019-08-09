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
clock_t start,stop;                   //clock_t�����������ͣ�������ʱ
double runtime;   //��¼ִ�к������õ�ʱ��


/* ********************************************���ݽṹ*********************************************************** */


typedef struct ElemType{                //������������
	int key;
}ElemType;

typedef struct BSTNode{             //�������������ݽṹ
	ElemType data;                   //����������	
	BSTNode *lchild,*rchild;         //�������Һ���
}BSTNode,*BSTree;

typedef struct AVLNode               //AVL�����ݽṹ
{
	ElemType data;                    //����������
	int bf;                           //����ƽ������
	struct AVLNode *lchild,*rchild;   //�������Һ���
}AVLNode,*AVLTree;



/* ********************************************���ݽṹend********************************************************** */





/* ********************************************�����������㷨********************************************************** */


void InsertBST(BSTree &T,ElemType e ) {       //�ݹ������
	if(!T) {                                      //���Ϊ��ʱ              			
		BSTree S = new BSTNode;                   //��ϵͳ����ռ䣬�����µĽ��  
		S->data = e;                              //��S��������ֵ               
		S->lchild = S->rchild = NULL;             //���Һ�����Ϊ��
		T=S;                                      //���½��S��Ϊ��ǰλ�õĽ��            				
	}
	else if (e.key< T->data.key)                 //��������ȵ�ǰ������С�Ļ�
		InsertBST(T->lchild, e );                 //���½�����������	
	else if (e.key> T->data.key)                 //��������ȵ�ǰ�������Ļ�
		InsertBST(T->rchild, e);	              //���½�����������	
}


BSTree SearchBST(BSTree T,int key) {                       //�����������Ĳ���
	if(!T)        return T;                                      //�����ҵ������ҵĽ��
	if(key==T->data.key)   return T;                             //�ҵ������ҵĽ��
	else if (key<T->data.key)  return SearchBST(T->lchild,key);  //������������
	else return SearchBST(T->rchild,key);                        //������������  		   			
} 

void CreateBST(BSTree &T) {                        //������˳���ÿ�����Ĺؼ��ָ�ֵ�������� InsertBST()
	T=NULL;
	ElemType e;
	int k;
	for(k=0;k<N;k++){ 
		e.key=a[k];                                  //���ΰ�����a�е��������ؼ���
		InsertBST(T, e);                             //�����½��
	}
	cout<<"�����н������\n"<<endl;
	cout<<"\n����������T1�ѽ���!"<<endl;
}


void CreateBST_random(BSTree &T,int* b){        //�������ÿ�����Ĺؼ��ָ�ֵ�������� InsertBST()
	ElemType e;
	int n;
	int k;
	int j;
	T=NULL;
	srand( (unsigned)time( NULL ) );                //srand()����������һ����ǰʱ�俪ʼ��������� 
	for(k=0;k<N;k++){                               //������b����ʵ���������
		n=rand()%N;                                 //rand()������СΪ0~n-1���������Ϊ����a���±�
		b[k]=a[n];                                  //����a�е�����ĵ�n������������b
		
	}
	
	for(j=0;j<N;j++){
		e.key=b[j];                                 //���ΰ�����b�е��������ؼ���
		InsertBST(T, e);                            //�����½��
	}
	cout<<"�����н������\n"<<endl;
	cout<<"����������T3�ѽ���!\n"<<endl;
}




void InOrderTraverse(BSTree &T)                     //�������,���������һ�������Լ�������������
{
	if(T)
	{
		InOrderTraverse(T->lchild);
		cout<<T->data.key<<endl;
		InOrderTraverse(T->rchild);
	}
}
void ProTraverse(BSTree &T)                          //�������������ͬ��
{
	if(T)
	{
		cout<<T->data.key<<endl;
		ProTraverse(T->lchild);
		ProTraverse(T->rchild);
	}
}

/* ********************************************�����������㷨END****************************************************** */





/* ************************************************AVL���㷨********************************************************** */
void R_Rotate(AVLTree &p)                    //�Խ��P������������
{
	AVLNode *lc;                                //�¶���һ�����,��Ϊ���p�����ӵ�ַ�ĸ���
	lc = p->lchild; 
	p->lchild = lc->rchild;                     //���p�����ӵ��Һ��ӽ���p������
	lc->rchild = p;                             //���P���ӽ��p�����ӵ��Һ���
	p=lc;                                       //���p��������Ϊ�µĸ����
	
}
void L_Rotate(AVLTree &p)                   //��������
{
	AVLNode *rc;                                //�¶���һ�����,��Ϊ���p���Һ��ӵ�ַ�ĸ���
	rc=p->rchild;
	p->rchild=rc->lchild;                       //���p���Һ��ӵ����ӽ���p���Һ���
	rc->lchild=p;                               //���P���ӽ��p���Һ��ӵ�����
	p=rc;                                       //���p���Һ�����Ϊ�µĸ����
}

void LeftBalance(AVLTree &T)               //����������ʧ�����
{
	AVLNode *lc,*rd;
	lc=T->lchild;
	switch(lc->bf)                            //���ݸ��������ӵ�ƽ�����ӣ�������Ӧ�Ĵ���
	{
	case LH:                                  //�����������ӵ���������������Ҫ�ߣ�LL�������                             
		R_Rotate(T);                              //��ԭ�����T������������
		T->bf=lc->bf=EH;                          //�޸ĸ����͸��������ӵ�ƽ������ΪEH 
		break;
	case RH:                                  //�����������ӵ���������������Ҫ�ߣ�LR�������
		rd=lc->rchild;
		switch(rd->bf)                            //���ݸ��������ӵ��Һ��ӵ�ƽ�����ӣ��޸�ƽ������ƽ������
		{
		case LH:                                    //���������ӵ��Һ��ӵ��������߹�������ʱ��
			T->bf=RH;lc->bf=EH;break;                    //ƽ���ԭ�����T��ƽ������ΪRH,ԭ�����T�����ӵ�ƽ������ΪEH
		case EH:                                    //���������ӵ��Һ��ӵ���������������ͬ��ʱ��
			T->bf=lc->bf=EH; break;                      //ƽ���ԭ�����T��ԭ�����T�����ӵ�ƽ�����Ӷ�ΪEH   
		case RH:                                    //���������ӵ��Һ��ӵ��������߹�������ʱ��
			T->bf=EH;lc->bf=LH;break;                    //ƽ���ԭ�����T��ƽ������ΪEH,ԭ�����T�����ӵ�ƽ������ΪLH
		}
		rd->bf=EH;                                  //�����������,ƽ����ԭ���������ӵ��Һ��ӵ�ƽ�����Ӷ���EH
		L_Rotate(T->lchild);                        //��ԭ�����T�����ӽ�����������
		R_Rotate(T);                                //��ԭ�����T������������
		break;
	}
}
void RightBalance(AVLTree &T)              //����������ʧ�����
{
	AVLNode *rc,*ld;
	rc=T->rchild;
	switch(rc->bf)                              //���ݸ������Һ��ӵ�ƽ�����ӣ�������Ӧ�Ĵ���
	{
	case LH:                                      //���������Һ��ӵ���������������Ҫ�ߣ�RL������� 
		ld=rc->lchild;
		switch(ld->bf)                                //���ݸ������Һ��ӵ����ӵ�ƽ�����ӣ��޸�ƽ������ƽ������
		{
		case LH:                                        //�������Һ��ӵ����ӵ��������߹�������ʱ��
			T->bf=EH; rc->bf=LH; break;                    //ƽ���ԭ�����T��ƽ������ΪEH,ԭ�����T���Һ��ӵ�ƽ������ΪLH
		case EH:                                        //���������ӵ��Һ��ӵ���������������ͬ��ʱ��
			T->bf=rc->bf=EH; break;                        //ƽ���ԭ�����T��ԭ�����T�����ӵ�ƽ�����Ӷ�ΪEH   
		case RH:                                        //�������Һ��ӵ����ӵ��������߹�������ʱ��
			T->bf=RH;rc->bf=EH; break;                     //ƽ���ԭ�����T��ƽ������ΪRH,ԭ�����T�����ӵ�ƽ������ΪEH
		}
		ld->bf=EH;                                    //�����������,ƽ����ԭ�������Һ��ӵ����ӵ�ƽ�����Ӷ���EH
		R_Rotate(T->rchild);                          //��ԭ�����T���Һ��ӽ�����������
		L_Rotate(T); break;                           //��ԭ�����T������������
	case RH:                                      //���������Һ��ӵ���������������Ҫ�ߣ�RR�������
	    L_Rotate(T);                                  //��ԭ�����T������������
	    T->bf=rc->bf=EH;                             //�޸ĸ����͸������Һ��ӵ�ƽ������ΪEH 

				break;
	}
}


int InsertAVL(AVLTree &T,ElemType e,bool &taller)     //�ݹ������
{
	if(!T)                                             //����ǰָ���㲻���ڵ�ʱ��
	{ 
		T=(AVLTree)malloc(sizeof(AVLNode));              //��ϵͳ����ռ䣬�����µĽ��
		T->data.key=e.key;                               //��Ԫ�ظ�������������
		T->lchild=T->rchild=NULL;                        //���Һ����ÿ�
		T->bf=EH;                                        //��ƽ��������Ϊ0
		taller=true;                                     //Ĭ������״̬��������
	}
	else 
	{
		if(e.key==T->data.key)                         //�����������ֵ�������н���ֵʱ
		{
			taller=false;                                 //����״̬��û�仯
			return 0;                                     //����ʧ��
		}
		if(e.key<T->data.key)                          //�����������ֵС�ڵ�ǰ����ֵʱ
		{ 
			if(!InsertAVL(T->lchild,e,taller))            //�Ѵ���������뵽������
				return 0; 
			if(taller==true)                              //���ɹ�����һ���½���
				switch(T->bf)                             //���ݸ�����ƽ������,�������е���
			{
            case LH:                                       //��ԭ������״̬���������ߵ������
				LeftBalance(T);                               //�����,ʹ��������ʧ��,��Ҫ����LeftBalance()������ƽ�⴦��
				taller=false;                                 //����LeftBalance()����ƽ���ˣ��޸�����״̬Ϊû�仯
				break;          
			case EH:                                       //��ԭ������״̬�����������ȸߵ������ 
				T->bf=LH;                                     //�����,ʹ����������������,�޸ĸ�����ƽ������ΪLH
				taller=true;                                  //�޸�����״̬Ϊ�����
				break;                   
			case RH:                                       //��ԭ������״̬���������ߵ������ 
				T->bf=EH;                                     //�����,ʹ�����������ȸߣ��޸ĸ�����ƽ������ΪEH
				taller=false;                                 //�޸�����״̬Ϊû�仯
				break;
			}
		}
		else                                          //�����������ֵ���ڵ�ǰ����ֵʱ
		{ 
			if(!InsertAVL(T->rchild,e,taller))            //�Ѵ���������뵽������
				return 0;
			if(taller==true)                              //���ɹ�����һ���½���
				switch(T->bf)                             //���ݸ�����ƽ������,�������е���
			{ 
            case LH:                                      //��ԭ������״̬���������ߵ������
				T->bf=EH;                                     //�����,ʹ�����������ȸߣ��޸ĸ�����ƽ������ΪEH                                
				taller=false;                                 //�޸�����״̬Ϊû�仯
				break;
			case EH:                                      //��ԭ������״̬�����������ȸߵ������ 
				T->bf=RH;                                     //�����,ʹ����������������,�޸ĸ�����ƽ������ΪRH
				taller=true;                                  //�޸�����״̬Ϊ����� 
				break;
			case RH:                                       //��ԭ������״̬���������ߵ������
				RightBalance(T);                              //�����,ʹ��������ʧ��,��Ҫ����RightBalance()������ƽ�⴦��
				taller=false;                                 //����RightBalance()����ƽ���ˣ��޸�����״̬Ϊû�仯
				break; 
			}
		}
	}
	return 1;
}
void CreateAVL(AVLTree &T){                        //��ÿ�����Ĺؼ��ָ�ֵ�������� InsertBST()
	bool m; 
	ElemType e;
	int k;
	T=NULL;
	e.key=0;
	for(k=0;k<N;k++){ 
		e.key=a[k];                                    //���ΰ�����a�е��������ؼ���
		InsertAVL(T, e,m);                             //�����½��
	}
	cout<<"�����н������\n"<<endl;
	cout<<"����ƽ����T2�ѽ���!"<<endl;
}


AVLTree SearchAVL(AVLTree T,int key) {             //AVL�����㷨
		
	if(!T) 	return T;
	if(key==T->data.key) return T;     	            	
	else if (key<T->data.key)  return SearchAVL(T->lchild,key);	  //������������
	else return SearchAVL(T->rchild,key);                         //������������ 		   			
} 



void InOrderTraverse_AVL(AVLTree &T)                 //�������,�����Լ�������������
{
	if(T)
	{
		InOrderTraverse_AVL(T->lchild);
		cout<<T->data.key<<endl;
		InOrderTraverse_AVL(T->rchild);
	}
}
void ProTraverse_AVL(AVLTree &T)                     //�������������ͬ��
{
	if(T)
	{
		cout<<T->data.key<<endl;
		ProTraverse_AVL(T->lchild);
		ProTraverse_AVL(T->rchild);
	}
}



/* ************************************************AVL���㷨END****************************************************** */
void show(){
	cout<<"\n***********************************************************************"<<endl;
    cout<<"********************** ��������Ҫ���еĲ���: **************************"<<endl;
	cout<<"***********************************************************************"<<endl;
	cout<<"***************        1:����������T1�Ĵ����Ͳ���      ****************"<<endl;
	cout<<"***************        2:AVL��T2�Ĵ����Ͳ���           ****************"<<endl;
	cout<<"***************        3:����������T3�Ĵ����Ͳ���      ****************"<<endl;
	cout<<"***************        4:���½������ݼ�                ****************"<<endl;
	cout<<"***************        5:�˳�����                      ****************"<<endl;
    cout<<"***********************************************************************"<<endl;
	cout<<"������ѡ�񣺡�"<<endl;
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
	cout<<"ָ�����Ľ����N:"<<endl;
    cin>>N;

    while(N<1000||N>10000)           //�쳣����
	{                                  
		cout<<"�������������Χ�����������벻С��1000�Ҳ�����10000��������N"<<endl;
		cin>>N;
	}

	cout<<"ָ�������ҵĽ����M:"<<endl;
	cin>>M;

	while(M>N)
	{                             //�쳣����
		cout<<"�������������Χ������������С��N��������M"<<endl;
		cin>>M;
	}
    
    cout<<"ָ���㷨�ظ�����k(���鷶Χ��10-500):"<<endl;
	cin>>k;
		while(k<1)
	{                             //�쳣����
		cout<<"kӦ�ǲ�С��1������,����������!"<<endl;
		cin>>k;
	}

	cout<<"Ϊ����T2��T3����ʱ�����0s�����,����T2��T3���ظ�����kΪT1ʱ��100��"<<endl;
    k2=k*100;
	k3=k*100;
    a=new int[N];
	int* b=new int[N];
	
	for(i=0;i<N;i++){
		a[i]=i+1;
	}                            //�������ݼ�
	

	show();
    while(1){
	cin>>s;
    if(s!=1&&s!=2&&s!=3&&s!=4&&s!=5)
		{
			cout<<"���������������������룡"<<endl;
			cin>>s;
		}

	switch(s)
	{
	/**************����������T1�Ĵ����Ͳ���****************/
	case 1:
    BSTree T1;
	CreateBST(T1);               //��������������T1	

    start=clock();               //��T1�ϲ���
	for(l=0;l<k;l++){
	j=N/M-1;
    while(j<N){
		SearchBST(T1,a[j]);
		j=j+N/M;
		
	} 
	}
	stop=clock();
	runtime=((double)stop-start)/CLK_TCK;
	cout<<"����������T1�������!"<<endl;
	cout<<"��T1�ϲ���:"<<endl;
    cout<<"�ظ�����k:"<<k<<endl;
    cout<<"��ʱ�䣺"<<runtime<<"(s)"<<endl;
 	cout<<"ƽ��ʱ�䣺"<<runtime/k<<"(s)\n"<<endl;
	break;



	/****************AVL��T2�Ĵ����Ͳ���******************/
	case 2:
	AVLTree T2;
	CreateAVL(T2);              //����AVL��T2
    
	start=clock();              //��T2�ϲ���
	for(l=0;l<k2;l++){
	j=N/M-1;
    while(j<N){
		SearchAVL(T2,a[j]);
		j=j+N/M;
	} 
	}
	stop=clock();
	runtime=((double)stop-start)/CLK_TCK;
	cout<<"����ƽ����T2�������!"<<endl;
    cout<<"��T2�ϲ���:"<<endl;
    cout<<"�ظ�����k:"<<k2<<endl;
	cout<<"��ʱ�䣺"<<runtime<<"(s)"<<endl;
 	cout<<"ƽ��ʱ�䣺"<<runtime/k2<<"(s)\n"<<endl;
    break;

	/**************����������T3�Ĵ����Ͳ���****************/
	case 3:
	BSTree T3;
	CreateBST_random(T3,b);     //��������������T3
	
	start=clock();              //��T3�ϲ���
	for(l=0;l<k3;l++){
	j=N/M-1;
    while(j<N){
		
		SearchBST(T3,a[j]);
		j=j+N/M;
	} 
	}
	stop=clock();
	runtime=((double)(stop-start))/CLK_TCK;
	cout<<"����������T3�������!\n"<<endl;
	cout<<"��T3�ϲ���:"<<endl;
    cout<<"�ظ�����k:"<<k3<<endl;
	cout<<"��ʱ�䣺"<<runtime<<"(s)"<<endl;
 	cout<<"ƽ��ʱ�䣺"<<runtime/k3<<"(s)\n"<<endl;
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