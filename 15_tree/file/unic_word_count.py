import sys

#d = set()
#for word in sys.stdin.read().split():
#    word_letters = ''.join(filter(str.isalpha, word)).lower()
#    if not word_letters:
#        continue
#    d.add(word_letters)
    
d = {''.join(filter(str.isalpha, word)).lower() for word in sys.stdin.read().split() if word.isalpha}

print(*d, sep='\n')    
print(len(d))