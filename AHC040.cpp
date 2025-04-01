#include <bits/stdc++.h>
// #define MOD 1000000007
#define MOD 998244353
#define ll long long
#define ld long double
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define frep(i, k, n) for (ll i = (ll)k; i < (ll)(n); i++)
#define brep(i, n) for (ll i = (ll)(n - 1); i >= 0; i--)
#define irep(it, mp) for (auto it = mp.begin(); it != mp.end(); it++)
#define pprint(x) cout << fixed << setprecision(12) << x << endl
#define BS(st, key) (st.find(key) != st.end() ? true : false)
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
template <typename T>
T max(vector<T>& v) {
    assert(!v.empty());
    T ret = v[0];
    for (T x : v) ret = max(ret, x);
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
template <typename T>
T max(T a, T b, T c) {
    T d = max(a, b);
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
void _print() { cout << endl; }
template <class Head, class... Tail>
void _print(Head&& head, Tail&&... tail) {
    if (sizeof...(tail) == 0)
        cout << head << endl;  // oj用
    else {
        cout << head << " ";
        _print(std::forward<Tail>(tail)...);
    }
}
template <class... All>
void print(All&&... a) {
    cout << "# ";
    _print(std::forward<All>(a)...);
}
template <class... All>
void ans_print(All&&... a) {
    _print(std::forward<All>(a)...);
}
template <typename T>
void vprint(vector<T>& v, bool debug = true) {
    if (debug) cout << "# ";
    rep(i, v.size()) cout << v[i] << (i != v.size() - 1 ? " " : "");
    cout << endl;
}
using P = pair<ll, ll>;
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

ll N, T, SIGMA2;
ll START_TIME;
constexpr ll TOTAL_END_TIME = 2500000;
constexpr ll INF = LONG_MAX;
ll PRED_HW;
ll ACTION_COUNT = 0;

// 実装的にグローバル変数として持たないと面倒
bool ALL_MODE;
ld MARGIN_1;
ld MARGIN_2;

// 値だけでなく、その不確かさも持つ
struct Info {
    ll value;
    ll sigma2;

    Info() {}
    Info(ll value_, ll sigma2_) : value(value_), sigma2(sigma2_) {}

    ll to_sigma() { return sqrt(sigma2); }

    Info operator+(const Info& another) const {
        return Info(value + another.value, sigma2 + another.sigma2);
    }
};

enum class Direction { UP, LEFT };

struct Action {
    ll number;
    bool rot;
    Direction direction;
    ll target;

    Action() {}
    Action(ll number_, bool rot_, Direction direction_, ll target_)
        : number(number_), rot(rot_), direction(direction_), target(target_) {}

    bool operator>(const Action& another) const { return number > another.number; }
    bool operator<(const Action& another) const { return number < another.number; }
};

namespace Utils {
ll calc_mean(vector<ll>& v) {
    assert(!v.empty());
    return SUM(v) / v.size();
}

/**
 *  N(a,s)からサンプリングされたvがある。この時、aはN(mean(v),s/len(v))からサンプリングされたと解釈できる
 */
ll calc_sigma2(vector<ll>& v) {
    assert(!v.empty());
    return SIGMA2 / v.size();
}

ll calc_margin(Info& a, Info& b) {
    ll a_sigma = a.to_sigma();
    ll b_sigma = b.to_sigma();
    return max(max(a_sigma, b_sigma) * MARGIN_1, (a_sigma + b_sigma) * MARGIN_2);
}

void print_action_vec(vector<Action> action_vec) {
    ACTION_COUNT++;
    ans_print(action_vec.size());
    for (Action& action : action_vec)
        ans_print(action.number, action.rot, (action.direction == Direction::LEFT ? "L" : "U"),
                  action.target);
}
};  // namespace Utils

struct Rect {
    ll number;
    Graph records;

    Rect() {}
    Rect(ll number_) : number(number_) { records.resize(2); }

    void add(ll h, ll w) {
        records[0].push_back(h);
        records[1].push_back(w);
    }

    tuple<Info, Info> calc_info() {
        return make_tuple(Info(Utils::calc_mean(records[0]), Utils::calc_sigma2(records[0])),
                          Info(Utils::calc_mean(records[1]), Utils::calc_sigma2(records[1])));
    }
};
vector<Rect> RECT_VEC;

namespace Simulator {
struct Pos {
    int x1, x2, y1, y2, t;
    bool r;
};

const Pos P0 = {-1, -1, -1, -1, -1, false};

struct Cmd {
    ll p;
    bool r;
    char d;
    int b;
};

struct Input {
    ll N, T;
    int sigma;
    std::vector<std::pair<int, int>> wh;
};

struct Output {
    std::vector<std::vector<Cmd>> out;
    std::vector<std::string> comments;
};

class Simulator {
   public:
    ll turn;
    std::vector<Pos> pos;
    int W, H, score_t, score;
    std::string comment;

    Simulator(const Input& input) : turn(0), W(0), H(0), score(0), comment("") {
        pos.assign(input.N, P0);
        score_t = 0;
        for (const auto& wh : input.wh) {
            score_t += wh.first + wh.second;
        }
        score = score_t;
    }

    void query(const Input& input, const std::vector<Cmd>& cmds) {
        pos.assign(input.N, P0);
        W = H = 0;
        int prev = -1;

        for (ll t = 0; t < cmds.size(); ++t) {
            const auto& c = cmds[t];
            if (prev >= static_cast<int>(c.p)) {
                throw std::runtime_error("p must be in ascending order.");
            }
            prev = static_cast<int>(c.p);

            if (pos[c.p].t >= 0) {
                throw std::runtime_error("Rectangle " + std::to_string(c.p) + " is already used");
            }

            if (c.b >= 0 && pos[c.b].t < 0) {
                throw std::runtime_error("Rectangle " + std::to_string(c.b) + " is not used");
            }

            auto [w, h] = input.wh[c.p];
            if (c.r) std::swap(w, h);

            int x1, x2, y1, y2;
            if (c.d == 'U') {
                x1 = (c.b < 0) ? 0 : pos[c.b].x2;
                x2 = x1 + w;
                y1 = 0;
                for (const auto& q : pos) {
                    if (q.t >= 0 && std::max(x1, q.x1) < std::min(x2, q.x2)) {
                        y1 = std::max(y1, q.y2);
                    }
                }
                y2 = y1 + h;
            } else if (c.d == 'L') {
                y1 = (c.b < 0) ? 0 : pos[c.b].y2;
                y2 = y1 + h;
                x1 = 0;
                for (const auto& q : pos) {
                    if (q.t >= 0 && std::max(y1, q.y1) < std::min(y2, q.y2)) {
                        x1 = std::max(x1, q.x2);
                    }
                }
                x2 = x1 + w;
            } else {
                throw std::runtime_error("Unknown direction: " + std::string(1, c.d));
            }

            pos[c.p] = {x1, x2, y1, y2, static_cast<int>(t), c.r};
            W = std::max(W, x2);
            H = std::max(H, y2);
        }

        score_t = W + H;

        for (ll i = 0; i < input.N; ++i) {
            if (pos[i].t < 0) {
                score_t += input.wh[i].first + input.wh[i].second;
            }
        }

        score = std::min(score, score_t);
        ++turn;
    }
};

Input create_input() {
    vector<pair<int, int>> wh;
    for (Rect rect : RECT_VEC) {
        auto [tate, yoko] = rect.calc_info();
        wh.push_back(make_pair(yoko.value, tate.value));
    }
    return Input{N, T, (int)sqrt(SIGMA2), wh};
};

vector<Cmd> action_to_cmd(vector<Action> action_vec) {
    vector<Cmd> ret;
    for (Action action : action_vec) {
        ll p = action.number;
        bool r = action.rot;
        char d = (action.direction == Direction::LEFT ? 'L' : 'U');
        int b = action.target;
        ret.push_back(Cmd{p, r, d, b});
    }
    return ret;
}

ll simulate(vector<Action> action_vec) {
    Input input = create_input();
    vector<Cmd> cmd_vec = action_to_cmd(action_vec);
    Simulator simulator(input);
    simulator.query(input, cmd_vec);
    return simulator.score;
}
};  // namespace Simulator

struct Predictor {
    ll count;
    Predictor(ll count_) : count(count_) {}

    void solve() {
        rep(i, count) {
            ll t = i % N;
            vector<Action> action_vec = {Action(t, 0, Direction::UP, -1)};
            Utils::print_action_vec(action_vec);
            ll h, w;
            cin >> w >> h;
            RECT_VEC[t].add(h, w);
        }
    }
};

struct FixedRect {
    Rect* rect;
    bool rot;

    FixedRect() {}
    FixedRect(Rect* rect_, bool rot_) : rect(rect_), rot(rot_) {}

    Info get_height() {
        if (rot)
            return get<1>(rect->calc_info());
        else
            return get<0>(rect->calc_info());
    }

    Info get_width() {
        if (rot)
            return get<0>(rect->calc_info());
        else
            return get<1>(rect->calc_info());
    }

    ll get_rect_number() { return rect->number; }
};

struct Planner {
    ll PLAN_END_TIME;
    ll LOWER_BOUND_SCORE;

    struct Node {
        FixedRect fixed_rect;
        Action action;
        shared_ptr<Node> left = nullptr;
        shared_ptr<Node> right = nullptr;

        Info width_info, height_info;
        ll target;
        bool is_clarified;

        Node() {}

        // 要素が1つ
        Node(FixedRect fixed_rect_, Action action_) : fixed_rect(fixed_rect_), action(action_) {
            width_info = fixed_rect.get_width();
            height_info = fixed_rect.get_height();
            target = fixed_rect.get_rect_number();
            is_clarified = true;
        }

        // 親の上に追加
        Node(FixedRect fixed_rect_, Action action_, shared_ptr<Node> left_)
            : fixed_rect(fixed_rect_), action(action_), left(left_) {
            height_info = left->height_info + fixed_rect.get_height();
            Info tmp = fixed_rect.get_width();
            if (tmp.value + MARGIN_1 * sqrt(tmp.sigma2) >
                left->width_info.value + MARGIN_1 * sqrt(left->width_info.sigma2)) {
                width_info = tmp;
                target = fixed_rect.get_rect_number();
            } else {
                width_info = left->width_info;
                target = left->target;
            }

            ll margin = Utils::calc_margin(tmp, left->width_info);
            if (left->is_clarified)
                is_clarified = abs(tmp.value - left->width_info.value) >= margin;
            else
                is_clarified = (tmp.value - left->width_info.value) >= margin;
        }

        // merge
        // 面倒なので条件を厳しく設定しておく
        Node(FixedRect fixed_rect_, Action action_, shared_ptr<Node> left_, shared_ptr<Node> right_)
            : fixed_rect(fixed_rect_), action(action_), left(left_), right(right_) {
            assert(right->is_clarified);

            Info child_height_info =
                (left->height_info.value > right->height_info.value ? left->height_info
                                                                    : right->height_info);
            height_info = child_height_info + fixed_rect.get_height();
            width_info = left->width_info + right->width_info;
            target = right->target;
            is_clarified = true;

            Info tmp = fixed_rect.get_width();
            ll margin = Utils::calc_margin(tmp, width_info);
            assert(width_info.value - tmp.value >= margin);
        }

        ll get_rect_number() { return fixed_rect.get_rect_number(); }
    };

    struct Stripe {
        shared_ptr<Node> node;

        Stripe() {}
        Stripe(shared_ptr<Node> node_) : node(node_) {}

        void add(FixedRect& fixed_rect, Action& action) {
            node = make_shared<Node>(fixed_rect, action, node);
        }

        // stripeの位置が途中の時
        bool inner_can_add(FixedRect& fixed_rect) {
            Info info = fixed_rect.get_width();
            ll margin = Utils::calc_margin(info, node->width_info);
            return info.value + margin < node->width_info.value;
        }

        void dump() const {
            vector<ll> v;
            function<void(shared_ptr<Node>)> f = [&](shared_ptr<Node> n) -> void {
                v.push_back(n->fixed_rect.rect->number);
                if (n->left != nullptr) f(n->left);
                if (n->right != nullptr) f(n->right);
            };
            f(node);
            vprint(v);
        }

        // stripeの幅を計算する
        Info get_width() { return node->width_info; }

        // stripeの高さを計算する
        Info get_height() { return node->height_info; }

        // 最大値が分散に負けていないか
        bool is_clarified() { return node->is_clarified; }
    };

    struct State {
        vector<Stripe> stripe_vec;
        ll eval_score;
        ll raw_score;

        bool can_add(ll idx, FixedRect fixed_rect) {
            ll n_stripes = stripe_vec.size();
            assert(idx <= n_stripes);
            if (idx == n_stripes) {
                if (idx == 0)
                    return true;
                else
                    return stripe_vec[idx - 1].is_clarified();
            } else if (idx == n_stripes - 1)
                return true;
            else
                return stripe_vec[idx].inner_can_add(fixed_rect);
        }

        void add(ll idx, FixedRect fixed_rect) {
            ll s = stripe_vec.size();
            assert(idx <= s);

            ll target;
            if (idx == 0)
                target = -1;
            else
                target = stripe_vec[idx - 1].node->target;
            Action action(fixed_rect.rect->number, fixed_rect.rot, Direction::UP, target);

            if (idx == s) {
                stripe_vec.push_back(Stripe(make_shared<Node>(fixed_rect, action)));
            } else {
                stripe_vec[idx].add(fixed_rect, action);
            }

            _set_score();
        }

        // idxとidx+1の上に置く
        bool can_merge(ll idx, FixedRect fixed_rect) {
            ll n_stripes = get_n_stripes();
            assert(idx + 1 < n_stripes);

            Stripe& left = stripe_vec[idx];
            Stripe& right = stripe_vec[idx + 1];
            if (!right.is_clarified()) return false;

            Info info = fixed_rect.get_width();
            Info merged_info = left.node->width_info + right.node->width_info;
            ll margin = Utils::calc_margin(info, merged_info);
            return merged_info.value >= info.value + margin;
        }

        void merge(ll idx, FixedRect fixed_rect) {
            ll target;
            if (idx == 0)
                target = -1;
            else
                target = stripe_vec[idx - 1].node->target;
            Action action(fixed_rect.rect->number, fixed_rect.rot, Direction::UP, target);

            stripe_vec[idx] = Stripe(make_shared<Node>(fixed_rect, action, stripe_vec[idx].node,
                                                       stripe_vec[idx + 1].node));
            stripe_vec.erase(stripe_vec.begin() + idx + 1);

            // update
            _set_score();
        }

        void _set_score() {
            ll sum_w = 0;
            ll sum_area = 0;
            ll max_h = 0;
            for (Stripe& stripe : stripe_vec) {
                ll w = stripe.get_width().value;
                sum_w += w;
                ll h = stripe.get_height().value;
                sum_area += h * w;
                max_h = max(max_h, stripe.get_height().value);
            }

            if (ALL_MODE)
                eval_score =
                    (max(sum_w - PRED_HW, 0) + max(max_h - PRED_HW, 0)) * 1000 + sum_area / 1000;
            else
                eval_score = (sum_w + max(max_h - PRED_HW, 0)) * 1000 + sum_area / 1000;
            raw_score = sum_w + max_h;
        }

        vector<Action> to_action_vec() {
            vector<Action> action_vec;

            function<void(shared_ptr<Node>)> dfs = [&](shared_ptr<Node> node) -> void {
                action_vec.push_back(node->action);
                if (node->left != nullptr) dfs(node->left);
                if (node->right != nullptr) dfs(node->right);
            };
            for (Stripe& stripe : stripe_vec) {
                dfs(stripe.node);
            }
            sort(all(action_vec));

            return action_vec;
        }

        void print_action_vec() {
            vector<Action> action_vec = to_action_vec();
            Utils::print_action_vec(action_vec);
        }

        vector<vector<FixedRect>> to_graph() {
            vector<vector<FixedRect>> ret;
            for (Stripe& stripe : stripe_vec) {
                vector<FixedRect> v;
                auto node = stripe.node;
                while (true) {
                    v.push_back(node->fixed_rect);
                    assert(node->right == nullptr);
                    node = node->left;
                    if (node == nullptr) break;
                }
                // reverse(all(v));
                ret.push_back(v);
            }
            reverse(all(ret));
            return ret;
        }

        void dump() {
            for (Stripe& s : stripe_vec) s.dump();
            // print(action_vec.size());
            // for (Action& action : action_vec) print(action.number, action.rot, "U",
            // action.target); print();
        }

        // accessor
        // =====================================================================================
        ll get_n_stripes() { return stripe_vec.size(); }

        Info get_width(ll idx) {
            assert(idx < get_n_stripes());
            return stripe_vec[idx].get_width();
        }

        Info get_height(ll idx) {
            assert(idx < get_n_stripes());
            return stripe_vec[idx].get_height();
        }

        Info get_max_height() {
            Info ret(0, 0);
            for (Stripe& stripe : stripe_vec) {
                Info info = stripe.get_height();
                if (ret.value < info.value) ret = info;
            }
            return ret;
        }

        bool operator>(const State& another) const { return eval_score > another.eval_score; }
        bool operator<(const State& another) const { return eval_score < another.eval_score; }
    };
    State best_state;

    Planner(ll PLAN_END_TIME_, ll LOWER_BOUND_SCORE_)
        : PLAN_END_TIME(PLAN_END_TIME_), LOWER_BOUND_SCORE(LOWER_BOUND_SCORE_) {}

    void solve() {
        vector<IQ<State>> pqs(N + 1);
        pqs[0].push(State());

        ll beam_count = 0;
        best_state.raw_score = INF;

        while (clock() - START_TIME < PLAN_END_TIME) {
            rep(t, N) {
                if (clock() - START_TIME > PLAN_END_TIME) break;
                rep(_, 10) {
                    if (clock() - START_TIME > PLAN_END_TIME) break;
                    if (pqs[t].empty()) break;

                    beam_count++;
                    State state = pqs[t].top();
                    pqs[t].pop();

                    if (t != N - 1) {
                        if (state.raw_score >= min(best_state.raw_score, LOWER_BOUND_SCORE))
                            continue;
                    } else {
                        if (state.raw_score >= best_state.raw_score) continue;
                    }

                    ll rect_number = (ALL_MODE ? t : N - t - 1);
                    rep(r, 2) {
                        FixedRect fixed_rect(&RECT_VEC[rect_number], r);
                        ll n_stripes = state.get_n_stripes();

                        ll min_range = (ALL_MODE ? 0 : max(n_stripes - 1, 0));
                        ll max_range = n_stripes + 1;
                        frep(i, min_range, max_range) {
                            if (ALL_MODE && !state.can_add(i, fixed_rect)) continue;

                            if (ALL_MODE && i == n_stripes &&
                                fixed_rect.get_height().value > fixed_rect.get_width().value) {
                                FixedRect rev(&RECT_VEC[t], 1 - r);
                                if (state.can_add(i, rev)) continue;
                            }

                            State next_state = state;
                            next_state.add(i, fixed_rect);

                            if (t != N - 1) {
                                if (next_state.raw_score <
                                    min(best_state.raw_score, LOWER_BOUND_SCORE))
                                    pqs[t + 1].push(next_state);
                            } else {
                                if (next_state.raw_score < best_state.raw_score)
                                    swap(best_state, next_state);
                            }
                        }

                        if (ALL_MODE) {
                            rep(i, n_stripes - 1) {
                                if (!state.can_merge(i, fixed_rect)) continue;
                                if (state.can_add(i, fixed_rect) ||
                                    state.can_add(i + 1, fixed_rect))
                                    continue;

                                State next_state = state;
                                next_state.merge(i, fixed_rect);

                                if (t != N - 1) {
                                    if (next_state.raw_score <
                                        min(best_state.raw_score, LOWER_BOUND_SCORE))
                                        pqs[t + 1].push(next_state);
                                } else {
                                    if (next_state.raw_score < best_state.raw_score)
                                        swap(best_state, next_state);
                                }
                            }
                        }
                    }
                }
            }
        }
        print(beam_count);

        if (best_state.raw_score != INF) best_state.dump();
    }
};

struct RandomSolver {
    ll RANDOM_END_TIME;

    struct Node {
        FixedRect fixed_rect;
        Action action;
        shared_ptr<Node> parent = nullptr;

        Info width_info, height_info;
        ll target;
        bool is_parent_brother;

        Node() {}

        // 要素が1つ
        Node(FixedRect fixed_rect_, Action action_) : fixed_rect(fixed_rect_), action(action_) {
            width_info = fixed_rect.get_width();
            height_info = fixed_rect.get_height();
            target = -1;
            is_parent_brother = false;
        }

        // 親の上に追加
        Node(FixedRect fixed_rect_, Action action_, shared_ptr<Node> parent_)
            : fixed_rect(fixed_rect_), action(action_), parent(parent_) {
            height_info = parent->height_info + fixed_rect.get_height();
            Info tmp = fixed_rect.get_width();
            if (parent->width_info.value < tmp.value)
                width_info = tmp;
            else
                width_info = parent->width_info;
            target = parent->get_rect_number();
            is_parent_brother = false;
        }

        // 兄弟
        Node(FixedRect fixed_rect_, Action action_, shared_ptr<Node> parent_, bool brother)
            : fixed_rect(fixed_rect_), action(action_), parent(parent_) {
            assert(brother);

            Info parent_width_info = parent->width_info;
            Info parent_height_info = parent->height_info;
            Info my_width_info = parent->fixed_rect.get_width() + fixed_rect.get_width();

            if (parent->parent != nullptr) {
                // 親に親がいる
                Info parent_parent_width_info = parent->parent->width_info;
                if (parent_parent_width_info.value > my_width_info.value)
                    width_info = parent_parent_width_info;
                else
                    width_info = my_width_info;

                if (parent->fixed_rect.get_height().value < fixed_rect.get_height().value)
                    height_info = parent->parent->height_info + fixed_rect.get_height();
            } else {
                // 親に親がいない
                width_info = my_width_info;
                if (height_info.value < fixed_rect.get_height().value)
                    height_info = fixed_rect.get_height();
            }
            target = parent->target;
            is_parent_brother = true;
        }

        ll get_rect_number() { return fixed_rect.get_rect_number(); }
    };

    struct Stripe {
        shared_ptr<Node> node;

        Stripe() {}
        Stripe(shared_ptr<Node> node_) : node(node_) {}

        void add(FixedRect& fixed_rect, Action& action, bool brother) {
            if (!brother)
                node = make_shared<Node>(fixed_rect, action, node);
            else
                node = make_shared<Node>(fixed_rect, action, node, brother);
        }

        void dump() const {
            vector<ll> v;
            function<void(shared_ptr<Node>)> f = [&](shared_ptr<Node> n) -> void {
                v.push_back(n->fixed_rect.rect->number);
                if (n->parent != nullptr) f(n->parent);
            };
            f(node);
            vprint(v);
        }

        // stripeの幅を計算する
        Info get_width() { return node->width_info; }

        // stripeの高さを計算する
        Info get_height() { return node->height_info; }

        // 兄弟を作れるか
        bool can_create_brother() { return !node->is_parent_brother; }
    };

    struct State {
        vector<Stripe> stripe_vec;
        ll eval_score;
        ll raw_score;

        void add(ll idx, FixedRect fixed_rect, bool brother) {
            ll s = stripe_vec.size();
            assert(idx <= s);

            ll target;
            if (brother)
                target = stripe_vec[idx].node->target;
            else {
                if (idx != s)
                    target = stripe_vec[idx].node->get_rect_number();
                else
                    target = -1;
            }
            Action action(fixed_rect.rect->number, fixed_rect.rot, Direction::LEFT, target);

            if (idx == s) {
                assert(!brother);
                stripe_vec.push_back(Stripe(make_shared<Node>(fixed_rect, action)));
            } else {
                stripe_vec[idx].add(fixed_rect, action, brother);
            }

            _set_score();
        }

        void _set_score() {
            ll sum_w = 0;
            ll sum_area = 0;
            ll max_h = 0;
            for (Stripe& stripe : stripe_vec) {
                ll w = stripe.get_width().value;
                sum_w += w;
                ll h = stripe.get_height().value;
                sum_area += h * w;
                max_h = max(max_h, stripe.get_height().value);
            }

            eval_score = (sum_w + max(max_h - PRED_HW, 0)) * 1000 + sum_area / 1000;
        }

        void finish_callback() {
            vector<Action> action_vec = to_action_vec();
            raw_score = Simulator::simulate(action_vec);
        }

        vector<Action> to_action_vec() {
            vector<Action> action_vec;

            function<void(shared_ptr<Node>)> dfs = [&](shared_ptr<Node> node) -> void {
                action_vec.push_back(node->action);
                if (node->parent != nullptr) dfs(node->parent);
            };
            for (Stripe& stripe : stripe_vec) {
                dfs(stripe.node);
            }
            sort(all(action_vec));

            return action_vec;
        }

        void print_action_vec() {
            vector<Action> action_vec = to_action_vec();
            Utils::print_action_vec(action_vec);
        }

        void dump() {
            for (Stripe& s : stripe_vec) s.dump();
            // print(action_vec.size());
            // for (Action& action : action_vec) print(action.number, action.rot, "U",
            // action.target); print();
        }

        // accessor
        // =====================================================================================
        ll get_n_stripes() { return stripe_vec.size(); }

        Info get_width(ll idx) {
            assert(idx < get_n_stripes());
            return stripe_vec[idx].get_width();
        }

        Info get_height(ll idx) {
            assert(idx < get_n_stripes());
            return stripe_vec[idx].get_height();
        }

        Info get_max_height() {
            Info ret(0, 0);
            for (Stripe& stripe : stripe_vec) {
                Info info = stripe.get_height();
                if (ret.value < info.value) ret = info;
            }
            return ret;
        }

        bool operator>(const State& another) const { return eval_score > another.eval_score; }
        bool operator<(const State& another) const { return eval_score < another.eval_score; }
    };
    State best_state;

    RandomSolver() {}
    RandomSolver(ll RANDOM_END_TIME_) : RANDOM_END_TIME(RANDOM_END_TIME_) {}

    void solve() {
        vector<IQ<State>> pqs(N + 1);
        pqs[0].push(State());

        ll beam_count = 0;
        best_state.raw_score = INF;

        while (clock() - START_TIME < RANDOM_END_TIME) {
            rep(t, N) {
                if (clock() - START_TIME > RANDOM_END_TIME) break;
                rep(_, 10) {
                    if (clock() - START_TIME > RANDOM_END_TIME) break;
                    if (pqs[t].empty()) break;

                    beam_count++;
                    State state = pqs[t].top();
                    pqs[t].pop();

                    ll rect_number = t;
                    rep(r, 2) {
                        FixedRect fixed_rect(&RECT_VEC[rect_number], r);
                        ll n_stripes = state.get_n_stripes();

                        auto operate = [&](State& next_state) -> void {
                            if (t != N - 1)
                                pqs[t + 1].push(next_state);
                            else {
                                next_state.finish_callback();
                                if (next_state.raw_score < best_state.raw_score)
                                    swap(best_state, next_state);
                            }
                        };

                        // 上に置く
                        if (n_stripes != 0) {
                            State next_state = state;
                            next_state.add(n_stripes - 1, fixed_rect, false);
                            operate(next_state);
                        }

                        // 列を追加する
                        if (true) {
                            State next_state = state;
                            next_state.add(n_stripes, fixed_rect, false);
                            operate(next_state);
                        }

                        // 兄弟
                        if (false && n_stripes != 0 &&
                            state.stripe_vec[n_stripes - 1].can_create_brother()) {
                            State next_state = state;
                            next_state.add(n_stripes - 1, fixed_rect, true);
                            operate(next_state);
                        }
                    }
                }
            }
        }
    }
};

void input() {
    ll s;
    cin >> N >> T >> s;
    SIGMA2 = s * s;
    PRED_HW = 0;

    rep(i, N) {
        ll h, w;
        cin >> w >> h;
        RECT_VEC.push_back(Rect(i));
        RECT_VEC[i].add(h, w);
        PRED_HW += h * w;
    }
    PRED_HW = sqrt(PRED_HW * 1.1);
}

int main() {
    START_TIME = clock();
    input();
    Predictor predictor(T - 4);
    predictor.solve();

    auto calc_end_time = [&](ll t) -> ll { return min(clock() + t, TOTAL_END_TIME); };

    // first
    ALL_MODE = true;
    MARGIN_1 = 3.0;
    MARGIN_2 = 2.0;
    Planner first_planner(calc_end_time(3e5), LONG_MAX);
    first_planner.solve();
    ll first_best_score = first_planner.best_state.raw_score;
    first_planner.best_state.print_action_vec();

    // second
    ALL_MODE = true;
    MARGIN_1 = 2.5;
    MARGIN_2 = 1.5;
    Planner second_planner(calc_end_time(4e5), first_best_score);
    second_planner.solve();
    ll second_best_score = second_planner.best_state.raw_score;
    second_planner.best_state.print_action_vec();

    // third
    ALL_MODE = true;
    MARGIN_1 = 2.0;
    MARGIN_2 = 1.25;
    Planner third_planner(calc_end_time(4e5), min(first_best_score, second_best_score));
    third_planner.solve();
    ll third_best_score = second_planner.best_state.raw_score;
    third_planner.best_state.print_action_vec();

    // fourth limited
    RandomSolver random_solver(TOTAL_END_TIME);
    random_solver.solve();
    print("pred h", PRED_HW);
    print("pred score", random_solver.best_state.raw_score);
    random_solver.best_state.dump();
    random_solver.best_state.print_action_vec();
}
