//1s 50万时钟周期
#include<bits/stdc++.h>
using namespace std;
const int inf=1e9;
const int maxn=600+10;
 const int maxb=21;
int f[maxb][1<<maxb],tran[maxb][1<<maxb];
#define submit
struct EDGE{
    int y,z,id;
    bool operator<(EDGE a)const {
        return z<a.z||(z==a.z && y<a.y) ||(z==a.z &&y==a.y &&id<a.id);
    }
};

vector<EDGE> e[maxn];
int visit[maxn];
int link[maxn][maxn],anstran[maxn];
int source,destination,m,n;
time_t a;
void print(int x){

    int y=anstran[x];
   	for(int i=0;i<e[x].size();i++)if(e[x][i].y==y){
        printf("%d",e[x][i].id);
        break;
    }
	if(y!=destination)printf("|");
	if(y!=destination)print(y);
}
namespace dp{

    void print(int x,int sta){

        int i=tran[x][sta];
        int y=e[x][i].y,z=e[x][i].z,id=e[x][i].id;
        printf("%d",id);
        if(y!=destination)printf("|");
        if(y!=destination)print(y,sta-(1<<x));
    }
    void dfs(int x,int sta){

        if(f[x][sta]<inf) return;

        for(int i=0;i<e[x].size();i++){
                int y=e[x][i].y,z=e[x][i].z,id=e[x][i].id;
                if(((1<<y)&sta)==0) continue;

                dfs(y,sta-(1<<x));
                if(f[y][sta-(1<<x)]+z<f[x][sta]){
                        f[x][sta]=f[y][sta-(1<<x)]+z;
                        tran[x][sta]=i;
                }
        }

    }
    int  work(){
       visit[source]=visit[destination]=1;
       for(int i=0;i<n;i++)
            memset(f[i],63,sizeof(int)*(1<<n));
        f[destination][(1<<destination)]=0;

        int receive_sta=0;
        for(int i=0;i<n;i++)if(visit[i]==1){
            receive_sta=receive_sta|(1<<i);
        }

        dfs(source,receive_sta);

        int ans=receive_sta;

        for(int i=0;i<(1<<n);i++){

                if((i&receive_sta)==receive_sta){
                        dfs(source,i);
                        if(f[source][i]<f[source][ans]) ans=i;
                }
        }

        print(source,ans);
    }
}

namespace ant{

const int maxant=160+10;

const int error_rate=20;
const double attenuation_rate=0.7;
const int view=3;
    int ansdis=inf,tran[maxant][maxn],v[maxant][maxn];

    int use[maxn];
    double error[maxn];

    double pher[maxn][maxn],pher2[maxn][maxn];
    int dis[maxn][maxn],have[maxn];

    int check(int id,int dis){

        for(int i=0;i<n;i++)if(visit[i]==1){
            if(v[id][i]==0)return 0;
        }
        if(v[id][destination]==0)return 0;
        if(dis<ansdis){
            ansdis=dis;
            for(int i=0;i<n;i++)anstran[i]=tran[id][i];
        }
        return 1;
    }
    double dfs_view(int id,int x,int dep){
        if(dep>view)return 0;
        double get=0;
        //get++;
        if(visit[x]==1) get+=1;
        for(int i=0;i<e[x].size();i++){
            int y=e[x][i].y;
            if(!v[id][y]){
                if(!use[y]){
                    use[y]=1;
                    dfs_view(id,y,dep+1);
                }

                //assert(pher[x][y]>0);
                get+=pher[x][y]/dep;
            }

        }

        assert(get>=-1e-6 &&get<=100000);
        return get;
    }
    double taste(int id,int x){
        double sum=0;
        for(int i=0;i<n;i++)if(visit[i]==1 &&v[id][i]==0){
            sum+=1.0/dis[x][i]*error[i];
        }
        //if(visit[x]==1 && v[id][x]==0) sum++;
        return sum;
    }

