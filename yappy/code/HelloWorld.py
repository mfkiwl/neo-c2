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
