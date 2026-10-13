class Solution:
    def mincostToHireWorkers(self, quality: list[int], wage: list[int], k: int) -> float:


        workers = sorted([(w /q, q) for q, w in zip(quality, wage)])

        max_heap = []
        quality_sum = 0
        min_cost = float('inf')

        for ratio, q in workers:
            heapq.heappush(max_heap, -q)
            quality_sum += q

            if len(max_heap) > k:
                quality_sum += heapq.heappop(max_heap)

            if len(max_heap) == k:
                min_cost = min(min_cost, ratio * quality_sum)

        return min_cost
        