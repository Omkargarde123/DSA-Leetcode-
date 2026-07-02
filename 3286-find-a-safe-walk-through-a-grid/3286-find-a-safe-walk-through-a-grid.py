from collections import deque

class Solution:
    def findSafeWalk(self, grid: list[list[int]], health: int) -> bool:
        m, n = len(grid), len(grid[0])
        
        # min_loss[i][j] will store the minimum health lost to reach cell (i, j)
        min_loss = [[float('inf')] * n for _ in range(m)]
        
        # Initialize deque for 0-1 BFS: (row, col)
        q = deque([(0, 0)])
        min_loss[0][0] = grid[0][0]
        
        # Directions for moving up, down, left, right
        directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        
        while q:
            r, c = q.popleft()
            
            # If we reached the destination, we can early exit
            if r == m - 1 and c == n - 1:
                break
                
            for dr, dc in directions:
                nr, nc = r + dr, c + dc
                
                # Check grid boundaries
                if 0 <= nr < m and 0 <= nc < n:
                    weight = grid[nr][nc]
                    # If we found a path with less health loss
                    if min_loss[r][c] + weight < min_loss[nr][nc]:
                        min_loss[nr][nc] = min_loss[r][c] + weight
                        
                        # 0-1 BFS logic
                        if weight == 0:
                            q.appendleft((nr, nc))
                        else:
                            q.append((nr, nc))
                            
        # We need at least 1 health remaining, meaning total loss must be < health
        return min_loss[m - 1][n - 1] < health