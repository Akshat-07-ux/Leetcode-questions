class Solution:
    def checkOverlap(self, radius: int, xCenter: int, yCenter: int, x1: int, y1: int, x2: int, y2: int) -> bool:
        close_x = max(x1, min(xCenter, x2))
        close_y = max(y1, min(yCenter, y2))

        dx = xCenter - close_x
        dy = yCenter - close_y

        return dx * dx + dy * dy <= radius * radius