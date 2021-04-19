import time
f = open("inp.txt","r")
fout = open("out.txt","w")
list_of_lines = f.readlines()
dictValues = dict()
constantFoldedList = []
print("Quadruple form after Constant Folding")
print("-------------------------------------")
for i in list_of_lines:
    i = i.strip("\n")
    op,arg1,arg2,res = i.split()
    if(op in ["+","-","*","/"]):
        if(arg1.isdigit() and arg2.isdigit()):
            result = eval(arg1+op+arg2)
            dictValues[res] = result
            print("=",result,"NULL",res)
            constantFoldedList.append(["=",result,"NULL",res])
        elif(arg1.isdigit()):
            if(arg2 in dictValues):
                result = eval(arg1+op+dictValues[arg2])
                dictValues[res] = result
                print("=",result,"NULL",res)
                constantFoldedList.append(["=",result,"NULL",res])
            else:
                print(op,arg1,arg2,res)
                constantFoldedList.append([op,arg1,arg2,res])
        elif(arg2.isdigit()):
            if(arg1 in dictValues):
                result = eval(dictValues[arg1]+op+arg2)
                dictValues[res] = result
                print("=",result,"NULL",res)
                constantFoldedList.append(["=",result,"NULL",res])
            else:
                print(op,arg1,arg2,res)
                constantFoldedList.append([op,arg1,arg2,res])
        else:
            flag1=0
            flag2=0
            arg1Res = arg1
            if(arg1 in dictValues):
                arg1Res = str(dictValues[arg1])
                flag1 = 1
            arg2Res = arg2
            if(arg2 in dictValues):
                arg2Res = str(dictValues[arg2])
                flag2 = 1
            if(flag1==1 and flag2==1):
                result = eval(arg1Res+op+arg2Res)
                dictValues[res] = result
                print("=",result,"NULL",res) 
                constantFoldedList.append(["=",result,"NULL",res])
            else:
                print(op,arg1Res,arg2Res,res)
                constantFoldedList.append([op,arg1Res,arg2Res,res])
            
    elif(op=="="):
        if(arg1.isdigit()):
            dictValues[res]=arg1
            print("=",arg1,"NULL",res)
            constantFoldedList.append(["=",arg1,"NULL",res])
        else:
            if(arg1 in dictValues):
                print("=",dictValues[arg1],"NULL",res)
                constantFoldedList.append(["=",dictValues[arg1],"NULL",res])
            else:
                print("=",arg1,"NULL",res)
                constantFoldedList.append(["=",arg1,"NULL",res])
    
    else:
        print(op,arg1,arg2,res)
        constantFoldedList.append([op,arg1,arg2,res])

print("\n")
print("Constant folded expression - ")
print("--------------------")
for i in constantFoldedList:
    if(i[0]=="="):
        print(i[3],i[0],i[1])
    elif(i[0] in ["+","-","*","/","==","<=","<",">",">="]):
        print(i[3],"=",i[1],i[0],i[2])
    elif(i[0] in ["if","goto","label","not"]):
        if(i[0]=="if"):
            print(i[0],i[1],"goto",i[3])
        if(i[0]=="goto"):
            print(i[0],i[3])
        if(i[0]=="label"):
            print(i[3],":")
        if(i[0]=="not"):
            print(i[3],"=",i[0],i[1])


print("\n")
print("After dead code elimination - ")
print("------------------------------")
for i in constantFoldedList:
    with open("deadcode.txt","w") as f:
        if(i[0]=="="):
            pass
        elif(i[0] in ["+","-","*","/","==","<=","<",">",">="]):
            print(i[3],"=",i[1],i[0],i[2])
            f.write(str(i[3])+"="+str(i[1])+str(i[0])+str(i[2]))
        elif(i[0] in ["if","goto","label","not"]):
            if(i[0]=="if"):
                print(i[0],i[1],"goto",i[3])
                f.write(str(i[0])+str(i[1])+"goto"+str(i[3]))
        if(i[0]=="goto"):
            print(i[0],i[3])
            f.write(str(i[0])+str(i[3]))
        if(i[0]=="label"):
            print(i[3],":")
            f.write(str(i[3])+":")
        if(i[0]=="not"):
            print(i[3],"=",i[0],i[1])
            f.write(str(i[3])+"="+str(i[0])+str(i[1]))

def existslabel(lines, i):

    if(i == 0):
        return 0
    while(i>=0):
        if(len(lines[i].split()) == 2):
            return 1
        i = i - 1
    return 0

        

