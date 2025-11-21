#include <stdio.h>
//#include <conio.h>
#define maxn 201
#define maxc 1000000000
long c[maxn],d[maxn][maxn],n,P,a[maxn][maxn],trace[maxn][maxn];
//FILE *p;
void visit(long u)
{
//printf("0 ");     
d[u][1]=c[u];
for(long v=1;v<=n;v++)
  if(a[u][v]==1)
    {
    a[v][u]=0;
    visit(v);
    for(long i=P;i>=1;i--)
      for(long j=1;j<=i-1;j++)
        if(d[u][i]<d[u][j]+d[v][i-j])
          {
          d[u][i]=d[u][j]+d[v][i-j];
          trace[v][i]=i-j;
          }
    }
}
void truy_vet(long u,long P)
{
//printf("1 "); 
for(long v=n;v>=1;v--)
  if(a[u][v]==1&&trace[v][P]>0)
    {
    truy_vet(v,trace[v][P]);
    P=P-trace[v][P];
    }
printf("%ld ",u);
}
void xuli()
{
long u,vt;
visit(1);
vt=1;
for(u=2;u<=n;u++)
  if(d[u][P]>d[vt][P])
    vt=u;
  // printf("%ld", d[vt][P]);
  truy_vet(vt,P);

}
void init()
{
for(long u=1;u<=n;u++)
  for(long k=1;k<=n;k++)
    d[u][k]=-maxc;
} 
void Enter()
{
//p=fopen("D:\\Hoc tap\\test\\PTREE\\PTREE.IN0","r");
long i,u,v;
scanf("%ld %ld",&n,&P);
for(i=1;i<=n;i++)
  scanf("%ld",&c[i]);
for(i=1;i<=n-1;i++)
  {
  scanf("%ld %ld",&u,&v);
  a[u][v]=1;
  a[v][u]=1;
  }
}         
main()
{
  #define NAME "PTREE"
  if (fopen(NAME".inp", "r")){
    freopen(NAME".inp", "r", stdin);
      freopen(NAME".ans", "w", stdout);
  }
Enter();
init();
xuli();
//getch();
}
