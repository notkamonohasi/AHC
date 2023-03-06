#ifdef _MSC_VER
#  include <intrin.h>
#else
#  include <x86intrin.h>
#endif

#include <bits/stdc++.h>
//#define MOD 1000000007
#define MOD 998244353
#define ll long long  // 要注意
#define ld long double
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define frep(i, k, n) for (ll i = (ll)k; i < (ll)(n); i++)
#define brep(i, n) for (ll i = (ll)(n - 1); i >= 0; i--)
#define irep(it, mp) for (auto it = mp.begin(); it != mp.end(); it++)
#define len(x) (ll)x.size()
#define print(x) cout << x << endl
#define nprint(x) cout << x << " "
#define dprint(a, b) cout << a << " " << b << endl
#define tprint(a, b, c) cout << a << " " << b << " " << c << endl
#define fprint(a, b, c, d) cout << a << " " << b << " " << c << " " << d << endl
#define pprint(x) cout << fixed << setprecision(10) << x << endl
#define vprint(v) for(auto x : v) cout << x << " ";   cout << endl
#define bs(st, key) (st.find(key) != st.end() ? true : false)
#define lb(v, k) lower_bound(v.begin(), v.end(), k)
#define ub(v, k) upper_bound(v.begin(), v.end(), k)
#define all(v) v.begin(), v.end()
#define bit(x,i)(((x)>>(i))&1)
using namespace std;

//const ll vec[][2] = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
//const ll vec[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
//const ld PI = 3.141592653589793238462643;

ll POW(ll a, ll n){if(n == 0) return 1; if(n == 1) return a; if(n % 2 == 1) return a * POW(a, n - 1); ll t = POW(a, n / 2); return t * t;}
ll MODPOW(ll a, ll n){if(n == 0) return 1; if(n == 1) return a % MOD; if(n % 2 == 1) return (a * MODPOW(a, n - 1)) % MOD; ll t = MODPOW(a, n / 2); return (t * t) % MOD;}
ll MODINV(ll a){return MODPOW(a, MOD - 2);}
ll CEIL(ll a, ll b){ll ret = (a + b - 1) / b; return ret;}
ll max(ll a, ll b){if(a > b) return a; else return b;}
ll min(ll a, ll b){if(a > b) return b; else return a;}
ll max(ll a, ll b, ll c){ll d = max(a, b); return max(c, d);}
ll min(ll a, ll b, ll c){ll d = min(a, b); return min(c, d);}
void chmax(ll& a, ll b){if(b > a) a = b;}
void chmin(ll& a, ll b){if(a > b) a = b;}
void yes(bool b){if(b) cout << "Yes" << endl; else cout << "No" << endl;}
using P = pair<ll, ll>;
bool sameP(P& p1, P& p2){if(p1.first == p2.first && p1.second == p2.second) return true; else return false;}
void print_pair(P& p){dprint(p.first, p.second);}
using T = tuple<ll, ll, ll>; // ll x, y, z; tie(x, y, z) = T
template<typename T> using PQ = priority_queue<T>;
template<typename T> using IQ = priority_queue<T, vector<T>, greater<T>>;
using Mat = vector<vector<ll>>;
Mat init_mat(ll a, ll b){Mat ret(a, vector<ll>(b, 0)); return ret;}
Mat init_mat(ll a, ll b, ll c){Mat ret(a, vector<ll>(b, c)); return ret;}
void print_mat(Mat mat){rep(i, mat.size()){rep(j, mat[i].size()){cout << mat[i][j] << " ";}cout << endl;}}
using PMat = vector<vector<P>>;
PMat init_pmat(ll a, ll b){PMat ret(a, vector<P>(b, P(0, 0))); return ret;}
PMat init_pmat(ll a, ll b, P c){PMat ret(a, vector<P>(b, c)); return ret;}
using BMat = vector<vector<bool>>;
BMat init_bmat(ll a, ll b){BMat ret(a, vector<bool>(b, false)); return ret;}
BMat init_bmat(ll a, ll b, bool c){BMat ret(a, vector<bool>(b, c)); return ret;}
void print_bmat(BMat bmat){rep(i, bmat.size()){rep(j, bmat[i].size()){cout << bmat[i][j];}cout << endl;}}
using DMat = vector<vector<double>>;
DMat init_dmat(ll a, ll b){DMat ret(a, vector<double>(b, 0.0)); return ret;}
DMat init_dmat(ll a, ll b, double c){DMat ret(a, vector<double>(b, c)); return ret;}
using Tensor = vector<vector<vector<ll>>>;
Tensor init_tensor(ll a, ll b, ll c){Tensor ret(a, Mat(b, vector<ll>(c, 0))); return ret;}
Tensor init_tensor(ll a, ll b, ll c, ll d){Tensor ret(a, Mat(b, vector<ll>(c, d))); return ret;}

using Graph = vector<vector<ll> >;
Graph init_graph(ll V){Graph ret; vector<ll> empty; rep(i, V) ret.push_back(empty); return ret;}

using CostGraph = vector<vector<P> >;
CostGraph init_costGraph(ll V){CostGraph ret; vector<P> empty; rep(i, V) ret.push_back(empty); return ret;}

//struct Edge{ll to, cost;};
//using Graph = vector<vector<Edge> >;
//Graph init_graph(ll V){Graph ret; vector<Edge> empty; rep(i, V) ret.push_back(empty); return ret;}

random_device rd;
// mt19937 eng(rd());
mt19937 eng(0);
uniform_int_distribution<> randInt(0, INT_MAX);
uniform_real_distribution<> uniform(0.0, 1.0);

const double INIT_END_TIME = 1000000; 
double START; 

const double START_TEMP =  1500; // 開始時の温度
const double END_TEMP   =  100; // 終了時の温度
const double END_TIME   =  5870000; // 終了時間

ll n, m, d, k;

struct Edge{
    ll number; 
    ll from; 
    ll to; 
    ll weight; 

    Edge(ll a, ll b, ll c, ll d) : number(a), from(b), to(c), weight(d){}

    bool operator > (const Edge& another) const{return weight > another.weight;}
    bool operator < (const Edge& another) const{return weight < another.weight;}
}; 

vector<Edge> edges; 
vector<P> nodes;
Graph edgeNumberGraph; 
CostGraph costGraph; 
vector<vector<Edge>> edgeGraph; 

class DisjointSet{
public:
    vector<ll> rank, p;
    DisjointSet(){}
    DisjointSet(ll size){rank.resize(size, 0); p.resize(size, 0); for(ll i=0; i<size; i++) makeSet(i);}
    void makeSet(ll x){p[x]=x; rank[x]=0;}
    bool same(ll x, ll y){return findSet(x) == findSet(y);}
    void unite(ll x, ll y){link(findSet(x), findSet(y));}
    void link(ll x, ll y){if(rank[x]>rank[y]) p[y]=x; else{p[x]=y; if(rank[x]==rank[y]) rank[y]++;}}
    ll findSet(ll x){if(x!=p[x]) p[x]=findSet(p[x]); return p[x];}
};