def exists_lhs(lines, variable, start, end):
    for i in range(start, end):
        if(lines[i].split()[0] == variable):
            return 1
    return 0

def exists_rhs(lines, lhs, start):

    for i in range(len(lines)-1, start-1, -1):

        if(len(lines[i].split()) == 5):
            rhs1 = lines[i].split()[2]
            rhs2 = lines[i].split()[4]

            if(rhs1 == lhs or rhs2 == lhs):              
                return i

        elif(len(lines[i].split()) == 3):
            rhs = lines[i].split()[2]
            if(rhs == lhs):
                return i

        elif(len(lines[i].split()) == 4):

            rhs = lines[i].split()[1]

            l1 = ""

            l2 = ""
            fl = 0
            for x in rhs:
                if x in [">", "<", "=", "!"]:
                    fl = 1
                    continue
                if (x == "="):
                    continue
                if(fl == 0):
                    l1 = l1 + x
                if(fl == 1):
                    l2 = l2 + x
            if(l1 == lhs or l2 == lhs):
                return i
    return -1
            
def findLoopLines(lines):

    gotoindex = dict()
    loopblock = []
    labelindex = dict()

    for i in range(len(lines)):

        lines[i] = lines[i].strip("\n")
        if(len(lines[i].split())==2 and lines[i].split()[0] == 'goto'):
            gotoindex[lines[i].split()[1]] = i
        if(len(lines[i].split()) == 2 and lines[i].split()[1] == ':'):
            labelindex[lines[i].split()[0]] = i

    for key in gotoindex:

        if(gotoindex[key]>labelindex[key]):
            loopblock.append([labelindex[key], gotoindex[key]])

    return loopblock



def loopMotion(lines):

    for i in range(len(lines)):

        lines[i] = lines[i].strip("\n")
    loopblock = findLoopLines(lines)

    for i in loopblock:

        initloc = i[0]
        for j in range(i[0], i[1]):

            if(len(lines[j].split()) == 3 and (lines[j].split()[0][0]!='*' and lines[j].split()[2].isdigit())):
                temp = lines.pop(j)
                lines.insert(initloc, temp)
                initloc+=1

            if(len(lines[j].split())==3 and (lines[j].split()[0][0]!='*' and lines[j].split()[2][0]!='*')):
                arg = lines[j].split()[2]

                if(not exists_lhs(lines, arg, initloc, i[1])):

                    temp = lines.pop(j)
                    lines.insert(initloc, temp)
                    initloc+=1

            if(len(lines[j].split()) == 5):

                arg1 = lines[j].split()[2]
                arg2 = lines[j].split()[4]


                if(arg1.isdigit() and arg2.isdigit() and (lines[j].split()[0][0]!='*')):

                    temp = lines.pop(j)
                    lines.insert(initloc, temp)
                    initloc+=1

                elif(arg1.isdigit()and (arg2[0]!='*' and lines[j].split()[0][0]!='*')):

                    if(not exists_lhs(lines, arg2, initloc, i[1])):
                       temp = lines.pop(j)
                       lines.insert(i[0], temp)

                elif(arg2.isdigit()and (arg1[0]!='*' and lines[j].split()[0][0]!='*')):

                    if(not exists_lhs(lines, arg1, initloc, i[1])):
                        temp = lines.pop(j)
                        lines.insert(initloc, temp)
                        initloc+=1

                else:

                    if(not exists_lhs(lines, arg1, initloc, i[1]) and not exists_lhs(lines, arg2, initloc, i[1]) and (arg1[0]!='*' and arg2[0]!='*' and lines[j].split()[0][0]!='*')):

                        temp  = lines.pop(j)
                        lines.insert(initloc, temp)
                        initloc+=1

    return lines, loopblock
    
    
def checkArray(token, lines, i):

    if('[' in token):
        newptr = "*"
        sub = ""
        trav = 0

        while(token[trav]!='['):
            newptr+=token[trav]
            trav+=1
        trav+=1

        while(token[trav]!=']'):
            sub+=token[trav]
            trav+=1
        print(newptr)
        print(trav)
        return [newptr, sub]

    else:
        return

def additem(newlist, out):

    array = out[0]
    subscript = out[1]
    newstr = array + " = " + array + " + " + subscript
    newlist.append(newstr)
    return newlist

    
fin = open("icg2.txt", "r")
fout = open("Optim_ICG.txt", "w")
lines = fin.readlines()
print()
print("______________________")
print()
#lines = modifyArray(lines)
print("Loop Invariant Code Motion")
print("__________________________")
print()
lines, loopblock = loopMotion(lines)
for i in lines:
    print(i)


               


