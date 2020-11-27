from linear_regression import LinearRegression
from my_exeption import ParserException

from colorama import Fore, Back, Style
import sys

def main():
	try:
		model = LinearRegression(filename=None, mode='No_file')
		model.predict_data_value()
	except IOError as e:
		print(Style.BRIGHT + Fore.RED + 'I/O Error: ' + Style.RESET_ALL + Fore.RESET + str(e))
	except ParserException as e:
		print(Style.BRIGHT + Fore.RED + 'ParserException: ' + Style.RESET_ALL + Fore.RESET + str(e))
	except LogisticRegressionException as e:
		print(Style.BRIGHT + Fore.RED + 'Logistic Regression Exception: ' + Style.RESET_ALL + Fore.RESET + str(e))

if __name__ == '__main__':
	main()