    void dfs(int id,int x){

        if(x==destination){
            return;
        }
        int ok=0;
        for(int i=0;i<e[x].size();i++)if(v[id][e[x][i].y]==0)ok=1;
        if(!ok)return;


        int pro=rand()%100;
        if(pro<=error_rate){

            int i=-1;
            do{
                i=rand()%e[x].size();
            }while(v[id][e[x][i].y]);
            assert(link[x][e[x][i].y]<inf);
            assert(v[id][e[x][i].y]==0);
            assert(i>=0);
            int y=e[x][i].y;
            tran[id][x]=y;
            v[id][y]=1;
            dfs(id,y);
        }
        else{
            for(int i=0;i<e[x].size();i++) {
                int y=e[x][i].y,live=0;
                if(v[y]||!visit[y])continue;
                for(int j=0;j<n;j++)if(!v[j] && link[j][y]<inf && j!=x){
                    live=1;
                    break;
                }
                if(!live) {
                    v[id][y]=1;
                    tran[id][x]=y;
                    dfs(id,y);
                    return;
                }
            }

            double maxget=-1;
            int y=-1;
            for(int i=0;i<e[x].size();i++)   if(v[id][e[x][i].y]==0){
                for(int j=0;j<n;j++)use[j]=0;
                double get=dfs_view(id,e[x][i].y,1);
                double get2=taste(id,e[x][i].y);
                //assert(get2<1e-6);
                //
                //cout<<get<<" "<<get2<<endl;

                if(exp(get)*get2>maxget){
                    maxget=exp(get)*get2;
                    y=e[x][i].y;
                }
            }
            assert(y>-1);
            tran[id][x]=y;
            v[id][y]=1;
            dfs(id,y);
        }

    }
    void modify(){
        double sum=0,sum2=0;

        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++) sum+=pher[i][j],sum2+=pher2[i][j];

        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++){
                pher[i][j]/=sum;
                if(sum2>0) pher2[i][j]/=sum2;else pher2[i][j]=0;
            }

        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++) pher[i][j]=pher[i][j]*attenuation_rate+pher2[i][j]*(1-attenuation_rate),pher2[i][j]=0;

    }
    int work(){
        visit[source]=visit[destination]=0;
        int nv=0;
        for(int i=0;i<n;i++)if(visit[i]==1) nv++;

        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++) if(link[i][j]==0) link[i][j]=inf;
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++) dis[i][j]=link[i][j];
        for(int k=0;k<n;k++)
            for(int i=0;i<n;i++)if(i!=k)
                for(int j=0;j<n;j++) if(k!=j && i!=j &&dis[i][k]+dis[k][j]<dis[i][j])
                    dis[i][j]=dis[i][k]+dis[k][j];
        //for(int i=0;i<n;i++)
        //    for(int j=0;j<n;j++)cout<<i<<" "<<j<<" "<<dis[i][j]<<endl;

        for(int i=0;i<n;i++)
            sort(e[i].begin(),e[i].end());

        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)if(link[i][j]<inf &&visit[j]==1) pher[i][j]=1;
            else pher[i][j]=0;
        modify();
        int ant=100;

        ansdis=inf;
        for(int i=0;i<n;i++)error[i]=1;
        for(int t=1;t<=10000000;t++){

           if(t%150==0){

                srand((u_int32_t)rand());

                for(int i=0;i<n;i++)error[i]=1;
                for(int i=0;i<n;i++)
                for(int j=0;j<n;j++)if(link[i][j]<inf && visit[j]==1)pher[i][j]=1;
                else pher[i][j]=0;
                modify();
            }
            if(clock()-a>9000000) {
            #ifndef submit
              /// cout<<t<<endl;
            #endif
                break;
            }

            for(int i=0;i<n;i++)have[i]=0;
            for(int i=1;i<=ant;i++){
                for(int j=0;j<n;j++)tran[i][j]=-1,v[i][j]=0;
                v[i][source]=1;
                dfs(i,source);
               // watch(i,source);
            }
            for(int i=1;i<=ant;i++){
                int x=source;
                double award=0,dis=0;

                while (tran[i][x]>=0){

                    dis+=link[x][tran[i][x]];
                    x=tran[i][x];


                    if(visit[x])award+=1.0*sqrt(error[x])*e[x].size();
                }



                if(check(i,dis)){
                    award*=100/(dis-ansdis+1);
                }

                x=source;
                while (tran[i][x]>=0){
                    if(tran[i][tran[i][x]]>=0 && tran[i][tran[i][tran[i][x]]]>=0){
                        pher2[i][tran[i][x]]+=award;
                    }
                    x=tran[i][x];
                    have[x]++;
                }

            }
            for(int i=0;i<n;i++)if(visit[i] && have[i]<=15)error[i]++;
            modify();
        }

        if(ansdis<inf){
            print(source);
            exit(0);
        }
    }
}
namespace greedy{
    int tran[maxn],v[maxn],use[maxn],q[maxn];
    void print(int x){

        int i=tran[x];
        int y=e[x][i].y,z=e[x][i].z,id=e[x][i].id;
        printf("%d",id);
        if(y!=destination)printf("|");
        if(y!=destination)print(y);
    }
    int check(){

        for(int i=0;i<n;i++)if(visit[i]==1){
            if(v[i]==0)return 0;
        }
        return 1;
    }
    bool isolated(int x){
        for(int i=0;i<n;i++)use[i]=0;

        int h=0,t=1;
        q[t]=x;use[x]=1;
        while(h<t){
            int x=q[++h];
            for(int i=0;i<e[x].size();i++){
                int y=e[x][i].y;
                if(!use[y] && !v[y]){
                    use[y]=1;
                    q[++t]=y;
                }
            }
        }
        for(int i=0;i<n;i++)if(visit[i]==1 && v[i]==0) {
            if(use[i]==0){
                    //++cnt;
                   // if(cnt%1000000==0)cout<<cnt<<endl;
                    return false;
                }
            if(i==destination)continue;
            int ok=0;
            for(int j=0;j<e[i].size();j++)if(v[e[i][j].y]==0) {
                ok=1;
                break;
            }
            if(!ok){
                    //++cnt;
                    //if(cnt%1000000==0)cout<<cnt<<endl;
                    return false;
            }
        }

                    //++cnt2;

           //if(cnt2%1000000==0)cout<<"cnt2="<<cnt2<<endl;
        return true;
    }
    void dfs(int x,int s){

        if(!isolated(x))
            return;
        if(x==destination){
            #ifndef submit
                //printf("yyy\n");
            #endif
            if(clock()-a>9000000){
                printf("NA\n");
                exit(0);
            }
            if(check()) {
                print(source);
                exit(0);
            }

            return;
        }

        for(int i=0;i<e[x].size();i++){
            int y=e[x][i].y,z=e[x][i].z,id=e[x][i].id;
            if(v[y])continue;
            tran[x]=i;

            v[y]=1;
            dfs(y,s+z);
            v[y]=0;
        }
    }
    int work(){
        visit[source]=0;
        visit[destination]=1;
        memset(v,0,sizeof(v));
        v[source]=1;
        a=clock();
        dfs(source,0);
    }
}

