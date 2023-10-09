from dataclasses import dataclass
from scipy.stats import norm

# 入力
L : int = -1 
N : int = -1 
S : int = -1 


# 出口についてのdataclass
# exitという名前にしたいが、exit()という関数が存在するので、以下出口をHoleという名前で統一します
@dataclass
class Hole : 
    hole_number : int
    y : int 
    x : int 
    
    # 出力用のベクトルを取得する
    # measure_costが小さくなるように値を変換している
    def get_vector_for_output(self) :   # -> tuple[int, int]    
        # 出口から(0, 0)へのベクトル
        dy, dx = -self.y, -self.x 
        
        # 出力する|y|と|x|を小さくする
        output_y = dy if abs(dy) < abs(dy + L) else dy + L
        output_x = dx if abs(dx) < abs(dx + L) else dx + L
        
        return output_y, output_x


hole_list : list = []   # 全ての出口を管理するlist
# hole_list : list[Hole] = []   # AtCoderのPythonのバージョンが3.9未満なので、この型アノテーションがエラーになる（#^ω^）


# 平均がmu、標準偏差がSの時に観測値がxとなる確率
# 観測値は[0, 1000]でclipされているため、xが0の時は[-inf, 0]、1000の時は[1000, inf]の確率を返す
# norm.cdf(x)はx以下となる確率を変えす
# pdfは確率密度関数のことです
def get_pdf(x : int, mu : int) -> float : 
    assert(0 <= x <= 1000)
    assert(0 <= mu <= 1000)
    if x == 0 : 
        return norm.cdf(0, loc=mu, scale=S)
    elif x == 1000 : 
        return 1.0 - norm.cdf(1000, loc=mu, scale=S)
    else : 
        return norm.pdf(x, loc=mu, scale=S)


