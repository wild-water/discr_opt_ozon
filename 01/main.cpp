#include <bits/stdc++.h>

using namespace std;


struct Item {
    double weight, value;
};

double best_value = -10000;


pair<double, double> get_lp_value(double k_weight, int cur_index, vector<Item> &items) {
    double lp_res = 0, int_res = 0;
    for (int i = cur_index; i < items.size(); ++i) {
        if (k_weight <= 0) {
            return {lp_res, int_res};
        }
        double c = min(k_weight / (items[i].weight+1e-8), 1.0);
        k_weight -= c * items[i].weight;
        lp_res += c * items[i].value;
        if (c == 1.0) {
            int_res += items[i].value;
        }

    }
    return {lp_res, int_res};
}


void search(double cur_value, double cur_weight, int cur_index,
            double k_weight, vector<Item> &items) {

    if (cur_index == items.size()) {
        best_value = max(best_value, cur_value);
        return;
    }

    auto [lp_res, int_res] = get_lp_value(k_weight - cur_weight,
                            cur_index, items);

    best_value = max(cur_value + int_res, best_value);
    if (cur_value + lp_res <= best_value) {
        return;
    }

    if (cur_weight + items[cur_index].weight <= k_weight) {
        search(cur_value + items[cur_index].value, cur_weight + items[cur_index].weight,
               cur_index + 1, k_weight, items);
    }
    search(cur_value, cur_weight, cur_index + 1, k_weight, items);
}


void solve() {
    double k_weight;
    int n_items;

    cin >> k_weight >> n_items;
    vector<Item> items(n_items);
    for (int i = 0; i < n_items; ++i) {
        cin >> items[i].weight >> items[i].value;
    }

    sort(items.begin(), items.end(), [](Item x, Item y) {
        return x.value * y.weight > y.value * x.weight;
    });
    search(0, 0, 0, k_weight, items);
    cout << (int)best_value << "\n";
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
