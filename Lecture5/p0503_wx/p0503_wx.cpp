#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#define N 100
// #define M 2*N-1
#define M (2*N-1)

typedef struct{
    int weight;
    int parent;
    int LChild;
    int RChild;
}HTNode,HuffmanTree[M+1];

typedef char * HuffmanCode[N+1];

int Min(HuffmanTree ht,int i){
    int j,flag=0;
    int k=2147483647;
    for(j=1;j<=i;j++){
        if(ht[j].weight<k&&ht[j].parent==0){
            k=ht[j].weight;
            flag=j;
        }
    }
    ht[flag].parent=1;
    return flag;
}

void Select(HuffmanTree ht,int i,int *s1,int *s2){
    int j;
    *s1=Min(ht,i);
    *s2=Min(ht,i);
    if(s1>s2){
        j=*s1;
        *s1=*s2;
        *s2=j;
    }
}

void CrtHuffmanTree(HuffmanTree ht,int w[],int n){
    int i,s1,s2,m;
    for(i=1;i<=n;i++){
        ht[i].weight=w[i];
        ht[i].parent=0;
        ht[i].LChild=0;
        ht[i].RChild=0;
    }
    m=2*n-1;
    for(i=n+1;i<=m;i++){
        ht[i].weight=0;
        ht[i].parent=0;
        ht[i].LChild=0;
        ht[i].RChild=0;
    }
    for(i=n+1;i<=m;i++){
        Select(ht,i-1,&s1,&s2);
        ht[i].weight=ht[s1].weight+ht[s2].weight;
        ht[s1].parent=i;
        ht[s2].parent=i;
        ht[i].LChild=s1;
        ht[i].RChild=s2;
    }
}

void CrtHuffmanCode(HuffmanTree ht,HuffmanCode hc,int n){
    char *cd;
    int i,start,c,p;
    cd=(char *)malloc(n *sizeof(char));
    cd[n-1]='\0';
    for(i=1;i<=n;i++){
        start=n-1;
        c=i;p=ht[i].parent;
        while(p!=0){
            --start;
            if(ht[p].LChild==c)
                cd[start]='1';
            else
                cd[start]='0';
                
    free(cd);
}

int main(){
	freopen("p0503.in", "r", stdin);
    int i,n;
    scanf("%d",&n);
    int w[n+1];
    for(i=1;i<=n;i++){
        scanf("%d",&w[i]);
    }
    HuffmanTree ht;
    HuffmanCode hc;
    CrtHuffmanTree(ht,w,n);
    CrtHuffmanCode(ht,hc,n);
    for(i=1;i<=n;i++){
        printf("%s\n",hc[i]);
    }
    return 0;
}

