#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

using namespace std;

struct Order {
  int size, price;
  bool isBuy;
} orders[11111]; // 所有的 order, 如果 cancel 或 匹配从这里删除

struct Level {
  queue<int> orders; // 这个价格下时间优先订单
  int agg_size;      // 这个价格下的总挂单量 aggregated size
};

map<int, Level> bids, asks; // <price, Level>

int n;

void initiate() {
  bids.clear();
  asks.clear();
}

void print_best_quote(map<int, Level> &side, bool isBuy, int size, int price) {
  while (!side.empty()) {
    map<int, Level>::iterator best = isBuy ? --side.end() : side.begin();
    if (best->second.agg_size > 0) {
      price = best->first;
      size = best->second.agg_size;
      break;
    } else {
      side.erase(best);
    }
  }
  cout << size << " " << price;
}

void print_quote() {
  int bid_size = 0, bid_price = 0, ask_size = 0, ask_price = 99999;

  cout << "QUOTE ";
  print_best_quote(bids, true, 0, 0);
  cout << " - ";
  print_best_quote(asks, false, 0, 99999);
  cout << endl;
}

void cancel(int q) {
  if (orders[q].size == 0) // 已经被删了
  {
    return;
  }
  map<int, Level> &side = orders[q].isBuy ? bids : asks;
  side[orders[q].price].agg_size -= orders[q].size;
  orders[q].size = 0;
}

int try_trade(int new_id, int oppo_id) {
  bool isBuy = orders[new_id].isBuy;
  int new_price = orders[new_id].price;
  int oppo_price = orders[oppo_id].price;
  int trade_size = 0;

  if ((isBuy && new_price >= oppo_price) ||
      (!isBuy && new_price <= oppo_price)) {
    trade_size = min(orders[new_id].size, orders[oppo_id].size);
  }
  if (trade_size > 0) {
    orders[new_id].size -= trade_size;
    orders[oppo_id].size -= trade_size;
    cout << "TRADE " << trade_size << " " << oppo_price << endl;
  }
  return trade_size;
}

void try_match(int id) {
  map<int, Level> &oppo = orders[id].isBuy ? asks : bids;
  while (oppo.size() != 0) {
    map<int, Level>::iterator best =
        orders[id].isBuy ? oppo.begin() : --oppo.end();
    while (best->second.orders.size() > 0 && orders[id].size > 0) {
      int oppo_id = best->second.orders.front();
      if (orders[oppo_id].size == 0) {
        best->second.orders.pop();
        continue;
      }
      int trade_size = try_trade(id, oppo_id);
      if (trade_size > 0) {
        best->second.agg_size -= trade_size;
        if (orders[oppo_id].size == 0) {
          best->second.orders.pop();
        }
      } else {
        break; // 价格不匹配
      }
    }
    if (orders[id].size == 0) {
      break;
    }
    if (best->second.agg_size == 0) {
      oppo.erase(best);
    } else {
      break;
    }
  }
}

int main() {
  bool isFirst = 1;
  while (cin >> n) {
    getchar();
    initiate();

    if (!isFirst) {
      cout << endl;
    }
    isFirst = 0;

    for (int i = 1; i <= n; i++) {
      string s;
      int q, p;
      cin >> s;
      if (s == "CANCEL") {
        cin >> q;
        cancel(q);
      } else {
        cin >> q >> p;
        bool isBuy = s == "BUY";
        orders[i] = {q, p, isBuy};
        try_match(i);
        if (orders[i].size > 0) {
          map<int, Level> &side = isBuy ? bids : asks;
          side[p].agg_size += orders[i].size;
          side[p].orders.push(i);
        }
      }
      print_quote();
    }
  }

  return 0;
}