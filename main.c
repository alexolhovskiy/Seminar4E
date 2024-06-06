#include <stdio.h>
#include <stdlib.h>


typedef struct veryLong{
    unsigned int num[100];
    int size;
}veryLong;

veryLong*veryLongCreate(int n){
    veryLong*vl=(veryLong*)malloc(sizeof(veryLong));
    for(int i=0;i<sizeof(vl->num)/sizeof(int);i++){
        vl->num[i]=0;
    }
    vl->size=0;
    while(n>0){
        vl->num[vl->size]=n%10;
        n/=10;
        vl->size++;
    }
    return vl;
}

//int rangeCnt(int num){
//    int cnt=0;
//    while(num>0){
//        num/=10;
//        cnt++;
//    }
//    return cnt;
//}

long long fromVeryLongtoLong(veryLong*vl){
    long long ll=0;
    for(int i=vl->size-1;i>=0;i--){
        ll+=vl->num[i];
        ll*=10;
    }
    ll/=10;
    return ll;
}

veryLong*arrReverse(veryLong*vl){
    int temp=0;
    for(int i=0;i<vl->size/2;i++){
        temp=vl->num[i];
        vl->num[i]=vl->num[vl->size-1-i];
        vl->num[vl->size-1-i]=temp;
    }
    return vl;
}

veryLong*veryLongDev(veryLong*vl,veryLong*vlDev){
    long long n=fromVeryLongtoLong(vlDev);
    veryLong*res=veryLongCreate(0);
    int temp=0;
    int j=0;
    int flag=0;
    for(int i=vl->size-1;i>=0;i--){
        temp+=vl->num[i];
        if(temp>=n){
            res->num[j]=temp/n;
            j++;
            temp%=n;
            flag=1;
        }else{
            if(flag==1){
                res->num[j]=0;
                j++;
            }
        }
        temp*=10;
    }
    res->size=j;
    //printf("Size %d\n",res->size);
    //veryLongPrint(res);
    return arrReverse(res);
}

veryLong*veryLongMult(veryLong*vl1,veryLong*vl2){
    int temp=0,arrSize=0,k=0,j=0;
    arrSize=vl2->size;
    veryLong**arr=(veryLong**)malloc(arrSize);
    for(int l=0;l<arrSize;l++){
        arr[l]=veryLongCreate(0);
    }
    for(int i=0;i<arrSize;i++){
        for(k=0;k<i;k++){
            arr[i]->num[k]=0;
        }
        temp=0;
        for(j=0;j<vl1->size;j++){
            temp+=vl1->num[j]*vl2->num[i];
            arr[i]->num[k+j]=temp%10;
            temp/=10;
        }

        arr[i]->size=k+j;
        if(temp>0){
            arr[i]->num[k+j]=temp;
            arr[i]->size=k+j+1;
        }
    }

    veryLong*vl3=veryLongCreate(0);
    for(int o=0;o<arrSize;o++){
        temp=0;
        int y;
        for(y=0;y<arr[o]->size;y++){
            temp+=vl3->num[y]+arr[o]->num[y];
            vl3->num[y]=temp%10;
            temp/=10;
        }
        vl3->size=y;

        if(temp>0){
            vl3->num[y]=temp;
            vl3->size=y+1;
        }
    }
    return vl3;
}

void veryLongPrint(veryLong*vl){
    for(int i=vl->size-1;i>=0;i--){
        printf("%d",vl->num[i]);
    }
    printf("\n");
}

veryLong*factorial(int start,int end){
    veryLong*vl=veryLongCreate(start);
    for(int i=start+1;i<=end;i++){
        vl=veryLongMult(vl,veryLongCreate(i));
    }
    return vl;
}

//n!/(m!*(n-m)!)
int binom(int n,int m){
    if(n>m){
        if(m>(n-m)){
            printf("Case1\n");
            veryLong*vl1=factorial(m+1,n);
            printf("1 ");veryLongPrint(vl1);
            veryLong*vl2=factorial(1,n-m);
            printf("2 ");veryLongPrint(vl2);
            veryLong*vl3=veryLongDev(vl1,vl2);
            printf("3 ");
            veryLongPrint(vl3);
            long long ll=fromVeryLongtoLong(vl3);
            printf("res %d",ll);
            return (int)ll;
        }else{
            printf("Case2\n");
            veryLong*vl1=factorial(n-m+1,n);
            printf("1 ");veryLongPrint(vl1);
            veryLong*vl2=factorial(1,m);
            printf("2 ");veryLongPrint(vl2);
            veryLong*vl3=veryLongDev(vl1,vl2);
            printf("3 ");
            veryLongPrint(vl3);
            long long ll=fromVeryLongtoLong(vl3);
            printf("res %d",ll);
            return (int)ll;
        }
    }
    return 0;
}


int main()
{
    printf("Hello world!\n");

    //1
    printf("Enter the larger number first and then the smaller one\n");
    int n=0,m=0;
    scanf("%d %d",&n,&m);
    printf("Number of combinations is %d\n",binom(n,m));


    return 0;
}
