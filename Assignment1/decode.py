def write(ch, subs, file):
    if ch == None:
        return
    elif ch.isnumeric():
        file.write(str((int(ch)-4)%10))    
    elif subs.get(ch.lower()) == None:
        file.write(ch)
    else:
        if ch.islower():
            file.write(subs[ch].lower())
        else:
            file.write(subs[ch.lower()].upper())
    # file.write(ch)

encrypt = open("cipher.txt", "r")
encrypt2 = open("cipher.txt", "r")
subs_cipher = open("subs.txt", "r")
perm_cipher = open("perm.txt", "r")

msg = open("message.txt", "w")

subs = {}
for line in subs_cipher.readlines():
    words = line.split()
    subs[words[0]] = words[1]
subs_cipher.close()

perm = {}
b = int(perm_cipher.readline())
for line in perm_cipher.readlines():
    words = line.split()
    perm[int(words[0])-1] = int(words[1])-1
perm_cipher.close()

words = [None]*b
spaces = []
lineb = []
i = 0
num = 0
loop = 0
for ch in encrypt.read():
    # print(loop)
    loop += 1
    num += 1
    # print(ch, sep='', end='')
    # ch = ch.lower()
    if(ch == '\n'):
        continue
    elif(ch == ' '):
        continue
    words[(i+10)%b] = ch
    i += 1
    i %= b
    # print(ch, i, num)
    if i == 0 or loop == 325:
        # print(num)
        j = 0
        for c in encrypt2.read(num):
            # print(c)
            if c != ' ' and c != '\n':
                write(words[j], subs, msg)
                j += 1
            else:
                write(c, subs, msg)
        words = [None]*b
        num = 0

# write(words, subs, msg)

encrypt.close()
encrypt2.close()
msg.close()