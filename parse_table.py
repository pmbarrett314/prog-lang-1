import csv



def make_token_define(token_name, token_code):
	return f"#define {token_name:17}{token_code}"


def main():
	with open("chart.csv", "r") as chartfile:
		chartreader = csv.reader(chartfile)
		for row in chartreader:
			print(make_token_define(row[2], row[1]))



if __name__=="__main__":
	main()