template<typename T>
class dynamic_connectivity{
    class euler_tour_tree{
        public:
        struct node;
        using np=node*;
        using lint=long long;
        struct node{
            np ch[2]={nullptr,nullptr};
            np p=nullptr;
            ll l,r,sz;
            T val=et,sum=et;
            bool exact;
            bool child_exact;
            bool edge_connected=0;
            bool child_edge_connected=0;
            node(){}
            node(ll l,ll r):l(l),r(r),sz(l==r),exact(l<r),child_exact(l<r){}
            bool is_root() {
                return !p;
            }
        };
        vector<unordered_map<int,np>>ptr;
        np get_node(ll l,ll r){
            if(ptr[l].find(r)==ptr[l].end())ptr[l][r]=new node(l,r);
            return ptr[l][r];
        }
        np root(np t){
            if(!t)return t;
            while(t->p)t=t->p;
            return t;
        }
        bool same(np s,np t){
            if(s)splay(s);
            if(t)splay(t);
            return root(s)==root(t);
        }
        np reroot(np t){
            auto s=split(t);
            return merge(s.second,s.first);
        }
        pair<np,np> split(np s){
            splay(s);
            np t=s->ch[0];
            if(t)t->p=nullptr;
            s->ch[0]=nullptr;
            return {t,update(s)};
        }
        pair<np,np> split2(np s){
            splay(s);
            np t=s->ch[0];
            np u=s->ch[1];
            if(t)t->p=nullptr;
            s->ch[0]=nullptr;
            if(u)u->p=nullptr;
            s->ch[1]=nullptr;
            return {t,u};
        }
        tuple<np,np,np> split(np s,np t){
            auto u=split2(s);
            if(same(u.first,t)){
                auto r=split2(t);
                return make_tuple(r.first,r.second,u.second);
            }else{
                auto r=split2(t);
                return make_tuple(u.first,r.first,r.second);
            }
        }
        template<typename First, typename... Rest>
        np merge(First s,Rest... t){
            return merge(s,merge(t...));
        }
        np merge(np s,np t){
            if(!s)return t;
            if(!t)return s;
            while(s->ch[1])s=s->ch[1];
            splay(s);
            s->ch[1]=t;
            if(t)t->p=s;
            return update(s);
        }
        ll size(np t){return t?t->sz:0;}
        np update(np t){
            t->sum=et;
            if(t->ch[0])t->sum=fn(t->sum,t->ch[0]->sum);
            if(t->l==t->r)t->sum=fn(t->sum,t->val);
            if(t->ch[1])t->sum=fn(t->sum,t->ch[1]->sum);
            t->sz=size(t->ch[0])+(t->l==t->r)+size(t->ch[1]);
            t->child_edge_connected=(t->ch[0]?t->ch[0]->child_edge_connected:0)|(t->edge_connected)|(t->ch[1]?t->ch[1]->child_edge_connected:0);
            t->child_exact=(t->ch[0]?t->ch[0]->child_exact:0)|(t->exact)|(t->ch[1]?t->ch[1]->child_exact:0);
            return t;
        }
        void push(np t){
            //遅延評価予定
        }
        void rot(np t,bool b){
            np x=t->p,y=x->p;
            if((x->ch[1-b]=t->ch[b]))t->ch[b]->p=x;
            t->ch[b]=x,x->p=t;
            update(x);update(t);
            if((t->p=y)){
                if(y->ch[0]==x)y->ch[0]=t;
                if(y->ch[1]==x)y->ch[1]=t;
                update(y);
            }
        }
        void splay(np t){
            push(t);
            while(!t->is_root()){
                np q=t->p;
                if(q->is_root()){
                    push(q), push(t);
                    rot(t,q->ch[0]==t);
                }else{
                    np r=q->p;
                    push(r), push(q), push(t);
                    bool b=r->ch[0]==q;
                    if(q->ch[1-b]==t)rot(q,b),rot(t,b);
                    else rot(t,1-b),rot(t,b);
                }
            }
        }
        void debug(np t){
            if(!t)return;
            debug(t->ch[0]);
            cerr<<t->l<<"-"<<t->r<<" ";
            debug(t->ch[1]);
        }
        public:
        euler_tour_tree(){}
        euler_tour_tree(ll sz){
            ptr.resize(sz);
            for(ll i=0;i<sz;i++)ptr[i][i]=new node(i,i);
        }
        ll size(ll s){
            np t=get_node(s,s);
            splay(t);
            return t->sz;
        }
        bool same(ll s,ll t){
            return same(get_node(s,s),get_node(t,t));
        }
        void set_size(ll sz){
            ptr.resize(sz);
            for(ll i=0;i<sz;i++)ptr[i][i]=new node(i,i);
        }
        void update(ll s,T x){
            np t=get_node(s,s);
            splay(t);
            t->val=fn(t->val,x);
            update(t);
        }
        void edge_update(ll s,auto g){
            np t=get_node(s,s);
            splay(t);
            function<void(np)>dfs=[&](np t){
                assert(t);
                if(t->l<t->r&&t->exact){
                    splay(t);
                    t->exact=0;
                    update(t);
                    g(t->l,t->r);
                    return;
                }
                if(t->ch[0]&&t->ch[0]->child_exact)dfs(t->ch[0]);
                else dfs(t->ch[1]);
            };
            while(t&&t->child_exact){
                dfs(t);
                splay(t);
            }
        }
        bool try_reconnect(ll s,auto f){
            np t=get_node(s,s);
            splay(t);
            function<bool(np)>dfs=[&](np t)->bool{
                assert(t);
                if(t->edge_connected){
                    splay(t);
                    return f(t->l);
                }
                if(t->ch[0]&&t->ch[0]->child_edge_connected)return dfs(t->ch[0]);
                else return dfs(t->ch[1]);
            };
            while(t->child_edge_connected){
                if(dfs(t))return 1;
                splay(t);
            }
            return 0;
        }
        void edge_connected_update(ll s,bool b){
            np t=get_node(s,s);
            splay(t);
            t->edge_connected=b;
            update(t);
        }
        bool link(ll l,ll r){
            if(same(l,r))return 0;
            merge(reroot(get_node(l,l)),get_node(l,r),reroot(get_node(r,r)),get_node(r,l));
            return 1;
        }
        bool cut(ll l,ll r){
            if(ptr[l].find(r)==ptr[l].end())return 0;
            np s,t,u;
            tie(s,t,u)=split(get_node(l,r),get_node(r,l));
            merge(s,u);
            np p=ptr[l][r];
            np q=ptr[r][l];
            ptr[l].erase(r);
            ptr[r].erase(l);
            delete p;delete q;
            return 1;
        }
        T get_sum(ll p,ll v){
            cut(p,v);
            np t=get_node(v,v);
            splay(t);
            T res=t->sum;
            link(p,v);
            return res;
        }
        T get_sum(ll s){
            np t=get_node(s,s);
            splay(t);
            return t->sum;
        }
    };
    ll dep=1;
    vector<euler_tour_tree> ett;
    vector<vector<unordered_set<ll>>>edges;
    ll sz;
    public:
    dynamic_connectivity(){}
    dynamic_connectivity(ll sz):sz(sz){
        ett.emplace_back(sz);
        edges.emplace_back(sz);
    }
    bool link(ll s,ll t){
        if(s==t)return 0;
        if(ett[0].link(s,t))return 1;
        edges[0][s].insert(t);
        edges[0][t].insert(s);
        if(edges[0][s].size()==1)ett[0].edge_connected_update(s,1);
        if(edges[0][t].size()==1)ett[0].edge_connected_update(t,1);
        return 0;
    }
    bool same(ll s,ll t){
        return ett[0].same(s,t);
    }
    ll size(ll s){
        return ett[0].size(s);
    }
    vector<ll>get_vertex(ll s){
        return ett[0].vertex_list(s);
    }
    void update(ll s,T x){
        ett[0].update(s,x);
    }
    T get_sum(ll s){
        return ett[0].get_sum(s);
    }
    bool cut(ll s,ll t){
        if(s==t)return 0;
        for(ll i=0;i<dep;i++){
            edges[i][s].erase(t);
            edges[i][t].erase(s);
            if(edges[i][s].size()==0)ett[i].edge_connected_update(s,0);
            if(edges[i][t].size()==0)ett[i].edge_connected_update(t,0);
        }
        for(ll i=dep-1;i>=0;i--){
            if(ett[i].cut(s,t)){
                if(dep-1==i){
                    dep++;
                    ett.emplace_back(sz);
                    edges.emplace_back(sz);
                }
                return !try_reconnect(s,t,i);
            }
        }
        return 0;
    }
    bool try_reconnect(ll s,ll t,ll k){
        for(ll i=0;i<k;i++){
            ett[i].cut(s,t);
        }
        for(ll i=k;i>=0;i--){
            if(ett[i].size(s)>ett[i].size(t))swap(s,t);
            auto g=[&](ll s,ll t){ett[i+1].link(s,t);};
            ett[i].edge_update(s,g);
            auto f=[&](ll x)->bool{
                for(auto itr=edges[i][x].begin();itr!=edges[i][x].end();){
                    auto y=*itr;
                    itr=edges[i][x].erase(itr);
                    edges[i][y].erase(x);
                    if(edges[i][x].size()==0)ett[i].edge_connected_update(x,0);
                    if(edges[i][y].size()==0)ett[i].edge_connected_update(y,0);
                    if(ett[i].same(x,y)){
                        edges[i+1][x].insert(y);
                        edges[i+1][y].insert(x);
                        if(edges[i+1][x].size()==1)ett[i+1].edge_connected_update(x,1);
                        if(edges[i+1][y].size()==1)ett[i+1].edge_connected_update(y,1);
                    }else{
                        for(ll j=0;j<=i;j++){
                            ett[j].link(x,y);
                        }
                        return 1;
                    }
                }
                return 0;
            };
            if(ett[i].try_reconnect(s,f))return 1;
        }
        return 0;
    }
    constexpr static T et=T();
    constexpr static T fn(T s,T t){
        return s+t;
    }
};


