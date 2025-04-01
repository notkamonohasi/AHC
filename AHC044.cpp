#include <bits/stdc++.h>
// #define MOD 1000000007
#define MOD 998244353
#define ll long long
#define ld long double
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define frep(i, k, n) for (ll i = (ll)k; i < (ll)(n); i++)
#define brep(i, n) for (ll i = (ll)(n - 1); i >= 0; i--)
#define irep(it, mp) for (auto it = mp.begin(); it != mp.end(); it++)
#define len(x) (ll) x.size()
#define pprint(x) cout << fixed << setprecision(12) << x << endl
#define bs(st, key) (st.find(key) != st.end() ? true : false)
#define lb(v, k) lower_bound(v.begin(), v.end(), k)
#define ub(v, k) upper_bound(v.begin(), v.end(), k)
#define all(v) v.begin(), v.end()
#define bit(x, i) (((x) >> (i)) & 1)
using namespace std;

// const vector<vector<ll>> neighbor_vec = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
// const vector<vector<ll>> neighbor_vec = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
// map<char, vector<ll>> neighbor_mp = {{'D', {1, 0}}, {'R', {0, 1}}, {'U', {-1, 0}}, {'L', {0,
// -1}}};  // constつかない const ld PI = 3.141592653589793238462643;

ll POW(ll a, ll n) {
    if (n == 0) return 1;
    if (n == 1) return a;
    if (n % 2 == 1) return a * POW(a, n - 1);
    ll t = POW(a, n / 2);
    return t * t;
}
ll MODPOW(ll a, ll n) {
    if (n == 0) return 1;
    if (n == 1) return a % MOD;
    if (n % 2 == 1) return (a * MODPOW(a, n - 1)) % MOD;
    ll t = MODPOW(a, n / 2);
    return (t * t) % MOD;
}
ll MODINV(ll a) { return MODPOW(a, MOD - 2); }
ll CEIL(ll a, ll b) {
    ll ret = (a + b - 1) / b;
    return ret;
}
ll SUM(vector<ll>& v) {
    ll ret = 0;
    for (ll x : v) ret += x;
    return ret;
}
ll max(vector<ll>& v) {
    assert(v.size() > 0);
    ll ret = v[0];
    for (ll x : v) ret = max(ret, x);
    return ret;
}
ll min(vector<ll>& v) {
    assert(v.size() > 0);
    ll ret = v[0];
    for (ll x : v) ret = min(ret, x);
    return ret;
}
ll max(ll a, ll b) {
    if (a > b)
        return a;
    else
        return b;
}
ll min(ll a, ll b) {
    if (a > b)
        return b;
    else
        return a;
}
double min(double a, double b) {
    if (a > b)
        return b;
    else
        return a;
}
ll max(ll a, ll b, ll c) {
    ll d = max(a, b);
    return max(c, d);
}
ll min(ll a, ll b, ll c) {
    ll d = min(a, b);
    return min(c, d);
}
ll argmax(vector<ll>& v) {
    assert(v.size() > 0);
    ll ret = 0;
    ll best = v[0];
    frep(i, 1, v.size()) {
        if (best < v[i]) {
            best = v[i];
            ret = i;
        }
    }
    return ret;
}
ll argmin(vector<ll>& v) {
    assert(v.size() > 0);
    ll ret = 0;
    ll best = v[0];
    frep(i, 1, v.size()) {
        if (best > v[i]) {
            best = v[i];
            ret = i;
        }
    }
    return ret;
}
void chmax(ll& a, ll b) {
    if (b > a) a = b;
}
void chmin(ll& a, ll b) {
    if (a > b) a = b;
}
void yes(bool b) {
    if (b)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
}
void print() { cout << endl; }
template <class Head, class... Tail>
void print(Head&& head, Tail&&... tail) {
    if (sizeof...(tail) == 0)
        cout << head << endl;  // oj用
    else {
        cout << head << " ";
        print(std::forward<Tail>(tail)...);
    }
}
template <typename T>
void vprint(vector<T>& v) {
    rep(i, v.size()) cout << v[i] << (i != v.size() - 1 ? " " : "");
    cout << endl;
}
using P = pair<ll, ll>;
bool sameP(P& p1, P& p2) {
    if (p1.first == p2.first && p1.second == p2.second)
        return true;
    else
        return false;
}
void print_pair(P& p) { cout << p.first << " " << p.second << endl; }
using T = tuple<ll, ll, ll>;  // ll x, y, z; tie(x, y, z) = T
template <typename T>
using PQ = priority_queue<T>;
template <typename T>
using IQ = priority_queue<T, vector<T>, greater<T>>;
using Mat = vector<vector<ll>>;
Mat init_mat(ll a, ll b) {
    Mat ret(a, vector<ll>(b, 0));
    return ret;
}
Mat init_mat(ll a, ll b, ll c) {
    Mat ret(a, vector<ll>(b, c));
    return ret;
}
template <typename T>
void print_mat(vector<vector<T>>& mat) {
    rep(i, mat.size()) {
        rep(j, mat[i].size()) { cout << mat[i][j] << " "; }
        cout << endl;
    }
}
using PMat = vector<vector<P>>;
PMat init_pmat(ll a, ll b) {
    PMat ret(a, vector<P>(b, P(0, 0)));
    return ret;
}
PMat init_pmat(ll a, ll b, P c) {
    PMat ret(a, vector<P>(b, c));
    return ret;
}
using BMat = vector<vector<bool>>;
BMat init_bmat(ll a, ll b) {
    BMat ret(a, vector<bool>(b, false));
    return ret;
}
BMat init_bmat(ll a, ll b, bool c) {
    BMat ret(a, vector<bool>(b, c));
    return ret;
}
using DMat = vector<vector<double>>;
DMat init_dmat(ll a, ll b) {
    DMat ret(a, vector<double>(b, 0.0));
    return ret;
}
DMat init_dmat(ll a, ll b, double c) {
    DMat ret(a, vector<double>(b, c));
    return ret;
}
using Tensor = vector<vector<vector<ll>>>;
Tensor init_tensor(ll a, ll b, ll c) {
    Tensor ret(a, Mat(b, vector<ll>(c, 0)));
    return ret;
}
Tensor init_tensor(ll a, ll b, ll c, ll d) {
    Tensor ret(a, Mat(b, vector<ll>(c, d)));
    return ret;
}

