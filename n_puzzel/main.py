from Classes.Parser import Parser
from Classes.Node import Node
from Classes.Game import Game
import argparse


def main():
    parser = argparse.ArgumentParser(description='n-puzzle')
    parser.add_argument('-d', '--distance-metric', help='Distance function', choices=['simple', 'manhattan', 'euclead'], default='manhattan')
    parser.add_argument('-v', '--verbose', help='Verbose intermediate results', action='store_true')
    parser.add_argument('-g', '--greedy', help='Use greedy algorithm', action='store_true')
    parser.add_argument('-u', '--uniform', help='Use uniform cost', action='store_true')
    parser.add_argument('file', help='input file')
    parser = parser.parse_args()

    try:
        data_parser = Parser(file_name=parser.file)
        node = Node(puzzle_data=data_parser.get_data(), metric=parser.distance_metric,
                    print_inter_res=parser.verbose, greedy=parser.greedy, uniform_cost=parser.uniform)
        game = Game(start_node=node)
        game.solve()
        exit(0)
    except ValueError as error:
        print(error)
        exit(2)


if __name__ == "__main__":
    main()