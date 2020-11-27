from Classes.Node import Node
from time import perf_counter

class Game:
    def __init__(self, start_node: Node):
        self.start_node = start_node
        self.open = []
        self.close = set()
        self.count_selected = 0
        self.count_max_open = 0
        self.count_max_close = 0

    def solve(self):
        if not self.start_node.is_solvable():
            raise ValueError('This puzzle is not solvable')
        self.open.append(self.start_node)

        start_time = perf_counter()
        while len(self.open) != 0:
            process = self._get_min_node()
            if process.print_inter_res:
                process.visualize_current_state()
            self.count_selected += 1
            if process.get_h_score() == 0:
                end_time = perf_counter()
                path_solutions = self._get_path(process)
                self._print_total_stat(path_solutions, work_time=end_time-start_time)
                self._print_path(path_solutions)
                return process
            self._remove_from_open(process)
            self.close.add(process)
            for state in process.find_other_coords():
                if self._find_node_in_close(state):
                    continue
                if not self._find_node_in_open(state):
                    state.set_predecessor(process)
                    self.open.append(state)
                else:
                    for i, opened in enumerate(self.open):
                        if opened.puzzle_data == state.puzzle_data and state.g_score < opened.g_score:
                            self.open[i].g_score = state.g_score
                            self.open[i].f_score = state.f_score
                            self.open[i].predecessor = state.predecessor
            count_max_open = len(self.open)
            if self.count_max_open < count_max_open:
                self.count_max_open = count_max_open
            count_max_close = len(self.close)
            if self.count_max_close < count_max_close:
                self.count_max_close = count_max_close

    def _print_total_stat(self, path, work_time):
        print('Total stats:')
        print('Max numbers SELECTED STATES:', self.count_selected)
        print('Max numbers at the same time:', self.count_max_open + self.count_max_close)
        print('Numbers of steps:', len(path) - 1)
        print('Heuristic function:', self.start_node.metric)
        print(f'Search duration: {work_time:.4f}\n')

    def _get_min_node(self) -> Node:
        return sorted(self.open, key=lambda x: x.f_score, reverse=False)[0]

    def _remove_from_open(self, node):
        for i, state in enumerate(self.open):
            if state.puzzle_data == node.puzzle_data:
                del self.open[i]

    def _find_node_in_close(self, node):
        for state in self.close:
            if state.puzzle_data == node.puzzle_data:
                return True
        return False

    def _find_node_in_open(self, node):
        for state in self.open:
            if state.puzzle_data == node.puzzle_data:
                return True
        return False

    @staticmethod
    def _get_path(node: Node):
        result = [node]
        while node.predecessor:
            result.append(node.predecessor)
            node = node.predecessor
        return result[::-1]

    @staticmethod
    def _print_path(path):
        print('All steps')
        for i, node in enumerate(path):
            print(f'Step {i}')
            node.visualize_current_state()
