class Solution:
    def largestOverlap(self, img1: List[List[int]], img2: List[List[int]]) -> int:
        l = len(img1)
        point1 = [(a, b) for a in range(l) for b in range(l) if img1[a][b] == 1]
        point2 = [(a, b) for a in range(l) for b in range(l) if img2[a][b] == 1]

        images = Counter()
        for a1, b1 in point1:
            for a2, b2 in point2:
                images[(a2 - a1, b2 - b1)] += 1

        return max(images.values()) if images else 0
        