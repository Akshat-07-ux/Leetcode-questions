class Node:
    __slots__ = ('remain', 'prod')
    def __init__(self, k):
        self.remain = [0] * k
        self.prod = 1

class SegmentTree:
    def __init__(self, nums: list[int], k: int):
        self.n = len(nums)
        self.k = k
        self.tree = [Node(k) for _ in range(4 * self.n)]
        self.build(nums, 0, 0, self.n - 1)

    def merge(self, left_node: Node, right_node: Node) -> Node:
        res = Node(self.k)
        res.prod = (left_node.prod * right_node.prod) % self.k

        for i in range(self.k):
            res.remain[i] = left_node.remain[i]

        for i in range(self.k):
            new_rem = (i * left_node.prod) % self.k
            res.remain[new_rem] += right_node.remain[i]

        return res

    def build(self, nums: list[int], cur: int, left: int, right: int):
        if left == right:
            self.tree[cur].remain[nums[left]] = 1
            self.tree[cur].prod = nums[left]

            return

        mid = (left + right) // 2
        self.build(nums, 2 * cur + 1, left, mid)
        self.build(nums, 2 * cur + 2, mid + 1, right)

        self.tree[cur] = self.merge(self.tree[2 * cur + 1], self.tree[2 * cur + 2])

    def update_val(self, cur:int, lo: int, hi: int, i:int, val:int):
        if lo == hi:
            for j in range(self.k):
                self.tree[cur].remain[j] = 0

            self.tree[cur].remain[val] = 1
            self.tree[cur].prod = val
            return

        mid = (lo + hi) // 2
        if i <= mid:
            self.update_val(2 * cur + 1, lo, mid, i, val)
        else:
            self.update_val(2 * cur + 2, mid  + 1, hi, i , val)

        self.tree[cur] = self.merge(self.tree[2 * cur + 1], self.tree[2 * cur + 2])

    def query_range(self, cur: int, lo: int, hi: int, i: int, j:int) -> Node:
        if i <= lo and hi <= j:
            return self.tree[cur]

        if j < lo or hi < i:
            return Node(self.k)

        mid = (lo + hi) // 2

        left_res = self.query_range(2 * cur + 1, lo, mid, i, j)
        right_res = self.query_range(2 * cur + 2, mid + 1, hi, i , j)

        return self.merge(left_res, right_res)


class Solution:
    def resultArray(self, nums: List[int], k: int, queries: List[List[int]]) -> List[int]:

        nums = [x % k for x in nums]

        n = len(nums)

        tree = SegmentTree(nums, k)

        win = []

        for index_i, value_i, start_i, xi in queries:
            val_mod = value_i % k

            tree.update_val(0,0, n - 1, index_i, val_mod)

            res_node = tree.query_range(0, 0, n - 1, start_i, n - 1)

            win.append(res_node.remain[xi])

        chno = win
        return chno
        