import sys

def xassert(msg:str, exp:bool) -> None:
   print(msg)
   if exp :
        print("->OK")
   else :
        print("->error")
        sys.exit(1)

a:int=123
xassert("var test", a == 123)

a=234
xassert("var test2", a == 234)

def fun() -> int:
    return 1

xassert("fun test", fun() == 1)

def fun2(a:int,b:int) -> int:
    return a + b

xassert("fun test2", fun2(1,2) == 3)

import Module

print(Module.fun())

xassert("Module test", Module.fun() == 1)

xassert("Module test2", Module.a == 2)
Module.a = 3

xassert("Module test3", Module.a == 3)
xassert("Module test4", Module.fun3(1,8) == 9)

class ClassA:
    A = 1
    
    def __init__(self):
        self.a:int = 9
        print("HELLO METHOD")

    def method(self) -> int:
        print(self)
        return self.a
    
    def method2(self, a:int, b:int) -> int:
        return a + b

xassert("Class test1", ClassA.A == 1)

xassert("Class test2", Module.ClassB.a == 3)

b = ClassA()

xassert("Object test1", b.a == 9)
xassert("Object test2", b.method() == 9)
xassert("Object test3", b.method2(1,2) == 3)
xassert("len test", len("abc") == 3)
print(len("あいう"))
xassert("len test2", len("あいう") == 3)

li = [1,"aaa",3]

print(li)

xassert("list test1", li[0] == 1 && li[1] == "aaa" && li[2] == 3 && len(li) == 3);

li2 = li[0:2]

xassert("list test2", li[0] == 1 && li[1] == "aaa" && len(li2) == 2)

li3 = li[:]

xassert("list test3", li3[0] == 1 && li3[1] == "aaa" && li3[2] == 3 && len(li3) == 3);

li4 = li[1:]

xassert("list test4", li4[0] == "aaa" && li4[1] == 3 && len(li4) == 2)

li5 = li[:2]

xassert("list test5", li5[0] == 1 && li[1] == "aaa" && len(li5) == 2)

li6 = [0,1,2,3,4,5,6,7,8,9]

li7 = li6[0:10:2]

xassert("list test6", li7[0] == 0 && li7[1] == 2 && li7[2] == 4 && li7[3] == 6 && li7[4] == 8);

li8 = li6[::2]

xassert("list test7", li8[0] == 0 && li8[1] == 2 && li8[2] == 4 && li8[3] == 6 && li8[4] == 8);

print li6[1::2]

li9 = [1,2] + [3,4]

xassert("list test8", li9[0] == 1 && li9[1] == 2 && li9[2] == 3 && li9[3] == 4 && len(li9) == 4)

xassert("str test", "AAA" + "BBB" == "AAABBB")

li10 = [1,2] * 2

xassert("list test9", li10[0] == 1 && li10[1] == 2 && li10[2] == 1 && li10[3] == 2 && len(li10) == 4)

xassert("str test2", "ABC" * 2 == "ABCABC")

xassert("list test10", [1,2] == [1,2])

xassert("list test11", [[1,2], [1,2]] == [[1,2], [1,2]])

class ListTestClass:
    def __init__(self,a,b):
        self.a = a
        self.b = b

xassert("list test", [ListTestClass(1,2),ListTestClass(3,4)] == [ListTestClass(1,2),ListTestClass(3,4)])

xassert("str test 3", int("1") + int("2") == 3);

xassert("str test 4", str(1) + str(2) == "12");
xassert("str test 5", str([1,2,3]) == "[1,2,3]");

#
#print "HELLO WORLD"

#def fun():
#    print "FUN"
#
#fun()
#fun()
#
#if True:
#    print "IF TRUE"
#elif True:
#    print "ELIF TRUE"
#else:
#    print "IF FALSE"
#
#
#fun();
#
#
#while True:
#    print "WHILE HELLO"
#    break
#else:
#    print "WHILE ELSE"
#
#a=123
#xassert("var test", a == 123)
#
#a=234
#
#xassert("var test2", a==234)
#
#def funX(a, b):
#    return a + b
#
##print funX(1,2)
#
##xassert("fun test", funX(1,2) == 3)
#
#print "TEST FINISH"
#
#
