#include <bits/stdc++.h>
using namespace std;

struct Treap
{
  struct Node
  {
    Node *l = nullptr;
    Node *r = nullptr;

    int x, y;
    int value, sum;

    Node(int v)
    {
      x = 1, y = (rand() << 16) | rand();
      value = v;
      sum = (v == 0);
    }
  }*root = nullptr;

  int get_size(Node *n)
  {
    if (n == nullptr) return 0;
    return n->x;
  }

  int get_sum(Node *n)
  {
    if (n == nullptr) return 0;
    return n->sum;
  }

  void update(Node *n)
  {
    if (n == nullptr) return;
    n->x = get_size(n->l) + 1 + get_size(n->r);
    n->sum = get_sum(n->l) + (n->value == 0) + get_sum(n->r);
  }

  pair<Node*, Node*> split(Node *n, int x, int left = 0)
  {
    if (n == nullptr) return {
      nullptr, nullptr
    };

    int pos = left + get_size(n->l) + 1;
    if (pos <= x)
    {
      auto p = split(n->r, x, pos);
      n->r = p.first;
      update(n);
      return {
        n, p.second
      };

    }
    else
    {
      auto p = split(n->l, x, left);
      n->l = p.second;
      update(n);
      return {
        p.first, n
      };

    }
  }

  Node* merge(Node *a, Node *b)
  {
    if (a == nullptr) return b;
    if (b == nullptr) return a;
    if (a->y < b->y)
    {
      b->l = merge(a, b->l);
      update(b);
      return b;
    }
    else
    {
      a->r = merge(a->r, b);
      update(a);
      return a;
    }
  }

  void add_node()
  {
    root = merge(root, new Node(0));
  }

  int findLeft(Node *n, int left = 0)
  {
    if (get_sum(n->l)) return findLeft(n->l, left);
    if (n->value == 0) return left + get_size(n->l) + 1;
    else return findLeft(n->r, left + get_size(n->l) + 1);
  }

  void modify(int v, int i)
  {
    auto p1 = split(root, i - 1);
    int pos = findLeft(p1.second) + i - 1;
    root = merge(p1.first, p1.second);
    auto p2 = split(root, pos);
    auto p3 = split(p2.first, pos - 1);
    root = merge(p3.first, p2.second);
    auto p4 = split(root, i - 1);
    root = merge(p4.first, merge(new Node(v), p4.second));
  }

  void print(Node *n, vector<int> &a)
  {
    if (n == nullptr) return;
    print(n->l, a);
    a.push_back(n->value);
    print(n->r, a);
  }
};

void solution()
{
  int n, m; scanf("%d %d", &n, &m);
  Treap t;
  int N = 3e5 + 1;
  for (int i = 0; i < N; i++)
  {
    t.add_node();
  }

  for (int i = 0; i < n; i++)
  {
    int x = i + 1;
    int p; scanf("%d", &p);
    t.modify(x, p);
  }

  vector<int> ans;
  t.print(t.root, ans);
  while (ans.back() == 0)
  {
    ans.pop_back();
  }

  printf("%d\n", (int) ans.size());
  for (auto i: ans)
  {
    printf("%d ", i);
  }

  puts("");
}

int main()
{
#ifdef ONLINE_JUDGE
  freopen("key.in", "r", stdin);
  freopen("key.out", "w", stdout);
#endif

  int t = 1;
  while (t--)
  {
    solution();
  }

  return 0;
}