int main(int argc, char *argv[]){
    srand(time(0));
    a=clock();
    #ifdef submit
    freopen(argv[1],"r",stdin);
    freopen(argv[3],"w",stdout);
#else
    freopen("a.txt","r",stdin);
   //freopen("result.txt","w",stdout);
#endif
    int w,x,y,z;
    char ch;

    while(scanf("%d,%d,%d,%d",&w,&x,&y,&z)!=EOF){

            ++m;
            if(link[x][y]==0){
                link[x][y]=z;
                e[x].push_back(EDGE{y,z,w});
            }
            else{
                link[x][y]=min(link[x][y],z);
                for(int i=0;i<e[x].size();i++) if(e[x][i].y==y){
                    e[x][i].z=z;
                    e[x][i].id=w;
                }
            }
            n=max(n,x);
            n=max(n,y);

    }
    n++;
#ifdef submit
    freopen(argv[2],"r",stdin);
#else
    freopen("b.txt","r",stdin);
#endif
    scanf("%d,%d,",&source,&destination);
    for(int i=0;i<n;i++) visit[i]=0;




    while(scanf("%d",&x)!=EOF){
            visit[x]=1;
            scanf("%c",&ch);
    }


    if(n<=20) {
        dp::work();

    }
    else {
        ant::work();
        greedy::work();
    }
}

