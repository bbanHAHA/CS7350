#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
int *s;
unsigned short xsub1[3];
typedef struct ANode
{
    int vertex;
    struct ANode *next;
} ANode, *PANode; //define Edge connected vertex (边表)

typedef struct VNode
{
    int vertex;
    int degree;
    PANode first;
} VNode, *PVNode; //difine vertex (顶点表)

typedef struct Graph
{
    PVNode p;
    int vexnum;
    int edgenum;
} Graph, *PGraph; // graph

void creatgraph(PGraph g, int v)
{
    g->p = (VNode *)calloc(v, sizeof(VNode));
    for (int i = 0; i < v; i++)
    {
        g->p[i].vertex = i;
        g->p[i].first = NULL;
        g->p[i].degree = 0;
    }
    g->vexnum = v;
    g->edgenum = 0;
}
//create  and initialize the graph

void addedge(PGraph g, int from, int to)
{
    PANode a, b;
    int isneed = 1;
    int succ = 0;
    b = g->p[from].first;
    if (from != to)
    {
        while (b)
        {
            if (b->vertex == to)
            {
                printf("插入失败\n");
                isneed = 0;
            }
            b = b->next;
        }
        if (isneed == 1)
        {
            a = (PANode)malloc(sizeof(ANode));
            a->next = NULL;
            a->vertex = to;
            a->next = g->p[from].first;
            g->p[from].first = a;
            g->p[from].degree++;
            printf("插入---<%d><%d>----------", from, to);
            succ++;
        }

        isneed = 1;
        b = g->p[to].first;
        while (b)
        {
            if (b->vertex == from)
            {
                printf("插入失败\n");
                isneed = 0;
            }
            b = b->next;
        }
        if (isneed == 1)
        {
            a = (PANode)malloc(sizeof(ANode));
            a->next = NULL;
            a->vertex = from;
            a->next = g->p[to].first;
            g->p[to].first = a;
            g->p[to].degree++;
            printf("---------<%d><%d>---成功\n", to, from);
            succ++;
        }
        if (succ == 2)
        {
            g->edgenum++;
        }
    }
    else
    {
        printf("插入失败\n");
    }
}

void completegraph(PGraph g)
{
    for (int i = 0; i < g->vexnum; i++)
    {
        for (int j = 0; j < g->vexnum; j++)
        {
            if (i == j)
            {
                continue;
            }
            else
            {
                addedge(g, i, j);
            }
        }
    }
}

void out(PGraph g)
{
    printf("%d\t\t# 0th value = Number of vertices\n", g->vexnum);
    int count = 1;
    for (int i = 0; i < g->vexnum; i++)
    {
        PANode a = g->p[i].first;
        if (a != NULL)
        {
            s[i] = count;
        }
        while (a != NULL)
        {

            printf("%d\t\t# %dth value = Vertex %d is adjacent to Vertex %d\n", g->p[i].vertex, count, i, a->vertex);
            a = a->next;
            count++;
        }
    }
    for (int i = 0; i < g->vexnum; i++)
    {
        if (s[i] != 0)
        {
            printf("%d\t\t# %dth value = starting location for vertex %d’s edges\n", s[i], count, i);
            count++;
        }
    }
}

void circle(PGraph g)
{
    for (int i = 0; i < g->vexnum; i++)
    {
        int j = i + 1;
        if (j == (g->vexnum))
        {
            j = 0;
        }
        addedge(g, i, j);
    }
}

int isedge(PGraph g, int from, int to)
{
    PANode a, b;
    b = g->p[from].first;
    while (b)
    {
        if (b->vertex == to)
        {
            printf("边存在 %d %d \n", from, to);
            return 1;
        }
        b = b->next;
    }
    printf("边不存在 %d %d \n", from, to);
    return 0;
}
int edgenum(PGraph g, int from)
{
    PANode a, b;
    b = g->p[from].first;
    int number = 0;
    while (b)
    {
        if (b != NULL)
        {
            number++;
        }
        b = b->next;
    }
    return number;
}

void uniform(PGraph g, int e)
{
    int i;
    int p;
    for (int j = 0; j < e; j++)
    {
        while (1)
        {
            i = rand() % (g->vexnum);
            while (1)
            {
                p = rand() % (g->vexnum);
                if (i != p)
                {
                    break;
                }
            }
            if (isedge(g, i, p) == 0)
            {
                break;
            }
            //sleep(1);
        }
        addedge(g, i, p);
        //sleep(1);
    }
}

int skewvertex(int a)
{
    float x;
    float slope;
    float random = 0;
    int number;
    float v = a;
    int choosed;
    int value = 0;
    float *possib = (float *)calloc(a, sizeof(float));

    x = 2 / (v - 1);
    slope = -(x) / v;

    for (int i = 0; i < v; i++)
    {
        possib[i] = (i + 1) * slope + x;
        random = random + possib[i];
    }
    float count = 0;
    for (int i = 0; i < a; i++)
    {
        possib[i] = count + possib[i] * 1000000;
        count = possib[i];
    }
    possib[a - 1] = possib[a - 1] + 100;

    number = rand() % 1000100;
    for (int j = 0; j < a; j++)
    {
        if (number <= possib[j])
        {
            value = j;
            break;
        }
    }
    return value;
}

void skew(PGraph g, int e)
{
    int first;
    int second;
    int isok;
    for (int i = 0; i < e; i++)
    {
        while (1)
        {
            first = skewvertex(g->vexnum);
            while (1)
            {
                second = skewvertex(g->vexnum);
                if (second != first)
                {
                    break;
                }
            }
            isok = isedge(g, first, second);
            if (isok != 1)
            {
                addedge(g, first, second);
                break;
            }
        }
    }
}

void normal(PGraph g, int e)
{
    int first;
    int second;
    int isok;
    int new;
    int count = 0;
    first = rand() % g->vexnum;
    while(1)
    {
        
        if (edgenum(g, first) == (g->vexnum - 1))
        {
            while(1){
                first = rand() % g->vexnum;
                if(edgenum(g, first) < (g->vexnum - 1)){
                    break;
                }
            }
        }
        
        while (1)
        {
            while (1)
            {
                second = rand() % g->vexnum;
                if (second != first)
                {
                    break;
                }
            }
            isok = isedge(g, first, second);
            if (isok != 1)
            {
                addedge(g, first, second);
                count++;
                break;
            }
        }
        if(count >= e){
            break;
        }
    }
}

int main()
{
    srand((unsigned)time(NULL));

    int v = 6;
    int edge = 15;
    Graph g;
    s = (int *)calloc(v, sizeof(int));
    creatgraph(&g, v);
    //completegraph(&g);
    //circle(&g);
    normal(&g, edge);

    out(&g);

    return 1;
}