template <typename Key, typename Val>
struct RadixHeap {
  using uint = typename make_unsigned<Key>::type;
  static constexpr int bit = sizeof(Key) * 8;
  array<vector<pair<uint, Val> >, bit + 1> vs;
  array<uint, bit + 1> ms;

  int s;
  uint last;

  RadixHeap() : s(0), last(0) { fill(begin(ms), end(ms), uint(-1)); }

  bool empty() const { return s == 0; }

  int size() const { return s; }

  __attribute__((target("lzcnt"))) inline uint64_t getbit(uint a) const {
    return 64 - _lzcnt_u64(a);
  }

  void push(const uint &key, const Val &val) {
    s++;
    uint64_t b = getbit(key ^ last);
    vs[b].emplace_back(key, val);
    ms[b] = min(key, ms[b]);
  }

  pair<uint, Val> pop() {
    if (ms[0] == uint(-1)) {
      int idx = 1;
      while (ms[idx] == uint(-1)) idx++;
      last = ms[idx];
      for (auto &p : vs[idx]) {
        uint64_t b = getbit(p.first ^ last);
        vs[b].emplace_back(p);
        ms[b] = min(p.first, ms[b]);
      }
      vs[idx].clear();
      ms[idx] = uint(-1);
    }
    --s;
    auto res = vs[0].back();
    vs[0].pop_back();
    if (vs[0].empty()) ms[0] = uint(-1);
    return res;
  }
};

template <typename T>
vector<T> dijkstra_radix_heap(CostGraph& g, int start = 0) {
  int N = (int)g.size();
  vector<T> d(N, T(-1));
  RadixHeap<T, int> Q;
  d[start] = 0;
  Q.push(0, start);
  while (!Q.empty()) {
    auto p = Q.pop();
    int cur = p.second;
    if (d[cur] < T(p.first)) continue;
    for (auto dst : g[cur]) {
      if (d[dst.first] == T(-1) || d[cur] + dst.second < d[dst.first]) {
        d[dst.first] = d[cur] + dst.second;
        Q.push(d[dst.first], dst.first);
      }
    }
  }
  return d;
}



class Debug{
public : 
    Debug(){}

    void judgeUnify(vector<ll> dropTurns){ 
        bool unify = true;
        rep(i, d){
            DisjointSet ds(n); 
            rep(j, m){
                if(dropTurns[j] != i) ds.unite(edges[j].from, edges[j].to); 
            }
            
            rep(x, n){
                rep(y, n){
                    if(x == y) continue;
                    if(ds.same(x, y) == false){ 
                        unify = false;
                    }
                }
            }
        }
        
        cout << "UNIFY : ";
        yes(unify); 
    }

    void judgeUnify(vector<set<ll>> dropEdgeTurn){
        bool unify = true;
        rep(t, d){
            DisjointSet ds(n);
            rep(i, m){
                if(bs(dropEdgeTurn[i], t) == false) ds.unite(edges[i].from, edges[i].to); 
            }
            rep(i, n){
                rep(j, n){
                    if(ds.same(i, j) == false) unify = false;
                }
            }
        }
        cout << "ST_UNIFY : "; 
        yes(unify); 
    }
}; 


