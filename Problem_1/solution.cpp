#include<bits/stdc++.h>
using namespace std;
 
const int N  = 1e6 + 20;
 
int st[4*N], lazy[4*N];
void build(int si, int ss, int se){
    if(ss == se){
        st[si] = 0;
        return;
    }
    int mid = (ss+se)/2;
    build(2*si, ss,mid);
    build(2*si+1 , mid+1,se);
    st[si] = st[2*si]+st[2*si+1];
}
int query(int si, int ss, int se, int qs, int qe){
    if(lazy[si] != 0){
        int dx = lazy[si];
        lazy[si] = 0;
        st[si] += dx*(se - ss + 1);
        if(ss != se){
            lazy[2*si] += dx;
            lazy[2*si+1] += dx;
        }
    }
    if(se < qs or qe < ss)return 0;
    if(qs <= ss and se <= qe){
        return st[si];
    }
    int mid = (ss+se)/2;
    return query(2*si,ss,mid,qs,qe)+query(2*si+1 , mid+1,se,qs,qe);
}
void update(int si, int ss, int se, int qs, int qe, int val){
    if(lazy[si] != 0){
        int dx = lazy[si];
        lazy[si] = 0;
        st[si] += dx*(se-ss+1);
 
        if(ss != se){
            lazy[2*si] += dx;
            lazy[2*si+1] += dx;
        }
    }
    if(se < qs or qe<ss)return ;
    if(qs <= ss  and se <= qe){
        int dx = (se-ss+1)*val;
        st[si] += dx;
        if(ss != se){
            lazy[2*si] += val;
            lazy[2*si+1] += val;
        }
        return;
    }
    int mid = (ss+se)/2;
    update(2*si , ss,mid,qs,qe,val);
    update(2*si+1,mid+1,se,qs,qe,val);
    st[si] = st[2*si]+st[2*si+1];
}
 
int32_t solve() {
 
    
    int q;
    cin>>q;
    build(1,1,N);
    vector<int> ex(N , 0);
    map<int,int> explored;
    while(q--){
        int t;
        cin>>t;
        if(t == 1){
            int x;
            cin>>x;
            explored[x] = 1;
            ex[x] = query(1,1,N,x,x);
        }else if(t == 2){
            int l,r,x;
            cin>>l>>r>>x;
            update(1,1,N,l,r , x);
        }else{
            int x;cin>>x;
            if(explored[x] == 0){
                cout<<0<<endl;
            }else{
                cout<<query(1,1,N,x,x) - ex[x]<<endl;
            }
        }
    }
 
    return 0;
    //error();
}
 
// int
int32_t main(){
    int test = 1;
    // cin>>test;
    // freopen("in.txt" , "r" , stdin);
    // freopen("out.txt" , "w" , stdout);
    while (test--)solve();return 0;
}
 