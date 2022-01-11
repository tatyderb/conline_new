import sys

d = {}
for word in sys.stdin.read().split():
    word_letters = ''.join(filter(str.isalpha, word)).lower()
    # print(word, word_letters)
    if not word_letters:
        continue
    d[word_letters] = 1 + d.get(word_letters, 0);
    
arr = sorted(d.items(), key=lambda x: (-x[1], x[0]))
# print(arr)

for x in arr:
     print(*x)
