/**
 * Author: Anonymous
 * Description:
 * Merge sort tree 2, for Dynamic Lower Bound problem.
 * given array and updates,
 * should find lower bound of x in range l to r.
*/

#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,q,a[N];
multiset<int> seg[4*N+5];
void build(int node,int l,int r){
    if (l==r){
        seg[node].insert(a[l]);
        return;
    }int mid=(l+r)/2;
    build(node*2,l,mid);
    build(node*2+1,mid+1,r);
    for (int i=l;i<=r;i++) seg[node].insert(a[i]);
    return;
}
void edit(int node,int l,int r,int idx,int val){
    if (l==r){
        seg[node].erase(a[idx]);
        seg[node].insert(val);
        return;
    }int mid=(l+r)/2;
    if (idx<=mid) edit(node*2,l,mid,idx,val);
    else edit(node*2+1,mid+1,r,idx,val);
    seg[node].erase(a[idx]);
    seg[node].insert(val);
    return;
}
int query(int node,int l,int r,int lx,int rx,int x){
    if (l>rx || r<lx) return INT_MAX;
    if (l>=lx && r<=rx){
        auto it=seg[node].lower_bound(x);
        if (it==seg[node].end()) return INT_MAX;
        return *it;
    }int mid=(l+r)/2;
    return min(query(node*2,l,mid,lx,rx,x),query(node*2+1,mid+1,r,lx,rx,x));
}
int32_t main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    cin>>n>>q;
    for (int i=1;i<=n;i++) cin>>a[i];
    build(1,1,n);
    while (q--){
        bool t;cin>>t;
        if (!t){
            int idx,val;
            cin>>idx>>val;
            edit(1,1,n,idx,val);
            a[idx]=val;
            continue;
        }int l,r,x;cin>>l>>r>>x;
        int y=query(1,1,n,l,r,x);
        if (y==INT_MAX) cout<<-1<<endl;
        else cout<<y<<endl;
    }
    return 0;
}