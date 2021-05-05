#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

int main(){
    srand((unsigned)time(NULL));
    float x;
    float slope;
    float random = 0;
    int number;
    int  a = 10;
    float v = a;
    int choosed;
    float *possib = (float*)calloc(10,sizeof(float));

    x = 2/(v-1);
    slope = -(x)/v;

    printf("x = %f\n",x);
    printf("a = %f\n",slope);

    for(int i = 0; i<v;i++){
        possib[i]=(i+1)*slope+x;
        random = random + possib[i];
        printf("当前poss %d 的概率为 %f\n",i,possib[i]);
    }
    float count = 0;
    for(int i = 0; i<a;i++){
        possib[i]=count + possib[i]*1000000;
        count =possib[i];
        printf("当前poss %d 的概率为 %f\n",i,possib[i]);
    }
    possib[a-1] = possib[a-1] + 100;
    printf("当前poss %d 的概率为 %f\n",a-1,possib[a-1]);
    printf("random = %f",random);
    int *counter = (int*)calloc(a,sizeof(int));
    for(int i = 0; i<10000;i++){
        number=rand()%1000100;
        for(int j = 0;j<a;j++){
            if(number<=possib[j]){
                counter[j]++;
                break;
            }
        }
    }
    for(int i = 0;i<a;i++){
        printf("顶点的%d 生成概率为%d\n ",i,counter[i]);
    }
    printf("done;");
    return 0;

}