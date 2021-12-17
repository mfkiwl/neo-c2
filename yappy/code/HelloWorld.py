def xassert(msg, exp):
    print msg
    if exp :
        print "->OK"
    else :
        print "->error"
        exit 1

a=123
xassert("var test", a == 123)

a=234
xassert("var test2", a == 234)

def fun():
    return 1

xassert("fun test", fun() == 1)

def fun2(a,b):
    return a + b

xassert("fun test2", fun2(1,2) == 3)

import Module

print Module.fun();

xassert("Module test", Module.fun() == 1)

xassert("Module test2", Module.a == 2)
Module.a = 3

xassert("Module test3", Module.a == 3)

class ClassA():
    a = 1
    
    def __init__(self):
        self.a = 9
        print "HELLO METHOD"
    
    def method(self):
        print self
        return self.a

xassert("Class test1", ClassA.a == 1)

xassert("Class test2", Module.ClassB.a == 3)

b = ClassA()

xassert("Object test1", b.a == 9)
xassert("Object test2", b.method() == 9)

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
