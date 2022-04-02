#include <bits/stdc++.h>
#define LIMIT (1<<30)
//#define MOD 1000000007
#define MOD 998244353
#define ll long long
#define ld float
#define ERROR "ERROR!!"
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define frep(i, k, n) for (ll i = (ll)k; i < (ll)(n); i++)
#define brep(i, n) for (ll i = (ll)(n - 1); i >= 0; i--)
#define len(x) (ll)x.size()
#define print(x) cout << x << endl
#define dprint(a, b) cout << a << " " << b << endl
#define tprint(a, b, c) cout << a << " " << b << " " << c << endl
#define fprint(a, b, c, d) cout << a << " " << b << " " << c << " " << d << endl
#define pprint(x) cout << fixed << setprecision(10) << x << endl
#define vprint(v) for(auto x : v) cout << x << " ";   cout << endl
#define bs(a, b) binary_search(a.begin(), a.end(), b)
using namespace std;

const ll INF = LLONG_MAX;
//const ll vec[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
//const ld PI = 3.141592653589793238462643;

ll POW(ll a, ll b){ll ret = 1; rep(i, b) ret *= a; return ret;}
ll max(ll a, ll b){if(a > b) return a; else return b;}
ll min(ll a, ll b){if(a > b) return b; else return a;}
ll max(ll a, ll b, ll c){ll d = max(a, b); return max(c, d);}
ll min(ll a, ll b, ll c){ll d = min(a, b); return min(c, d);}
void yes(bool b){if(b) cout << "Yes" << endl; else cout << "No" << endl;}
struct Edge {ll to, cost;};
using P = pair<ll, ll>;
using Graph = vector<vector<Edge> >;
using Mat = vector<vector<ll> >;
Graph init_graph(ll V){Graph ret; vector<Edge> empty; rep(i, V) ret.push_back(empty); return ret;}
Mat init_mat(ll a, ll b){Mat ret; vector<ll> empty; rep(i, b) empty.push_back(0); rep(i, a) ret.push_back(empty); return ret;}
Mat init_mat(ll a, ll b, ll c){Mat ret; vector<ll> empty; rep(i, b) empty.push_back(c); rep(i, a) ret.push_back(empty); return ret;}

const float START_TEMP =  1500; // 開始時の温度
const float END_TEMP   =  50; // 終了時の温度
const float END_TIME   =  1980000; // 終了時間

const ll H = 20;
const ll W = 20;
const ll T = 200;
const ll MAX_LENGTH = 200;
const ld EPSILON = pow(10, -5);
char all_vect[] = {'D', 'R', 'U', 'L'};

random_device rd;
mt19937 eng(rd());
uniform_int_distribution<> randInt(0, INT_MAX);
uniform_real_distribution<> uniform(0.0, 1.0);

ll si, sj, ti, tj;
float p;

clock_t start;

bool yoko[H][W - 1], tate[H - 1][W];
map<char, bool> wall[H][W];
Graph g;

ld prob[T + 1][H][W];

void __init__(){
    rep(i, H){
        rep(j, W){
            rep(t, T + 1){
                prob[t][i][j] = 0.0;
            }
        }
    }
    prob[0][si][sj] = 1.0;
    
    rep(i, H){
        rep(j, W){
            for(auto c : all_vect) wall[i][j][c] = false;
        }
    }
}

void __input__(){
    cin >> si >> sj >> ti >> tj;
    cin >> p;
    rep(i, H){
        rep(j, W - 1){
            char a;   cin >> a;
            if(a == '0'){
                wall[i][j]['R'] = true;
                wall[i][j + 1]['L'] = true;
            }
        }
    }
    rep(i, H - 1){
        rep(j, W){
            char a;   cin >> a;
            if(a == '0'){
                wall[i][j]['D'] = true;
                wall[i + 1][j]['U'] = true;
            }
        }
    }
}

P calc_next(ll y, ll x, char c){
    if(wall[y][x][c] == false){P ret = make_pair(y, x); return ret;}
    else{
        ll dy = y;   ll dx = x;
        if(c == 'D') dy++;
        else if(c == 'R') dx++;
        else if(c == 'U') dy--;
        else if(c == 'L') dx--;
        else print(ERROR);
        
        P ret = make_pair(dy, dx);
        return ret;
    }
}

void __make_graph__(){
    g = init_graph(H * W);
    rep(i, H){
        rep(j, W){
            for(auto c : all_vect){
                if(wall[i][j][c] == true){ 
                    P next = calc_next(i, j, c);
                    Edge e = {next.first * W + next.second, (rand() % 20) + 10};
                    g[i * W + j].push_back(e);
                }
            }
        }
    }
}

