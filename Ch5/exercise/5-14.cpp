#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <map>

using namespace std;

struct Order
{
    int size, price;
    bool isBuy;
};

map<int, Order> orders; // 所有的 order, 如果 cancel 或 匹配从这里删除

struct OrderInfo
{
    int id;
    bool operator<(const OrderInfo &rhs) const // 默认认为 a < b 时 b 优先, BUY 最高买价优先
    {
        Order a = orders[id];
        Order b = orders[rhs.id];
        if (a.price != b.price)
            return a.price < b.price;
        return id > rhs.id;
    }
};

struct SellComparator // SELL 低价优先
{
    bool operator()(const OrderInfo &a, const OrderInfo &b)
    {
        Order _a = orders[a.id];
        Order _b = orders[b.id];
        if (_a.price != _b.price)
            return _a.price > _b.price;
        return a.id > b.id;
    }
};

priority_queue<OrderInfo> bids;                                    // BUY 高价优先
priority_queue<OrderInfo, vector<OrderInfo>, SellComparator> asks; // SELL 低价优先
map<int, int> bid_agg, ask_agg;                                    // price, size
int T;

void test_display_all()
{
    cout << "======= Bids ==============" << endl;
    while (!bids.empty())
    {
        int id = bids.top().id;
        bids.pop();
        Order info = orders[id];

        cout << "Id: " << id << ", Size: " << info.size
             << ", Price: " << info.price << endl;
    }
    cout << "======= Asks ==============" << endl;
    while (!asks.empty())
    {
        int id = asks.top().id;
        asks.pop();
        Order info = orders[id];
        cout << "Id: " << id << ", Size: " << info.size
             << ", Price: " << info.price << endl;
    }
    cout << "===========================" << endl;
}

void initiate()
{
    orders.clear();
    bid_agg.clear();
    ask_agg.clear();
    while (!bids.empty())
    {
        bids.pop();
    }
    while (!asks.empty())
    {
        asks.pop();
    }
}

void solve(bool isBuy)
{
    while (!bids.empty() && !asks.empty())
    {
        OrderInfo bid = bids.top();
        OrderInfo ask = asks.top();

        if (orders[bid.id].size == 0) // 已被删
        {
            bids.pop();
            continue;
        }
        if (orders[ask.id].size == 0)
        {
            asks.pop();
            continue;
        }
        Order &bid_item = orders[bid.id];
        Order &ask_item = orders[ask.id];

        if (bid_item.price >= ask_item.price) // 存在成交
        {
            int trade_size = min(bid_item.size, ask_item.size);        // 成交数目
            int trade_price = isBuy ? ask_item.price : bid_item.price; // 成交价格
            // 打印成交数目和价格
            cout << "TRADE " << trade_size << " " << trade_price << endl;

            // bid 有剩余
            bid_item.size -= trade_size;
            bid_agg[bid_item.price] -= trade_size;
            if (bid_item.size == 0)
            {
                bids.pop();
            }

            // ask 有剩余
            ask_item.size -= trade_size;
            ask_agg[ask_item.price] -= trade_size;
            if (ask_item.size == 0)
            {
                asks.pop();
            }
        }
        else
        {
            break;
        }
    }
}

void print_quote()
{
    int bid_size = 0, bid_price = 0, ask_size = 0, ask_price = 99999;

    while (!bids.empty())
    {
        OrderInfo order = bids.top();
        if (orders[order.id].size == 0)
        {
            bids.pop();
            continue;
        }
        bid_price = orders[order.id].price;
        bid_size = bid_agg[bid_price];
        break;
    }
    while (!asks.empty())
    {
        OrderInfo order = asks.top();
        if (orders[order.id].size == 0)
        {
            asks.pop();
            continue;
        }
        ask_price = orders[order.id].price;
        ask_size = ask_agg[ask_price];

        break;
    }
    cout << "QUOTE " << bid_size << " " << bid_price << " - "
         << ask_size << " " << ask_price << endl;
}

void cancel(int q)
{
    if (orders[q].size == 0) // 已经被删了
    {
        return;
    }
    if (orders[q].isBuy)
    {
        bid_agg[orders[q].price] -= orders[q].size;
    }
    else
    {
        ask_agg[orders[q].price] -= orders[q].size;
    }
    orders[q].size = 0;
}

int main()
{
    bool isFirst = 1;
    while (cin >> T)
    {
        getchar();
        initiate();

        if (!isFirst)
        {
            cout << endl;
        }
        isFirst = 0;

        for (int i = 1; i <= T; i++)
        {
            string s;
            int q, p;
            cin >> s;
            if (s == "CANCEL")
            {
                cin >> q;
                cancel(q);
            }
            else
            {
                cin >> q >> p;
                if (s == "BUY")
                {
                    orders[i] = {q, p, true};
                    bids.push({i});
                    bid_agg[p] += q;
                    // 尝试匹配
                    solve(true);
                }
                else // SELL
                {
                    orders[i] = {q, p, false};
                    asks.push({i});
                    ask_agg[p] += q;
                    solve(false);
                }
            }
            print_quote();
        }
        // test
        // test_display_all();
    }

    return 0;
}