class Cluster{
private : 
    vector<P> centerVec = {
        {-400, 0}, 
        {-200, -200}, {-200, 0}, {-200, 200}, 
        {0, -400}, {0, -200}, {0, 0}, {0, 200}, {0, 400}, 
        {200, -200}, {200, 0}, {200, 200}, 
        {400, 0}
    };
    vector<ll> firstVec; 
    Graph clusterGraph; 
    vector<ll> parVec;

public : 
    Cluster(){}
    
    void init(){
        clusterGraph = init_graph(centerVec.size()); 
        parVec = vector<ll>(n, -1); 
        
        calcFirstVec(); 
        
        rep(i, n){
            ll minDist = INT_MAX; 
            ll index; 
            P p = nodes[i]; 
            rep(j, centerVec.size()){
                ll dist = calcDist(p, centerVec[j]); 
                if(minDist > dist){
                    minDist = dist; 
                    index = j;
                }
            }
            clusterGraph[index].push_back(i);
        }
    }
    
    void calcFirstVec(){
        for(P& p1 : centerVec){
            ll minDist = INT_MAX; 
            ll index = -1; 
            ll size = nodes.size(); 
            rep(i, size){
                P p2 = nodes[i]; 
                ll dist = calcDist(p1, p2); 
                if(minDist > dist){
                    minDist = dist; 
                    index = i; 
                }
            }
            firstVec.push_back(index); 
        }
    }
    
    ll calcDist(P& p1, P& p2){
        ll ret = sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2)); 
        return ret; 
    }
    
    void printCluster(){
        rep(i, firstVec.size()){
            tprint("----- cluster", i, "-----"); 
            dprint("size :", clusterGraph[i].size());
            for(ll x : clusterGraph[i]){
                cout << "(" << nodes[x].first << ", " << nodes[x].second << ") " << endl;
            }
            cout << endl;
        }
    }
    
    vector<ll> sampling(){
        vector<ll> ret; 
        rep(i, clusterGraph.size()){
            ll size = clusterGraph[i].size(); 
            if(size == 0) continue;
            ll r = randInt(eng) % size; 
            ret.push_back(clusterGraph[i][r]); 
        }
        return ret;
    }
}; 
Cluster cluster; 


class State{
public : 
    ll n, m, d, k; 
    vector<bool> useVec; 
    dynamic_connectivity<ll> dc; 

    State(){}
    State(ll n_, ll m_, ll d_, ll k_) : n(n_), m(m_), d(d_), k(k_), useVec(m, false), dc(n){}

    void init(){
        IQ<Edge> pq; 
        for(Edge edge : edges){
            edge.weight = randInt(eng); 
            pq.push(edge); 
        }
        DisjointSet ds(n); 
        while(!pq.empty()){
            Edge node = pq.top(); 
            pq.pop(); 
            if(ds.same(node.from, node.to) == false){
                ds.unite(node.from, node.to);
                dc.link(node.from, node.to); 
                useVec[node.number] = true;
            } 
        }
    }

    // void link(ll u, ll v){dc.link(u, v);}
    void link(ll num){
        dc.link(edges[num].from, edges[num].to);
        useVec[num] = true;
    }

    void cut(ll num){
        if(useVec[num] == false){
            print("NOT LINK in State::cut"); 
            exit(EXIT_FAILURE); 
        }
        dc.cut(edges[num].from, edges[num].to); 
        useVec[num] = true;
    }

    bool isUseEdge(ll a){return useVec[a];}
    
    bool canCut(ll num){
        if(useVec[num] == false){
            print("INPUT ERROR in State::canCut"); 
            exit(EXIT_FAILURE); 
        }
        dc.cut(edges[num].from, edges[num].to); 
        ll size = dc.size(0); 
        dc.link(edges[num].from, edges[num].to); 
        if(size != m) return false;
        else return true; 
    }
}; 


class Total{
public : 
    ll n, m, d, k; 
    vector<State> states; 
    vector<set<ll>> dropTurnEdge;   // 各ターンがどの辺を消しているか
    vector<set<ll>> dropEdgeTurn;   // 各辺がどのターンで消されているか
    BMat useMat; 
    Mat kindMat;   // -1が使わない、0が固定、1が追加

    Total(){}
    Total(ll n_, ll m_, ll d_, ll k_) : n(n_), m(m_), d(d_), k(k_), states(d), dropTurnEdge(d), dropEdgeTurn(m){
        useMat = init_bmat(d, m); 
        kindMat = init_mat(d, m, -1); 
    }

    bool init(){
        rep(t, d){
            states[t] = State(n, m, d, k); 
            states[t].init(); 
            rep(i, m) useMat[t][i] = states[t].isUseEdge(i);
            rep(i, m){ 
                if(useMat[t][i] == true){ 
                    kindMat[t][i] = 0; 
                }
                else{
                    dropTurnEdge[t].insert(i);
                    dropEdgeTurn[i].insert(t);
                    kindMat[t][i] = -1; 
                }
            }
        }

        bool linkAdjustSuccess = linkAdjust();
        if(linkAdjustSuccess){ 
            linkMargin();
            bool rebalanceSuccess = rebalance();
            if(rebalanceSuccess == true) return true;
            else return false;
        }
        return false; 
    }

    // 
    void linkMargin(){
        rep(i, m){
            vector<ll> cand;
            rep(t, d){
                if(kindMat[t][i] == -1) cand.push_back(t);
            }
            ll r = randInt(eng) % (ll)cand.size(); 
            rep(j, cand.size()){
                if(j != r){ 
                    kindMat[cand[j]][i] = 1;
                    link(cand[j], i); 
                }
            }
        }
    }

    bool linkAdjust(){
        set<ll> invalidEdgeSt; 
        rep(i, m){
            if(dropEdgeTurn[i].size() == 0) invalidEdgeSt.insert(i); 
        }

        ll prevSize = -1; 
        ll continuousCount = 0; 
        bool emergencyFlag = false;

        double lapse = clock() - START;
        while(invalidEdgeSt.size() != 0 && lapse < INIT_END_TIME){
            // 更新方法
            if(invalidEdgeSt.size() == prevSize){ 
                continuousCount++;
                if(continuousCount >= 20){ 
                    if(emergencyFlag == false){
                        continuousCount = 0; 
                        emergencyFlag = true;
                    }
                    else{ 
                        // cout << "GIVE UP" << endl;
                        break;
                    }
                }
            }
            else{
                continuousCount = 0; 
                prevSize = invalidEdgeSt.size();
            }

            if(emergencyFlag == false){
                ll x = chooseRandomSt(invalidEdgeSt); 
                subLinkAdjust(invalidEdgeSt, x); 
                // dprint(x, invalidEdgeSt.size());
            }
            else{
                ll x = chooseRandomSt(invalidEdgeSt); 
                emergencyLinkAdjust(invalidEdgeSt, x);
                // dprint(x, invalidEdgeSt.size());
            }
        }

        if(invalidEdgeSt.size() == 0) return true;
        else return false;
    }

