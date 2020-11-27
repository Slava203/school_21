from my_exeption import ParserException

from colorama import Fore, Back, Style

class WeightsParser:
	def __init__(self, filename):
		self.__line_number = 0
		with open(filename, 'r') as weights_file:
			self.tet = self.__parse_line(weights_file.readline().strip(), 2)
			# self.tet_1 = self.__parse_line(weights_file.readline().strip(), 1)

	def __parse_line(self, line, num_terms):
		self.__line_number += 1
		tokens = line.split()
		if len(tokens) != num_terms:
			raise ParserException('invalid number of terms at ' +
				Fore.GREEN + 'line ' + str(self.__line_number) + Fore.RESET + ': ' +
				Fore.MAGENTA + line + Fore.RESET + '\n (expecting %d terms)' % num_terms)
		lst = []
		for token in tokens:
			try:
				lst.append(float(token))
			except ValueError:
				raise ParserException('invalid term at ' +
					Fore.GREEN + 'line ' + str(self.__line_number) + Fore.RESET + ': ' +
					Fore.MAGENTA + token + Fore.RESET)
		return lst