using Graph = vector<vector<ll>>;
Graph init_graph(ll V) {
    Graph ret;
    vector<ll> empty;
    rep(i, V) ret.push_back(empty);
    return ret;
}

struct Edge {
    ll number, from, to;
    ll cost;
    Edge() {}
    Edge(ll a) : to(a) {}
    Edge(ll a, ll b) : to(a), cost(b) {}
    Edge(ll a, ll b, ll c) : from(a), to(b), cost(c) {}
    Edge(ll a, ll b, ll c, ll d) : number(a), from(b), to(c), cost(d) {}
    bool operator>(const Edge& another) const { return cost > another.cost; }
    bool operator<(const Edge& another) const { return cost < another.cost; }
};
using EdgeGraph = vector<vector<Edge>>;
EdgeGraph init_edgeGraph(ll V) {
    EdgeGraph ret;
    vector<Edge> empty;
    rep(i, V) ret.push_back(empty);
    return ret;
}

struct Place {
    ll y, x;
    Place() {}
    Place(ll y_, ll x_) : y(y_), x(x_) {}
    bool is_inside(ll h, ll w) { return (0 <= y && y < h && 0 <= x && x < w); }
    bool is_inside(ll n) { return is_inside(n, n); }
    Place operator+(const Place& another) const { return Place(y + another.y, x + another.x); }
    Place operator+(const P& p) const { return Place(y + p.first, x + p.second); }
    Place operator+(const vector<ll>& v) const { return Place(y + v[0], x + v[1]); }
    bool operator==(const Place& another) const { return y == another.y && x == another.x; }
};

random_device rd;
mt19937 eng(0);
uniform_int_distribution<> randInt(0, INT_MAX);
uniform_real_distribution<> uniform(0.0, 1.0);

constexpr ll N = 100;
constexpr ll L = 500000;
constexpr ll END_TIME = 1980000;
constexpr ll POST_PROCESS_TIME = 40000;