    // 時刻tのx番目の辺を削除する
    void subLinkAdjust(set<ll>& invalidEdgeSt, ll x){
        ll t = randInt(eng) % d;
        cut(t, x); 
        kindMat[t][x] = -1;

        bool success = false; 
        ll count = 0; 

        vector<ll> edgeNumberVec; 
        for(ll a : edgeNumberGraph[edges[x].from]){
            if(a != x) edgeNumberVec.push_back(a); 
        }
        for(ll a : edgeNumberGraph[edges[x].to]){
            if(a != x) edgeNumberVec.push_back(a); 
        }
        vector<ll> shuffleEdgeNumberVec = shuffleVec(edgeNumberVec); 

        ll size = shuffleEdgeNumberVec.size(); 
        rep(i, size){
            ll r = shuffleEdgeNumberVec[i]; 
            Edge edge = edges[r]; 
            if(states[t].dc.same(edge.from, edge.to) == false){
                success = true;
                dropEdgeTurn[x].insert(t); 
                dropEdgeTurn[r].erase(t); 
                link(t, r); 
                kindMat[t][r] = 0; 

                if(dropEdgeTurn[r].size() == 0) invalidEdgeSt.insert(r);
                break;
            }
        }

        if(success == true){
            invalidEdgeSt.erase(x); 
        }
        else{
            link(t, x); 
            kindMat[t][x] = 0; 
        }
    }

    // subでは解決できないときに呼び出す
    // 適当に2本の辺を張って解決する
    void emergencyLinkAdjust(set<ll>& invalidEdgeSt, ll x){
        ll t = randInt(eng) % d;
        cut(t, x); 
        kindMat[t][x] = -1;

        ll node1 = edges[x].from; 
        ll node2 = edges[x].to; 

        bool success = false;  

        vector<ll> edgeNumberVec; 
        for(ll a : edgeNumberGraph[edges[x].from]){
            if(a != x) edgeNumberVec.push_back(a); 
        }
        for(ll a : edgeNumberGraph[edges[x].to]){
            if(a != x) edgeNumberVec.push_back(a); 
        }
        vector<ll> shuffleEdgeNumberVec = shuffleVec(edgeNumberVec); 

        for(ll edgeNumber1 : shuffleEdgeNumberVec){
            if(dropEdgeTurn[edgeNumber1].size() <= 1) continue;   // 空きが一個しかないと無理
            else if(useMat[t][edgeNumber1] == true) continue;   // すでに使われているならだめ

            ll to1;
            if(edges[edgeNumber1].from != node1 && edges[edgeNumber1].from != node2) to1 = edges[edgeNumber1].from;
            else if(edges[edgeNumber1].to != node1 && edges[edgeNumber1].to != node2) to1 = edges[edgeNumber1].to; 
            else{
                print("EMERGENCY ERROR in Total::emergencyLinkAdjust"); 
                exit(EXIT_FAILURE); 
            }

            link(t, edgeNumber1); 
            for(ll edgeNumber2 : edgeNumberGraph[to1]){
                // tprint(node1, node2, to1);
                // tprint(x, edgeNumber1, edgeNumber2);
                if(dropEdgeTurn[edgeNumber2].size() <= 1) continue;   // 空きが一個しかないと無理
                else if(edgeNumber1 == edgeNumber2) continue;
                else if(useMat[t][edgeNumber2] == true) continue;

                link(t, edgeNumber2); 
                if(states[t].dc.same(node1, node2) == true){
                    success = true;
                    kindMat[t][edgeNumber1] = 0; 
                    kindMat[t][edgeNumber2] = 0;
                    invalidEdgeSt.erase(x);
                    return;
                }
                else cut(t, edgeNumber2); 
            }
            cut(t, edgeNumber1); 
        }

        kindMat[t][x] = 0; 
        link(t, x); 
    }

    bool rebalance(){
        vector<ll> invalidVec; 
        rep(t, d){
            if(dropTurnEdge[t].size() > k) invalidVec.push_back(t); 
        }

        while(invalidVec.size() != 0){
            if(clock() - START > INIT_END_TIME) return false; 
            ll r = randInt(eng) % (ll)invalidVec.size(); 
            subRebalance(invalidVec, invalidVec[r]); 
        }

        if(invalidVec.size() == 0) return true;
        else return false;
    }

    void subRebalance(vector<ll>& invalidVec, ll t){
        ll r = randInt(eng) % (ll)dropTurnEdge[t].size(); 
        auto it = dropTurnEdge[t].begin(); 
        rep(_, r) it++;
        ll tar = *it;

        if(kindMat[t][tar] != -1){
            print("ERROR");
            exit(EXIT_FAILURE);
        }
        
        ll count = 0; 
        set<ll> visitSt; 
        while(count < 10){
            count++;
            ll a = randInt(eng) % d; 
            if(bs(visitSt, a) == true) continue;
            visitSt.insert(a); 

            if(searchVec(invalidVec, a) == true) continue;
            if(kindMat[a][tar] == 1){
                cut(a, tar);
                link(t, tar); 
                kindMat[a][tar] = -1;
                kindMat[t][tar] = 1;
                if(isValidIndex(a) == false) invalidVec.push_back(a);
                if(isValidIndex(t) == true) deleteVec(invalidVec, t); 
                break;
            }
        }
    }

    void sa(){
        ll updateCount = 0; 

        while(true){
            double pos_time = clock() - START;
            if(pos_time > END_TIME) break;

            // ll r = randInt(eng) % 3;

            // if(r == 0) sa_transition_swap(updateCount); 
            // else sa_transition_give(updateCount); 
            // sa_transition_swap(updateCount);

            // sa_transition_node(updateCount); 
            sa_transition_edge(updateCount);
        }

        // print(updateCount);
    }

