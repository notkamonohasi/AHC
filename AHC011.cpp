#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
//#define MOD 1000000007
#define MOD 998244353
#define ll int
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
#define bs(v, k) binary_search(v.begin(), v.end(), k)
#define lb(v, k) lower_bound(v.begin(), v.end(), k)
#define ub(v, k) upper_bound(v.begin(), v.end(), k)
#define all(v) v.begin(), v.end()
using namespace std;

//const ll INF = LLONG_MAX;
//const ll LIMIT = pow(2, 60);
//const ll vec[][2] = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
const ll VEC[][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
//const ld PI = 3.141592653589793238462643;

ll POW(ll a, ll n){if(n == 0) return 1; if(n == 1) return a; if(n % 2 == 1) return (a * POW(a, n - 1)); ll t = POW(a, n / 2); return (t * t);}
ll CEIL(ll a, ll b){ll ret = (a + b - 1) / b; return ret;}
ll max(ll a, ll b){if(a > b) return a; else return b;}
ll min(ll a, ll b){if(a > b) return b; else return a;}
ll max(ll a, ll b, ll c){ll d = max(a, b); return max(c, d);}
ll min(ll a, ll b, ll c){ll d = min(a, b); return min(c, d);}
void yes(bool b){if(b) cout << "Yes" << endl; else cout << "No" << endl;}
using P = pair<ll, ll>;
using T = tuple<ll, ll, ll>; // ll x, y, z; tie(x, y, z) = T
using Graph = vector<vector<ll> >;
using Mat = vector<vector<ll> >;
template<typename T> using PQ = priority_queue<T>;
template<typename T> using IQ = priority_queue<T, vector<T>, greater<T>>;
Graph init_graph(ll V){Graph ret; vector<ll> empty; rep(i, V) ret.push_back(empty); return ret;}
Mat init_mat(ll a, ll b, ll c = 0){Mat ret; vector<ll> empty; rep(i, b) empty.push_back(c); rep(i, a) ret.push_back(empty); return ret;}

Mat orders = {
      {0, 2, 15, 13, 7, 5, 1, 4, 3, 6, 9, 12, 14, 10, 11, 8}   // 先に横を使い切りたい、ただし上向きは最後に使いにくいので最初に消費する
    , {0, 15, 14, 13, 11, 7, 12, 10, 9, 6, 3, 5, 8, 4, 2, 1}   // とにかく手が多いのから使っていく
    , {0, 2, 15, 14, 11, 10, 9, 13, 12, 8, 7, 6, 5, 3, 1, 4}
    , {0, 1, 2, 4, 8, 3, 5, 6, 9, 10, 12, 7, 11, 13, 14, 15}
};

vector<int> time_vec = {900000, 1700000, 2500000, 2700000};
const int TOTAL_END_TIME = 2950000;
const int RAND_K = 4;

random_device rd;
mt19937 eng(rd());
uniform_int_distribution<> randInt(0, INT_MAX);

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
            int l,r,sz;
            T val=et,sum=et;
            bool exact;
            bool child_exact;
            bool edge_connected=0;
            bool child_edge_connected=0;
            node(){}
            node(int l,int r):l(l),r(r),sz(l==r),exact(l<r),child_exact(l<r){}
            bool is_root() {
                return !p;
            }
        };
        vector<unordered_map<int,np>>ptr;
        np get_node(int l,int r){
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
        int size(np t){return t?t->sz:0;}
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
        euler_tour_tree(int sz){
            ptr.resize(sz);
            for(int i=0;i<sz;i++)ptr[i][i]=new node(i,i);
        }
        int size(int s){
            np t=get_node(s,s);
            splay(t);
            return t->sz;
        }
        bool same(int s,int t){
            return same(get_node(s,s),get_node(t,t));
        }
        void set_size(int sz){
            ptr.resize(sz);
            for(int i=0;i<sz;i++)ptr[i][i]=new node(i,i);
        }
        void update(int s,T x){
            np t=get_node(s,s);
            splay(t);
            t->val=fn(t->val,x);
            update(t);
        }
        void edge_update(int s,auto g){
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
        bool try_reconnect(int s,auto f){
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
        void edge_connected_update(int s,bool b){
            np t=get_node(s,s);
            splay(t);
            t->edge_connected=b;
            update(t);
        }
        bool link(int l,int r){
            if(same(l,r))return 0;
            merge(reroot(get_node(l,l)),get_node(l,r),reroot(get_node(r,r)),get_node(r,l));
            return 1;
        }
        bool cut(int l,int r){
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
        T get_sum(int p,int v){
            cut(p,v);
            np t=get_node(v,v);
            splay(t);
            T res=t->sum;
            link(p,v);
            return res;
        }
        T get_sum(int s){
            np t=get_node(s,s);
            splay(t);
            return t->sum;
        }
    };
    int dep=1;
    vector<euler_tour_tree> ett;
    vector<vector<unordered_set<int>>>edges;
    int sz;
    public:
    dynamic_connectivity(){}   // 追加
    dynamic_connectivity(int sz):sz(sz){
        ett.emplace_back(sz);
        edges.emplace_back(sz);
    }
    bool link(int s,int t){
        if(s==t)return 0;
        if(ett[0].link(s,t))return 1;
        edges[0][s].insert(t);
        edges[0][t].insert(s);
        if(edges[0][s].size()==1)ett[0].edge_connected_update(s,1);
        if(edges[0][t].size()==1)ett[0].edge_connected_update(t,1);
        return 0;
    }
    bool same(int s,int t){
        return ett[0].same(s,t);
    }
    int size(int s){
        return ett[0].size(s);
    }
    vector<int>get_vertex(int s){
        return ett[0].vertex_list(s);
    }
    void update(int s,T x){
        ett[0].update(s,x);
    }
    T get_sum(int s){
        return ett[0].get_sum(s);
    }
    bool cut(int s,int t){
        if(s==t)return 0;
        for(int i=0;i<dep;i++){
            edges[i][s].erase(t);
            edges[i][t].erase(s);
            if(edges[i][s].size()==0)ett[i].edge_connected_update(s,0);
            if(edges[i][t].size()==0)ett[i].edge_connected_update(t,0);
        }
        for(int i=dep-1;i>=0;i--){
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
    bool try_reconnect(int s,int t,int k){
        for(int i=0;i<k;i++){
            ett[i].cut(s,t);
        }
        for(int i=k;i>=0;i--){
            if(ett[i].size(s)>ett[i].size(t))swap(s,t);
            auto g=[&](int s,int t){ett[i+1].link(s,t);};
            ett[i].edge_update(s,g);
            auto f=[&](int x)->bool{
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
                        for(int j=0;j<=i;j++){
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

dynamic_connectivity<int> ds;
int n, t;
vector<vector<vector<bool>>> resp, wall_resp, link;
int tile[16];
Mat field, target, pos_field, start_field;
clock_t start; 
int sy, sx;
vector<int> arm_vec;
vector<Mat> all_target; 

char encode(int k){
    if(k == -1) return '0';
    else if(0 <= k && k <= 9) return '0' + k;
    else return 'a' + (k - 10);
}
int decode(char c){
    if('0' <= c && c <= '9') return c - '0';
    else return 10 + (c - 'a');
}
int count_flag(int k){
    int ret = 0;
    rep(i, 4){
        if(k & (1 << i)) ret++;
    }
    return ret;
}
int ret_num(int y, int x){
    return y * n + x;
}
void print_mat(Mat mat){
    rep(i, n){
        rep(j, n){
            cout << encode(mat[i][j]);
        }
        cout << endl;
    }
    cout << endl;
}


class MakeRoute{
public : 
    int n;
    Mat pos_field; 
    Mat target_field;

    MakeRoute(Mat m1, Mat m2){
        pos_field = m1;
        target_field = m2; 
        n = len(m1); 
    }

    string make(){
        string ans = "";
        bool start_flag = true;
        Mat fix = init_mat(n, n, 0);
        P hole = search_hole();
    
        rep(i, n - 2){
            rep(j, n){
                int target_num = make_target_num(i, j);
                P tar = make_tar(i, j);
                P pos = decide_target(target_num, tar, fix);
                
                if(pos.first == tar.first && pos.second == tar.second){
                    fix[tar.first][tar.second] = 1;
                    continue;
                }
                else{
                    string move = make_usual_move(pos, tar, hole, start_flag, fix);
                    if(move == "-1") return "-1";
                    else ans += move;
                    fix[tar.first][tar.second] = 1;
                    start_flag = false;   // 一回でも行動したらこれをfalseにする
                }
            }
            ans += make_last_move(hole, i);
            fix[i][n - 1] = 1;
            fix[i + 1][n - 2] = 0;
        }
        
        rep(j, n - 2){
            for(int i = n - 1; i >= n - 2; i--){
                int target_num = make_target_num(i, j); 
                P tar = make_tar(i, j);
                P pos = decide_target(target_num, tar, fix);
                
                if(pos.first == tar.first && pos.second == tar.second){
                    fix[tar.first][tar.second] = 1;
                    continue;
                }
                else{ 
                    ans += make_last_2_move(pos, tar, hole, fix);
                    fix[tar.first][tar.second] = 1;
                }
            }

            ans += make_last_arrange_move(hole, j);
            fix[n - 1][j] = 1;
            fix[n - 2][j + 1] = 0;
        }
        
        string last_move = make_totally_last_move();
        if(last_move == "-1"){
            // print("impossible");
            ans = "-1";
        } 
        else ans += last_move;

        return ans;
    }

    bool inside(int y, int x){
        if(y < 0 || y >= n) return false;
        if(x < 0 || x >= n) return false;
        return true;
    }
    P search_hole(){
        rep(i, n){
            rep(j, n){
                if(pos_field[i][j] == 0) return make_pair(i, j);
            }
        }
        return make_pair(-1, -1);
    }
    P search_hole(Mat& mat){
        rep(i, n){
            rep(j, n){
                if(mat[i][j] == 0) return make_pair(i, j);
            }
        }
        return make_pair(-1, -1);
    }
    Mat copy_mat(Mat& mat){
        int n = len(mat);
        Mat ret = init_mat(n, n);
        rep(i, n){
            rep(j, n){
                ret[i][j] = mat[i][j];
            }
        }
        return ret;
    }

    P ret_next(P p, char c){
        if(c == 'L') return make_pair(p.first, p.second - 1);
        else if(c == 'U') return make_pair(p.first - 1, p.second);
        else if(c == 'R') return make_pair(p.first, p.second + 1);
        else if(c == 'D') return make_pair(p.first + 1, p.second);
        else{
            // print("ERROR in ret_next");
            return make_pair(-1, -1);
        }
    }

    P ret_next(P& p, string& s){
        P ret = make_pair(p.first, p.second);
        rep(i, len(s)) ret = ret_next(ret, s[i]);
        return ret; 
    }

    bool _judge_valid_random_action(string& s, char c){
        if(len(s) == 0) return true;
        else{
            char last = s[len(s) - 1];
            if(last == 'R' && c == 'L') return false;
            else if(last == 'L' && c == 'R') return false;
            else if(last == 'U' && c == 'D') return false;
            else if(last == 'D' && c == 'U') return false;
            else return true;
        }
    }

    char _make_random_action(){
        int a = randInt(eng) % 4;
        if(a == 0) return 'L';
        else if(a == 1) return 'U';
        else if(a == 2) return 'R';
        else if(a == 3) return 'D';
        else{
            // print("ERROR in _make_random_action");
            return 'A';
        }
    }

    string make_random_action(P& p, int k){
        string ret = "";
        while(len(ret) < k){
            char c = _make_random_action();
            if(_judge_valid_random_action(ret, c) == true){
                string memo = ret + c;
                P next = ret_next(p, memo);
                if(inside(next.first, next.second)) ret = memo;
            }
        }
        return ret; 
    }

    Mat simulate(Mat& mat, string& s){
        Mat ret = copy_mat(mat); 
        P hole = search_hole(mat);
        int k = len(s);
        rep(i, k){
            P next = ret_next(hole, s[i]); 
            swap(ret[hole.first][hole.second], ret[next.first][next.second]); 
            hole = next;
        }

        return ret;
    }

    pair<string, string> update_little(string& s){
        Mat before = copy_mat(pos_field);
        Mat m1 = simulate(pos_field, s);
        P hole = search_hole(m1);
        int k = randInt(eng) % 6 + RAND_K;
        string rand_action = make_random_action(hole, k); 
        Mat m2 = simulate(m1, rand_action);
        pos_field = m2;
        string ret1 = s + rand_action;
        string ret2 = make(); 

        pos_field = before;   // pos_fieldを元に戻しておく

        return make_pair(ret1, ret2);  
    }

    void myswap(P& pos, P& hole, string& ret){
        if(abs(pos.first - hole.first) + abs(pos.second - hole.second) != 1){
            // cout << "ERROR in myswap" << endl;
            // print_mat(pos_field);
            // print_mat(target_field);
            return;
        }
        else{
            swap(pos_field[pos.first][pos.second], pos_field[hole.first][hole.second]);
            if(pos.first - hole.first == 1){
                hole.first = hole.first + 1;
                pos.first = pos.first - 1;
                ret += "D";
            }
            else if(pos.first - hole.first == -1){
                hole.first = hole.first - 1;
                pos.first = pos.first + 1;
                ret += "U";
            }
            else if(pos.second - hole.second == 1){
                hole.second = hole.second + 1;
                pos.second = pos.second - 1 ;
                ret += "R";
            }
            else{
                hole.second = hole.second - 1;
                pos.second = pos.second + 1;
                ret += "L";
            }
        }
    }


    void myswap(string dir, P& hole, string& ret){
        P _pos;
        if(dir == "D") _pos = make_pair(hole.first + 1, hole.second);
        else if(dir == "U") _pos = make_pair(hole.first - 1, hole.second);
        else if(dir == "R") _pos = make_pair(hole.first, hole.second + 1);
        else if(dir == "L") _pos = make_pair(hole.first, hole.second - 1);
        else print("ERROR in myswap string"); 

        myswap(_pos, hole, ret);
    }


    string make_hole_action_tate(P& pos, P tar, P& hole, Mat& fix){
        string ret = "";

        if(fix[tar.first][hole.second] == 1){
            if(tar.second > hole.second){
                int _t = tar.second - hole.second;
                rep(_, _t) myswap("R", hole, ret);
            }
            else if(tar.second < hole.second){
                int _t = hole.second - tar.second;
                rep(_, _t) myswap("L", hole, ret);
            }
            else{
                // print("よく分からん"); 
            }
        }
        
        // まず上下方向を揃える
        if(hole.first > tar.first){
            int _t = hole.first - tar.first;
            rep(_, _t){ 
                myswap("U", hole, ret);
            }
        }
        else{
            int _t = tar.first - hole.first;
            rep(_, _t){ 
                myswap("D", hole, ret);
            }
        }
        
        // 次に横方向を揃える
        if(hole.second > tar.second){
            int _t = hole.second - tar.second;
            rep(_, _t){ 
                myswap("L", hole, ret);
                if(hole.first == pos.first && hole.second == pos.second){ 
                    pos = make_pair(hole.first, hole.second + 1);
                    break;   // 入れ替わったらその時点でこのphaseを終了できる、設計時点では考えていなくて、かなり場当たり的
                }
            }
        }
        else{
            int _t = tar.second - hole.second;
            rep(_, _t){ 
                myswap("R", hole, ret);
                if(hole.first == pos.first && hole.second == pos.second){ 
                    pos = make_pair(hole.first, hole.second - 1);
                    break;   // 入れ替わったらその時点でこのphaseを終了できる、設計時点では考えていなくて、かなり場当たり的
                }
            }
        }
        
        return ret; 
    }


    // dirで上を通るか下を通るかを決定、defaultで"U"にしておく
    void move_right(P& pos, P& hole, string& s, string dir){
        string ret;
        if(dir != "U" && dir != "D") print("ERROR in move_right");

        if(dir == "U") myswap("U", hole, ret); else myswap("D", hole, ret);
        rep(_, 2) myswap("R", hole, ret);
        if(dir == "U") myswap("D", hole, ret); else myswap("U", hole, ret);
        myswap("L", hole, ret);
        
        pos = make_pair(pos.first, pos.second + 1);
        s += ret;
    }

    void move_left(P& pos, P& hole, string& s, string dir){
        string ret;
        if(dir != "U" && dir != "D") print("ERROR in move_left");

        if(dir == "U") myswap("U", hole, ret); else myswap("D", hole, ret);
        rep(_, 2) myswap("L", hole, ret);
        if(dir == "U") myswap("D", hole, ret); else myswap("U", hole, ret);
        myswap("R", hole, ret);

        pos = make_pair(pos.first, pos.second - 1);
        s += ret;
    }

    void move_up(P& pos, P& hole, string& s){
        string ret;

        myswap("R", hole, ret);
        rep(_, 2) myswap("U", hole, ret);
        myswap("L", hole, ret);
        myswap("D", hole, ret);
        
        pos = make_pair(pos.first - 1, pos.second); 
        s += ret;
    }


    // ooot
    // ...p
    // この位置関係でrightは事故る
    // pointをtrueにすると大回りして回避する
    void around(string dir, P& hole, bool point, string& s){
        string ret;
        if(hole.first == n - 1 && point == true){ 
            // print("ERROR in around point");
            // print_mat(pos_field); 
        }

        if(point == false){
            myswap("U", hole, ret);
            
            if(dir == "left") myswap("L", hole, ret);
            else if(dir == "right") myswap("R", hole, ret);
            // else print("ERROR in around"); 
        }
        else{
            myswap("D", hole, ret);
            rep(_, 2){
                if(dir == "left") myswap("L", hole, ret);
                else if(dir == "right") myswap("R", hole, ret);
            }
            rep(_, 2) myswap("U", hole, ret);

            /* 逆になっていることに注意 */
            if(dir == "left") myswap("R", hole, ret);
            else if(dir == "right") myswap("L", hole, ret);
        }
        
        s += ret;
    }

    string make_usual_move(P pos, P tar, P& hole, bool start_flag, Mat& fix){
        string ret;
        P temp;
        
        if(hole.first > pos.first && start_flag == false){   // holeがposより上に来てしまっている場合、結構レア、ただしスタート時点ではあり得るのでフラグを使って管理
            // if(hole.first - pos.first != 1 || hole.second > pos.second) print("ERROR in make_usual_move in if(hole.first > pos.first)");   // このケースはあり得ないはず
            /* 隣まで移動 */
            int _t = pos.second - hole.second - 1;
            rep(_, _t) myswap("R", hole, ret);
            myswap("U", hole, ret);
            
            /* 揃える */
            // 下を通って移動させることに注意
            // if(pos.first == n - 1) print("ERROR in make_usual_move in if(hole.first > pos.first) pos.first == n - 1");
            myswap(pos, hole, ret);
            _t = pos.second - tar.second; 
            rep(_, _t) move_left(pos, hole, ret, "D"); 
        }
        else{   
            if(pos.second == hole.second){
                if(hole.second == n - 1){ 
                    // print("ERROR in make_usual_move and exit"); 
                    // exit(0); 
                    if(fix[hole.first][hole.second - 1] == 0) myswap("L", hole, ret);   // 左に移動できるならok
                    else{
                        if(hole.first + 1 == pos.first){
                        // 結構面倒なタイプ
                        // とりあえずスルー
                        return "-1";
                    }
                        else{
                            myswap("D", hole, ret);
                            myswap("L", hole, ret);
                        }
                    }
                }
                else{
                    if(hole.second + 1 == pos.second) myswap(pos, hole, ret);
                    else myswap("R", hole, ret);
                }
            }
            if(pos.second > tar.second){   // 左に移動
                temp = make_pair(pos.first, pos.second - 1);
                ret += make_hole_action_tate(pos, temp, hole, fix);
                myswap(pos, hole, ret);
                int _t = pos.second - tar.second;
                string move_dir;
                if(pos.first == n - 1) move_dir = "U";
                else move_dir = "D";
                rep(i, _t) move_left(pos, hole, ret, move_dir);
                
                temp = make_pair(pos.first, tar.second);
            }
            else if(pos.second < tar.second){   // 右に移動
                temp = make_pair(pos.first, pos.second + 1);
                ret += make_hole_action_tate(pos, temp, hole, fix);
                myswap(pos, hole, ret);
                int _t = tar.second - pos.second;
                string move_dir;
                if(pos.first == n - 1) move_dir = "U";
                else move_dir = "D";
                rep(i, _t) move_right(pos, hole, ret, move_dir);
                
                temp = make_pair(pos.first, tar.second);
            }
            else{   // 同じ場合
                // 目標の真横にまで移動する
                if(pos.second != hole.second){
                    if(pos.second > hole.second){
                        temp = make_pair(pos.first, pos.second - 1);
                        ret += make_hole_action_tate(pos, temp, hole, fix);
                    }
                    else{
                        temp = make_pair(pos.first, pos.second + 1);
                        ret += make_hole_action_tate(pos, temp, hole, fix);
                    }
                }
                else{   // 横がかぶってしまっている時は回り込む、この時は一番右にいることはないはずなので、目標の右を狙う
                    myswap("R", hole, ret);
                    int _t = abs(pos.first - hole.first);
                    if(pos.first > hole.first){
                        rep(_, _t) myswap("D", hole, ret);
                    }
                    else{
                        rep(_, _t) myswap("U", hole, ret);
                    }
                }
            }
            
            if(tar.first == pos.first && tar.second == pos.second){   // たまたま揃ってしまった時、j=n-1の時に起こり得る
                // バグが怖いのでholeの場所を変える
                if(hole.second == n - 1){
                    // よく分からないから消した。あった方が良いのかも
                    //myswap("D", hole, ret);
                    //rep(_, 2) myswap("L", hole, ret);
                    //myswap("U", hole, ret);
                    
                    // 更新
                    myswap("D", hole, ret);
                    myswap("L", hole, ret);
                }
            }
            else if(pos.second != hole.second){
                if(pos.second < hole.second) around("left", hole, false, ret);
                else if(pos.second > hole.second){
                    // 最後二つ縦に並べる時に関しても大回りしてしまっているので、それを改善したい
                    bool big_around_flag = ((fix[hole.first - 1][hole.second] == 1) || (fix[hole.first - 1][hole.second + 1] == 1));   // 穴の上が固定されている場合は大回りする
                    if(big_around_flag){ 
                        // print("大回り");
                        // print_mat(fix);
                    }
                    if(big_around_flag) around("right", hole, true, ret);   // 大回りする、leftの時はしなくても良い。ここは未デバッグなのでバグってるかも
                    else around("right", hole, false, ret);
                }
                
                myswap(pos, hole, ret);
                int _t = pos.first - tar.first;
                rep(_, _t) move_up(pos, hole, ret);
            }
            //else print("ERROR in make_usual_move"); 
        }
        
        //if(pos.first != tar.first || pos.second != tar.second) print("============= not same =============");
        if(pos.first != tar.first || pos.second != tar.second) return "-1";   // なんか事故ってる時
        
        return ret; 
    }

    string make_last_move(P& hole, int tate){
        string ret = "";
        
        /* process1 端っこまでいく */
        if(hole.second == n - 1){ 
            int _t = hole.first - tate;
            rep(_, _t) myswap("U", hole, ret);
        }
        else if(hole.second == n - 2){
            myswap("R", hole, ret);
            int _t = hole.first - tate;
            rep(_, _t) myswap("U", hole, ret);
        }
        else{
            // 崩さないように下まで移動する、こんなケースあんの？
            int _t = tate + 2 - hole.first;   
            rep(_, _t) myswap("D", hole, ret);
            _t = n - 1 - hole.second;
            rep(_, _t) myswap("R", hole, ret);
            _t = hole.first - tate;
            rep(_, _t) myswap("U", hole, ret);
        }
        
        /* process2 揃える */
        myswap("L", hole, ret);
        myswap("D", hole, ret);
        
        return ret;
    }

    P decide_target(int num, P place, Mat& fix){
        queue<P> que;
        rep(i, n){
            rep(j, n){
                if(fix[i][j] == 1) continue;
                if(pos_field[i][j] == num) que.push(make_pair(i, j));
            }
        }
        
        if(que.size() == 0){
            // print("ERROR in decide_target"); 
            // dprint("target_number :", num); 
            // print_mat(fix);
        }
        
        int best_dist = 100000;   // 適当
        P ret;
        while(que.empty() == false){
            P p = que.front();
            que.pop();
            int dist = abs(p.first - place.first) + abs(p.second - place.second);
            if(best_dist >= dist){   // 同じだったら後の方が嬉しい
                ret = p;
                best_dist = dist;
            }
        }
        
        return ret;
    }

    int make_target_num(int i, int j){
        int ret;
        if(i < n - 2){
            if(j == n - 2) ret = target_field[i][n - 1];
            else if(j == n - 1) ret = target_field[i][n - 2];
            else ret = target_field[i][j];
        }
        else ret = target_field[i][j];
        
        return ret;
    }

    P make_tar(int i, int j){
        P ret;
        if(i < n - 2){
            if(j == n - 2) ret = make_pair(i, n - 2);
            else if(j == n - 1) ret = make_pair(i + 1, n - 2);
            else ret = make_pair(i, j);
        }
        else{
            if(i == n - 1) ret = make_pair(n - 2, j);
            else if(i == n - 2) ret = make_pair(n - 2, j + 1);
            // else print("ha?");
        }
        
        return ret;
    }

    string make_last_2_move(P& pos, P& tar, P& hole, Mat& fix){
        string ret;
        if(pos.first == tar.first){   // 横のみ考えれば良い
            if(hole.second > pos.second){   // 穴が右にある
                if(hole.first == n - 1) myswap("U", hole, ret); 
                int _t = hole.second - pos.second - 1;
                rep(_, _t) myswap("L", hole, ret);   // targetの右に移動する
                _t = pos.second - tar.second;
                rep(_, _t) move_left(pos, hole, ret, "D");
            }
            else if(hole.second == pos.second){   // 穴がtargetの下
                // if(hole.first == pos.first) print("wowow");   // あり得ない
                // targetの左に移動する
                myswap("L", hole, ret);
                myswap("U", hole, ret);
                myswap(pos, hole, ret);
                int _t = pos.second - tar.second;
                rep(_, _t) move_left(pos, hole, ret, "D");
            }
            else{   // 穴が左
                if(hole.first == n - 1){
                    if(fix[n - 2][hole.second] == 1){
                        myswap("R", hole, ret);
                        myswap("U", hole, ret);
                    }
                    else myswap("U", hole, ret);
                    
                    if(hole.first == pos.first && hole.second == pos.second){
                        // この状態は解決できない可能性がある
                        // ("game over 1");
                    }
                }
                
                int _t = pos.second - hole.second - 1;
                rep(_, _t) myswap("R", hole, ret);   // targetの左に移動する
                myswap(pos, hole, ret);
                _t = pos.second - tar.second;
                rep(_, _t) move_left(pos, hole, ret, "D");
            }
        }
        else{
            /* 解決困難な配置 */
            if(pos.second + 1 == tar.second){
                if(hole.first == n - 2) myswap("D", hole, ret);
                int _t = hole.second - pos.second;
                rep(_, _t) myswap("L", hole, ret);   // 最後の一回はpos
                myswap("U", hole, ret);
                rep(_, 2) myswap("R", hole, ret);
                myswap("D", hole, ret);
                myswap("L", hole, ret);   // これはpos
                myswap("L", hole, ret);   // これはfix
                myswap("U", hole, ret);
                myswap("R", hole, ret); 
                myswap("D", hole, ret);   // これはfix
                myswap("L", hole, ret);
                myswap("U", hole, ret);
                myswap("R", hole, ret);   // これはfix
                myswap("R", hole, ret);   
                myswap("D", hole, ret);   // これはpos
                myswap("L", hole, ret);
                myswap("U", hole, ret);
                myswap("R", hole, ret);   // これはpos
                
                pos = make_pair(tar.first, tar.second);
                // print("注意1？");   
                        
                return ret;
            }
            
            /* まずtargetをn-2に上げる */
            if(hole.first == n - 1){
                // 穴の上が使えない場合、右にずれる
                if(fix[n - 2][hole.second] == 1){
                    // 右隣がtargetである場合は無理やり解決する
                    if(hole.second + 1 != pos.second){ 
                        myswap("R", hole, ret);
                        myswap("U", hole, ret);
                    }
                    else{
                        myswap("U", hole, ret);
                        rep(_, 2) myswap("R", hole, ret);
                        myswap("D", hole, ret);
                        myswap("L", hole, ret);   // これはpos
                        myswap("L", hole, ret);   // これはfix
                        myswap("U", hole, ret);
                        myswap("R", hole, ret); 
                        myswap("D", hole, ret);   // これはfix
                        myswap("L", hole, ret);
                        myswap("U", hole, ret);
                        myswap("R", hole, ret);   // これはfix
                        myswap("R", hole, ret);   
                        myswap("D", hole, ret);   // これはpos
                        myswap("L", hole, ret);
                        myswap("U", hole, ret);
                        myswap("R", hole, ret);   // これはpos
                        
                        pos = make_pair(tar.first, tar.second);
                        // print("注意2？");   
                        
                        return ret;
                    }
                }
                else myswap("U", hole, ret);
            }
            
            if(hole.second > pos.second){
                int _t = hole.second - pos.second;
                rep(_, _t) myswap("L", hole, ret);
            }
            else if(hole.second < pos.second){
                int _t = pos.second - hole.second;
                rep(_, _t) myswap("R", hole, ret);
            }
            else{
                // よく分からない
            }
            
            myswap(pos, hole, ret);   // これで縦を調整できた
            
            // このタイミングで、たまたまゴールしている時がある
            if(pos.first == tar.first && pos.second == tar.second){ 
                // print("accident goal");
                return ret;
            }
            
            // 左に回り込む
            myswap("L", hole, ret);
            myswap("U", hole, ret);
            
            myswap(pos, hole, ret);
            int _t = pos.second - tar.second;
            rep(_, _t) move_left(pos, hole, ret, "D");
        }
        
        return ret;
    }

    string make_last_arrange_move(P& hole, int yoko){
        // print_mat(pos_field);
        string ret = "";
        if(hole.first == n - 2) myswap("D", hole, ret);
        int _t = hole.second - yoko;
        rep(_, _t) myswap("L", hole, ret);
        myswap("U", hole, ret);
        myswap("R", hole, ret);
        
        return ret;
    }

    string make_totally_last_move(){
        string ret = "-1"; 
        if(pos_field[n - 2][n - 2] == target_field[n - 2][n - 2] && pos_field[n - 2][n - 1] == target_field[n - 2][n - 1] && pos_field[n - 1][n - 2] == target_field[n - 1][n - 2]){
            return "";
        }
        P hole = search_hole();
        
        Mat field = copy_mat(pos_field);
        
        // 反時計回り
        if(true){
            string memo = "";
            P _hole = make_pair(hole.first, hole.second);
            if(_hole.first == n - 2 && _hole.second == n - 1) myswap("L", _hole, memo);
            if(_hole.first == n - 2 && _hole.second == n - 2) myswap("D", _hole, memo);
            if(_hole.first == n - 1 && _hole.second == n - 2) myswap("R", _hole, memo);
            rep(_, 5){
                if(pos_field[n - 2][n - 2] == target_field[n - 2][n - 2] && pos_field[n - 2][n - 1] == target_field[n - 2][n - 1] && pos_field[n - 1][n - 2] == target_field[n - 1][n - 2]){
                    if(ret == "-1") ret = memo;
                    else if(len(ret) > len(memo)) ret = memo;
                }
                myswap("U", _hole, memo);
                myswap("L", _hole, memo);
                myswap("D", _hole, memo);
                myswap("R", _hole, memo);
            }
            pos_field = copy_mat(field);
        }
        if(true){
            string memo = "";
            P _hole = make_pair(hole.first, hole.second);
            if(_hole.first == n - 1 && _hole.second == n - 2) myswap("U", _hole, memo);
            if(_hole.first == n - 2 && _hole.second == n - 2) myswap("R", _hole, memo);
            if(_hole.first == n - 2 && _hole.second == n - 1) myswap("D", _hole, memo);
            rep(_, 5){
                if(pos_field[n - 2][n - 2] == target_field[n - 2][n - 2] && pos_field[n - 2][n - 1] == target_field[n - 2][n - 1] && pos_field[n - 1][n - 2] == target_field[n - 1][n - 2]){
                    if(ret == "-1") ret = memo;
                    else if(len(ret) > len(memo)) ret = memo;
                }
                myswap("L", _hole, memo);
                myswap("U", _hole, memo);
                myswap("R", _hole, memo);
                myswap("D", _hole, memo);
            }
            pos_field = copy_mat(field);
            
        }
        
        return ret;
    }
}; 


vector<vector<vector<bool>>> make_resp(){
    vector<vector<vector<bool>>> v;
    rep(i, 16){
        vector<vector<bool>> h;
        v.push_back(h);
        rep(j, 16){
            vector<bool> m = {false, false, false, false};
            v[i].push_back(m);
        }
    }
    rep(i, 16){
        rep(j, 16){
            rep(k, 4){
                int l = (k + 2) % 4;
                if((i & (1 << k)) != 0 && (j & (1 << l)) != 0){ 
                    if(count_flag(i) != 1 || count_flag(j) != 1) v[i][j][k] = true;
                    else v[i][j][k] = false;
                }
                else if((i & (1 << k)) == 0 && (j & (1 << l)) == 0) v[i][j][k] = true;
                else v[i][j][k] = false;
            }
        }
    }
    
    return v;
}
vector<vector<vector<bool>>> make_wall_resp(){
    vector<vector<vector<bool>>> v;
    rep(i, n){
        vector<vector<bool>> h;
        v.push_back(h);
        rep(j, n){
            vector<bool> m;
            rep(_, 16) m.push_back(false);
            v[i].push_back(m);
        }
    }

    rep(i, n){
        rep(j, n){
            rep(k, 16){
                bool p = true;
                if(i == 0 && (k & (1 << 1)) != 0) p = false;
                if(i == n - 1 && (k & (1 << 3)) != 0) p = false;
                if(j == 0 && (k & (1 << 0)) != 0) p = false;
                if(j == n - 1 && (k & (1 << 2)) != 0) p = false;
                v[i][j][k] = p;
            }
        }
    }
    
    return v;
}
vector<vector<vector<bool>>> make_link(){
    vector<vector<vector<bool>>> v;
    rep(i, 16){
        vector<vector<bool>> h;
        v.push_back(h);
        rep(j, 16){
            vector<bool> m = {false, false, false, false};
            v[i].push_back(m);
        }
    }
    rep(i, 16){
        rep(j, 16){
            rep(k, 4){
                int l = (k + 2) % 4;
                if((i & (1 << k)) != 0 && (j & (1 << l)) != 0) v[i][j][k] = true;
                else v[i][j][k] = false;
            }
        }
    }
    
    return v;
}
bool inside(int y, int x){
    if(y < 0 || y >= n) return false;
    if(x < 0 || x >= n) return false;
    return true;
}
char ret_dir(int y, int x, int dy, int dx){
    if(dx == x && dy - y == 1) return 'D';
    else if(dx == x && dy - y == -1) return 'U';
    else if(dx - x == 1 && dy == y) return 'R';
    else if(dx - x == -1 && dy == y) return 'L';
    else return 'n';
}

bool forward(int y, int x, int k){
    /* 円にならないかもチェックする */
    bool ret = true;
    int link_num = 0;
    rep(i, 4){
        int dy = y + VEC[i][0];
        int dx = x + VEC[i][1];
        if(inside(dy, dx) == false) continue;
        int t = pos_field[dy][dx];
        if(t >= 0 && link[k][t][i] == true){ 
            int a = ret_num(y, x);
            int b = ret_num(dy, dx);
            if(ds.same(a, b) == true) ret = false;
            ds.link(a, b); 
            link_num++;
        }
    }
    
    int d_arm_num = count_flag(k) - 2 * link_num;   // 残りの腕の数の変化
    arm_vec[ret_num(y, x)] = d_arm_num; 
    ds.update(ret_num(y, x), d_arm_num); 
    int remain_arm_num = ds.get_sum(ret_num(y, x)); 
    if(remain_arm_num == 0 && k != 0 && ret_num(y, x) != 0) ret = false;
    else if(remain_arm_num < 0) print("ERROR in forward"); 
    
    //cout << remain_arm_num << " ";
    //yes(ret);
    //print_mat(pos_field);

    return ret;
}

void backward(int y, int x, int k){
    rep(i, 4){
        int dy = y + VEC[i][0];
        int dx = x + VEC[i][1];
        if(inside(dy, dx) == false) continue;
        int t = pos_field[dy][dx];
        if(t >= 0 && link[k][t][i] == true){ 
            int a = ret_num(y, x);
            int b = ret_num(dy, dx);
            ds.cut(a, b); 
        }
    }

    ds.update(ret_num(y, x), -1 * arm_vec[ret_num(y, x)]); 
    arm_vec[ret_num(y, x)] = 0; 
}

bool check_valid(int y, int x, int k){
    /* (y, x)にkをおく */
    /* まずおけるかどうか */
    rep(i, 4){
        int dy = y + VEC[i][0];
        int dx = x + VEC[i][1];
        if(inside(dy, dx) == false) continue;
        int t = pos_field[dy][dx];
        if(t >= 0 && resp[k][t][i] == false) return false;
    }

    return true;
}


void dfs(int y, int x, int order_num){
    if(y == -1 && x == n - 1){ 
        target = pos_field;
        // print_mat(target);
        all_target.push_back(target); 
        return;
    }
    else if(clock() - start > time_vec[order_num]) return;
    
    int next_y = y;
    int next_x = x;
    if(next_x == 0){next_y--; next_x = n - 1;}
    else next_x--;
    
    vector<int> order = orders[order_num]; 
    for(int k : order){
        if(tile[k] == 0) continue;
        if(wall_resp[y][x][k] == false) continue;
        
        if(check_valid(y, x, k)){
            /* forward */
            pos_field[y][x] = k;
            tile[k]--;
            bool success = forward(y, x, k);

            if(success) dfs(next_y, next_x, order_num);
            
            /* backward */
            tile[k]++;
            pos_field[y][x] = -1;
            backward(y, x, k);
        }
    }
}


void init(){
    start = clock();
    cin >> n >> t;
    field = init_mat(n, n);
    target = init_mat(n, n, -1);
    pos_field = init_mat(n, n, -1);
    rep(i, 16) tile[i] = 0;
    rep(i, n){
        rep(j, n){
            char c;
            cin >> c;
            field[i][j] = decode(c);
            if(c == '0'){sy = i; sx = j;}
            tile[field[i][j]]++;
        }
    }

    arm_vec = vector<int>(n * n, 0); 
    resp = make_resp();
    wall_resp = make_wall_resp();
    link = make_link();
    ds = dynamic_connectivity<int>(n * n);
}

int main(){
    init();
    rep(i, len(time_vec)) dfs(n - 1, n - 1, i);
    Mat best_target_field = init_mat(n, n, 0);
    
    string ans = "-1";
    for(auto target : all_target){
        if(clock() - start > TOTAL_END_TIME) break;
        MakeRoute makeRoute(field, target);
        // print_mat(target);
        string memo = makeRoute.make();
        // print(memo);
        if(ans == "-1"){ 
            ans = memo;
            best_target_field = target;
        }
        else if(memo != "-1" && len(ans) > len(memo)){ 
            ans = memo;
            best_target_field = target;
        }
    }

    if(ans != "-1"){
        string update = "";
        MakeRoute makeRoute(field, best_target_field);
        while(clock() - start < TOTAL_END_TIME)
        rep(_, 200){
            if(clock() - start >= TOTAL_END_TIME) break;
            pair<string, string> p = makeRoute.update_little(update);
            if(p.second == "-1") continue;
            else{
                string cand = p.first + p.second;
                if(len(ans) > len(cand)){
                    ans = cand;
                    update = p.first;
                }
            }
        }
    }

    for(auto target : all_target){
        if(clock() - start >= TOTAL_END_TIME) break;
        string update = "";
        MakeRoute makeRoute(field, best_target_field);
        while(clock() - start < TOTAL_END_TIME)
        rep(_, 30){
            if(clock() - start >= TOTAL_END_TIME) break;
            pair<string, string> p = makeRoute.update_little(update);
            if(p.second == "-1") continue;
            else{
                string cand = p.first + p.second;
                if(len(ans) > len(cand)){
                    ans = cand;
                    update = p.first;
                }
            }
        }
    }

    if(ans != "-1"){
        print(ans);
        int score = 500000 * (2.0 - (float(len(ans)) / float(t)));
        // print(score);
    }
    else{
        print("");
    }
}