ld calc_score(string str){
    rep(i, H){
        rep(j, W){
            rep(t, T + 1){
                prob[t][i][j] = 0.0;
            }
        }
    }
    prob[0][si][sj] = 1.0;
    
    ld score = 0.0;
    rep(t, len(str)){
        char c = str[t];
        rep(i, H){
            rep(j, W){
                ld pos = prob[t][i][j];
                if(pos < EPSILON) continue;
                P next = calc_next(i, j, c);
                if(pos > 1.0) dprint(next.first, next.second);
                prob[t + 1][next.first][next.second] += pos * (1.0 - p);
                prob[t + 1][i][j] += pos * p;
            }
        }
        
        score += (400 - t) * prob[t + 1][ti][tj];
        prob[t + 1][ti][tj] = 0.0;
    }
    
    score *= 250000.0;
    
    return score;
}

void dijkstra(const Graph& G, ll s, vector<ll>& dis, vector<ll>& prev) {
    ll N = G.size();
    dis.resize(N, INF);
    prev.resize(N, -1); // 初期化
    priority_queue<P, vector<P>, greater<P>> pq; 
    dis[s] = 0;
    pq.emplace(dis[s], s);
    while(!pq.empty()){
        P p = pq.top();
        pq.pop();
        ll v = p.second;
        if(dis[v] < p.first){
            continue;
        }
        for(auto &e : G[v]){
            if(dis[e.to] > dis[v] + e.cost){
                dis[e.to] = dis[v] + e.cost;
                prev[e.to] = v; // 頂点 v を通って e.to にたどり着いた
                pq.emplace(dis[e.to], e.to);
            }
        }
    }
}

// tへの最短path
vector<ll> get_path(const vector<ll>& prev, ll t){
    vector<ll> path;
    for(ll cur = t; cur != -1; cur = prev[cur]){
        path.push_back(cur);
    }
    reverse(path.begin(), path.end()); // 逆順なのでひっくり返す
    return path;
}

string path_to_str(const vector<ll>& path){
    string ret = "";
    ll size = len(path);
    rep(i, size - 1){
        ll y = path[i] / W;
        ll x = path[i] % W;
        ll dy = path[i + 1] / W;
        ll dx = path[i + 1] % W;
        if(dy - y == 1) ret += 'D';
        else if(y - dy == 1) ret += 'U';
        else if(dx - x == 1) ret += 'R';
        else if(x - dx == 1) ret += 'L';
        else print(ERROR);
    }
    
    return ret;
}

char make_char(){
    ll t = randInt(eng) % 4;
    if(t == 0) return 'U';
    else if(t == 1) return 'R';
    else if(t == 2) return 'D';
    else if(t == 3)return 'L';
    else{print("ERROR"); return 'A';}
}

string arrange_first_answer(string str){
    string ret;
    rep(i, len(str)){
        ll t = uniform(eng) * 5 * p;
        rep(j, t + 1) ret += str[i];
    }
    ll pos_len = len(ret);
    rep(i, MAX_LENGTH - pos_len) ret += make_char();
    return ret;
}

string make_first_answer(){
    __make_graph__();
    vector<ll> dis, prev;
    ll start = si * W + sj;
    ll goal = ti * W + tj;
    dijkstra(g, start, dis, prev);
    vector<ll> path = get_path(prev, goal);
    string str = path_to_str(path);
    return arrange_first_answer(str);
}

/*焼きなましの遷移*/
string insert(string str){
    ll size = len(str);
    ll t = randInt(eng) % size;
    char c = make_char();
    string ret = "";
    rep(i, t) ret += str[i];
    ret += c;
    frep(i, t, size) ret += str[i];
    ll p = randInt(eng) % (size + 1);
    ret.erase(p, 1);
    return ret;
}

string swap(string str){
    ll size = len(str);
    ll t = randInt(eng) % (size - 1);
    string ret = str;
    swap(ret[t], ret[t + 1]);
    return ret;
}

string doubling(string str){
    ll size = len(str);
    ll t = randInt(eng) % size;
    string ret = "";
    rep(i, t) ret += str[i];
    ret += str[t];
    frep(i, t, min(MAX_LENGTH - 1, size)) ret += str[i];
    return ret;
}

string simulated_annieling(string first_str){
    ld best_score = calc_score(first_str);
    string best_str = first_str;
    ld pos_score = best_score;
    string pos_str = first_str;
    
    // 焼きなましスタート
    while(true){
        clock_t pos_time = clock();
        if(pos_time > END_TIME) break;
        
        float lapse = pos_time - start;
        float progressRatio = lapse / END_TIME;   // 進捗。開始時が0.0、終了時が1.0
        float temp = START_TEMP + (END_TEMP - START_TEMP) * progressRatio;
        
        string next;
        ll r = randInt(eng) % 3;
        if(r == 0) next = insert(pos_str);
        else if(r == 1) next = swap(pos_str);
        else if(r == 2) next = doubling(pos_str);
        
        ld score = calc_score(next);
        ld delta = score - pos_score;
        float probability = exp(delta / temp);
        
        if(probability > uniform(eng)){
            pos_score = score;
            pos_str = next;
            if(score > best_score){
                best_score = score;
                best_str = next;
            }
        }
    }
    
    // pprint(best_score);
    return best_str;
}


int main(){
    start = clock();   // time_recorder
    __init__();
    __input__();
    string str = make_first_answer();
    string best_str = simulated_annieling(str);
    
    print(best_str);
}