    void sa_transition_swap(ll& updateCount){
        ll t1 = randInt(eng) % d; 
        ll t2 = randInt(eng) % d; 
        if(t1 == t2 || dropTurnEdge[t1].size() == 0 || dropTurnEdge[t2].size() == 0) return;

        // t1にx2を追加、x1を削除
        ll x2 = chooseRandomSt(dropTurnEdge[t1]); 
        ll x1 = chooseRandomSt(dropTurnEdge[t2]); 

        cut(t1, x1); 
        link(t1, x2); 
        if(same(t1, x1) == false){
            link(t1, x1); 
            cut(t1, x2); 
            return; 
        }

        cut(t2, x2); 
        link(t2, x1); 
        if(same(t2, x2) == false){
            // t1も戻す必要があることに注意
            link(t1, x1); 
            cut(t1, x2); 

            link(t2, x2); 
            cut(t2, x1); 
            return; 
        }

        vector<ll> monteVec = cluster.sampling(); 
        
        ll afterScore = calcDistSum(t1, monteVec) + calcDistSum(t2, monteVec); 

        // 元に戻す
        link(t1, x1); 
        cut(t1, x2);
        link(t2, x2); 
        cut(t2, x1); 

        ll prevScore = calcDistSum(t1, monteVec) + calcDistSum(t2, monteVec);

        // 得点が改善されたら更新する
        if(afterScore < prevScore){
            updateCount++;
            cut(t1, x1); 
            link(t1, x2); 
            cut(t2, x2); 
            link(t2, x1); 
        }
    }

    void sa_transition_give(ll& updateCount){
        ll t1 = randInt(eng) % d; 
        ll t2 = randInt(eng) % d; 

        // すでに辺が多く落ちているときはダメ
        if(dropTurnEdge[t2].size() >= k) return;
        else if(dropTurnEdge[t1].size() == 0) return;
        else if(t1 == t2) return;

        // t2からt1に辺xを与える
        ll x = chooseRandomSt(dropTurnEdge[t1]); 

        cut(t2, x); 
        if(same(t2, x) == false){
            link(t2, x); 
            return;
        }

        vector<ll> monteVec = cluster.sampling(); 

        link(t1, x); 
        ll afterScore = calcDistSum(t1, monteVec) + calcDistSum(t2, monteVec); 

        link(t2, x);
        cut(t1, x);  

        ll prevScore = calcDistSum(t1, monteVec) + calcDistSum(t2, monteVec); 

        if(afterScore < prevScore){
            updateCount++;
            cut(t2, x); 
            link(t1, x);
        }
    }

    void sa_transition_destroy(ll& updateCount){

    }

    void link(ll t, ll i, bool update = false){
        if(useMat[t][i] == true){
            print("ALREADY LINK in Total::link");
            exit(EXIT_FAILURE); 
        }
        states[t].link(i);
        useMat[t][i] = true;
        dropEdgeTurn[i].erase(t);
        dropTurnEdge[t].erase(i);
    }

    void cut(ll t, ll i, bool update = false){
        if(useMat[t][i] == false){
            print("NOT LINK IN Total::cut"); 
            exit(EXIT_FAILURE); 
        }
        states[t].cut(i); 
        useMat[t][i] = false;
        dropEdgeTurn[i].insert(t);
        dropTurnEdge[t].insert(i);
    }

    // edgeの両端が同じ組に所属しているか
    bool same(ll t, ll x){
        bool ret = states[t].dc.same(edges[x].from, edges[x].to); 
        return ret; 
    }

    bool isValidIndex(ll t){
        if(dropTurnEdge[t].size() > k) return false;
        else return true;
    }

    void deleteVec(vector<ll>& v, ll x){
        ll size = v.size(); 
        rep(i, size){
            if(v[i] == x){
                swap(v[i], v[size - 1]); 
                v.pop_back(); 
                return; 
            }
        }

        print("CANT DELETE in Total::deleteVec"); 
        exit(EXIT_FAILURE); 
    }

    // 配列からランダムに削除する
    void deleteRandomVec(vector<ll>& v){
        ll size = v.size();
        ll x = randInt(eng) % size; 
        swap(v[x], v[size - 1]); 
        v.pop_back();
    }

    ll chooseRandomSt(set<ll>& st){
        auto it = st.begin(); 
        ll size = st.size(); 
        ll r = randInt(eng) % size; 
        rep(i, r) it++;
        ll ret = *it; 
        return ret; 
    }

    vector<ll> shuffleVec(vector<ll>& v){
        set<ll> st; 
        for(ll x : v) st.insert(x); 
        vector<ll> ret;
        PQ<P> pq;
        auto it = st.begin(); 
        auto end = st.end(); 
        while(it != end){
            ll r = randInt(eng);
            pq.push(P(r, *it)); 
            it++;
        }
        while(!pq.empty()){
            ret.push_back(pq.top().second); 
            pq.pop(); 
        }
        return ret;
    }

    bool searchVec(vector<ll>& v, ll t){
        for(ll x : v){
            if(t == x) return true;
        }
        return false;
    }

    vector<ll> getDropTurn(){
        vector<ll> ret(m, -1); 
        rep(i, m){
            if(dropEdgeTurn[i].size() == 0) continue;
            auto it = dropEdgeTurn[i].begin();
            ret[i] = *it;
        }
        return ret;
    }

    void printAns(){
        vector<ll> dropTurns = getDropTurn(); 
        for(ll x : dropTurns){ 
            if(x == -1){
                print(""); 
                print("INVALID ANSWER"); 
                exit(EXIT_FAILURE);
            }
            cout << x + 1 << " ";
        }
        cout << endl;
    }

    ll calcDistSum(ll t, vector<ll>& vec){
        clock_t aa = clock(); 

        /*
        CostGraph costGraph = init_costGraph(n);
        ll size = edges.size(); 
        rep(i, size){
            if(bs(dropTurnEdge[t], i) == false){
                P p1(edges[i].from, edges[i].weight); 
                P p2(edges[i].to, edges[i].weight); 
                costGraph[edges[i].to].push_back(p1); 
                costGraph[edges[i].from].push_back(p2);
            }
        }
        */

        vector<bool> existEdge(m, true); 
        irep(it, dropTurnEdge[t]){
            existEdge[*it] = false;
        }

        ll ret = 0; 
        for(ll x : vec){
            vector<ll> dis = dijkstra(existEdge, x); 
            // vector<ll> dis = dijkstra_radix_heap<ll>(costGraph, x);
            for(ll y : dis) ret += y; 
        }

        return ret;
    }

    vector<ll> dijkstra(vector<bool>& existEdge, ll s){
        const ll INF = INT_MAX; 
        const ll N = edgeGraph.size();
        vector<ll> dis(N, INF); 
        IQ<P> pq; 
        dis[s] = 0;
        pq.emplace(dis[s], s);
        while(!pq.empty()){
            auto [dv, v] = pq.top();
            pq.pop();
            if(dis[v] < dv) continue;
            for(auto&& e : edgeGraph[v]){
                if(existEdge[e.number] == false) continue; 
                ll cost = dis[v] + e.weight;
                if(dis[e.to] > cost){
                    dis[e.to] = cost;
                    pq.emplace(cost, e.to);
                }
            }
        }
        return dis;
    }

