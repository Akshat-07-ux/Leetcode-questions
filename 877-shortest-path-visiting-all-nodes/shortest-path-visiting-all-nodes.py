from queue import deque
class Solution:
    def shortestPathLength(self, graph: list[list[int]]) -> int:

        n, target = len(graph), (1 << len(graph)) - 1
        q = deque([(i, 1 << i, 0) for i in range(n)])
        seen = {(i, 1 << i) for i in range(n)}

        while q:
            u, mask, dist = q.popleft()
            if mask == target:
                return dist

            for v in graph[u]:
                nxt = (v, mask | (1 << v))
                if nxt not in seen:
                    seen.add(nxt)
                    q.append((*nxt, dist + 1))
        