constexpr double START_TEMP = 100000;  // 開始時の温度
constexpr double END_TEMP = 100;       // 終了時の温度

vector<ll> TARGET_VEC;
ll START_TIME;

namespace Distribute {
struct RatioElement {
    ll index;
    double fractional_part;
};

std::vector<ll> distributeClosestSum(ll N, const std::vector<ll>& ratios) {
    ll n = ratios.size();
    std::vector<ll> result(n, 0);
    std::vector<RatioElement> fractional_parts;

    ll sum_ratios = 0;
    for (ll r : ratios) sum_ratios += r;

    ll sum_rounded = 0;
    for (ll i = 0; i < n; ++i) {
        double ideal_value = (double)ratios[i] / sum_ratios * N;
        result[i] = std::floor(ideal_value);
        fractional_parts.push_back({i, ideal_value - result[i]});
        sum_rounded += result[i];
    }

    // 調整する必要がある個数
    ll adjustment_needed = N - sum_rounded;

    // 小数部分の大きい順にソートして調整
    std::sort(fractional_parts.begin(), fractional_parts.end(),
              [](const RatioElement& a, const RatioElement& b) {
                  return a.fractional_part > b.fractional_part;
              });

    for (ll i = 0; i < adjustment_needed; ++i) {
        result[fractional_parts[i].index]++;  // 切り上げ調整
    }

    return result;
}
};  // namespace Distribute

double calc_sa_temp() {
    double lapse = clock() - START_TIME;
    double progressRatio = lapse / (ld)END_TIME;  // 進捗。開始時が0.0、終了時が1.0
    double b = 1.0 / (1.0 + exp(progressRatio));
    double temp = END_TEMP + (START_TEMP - END_TEMP) * b;
    return temp;
}

struct Solver {
    struct State {
        Mat answer_mat;
        vector<ll> cnt_vec;
        Mat cnt_mat;
        ll score;

        State() {}
        State(Mat answer_mat_) : answer_mat(answer_mat_) {}

        tuple<ll, vector<ll>, Mat> simulate(ll l) {
            assert(l > 0);
            vector<ll> my_cnt_vec(N, 0);
            Mat my_cnt_mat = init_mat(N, 2, 0);
            ll pos = 0;
            rep(_, l) {
                my_cnt_vec[pos]++;
                ll odd = my_cnt_vec[pos] % 2;
                ll next = answer_mat[pos][odd];
                my_cnt_mat[pos][odd]++;
                pos = next;
            }

            ll ret = 0;
            rep(i, N) {
                ll t = my_cnt_vec[i] * L / l;
                ret += abs(TARGET_VEC[i] - t);
            }

            ld a = (ld)L / (ld)l;
            rep(i, N) {
                my_cnt_vec[i] *= a;
                rep(j, 2) { my_cnt_mat[i][j] *= a; }
            }

            return make_tuple(ret, my_cnt_vec, my_cnt_mat);
        }

        void post_process() {
            while (clock() - START_TIME <= END_TIME) {
                ll target = -1;
                ll best_score = -1;
                rep(i, N) {
                    if (cnt_vec[i] == 0) {
                        ll s = TARGET_VEC[i];
                        if (s > best_score) {
                            best_score = s;
                            target = i;
                        }
                    }
                }
                if (target < 0) break;
                // print("tar", target, TARGET_VEC[target]);

                ll best_dif = 0;
                P sol;
                rep(i, N) {
                    rep(j, 2) {
                        ll next = answer_mat[i][j];
                        if (cnt_vec[next] <= TARGET_VEC[next]) continue;
                        if (cnt_mat[i][j] == 0) continue;
                        ll pos_score = abs(cnt_vec[next] - TARGET_VEC[next]) + TARGET_VEC[target];
                        ll next_score = abs(cnt_vec[next] - cnt_mat[i][j] - TARGET_VEC[next]) +
                                        abs(TARGET_VEC[target] - cnt_mat[i][j]);
                        ll dif = pos_score - next_score;
                        // print("s", dif, cnt_mat[i][j], pos_score, next_score, cnt_vec[next],
                        // TARGET_VEC[next]);
                        if (dif > best_dif) {
                            best_dif = dif;
                            sol = P(i, j);
                        }
                    }
                }

                if (best_dif != 0) {
                    ll a = answer_mat[sol.first][sol.second];
                    answer_mat[target][0] = a;
                    answer_mat[target][1] = a;
                    answer_mat[sol.first][sol.second] = target;
                    set_result(L);
                } else
                    break;
            }
        }