    // 見つけたいノードまでの距離が確定したら、その時点で計算終了
    // mapにした方が早い？？？
    vector<ll> limitedDijkstra(ll t, ll s, vector<ll>& targetVec){
        // targetVecをsetに変換
        set<ll> targetSt; 
        for(ll x : targetVec) targetSt.insert(x);

        const ll INF = INT_MAX; 
        const ll N = edgeGraph.size();
        vector<ll> dis(N, INF); 
        IQ<P> pq; 
        dis[s] = 0;
        targetSt.erase(s);
        pq.emplace(dis[s], s);
        while(!pq.empty() && targetSt.size() != 0){
            auto [dv, v] = pq.top();
            pq.pop();
            if(dis[v] < dv) continue;
            for(auto&& e : edgeGraph[v]){
                if(useMat[t][e.number] == false) continue;
                ll cost = dis[v] + e.weight;
                if(dis[e.to] > cost){
                    dis[e.to] = cost;
                    targetSt.erase(e.to); 
                    pq.emplace(cost, e.to);
                }
            }
        }
        return dis;
    }

    ll calcNodeDistSum(ll targetNode, ll maxDepth, Graph& prevDropGraph, Graph& afterDropGraph){
        vector<ll> miniBatch = calcMiniBatch(targetNode, maxDepth); 
        vector<ll> neighborVec = calcMiniBatch(targetNode, 1); 
        ll ret = 0; 
        rep(t, d){
            if(isSameVector(prevDropGraph[t], afterDropGraph[t]) == true) continue;
            for(ll center : neighborVec){
                vector<ll> distVec = limitedDijkstra(t, center, miniBatch); 
                for(ll x : miniBatch) ret += distVec[x]; 
            }
        }
        return ret;
    }

    vector<ll> calcMiniBatch(ll s, ll maxDepth){
        set<ll> visit;
        visit.insert(s); 
        dfsCalcMiniBatch(s, visit, 0, maxDepth); 
        vector<ll> ret; 
        irep(it, visit) ret.push_back(*it); 
        return ret; 
    }

    void dfsCalcMiniBatch(ll pos, set<ll>& visit, ll d, ll maxDepth){
        if(d == maxDepth) return; 
        for(Edge& edge : edgeGraph[pos]){
            ll next = edge.to; 
            if(bs(visit, next) == false){
                visit.insert(next); 
                dfsCalcMiniBatch(next, visit, d + 1, maxDepth); 
            }
        }
    }

    void sa_transition_node(ll& updateCount){
        clock_t aa = clock(); 

        ll targetNode = randInt(eng) % n; 
        ll edgeSize = edgeGraph[targetNode].size(); 
        vector<ll> dropVec(edgeSize, -1); 
        rep(i, edgeSize) dropVec[i] = randInt(eng) % d;

        Graph prevDropGraph = init_graph(d); 
        Graph afterDropGraph = init_graph(d);  

        // リンクした時とカットした時に入れる。元に戻す時に使う
        vector<P> linkVec; 
        vector<P> cutVec;

        for(Edge& edge : edgeGraph[targetNode]){
            auto it = dropEdgeTurn[edge.number].begin(); 
            ll dropTurn = *it; 
            link(dropTurn, edge.number); 
            linkVec.push_back(P(dropTurn, edge.number)); 
            prevDropGraph[dropTurn].push_back(edge.number); 
        }
        rep(i, edgeSize){
            ll edgeNumber = edgeGraph[targetNode][i].number; 
            ll dropTurn = dropVec[i]; 
            cut(dropTurn, edgeNumber); 
            cutVec.push_back(P(dropTurn, edgeNumber)); 
            afterDropGraph[dropTurn].push_back(edgeNumber); 
        }

        bool success = true;
        rep(t, d){
            if(isValidIndex(t) == false){ 
                success = false;
                break;
            }
        }
        rep(t, d){
            if(success == false) break;
            for(Edge& edge : edgeGraph[targetNode]){
                if(useMat[t][edge.number] == true) continue;
                else if(same(t, edge.number) == false){ 
                    success = false; 
                    break;
                }
            }
        }

        if(success == false){
            undo_sa_transition_node(linkVec, cutVec); 
            // dprint("failure :", clock() - aa);
            return; 
        }

        // vector同一判定のためにはsort済みである必要がある
        rep(t, d) sort(all(prevDropGraph[t])); 
        rep(t, d) sort(all(afterDropGraph[t])); 

        updateCount++;

        ll maxDepth = 5; 
        ll afterNodeDistSum = calcNodeDistSum(targetNode, maxDepth, prevDropGraph, afterDropGraph); 

        undo_sa_transition_node(linkVec, cutVec); 
        ll prevNodeDistSum = calcNodeDistSum(targetNode, maxDepth, prevDropGraph, afterDropGraph); 

        // 改善したら遷移を取り入れる
        if(afterNodeDistSum < prevNodeDistSum){
            redo_sa_transition_node(linkVec, cutVec); 
        }

        // dprint("success :", clock() - aa);
    }

    void undo_sa_transition_node(vector<P>& linkVec, vector<P>& cutVec){
        // 同一辺をリンクしてカットする場合バグるので、リンクとカットはこの順番である必要がある
        for(P& p : cutVec) link(p.first, p.second);
        for(P& p : linkVec) cut(p.first, p.second);  
    }

    void redo_sa_transition_node(vector<P>& linkVec, vector<P>& cutVec){
        for(P& p : linkVec) link(p.first, p.second); 
        for(P& p : cutVec) cut(p.first, p.second); 
    }

    void sa_transition_edge(ll& updateCount){
        ll maxDepth = 2; 
        ll targetEdge = randInt(eng) % m; 

        updateCount++;

        auto targetTurnIt = dropEdgeTurn[targetEdge].begin(); 
        ll targetTurn = *targetTurnIt;

        vector<ll> miniBatch = calcMiniBatchEdge(targetEdge, maxDepth); 
        vector<ll> neighborVec = calcMiniBatchEdge(targetEdge, 1); 

        ll prevTargetTurnDist = calcNodeDistSumEdge(targetTurn, targetEdge, maxDepth, miniBatch, neighborVec); 
        link(targetTurn, targetEdge); 
        ll afterTargetTurnDist = calcNodeDistSumEdge(targetTurn, targetEdge, maxDepth, miniBatch, neighborVec);

        ll bestScore = 0; 
        ll bestTurn = -1;

        // vector<ll> sampleTurnVec = sampleTurn(targetTurn, 5); 
        vector<ll> sampleTurnVec = sampleTurnByWeight(targetEdge, targetTurn, 5); 
        for(ll t : sampleTurnVec){
            if(dropTurnEdge[t].size() >= k) continue;   // 多すぎ
            cut(t, targetEdge); 
            if(same(t, targetEdge) == false){ 
                // くっついてない
                link(t, targetEdge);
                continue;   
            }
            ll afterSwapTurnDist = calcNodeDistSumEdge(t, targetEdge, maxDepth, miniBatch, neighborVec); 
            link(t, targetEdge);
            ll prevSwapTurnDist = calcNodeDistSumEdge(t, targetEdge, maxDepth, miniBatch, neighborVec);
            ll prevScore = prevTargetTurnDist + prevSwapTurnDist; 
            ll afterScore = afterTargetTurnDist + afterSwapTurnDist; 
            ll dScore = prevScore - afterScore;   // これが大きい方が良い
            if(dScore > bestScore){
                bestScore = dScore; 
                bestTurn = t; 
            }
        }

        if(bestTurn < 0){
            // なにもしな方がよかった
            cut(targetTurn, targetEdge);
        }
        else{
            cut(bestTurn, targetEdge); 
        }
    }

