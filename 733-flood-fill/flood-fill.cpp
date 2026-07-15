#include <vector>

using namespace std;

class Solution {
private:
    void dfs(vector<vector<int>>& image, int r, int c, int initialColor, int newColor) {
        // Boundary checks and color match check
        if (r < 0 || r >= image.size() || c < 0 || c >= image[0].size() || image[r][c] != initialColor) {
            return;
        }

        // Update the color of the current pixel
        image[r][c] = newColor;

        // Recursively visit all 4 adjacent pixels
        dfs(image, r + 1, c, initialColor, newColor); // Down
        dfs(image, r - 1, c, initialColor, newColor); // Up
        dfs(image, r, c + 1, initialColor, newColor); // Right
        dfs(image, r, c - 1, initialColor, newColor); // Left
    }

public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int initialColor = image[sr][sc];
        
        // If the starting pixel already has the target color, no operation is needed
        if (initialColor != color) {
            dfs(image, sr, sc, initialColor, color);
        }
        
        return image;
    }
};