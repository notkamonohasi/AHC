#include <bits/stdc++.h>
// #define MOD 1000000007
#define MOD 998244353
#define ll long long
#define ld long double
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define frep(i, k, n) for (ll i = (ll)k; i < (ll)(n); i++)
#define brep(i, n) for (ll i = (ll)(n - 1); i >= 0; i--)
#define irep(it, mp) for (auto it = mp.begin(); it != mp.end(); it++)
#define len(x) (ll)x.size()
#define pprint(x) cout << fixed << setprecision(10) << x << endl
#define bs(st, key) (st.find(key) != st.end() ? true : false)
// #define lb(v, k) lower_bound(v.begin(), v.end(), k)   // setでこれを使うと死ぬので消しておく
// #define ub(v, k) upper_bound(v.begin(), v.end(), k)
#define all(v) v.begin(), v.end()
#define bit(x,i)(((x)>>(i))&1)
using namespace std;

//const ll vec[][2] = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
const ll neighborVec[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
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
void print(){cout << endl;}
template <class Head, class... Tail> void print(Head&& head, Tail&&... tail){cout << head << " "; print(std::forward<Tail>(tail)...);}
template<typename T> void vprint(vector<T>& v){for(auto& x : v) cout << x << " "; cout << endl;}
using P = pair<ll, ll>;
bool sameP(P& p1, P& p2){if(p1.first == p2.first && p1.second == p2.second) return true; else return false;}
void print_pair(P& p){cout << p.first << " " << p.second << endl;}
using T = tuple<ll, ll, ll>; // ll x, y, z; tie(x, y, z) = T
template<typename T> using PQ = priority_queue<T>;
template<typename T> using IQ = priority_queue<T, vector<T>, greater<T>>;
using Mat = vector<vector<ll>>;
Mat init_mat(ll a, ll b){Mat ret(a, vector<ll>(b, 0)); return ret;}
Mat init_mat(ll a, ll b, ll c){Mat ret(a, vector<ll>(b, c)); return ret;}
template<typename T>
void print_mat(vector<vector<T>>& mat){rep(i, mat.size()){rep(j, mat[i].size()){cout << mat[i][j] << " ";}cout << endl;}}
using PMat = vector<vector<P>>;
PMat init_pmat(ll a, ll b){PMat ret(a, vector<P>(b, P(0, 0))); return ret;}
PMat init_pmat(ll a, ll b, P c){PMat ret(a, vector<P>(b, c)); return ret;}
using BMat = vector<vector<bool>>;
BMat init_bmat(ll a, ll b){BMat ret(a, vector<bool>(b, false)); return ret;}
BMat init_bmat(ll a, ll b, bool c){BMat ret(a, vector<bool>(b, c)); return ret;}
using DMat = vector<vector<double>>;
DMat init_dmat(ll a, ll b){DMat ret(a, vector<double>(b, 0.0)); return ret;}
DMat init_dmat(ll a, ll b, double c){DMat ret(a, vector<double>(b, c)); return ret;}
using Tensor = vector<vector<vector<ll>>>;
Tensor init_tensor(ll a, ll b, ll c){Tensor ret(a, Mat(b, vector<ll>(c, 0))); return ret;}
Tensor init_tensor(ll a, ll b, ll c, ll d){Tensor ret(a, Mat(b, vector<ll>(c, d))); return ret;}

using Graph = vector<vector<ll> >;
Graph init_graph(ll V){Graph ret; vector<ll> empty; rep(i, V) ret.push_back(empty); return ret;}

struct Edge{
    ll number, from, to; 
    double cost;
    bool broken; 
    Edge(){ broken = false; }
    Edge(ll a) : to(a){ broken = false; }
    Edge(ll a, double b) : to(a), cost(b){ broken = false; }
    Edge(ll a, ll b, double c) : from(a), to(b), cost(c){ broken = false; }
    Edge(ll a, ll b, ll c, double d) : number(a), from(b), to(c), cost(d){ broken = false; }
    bool operator > (const Edge& another) const{return cost > another.cost;}
    bool operator < (const Edge& another) const{return cost < another.cost;}
}; 
using EdgeGraph = vector<vector<Edge> >;
EdgeGraph init_edgeGraph(ll V){EdgeGraph ret; vector<Edge> empty; rep(i, V) ret.push_back(empty); return ret;}

const bool LOCAL = false;
const bool VISUALIZE = false;

ll N, WATER_SIZE, HOUSE_SIZE, C;

const ll MAX_HARDNESS = 5000; 
const ll MIN_HARDNESS = 10; 
const double FIRST_WEIGHT = 1e-20;
const double FIRST_ESTIMATE = 2505; 
const ll ESTIMATE_RANGE = 15; 
unordered_map<ll, ll> FIRST_POWER = {
    {1, 12}, {2, 16}, {4, 18}, {8, 24}, {16, 32}, {32, 40}, {64, 50}, {128, 52} 
}; 
unordered_map<ll, ll> SECOND_POWER = {
    {1, 12}, {2, 20}, {4, 22}, {8, 48}, {16, 56}, {32, 64}, {64, 128}, {128, 164} 
}; 
unordered_map<ll, ll> THIRD_POWER = {
    {1, 12}, {2, 20}, {4, 26}, {8, 48}, {16, 70}, {32, 96}, {64, 180}, {128, 254} 
}; 
unordered_map<ll, ll> SEARCH_POWER = {
    {1, 12}, {2, 20}, {4, 26}, {8, 48}, {16, 70}, {32, 96}, {64, 180}, {128, 254} 
}; 
unordered_map<ll, double> UNBROKEN_WEIGHT = {
    {0, 0.0}, {1, 1.0}, {2, 0.9}, {3, 0.8}, {4, 0.65}, {5, 0.5}, {6, 0.40}, {7, 0.35}, {8, 0.30}, {9, 0.25}, {10, 0.20}, {11, 0.15}, {12, 0.10}, {13, 0.05}, {14, 0.02}, {15, 0.01}
}; 
unordered_map<ll, double> BROKEN_WEIGHT = {
    {0, 1.0}, {1, 1.0}, {2, 0.9}, {3, 0.8}, {4, 0.65}, {5, 0.5}, {6, 0.40}, {7, 0.35}, {8, 0.30}, {9, 0.25}, {10, 0.20}, {11, 0.15}, {12, 0.10}, {13, 0.05}, {14, 0.02}, {15, 0.01}
}; 
unordered_map<ll, ll> UNKNOWN_POWER = {
    {1, 180}, {2, 160}, {4, 200}, {8, 200}, {16, 240}, {32, 220}, {64, 200}, {128, 350}
}; 

inline bool isInside(ll y, ll x){
    if(0 <= y && y < N && 0 <= x && x < N) return true;
    else return false;
}
inline bool isInside(P& p){ return isInside(p.first, p.second); }
inline ll f(ll y, ll x){ return y * N + x; }
inline ll f(P p){ return f(p.first, p.second); }
inline P inverse(ll number){ return P(int(number / N), number % N); }

struct House{
    ll number, y, x; 
    House(ll number_, ll y_, ll x_) : number(number_), y(y_), x(x_){}
    ll getHouseNumber(){ return number; }
    ll getPlaceNumber(){ return f(y, x); }
    P getPlace(){ return P(y, x); }
}; 
struct Water{
    ll number, y, x; 
    Water(ll number_, ll y_, ll x_) : number(number_), y(y_), x(x_){}
    ll getWaterNumber(){ return number; }
    ll getPlaceNumber(){ return f(y, x); }
    P getPlace(){ return P(y, x); }
};  
struct Info{ 
    ll number;
    double estimate; 
    double weight;

    Info(){}
    Info(ll number_, double estimate_, double weight_) : number(number_), estimate(estimate_), weight(weight_){}
    ll getNumber() const { return number; }
    ll getEstimate() const { return estimate; }
    double getWeight() const { return weight; }
    void updateEstimate(ll nextEstimate){ estimate = nextEstimate; }
}; 
inline bool operator < (const Info& i1, const Info& i2) {return i1.number < i2.number;}
inline bool operator > (const Info& i1, const Info& i2) {return i1.number > i2.number;}

struct AstarState{
    ll houseNumber; 
    ll y, x;
    ll gridNumber; 
    ll totalCost; 
    AstarState(){}
    AstarState(ll a, ll b, ll c, ll d, ll e) : houseNumber(a), y(b), x(c), gridNumber(d), totalCost(e){}

    ll getHouseNumber() const{ return houseNumber; }
    ll getGridNumber() const{ return gridNumber; }
    ll getTotalCost() const{ return totalCost; }
    P getPlace() const{ return P(y, x); }      
}; 
inline bool operator < (const AstarState& s1, const AstarState& s2){ return s1.totalCost < s2.totalCost; }
inline bool operator > (const AstarState& s1, const AstarState& s2){ return s1.totalCost > s2.totalCost; }

struct Block{
    // 確定情報
    ll y, x; 
    ll drill; 
    ll minHardness; 
    ll maxHardness;  
    ll searchCount; 
    bool broken; 
    bool searched;   // 一度でも探索したらtrue

    // 推定に使う
    double weightSum; 
    double estimateSum; 
    double estimate; 
    set<Info> infoSt; 

    Block(){}
    Block(ll y_, ll x_) : y(y_), x(x_){
        drill = 0; 
        minHardness = MIN_HARDNESS; 
        maxHardness = MAX_HARDNESS; 
        weightSum = FIRST_WEIGHT; 
        estimate = FIRST_ESTIMATE; 
        estimateSum = estimate * weightSum; 
        searchCount = 0; 
        broken = false;
        searched = false;
    }
    void updateBlock(ll power, ll brokenFeedback){
        if(broken){
            print("already broken error in Block::updateBlock"); 
            exit(EXIT_FAILURE); 
        }
        searchCount++; 
        drill += power; 
        searched = true;
        if(brokenFeedback == 0) minHardness += power; 
        else{
            broken = true;
            maxHardness = minHardness + power; 
            minHardness++;   // 厳密には違うが、厳しく考える必要はない
        }
    }
    void updateEstimate(Info& info){
        auto it = infoSt.find(info); 
        if(it != infoSt.end()){
            weightSum += info.getWeight() - it->getWeight(); 
            estimateSum += info.getWeight() * info.getEstimate() - it->getWeight() * it->getEstimate(); 
            estimate = estimateSum / weightSum; 
            infoSt.erase(it); 
            infoSt.insert(info); 
        }
        else{
            weightSum += info.getWeight(); 
            estimateSum += info.getWeight() * info.getEstimate(); 
            estimate = estimateSum / weightSum;
            infoSt.insert(info); 
        }
    }
    inline ll getDrill() const{ return drill; }
    inline ll getHardness() const{ return broken ? (minHardness + maxHardness) / 2 : minHardness + UNKNOWN_POWER[C]; }
    inline ll getSearchCount() const{ return searchCount; }
    inline double getMinHardness() const{ return minHardness; }
    inline double getMaxHardness() const{ return maxHardness; }
    inline double getEstimate() const{ return broken ? ((minHardness + maxHardness) / 2) : estimate; }
    inline bool isBroken() const{ return broken; }
    inline bool isSearched() const { return searched; }
    inline double getEstimateRemain() const{ return estimate - (double)drill; }
};

vector<House> houseVec; 
vector<Water> waterVec; 
vector<ll> houseGridNumberVec; 
vector<ll> waterGridNumberVec; 

namespace dijkstra{
    void dijkstra(const EdgeGraph& G, ll s, ll t, vector<double>& dis, vector<ll>& prev) {
        ll N = G.size();
        dis.resize(N, INT_MAX);   // オーバーフローに注意
        prev.resize(N, -1); // 初期化
        priority_queue<P, vector<P>, greater<P>> pq; 
        dis[s] = 0.0;
        pq.emplace(dis[s], s);
        while(!pq.empty()){
            P p = pq.top();
            pq.pop();
            ll v = p.second;
            if(dis[v] < p.first) continue;   // これがないと余計にPQに追加されたnodeを何回も見ることになり、O(V^2)？O(E^2)になってしまう
            if(v == t) return;   // ゴールまで見れば十分   // これがあるとバグる...
            for(auto &e : G[v]){
                if(dis[e.to] > dis[v] + e.cost){
                    dis[e.to] = dis[v] + e.cost;
                    prev[e.to] = v; // 頂点 v を通って e.to にたどり着いた   
                    pq.emplace(dis[e.to], e.to);
                }
            }
        }
    }

    // targets全て見たら終わりにする
    // 見たいものと一つだけ、というのを分ければ高速化できる
    void dijkstra(const EdgeGraph& G, ll s, vector<ll>& targetVec, vector<ll>& dis, vector<ll>& prev) {
        ll N = G.size();
        dis.resize(N, INT_MAX);   // オーバーフローに注意
        prev.resize(N, -1); // 初期化
        set<ll> targetSt; 
        for(ll x : targetVec) targetSt.insert(x); 
        priority_queue<P, vector<P>, greater<P>> pq; 
        dis[s] = 0.0;
        pq.emplace(dis[s], s);
        while(!pq.empty()){
            P p = pq.top();
            pq.pop();
            ll v = p.second;
            if(dis[v] < p.first) continue;   // これがないと余計にPQに追加されたnodeを何回も見ることになり、O(V^2)？O(E^2)になってしまう
            if(bs(targetSt, v) == true) targetSt.erase(v);
            targetSt.insert(v);    
            for(auto &e : G[v]){
                if(dis[e.to] > dis[v] + e.cost){
                    dis[e.to] = dis[v] + e.cost;
                    prev[e.to] = v; // 頂点 v を通って e.to にたどり着いた   
                    pq.emplace(dis[e.to], e.to);
                }
            }
        }
    }

    // sからtへの最短path
    vector<ll> get_path(const vector<ll>& prev, ll t){
        vector<ll> path;
        for(ll cur = t; cur != -1; cur = prev[cur]){
            path.push_back(cur);
        }
        reverse(path.begin(), path.end()); // 逆順なのでひっくり返す
        return path;
    }
}; 

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

class Simulator{
public : 
    Mat remainRock; 
    ll totalCost; 
    Simulator(){ totalCost = 0; }
    void init(){
        if(LOCAL == false) return; 
        remainRock = init_mat(N, N); 
        rep(i, N){
            rep(j, N){
                cin >> remainRock[i][j]; 
            } 
        }
    }

    ll increment(ll y, ll x, ll power){
        totalCost += power + C; 
        if(remainRock[y][x] < 0){
            print("This rock is broken", y, x); 
            exit(EXIT_FAILURE); 
        }
        else{
            remainRock[y][x] -= power; 
            if(remainRock[y][x] <= 0) return 1; 
            else return 0; 
        }
    }

    void printTotalCost(){ print("# totalCost", totalCost); }
};
Simulator simulator; 

class State{
public : 
    vector<vector<Block>> blockMat; 
    EdgeGraph gridGraph; 
    unordered_map<ll, ll> gridNumberAdministrator; 
    unordered_map<ll, P> gridPlaceAdministrator; 
    unordered_map<ll, ll> houseGridAdministrator; 
    unordered_map<ll, ll> waterGridAdministrator;

    State(){ init(); }

    void init(){
        blockMat = vector<vector<Block>>(N, vector<Block>(N)); 
        rep(i, N){ 
            rep(j, N){
                blockMat[i][j] = Block(i, j); 
            }
        }
        initGridGraph();
    }

    void initGridGraph(){ 
        makeGrid(); 
        makeGridEdge(); 
    }

    void makeGrid(){
        ll posNumber = 0; 
        set<ll> visitSt; 

        // 家と水源もgridに入れる
        for(House& house : houseVec){
            gridNumberAdministrator[f(house.getPlace())] = posNumber; 
            gridPlaceAdministrator[posNumber] = house.getPlace(); 
            houseGridNumberVec.push_back(posNumber); 
            houseGridAdministrator[house.getHouseNumber()] = posNumber; 
            posNumber++;
            visitSt.insert(f(house.getPlace())); 
        }
        for(Water& water : waterVec){
            gridNumberAdministrator[f(water.getPlace())] = posNumber; 
            gridPlaceAdministrator[posNumber] = water.getPlace(); 
            waterGridNumberVec.push_back(posNumber); 
            waterGridAdministrator[water.getWaterNumber()] = posNumber; 
            posNumber++;
            visitSt.insert(f(water.getPlace())); 
        }
        
        if(C == 128){
            ll y = 0; 
            while(y < 200){
                ll x = 0; 
                while(x < 200){
                    if(bs(visitSt, f(y, x)) == false){   // 家か水源と一致している可能性がある
                        gridNumberAdministrator[f(y, x)] = posNumber; 
                        gridPlaceAdministrator[posNumber] = P(y, x); 
                        posNumber++; 
                    }
                    if(x == 0 || x == 14) x += 14; 
                    else if(x == 184) x += 15; 
                    else x += 12; 
                }
                if(y == 0 || y == 14) y += 14; 
                else if(y == 184) y += 15; 
                else y += 12; 
            }
        }
        else if(C == 64){
            ll y = 0; 
            while(y < 200){
                ll x = 0; 
                while(x < 200){
                    if(bs(visitSt, f(y, x)) == false){   // 家か水源と一致している可能性がある
                        gridNumberAdministrator[f(y, x)] = posNumber; 
                        gridPlaceAdministrator[posNumber] = P(y, x); 
                        posNumber++; 
                    }
                    if(x == 0) x += 12; 
                    else x += 11; 
                }
                if(y == 0) y += 12; 
                else y += 11; 
            }
        }
        else{
            ll y = 0; 
            while(y < 200){
                ll x = 0; 
                while(x < 200){
                    if(bs(visitSt, f(y, x)) == false){   // 家か水源と一致している可能性がある
                        gridNumberAdministrator[f(y, x)] = posNumber; 
                        gridPlaceAdministrator[posNumber] = P(y, x); 
                        posNumber++; 
                    }
                    if(x == 190) x = 199; 
                    else x += 10; 
                }
                if(y == 190) y = 199; 
                else y += 10; 
            }
        }
    }

    // 隣接点を考える
    // 面倒なのでマンハッタン距離が16以下と定義する。グリッドの大きさを変えたら、こちらも変えないといけないので注意
    void makeGridEdge(){
        const ll THRESHOLD_GRID_DIST = 15;  
        ll gridSize = getGridSize(); 
        gridGraph = init_edgeGraph(gridSize); 
        ll posGridEdgeNumber = 0; 
        rep(i, gridSize){
            P p1 = getGridPlace(i); 
            frep(j, i + 1, gridSize){
                P p2 = getGridPlace(j); 
                if(calcManhattanDist(p1, p2) <= THRESHOLD_GRID_DIST){
                    ll cost = calcGridDist(i, j); 
                    gridGraph[i].push_back(Edge(posGridEdgeNumber, i, j, cost)); 
                    gridGraph[j].push_back(Edge(posGridEdgeNumber, j, i, cost)); 
                    posGridEdgeNumber++;
                    // print("# cost", i, j, cost); 
                }
            }
        }
    }

    // (家の)近くのグリッドを探す
    vector<ll> getNeighborGrid(P house){
        const ll THRESHOLD_GRID_DIST = 15;  
        ll gridSize = getGridSize(); 
        vector<ll> ret; 
        rep(i, gridSize){
            P p = getGridPlace(i); 
            if(calcManhattanDist(p, house) <= THRESHOLD_GRID_DIST) ret.push_back(i); 
        }
        return ret; 
    }

    vector<Edge> getNeighborGridEdge(ll gridNumber){
        return gridGraph[gridNumber]; 
    }

    vector<ll> getNeighborGridNumber(ll gridNumber){
        vector<ll> ret; 
        for(Edge& edge : gridGraph[gridNumber]){
            ret.push_back(edge.to); 
        }
        return ret; 
    }

    ll getGridShortestPathDist(ll posGridNumber, ll houseNumber){
        vector<ll> gridNumberVec;   // 全ての水源と出発点の家を入れる
        ll houseGridNumber = getHouseGridNumber(houseNumber); 
        gridNumberVec.push_back(houseGridNumber);
        for(Water& water : waterVec){
            ll waterGridNumber = getWaterGridNumber(water.getWaterNumber()); 
            gridNumberVec.push_back(waterGridNumber); 
        }
        vector<ll> dist, prev; 
        dijkstra::dijkstra(gridGraph, posGridNumber, gridNumberVec, dist, prev); 

        ll bestDist = INT_MAX; 
        frep(i, 1, gridNumberVec.size()){   // 最初は水源ではなく家なので無視
            ll thisDist = dist[houseGridNumber] + dist[gridNumberVec[i]];   // pos→house + pos→water = house + water
            if(bestDist > thisDist) bestDist = thisDist; 
        }
        return bestDist; 
    }

    void getShortestPath(const EdgeGraph& graph, ll waterNumber, ll houseNumber, vector<ll>& routeVec, double& cost){
        ll waterPlaceNumber = waterVec[waterNumber].getPlaceNumber(); 
        ll housePlaceNumber = houseVec[houseNumber].getPlaceNumber(); 
        vector<double> dist; 
        vector<ll> prev; 
        dijkstra::dijkstra(graph, waterPlaceNumber, housePlaceNumber, dist, prev); 
        routeVec = dijkstra::get_path(prev, housePlaceNumber); 

        // 水源の岩盤が壊れていない場合、これを壊す必要がある
        double waterRockCost; 
        P waterPlace = inverse(waterPlaceNumber); 
        if(isBroken(waterPlace) == false) waterRockCost = getEstimateRemain(waterPlace);
        else waterRockCost = 0; 
        cost = waterRockCost + dist[housePlaceNumber]; 
    }

    // 最適なプランを返す
    // 参照でhouseNumberを返す
    vector<ll> getPlan(ll& targetHouseNumber, ll& bestScore){
        // グラフを作る
        EdgeGraph graph = init_edgeGraph(f(N, N)); 
        rep(i, N){
            rep(j, N){
                rep(k, 4){
                    ll dy = i + neighborVec[k][0]; 
                    ll dx = j + neighborVec[k][1]; 
                    if(isInside(dy, dx) == false) continue;
                    double thisCost; 
                    // +Cというのは要調整
                    if(isBroken(dy, dx) == false) thisCost = max(getEstimateRemain(dy, dx), 10) + C;   // まだ隣の岩盤が壊れていないならコストが必要
                    else thisCost = 0;
                    graph[f(i, j)].push_back(Edge(-1, f(i, j), f(dy, dx), thisCost)); 
                }
            }
        }

        vector<ll> bestRouteVec; 
        double bestCost = INT_MAX; 
        rep(waterNumber, WATER_SIZE){
            vector<ll> routeVec; 
            double cost; 
            getShortestPath(graph, waterNumber, targetHouseNumber, routeVec, cost); 
            if(cost < bestCost){
                bestRouteVec = routeVec; 
                bestCost = cost; 
            }
        } 
        return bestRouteVec; 
    }

    // (y, x)をpowerで叩いたところ、brokenという結果が帰ってきた
    void update(ll y, ll x, ll power, ll broken){
        updateBlock(y, x, power, broken); 
        updateEstimate(y, x); 
    }

    void updateEstimate(ll y, ll x){
        ll min_y = max(0, y - ESTIMATE_RANGE); 
        ll max_y = min(N, y + ESTIMATE_RANGE + 1); 
        ll min_x = max(0, x - ESTIMATE_RANGE); 
        ll max_x = min(N, x + ESTIMATE_RANGE + 1); 
        frep(dy, min_y, max_y){
            frep(dx, min_x, max_x){
                subUpdateEstimate(dy, dx, y, x); 
            }
        }
    }

    // (y, x)の点をsearchして、(y, x)と(dy, dx)によって(ddy, ddx)を更新しようとしている
    void subUpdateEstimate(ll dy, ll dx, ll y, ll x){
        const ll THRESHOLD_GRID_DIST = 15;
        if(isBroken(y, x) == false || isBroken(dy, dx) == false) return; 
        else if(dy == y && dx == x) return; 
        else if(calcManhattanDist(y, x, dy, dx) > THRESHOLD_GRID_DIST) return; 

        double dist = calcDist(dy, dx, y, x);
        double trustWorthiness = calcTrustworthiness(y, x) * calcTrustworthiness(dy, dx); 
        ll hardness_1 = getHardness(y, x); 
        ll hardness_2 = getHardness(dy, dx); 
        if(dy == y){
            ll ddy = dy; 
            ll min_x = min(x, dx); 
            ll max_x = max(x, dx); 
            frep(ddx, min_x + 1, max_x){ 
                double dist_1 = pow(calcDist(ddy, ddx, y, x), 2); 
                double dist_2 = pow(calcDist(ddy, ddx, dy, dx), 2); 
                double estimate = ((double)hardness_1 * dist_2 + (double)hardness_2 * dist_1) / (dist_1 + dist_2); 
                double weight = trustWorthiness / (dist_1 * dist_2); 
                ll number = getEdgeNumber(dy, dx, y, x); 
                Info info(number, estimate, weight); 
                updateBlockEstimate(ddy, ddx, info); 
            }
        }
        else if(dx == x){
            ll ddx = dx; 
            ll min_y = min(y, dy); 
            ll max_y = max(y, dy); 
            frep(ddy, min_y + 1, max_y){ 
                double dist_1 = pow(calcDist(ddy, ddx, y, x), 2); 
                double dist_2 = pow(calcDist(ddy, ddx, dy, dx), 2); 
                double estimate = ((double)hardness_1 * dist_2 + (double)hardness_2 * dist_1) / (dist_1 + dist_2); 
                double weight = trustWorthiness / (dist_1 * dist_2); 
                ll number = getEdgeNumber(dy, dx, y, x); 
                Info info(number, estimate, weight); 
                updateBlockEstimate(ddy, ddx, info); 
            }
        }
        else{
            vector<P> latticePointVec = getLatticePoint(dy, dx, y, x); 
            for(P& p : latticePointVec){
                ll ddy = p.first; 
                ll ddx = p.second; 
                double dist_1 = pow(calcDist(ddy, ddx, y, x), 2); 
                double dist_2 = pow(calcDist(ddy, ddx, dy, dx), 2); 
                double estimate = ((double)hardness_1 * dist_2 + (double)hardness_2 * dist_1) / (dist_1 + dist_2); 
                double weight = trustWorthiness / (dist_1 * dist_2); 
                ll number = getEdgeNumber(dy, dx, y, x); 
                Info info(number, estimate, weight); 
                updateBlockEstimate(ddy, ddx, info); 
            }
        }
    }

    vector<P> getLatticePoint(ll dy, ll dx, ll y, ll x){
        vector<P> ret;
        set<P> st; 
        if(dx < x){
            swap(x, dx); 
            swap(y, dy); 
        }
        double tilt = (double)(dy - y) / (double)(dx - x);
        frep(ddx, x + 1, dx){
            double dif_x = ddx - x; 
            double dif_y = tilt * dif_x; 
            double ddy = (double)y + dif_y; 
            ll int_ddy = floor(ddy); 
            st.insert(P(int_ddy, ddx)); 
            // if(abs((double)int_ddy - ddy) > 1e-5) st.insert(P(int_ddy + 1, ddx)); 
            if(isInside(int_ddy + 1, ddx) == true) st.insert(P(int_ddy + 1, ddx));   // 格子点上にあってもこれを追加する。y=xでバグるため（y=2xは堪えると思うが一応）
            if(isInside(int_ddy - 1, ddx) == true) st.insert(P(int_ddy - 1, ddx));
        }
        
        if(dy < y){
            swap(x, dx); 
            swap(y, dy); 
        }
        tilt = (double)(dx - x) / (double)(dy - y);
        frep(ddy, y + 1, dy){
            double dif_y = ddy - y; 
            double dif_x = tilt * dif_y; 
            double ddx = (double)x + dif_x; 
            ll int_ddx = floor(ddx); 
            st.insert(P(ddy, int_ddx)); 
            // if(abs((double)int_ddx - ddx) > 1e-5) st.insert(P(ddy, int_ddx + 1)); 
            if(isInside(ddy, int_ddx + 1) == true) st.insert(P(ddy, int_ddx + 1));   // 格子点上にあってもこれを追加する。y=xでバグるため（y=2xは堪えると思うが一応）
            if(isInside(ddy, int_ddx - 1) == true) st.insert(P(ddy, int_ddx - 1));
        }
        irep(it, st) ret.push_back(*it); 
        return ret; 
    }

    void updateGrid(ll y, ll x){
        ll gridNumber = getGridNumber(y, x); 
        ll toSize = gridGraph[gridNumber].size(); 
        rep(i, toSize){
            ll toGridNumber = gridGraph[gridNumber][i].to; 
            ll dist = calcGridDist(gridNumber, toGridNumber); 
            gridGraph[gridNumber][i].cost = dist; 

            ll toGridSize = gridGraph[toGridNumber].size(); 
            rep(j, toGridSize){
                if(gridGraph[toGridNumber][j].to == gridNumber) gridGraph[toGridNumber][j].cost = dist; 
            }
        }
    }

    void updateTotalGridEdge(){
        DisjointSet ds(N * N); 
        BMat visit = init_bmat(N, N, false); 
        rep(y, N){
            rep(x, N){
                if(isBroken(y, x) == false) continue;
                else if(visit[y][x] == true) continue;
                queue<P> que; 
                que.push(P(y, x)); 
                while(!que.empty()){
                    P pos = que.front(); 
                    que.pop(); 
                    if(visit[pos.first][pos.second]) continue;
                    visit[pos.first][pos.second] = true; 
                    rep(k, 4){
                        ll dy = pos.first + neighborVec[k][0]; 
                        ll dx = pos.second + neighborVec[k][1]; 
                        if(isInside(dy, dx) == false) continue;
                        else if(visit[dy][dx] == true || isBroken(dy, dx) == false) continue;
                        ds.unite(f(pos.first, pos.second), f(dy, dx)); 
                    }
                }
            }
        }
        unordered_map<ll, vector<ll>> mp; 
        rep(y, N){
            rep(x, N){
                ll gridNumber = getGridNumber(y, x, true); 
                if(gridNumber < 0) continue;
                ll par = ds.findSet(f(y, x)); 
                mp[par].push_back(gridNumber); 
            }
        }
        irep(it, mp){
            // 同じ親を持つ、つまり、grid同士はコスト0で移動することができる。
            vector<ll> vec = it->second; 
            rep(i, vec.size()){
                rep(j, vec.size()){
                    if(i == j) continue;
                    ll gridNumber_1 = vec[i]; 
                    ll gridNumber_2 = vec[j]; 
                    P gridPlace_1 = getGridPlace(gridNumber_1); 
                    P gridPlace_2 = getGridPlace(gridNumber_2);
                    ll edgeNumber = getEdgeNumber(gridPlace_1, gridPlace_2); 
                    bool find = false;
                    rep(k, gridGraph[gridNumber_1].size()){
                        if(gridGraph[gridNumber_1][k].number == edgeNumber){
                            find = true; 
                            gridGraph[gridNumber_1][k].cost = 0; 
                            gridGraph[gridNumber_1][k].broken = true; 
                        }
                    }
                    if(find == false){
                        Edge newEdge(edgeNumber, gridNumber_1, gridNumber_2, 0); 
                        newEdge.broken = true; 
                        gridGraph[gridNumber_1].push_back(newEdge); 
                    }
                }
            }
        }
    }

    /*
    ll getProperPower(ll y, ll x){
        ll estimate = getEstimate(y, x); 
        ll estimateRemain = getEstimateRemain(y, x); 
        bool flag = isSearched(y, x);   // すでに探索されているか
        unordered_map<ll, double> FIRST_RATIO = {
            {1, 0.80}, {2, 0.85}, {4, 0.90}, {8, 1.0}, {16, 1.02}, {32, 1.05}, {64, 1.07}, {128, 1.1}
        }; 
        ll marginalPower = min((FIRST_RATIO[C] - 1.0) * estimate, C / 8); 
        if(flag == false) return max(estimateRemain + marginalPower, 10);
        else{   // 見積もりよりも大きい
            unordered_map<ll, ll> MIN_SHORT_POWER = 
                {{1, 8}, {2, 15}, {4, 25}, {8, 40}, {16, 60}, {32, 80}, {64, 100}, {128, 160}}; 
            ll power = min(max((ll)(estimate * 0.05), MIN_SHORT_POWER[C]), estimate); 
            return power; 
        } 
    }
    ll getProperPower(P p){ return getProperPower(p.first, p.second); }
    */

    ll getProperPower(ll y, ll x){
        ll estimate = getEstimate(y, x); 
        ll drill = getDrill(y, x); 
        bool flag = isSearched(y, x);   // すでに探索されているか
        unordered_map<ll, double> mp; 
        if(flag == false){
            if(estimate <= 20) mp = { {1, 0.80}, {2, 0.85}, {4, 0.90}, {8, 0.95}, {16, 1.00}, {32, 1.10}, {64, 1.15}, {128, 1.2} }; 
            else if(estimate <= 50) mp = { {1, 0.75}, {2, 0.80}, {4, 0.85}, {8, 0.95}, {16, 1.02}, {32, 1.05}, {64, 1.10}, {128, 1.15} };
            else if(estimate <= 100) mp = { {1, 0.75}, {2, 0.80}, {4, 0.85}, {8, 0.95}, {16, 1.02}, {32, 1.05}, {64, 1.10}, {128, 1.15} };
            else if(estimate <= 500) mp = { {1, 0.75}, {2, 0.80}, {4, 0.85}, {8, 0.95}, {16, 1.02}, {32, 1.05}, {64, 1.08}, {128, 1.10} };
            else mp = { {1, 0.75}, {2, 0.80}, {4, 0.85}, {8, 0.95}, {16, 1.00}, {32, 1.02}, {64, 1.05}, {128, 1.08} };
            ll power = estimate + min((mp[C] - 1.0) * estimate, C / 8); 
            return power; 
        }
        else{
            if(estimate <= 20) mp = { {1, 3}, {2, 4}, {4, 5}, {8, 6}, {16, 6}, {32, 8}, {64, 12}, {128, 12} }; 
            else if(estimate <= 35) mp = { {1, 4}, {2, 5}, {4, 6}, {8, 6}, {16, 6}, {32, 8}, {64, 12}, {128, 16} };
            else if(estimate <= 50) mp = { {1, 5}, {2, 6}, {4, 8}, {8, 9}, {16, 10}, {32, 12}, {64, 16}, {128, 20} };
            else if(estimate <= 75) mp = { {1, 7}, {2, 8}, {4, 11}, {8, 13}, {16, 15}, {32, 18}, {64, 22}, {128, 26} };
            else if(estimate <= 100) mp = { {1, 8}, {2, 11}, {4, 13}, {8, 16}, {16, 20}, {32, 24}, {64, 30}, {128, 36} };
            else if(estimate <= 150) mp = { {1, 10}, {2, 12}, {4, 16}, {8, 20}, {16, 25}, {32, 34}, {64, 40}, {128, 44} };
            else if(estimate <= 200) mp = { {1, 12}, {2, 14}, {4, 20}, {8, 24}, {16, 30}, {32, 44}, {64, 48}, {128, 56} };
            else if(estimate <= 350) mp = { {1, 14}, {2, 17}, {4, 25}, {8, 28}, {16, 35}, {32, 56}, {64, 60}, {128, 72} };
            else if(estimate <= 500) mp = { {1, 16}, {2, 20}, {4, 30}, {8, 35}, {16, 40}, {32, 70}, {64, 80}, {128, 96} };
            else if(estimate <= 1000) mp = { {1, 20}, {2, 24}, {4, 36}, {8, 42}, {16, 50}, {32, 96}, {64, 112}, {128, 128} };
            else mp = { {1, 24}, {2, 30}, {4, 42}, {8, 52}, {16, 60}, {32, 112}, {64, 128}, {128, 160} };
            return mp[C];
        }
    }
    ll getProperPower(P p){ return getProperPower(p.first, p.second); }

    // (y, x)の大きさを真面目に推定する
    // xx$xx
    // x@o@x
    // x@@@x
    // "$"を推定するときに"@"の情報があれば優先的に使うようにしたい
    double estimateSeriously(ll y, ll x) const{
        const ll SERIOUS_ESTIMATE_RANGE = 5;   // 正確に推定したいので範囲は小さくとる
        unordered_map<ll, double> SERIOUS_ESTIMATE_WEIGHT = {
            {1, 1.0}, {2, 0.5}, {3, 0.3}, {4, 0.2}, {5, 0.1}
        }; 
        vector<P> vec; 
        frep(dy, y - SERIOUS_ESTIMATE_RANGE, y + SERIOUS_ESTIMATE_RANGE + 1){
            frep(dx, x - SERIOUS_ESTIMATE_RANGE, x + SERIOUS_ESTIMATE_RANGE + 1){
                ll dist = calcDist(dy, dx, y, x); 
                if(dist > SERIOUS_ESTIMATE_RANGE || isInside(dy, dx) == false) continue; 
                else if(isBroken(dy, dx) == false) continue;
                else if(dy == y && dx == x) continue;
                else vec.push_back(P(dy, dx)); 
            }
        }

        if(vec.size() == 0) return getEstimate(y, x);   // 情報がないなら適当に、こんなことないと思うが

        double weightSum = 0.0; 
        double estimateSum = 0.0; 
        for(P& p : vec){
            ll dist = calcDist(p.first, p.second, y, x); 
            double trustworthiness = calcTrustworthiness(p.first, p.second); 
            double weight = SERIOUS_ESTIMATE_WEIGHT[dist] * trustworthiness; 
            weightSum += weight; 
            estimateSum += weight * getHardness(p.first, p.second);   // これをMaxHardnessとするのは雑すぎるが、とりあえず。MinHardnessも有効的に使えるようにしたい（とりあえずベンチマークがわりに）
        }
        double estimate = estimateSum / weightSum; 
        return estimate; 
    }

    double calcTrustworthiness(ll y, ll x) const{
        return sqrt(1.0 / (double)(getMaxHardness(y, x) - getMinHardness(y, x))); 
    }

    double calcWeight(ll dy, ll dx, ll y, ll x){
        ll dist = calcDist(dy, dx, y, x);   // これsqrt(2)の重みの推定がかなり雑では？
        if(dist > ESTIMATE_RANGE) return 0.0; 
        else if(isBroken(y, x)) return BROKEN_WEIGHT[dist]; 
        else return UNBROKEN_WEIGHT[dist]; 
    }

    // 2点間の距離を計算する
    // ユークリッド距離なのかマンハッタン距離にすべきなのかは真面目に確認する必要がある
    double calcDist(ll dy, ll dx, ll y, ll x) const{
        double d = pow(dy - y, 2) + pow(dx - x, 2); 
        double ret = sqrt(d); 
        return ret; 
    }
    double calcDist(P& p1, P& p2) const{ return calcDist(p1.first, p1.second, p2.first, p2.second); }

    inline ll calcManhattanDist(ll dy, ll dx, ll y, ll x) const{ return abs(dy - y) + abs(dx - x); }
    inline ll calcManhattanDist(P p1, P p2) const{ return calcManhattanDist(p1.first, p1.second, p2.first, p2.second); }

    ll calcGridDist(ll number_1, ll number_2){
        P p1 = getGridPlace(number_1); 
        P p2 = getGridPlace(number_2); 
        ll dist = calcManhattanDist(p1, p2); 
        double estimate1 = getHardness(p1); 
        double estimate2 = getHardness(p2); 
        bool broken1 = isBroken(p1); 
        bool broken2 = isBroken(p2); 
        ll ret = (estimate1 + estimate2) / 2 * dist; 
        return ret; 
    }

    // (y, x)から距離threshold以内に破壊されている点がないか
    bool judgeNeighborSearch(ll y, ll x, ll threshold){
        vector<ll> v{-1, 1}; 
        rep(i, threshold + 1){
            rep(j, threshold + 1 - i){
                for(ll s : v){
                    for(ll t : v){
                        ll dy = y + i * s; 
                        ll dx = x + j * t; 
                        if(isInside(dy, dx) && isSearched(dy, dx)) return true;
                    }
                }
            }
        }
        return false;
    }
    bool judgeNeighborSearch(P p, ll threshold){ return judgeNeighborSearch(p.first, p.second, threshold); }

    ll getEdgeNumber(ll y, ll x, ll dy, ll dx){
        ll a = f(y, x); 
        ll b = f(dy, dx); 
        if(a > b) swap(a, b); 
        ll c = N * N;
        return a * c + b;
    }
    ll getEdgeNumber(P p1, P p2){ return getEdgeNumber(p1.first, p1.second, p2.first, p2.second); }

    // Blockへのアクセス
    inline ll getDrill(ll y, ll x) const{ return blockMat[y][x].getDrill(); }
    inline ll getDrill(P& p) const{ return getDrill(p.first, p.second); }
    inline ll getSearchCount(ll y, ll x) const{ return blockMat[y][x].getSearchCount(); }
    inline ll getSearchCount(P& p) const{ return getSearchCount(p.first, p.second); }
    inline bool isBroken(ll y, ll x) const{ return blockMat[y][x].isBroken(); }
    inline bool isBroken(P& p) const{ return isBroken(p.first, p.second); }
    inline bool isSearched(ll y, ll x) const{ return blockMat[y][x].isSearched(); }
    inline bool isSearched(P& p) const{ return isSearched(p.first, p.second); }
    inline double getHardness(ll y, ll x) const{ return blockMat[y][x].getHardness(); }
    inline double getHardness(P& p) const{ return getHardness(p.first, p.second); }
    inline double getMinHardness(ll y, ll x) const{ return blockMat[y][x].getMinHardness(); }
    inline double getMinHardness(P& p) const{ return getMinHardness(p.first, p.second); }
    inline double getMaxHardness(ll y, ll x) const{ return blockMat[y][x].getMaxHardness(); }
    inline double getMaxHardness(P& p) const{ return getMaxHardness(p.first, p.second); }
    inline double getEstimate(ll y, ll x) const{ return blockMat[y][x].getEstimate(); }
    inline double getEstimate(P& p) const{ return getEstimate(p.first, p.second); }
    inline double getEstimateRemain(ll y, ll x) const{ return blockMat[y][x].getEstimateRemain(); }
    inline double getEstimateRemain(P& p) const{ return getEstimateRemain(p.first, p.second); }

    inline void updateBlock(ll y, ll x, ll power, ll broken){ blockMat[y][x].updateBlock(power, broken); }
    inline void updateBlockEstimate(ll y, ll x, Info& info){ blockMat[y][x].updateEstimate(info); }

    // グリッド関係
    // b==trueならgridでない点を入力したとき-1を返す
    inline ll getGridNumber(P p, bool b = false){
        ll number = f(p); 
        if(gridNumberAdministrator.find(number) != gridNumberAdministrator.end()) return gridNumberAdministrator[number]; 
        else if(b == false){
            print("Invalid input in State::getGridNumber", p.first, p.second); 
            exit(EXIT_FAILURE); 
        }
        else return -1;  
    }
    inline ll getGridNumber(ll y, ll x, bool b = false){ return getGridNumber(P(y, x), b); }
    inline P getGridPlace(ll number){
        P ret = gridPlaceAdministrator[number];
        if(gridPlaceAdministrator.find(number) != gridPlaceAdministrator.end()) return ret; 
        else{
            print("Invalid input in State::getGridPlace", number); 
            exit(EXIT_FAILURE); 
        }
    }
    inline ll getGridSize() const{ return gridNumberAdministrator.size(); }
    inline ll getHouseGridNumber(ll houseNumber){
        if(houseGridAdministrator.find(houseNumber) != houseGridAdministrator.end()) return houseGridAdministrator[houseNumber]; 
        else{
            print("Invalid input in State::getHouseGridNumber", houseNumber); 
            exit(EXIT_FAILURE); 
        }
    }
    inline ll getWaterGridNumber(ll waterNumber){
        if(waterGridAdministrator.find(waterNumber) != waterGridAdministrator.end()) return waterGridAdministrator[waterNumber]; 
        else{
            print("Invalid input in State::getWaterGridNumber", waterNumber); 
            exit(EXIT_FAILURE); 
        }
    }
    bool isGridBroken(ll gridNumber){
        P gridPlace = getGridPlace(gridNumber); 
        return isBroken(gridPlace); 
    }
}; 

class Agent{
public : 
    State state; 

    Agent() : state(){ init(); }

    void init(){}

    void solve(){
        destroyHouse();
        play(); 
        if(LOCAL) simulator.printTotalCost(); 
    }

    void destroyHouse(){
        for(House& house : houseVec){
            P housePlace = house.getPlace(); 
            while(state.isBroken(housePlace) == false){
                ll power = SEARCH_POWER[C]; 
                if(state.isSearched(housePlace) == false) power = FIRST_POWER[C]; 
                act(housePlace, power, true); 
            }
        }
    }

    void bandit_Astar(House& targetHouse){
        IQ<AstarState> pq; 
        ll gridSize = state.getGridSize();  
        DisjointSet ds(gridSize); 
        vector<bool> visit(gridSize, false);
        set<ll> finishHouseSt;   // 水源までたどり着いたhouseの番号を入れる

        // dsを初期化
        // 隣接&&壊れているgridをuniteしておく
        rep(i, gridSize){
            if(state.isGridBroken(i) == false) continue;
            vector<ll> neighborGridVec = state.getNeighborGridNumber(i); 
            for(ll j : neighborGridVec){
                if(state.isGridBroken(j) == true) ds.unite(i, j); 
            }
        }

        // 初期化
        if(true){
            ll houseNumber =  targetHouse.getHouseNumber();  
            P housePlace = targetHouse.getPlace(); 
            vector<ll> neighborGridVec = state.getNeighborGrid(housePlace);
            ll houseGridNumber = state.getHouseGridNumber(houseNumber); 
            ll cost = state.getGridShortestPathDist(houseGridNumber, houseNumber);   // posとhouse、今はposがhouseなのでこれで問題ない
            AstarState astarState(houseNumber, housePlace.first, housePlace.second, houseGridNumber, cost); 
            pq.push(astarState); 
        }

        while(true){
            AstarState posState = pq.top(); 
            pq.pop(); 
            ll posGridNumber = posState.getGridNumber(); 
            ll houseNumber = posState.getHouseNumber(); 
            ll houseGridNumber = state.getHouseGridNumber(houseNumber); 
            P targetPlace = posState.getPlace();

            // もう水源と繋がっているならおにまい
            if(isUniteHouseAndWater(houseNumber, ds) == true) break; 
            
            // すでに壊れている可能性もある、その時はactをスキップして辺の追加だけ行うようにする
            if(state.isGridBroken(posGridNumber) == false){
                ll power; 
                ll searchCount = state.getSearchCount(targetPlace); 
                if(searchCount == 0) power = FIRST_POWER[C]; 
                else if(searchCount == 1) power = SECOND_POWER[C]; 
                else if(searchCount == 2) power = THIRD_POWER[C]; 
                else power = SEARCH_POWER[C]; 
                act(targetPlace, power, true); 
            }

            // A*を更新
            if(state.isBroken(targetPlace) == false){
                // コストを再計算してpush
                ll dist = state.getGridShortestPathDist(posGridNumber, houseNumber); 
                AstarState nextState(houseNumber, targetPlace.first, targetPlace.second, posGridNumber, dist); 
                pq.push(nextState);
            }
            else{
                // 隣接するgridをpushできるのは1度だけ、そうしないと無限ループする
                if(visit[posGridNumber] == false){ 
                    visit[posGridNumber] = true;
                    uniteGrid(posGridNumber, ds); 
                    if(isUniteHouseAndWater(houseNumber, ds) == true){   
                        // 家と水源をつなげることが出来たらPriority Queueを更新せずに終了
                    }
                    else{
                        // 隣接するgridをpush
                        vector<Edge> neighborEdgeVec = state.getNeighborGridEdge(posGridNumber); 
                        for(Edge& edge : neighborEdgeVec){
                            ll nextGridNumber = edge.to; 
                            ll dist = state.getGridShortestPathDist(nextGridNumber, houseNumber);
                            P nextPlace = state.getGridPlace(nextGridNumber); 
                            AstarState nextState(houseNumber, nextPlace.first, nextPlace.second, nextGridNumber, dist); 
                            pq.push(nextState); 
                        } 
                    }
                }
            }

            // 終了条件を更新
            for(House& house : houseVec){
                if(isUniteHouseAndWater(house.getHouseNumber(), ds) == true) finishHouseSt.insert(house.getHouseNumber()); 
            } 
        }
    }

    void uniteGrid(ll brokenGridNumber, DisjointSet& ds){
        vector<ll> neighborGridNumberVec = state.getNeighborGridNumber(brokenGridNumber); 
        for(ll toGridNumber : neighborGridNumberVec){
            if(state.isGridBroken(toGridNumber) == true) ds.unite(brokenGridNumber, toGridNumber); 
        }
    }

    bool isUniteHouseAndWater(ll houseNumber, DisjointSet& ds){
        ll houseGridNumber = state.getHouseGridNumber(houseNumber); 
        for(Water& water : waterVec){
            ll waterGridNumber = state.getWaterGridNumber(water.getWaterNumber()); 
            if(ds.same(houseGridNumber, waterGridNumber) == true) return true; 
        }
        return false; 
    }

    void drillRoute(vector<ll>& routeVec, ll targetHouseNumber){
        queue<P> que;
        for(ll t : routeVec) que.push(inverse(t)); 
        ll v = 0; 
        while(!que.empty()){
            P p = que.front(); 
            if(state.isBroken(p.first, p.second)) que.pop(); 
            else act(p, state.getProperPower(p)); 
        }
    }

    void play(){
        set<ll> unvisitHouseSt; 
        rep(i, houseVec.size()) unvisitHouseSt.insert(i); 
        while(unvisitHouseSt.size() != 0){
            state.updateTotalGridEdge();
            ll targetHouseNumber;
            ll bestScore = INT_MAX; 
            irep(it, unvisitHouseSt){
                ll houseNumber = *it;
                ll houseGridNumber = state.getHouseGridNumber(houseNumber);  
                ll score = state.getGridShortestPathDist(houseGridNumber, houseGridNumber);
                if(score < bestScore){
                    bestScore = score; 
                    targetHouseNumber = houseNumber; 
                }
            }
            bandit_Astar(houseVec[targetHouseNumber]);
            ll score; 
            vector<ll> routeVec = state.getPlan(targetHouseNumber, score);  
            vector<ll> bestRoute = shuffleRoute(routeVec); 
            drillRoute(bestRoute, targetHouseNumber);  
            unvisitHouseSt.erase(targetHouseNumber); 
        }
    }

    queue<ll> calcHouseOrder(){
        IQ<P> pq; 
        for(House& house : houseVec){
            ll minDist = INT_MAX; 
            for(Water& water : waterVec){
                ll dist = state.calcManhattanDist(house.getPlace(), water.getPlace()); 
                if(minDist > dist) minDist = dist; 
            }
            P p(minDist, house.getHouseNumber()); 
            pq.push(p); 
        }
        queue<ll> ret; 
        while(!pq.empty()){
            P p = pq.top(); 
            pq.pop(); 
            ret.push(p.second); 
        }
        return ret; 
    }

    vector<ll> shuffleRoute(vector<ll>& routeVec){
        // 135642という順番で掘っていく〜
        vector<ll> brokenIndex; 
        rep(i, routeVec.size()){
            ll number = routeVec[i]; 
            P p = inverse(number); 
            if(state.isBroken(p) == true) brokenIndex.push_back(i); 
        }
        
        vector<ll> ret;
        rep(i, brokenIndex.size() - 1){
            ll left = brokenIndex[i] + 1; 
            ll right = brokenIndex[i + 1] - 1;
            if(right - left < 0) continue;
            set<ll> st;
            while(true){
                if(bs(st, left)) break;
                st.insert(left); 
                ret.push_back(routeVec[left]); 
                left++;
                if(bs(st, right)) break;
                st.insert(right); 
                ret.push_back(routeVec[right]); 
                right--; 
            }
        }
        return ret; 
    }

    void act(ll y, ll x, ll power, bool gridUpdate = false){
        const ll MAX_POWER = 4999;
        const ll MIN_POWER = 1; 
        power = max(power, MIN_POWER);  
        power = min(power, MAX_POWER); 
        if(LOCAL){
            ll result = simulator.increment(y, x, power); 
            print(y, x, power); 
            state.update(y, x, power, result); 
            if(gridUpdate) state.updateGrid(y, x); 
        }
        else{
            print(y, x, power); 
            ll result; 
            cin >> result; 
            state.update(y, x, power, result); 
            if(gridUpdate) state.updateGrid(y, x); 
        }
    }
    void act(P& p, ll power, bool gridUpdate = false){ act(p.first, p.second, power, gridUpdate); }
}; 

int main(){
    cin >> N >> WATER_SIZE >> HOUSE_SIZE >> C;  
    simulator.init(); 
    rep(i, WATER_SIZE){
        ll a, b;
        cin >> a >> b;
        waterVec.push_back(Water(i, a, b)); 
    }
    rep(i, HOUSE_SIZE){
        ll c, d;
        cin >> c >> d; 
        houseVec.push_back(House(i, c, d)); 
    }
    Agent agent;
    agent.solve(); 
}


