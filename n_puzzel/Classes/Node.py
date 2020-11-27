class Node:
    def __init__(self, puzzle_data, g_score=0, metric='manhattan',
                 print_inter_res=True, greedy=False, uniform_cost=False):
        self.puzzle_data = puzzle_data
        self.dim = len(puzzle_data)
        self.print_inter_res = print_inter_res
        self.puzzle_goal = self._generate_puzzle_goal()
        self.coords_empty_block = self._find_coords_empty_block()
        self.uniform_cost = uniform_cost
        self.g_score = g_score if not self.uniform_cost else 0
        self.metric = metric
        self.greedy = greedy
        self.f_score = self.get_f_score()
        self.predecessor = None

    def set_predecessor(self, predecessor):
        if isinstance(predecessor, Node):
            self.predecessor = predecessor

    def get_h_score(self):
        if self.metric == 'simple':
            return self._get_h_simple()
        if self.metric == 'manhattan':
            return self._get_h_manhattan()
        if self.metric == 'euclead':
            return self._get_h_euclead()

    def _get_h_simple(self):
        result = 0
        for i in range(self.dim):
            for j in range(self.dim):
                if self.puzzle_data[i][j] != self.puzzle_goal[i][j]:
                    result += 1
        return result

    def _get_h_manhattan(self):
        result = 0
        for i in range(self.dim):
            for j in range(self.dim):
                tile = self.puzzle_data[i][j]
                if tile == 0 or tile == '0':
                    continue
                row_goal, col_goal = self._find_coord_goal_state(tile)
                result += abs(row_goal - i) + abs(col_goal - j)
        return result

    def _get_h_euclead(self):
        result = 0
        for i in range(self.dim):
            for j in range(self.dim):
                tile = self.puzzle_data[i][j]
                if tile == 0 or tile == '0':
                    continue
                row_goal, col_goal = self._find_coord_goal_state(tile)
                result += (row_goal - i) ** 2 + abs(col_goal - j) ** 2
        return result

    def _find_coord_goal_state(self, tile):
        for i in range(self.dim):
            for j in range(self.dim):
                if self.puzzle_goal[i][j] == tile:
                    return i, j

    def get_f_score(self):
        if not self.greedy:
            return self.get_h_score() + self.g_score
        return self.get_h_score()

    def _find_coords_empty_block(self):
        for i in range(self.dim):
            for j in range(self.dim):
                if self.puzzle_data[i][j] == 0 or self.puzzle_data[i][j] == '0':
                    return i, j
        return None

    def _right(self):
        if self._check_possible_move('right'):
            return [self.coords_empty_block[0], self.coords_empty_block[1] + 1]
        return False

    def _left(self):
        if self._check_possible_move('left'):
            return [self.coords_empty_block[0], self.coords_empty_block[1] - 1]
        return False

    def _top(self):
        if self._check_possible_move('top'):
            return [self.coords_empty_block[0] - 1, self.coords_empty_block[1]]
        return False

    def _bottom(self):
        if self._check_possible_move('bottom'):
            return [self.coords_empty_block[0] + 1, self.coords_empty_block[1]]
        return False

    def _change_coords_empty_block(self, new_coords):
        if new_coords[0] < 0 or new_coords[0] > self.dim or new_coords[1] < 0 or new_coords[1] > self.dim:
            raise ValueError(f'New coords are incorrect {new_coords}')
        temp_puzzle = [i.copy() for i in self.puzzle_data]
        temp_val = temp_puzzle[new_coords[0]][new_coords[1]]
        temp_puzzle[new_coords[0]][new_coords[1]] = \
            self.puzzle_data[self.coords_empty_block[0]][self.coords_empty_block[1]]
        temp_puzzle[self.coords_empty_block[0]][self.coords_empty_block[1]] = temp_val
        return temp_puzzle

    def _check_possible_move(self, direction):
        if direction == 'top':
            return self.coords_empty_block[0] - 1 >= 0
        elif direction == 'bottom':
            return self.coords_empty_block[0] + 1 < self.dim
        elif direction == 'right':
            return self.coords_empty_block[1] + 1 < self.dim
        elif direction == 'left':
            return self.coords_empty_block[1] - 1 >= 0
        else:
            raise ValueError('No such direction to move')

    def find_other_coords(self):
        nodes = []
        for find_direction in [self._top, self._bottom, self._right, self._left]:
            coord = find_direction()
            if coord:
                nodes.append(
                    Node(
                        self._change_coords_empty_block(coord),
                        self.g_score + 1,
                        self.metric,
                        self.print_inter_res,
                        self.greedy,
                        self.uniform_cost,
                    )
                )
        return nodes

    def _generate_puzzle_goal(self):
        mat = [['0'] * self.dim for i in range(self.dim)]
        st = 1
        for v in range(self.dim // 2):
            for i in range(self.dim - v * 2):
                mat[v][i+v] = str(st)
                st += 1
            for i in range(v + 1, self.dim - v):
                mat[i][-v-1] = str(st)
                st += 1
            for i in range(v + 1, self.dim - v):
                mat[-v-1][-i-1] = str(st)
                st += 1
            for i in range(v + 1, self.dim - (v + 1)):
                mat[-i-1][v] = str(st)
                st += 1
        if self.dim % 2 == 0:
            mat[self.dim // 2][self.dim // 2 - 1] = '0'
        return mat

    def visualize_current_state(self):
        for i in range(self.dim):
            print(' '.join(self.puzzle_data[i]))
        print(f'F_score: {self.f_score}\n')

    def _count_inversions(self):
        res = 0
        puzzele_v = [item for row in self.puzzle_data for item in row]
        puzzle_goal_v = [item for row in self.puzzle_goal for item in row]
        for i in range(self.dim * self.dim - 1):
            for j in range(i + 1, self.dim * self.dim):
                vi = puzzele_v[i]
                vj = puzzele_v[j]
                if puzzle_goal_v.index(vi) > puzzle_goal_v.index(vj):
                    res += 1
        return res

    def is_solvable(self):
        puzzle_goal_list = [i for row in self.puzzle_goal for i in row]
        inversions = self._count_inversions()
        solved_zero_row = puzzle_goal_list.index('0') // self.dim
        solved_zero_column = puzzle_goal_list.index('0') % self.dim
        taxicab = abs(self.coords_empty_block[0] - solved_zero_row) + abs(self.coords_empty_block[1] - solved_zero_column)
        if taxicab % 2 == 0 and inversions % 2 == 0:
            return True
        if taxicab % 2 == 1 and inversions % 2 == 1:
            return True
        return False