class Solver : 
    def __init__(self) -> None :
        self.ans_list : list[int] = [None for _ in range(N)]   # 各entrance_numberに対応するhole_number 
        self.measure_count = 0   # 計測した回数
    
    
    # 盤面の温度を出力する
    def output_temp(self) : 
        self.target_temp = min(4 * S, 1000)   # 位置特定用位置(0, 0)のセルの温度、σに対してある程度小さくても意外と行けます
        
        # (0, 0)のみをself.target_temp, 他を0として出力
        for y in range(L) : 
            for x in range(L) : 
                if y == 0 and x == 0 : 
                    print(self.target_temp, end=" ")
                else : 
                    print(0, end=" ")
            print()
        
        
    # 実際に問題を解いていく
    def solve(self) : 
        # 出口の順番を決める
        # 位置特定用セル(0, 0)から近い順にする
        hole_number_cost_arr : list[list[int]] = []
        for hole_number in range(N) : 
            y, x = hole_list[hole_number].get_vector_for_output() 
            hole_number_cost_arr.append([hole_number, abs(y) + abs(x)])
        sorted_hole_number_cost_arr = sorted(hole_number_cost_arr, reverse=False, key=lambda x: x[1])
        
        # 入口毎に、対応する出口を探す
        for number_cost in sorted_hole_number_cost_arr : 
            hole_number = number_cost[0]
            
            # 詳細はself.solve_one()へ
            ans_entrance_number = self.solve_one(hole_number) 
            
            # 制限回数を超えた場合、Noneが返ってくる
            if ans_entrance_number is None : 
                print(f'# FAILURE 制限回数を超えています, hole_number={hole_number}')
            else : 
                print(f'# SUCCESS entrance_number={ans_entrance_number}, hole_number={hole_number}')
                self.ans_list[ans_entrance_number] = hole_number
        
    
    # hole_numberに対応するentrance_numberを見つける
    def solve_one(self, hole_number : int) -> int : 
        # 評価値を格納するlistを用意する
        # i番目の入口に対する評価値がestimation_list[i]
        # 既に確定している入口の評価値は0とする
        estimation_list : list[float] = [1.0 for _ in range(N)] 
        for entrance_number in range(N) : 
            if self.ans_list[entrance_number] is not None : 
                estimation_list[entrance_number] = 0
                
        # 実際に計測を行っていく
        # 計測は今の評価値が最も高いhole_number順に行う
        while True : 
            # 計測回数が上限に達しているなら強制終了
            if self.measure_count >= 1e4 : 
                return None 
            
            # 今最も評価値が高いentrance_number
            target_entrance_number = self.argmax_for_hole_number(estimation_list)
            
            # target_entrance_numberが正しいならば計測値はself.target_temp、間違っているならば0に近い値が返ってくるはず
            measured_temp = self.measure(entrance_number=target_entrance_number, 
                                         hole_number=hole_number)
            
            # 今の計測に対する評価値を計算
            # 評価値は「平均がself.target_tempの下でmeasured_tempとなる確率」÷「平均が0の下でmeasured_tempとなる確率」
            estimation = get_pdf(measured_temp, mu=self.target_temp) / get_pdf(measured_temp, mu=0)
            
            # estimation_listを更新
            estimation_list[target_entrance_number] *= estimation 
            
            # estimation_listの和が1.0になるように正規化
            estimation_sum = sum(estimation_list)
            for entrance_number in range(N) : 
                estimation_list[entrance_number] /= estimation_sum 
                
            # 最大評価値が閾値を上回っているならそれが答え、そうでないなら計測を継続
            best_entrance_number = self.argmax_for_hole_number(estimation_list)
            if estimation_list[best_entrance_number] > 0.9999 : 
                return best_entrance_number 
            else : 
                continue 
        
    
    # 計測を行う
    # 返り値は計測温度
    def measure(self, entrance_number : int, hole_number : int) -> int :         
        # 出力
        output_y, output_x = hole_list[hole_number].get_vector_for_output()
        print(entrance_number, output_y, output_x)
        
        # 計測回数更新
        self.measure_count = self.measure_count + 1 
        
        # 結果受け取り
        measured_temperature = int(input())
        
        return measured_temperature 
    
    
    # 解答を出力する
    def output_ans(self) : 
        print(-1, -1, -1)
        for ans in self.ans_list : 
            # 答えが見つかっていない場合は適当に0を出力する
            if ans is None : 
                print(0) 
            else : 
                print(ans)
    
    
    # 最大評価値の出口を求める
    # 評価値が同じときは、測定コストが小さいほうを選ぶ
    def argmax_for_hole_number(self, estimation_list : list) -> int : 
        best_estimation = -1e10 
        best_hole_number = None 
        EPSILON = 1e-3   # floatなので==は使わない
        for hole_number, estimation in enumerate(estimation_list) : 
            if abs(estimation - best_estimation) < EPSILON and best_hole_number is not None : 
                # 今評価が高い方の測定コスト
                y0, x0 = hole_list[best_hole_number].get_vector_for_output()
                measure_cost_0 = abs(y0) + abs(x0)
                # 今見ている方の測定コスト
                y1, x1 = hole_list[hole_number].get_vector_for_output()
                measure_cost_1 = abs(y1) + abs(x1)
                
                if measure_cost_1 < measure_cost_0 : 
                    best_estimation = estimation
                    best_hole_number = hole_number
                    
            elif estimation > best_estimation or best_hole_number is None : 
                best_estimation = estimation
                best_hole_number = hole_number 
        assert best_hole_number is not None 
        return best_hole_number      
        

if __name__ == "__main__" : 
    # 入力
    L, N, S = map(int, input().split(" ")) 
    for hole_number in range(N) : 
        y, x = map(int, input().split(" "))
        hole_list.append(Hole(hole_number=hole_number, 
                              y=y,
                              x=x))
            
    # solve
    solver = Solver()
    solver.output_temp() 
    solver.solve() 
    
    # 答えを出力
    solver.output_ans() 
    
    # 終了
    
