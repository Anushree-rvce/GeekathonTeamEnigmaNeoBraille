if __name__=="__main__":
    try:
        braille_file = open("braille_question.txt","w")
        #Braille equivalents
        charset = {'@': '010000', ' ': '000000', '#': '010111', '"': '000100', '%': '110001', '$': '111001', "'": '000010', '&': '111011',
             ')': '011111', '(': '101111', '+': '010011', '*': '100001', '-': '000011', ',': '000001', '/': '010010', '.': '010001',
             '1': '001000', '0': '000111', '3': '001100', '2': '001010', '5': '001001', '4': '001101', '7': '001111', '6': '001110',
             '9': '000110', '8': '001011', ';': '000101', ':': '100101', '=': '111111', '<': '101001', '?': '110101', '>': '010110',
             'A': '100000', '!': '011011', 'C': '110000', 'B': '101000', 'E': '100100', 'D': '110100', 'G': '111100', 'F': '111000',
             'I': '011000', 'H': '101100', 'K': '100010', 'J': '011100', 'M': '110010', 'L': '101010', 'O': '100110', 'N': '110110',
             'Q': '111110', 'P': '111010', 'S': '011010', 'R': '101110', 'U': '100011', 'T': '011110', 'W': '011101', 'V': '101011',
             'Y': '110111', 'X': '110011', '[': '011001', 'Z': '100111', ']': '111101', '\\': '101101', '_': '010101', '^': '010100'}
        for i in charset:
            charset[i]=charset[i].replace('0','.')
            charset[i]=charset[i].replace('1','o')
        with open("question.txt","r") as question_file:
            questions = question_file.read().upper().split("\n")
            print("Question paper scanned from a file named \"question.txt\"")
            for q in questions:
                for j in range(3):#3 - rows
                    for character in q:
                        braille_file.write(charset[character][j*2:j*2+2])
                        braille_file.write("  ")
                    braille_file.write("\n")
                braille_file.write("\n")
        print("Braille question paper generated in a file named \"braille_question.txt\"")
        braille_file.close()
    except Exception as e:
        print("Error: "+str(e))
