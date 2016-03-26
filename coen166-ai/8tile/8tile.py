# 8 Tile Solver
# Written by Daniel Ong for COEN 166: Artificial Intelligence
#
# A comparison of the real time taken to solve an n tile puzzle using:
# 1. Iterative deepening depth-first search
# 2. Depth-first search
# 3. Breadth-first search
# Tested on the 8 tile puzzle
# Some code adapted from Edd Mann's blog post: http://eddmann.com/posts/using-iterative-deepening-depth-first-search-in-python/

import itertools
import random
import time

def id_dfs(puzzle, goal, get_moves):
    def idfs(path, depth):
        # unable to search when depth is 0
        if depth == 0:
            return
        # check if goal has been reached
        if path[-1] == goal:
            return path
        # iterate through possible moves
        for move in get_moves(path[-1]):
            # run this function on unvisited nodes, decrementing depth
            if move not in path:
                next_path = idfs(path + [move], depth - 1)
                if next_path:
                    return next_path
    # runs dfs up to a limit of depth
    # depth increases until goal is found
    for depth in itertools.count():
        path = idfs([puzzle], depth)
        if path:
            return path
            
def num_matrix(rows, cols, steps=25):
    # fill default puzzle
    nums = list(range(1, rows * cols)) + [0]
    goal = [ nums[i:i+rows] for i in range(0, len(nums), rows) ]

    get_moves = num_moves(rows, cols)
    puzzle = goal
    # shuffle puzzle
    for steps in range(steps):
        puzzle = random.choice(get_moves(puzzle))

    return puzzle, goal
    
def num_moves(rows, cols):
    def get_moves(subject):
        moves = []

        zrow, zcol = next((r, c)
            for r, l in enumerate(subject)
                for c, v in enumerate(l) if v == 0)

        def swap(row, col):
            import copy
            s = copy.deepcopy(subject)
            s[zrow][zcol], s[row][col] = s[row][col], s[zrow][zcol]
            return s

        # north
        if zrow > 0:
            moves.append(swap(zrow - 1, zcol))
        # east
        if zcol < cols - 1:
            moves.append(swap(zrow, zcol + 1))
        # south
        if zrow < rows - 1:
            moves.append(swap(zrow + 1, zcol))
        # west
        if zcol > 0:
            moves.append(swap(zrow, zcol - 1))

        return moves
    return get_moves
    
def dfs(puzzle, goal, get_moves):
    # maintain a stack of paths
    stack = []
    # push the first path into the stack
    stack.append([puzzle])
    while stack:
        # get the first path from the stack
        path = stack.pop(0)
        # get the last node from the path
        node = path[-1]
        # path found
        if node == goal:
            return path
        # enumerate all adjacent nodes, construct a new path and push it into the stack
        for adjacent in get_moves(node):
            if adjacent not in path:
                new_path = list(path)
                new_path.append(adjacent)
                stack.append(new_path)
        
def bfs(puzzle, goal, get_moves):
    # maintain a queue of paths
    queue = []
    # push the first path into the queue
    queue.append([puzzle])
    while queue:
        # get the first path from the queue
        path = queue.pop(0)
        # get the last node from the path
        node = path[-1]
        # path found
        if node == goal:
            return path
        # enumerate all adjacent nodes, construct a new path and push it into the queue
        for adjacent in (get_moves(node)):
            if adjacent not in path:
                new_path = list(path)
                new_path.append(adjacent)
                queue.append(new_path)

                
if __name__ == '__main__':
    reps = 1
    rows = cols = 4
    iddfs_total = bfs_total = dfs_total = 0
    shuffles = 30
    for n in range(reps):
        print('Solving puzzle #', n)
        # generate puzzle
        puzzle, goal = num_matrix(rows,cols, shuffles)
        print('Initial puzzle: ')
        for row in puzzle:
            print(row)
        print('\n')
        
        print('solving BFS')
        # bfs
        bfs_t0 = time.time()
        solution = bfs(puzzle, goal, num_moves(rows,cols))
        bfs_t1 = time.time()
        bfs_total += (bfs_t1 - bfs_t0)
        print('BFS solved')
        
        print('solving DFS')
         # dfs
        dfs_t0 = time.time()
        solution = id_dfs(puzzle, goal, num_moves(rows,cols))
        dfs_t1 = time.time()
        dfs_total += (dfs_t1 - dfs_t0)
        print('DFS solved')
        
        print('solving ID_DFS')
        # id_dfs
        iddfs_t0 = time.time()
        solution = id_dfs(puzzle, goal, num_moves(rows,cols))
        iddfs_t1 = time.time()
        iddfs_total += (iddfs_t1 - iddfs_t0)
        print('ID_DFS solved')
        
        print('Solution path')
        for state in solution[1:]:
            for row in state:
                print(row)
            print('\n')
    
    print('Solution path length:', len(solution))
    print('Total time to solve', reps, 'puzzles with id_dfs:', iddfs_total, 'seconds.')
    print('Total time to solve', reps, 'puzzles with dfs:', dfs_total, 'seconds.')
    print('Total time to solve', reps, 'puzzles with bfs:', bfs_total, 'seconds.')