        void set_result(ll l) {
            const auto [a, b, c] = simulate(l);
            score = a;
            cnt_vec = b;
            cnt_mat = c;
        }

        void print_answer() { print_mat(answer_mat); }
    };
    State state;

    ll FIRST_L = 1000;

    Solver() { init(); }

    void init() {
        vector<ll> weight_vec(N);
        rep(i, N) weight_vec[i] = sqrt(TARGET_VEC[i]);
        vector<ll> cnt_vec = Distribute::distributeClosestSum(2 * N, weight_vec);
        vector<ll> v;
        rep(i, N) { rep(_, cnt_vec[i]) v.push_back(i); }
        // vprint(v);
        shuffle(all(v), eng);
        Mat first_answer_mat = init_mat(N, 2);
        rep(i, N) {
            rep(j, 2) { first_answer_mat[i][j] = v[i * 2 + j]; }
        }
        state = State(first_answer_mat);
        state.set_result(FIRST_L);
    }

    void solve() {
        ll prev_l = FIRST_L;
        vector<P> TIMES = {
            P(1e5, FIRST_L),
            P(2e5, 5000),
            P(5e5, 25000),
            P(9e5, 125000),
            P(END_TIME - POST_PROCESS_TIME, L),
        };
        while (true) {
            ll t = clock() - START_TIME;
            if (t >= TIMES.back().first) break;
            ll l = L;
            bool ok = false;
            rep(i, TIMES.size() - 1) {
                if (TIMES[i].first <= t && t <= TIMES[i + 1].first) {
                    l = TIMES[i + 1].second;
                    ok = true;
                    break;
                }
            }
            if (!ok) l = TIMES[0].second;
            l = min(L, l);
            if (prev_l != l) state.set_result(l);
            prev_l = l;
            solve_one(l);
        }
        // state.print_answer();
        // print("#");
        state.post_process();
    }

    void solve_one(ll l) {
        ll r1 = randInt(eng) % N;
        ll r2 = randInt(eng) % 2;
        ll r3 = randInt(eng) % N;
        ll r4 = randInt(eng) % 2;
        ll a = state.answer_mat[r1][r2];
        ll b = state.answer_mat[r3][r4];

        if (true) {
            ll pos_score =
                abs(state.cnt_vec[a] - TARGET_VEC[a]) + abs(state.cnt_vec[b] - TARGET_VEC[b]);
            ll next_score = abs(state.cnt_vec[a] - TARGET_VEC[a] - state.cnt_mat[r1][r2] +
                                state.cnt_mat[r3][r4]) +
                            abs(state.cnt_vec[b] - TARGET_VEC[b] + state.cnt_mat[r1][r2] -
                                state.cnt_mat[r3][r4]);
            // print(pos_score, next_score);
            if (pos_score <= next_score) return;
        }

        Mat next_answer_mat = state.answer_mat;
        swap(next_answer_mat[r1][r2], next_answer_mat[r3][r4]);
        State next_state(next_answer_mat);
        next_state.set_result(l);

        double temp = calc_sa_temp();
        ll delta = state.score - next_state.score;
        double prob = exp(delta / temp);
        if (prob > uniform(eng)) {
            swap(state, next_state);
            // if (l == L) yes(true);
        } else {
            // if (l == L) yes(false);
        }

        if (l == L && randInt(eng) % 20 == 0) state.post_process();
    }
};

void input() {
    ll n, l;
    cin >> n >> l;
    TARGET_VEC.resize(N);
    rep(i, N) cin >> TARGET_VEC[i];
}

int main() {
    START_TIME = clock();
    input();
    Solver solver;
    solver.solve();
    solver.state.print_answer();
}