    // edgeの周辺のnodeを取る
    vector<ll> calcMiniBatchEdge(ll targetEdge, ll maxDepth){
        set<ll> st; 
        vector<ll> nodeVec; 
        Edge edge = edges[targetEdge]; 
        nodeVec.push_back(edge.from); 
        nodeVec.push_back(edge.to); 
        for(ll x : nodeVec){
            vector<ll> memo = calcMiniBatch(x, maxDepth);
            for(ll y : memo) st.insert(y);  
        }
        vector<ll> ret; 
        irep(it, st) ret.push_back(*it); 
        return ret; 
    }

    vector<ll> calcMiniBatchEdge(vector<ll>& targetEdgeVec, ll maxDepth){
        set<ll> st; 
        for(ll x : targetEdgeVec){
            vector<ll> v = calcMiniBatch(x, maxDepth); 
            for(ll y : v) st.insert(y);
        }
        vector<ll> ret; 
        irep(it, st) ret.push_back(*it); 
        return ret; 
    }

    ll calcNodeDistSumEdge(ll t, ll targetEdge, ll maxDepth, vector<ll>& miniBatch, vector<ll>& neighborVec){
        ll ret = 0; 
        for(ll center : neighborVec){
            vector<ll> distVec = limitedDijkstra(t, center, miniBatch); 
            for(ll x : miniBatch) ret += distVec[x]; 
        }
        return ret;
    }

    // 時刻tで番号iの周りで落ちている辺の数を調べる
    vector<ll> countDropEdge(ll edgeNumber){
        Edge edge = edges[edgeNumber]; 
        vector<ll> v{edge.to, edge.from};
        vector<ll> ret(d, 0); 
        for(ll x : v){
            for(Edge& edge : edgeGraph[x]){
                if(edgeNumber == edge.number) continue;
                auto it = dropEdgeTurn[edge.number].begin(); 
                ret[*it]++;
            }
        }
        return ret;
    }

    vector<ll> sampleTurnByWeight(ll edgeNumber, ll targetTurn, ll k){
        vector<ll> dropCountVec = countDropEdge(edgeNumber); 
        set<ll> st; 
        rep(_, k){
            ll tar = subSampleTurnByWeight(dropCountVec, targetTurn); 
            st.insert(tar); 
        }
        vector<ll> ret; 
        irep(it, st) ret.push_back(*it); 
        return ret; 
    }

    ll subSampleTurnByWeight(vector<ll>& v, ll targetTurn){
        ll size = v.size(); 
        vector<ll> weight{0}; 
        rep(i, size){
            // 1を足しておく、全てゼロとなることがあるっぽい
            if(i != targetTurn) weight.push_back(weight[i] + v[i]); 
            else weight.push_back(weight[i]); 
        }
        // vprint(weight);
        ll last = weight[size]; 
        ll r = randInt(eng) % last; 
        rep(i, size){
            if(weight[i] <= r && r < weight[i + 1]){
                return i;
            }
        }
        print("ERROR"); 
        return 0; 
    }

    // sort済みである必要がある
    bool isSameVector(vector<ll>& v1, vector<ll>& v2){
        if(v1.size() != v2.size()) return false;
        ll size = v1.size();
        rep(i, size){
            if(v1[i] != v2[i]) return false;
        }
        return true;
    }

    // t以外からk個サンプリングする
    vector<ll> sampleTurn(ll t, ll k){
        set<ll> st; 
        rep(i, k){
            ll r = randInt(eng) % d; 
            if(r == t) continue;
            else st.insert(r);
        }
        vector<ll> ret;
        irep(it, st) ret.push_back(*it); 
        return ret; 
    }
}; 

void makeRandomAns(){
    vector<ll> v(m);
    rep(i, m) v[i] = (i % d) + 1;
    vprint(v); 
}

int main(){
    START = clock();

    cin >> n >> m >> d >> k; 
    rep(i, m){
        ll x, y, w;
        cin >> x >> y >> w; 
        x--; y--; 
        edges.push_back(Edge(i, x, y, w)); 
    }

    edgeNumberGraph = init_graph(n);
    edgeGraph = vector<vector<Edge>>(n); 
    for(Edge& edge : edges){
        edgeNumberGraph[edge.from].push_back(edge.number); 
        edgeNumberGraph[edge.to].push_back(edge.number); 
        Edge edge1 = edge; 
        Edge edge2 = edge;
        swap(edge2.from, edge2.to); 
        edgeGraph[edge.from].push_back(edge1); 
        edgeGraph[edge.to].push_back(edge2);
    }

    costGraph = init_costGraph(n);
    for(Edge& edge : edges){
        P p1(edge.to, edge.weight); 
        P p2(edge.from, edge.weight); 
        costGraph[edge.from].push_back(p1); 
        costGraph[edge.to].push_back(p2); 
    }

    rep(i, n){
        ll y, x;
        cin >> y >> x;
        y -= 500;   x -= 500;
        nodes.push_back(P(y, x)); 
    }
    cluster.init(); 

    /*
    Total total(n, m, d, k); 
    bool initSuccess = total.init(); 
    if(initSuccess == true) total.printAns();
    else makeRandomAns(); 
    */

    Total total; 
    bool initSuccess = false;
    while(true){
        double lapse = clock() - START; 
        if(lapse > END_TIME) break;
        total = Total(n, m, d, k); 
        bool success = total.init(); 
        if(success == true){
            initSuccess = true;
            break;
        } 
        else{
            // cout << clock() - START << endl;
            // print("RESET");
        }
    }

    // cout << "FOUND:" << clock() - START << endl;

    if(initSuccess == true){ 
        total.sa(); 
        total.printAns();
    }
    else makeRandomAns(); 

    // Debug db; 
    // db.judgeUnify(total.getDropTurn());
}
