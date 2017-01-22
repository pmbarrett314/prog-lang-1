import csv



def format_token_define(token_name, token_code):
	return f"#define {token_name:17}{token_code}"

def make_token_defines(filename):
	with open(filename, "r") as chartfile:
		chartreader = csv.reader(chartfile)
		for row in chartreader:
			print(format_token_define(row[2], row[1]))

def format_single_caracter_token(token,token_name):
	if(token=="\\"):
		token="\\\\"
	return f"\tcase '{token}': return {token_name}; break;"

def make_single_character_switch(filename):
	with open(filename, "r") as chartfile:
		chartreader = csv.reader(chartfile)
		print("swtich(token){")
		for row in chartreader:
			if(len(row[0])==1):
				print(format_single_caracter_token(row[0],row[2]),end=None)
		print("\tdefault: return -1; break;\n\t}")

def format_keyword_token(token,token_name):
	token_len=len(token)
	return f"\tif(strncmp(lexeme, \"{token}\", {token_len})==0) return {token_name};"

def make_keyword_defines(filename):
	with open(filename, "r") as chartfile:
		chartreader = csv.reader(chartfile)
		for row in chartreader:
			if(len(row[0])>1 and int(row[1])<4000):
				print(format_keyword_token(row[0],row[2]),end=None)


def main():
	chartfilename = "chart.csv"
	make_token_defines(chartfilename)
	make_single_character_switch(chartfilename)
	make_keyword_defines(chartfilename)



if __name__=="__main__":
	main()